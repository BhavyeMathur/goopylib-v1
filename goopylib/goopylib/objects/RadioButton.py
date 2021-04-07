from goopylib.objects.Checkbox import Checkbox
from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.util import GraphicsError

class RadioButton(GraphicsObject):

    def __init__(self, *checkboxes, state=0, cursor="arrow", layer=0, tag=None, autoflush=True):
        if len(checkboxes) > 0:
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

            number_of_states = 0
            self.anchor = [0, 0]
            for state in self.checkboxes:
                state_anchor = state.get_anchor()
                if state_anchor is not None:
                    self.anchor[0] += state_anchor[0]
                    self.anchor[1] += state_anchor[1]
                    number_of_states += 1

            if number_of_states != 0:
                self.anchor = [self.anchor[0] // number_of_states, self.anchor[1] // number_of_states]

            self.current_state = self.checkboxes[self.state].set_state(True)
        else:
            raise GraphicsError("\n\nGraphicsError: RadioButton must have at least 1 state, not 0")

    def __repr__(self):
        return f"RadioButton({self.checkboxes[self.state]} and {len(self.checkboxes) - 1} others)"

    def __iter__(self):
        for state in self.checkboxes:
            yield state

    def __len__(self):
        return len(self.checkboxes)

    def __getitem__(self, item):
        return self.checkboxes[item]

    def _draw(self, canvas, options):
        for checkbox in self.checkboxes:
            checkbox.draw(canvas, _internal_call=True)
        return self

    def _undraw(self):
        for checkbox in self.checkboxes:
            checkbox.undraw()

    def destroy(self):
        GraphicsObject.objects.discard(self)
        GraphicsObject.object_layers[self.layer].discard(self)
        GraphicsObject.draggable_objects.discard(self)
        GraphicsObject.cursor_objects.discard(self)

        GraphicsObject.radiobutton_instances.discard(self)

        if self in GraphicsObject.redraw_on_frame[self.layer]:
            GraphicsObject.redraw_on_frame[self.layer].remove(self)

        for checkbox in self.checkboxes:
            checkbox.destroy()

        self.drawn = False
        self.graphwin = None
        self.id = None

        return self

    def base_undraw(self):
        for checkbox in self.checkboxes:
            checkbox.base_undraw()

    def _rotate(self, dr, sampling="bicubic", center=None):
        for checkbox in self.checkboxes:
            checkbox.rotate(dr, sampling=sampling, center=center)

    def _move(self, dx, dy):
        self.anchor[0] += dx
        self.anchor[1] += dy
        for checkbox in self.checkboxes:
            checkbox.move(dx, dy)

    def get_anchor(self):
        return self.anchor

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
            if self not in GraphicsObject.radiobutton_instances:
                GraphicsObject.radiobutton_instances.add(self)
        elif self in GraphicsObject.radiobutton_instances:
            GraphicsObject.radiobutton_instances.remove(self)
        return self

    def set_state(self, state):
        for checkbox in self.checkboxes:
            if self.checkboxes[state] == checkbox:
                checkbox.click()
                self.current_state.click()
                self.current_state = checkbox
                break

    def get_state(self):
        return self.checkboxes.index(self.current_state)

    def get_object(self):
        return self.current_state
