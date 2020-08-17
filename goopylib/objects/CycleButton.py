from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError

from math import cos, sin


class CycleButton(GraphicsObject):
    def __init__(self, *states, state=0, disabled_graphic=None, autoflush=True, layer=None, tag=None, bounds=None):
        self.states = list(states)
        self.state = state

        self.is_disabled = False
        self.disabled_graphic = disabled_graphic

        self.autoflush = autoflush

        self.graphic = states[state]

        GraphicsObject.__init__(self, (), tag=tag, bounds=bounds)
        GraphicsObject.cyclebutton_instances.add(self)

        if layer is not None:
            self.set_layer(layer)

    def __repr__(self):
        return f"CycleButton({self.graphic} and {len(self.states)} other states)"

    def __iter__(self):
        for state in self.states:
            yield state

    def _draw(self, canvas=None, options=None):
        self.states[self.state].draw(canvas, _internal_call=True)

        for graphic in self.states:
            graphic.graphwin = canvas
        if self.disabled_graphic is not None:
            self.disabled_graphic.graphwin = canvas

        return self

    def _undraw(self, set_blinking=True):
        for obj in self.states:
            print(obj, obj.drawn)
            if obj.drawn:
                obj.undraw(set_blinking=set_blinking)
        return self

    def base_undraw(self):
        for obj in self.states:
            if obj.drawn:
                obj.base_undraw()

    def _rotate(self, dr, sampling="bicubic", center=None):
        for graphic in self.states:
            graphic.rotate(dr, sampling=sampling, center=center)
        if self.disabled_graphic is not None:
            self.disabled_graphic.rotate(dr, sampling=sampling, center=center)

    def _move(self, dx, dy):
        for graphic in self.states:
            graphic.move(dx, dy)
        if self.disabled_graphic is not None:
            self.disabled_graphic.move(dx, dy)

    def click(self):
        if not self.is_disabled:
            self.state += 1
            self.state %= len(self.states)
            self.graphic = self.states[self.state]

            self._update_layer()
        return self

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            return self.graphic.is_clicked(mouse_pos)
        else:
            return self.bounds.is_clicked(mouse_pos)

    def change_graphic(self, element, value):
        self.states[element] = value
        self._update_layer()

    # -------------------------------------------------------------------------
    # LAYERING SYSTEM FUNCTIONS

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

        for obj in self.states:
            obj.move_up_layer(layers=layers)
        if self.disabled_graphic is not None:
            self.disabled_graphic.move_up_layer(layers=layers)
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

        for obj in self.states:
            obj.move_down_layer(layers=layers)
        if self.disabled_graphic is not None:
            self.disabled_graphic.move_down_layer(layers=layers)
        return self

    def set_layer(self, layer=0):
        if not isinstance(layer, int):
            raise GraphicsError(f"\n\nGraphicsError: layer to set to must be an integer, not {layer}")
        if layer < 0:
            raise GraphicsError("\n\nGraphicsError: layer to set to must be greater than (or equal to) 0, "
                                f"not {layer}")

        for obj in self.states:
            obj.set_layer(layer=layer)
        if self.disabled_graphic is not None:
            self.disabled_graphic.set_layer(layer=layer)

        GraphicsObject.object_layers[self.layer].remove(self)
        while layer > len(GraphicsObject.object_layers) - 1:
            GraphicsObject.object_layers.append({*()})
        GraphicsObject.object_layers[layer].add(self)

        self.layer = layer

        return self

    # -------------------------------------------------------------------------
    # ENABLING & DISABLING FUNCTIONS

    def enable(self):
        self.is_disabled = False

        self.graphic = self.states[self.state]

        self.rotation = self.graphic.rotation
        self.cosrotation = cos(self.rotation / 57.2958)
        self.sinrotation = sin(self.rotation / 57.2958)
        self._update_layer()
        return self

    def disable(self):
        self.is_disabled = True

        self.graphic = self.disabled_graphic

        self.rotation = self.graphic.rotation
        self.cosrotation = cos(self.rotation / 57.2958)
        self.sinrotation = sin(self.rotation / 57.2958)
        self._update_layer()
        return self

    def toggle_enabled(self):
        self.is_disabled = not self.is_disabled
        if self.is_disabled:
            self.disable()
        else:
            self.enable()
        return self

    def set_enabled(self, enable=True):
        if enable:
            self.enable()
        else:
            self.disable()
        return self

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_state(self, state):
        if state != self.state:
            if self.graphic in GraphicsObject.redraw_on_frame[self.layer]:
                GraphicsObject.redraw_on_frame[self.layer].remove(self.graphic)

            self.state = state
            self.graphic = self.states[state]

            self.rotation = self.graphic.rotation
            self.cosrotation = cos(self.rotation / 57.2958)
            self.sinrotation = sin(self.rotation / 57.2958)

            self._update_layer()

        return self

    def add_state(self, state):
        self.states.append(state)
        return self

    def remove_state(self, state):
        if state not in self.states:
            raise GraphicsError("\n\nThe state to remove is not an existing state of this cycle button")

        self.states.remove(state)
        return self

    def pop_state(self, index):
        return self.states.pop(index)

    def set_object(self, obj):
        if obj not in self.states:
            if obj in GraphicsObject.tagged_objects:
                obj = GraphicsObject.tagged_objects[obj]
            else:
                raise GraphicsError(f"\n\nGraphicsError: The object you have specified ({obj}) is not a valid state "
                                    f"for this CycleButton")

        if obj != self.graphic:
            if self.graphic in GraphicsObject.redraw_on_frame[self.layer]:
                GraphicsObject.redraw_on_frame[self.layer].remove(self.graphic)

            self.state = self.states.index(obj)
            self.graphic = obj

            self.rotation = self.graphic.rotation
            self.cosrotation = cos(self.rotation / 57.2958)
            self.sinrotation = sin(self.rotation / 57.2958)

            self._update_layer()

        return self

    def get_object(self):
        return self.states[self.state]

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
        return self.graphic.anchor

    def get_state(self):
        return self.state

    def get_graphics(self):
        return self.states

    def set_contrast(self, level):
        for state in self.states:
            state.set_contrast(level)
        self._update_layer()
        return self

    def change_contrast(self, level):
        for state in self.states:
            state.change_contrast(level)
        self._update_layer()
        return self

    def reset_contrast(self):
        self.set_contrast(0)
        self._update_layer()

    # -------------------------------------------------------------------------
    # IMAGE MANIPULATION FUNCTIONS

    def crop(self, left=0, top=0, right=500, down=500, align="center"):
        for state in self.states:
            state.crop(left=left, top=top, right=right, down=down, align=align)
        self._update_layer()
        return self

    # Blending & Compositing Functions

    def blend(self, state, alpha):
        for state in self.states:
            state.blend(state, alpha)
        self._update_layer()
        return self

    def alpha_composite(self, other):
        for state in self.states:
            state.alpha_composite(other)
        self._update_layer()
        return self

    def composite(self, other, state_mask):
        for state in self.states:
            state.composite(other, state_mask)
        self._update_layer()
        return self

    def convert_greyscale(self):
        for state in self.states:
            state.convert_greyscale()
        self._update_layer()
        return self

    def convert_binary(self):
        for state in self.states:
            state.convert_binary()
        self._update_layer()
        return self

    # ----------------------------------
    # Flipping Functions

    def flip(self, x_axis=True, y_axis=True):
        for state in self.states:
            state.flip(x_axis=x_axis, y_axis=y_axis)
        self._update_layer()
        return self

    def flip_x(self):
        for state in self.states:
            state.flip_x()
        self._update_layer()
        return self

    def flip_y(self):
        for state in self.states:
            state.flip_y()
        self._update_layer()
        return self

    def flip_xy(self):
        for state in self.states:
            state.flip_xy()
        self._update_layer()
        return self

    def transverse(self):
        for state in self.states:
            state.transverse()
        self._update_layer()
        return self

    def transpose(self):
        for state in self.states:
            state.transpose()
        self._update_layer()
        return self

    # ----------------------------------
    # Skew Transformation Functions

    def skew_x(self, scale=0.3, sampling="bicubic", align="center"):
        for state in self.states:
            state.skew_x(scale=scale, sampling=sampling, align=align)
        self._update_layer()
        return self

    def skew_y(self, scale=0.3, sampling=None, align="center"):
        for state in self.states:
            state.skew_y(scale=scale, sampling=sampling, align=align)
        self._update_layer()
        return self

    def skew_xy(self, x_scale=0.3, y_scale=None, sampling=None, x_align="center", y_align=None):
        for state in self.states:
            state.skew_xy(x_scale=x_scale, y_scale=y_scale, sampling=sampling, x_align=x_align, y_align=y_align)
        self._update_layer()
        return self

    # ----------------------------------
    # Resizing Functions

    def resize(self, width, height, sampling=None, _external_call=True):
        for state in self.states:
            state.resize(width, height, sampling=sampling, _external_call=_external_call)
        self._update_layer()
        return self

    def resize_height(self, height, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_height(height, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                _external_call=_external_call)
        self._update_layer()
        return self

    def resize_width(self, width, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_width(width, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                               _external_call=_external_call)
        self._update_layer()
        return self

    def resize_factor(self, factor, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_factor(factor, sampling=sampling, _external_call=_external_call)
        self._update_layer()
        return self

    def resize_width_factor(self, factor, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_width_factor(factor, sampling=sampling, _external_call=_external_call)
        self._update_layer()
        return self

    def resize_height_factor(self, factor, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_width_factor(factor, sampling=sampling, _external_call=_external_call)
        self._update_layer()
        return self

    def resize_to_fit(self, obj, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_to_fit(obj, sampling=sampling, _external_call=_external_call)
        self._update_layer()
        return self

    def resize_to_fit_width(self, obj, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_to_fit_width(obj, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                      _external_call=_external_call)
        self._update_layer()
        return self

    def resize_to_fit_height(self, obj, preserve_aspect_ratio=False, sampling=None, _external_call=True):
        for state in self.states:
            state.resize_to_fit_height(obj, preserve_aspect_ratio=preserve_aspect_ratio, sampling=sampling,
                                       _external_call=_external_call)
        self._update_layer()
        return self

    # ----------------------------------
    # Blurring & Sharpening Functions

    def blur(self):
        for state in self.states:
            state.blur()
        self._update_layer()
        return self

    def blur_box(self, radius=3):
        for state in self.states:
            state.blur_box(radius=radius)
        self._update_layer()
        return self

    def blur_gaussian(self, radius=3):
        for state in self.states:
            state.blur_gaussian(radius=radius)
        self._update_layer()
        return self

    def sharpen(self, radius=3, percent=150):
        for state in self.states:
            state.sharpen(radius=radius, percent=percent)
        self._update_layer()
        return self

    # ----------------------------------
    # Filter Functions

    def filter_contour(self):
        for state in self.states:
            state.filter_contour()
        self._update_layer()
        return self

    def filter_detail(self):
        for state in self.states:
            state.filter_detail()
        self._update_layer()
        return self

    def filter_emboss(self):
        for state in self.states:
            state.filter_emboss()
        self._update_layer()
        return self

    def filter_find_edges(self):
        for state in self.states:
            state.filter_find_edges()
        self._update_layer()
        return self

    def filter_sharpen(self):
        for state in self.states:
            state.filter_sharpen()
        self._update_layer()
        return self

    def filter_smooth(self):
        for state in self.states:
            state.filter_smooth()
        self._update_layer()
        return self

    def filter_more_smooth(self):
        for state in self.states:
            state.filter_more_smooth()
        self._update_layer()
        return self

    def filter_enhance_edge(self):
        for state in self.states:
            state.filter_enhance_edge()
        self._update_layer()
        return self

    def filter_more_enhance_edge(self):
        for state in self.states:
            state.more_enhance_edge()
        self._update_layer()
        return self
