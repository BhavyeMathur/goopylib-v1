from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.objects.Image import Image
from goopylib.util import GraphicsError

from os import listdir as oslistdir
from os.path import dirname as osdirname
from os.path import isdir as osisdir
from time import time as timetime


class AnimatedImage(GraphicsObject):
    def __init__(self, p, frames, align="center", cursor="arrow", update_time=1/30, layer=0,
                 tag=None, autoflush=True, frame_callback=None, bounds=None):

        if not (callable(frame_callback) or frame_callback is None):
            raise GraphicsError("\n\nGraphicsError: Frame Increment callback for Animated Image must be a function, "
                                f"not {frame_callback}")

        self.frame = 0
        self.number_of_frames = len(frames)
        self.drawn_frame = 0
        self.frame_bound_objects = {*()}

        self.imgs = [Image(p, path, align=align, cursor=cursor, bounds=bounds) for path in frames]

        self.last_update_time = timetime()
        self.update_time = update_time
        self.autoflush = autoflush

        self.moved = False

        GraphicsObject.__init__(self, [], cursor=cursor, layer=layer, tag=tag)

        self.callbacks["frame increment"] = frame_callback

    # -------------------------------------------------------------------------
    # INTERNAL FUNCTIONS

    def __repr__(self):
        return f"AnimatedImage({self.anchor}, {self.imgs[self.frame]} and {self.number_of_frames - 1} others.)"
    
    def __iter__(self):
        for img in self.imgs:
            yield img

    def _draw(self, canvas, options):
        self.imgs[self.frame].anchor = self.anchor.clone()
        self.imgs[self.frame].draw(canvas, _internal_call=True)

        self.drawn_frame = self.frame
        if self.graphwin != canvas:
            for img in self.imgs:
                img.graphwin = canvas

        if self.autoflush and self not in GraphicsObject.animated_image_instances:
            GraphicsObject.animated_image_instances.add(self)

    def _move(self, dx, dy):
        self.anchor.x += dx
        self.anchor.y += dy

    def _rotate(self, dr, sampling=None, center=None):
        for img in self.imgs:
            img.rotate(dr)
            
    def move_up_layer(self, layers=1):
        if not isinstance(layers, int):
            raise GraphicsError(f"\n\nGraphicsError: layers to move up must be an integer, not {layers}")
        if layers < 0:
            raise GraphicsError("\n\nGraphicsError: layers to move up must be greater than (or equal to) 0, "
                                f"not {layers}")

        GraphicsObject.object_layers[self.layer].remove(self)
        self.layer += layers

        while self.layer > len(GraphicsObject.object_layers) - 1:
            GraphicsObject.object_layers.append([])
        GraphicsObject.object_layers[self.layer].add(self)

        for obj in self.imgs:
            obj.move_up_layer(layers=layers)
        return self

    def move_down_layer(self, layers=1):
        if not isinstance(layers, int):
            raise GraphicsError(f"\n\nGraphicsError: layers to move down must be an integer, not {layers}")
        if layers < 0:
            raise GraphicsError("\n\nGraphicsError: layers to move down must be greater than (or equal to) 0, "
                                f"not {layers}")

        GraphicsObject.object_layers[self.layer].remove(self)
        self.layer += layers
        if self.layer < 0:
            self.layer = 0

        while self.layer > len(GraphicsObject.object_layers) - 1:
            GraphicsObject.object_layers.append([])
        GraphicsObject.object_layers[self.layer].add(self)

        for obj in self.imgs:
            obj.move_down_layer(layers=layers)
        return self

    def set_layer(self, layer=0):
        if not isinstance(layer, int):
            raise GraphicsError(f"\n\nGraphicsError: layer to set to must be an integer, not {layer}")
        if layer < 0:
            raise GraphicsError("\n\nGraphicsError: layer to set to must be greater than (or equal to) 0, "
                                f"not {layer}")

        for obj in self.imgs:
            obj.set_layer(layer=layer)

        GraphicsObject.object_layers[self.layer].remove(self)
        while layer > len(GraphicsObject.object_layers) - 1:
            GraphicsObject.object_layers.append({*()})
        GraphicsObject.object_layers[layer].add(self)

        self.layer = layer

        return self

    def set_autoflush(self, autoflush):
        self.autoflush = autoflush
        if self.autoflush:
            if self.drawn and self not in GraphicsObject.animated_image_instances:
                GraphicsObject.animated_image_instances.add(self)

        elif self in GraphicsObject.animated_image_instances:
            GraphicsObject.animated_image_instances.remove(self)

    def increment_frame(self, _time=None, _internal_call=False):
        self.frame += 1
        if self.frame == self.number_of_frames:
            self.frame = 0

        if _time is None:
            self.last_update_time = timetime()
        else:
            self.last_update_time = _time

        for obj in self.frame_bound_objects:
            if obj.drawn:
                obj.increment_frame(_time=_time, _internal_call=_internal_call)

        if self.callbacks["frame increment"] is not None:
            self.callbacks["frame increment"]()

        self._update_layer()
        return self

    def set_frame_increment_callback(self, func):
        if not (callable(func) or func is None):
            raise GraphicsError("\n\nGraphicsError: Frame Increment callback for Animated Image must be a function, "
                                f"not {func}")
        self.callbacks["frame increment"] = func
        return self

    def decrement_frame(self, _time=None, _internal_call=False):
        self.frame -= 1
        if self.frame == -1:
            self.frame = self.number_of_frames - 1

        if _time is None:
            self.last_update_time = timetime()
        else:
            self.last_update_time = _time

        for obj in self.frame_bound_objects:
            obj.decrement_frame(_time=_time, _internal_call=_internal_call)
        self._update_layer()
        return self

    def set_frame(self, frame, _time=None, _internal_call=False):

        if not (0 <= frame < self.number_of_frames):
            raise GraphicsError("\n\nGraphicsError: Frame to set the Animated Image to must be between (inclusive) 0 & "
                                f"{self.number_of_frames - 1}, not {frame}")

        self.frame = frame

        if _time is None:
            self.last_update_time = timetime()
        else:
            self.last_update_time = _time
        self._update_layer()
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
        self.set_autoflush(False)
        return self

    # -------------------------------------------------------------------------
    # OTHER & IMPORTANT FUNCTIONS

    def _undraw(self, set_blinking=True):
        self.imgs[self.drawn_frame].undraw(set_blinking=set_blinking)

        if self in GraphicsObject.animated_image_instances:
            GraphicsObject.animated_image_instances.remove(self)

    def base_undraw(self):
        for img in self.imgs:
            if img.drawn:
                img.base_undraw()

    def is_clicked(self, mouse_pos):
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

    def skew_y(self, scale=0.3, sampling=None, align="center"):
        for img in self.imgs:
            img.skew_y(scale=scale, sampling=sampling, align=align)
        return self

    def skew_xy(self, x_scale=0.3, y_scale=None, sampling=None, x_align="center", y_align=None):
        for img in self.imgs:
            img.skew_xy(x_scale=x_scale, y_scale=y_scale, sampling=sampling, x_align=x_align, y_align=y_align)
        return self

    # ----------------------------------
    # Resizing Functions

    def resize(self, width, height, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize(width, height, sampling=sampling, _external_call=_external_call)
        return self

    def resize_height(self, height, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_height(height, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                _external_call=_external_call)
        return self

    def resize_width(self, width, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_width(width, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                               _external_call=_external_call)
        return self

    def resize_factor(self, factor, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_factor(factor, sampling=sampling, _external_call=_external_call)
        return self

    def resize_width_factor(self, factor, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_width_factor(factor, sampling=sampling, _external_call=_external_call)
        return self

    def resize_height_factor(self, factor, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_width_factor(factor, sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit(self, obj, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_to_fit(obj, sampling=sampling, _external_call=_external_call)
        return self

    def resize_to_fit_width(self, obj, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for img in self.imgs:
            img.resize_to_fit_width(obj, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                      _external_call=_external_call)
        return self

    def resize_to_fit_height(self, obj, preserve_aspect_ratio=False, sampling=None, _external_call=True):
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
            img.more_enhance_edge()
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
