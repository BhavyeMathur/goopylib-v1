from goopylib.objects.CycleButton import CycleButton

from math import cos, sin

class Checkbox(CycleButton):
    def __init__(self, true_graphic, false_graphic, disabled_graphic=None, autoflush=True, state=True, layer=0,
                 tag=None):
        super().__init__(true_graphic, false_graphic, disabled_graphic=disabled_graphic, state=int(state), layer=layer,
                         autoflush=autoflush, tag=tag)

    def __repr__(self):
        return f"Checkbox({self.states[0]}, {self.states[1]})"

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos)

    def set_state(self, state):
        super().set_state(int(state))
        return self

    def get_state(self):
        return bool(self.state)

    def change_state(self):
        self.set_state(not self.state)

    def click(self):
        self.change_state()
