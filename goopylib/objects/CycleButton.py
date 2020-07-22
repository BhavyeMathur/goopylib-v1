from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError

class CycleButton(GraphicsObject):
    def __init__(self, *states, state=0, disabled_graphic=None, autoflush=True, layer=None):
        self.states = list(states)
        self.state = state

        self.is_disabled = False
        self.disabled_graphic = disabled_graphic

        self.autoflush = autoflush

        self.graphic = states[state]

        GraphicsObject.__init__(self, ())
        GraphicsObject.cyclebutton_instances.append(self)

        if layer is not None:
            self.set_layer(layer)

    def __repr__(self):
        return f"CycleButton({self.graphic} and {len(self.states)} other states)"

    def _draw(self, canvas, options=()):
        self.graphic.draw(canvas)
        for graphic in self.states:
            graphic.graphwin = canvas
        if self.disabled_graphic is not None:
            self.disabled_graphic.graphwin = canvas
        return self

    def undraw(self, set_blinking=True):
        self.graphic.undraw(set_blinking=set_blinking)
        self.drawn = False
        return self

    def _rotate(self, dr):
        for graphic in self.states:
            graphic.rotate(dr)
        if self.disabled_graphic is not None:
            self.disabled_graphic.rotate(dr)

    def _move(self, dx, dy):
        for graphic in self.states:
            graphic.move(dx, dy)
        if self.disabled_graphic is not None:
            self.disabled_graphic.move(dx, dy)

    def click(self):
        if not self.is_disabled:
            self.undraw()
            self.state += 1
            self.state %= len(self.states)
            self.graphic = self.states[self.state]
            self.draw(self.graphwin)
        return self

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos)

    def change_graphic(self, element, value):
        self.states[element] = value

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
        GraphicsObject.object_layers[self.layer].append(self)

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
        GraphicsObject.object_layers[self.layer].append(self)

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
            GraphicsObject.object_layers.append([])
        GraphicsObject.object_layers[layer].append(self)

        self.layer = layer

        return self

    # -------------------------------------------------------------------------
    # ENABLING & DISABLING FUNCTIONS

    def enable(self):
        self.is_disabled = False
        self.undraw()
        self.graphic = self.states[self.state]
        self._draw(self.graphwin)

    def disable(self):
        self.is_disabled = True
        self.undraw()
        self.graphic = self.disabled_graphic
        self._draw(self.graphwin)

    def toggle_enabled(self):
        self.is_disabled = not self.is_disabled
        self.undraw()
        if self.is_disabled:
            self.graphic = self.disabled_graphic
        self.draw(self.graphwin)

    def set_enabled(self, enable=True):
        if enable:
            self.enable()
        else:
            self.disable()

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_state(self, state):
        self.undraw()
        self.state = state
        self.graphic = self.states[state]
        self.draw(self.graphwin)

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

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
        return self.graphic.anchor

    def get_state(self):
        return self.state