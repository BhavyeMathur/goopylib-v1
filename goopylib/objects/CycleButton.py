from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError

class CycleButton(GraphicsObject):
    def __init__(self, state, *states, disabled_graphic=None, autoflush=True):
        self.states = list(states)
        self.state = state

        self.label = None

        self.is_disabled = False
        self.disabled_graphic = disabled_graphic

        self.autoflush = autoflush

        self.graphic = states[state]

        GraphicsObject.__init__(self, ())
        GraphicsObject.cyclebutton_instances.append(self)

    def __repr__(self):
        return f"CycleButton({self.graphic} and {len(self.states)} other states)"

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

    def _draw(self, canvas, options=()):
        self.graphic.draw(canvas)
        for graphic in self.states:
            graphic.graphwin = canvas
        if self.disabled_graphic is not None:
            self.disabled_graphic.graphwin = canvas
        return self

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos)

    def undraw(self, set_blinking=True):
        self.graphic.undraw()
        self.drawn = False
        return self

    def click(self):
        if not self.is_disabled:
            self.undraw()
            self.state += 1
            self.state %= len(self.states)
            self.graphic = self.states[self.state]
            self.draw(self.graphwin)
        return self

    def change_Graphic(self, element, value):
        self.states[element] = value

    def append(self, state):
        self.states.append(state)

    def remove(self, state):
        if state not in self.states:
            raise GraphicsError("\n\nThe state to remove is not an existing state of this cycle button")

        self.states.remove(state)

    def pop(self, index):
        if index < 0:
            raise GraphicsError("\n\nThe given index is a negative number")

        elif index > len(self.states) - 1:
            raise GraphicsError("\n\nThe specified index cannot be removed as it does not exist")

        self.states.pop(index)

    def get_anchor(self):
        return self.graphic.anchor

    def set_state(self, state):
        self.undraw()
        self.state = state
        self.graphic = self.states[state]
        self.draw(self.graphwin)

    def get_state(self):
        return self.state