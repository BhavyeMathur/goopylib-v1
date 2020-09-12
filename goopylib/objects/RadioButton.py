from goopylib.objects.Checkbox import Checkbox
from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError

class RadioButton(GraphicsObject):

    def __init__(self, *checkboxes, state=0, cursor="arrow", layer=0, tag=None, autoflush=True):
        for obj in checkboxes:
            if not isinstance(obj, Checkbox):
                raise GraphicsError(f"\n\nGraphicsError: All Radio Button states must be Checkboxes, not {obj}")
            if obj in GraphicsObject.cyclebutton_instances:
                GraphicsObject.cyclebutton_instances.remove(obj)
            obj.set_state(False)

        self.checkboxes = checkboxes

        super().__init__(options=(), cursor=cursor, layer=layer, tag=tag)
        if autoflush:
            GraphicsObject.radiobutton_instances.add(self)

        self.state = state

        self.current_state = self.checkboxes[self.state].set_state(True)

    def __repr__(self):
        return f"RadioButton({self.checkboxes[self.state]} and {len(self.checkboxes) - 1} others)"

    def _draw(self, canvas, options):
        for checkbox in self.checkboxes:
            checkbox.draw(canvas, _internal_call=True)
        return self

    def _undraw(self):
        for checkbox in self.checkboxes:
            checkbox.undraw()

    def base_undraw(self):
        for checkbox in self.checkboxes:
            checkbox.base_undraw()

    def _rotate(self, dr, sampling="bicubic", center=None):
        for checkbox in self.checkboxes:
            checkbox.rotate(dr, sampling=sampling, center=center)

    def _move(self, dx, dy):
        for checkbox in self.checkboxes:
            checkbox.move(dx, dy)

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            for checkbox in self.checkboxes:
                if checkbox.is_clicked(mouse_pos):
                    return True
        else:
            return self.bounds.is_clicked(mouse_pos)

        return False

    def set_autoflush(self, autoflush):
        if autoflush:
            if self not in GraphicsObject.radio_button_instances:
                GraphicsObject.radio_button_instances.add(self)
        elif self in GraphicsObject.radio_button_instances:
            GraphicsObject.radio_button_instances.remove(self)
        return self
