from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point
from goopylib.styles import *
from goopylib.constants import ARROWS

from math import sin, cos, radians


class Line(GraphicsObject):

    def __init__(self, *p, style=None, outline=None, outline_width=None, arrow=None, cursor="arrow"):

        self.points = list(p)
        for i, p in enumerate(self.points):
            if not isinstance(p, Point):
                raise GraphicsError(f"\n\nGraphicsError: Points for Line class must be Points, not {p} at index {i}")

        self.low_x, self.low_y = None, None
        self.high_x, self.high_y = None, None

        self.width, self.height = None, None
        self.anchor = None

        self.get_anchor()

        GraphicsObject.__init__(self, options=["arrow", "width", "fill"], cursor=cursor)

        self.set_arrow(arrow)
        self.set_outline(outline)
        self.set_outline_width(outline_width)

        self.set_fill = self.set_outline

    def __repr__(self):
        return f"Line({self.points})"

    def _draw(self, canvas, options):
        points = [canvas.to_screen(point.x, point.y) for point in self.points]

        return canvas.create_line(points, options)

    def _move(self, dx, dy):
        for i in range(len(self.points)):
            self.points[i] += Point(dx, dy)
        self.anchor = self.get_anchor()

    def _rotate(self, dr, center=None):
        if center is None:
            center = self.get_anchor()

        for point in self.points:
            # Formula from (https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d)
            p = point.clone()
            point.x = cos(radians(dr)) * (p.x - center.x) - sin(radians(dr)) * (p.y - center.y) + center.x
            point.y = sin(radians(dr)) * (p.x - center.x) + cos(radians(dr)) * (p.y - center.y) + center.yz

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
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

        self.width = (self.low_x ** 2 + self.high_x ** 2) ** 0.5
        self.height = (self.low_y ** 2 + self.high_y ** 2) ** 0.5
        self.anchor /= len(self.points)

        return self.anchor

    def get_width(self):
        return self.width

    def get_height(self):
        return self.height

    def get_fill(self):
        return self.config["fill"]

    def get_arrow(self):
        return self.config["arrow"]

    def get_outline(self):
        return self.config["fill"]

    def get_cursor(self):
        return self.cursor

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_arrow(self, option):
        if option is not None:
            if option.lower() not in ARROWS:
                raise GraphicsError("\n\nGraphicsError: Arrow option for line must be one of "
                                    f"['first', 'last', 'both', 'none'], not {option}")
            self._reconfig("arrow", option)
        else:
            self._reconfig("arrow", STYLES[self.style]["arrow"])

    def remove_arrows(self):
        self.set_arrow("none")

    def set_arrow_both(self):
        self.set_arrow("none")

    def set_arrow_first(self):
        self.set_arrow("none")

    def set_arrow_last(self):
        self.set_arrow("none")

    def set_outline(self, outline):
        if outline is not None:
            if isinstance(outline, Colour):
                self._reconfig("fill", outline)
            elif outline in STYLES[self.style].keys():
                self._reconfig("fill", STYLES[self.style][outline])
            else:
                raise GraphicsError("\n\nGraphicsError: The line outline must be either a Colour or a string referencing a "
                                    f"colour style, not {outline}")
        else:
            self._reconfig("fill", STYLES[self.style]["line outline"])

    def set_outline_width(self, outline_width):
        if outline_width is not None:
            if isinstance(outline_width, Colour):
                self._reconfig("width", outline_width)
            elif outline_width in STYLES[self.style].keys():
                self._reconfig("width", STYLES[self.style][outline_width])
            else:
                raise GraphicsError("\n\nGraphicsError: The line width must be either a Colour or a string referencing "
                                    "a style, not {outline_width}")
        else:
            self._reconfig("width", STYLES[self.style]["line width"])

    # -------------------------------------------------------------------------
    # OTHER FUNCTIONS

    def is_clicked(self, mouse_pos):
        return False
