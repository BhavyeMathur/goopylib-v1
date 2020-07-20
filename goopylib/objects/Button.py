from goopylib.objects.Checkbox import Checkbox
from goopylib.objects.GraphicsObject import GraphicsObject

class Button(GraphicsObject):
    def __init__(self, graphic, hover_graphic=None, clicked_graphic=None, disabled_graphic=None,
                 disable=False, autoflush=True, label=None, layer=0):

        self.disabled_graphic_given = True
        self.clicked_graphic_given = True
        self.hover_graphic_given = True

        self.normal_graphic = graphic
        if hover_graphic is not None:
            self.hover_graphic = hover_graphic
        else:
            self.hover_graphic = graphic
            self.hover_graphic_given = False

        if clicked_graphic is not None:
            self.clicked_graphic = clicked_graphic
        else:
            self.clicked_graphic = graphic
            self.clicked_graphic_given = False

        if disabled_graphic is not None:
            self.disabled_graphic = disabled_graphic
        else:
            self.disabled_graphic = graphic
            self.disabled_graphic_given = False

        self.graphic = self.normal_graphic

        self.label = label
        self.is_disabled = disable

        if not isinstance(self, Checkbox):
            GraphicsObject.button_instances.append(self)

        GraphicsObject.__init__(self, options=(), layer=layer)

    def __repr__(self):
        return "Button({})".format(self.graphic)

    def _draw(self, canvas, options):
        self.graphic.draw(canvas)

        self.anchor = self.graphic.anchor

        if self.label is not None:
            self.label.draw(canvas)

    def _move(self, dx, dy):
        if self.hover_graphic_given:
            self.hover_graphic.move(dx, dy)
        self.normal_graphic.move(dx, dy)
        if self.clicked_graphic_given:
            self.clicked_graphic.move(dx, dy)
        if self.disabled_graphic_given:
            self.disabled_graphic.move(dx, dy)

        self.anchor.x += dx
        self.anchor.y += dy

        if self.label is not None:
            self.label.move(dx, dy)

    def _rotate(self, dr):
        self.disabled_graphic.rotate(dr)
        self.normal_graphic.rotate(dr)
        self.hover_graphic.rotate(dr)
        self.clicked_graphic.rotate(dr)
        if self.label is not None:
            self.label.rotate(dr)

    def undraw(self, set_blinking=False):
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

    def get_width(self):
        return self.graphic.get_width()

    def get_height(self):
        return self.graphic.get_height()

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

    def is_clicked(self, mouse_pos):
        if self.drawn:
            return self.graphic.is_clicked(mouse_pos) and not self.is_disabled
        else:
            return False

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
