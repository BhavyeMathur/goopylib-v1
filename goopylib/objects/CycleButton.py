from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError

import time

class CycleButton:
    def __init__(self, state, *states, window):
        self.states = list(states)
        self.state = state

        self.label = None

        for obj in states:
            if not isinstance(obj, GraphicsObject):
                raise GraphicsError("\n\nThe states must all be Graphic Objects")

        self.rotating_dest = None
        self.rotating_initial = None
        self.rotating_dist = None
        self.rotating_easing = None

        self.is_rotating = True
        self.rotation = 0

        self.rotating_time = None
        self.rotating_update = 0
        self.rotating_start = None
        self.rotating_args = None

        self.graphwin = None
        self.drawn = False

        self.graphic = states[state]

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

    def rotate(self, dr):
        for graphic in self.states:
            graphic.rotate(dr)

    def set_rotation(self, r):
        for graphic in self.states:
            graphic.set_rotation(r)

    def animate_rotate(self, dr, t, easing="Linear", args=None):

        self.rotating_dest = self.rotation + dr
        self.rotating_initial = self.rotation
        self.rotating_dist = dr
        self.rotating_easing = easing

        self.is_rotating = True

        self.rotating_time = t
        self.rotating_update = time.time()
        self.rotating_start = self.rotating_update
        self.rotating_args = args

        GraphicsObject.rotating_objects.append(self)
        return self
