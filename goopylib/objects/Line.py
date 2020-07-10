from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point
from goopylib.styles import *


class Line(GraphicsObject):

    def __init__(self, *p, bounds=None, style=None, outline=None, outline_width=None, arrow=None, cursor="arrow"):

        GraphicsObject.__init__(self, options=["arrow", "width", "fill"], cursor=cursor)

        if arrow in STYLES[self.style].keys():
            self.arrow = STYLES[self.style][arrow]
        elif isinstance(arrow, str):
            self.arrow = arrow
        else:
            if "arrow face" in STYLES[self.style].keys():
                self.arrow = STYLES[self.style]["arrow face"]
            else:
                self.arrow = STYLES["default"]["arrow face"]

        self.points = p

        self.low_x, self.low_y = self.points[0].x, self.points[0].y
        self.high_x, self.high_y = self.low_x, self.low_y
        self.anchor = Point(0, 0)
        for point in self.points:
            if point.x < self.low_x:
                self.low_x = point.x
            elif point.x > self.high_x:
                self.high_x = point.x
            if point.y < self.low_y:
                self.low_y = point.y
            elif point.y > self.high_y:
                self.high_y = point.y
            self.anchor += point

        self.width = abs(self.low_x.distance_x(self.high_x))
        self.height = abs(self.low_y.distance_y(self.high_y))
        self.anchor /= len(self.points)

        self.set_outline = self.set_fill

    def __repr__(self):
        return f"Line({self.points})"

    def _draw(self, canvas, options):
        points = [canvas.to_screen(point.x, point.y) for point in self.points]
        self.graphwin = canvas

        return canvas.create_line(points, options)

    def set_arrow(self, option):
        if option.lower() not in ["first", "last", "both", "none"]:
            raise GraphicsError("\n\nArrow option for line must be one of ['first', 'last', 'both', 'none']")
        self._reconfig("arrow", option)

    def remove_arrows(self):
        self.set_arrow("none")

    def set_arrow_both(self):
        self.set_arrow("none")

    def set_arrow_first(self):
        self.set_arrow("none")

    def set_arrow_last(self):
        self.set_arrow("none")

    def _move(self, dx, dy):
        for i in range(len(self.points)):
            self.points[i] += Point(dx, dy)

        self.anchor = self.get_anchor()
        self._update()

    def is_clicked(self, mouse_pos):
        return False

    def get_anchor(self):
        return Point((self.p1.x + self.p2.x) / 2, (self.p1.y + self.p2.y) / 2)

    def get_width(self):
        return self.width

    def get_height(self):
        return self.height

    def get_fill(self):
        return self.config["fill"]

