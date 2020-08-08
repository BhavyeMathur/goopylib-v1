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

    default_sampling = "bicubic"
    texture_path = "textures/"

    def __init__(self, p, filepath, align="center", cursor="arrow", layer=0, tag=None, bounds=None):

        if not isinstance(p, Point):
            raise GraphicsError(f"\n\nGraphicsError: Image anchor point (p) must be a Point object, not {p}")
        if align not in ALIGN_OPTIONS:
            raise GraphicsError(f"\n\nGraphicsError: Image align must be one of {ALIGN_OPTIONS}, not {align}")

        if osisfile(Image.texture_path + filepath):
            self.texture = Image.texture_path + filepath
        elif osisfile(filepath):
            self.texture = filepath
        else:
            raise GraphicsError("\n\nGraphicsError: Image filepath is not valid. No such file or directory as "
                                f"{filepath}")

        self.texture = resource_path(self.texture)
        self.reprpath = f"\"{filepath}\""

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
        self.resized = False

        self.contrast = 0
        self.blur_amount = 0

        self.update_required = False

        GraphicsObject.__init__(self, [], cursor=cursor, layer=layer, tag=tag, bounds=bounds)

        self.image_id = Image.id_count
        Image.id_count = Image.id_count + 1

    # -------------------------------------------------------------------------
    # INTERNAL FUNCTIONS

    def __repr__(self):
        return f"Image({self.anchor}, {self.reprpath})"

    def _draw(self, canvas, options):
        x, y = self.anchor

        if self.align == "center":
            pass
        elif self.align == "bottom":
            y += self.initial_height / -2
        elif self.align == "top":
            y += self.initial_height / 2
        elif self.align == "left":
            x += self.initial_width / 2
        elif self.align == "right":
            x += self.initial_width / -2
        elif self.align == "bottomleft":
            y += self.initial_height / -2
            x += self.initial_width / 2
        elif self.align == "bottomright":
            y += self.initial_height / 2
            x += self.initial_width / -2
        elif self.align == "topleft":
            x += self.initial_width / 2
            y += self.initial_height / 2
        elif self.align == "topright":
            x += self.initial_width / -2
            y += self.initial_height / 2

        if canvas.trans.x_scale != 1 and canvas.trans.y_scale != 1:
            if not self.resized:
                init_width = abs(self.initial_width / canvas.trans.x_scale)
                init_height = abs(self.initial_height / canvas.trans.y_scale)
                self.resize(ceil(init_width), ceil(init_height), sampling=Image.default_sampling, _external_call=False)
                self.resized = True
            x, y = canvas.to_screen(x, y)

        if self.update_required:
            self.update()
            self.update_required = False

        return canvas.create_image(x, y, image=self.img)

    def _move(self, dx, dy):
        self.anchor.x += dx
        self.anchor.y += dy

    def _rotate(self, dr, sampling=None, center=None):
        if sampling is None:
            sampling = Image.default_sampling
        if center is not None:
            self.transforming_img = self.original_img.rotate(angle=-self.rotation, expand=True,
                                                             resample=IMAGE_INTERPOLATIONS[sampling],
                                                             center=(center.x, center.y))
        else:
            self.transforming_img = self.original_img.rotate(angle=-self.rotation, expand=True,
                                                             resample=IMAGE_INTERPOLATIONS[sampling])
        self.img_PIL = self.transforming_img.copy()
        self.update_required = True
        return self

    def update(self):
        try:
            self.graphwin.delete(self.id)
            self.img = ImageTk.PhotoImage(self.img_PIL, master=self.graphwin.master)
        except AttributeError:
            self.img = ImageTk.PhotoImage(self.img_PIL)

        self._update_layer()

    # -------------------------------------------------------------------------
    # OTHER & IMPORTANT FUNCTIONS

    def is_clicked(self, mouse_pos):
        if mouse_pos is None:
            return False
        else:
            if self.bounds is None:
                if not isinstance(mouse_pos, Point):
                    raise GraphicsError(f"\n\nMouse Pos argument for is_clicked() must be a Point object, not {mouse_pos}")

                if self.drawn:
                    width, height = abs(self.img.width() * self.graphwin.trans.x_scale), \
                                    abs(self.img.height() * self.graphwin.trans.y_scale)
                else:
                    width, height = self.img.width(), self.img.height()

                if (self.anchor.x - width / 2 < mouse_pos.x < self.anchor.x + width / 2) and (
                        self.anchor.y - height / 2 < mouse_pos.y < self.anchor.y + height / 2):
                    return True
                else:
                    return False
            else:
                return self.bounds.is_clicked(mouse_pos)

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
        self.update_required = True

        self._update_layer()
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
        self.transforming_img = self.transforming_img.crop(box=(left, top, right, down))

        self.update_required = True

        self._update_layer()
        return self

    # Blending & Compositing Functions

    def blend(self, img, alpha):
        if not isinstance(img, Image):
            raise GraphicsError("\n\nGraphicsError: img argument for blending must be another goopylib_b Image Object, "
                                f"not {img}")
        if not (isinstance(alpha, int) or isinstance(alpha, float)):
            raise GraphicsError(f"\n\nGraphicsError: Blend alpha value must be an integer or float, not {alpha}")
        if not (0 <= alpha <= 1):
            raise GraphicsError(f"\n\nGraphicsError: Blend alpha value must be between 0 and 1, not {alpha}")

        self.img_PIL = Img.blend(self.img_PIL, img.img_PIL, alpha)
        self.transforming_img = self.img_PIL
        self.update_required = True

        self._update_layer()
        return self

    def alpha_composite(self, img):
        if not isinstance(img, Image):
            raise GraphicsError("\n\nGraphicsError: img argument for composite must be another goopylib_b Image Object, "
                                f"not {img}")

        self.img_PIL = Img.alpha_composite(self.img_PIL, img.img_PIL)
        self.transforming_img = self.img_PIL
        self.update_required = True

        self._update_layer()
        return self

    def composite(self, img, img_mask):
        if not isinstance(img, Image):
            raise GraphicsError("\n\nGraphicsError: img argument for composite must be another goopylib_b Image Object, "
                                f"not {img}")
        if not isinstance(img_mask, Image):
            raise GraphicsError("\n\nGraphicsError: img mask argument for composite must be another goopylib_b Image "
                                f"Object, not {img_mask}")

        self.img_PIL = Img.composite(self.img_PIL, img.img_PIL, img_mask.img_PIL)
        self.transforming_img = self.img_PIL
        self.update_required = True

        self._update_layer()
        return self

    def convert_greyscale(self):
        self.img_PIL = self.img_PIL.convert("LA")
        self.transforming_img = self.img_PIL
        self.update_required = True

        self._update_layer()
        return self

    def convert_binary(self):
        self.img_PIL = self.img_PIL.convert("1")
        self.transforming_img = self.img_PIL
        self.update_required = True

        self._update_layer()
        return self

    # ----------------------------------
    # Flipping Functions

    def flip(self, x_axis=True, y_axis=True):
        if x_axis:
            self.flip_x()
        if y_axis:
            self.flip_y()

        self._update_layer()
        return self

    def flip_x(self):
        self.img_PIL = self.img_PIL.transpose(Img.FLIP_LEFT_RIGHT)
        self.update_required = True

        self._update_layer()
        return self

    def flip_y(self):
        self.img_PIL = self.img_PIL.transpose(Img.FLIP_TOP_BOTTOM)
        self.update_required = True

        self._update_layer()
        return self

    def flip_xy(self):
        self.flip_x()
        self.flip_y()
        return self

    def transverse(self):
        self.img_PIL = self.img_PIL.transpose(Img.TRANSVERSE)
        self.update_required = True

        self._update_layer()
        return self

    def transpose(self):
        self.img_PIL = self.img_PIL.transpose(Img.TRANSPOSE)
        self.update_required = True

        self._update_layer()
        return self

    # ----------------------------------
    # Skew Transformation Functions

    def skew_x(self, scale=0.3, sampling=None, align="center"):
        if sampling is None:
            sampling = Image.default_sampling
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
            self.update_required = True

        self._update_layer()
        return self

    def skew_y(self, scale=0.3, sampling=None, align="center"):
        if sampling is None:
            sampling = Image.default_sampling
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

            self.update_required = True

        self._update_layer()
        return self

    def skew_xy(self, x_scale=0.3, y_scale=None, sampling=None, x_align="center", y_align=None):
        if y_align is None:
            y_align = x_align
        if y_scale is None:
            y_scale = x_scale

        if sampling is None:
            sampling = Image.default_sampling

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

        self.update_required = True

        self._update_layer()
        return self

    # ----------------------------------
    # Resizing Functions

    def resize(self, width, height, sampling=None, _external_call=True):
        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nGraphicsError: Resize Width must be an integer or float, not {width}")
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError(f"\n\nThe window's height must be an integer or float, not {height}")

        if sampling is None:
            sampling = Image.default_sampling

        if sampling not in IMAGE_INTERPOLATIONS.keys():
            raise GraphicsError("\n\nGraphicsError: The resizing sampling argument must be one of "
                                f"{IMAGE_INTERPOLATIONS}, not {sampling}")

        self.img_PIL = self.img_PIL.resize((ceil(width), ceil(height)), IMAGE_INTERPOLATIONS[sampling])
        self.original_img = self.original_img.resize((ceil(width), ceil(height)), IMAGE_INTERPOLATIONS[sampling])

        if _external_call:
            self.initial_width = width
            self.initial_height = height
        self.update_required = True

        self._update_layer()

        return self

    def resize_height(self, height, preserve_aspect_ratio=False, sampling=None, _external_call=True):

        if not isinstance(preserve_aspect_ratio, bool):
            raise GraphicsError("\n\nGraphicsError: Resizing Preserve Aspect Ratio argument must be a boolean, not "
                                f"{preserve_aspect_ratio}")

        width = height * (self.get_width() / self.get_height()) if preserve_aspect_ratio else self.get_width()
        self.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_width(self, width, preserve_aspect_ratio=False, sampling=None, _external_call=True):

        if not isinstance(preserve_aspect_ratio, bool):
            raise GraphicsError("\n\nGraphicsError: Resizing Preserve Aspect Ratio argument must be a boolean, not "
                                f"{preserve_aspect_ratio}")

        height = width * (self.get_height() / self.get_width()) if preserve_aspect_ratio else self.get_height()
        self.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_factor(self, factor, sampling=None, _external_call=True):
        self.resize_width_factor(factor, sampling, _external_call)
        self.resize_height_factor(factor, sampling, _external_call)
        return self

    def resize_width_factor(self, factor, sampling=None, _external_call=True):
        self.resize(int(self.get_width() * factor), self.get_height(), sampling, _external_call)
        return self

    def resize_height_factor(self, factor, sampling=None, _external_call=True):
        self.resize(self.get_width(), int(self.get_height() * factor), sampling, _external_call)
        return self

    def resize_to_fit(self, obj, sampling=None, _external_call=True):
        self.resize(obj.get_width(), obj.get_height(), sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit_width(self, obj, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        self.resize_width(obj.get_width(), preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                          _external_call=_external_call)
        return self

    def resize_to_fit_height(self, obj, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        self.resize_height(obj.get_height(), preserve_aspect_ratio=preserve_aspect_ratio,
                           sampling=sampling, _external_call=_external_call)
        return self

    # ----------------------------------
    # Blurring & Sharpening Functions

    def blur(self):
        self.img_PIL = self.original_img.filter(filter=ImageFilter.BLUR)
        self.update_required = True

        self._update_layer()
        return self

    def blur_box(self, radius=3):

        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Radius for Blur must be an integer or float, not {radius}")

        self.img_PIL = self.original_img.filter(filter=ImageFilter.BoxBlur(radius))
        self.update_required = True

        self._update_layer()
        return self

    def blur_gaussian(self, radius=3):

        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Radius for Blur must be an integer or float, not {radius}")

        self.img_PIL = self.original_img.filter(filter=ImageFilter.GaussianBlur(radius))
        self.blur_amount = radius
        self.update_required = True

        self._update_layer()
        return self

    def sharpen(self, radius=3, percent=150):

        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Radius for Blur must be an integer or float, not {radius}")
        if not isinstance(percent, int):
            raise GraphicsError(f"\n\nGraphicsError: Percent Blur must be an integer or float, not {percent}")

        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.UnsharpMask(radius=radius, percent=percent))
        self.update_required = True

        self._update_layer()
        return self

    # ----------------------------------
    # Filter Functions

    def filter_contour(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.CONTOUR)
        self.update_required = True

        self._update_layer()
        return self

    def filter_detail(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.DETAIL)
        self.update_required = True

        self._update_layer()
        return self

    def filter_emboss(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.EMBOSS)
        self.update_required = True

        self._update_layer()
        return self

    def filter_find_edges(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.FIND_EDGES)
        self.update_required = True

        self._update_layer()
        return self

    def filter_sharpen(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.SHARPEN)
        self.update_required = True

        self._update_layer()
        return self

    def filter_smooth(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.SMOOTH)
        self.update_required = True

        self._update_layer()
        return self

    def filter_more_smooth(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.SMOOTH_MORE)
        self.update_required = True

        self._update_layer()
        return self

    def filter_enhance_edge(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.EDGE_ENHANCE)
        self.update_required = True

        self._update_layer()
        return self

    def filter_more_enhance_edge(self):
        self.img_PIL = self.img_PIL.filter(filter=ImageFilter.EDGE_ENHANCE_MORE)
        self.update_required = True

        self._update_layer()
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

    def set_pixel(self, x, y, colour):
        """Sets pixel (x,y) to the given colour

        """
        self.original_img = self.original_img.putpixel((x, y), colour)
        self.img_PIL = self.img_PIL.putpixel((x, y), colour)
        self.update_required = True

        self._update_layer()
        return self

    @staticmethod
    def set_default_sampling(sampling):
        if sampling not in IMAGE_INTERPOLATIONS:
            raise GraphicsError(f"\n\nGraphicsError: sampling to set as default must be one of {IMAGE_INTERPOLATIONS}, "
                                f"not {sampling}")
        Image.default_sampling = sampling
    
    @staticmethod
    def set_texture_path(path):
        Image.texture_path = path
