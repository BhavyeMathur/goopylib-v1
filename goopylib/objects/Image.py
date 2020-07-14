from PIL import ImageTk, ImageFilter
from PIL import Image as Img

from math import gcd, ceil
from time import time as timetime
from os.path import isfile as osisfile

from goopylib.util import GraphicsError, resource_path

from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point
from goopylib.constants import ALIGN_OPTIONS

class Image(GraphicsObject):
    id_count = 0
    image_cache = {}  # tk photo images go here to avoid GC while drawn

    def __init__(self, p, filepath, align="center", cursor="arrow"):

        if not isinstance(p, Point):
            raise GraphicsError(f"\n\nGraphicsError: Image anchor point (p) must be a Point object, not {p}")
        if align not in ALIGN_OPTIONS:
            raise GraphicsError(f"\n\nGraphicsError: Image align must be one of {ALIGN_OPTIONS}, not {align}")

        if osisfile(f"textures/{filepath}"):
            self.texture = f"textures/{filepath}"
        elif osisfile(filepath):
            self.texture = filepath
        else:
            raise GraphicsError("\n\nGraphicdError: Image filepath is not valid. No such file or directory as "
                                f"{filepath}")

        self.image_id = Image.id_count
        Image.id_count = Image.id_count + 1

        self.texture = resource_path(self.texture)

        self.img_PIL = Img.open(self.texture)
        self.img = ImageTk.PhotoImage(self.img_PIL)

        self.initial_width = self.get_width()
        self.initial_height = self.get_height()

        self.rotation_img = self.img_PIL
        self.align = align

        self.anchor = p.clone()

        if align not in ["center", "bottom", "top", "left", "right"]:
            raise GraphicsError(f"\n\nGraphicsError: Image align must be one of center, bottom, top, left, or right, not {align}")

        self.x = self.anchor.x
        self.y = self.anchor.y

        GraphicsObject.__init__(self, [], cursor=cursor)

    # -------------------------------------------------------------------------
    # INTERNAL FUNCTIONS

    def __repr__(self):
        return "Image({}, {})".format(self.anchor, self.texture)

    def _draw(self, canvas, options):
        self.image_cache[self.image_id] = self.img  # save a reference

        p = self.anchor.clone()

        if self.align == "bottom":
            p.add_y(self.initial_height / -2)
        elif self.align == "top":
            p.add_y(self.initial_height / 2)
        elif self.align == "left":
            p.add_x(self.initial_width / 2)
        elif self.align == "right":
            p.add_x(self.initial_width / -2)

        if canvas != self.graphwin:
            init_width = abs(self.initial_width / canvas.trans.x_scale)
            init_height = abs(self.initial_height / canvas.trans.y_scale)

            self.rotation_img = self.rotation_img.resize((ceil(init_width), ceil(init_height)), Img.BICUBIC)
            self.resize(ceil(init_width), ceil(init_height))

        x, y = canvas.to_screen(p.x, p.y)

        return canvas.create_image(x, y, image=self.img)

    def _move(self, dx, dy):
        self.anchor.x += dx
        self.anchor.y += dy

    def _rotate(self, dr, sampling=Img.BICUBIC, center=None):

        self.rotation += dr
        if center is not None:
            self.img_PIL = self.img_PIL.rotate(angle=self.rotation, resample=sampling, expand=True,
                                               center=(center.x, center.y))
        else:
            self.img_PIL = self.rotation_img.rotate(angle=self.rotation, resample=sampling, expand=True)
        self.update()
        return self

    def update(self):
        try:
            self.img = ImageTk.PhotoImage(self.img_PIL, master=self.graphwin.master)
        except AttributeError:
            self.img = ImageTk.PhotoImage(self.img_PIL)

        if self.graphwin is not None:
            if self.graphwin.autoflush:
                self.graphwin.update()
            self.redraw()

    # -------------------------------------------------------------------------
    # OTHER & IMPORTANT FUNCTIONS

    def undraw(self, set_blinking=True):
        try:
            del self.image_cache[self.image_id]  # allow gc of tk photo image
        except KeyError:
            pass
        if self.is_blinking and set_blinking:
            self.animate_blinking(0, animate=False)
        GraphicsObject.undraw(self, set_blinking)
        return self

    def is_clicked(self, mouse_pos):
        width, height = abs(self.img.width() * self.graphwin.trans.x_scale), abs(
            self.img.height() * self.graphwin.trans.y_scale)
        if mouse_pos is not None:
            if (self.anchor.x - width / 2 < mouse_pos.x < self.anchor.x + width / 2) and (
                    self.anchor.y - height / 2 < mouse_pos.y < self.anchor.y + height / 2):
                return True
            else:
                return False

    def clone(self):
        other = Image(Point(0, 0), 0, 0)
        other.img = self.img.copy()
        other.anchor = self.anchor.clone()
        other.config = self.config.copy()
        return other

    def save(self, filename):
        """Saves the pixmap image to filename.
        The format for the save image is determined from the filname extension.

        """

    # -------------------------------------------------------------------------
    # IMAGE MANIPULATION FUNCTIONS

    def crop(self, left=0, top=0, right=500, down=500, align="center"):
        if align != "center":
            if "top" in align:
                self.move_y((self.get_height() - (down - top)) / -2)
            elif "bottom" in align:
                self.move_y((self.get_height() - (down - top)) / 2)

            if "left" in align:
                self.move_x((self.get_height() - (right - left)) / -2)
            elif "right" in align:
                self.move_x((self.get_height() - (right - left)) / 2)

        self.img_PIL = self.img_PIL.crop(box=(left, top, right, down))

        self.update()
        return self

    # Blending & Compositing Functions

    def blend(self, img, alpha):
        self.img_PIL = Img.blend(self.img_PIL, img.img_PIL, alpha)
        self.rotation_img = self.img_PIL
        self.update()
        return self

    def alpha_composite(self, img):
        self.img_PIL = Img.alpha_composite(self.img_PIL, img.img_PIL)
        self.rotation_img = self.img_PIL
        self.update()
        return self

    def composite(self, img, img_mask):
        self.img_PIL = Img.composite(self.img_PIL, img.img_PIL, img_mask.img_PIL)
        self.rotation_img = self.img_PIL
        self.update()
        return self

    def convert_greyscale(self):
        self.img_PIL = self.img_PIL.convert("LA")
        self.rotation_img = self.img_PIL
        self.update()
        return self

    def convert_binary(self):
        self.img_PIL = self.img_PIL.convert("1")
        self.rotation_img = self.img_PIL
        self.update()
        return self

    # ----------------------------------
    # Resizing Functions

    def resize(self, width, height, sampling=Img.BICUBIC, _external_call=True):
        self.img_PIL = self.img_PIL.resize((ceil(width), ceil(height)), sampling)

        if _external_call:
            self.initial_width = width
            self.initial_height = height
        self.update()
        return self

    def resize_height(self, height, preserve_aspect_ratio=False, sampling=Img.BICUBIC, _external_call=True):
        width = height * (self.get_width()/self.get_height()) if preserve_aspect_ratio else self.get_width()
        self.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_width(self, width, preserve_aspect_ratio=False, sampling=Img.BICUBIC, _external_call=True):
        height = width * (self.get_height()/self.get_width()) if preserve_aspect_ratio else self.get_height()
        self.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_factor(self, factor, sampling=Img.BICUBIC, _external_call=True):
        self.resize_width_factor(factor, sampling, _external_call)
        self.resize_height_factor(factor, sampling, _external_call)
        return self

    def resize_width_factor(self, factor, sampling=Img.BICUBIC, _external_call=True):
        self.resize(int(self.get_width() * factor), self.get_height(), sampling, _external_call)
        return self

    def resize_height_factor(self, factor, sampling=Img.BICUBIC, _external_call=True):
        self.resize(self.get_width(), int(self.get_height() * factor), sampling, _external_call)
        return self
    
    def resize_to_fit(self, obj, sampling=Img.BICUBIC, _external_call=True):
        self.resize(obj.get_width(), obj.get_height(), sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit_width(self, obj, preserve_aspect_ratio=False, sampling=Img.BICUBIC, _external_call=True):
        self.resize_width(obj.get_width(), preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                          _external_call=_external_call)
        return self

    def resize_to_fit_height(self, obj, preserve_aspect_ratio=False, sampling=Img.BICUBIC, _external_call=True):
        self.resize_height(obj.get_height(), preserve_aspect_ratio=preserve_aspect_ratio,
                           sampling=sampling, _external_call=_external_call)
        return self

    # ----------------------------------
    # Filter Functions

    def filter_blur(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.BLUR)
        self.update()
        return self

    def filter_blur_box(self, radius=3):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.BoxBlur(radius))
        self.update()
        return self

    def filter_blur_gaussian(self, radius=3):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.GaussianBlur(radius))
        self.update()
        return self

    def filter_blur_unsharp(self, radius=3, percent=150):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.UnsharpMask(radius=radius, percent=percent))
        self.update()
        return self

    def filter_contour(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.CONTOUR)
        self.update()
        return self

    def filter_detail(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.DETAIL)
        self.update()
        return self

    def filter_emboss(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.EMBOSS)
        self.update()
        return self

    def filter_find_edges(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.FIND_EDGES)
        self.update()
        return self

    def filter_sharpen(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.SHARPEN)
        self.update()
        return self

    def filter_smooth(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.SMOOTH)
        self.update()
        return self

    def filter_more_smooth(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.SMOOTH_MORE)
        self.update()
        return self

    def filter_enhance_edge(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.EDGE_ENHANCE)
        self.update()
        return self

    def filter_more_enhance_edge(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.EDGE_ENHANCE_MORE)
        self.update()
        return self

    # -------------------------------------------------------------------------
    # ANIMATION FUNCTIONS

    def animate_resize_factor(self, f, t, easing="Linear", args=None):
        self.resizing_factor = f
        self.resizing_easing = easing
        self.is_resizing = True

        self.resizing_time = t
        self.resizing_update = timetime()
        self.resizing_start = self.resizing_update
        self.resizing_args = args

        GraphicsObject.resizing_objects.append(self)

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
        return self.anchor.clone()

    def get_width(self):
        """Returns the width of the image in pixels"""
        return self.img.width()

    def get_height(self):
        """Returns the height of the image in pixels"""
        return self.img.height()

    def get_size(self):
        return self.get_width(), self.get_height()

    def get_aspect_ratio(self):
        divisor = gcd(self.get_width(), self.get_height())
        return self.get_width()/divisor, self.get_height()/divisor

    def get_pixel(self, x, y):
        """Returns a list [r,g,b] with the RGB colour values for pixel (x,y)
        r,g,b are in range(256)

        """
        return self.img_PIL.getpixel((x, y))

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_pixel(self, x, y, Colour):
        """Sets pixel (x,y) to the given colour

        """
        self.img_PIL = self.img_PIL.putpixel((x, y), Colour)
        self.img = ImageTk.PhotoImage(self.img_PIL)
        return self
