from goopylib.objects.CycleButton import CycleButton
from goopylib.util import GraphicsError

class Checkbox(CycleButton):
    def __init__(self, true_graphic, false_graphic, disabled_graphic=None, autoflush=True, state=True, layer=0,
                 tag=None):
        super().__init__(true_graphic, false_graphic, disabled_graphic=disabled_graphic, state=int(not state),
                         layer=layer, autoflush=autoflush, tag=tag)
        self.bound_objects = {*()}

    def __repr__(self):
        return f"Checkbox({self.states[0]}, {self.states[1]})"

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos)

    def set_state(self, state):
        super().set_state(int(state))
        for obj in self.bound_objects:
            obj.set_state(state)
        return self

    def get_state(self):
        return bool(self.state)

    def change_state(self):
        self.set_state(not self.state)
        return self

    def click(self):
        self.change_state()
        return self

    def bind_state_to(self, other):
        if not isinstance(other, Checkbox):
            raise GraphicsError(f"Object to bind this Checkbox to must be another Checkbox, not {other}")
        other.bound_objects.add(self)

        self.autoflush = False
        self.set_state(other.state)

        return self
