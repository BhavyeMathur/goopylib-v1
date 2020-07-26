from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.objects.Image import Image
from goopylib.util import GraphicsError

from os import listdir as oslistdir
from os.path import dirname as osdirname
from time import time as timetime


class AnimatedImage(GraphicsObject):
    def __init__(self, p, filepath, align="center", cursor="arrow", number_of_frames=None, update_time=1/24, layer=0,
                 tag=None, autoflush=True):
        self.reprpath = filepath
        filepath = filepath.replace('\\', '/')
        self.filepath = filepath.split('.')

        if number_of_frames is not None:
            self.number_of_frames = number_of_frames
        else:
            texture_dir = osdirname(f"{self.filepath[0]}{0}{self.filepath[1]}")
            if texture_dir == "":
                texture_dir = "."

            self.number_of_frames = 0
            for file in oslistdir(f"{texture_dir}/textures/"):
                if self.filepath[0] in file and len(file) - (len(self.filepath[0]) + len(self.filepath[1])) == 2:
                    self.number_of_frames += 1

            if self.number_of_frames == 0:
                files = oslistdir(texture_dir)
                for file in files:
                    if self.filepath[0] in file and len(file) - (len(self.filepath[0]) + len(self.filepath[1])) == 2:
                        self.number_of_frames += 1

        self.frame = 0
        self.drawn_frame = 0
        self.frame_bound_objects = {*()}

        self.imgs = [Image(p, f"{self.filepath[0]}{i}.{self.filepath[1]}", align=align, cursor=cursor)
                     for i in range(self.number_of_frames)]

        self.last_update_time = timetime()
        self.update_time = update_time
        self.autoflush = autoflush

        self.moved = False

        GraphicsObject.__init__(self, [], cursor=cursor, layer=layer, tag=tag)
        GraphicsObject.animated_image_instances.add(self)

    # -------------------------------------------------------------------------
    # INTERNAL FUNCTIONS

    def __repr__(self):
        return f"AnimatedImage({self.anchor}, {self.reprpath} and {len(self.imgs) - 1} others.)"

    def _draw(self, canvas, options):
        self.imgs[self.frame].draw(canvas)
        self.drawn_frame = self.frame
        if self.graphwin != canvas:
            for img in self.imgs:
                img.graphwin = canvas

    def _move(self, dx, dy):
        for img in self.imgs:
            img._move(dx, dy)
        self.anchor.x += dx
        self.anchor.y += dy

    def _rotate(self, dr, sampling="bicubic", center=None):
        for img in self.imgs:
            img.rotate(dr)

    def increment_frame(self, _time=None, _internal_call=False):
        self.frame += 1
        if self.frame == self.number_of_frames:
            self.frame = 0
        if self.drawn:
            if self.graphwin.autoflush:
                self.undraw()
                self.draw(self.graphwin)
            else:
                if self not in GraphicsObject.redraw_on_frame[self.layer]:
                    GraphicsObject.redraw_on_frame[self.layer].add(self)

        if _time is None:
            self.last_update_time = timetime()
        else:
            self.last_update_time = _time

        for obj in self.frame_bound_objects:
            obj.increment_frame(_time=_time, _internal_call=_internal_call)
        return self

    def decrement_frame(self, _time=None, _internal_call=False):
        self.frame -= 1
        if self.frame == -1:
            self.frame = self.number_of_frames - 1
        if self.drawn:
            if self.graphwin.autoflush:
                self.undraw()
                self.draw(self.graphwin)
            else:
                if self not in GraphicsObject.redraw_on_frame[self.layer]:
                    GraphicsObject.redraw_on_frame[self.layer].append(self)

        if _time is None:
            self.last_update_time = timetime()
        else:
            self.last_update_time = _time

        for obj in self.frame_bound_objects:
            obj.decrement_frame(_time=_time, _internal_call=_internal_call)
        return self

    def set_frame(self, frame, _time=None, _internal_call=False):

        if not (0 <= frame < self.number_of_frames):
            raise GraphicsError("\n\nGraphicsError: Frame to set the Animated Image to must be between (inclusive) 0 & "
                                f"{self.number_of_frames - 1}, not {frame}")

        self.frame = frame
        if self.drawn:
            if self.graphwin.autoflush:
                self.undraw()
                self.draw(self.graphwin)
            else:
                if self not in GraphicsObject.redraw_on_frame[self.layer]:
                    GraphicsObject.redraw_on_frame[self.layer].append(self)

        if _time is None:
            self.last_update_time = timetime()
        else:
            self.last_update_time = _time
        return self

    def bind_frame_to(self, obj):
        if not isinstance(obj, AnimatedImage):
            if obj in GraphicsObject.tagged_objects:
                obj = GraphicsObject.tagged_objects[obj]
                if not isinstance(obj, AnimatedImage):
                    raise GraphicsError("\n\nGraphicsError: object to bind frame to must be an Animated Image object, "
                                        f"not {obj}")
            else:
                raise GraphicsError("\n\nGraphicsError: object to bind frame to must be an Animated Image object, "
                                    f"not {obj}")
        obj.frame_bound_objects.add(self)
        return self

    # -------------------------------------------------------------------------
    # OTHER & IMPORTANT FUNCTIONS

    def undraw(self, set_blinking=True):
        self.drawn = False
        self.imgs[self.drawn_frame].undraw(set_blinking=set_blinking)

    def is_clicked(self, mouse_pos):
        for img in self.imgs:
            img.graphwin = self.graphwin
        return self.imgs[self.frame].is_clicked(mouse_pos)

    def save(self, filename):
        self.imgs[self.frame].save(filename)
        return self

    # -------------------------------------------------------------------------
    # IMAGE COLOUR & ENHANCE FUNCTIONS

    def set_contrast(self, level):
        for img in self.imgs:
            img.set_contrast(level)
        return self

    def change_contrast(self, level):
        for img in self.imgs:
            img.change_contrast(level)
        return self

    def reset_contrast(self):
        self.set_contrast(0)

    # -------------------------------------------------------------------------
    # IMAGE MANIPULATION FUNCTIONS

    def crop(self, left=0, top=0, right=500, down=500, align="center"):
        for img in self.imgs:
            img.crop(left=left, top=top, right=right, down=down, align=align)
        return self

    # Blending & Compositing Functions

    def blend(self, img, alpha):
        for img in self.imgs:
            img.blend(img, alpha)
        return self

    def alpha_composite(self, other):
        for img in self.imgs:
            img.alpha_composite(other)
        return self

    def composite(self, other, img_mask):
        for img in self.imgs:
            img.composite(other, img_mask)
        return self

    def convert_greyscale(self):
        for img in self.imgs:
            img.convert_greyscale()
        return self

    def convert_binary(self):
        for img in self.imgs:
            img.convert_binary()
        return self

    # ----------------------------------
    # Flipping Functions

    def flip(self, x_axis=True, y_axis=True):
        for img in self.imgs:
            img.flip(x_axis=x_axis, y_axis=y_axis)
        return self

    def flip_x(self):
        for img in self.imgs:
            img.flip_x()
        return self

    def flip_y(self):
        for img in self.imgs:
            img.flip_y()
        return self

    def flip_xy(self):
        for img in self.imgs:
            img.flip_xy()
        return self

    def transverse(self):
        for img in self.imgs:
            img.transverse()
        return self

    def transpose(self):
        for img in self.imgs:
            img.transpose()
        return self

    # ----------------------------------
    # Skew Transformation Functions

    def skew_x(self, scale=0.3, sampling="bicubic", align="center"):
        for img in self.imgs:
            img.skew_x(scale=scale, sampling=sampling, align=align)
        return self

    def skew_y(self, scale=0.3, sampling="bicubic", align="center"):
        for img in self.imgs:
            img.skew_y(scale=scale, sampling=sampling, align=align)
        return self

    def skew_xy(self, x_scale=0.3, y_scale=None, sampling="bicubic", x_align="center", y_align=None):
        for img in self.imgs:
            img.skew_xy(x_scale=x_scale, y_scale=y_scale, sampling=sampling, x_align=x_align, y_align=y_align)
        return self

    # ----------------------------------
    # Resizing Functions

    def resize(self, width, height, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_height(self, height, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_height(height, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                              _external_call=_external_call)
        return self

    def resize_width(self, width, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_width(width, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                             _external_call=_external_call)
        return self

    def resize_factor(self, factor, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_factor(factor, sampling=sampling, _external_call=_external_call)

    def resize_width_factor(self, factor, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_width_factor(factor, sampling=sampling, _external_call=_external_call)
        return self

    def resize_height_factor(self, factor, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_width_factor(factor, sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit(self, obj, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_to_fit(obj, sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit_width(self, obj, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_to_fit_width(obj, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                    _external_call=_external_call)
        return self

    def resize_to_fit_height(self, obj, preserve_aspect_ratio=False, sampling="bicubic", _external_call=True):
        for img in self.imgs:
            img.resize_to_fit_height(obj, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                    _external_call=_external_call)
        return self

    # ----------------------------------
    # Blurring & Sharpening Functions

    def blur(self):
        for img in self.imgs:
            img.blur()
        return self

    def blur_box(self, radius=3):
        for img in self.imgs:
            img.blur_box(radius=radius)
        return self

    def blur_gaussian(self, radius=3):
        for img in self.imgs:
            img.blur_gaussian(radius=radius)
        return self

    def sharpen(self, radius=3, percent=150):
        for img in self.imgs:
            img.sharpen(radius=radius, percent=percent)
        return self

    # ----------------------------------
    # Filter Functions

    def filter_contour(self):
        for img in self.imgs:
            img.filter_contour()
        return self

    def filter_detail(self):
        for img in self.imgs:
            img.filter_detail()
        return self

    def filter_emboss(self):
        for img in self.imgs:
            img.filter_emboss()
        return self

    def filter_find_edges(self):
        for img in self.imgs:
            img.filter_find_edges()
        return self

    def filter_sharpen(self):
        for img in self.imgs:
            img.filter_sharpen()
        return self

    def filter_smooth(self):
        for img in self.imgs:
            img.filter_smooth()
        return self

    def filter_more_smooth(self):
        for img in self.imgs:
            img.filter_more_smooth()
        return self

    def filter_enhance_edge(self):
        for img in self.imgs:
            img.filter_enhance_edge()
        return self

    def filter_more_enhance_edge(self):
        for img in self.imgs:
            img.filter_more_enhance_edge()
        return self

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
        return self.imgs[0].get_anchor()

    def get_width(self):
        return self.imgs[0].get_width()

    def get_height(self):
        return self.imgs[0].get_height()

    def get_aspect_ratio(self):
        return self.imgs[0].get_aspect_ratio()

    def get_pixel(self, x, y):
        return self.imgs[0].get_pixel(x, y)

    def get_format(self):
        return self.imgs[0].get_format()

    def get_mode(self):
        return self.imgs[0].get_mode()

    def get_contrast(self):
        return self.imgs[0].get_contrast()

    def get_frame(self):
        return self.frame

    def get_number_of_frames(self):
        return len(self.imgs)

    def get_current_frame(self):
        return self.imgs[self.frame]

    def get_all_frames(self):
        return self.imgs

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_pixel(self, x, y, colour):
        for img in self.imgs:
            img.set_pixel(x, y, colour)
        return self
