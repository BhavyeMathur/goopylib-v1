from goopylib.objects.GraphicsObject import GraphicsObject

class Checkbox:
    def __init__(self, true_graphic, false_graphic, disabled_graphic=None, autoflush=True, state=True):

        self.state = state
        self.autoflush = autoflush
        self.is_disabled = False

        self.true_graphic = true_graphic
        self.false_graphic = false_graphic
        self.disabled_graphic = disabled_graphic

        if state:
            self.graphic = true_graphic
        else:
            self.graphic = false_graphic

        self.is_rotating = False

        self.graphwin = None
        self.drawn = False

        GraphicsObject.checkbox_instances.append(self)

    def __repr__(self):
        return "Checkbox({}, {})".format(self.true_graphic, self.false_graphic)

    def draw(self, canvas):
        self.graphwin = canvas

        self.graphic.draw(canvas)
        self.drawn = True

        return self

    def undraw(self):
        self.graphic.undraw()
        self.drawn = False

    def redraw(self):
        if self.graphic.graphwin is None and self.graphwin is not None:
            self.graphic.graphwin = self.graphwin

        self.drawn = True
        self.graphic.redraw()

        return self

    def animate_rotate(self, dr, t, easing="Linear", args=None):
        self.true_graphic.animate_rotate(dr, t, easing, args)
        self.false_graphic.animate_rotate(dr, t, easing, args)

        self.is_rotating = True

        return self

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos)

    def get_anchor(self):
        return self.graphic.anchor

    def disable(self):
        self.is_disabled = True

        self.undraw()
        if self.disabled_graphic is not None:
            self.graphic = self.disabled_graphic
        self.draw(self.graphwin)

    def enable(self):
        self.is_disabled = False

        self.undraw()
        if self.state:
            self.graphic = self.true_graphic
        else:
            self.graphic = self.false_graphic

        self.draw(self.graphwin)

    def toggle_enabled(self):
        self.set_enabled(not self.is_disabled)

    def set_enabled(self, enable):
        if enable:
            self.enable()
        else:
            self.disable()

    def move(self, dx, dy):
        self.true_graphic.move(dx, dy)
        self.false_graphic.move(dx, dy)

        return self

    def move_to(self, x, y):
        self.true_graphic.move_to(x, y)
        self.false_graphic.move_to(x, y)

        return self

    def set_state(self, state):
        self.graphic.undraw()
        self.state = state

        if self.state:
            self.graphic = self.true_graphic
        else:
            self.graphic = self.false_graphic
        if self.graphwin is not None:
            self.graphic.draw(self.graphwin)

    def get_state(self):
        return self.state

    def change_state(self):
        self.set_state(not self.state)

    def click(self):
        self.change_state()

    def change_graphics(self, true_graphic=None, false_graphic=None, disabled_graphic=None):

        self.graphic.undraw()

        if true_graphic is not None:
            self.true_graphic = true_graphic
        if false_graphic is not None:
            self.false_graphic = false_graphic
        if disabled_graphic is not None:
            self.disabled_graphic = disabled_graphic

        if self.state:
            self.graphic = self.true_graphic
        else:
            self.graphic = self.false_graphic

        self.graphic.draw(self.graphwin)
