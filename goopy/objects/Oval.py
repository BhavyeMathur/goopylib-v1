import goopy.objects._BBox as gpBBox
from goopy.objects.Rectangle import Rectangle

from goopy.Point import Point
from goopy._internal_classes import VectorEquation


class Oval(gpBBox.BBox):

    def __init__(self, center, radius1, radius2, bounds=None, style=None, fill=None, outline=None, outline_width=None,
                 cursor="arrow", window=None):

        p1 = Point(center.x - radius1, center.y - radius2)
        p2 = Point(center.x + radius1, center.y + radius2)

        self.radius1 = radius1
        self.radius2 = radius2

        gpBBox.BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, outline_width=outline_width,
                             style=style, cursor=cursor,
                             window=window)

        self.equation = VectorEquation("(((x-{})**2)/({}**2))+(((y-{})**2)/({}**2)) < 1".format(center.x, radius1,
                                                                                                center.y, radius2))

    def __repr__(self):
        return "Oval({}, {})".format(str(self.p1), str(self.p2))

    def clone(self):
        other = Oval(self.p1, self.p2)
        other.config = self.config.copy()
        return other

    def _draw(self, canvas, options):
        p1 = self.p1
        p2 = self.p2
        x1, y1 = canvas.to_screen(p1.x, p1.y)
        x2, y2 = canvas.to_screen(p2.x, p2.y)
        return canvas.create_oval(x1, y1, x2, y2, options)

    def _set_resizable(self, resizables, thickness=10, show_bounds=False):
        self.resizing_bounds = {}
        if resizables[0]:
            self.resizing_bounds["top"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                    Point(self.p2.x + thickness / 2, self.p1.y + thickness / 2),
                                                    cursor="sb_v_double_arrow")
        if resizables[1]:
            self.resizing_bounds["bottom"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y - thickness / 2),
                                                       Point(self.p1.x - thickness / 2, self.p2.y + thickness / 2),
                                                       cursor="sb_v_double_arrow")
        if resizables[2]:
            self.resizing_bounds["left"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                     Point(self.p1.x + thickness / 2, self.p2.y + thickness / 2),
                                                     cursor="sb_h_double_arrow")
        if resizables[3]:
            self.resizing_bounds["right"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y + thickness / 2),
                                                      Point(self.p2.x - thickness / 2, self.p1.y - thickness / 2),
                                                      cursor="sb_h_double_arrow")

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            return self.equation.is_clicked(mouse_pos)
        else:
            return self.bounds.is_clicked(mouse_pos)

    def _update(self):
        self.equation = VectorEquation("(((x-{})**2)/({}**2))+(((y-{})**2)/({}**2)) < 1".format(self.anchor.x,
                                                                                                self.radius1,
                                                                                                self.anchor.y,
                                                                                                self.radius2))