from goopylib.objects.Checkbox import Checkbox
from goopylib.objects.GraphicsObject import GraphicsObject

class Button:
    def __init__(self, graphic, hover_graphic=None, clicked_graphic=None, disabled_graphic=None,
                 disable=False, autoflush=True, label=None, sound=None, window=None):

        self.normal_graphic = graphic

        if hover_graphic is not None:
            self.hover_graphic = hover_graphic
        else:
            self.hover_graphic = graphic

        if clicked_graphic is not None:
            self.clicked_graphic = clicked_graphic
        else:
            self.clicked_graphic = graphic

        if disabled_graphic is not None:
            self.disabled_graphic = disabled_graphic
        else:
            self.disabled_graphic = graphic

        self.graphic = self.normal_graphic

        self.label = label
        self.is_disabled = disable

        self.graphwin = None
        self.drawn = False

        self.is_rotating = False

        if not isinstance(self, Checkbox):
            GraphicsObject.button_instances.append(self)

    def __repr__(self):
        return "Button({})".format(self.graphic)

    def draw(self, canvas):
        self.graphic.draw(canvas)

        if self.label is not None:
            self.label.draw(canvas)
        self.graphwin = canvas

        self.drawn = True
        return self

    def undraw(self):
        self.graphic.undraw()
        if self.label is not None:
            self.label.undraw()

        self.drawn = False
        return self

    def redraw(self):
        if self.graphic.graphwin is None and self.graphwin is not None:
            self.graphic.graphwin = self.graphwin

        if self.label is not None:
            self.label.redraw()

        self.drawn = True
        self.graphic.redraw()

        return self

    def set_graphic(self, graphic):
        self.undraw()
        if graphic == "Normal":
            self.graphic = self.normal_graphic
        elif graphic == "Hover":
            self.graphic = self.hover_graphic
        elif graphic == "Clicked":
            self.graphic = self.clicked_graphic
        elif graphic == "Disabled":
            self.graphic = self.disabled_graphic

        self.draw(self.graphwin)

    def animate_rotate(self, dr, t, easing="Linear", args=None):
        self.hover_graphic.animate_rotate(dr, t, easing, args)
        self.normal_graphic.animate_rotate(dr, t, easing, args)
        self.clicked_graphic.animate_rotate(dr, t, easing, args)
        self.disabled_graphic.animate_rotate(dr, t, easing, args)

        self.is_rotating = True

        if self.label is not None:
            self.label.animate_rotate(dr, t, easing, args)

        return self

    def move(self, dx, dy):
        self.hover_graphic.move(dx, dy)
        self.normal_graphic.move(dx, dy)
        self.clicked_graphic.move(dx, dy)
        self.disabled_graphic.move(dx, dy)

        if self.label is not None:
            self.label.move(dx, dy)

        return self

    def move_to(self, x, y):
        self.hover_graphic.move_to(x, y)
        self.normal_graphic.move_to(x, y)
        self.clicked_graphic.move_to(x, y)
        self.disabled_graphic.move_to(x, y)

        if self.label is not None:
            self.label.move_to(x, y)

        return self

    def is_clicked(self, mouse_pos):
        return self.graphic.is_clicked(mouse_pos) and not self.is_disabled

    def get_anchor(self):
        return self.graphic.anchor

    def disable(self):
        self.is_disabled = True

        self.undraw()
        self.graphic = self.disabled_graphic
        self.draw(self.graphwin)

    def enable(self):
        self.is_disabled = False

        self.undraw()
        self.graphic = self.normal_graphic
        self.draw(self.graphwin)

    def toggle_enabled(self):
        self.set_enabled(not self.is_disabled)

    def set_enabled(self, enable):
        if enable:
            self.enable()
        else:
            self.disable()

    def change_graphic(self, graphic=None, hover_graphic=None, clicked_graphic=None, disabled_graphic=None, label=None):
        self.undraw()
        if hover_graphic is not None:
            self.hover_graphic = hover_graphic
        if graphic is not None:
            self.normal_graphic = graphic
        if clicked_graphic is not None:
            self.clicked_graphic = clicked_graphic
        if disabled_graphic is not None:
            self.disabled_graphic = disabled_graphic

        if label is not None:
            self.label = label

        self.draw(self.graphwin)
