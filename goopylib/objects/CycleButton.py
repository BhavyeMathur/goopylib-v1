from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError
from goopylib.objects.Button import Button

import time

class CycleButton:
    def __init__(self, state, *states, disabled_graphic=None, autoflush=True):
        self.states = list(states)
        self.state = state

        self.label = None

        self.graphwin = None
        self.drawn = False

        self.is_disabled = False
        self.disabled_graphic = disabled_graphic

        self.autoflush = autoflush

        self.graphic = states[state]
        GraphicsObject.cyclebutton_instances.append(self)

    def enable(self):
        self.is_disabled = False
        self.undraw()
        self.graphic = self.states[self.state]
        self.draw(self.graphwin)

    def disable(self):
        self.is_disabled = True
        self.undraw()
        self.graphic = self.disabled_graphic
        self.draw(self.graphwin)

    def toggle_enabled(self):
        self.is_disabled = not self.is_disabled
        self.undraw()
        if self.is_disabled:
            self.graphic = self.disabled_graphic
        self.draw(self.graphwin)

    def draw(self, canvas):
        self.graphic.draw(canvas)
        self.graphwin = canvas
        return self

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos)

    def undraw(self):
        self.graphic.undraw()
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

    def rotate(self, dr):
        for graphic in self.states:
            graphic.rotate(dr)

    def set_rotation(self, r):
        for graphic in self.states:
            graphic.set_rotation(r)

    def animate_rotate(self, dr, t, easing="Linear", args=None):
        GraphicsObject.rotating_objects.append(self)
        return self
