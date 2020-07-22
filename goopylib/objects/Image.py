from PIL import ImageTk
from PIL import ImageFilter
from PIL import Image as Img

from math import gcd, ceil
from os.path import isfile as osisfile

from goopylib.util import GraphicsError, resource_path

from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point
from goopylib.constants import ALIGN_OPTIONS, IMAGE_INTERPOLATIONS


class Image(GraphicsObject):
    id_count = 0
    image_cache = {}  # tk photo images go here to avoid GC while drawn

    def __init__(self, p, filepath, align="center", cursor="arrow", layer=0):

        if not isinstance(p, Point):
            raise GraphicsError(f"\n\nGraphicsError: Image anchor point (p) must be a Point object, not {p}")
        if align not in ALIGN_OPTIONS:
            raise GraphicsError(f"\n\nGraphicsError: Image align must be one of {ALIGN_OPTIONS}, not {align}")

        if osisfile(f"textures/{filepath}"):
            self.texture = f"textures/{filepath}"
        elif osisfile(filepath):
            self.texture = filepath
        else:
            raise GraphicsError("\n\nGraphicsError: Image filepath is not valid. No such file or directory as "
                                f"{filepath}")

        self.texture = resource_path(self.texture)
        self.reprpath = filepath

        self.img_PIL = Img.open(self.texture, )
        self.img = ImageTk.PhotoImage(self.img_PIL)
        self.original_img = self.img_PIL.copy()
        self.transforming_img = self.img_PIL.copy()

        self.align = align
        self.anchor = p.clone()

        self.x = self.anchor.x
        self.y = self.anchor.y
        self.initial_width = self.get_width()
        self.initial_height = self.get_height()

        self.contrast = 0
        self.blur_amount = 0

        GraphicsObject.__init__(self, [], cursor=cursor, layer=layer)

        self.image_id = Image.id_count
        Image.id_count = Image.id_count + 1

    # -------------------------------------------------------------------------
    # INTERNAL FUNCTIONS

    def __repr__(self):
        return f"Image({self.anchor}, {self.reprpath})"

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
            self.resize(ceil(init_width), ceil(init_height))

        x, y = canvas.to_screen(p.x, p.y)

        return canvas.create_image(x, y, image=self.img)

    def _move(self, dx, dy):
        self.anchor.x += dx
        self.anchor.y += dy

    def _rotate(self, dr, sampling=Img.BICUBIC, center=None):
        if center is not None:
            self.transforming_img = self.original_img.rotate(angle=self.rotation, resample=sampling, expand=True,
                                                             center=(center.x, center.y))
        else:
            self.transforming_img = self.original_img.rotate(angle=self.rotation, resample=sampling, expand=True)
        self.img_PIL = self.transforming_img.copy()
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

        if not isinstance(set_blinking, bool):
            raise GraphicsError("\n\nGraphicsError: set_blinking paramter of undraw must be a boolean, not "
                                f"{set_blinking}")

        try:
            del self.image_cache[self.image_id]  # allow gc of tk photo image
        except KeyError:
            pass
        if self.is_blinking and set_blinking:
            self.animate_blinking(0, animate=False)
        GraphicsObject.undraw(self, set_blinking)
        return self

    def is_clicked(self, mouse_pos):
        if mouse_pos is not None:
            if not isinstance(mouse_pos, Point):
                raise GraphicsError(f"\n\nMouse Pos argument for is_clicked() must be a Point object, not {mouse_pos}")

            width, height = abs(self.img.width() * self.graphwin.trans.x_scale), abs(
                self.img.height() * self.graphwin.trans.y_scale)
            if (self.anchor.x - width / 2 < mouse_pos.x < self.anchor.x + width / 2) and (
                    self.anchor.y - height / 2 < mouse_pos.y < self.anchor.y + height / 2):
                return True
            else:
                return False

    def clone(self):
        other = Image(self.anchor.copy(), self.texture)
        other.config = self.config.copy()
        return other

    def save(self, filename):
        """Saves the pixmap image to filename.
        The format for the save image is determined from the filname extension.
        """

    # -------------------------------------------------------------------------
    # IMAGE COLOUR & ENHANCE FUNCTIONS

    def set_contrast(self, level):
        self.change_contrast(level - self.contrast)
        return self

    def change_contrast(self, level):
        if not (isinstance(level, int) or isinstance(level, float)):
            raise GraphicsError(f"\n\nGraphicsError: contrast level must be an integer or float, not {level}")

        self.contrast += level

        # Code from https://stackoverflow.com/questions/42045362/change-contrast-of-image-in-pil
        factor = (259 * (level + 255)) / (255 * (259 - level))

        def contrast(c):
            return 128 + factor * (c - 128)

        self.original_img = self.original_img.point(contrast)
        self.img_PIL = self.img_PIL.point(contrast)
        self.update()
        return self

    def reset_contrast(self):
        self.set_contrast(0)

    # -------------------------------------------------------------------------
    # IMAGE MANIPULATION FUNCTIONS

    def crop(self, left=0, top=0, right=500, down=500, align="center"):

        if not (isinstance(left, float) or isinstance(left, int)):
            raise GraphicsError(f"\n\nGraphicsError: The crop left argument must be an integer or float, not {left}")
        if not (isinstance(right, float) or isinstance(right, int)):
            raise GraphicsError(f"\n\nGraphicsError: The crop right argument must be an integer or float, not {right}")
        if not (isinstance(top, float) or isinstance(top, int)):
            raise GraphicsError(f"\n\nGraphicsError: The crop top argument must be an integer or float, not {top}")
        if not (isinstance(down, float) or isinstance(down, int)):
            raise GraphicsError(f"\n\nGraphicsError: The crop down argument must be an integer or float, not {down}")

        if align != "center":
            valid = False
            if "top" in align:
                self.move_y((self.get_height() - (down - top)) / -2)
                valid = True
            elif "bottom" in align:
                self.move_y((self.get_height() - (down - top)) / 2)
                valid = True

            if "left" in align:
                self.move_x((self.get_width() - (right - left)) / -2)
                valid = True
            elif "right" in align:
                self.move_x((self.get_width() - (right - left)) / 2)
                valid = True

            if not valid:
                raise GraphicsError(f"\n\nGraphicsError: Crop align must be one of {ALIGN_OPTIONS}, not {align}")

        self.img_PIL = self.img_PIL.crop(box=(left, top, right, down))

        self.update()
        return self

    # Blending & Compositing Functions

    def blend(self, img, alpha):
        if not isinstance(img, Image):
            raise GraphicsError("\n\nGraphicsError: img argument for blending must be another goopylib Image Object, "
                                f"not {img}")
        if not (isinstance(alpha, int) or isinstance(alpha, float)):
            raise GraphicsError(f"\n\nGraphicsError: Blend alpha value must be an integer or float, not {alpha}")
        if not (0 <= alpha <= 1):
            raise GraphicsError(f"\n\nGraphicsError: Blend alpha value must be between 0 and 1, not {alpha}")

        self.img_PIL = Img.blend(self.img_PIL, img.img_PIL, alpha)
        self.transforming_img = self.img_PIL
        self.update()
        return self

    def alpha_composite(self, img):
        if not isinstance(img, Image):
            raise GraphicsError("\n\nGraphicsError: img argument for composite must be another goopylib Image Object, "
                                f"not {img}")

        self.img_PIL = Img.alpha_composite(self.img_PIL, img.img_PIL)
        self.transforming_img = self.img_PIL
        self.update()
        return self

    def composite(self, img, img_mask):
        if not isinstance(img, Image):
            raise GraphicsError("\n\nGraphicsError: img argument for composite must be another goopylib Image Object, "
                                f"not {img}")
        if not isinstance(img_mask, Image):
            raise GraphicsError("\n\nGraphicsError: img mask argument for composite must be another goopylib Image "
                                f"Object, not {img_mask}")

        self.img_PIL = Img.composite(self.img_PIL, img.img_PIL, img_mask.img_PIL)
        self.transforming_img = self.img_PIL
        self.update()
        return self

    def convert_greyscale(self):
        self.img_PIL = self.img_PIL.convert("LA")
        self.transforming_img = self.img_PIL
        self.update()
        return self

    def convert_binary(self):
        self.img_PIL = self.img_PIL.convert("1")
        self.transforming_img = self.img_PIL
        self.update()
        return self

    # ----------------------------------
    # Flipping Functions

    def flip(self, x_axis=True, y_axis=True):
        if x_axis:
            self.flip_x()
        if y_axis:
            self.flip_y()
        return self

    def flip_x(self):
        self.img_PIL = self.img_PIL.transpose(Img.FLIP_LEFT_RIGHT)
        return self

    def flip_y(self):
        self.img_PIL = self.img_PIL.transpose(Img.FLIP_TOP_BOTTOM)
        return self

    def flip_xy(self):
        self.flip_x()
        self.flip_y()
        return self

    def transverse(self):
        self.img_PIL = self.img_PIL.transpose(Img.TRANSVERSE)
        self.update()
        return self

    def transpose(self):
        self.img_PIL = self.img_PIL.transpose(Img.TRANSPOSE)
        self.update()
        return self

    # ----------------------------------
    # Skew Transformation Functions

    def skew_x(self, scale=0.3, sampling="bicubic", align="center"):
        if self.x_skew != scale:
            if sampling not in IMAGE_INTERPOLATIONS.keys():
                raise GraphicsError("\n\nGraphicsError: The resizing sampling argument must be one of "
                                    f"{IMAGE_INTERPOLATIONS}, not {sampling}")
            if not (isinstance(scale, int) or isinstance(scale, float)):
                raise GraphicsError(f"\n\nThe skew scale must be an integer or float, not {scale}")

            if align != "center":
                valid = False
                if align == "left" or align == "right":
                    self.move_to_x(self.anchor.x, align=align)
                else:
                    raise GraphicsError(f"\n\nGraphicsError: Skew align must be one of ['center', 'left', 'right'], "
                                        f"not {align}")

            self.x_skew = scale

            # Code (modified) from https://stackoverflow.com/questions/14177744/how-does-perspective-transformation-work-in-pil
            width, height = self.transforming_img.width, self.transforming_img.height
            new_width = round((1 + abs(scale)) * width)
            size_factor = width / height
            self.img_PIL = self.transforming_img.transform((new_width, height), Img.AFFINE, (1, scale * size_factor,
                                                  (abs(scale) * -width) if scale > 0 else 0, 0, 1, 0),
                                                  IMAGE_INTERPOLATIONS[sampling])
            self.update()
        return self

    def skew_y(self, scale=0.3, sampling="bicubic", align="center"):
        if self.y_skew != scale:
            if sampling not in IMAGE_INTERPOLATIONS.keys():
                raise GraphicsError("\n\nGraphicsError: The resizing sampling argument must be one of "
                                    f"{IMAGE_INTERPOLATIONS}, not {sampling}")
            if not (isinstance(scale, int) or isinstance(scale, float)):
                raise GraphicsError(f"\n\nThe skew scale must be an integer or float, not {scale}")

            if align != "center":
                valid = False
                if align == "top" or align == "bottom":
                    self.move_to_y(self.anchor.y, align=align)
                else:
                    raise GraphicsError(f"\n\)nGraphicsError: Skew align must be one of ['center', 'top', 'bottom'], "
                                        f"not {align}")

            self.y_skew = scale

            width, height = self.transforming_img.width, self.transforming_img.height
            new_height = round(height * (abs(scale) + 1))
            size_factor = height / width
            self.img_PIL = self.transforming_img.transform((width, new_height), Img.AFFINE,
                                                  (1, 0, 0, scale * size_factor, 1,
                                                  (abs(scale) * -height) if scale > 0 else 0),
                                                  IMAGE_INTERPOLATIONS[sampling])

            self.update()
        return self

    def skew_xy(self, x_scale=0.3, y_scale=None, sampling="bicubic", x_align="center", y_align=None):
        if y_align is None:
            y_align = x_align
        if y_scale is None:
            y_scale = x_scale

        if sampling not in IMAGE_INTERPOLATIONS.keys():
            raise GraphicsError("\n\nGraphicsError: The resizing sampling argument must be one of "
                                f"{IMAGE_INTERPOLATIONS}, not {sampling}")
        if not (isinstance(x_scale, int) or isinstance(x_scale, float)):
            raise GraphicsError(f"\n\nThe skew x_scale must be an integer or float, not {x_scale}")
        if not (isinstance(y_scale, int) or isinstance(y_scale, float)):
            raise GraphicsError(f"\n\nThe skew y_scale must be an integer or float, not {y_scale}")

        if y_align != "center":
            valid = False
            if y_align == "top" or y_align == "bottom":
                self.move_to_y(self.anchor.y, align=y_align)
            else:
                raise GraphicsError(f"\n\nGraphicsError: Skew Y Align must be one of ['center', 'top', 'bottom'], "
                                    f"not {y_align}")
        if x_align != "center":
            valid = False
            if x_align == "left" or x_align == "right":
                self.move_to_x(self.anchor.x, align=x_align)
            else:
                raise GraphicsError(f"\n\nGraphicsError: Skew X Align must be one of ['center', 'left', 'right'], "
                                    f"not {x_align}")

        self.x_skew = x_scale
        self.y_skew = y_scale

        width, height = self.transforming_img.width, self.transforming_img.height
        new_height = round(height * (y_scale + 1))
        new_width = round(width * (x_scale + 1))

        size_factor_h = height / new_width
        size_factor_w = width / new_height
        self.img_PIL = self.transforming_img.transform((new_width, new_height), Img.AFFINE, (
            1, x_scale * size_factor_w, (abs(x_scale) * -width) if x_scale > 0 else 0,
            y_scale * size_factor_h, 1, (abs(y_scale) * -height) if y_scale > 0 else 0),
                                                       IMAGE_INTERPOLATIONS[sampling])

        self.update()
        return self

    # ----------------------------------
    # Resizing Functions

    def resize(self, width, height, sampling="bicubic", _external_call=True):
        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nGraphicsError: Resize Width must be an integer or float, not {width}")
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError(f"\n\nThe window's height must be an integer or float, not {height}")

        if sampling not in IMAGE_INTERPOLATIONS.keys():
            raise GraphicsError("\n\nGraphicsError: The resizing sampling argument must be one of "
                                f"{IMAGE_INTERPOLATIONS}, not {sampling}")

        self.img_PIL = self.img_PIL.resize((ceil(width), ceil(height)), IMAGE_INTERPOLATIONS[sampling])

        if _external_call:
            self.initial_width = width
            self.initial_height = height
        self.update()
        return self

    def resize_height(self, height, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):

        if not isinstance(preserve_aspect_ratio, bool):
            raise GraphicsError("\n\nGraphicsError: Resizing Preserve Aspect Ratio argument must be a boolean, not "
                                f"{preserve_aspect_ratio}")

        width = height * (self.get_width() / self.get_height()) if preserve_aspect_ratio else self.get_width()
        self.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_width(self, width, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):

        if not isinstance(preserve_aspect_ratio, bool):
            raise GraphicsError("\n\nGraphicsError: Resizing Preserve Aspect Ratio argument must be a boolean, not "
                                f"{preserve_aspect_ratio}")

        height = width * (self.get_height() / self.get_width()) if preserve_aspect_ratio else self.get_height()
        self.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_factor(self, factor, sampling="bicubic", _external_call=True):
        self.resize_width_factor(factor, sampling, _external_call)
        self.resize_height_factor(factor, sampling, _external_call)
        return self

    def resize_width_factor(self, factor, sampling="bicubic", _external_call=True):
        self.resize(int(self.get_width() * factor), self.get_height(), sampling, _external_call)
        return self

    def resize_height_factor(self, factor, sampling="bicubic", _external_call=True):
        self.resize(self.get_width(), int(self.get_height() * factor), sampling, _external_call)
        return self

    def resize_to_fit(self, obj, sampling="bicubic", _external_call=True):
        self.resize(obj.get_width(), obj.get_height(), sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit_width(self, obj, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):
        self.resize_width(obj.get_width(), preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                          _external_call=_external_call)
        return self

    def resize_to_fit_height(self, obj, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):
        self.resize_height(obj.get_height(), preserve_aspect_ratio=preserve_aspect_ratio,
                           sampling=sampling, _external_call=_external_call)
        return self

    # ----------------------------------
    # Blurring & Sharpening Functions

    def blur(self):
        self.img_PIL = self.original_img.filter(filter=ImageFilter.BLUR)
        self.update()
        return self

    def blur_box(self, radius=3):

        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Radius for Blur must be an integer or float, not {radius}")

        self.img_PIL = self.original_img.filter(filter=ImageFilter.BoxBlur(radius))
        self.update()
        return self

    def blur_gaussian(self, radius=3):

        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Radius for Blur must be an integer or float, not {radius}")

        self.img_PIL = self.original_img.filter(filter=ImageFilter.GaussianBlur(radius))
        self.blur_amount = radius
        self.update()
        return self

    def sharpen(self, radius=3, percent=150):

        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Radius for Blur must be an integer or float, not {radius}")
        if not isinstance(percent, int):
            raise GraphicsError(f"\n\nGraphicsError: Percent Blur must be an integer or float, not {percent}")

        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.UnsharpMask(radius=radius, percent=percent))
        self.update()
        return self

    # ----------------------------------
    # Filter Functions

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
    # GETTER FUNCTIONS

    def get_anchor(self):
        return self.anchor.clone()

    def get_width(self):
        """Returns the width of the image in pixels"""
        return self.img_PIL.width

    def get_height(self):
        """Returns the height of the image in pixels"""
        return self.img_PIL.height

    def get_aspect_ratio(self):
        divisor = gcd(self.get_width(), self.get_height())
        return self.get_width() / divisor, self.get_height() / divisor

    def get_pixel(self, x, y):
        """Returns a list [r,g,b] with the RGB colour values for pixel (x,y)
        r,g,b are in range(256)

        """
        return self.img_PIL.getpixel((x, y))

    def get_format(self):
        return self.img_PIL.format

    def get_mode(self):
        return self.img_PIL.mode

    def get_contrast(self):
        return self.contrast

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_pixel(self, x, y, Colour):
        """Sets pixel (x,y) to the given colour

        """
        self.img_PIL = self.img_PIL.putpixel((x, y), Colour)
        self.img = ImageTk.PhotoImage(self.img_PIL)
        return self
