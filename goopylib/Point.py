from goopylib.util import GraphicsError
import math

class Point:
    def __init__(self, x, y):

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("\n\nx (x={}) & y (y={}) positions must be integers".format(x, y))

        self.x = float(x)
        self.y = float(y)

    def __repr__(self):
        return "Point({}, {})".format(self.x, self.y)

    def __mul__(self, other):
        try:
            return Point(self.x * other.x, self.y * other.y)
        except AttributeError:
            return Point(self.x * other, self.y * other)

    def __add__(self, other):
        try:
            return Point(self.x + other.x, self.y + other.y)
        except AttributeError:
            return Point(self.x + other, self.y + other)

    def __sub__(self, other):
        return self + -other

    def _move(self, dx, dy):
        self.x = self.x + dx
        self.y = self.y + dy

    def distance(self, p2):

        if not isinstance(p2, Point):
            raise GraphicsError("\n\np2 argument for distance calculation must be a Point class")
        return math.sqrt((p2.x - self.x) ** 2 + (p2.y - self.y) ** 2)

    def distance_x(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError("\n\np2 argument for distance calculation must be a Point class")
        return p2.x - self.x

    def distance_y(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError("\n\np2 argument for distance calculation must be a Point class")
        return p2.y - self.y

    def clone(self):
        return Point(self.x, self.y)

    def swap(self):
        t = self.y
        self.y = self.x
        self.x = t

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def move_y(self, dy):
        self.y += dy
        return self

    def move_x(self, dx):
        self.x += dx
        return self

    def move(self, dx, dy):
        self.y += dy
        self.x += dx
        return self

    def move_to(self, x, y):
        self.x = x
        self.y = y
        return self

    def add(self, dx, dy):
        return self.clone().move(dx, dy)

    def set(self, x, y):
        return self.clone().move_to(x, y)

    def move_to_x(self, x):
        self.x = x
        return self

    def move_to_y(self, y):
        self.y = y
        return self

    def get_anchor(self):
        return self

    def add_y(self, dy):
        return self.clone().move_y(dy)

    def add_x(self, dx):
        return self.clone().move_x(dx)

    def set_x(self, x):
        return self.clone().move_to_x(x)

    def set_y(self, y):
        return self.clone().move_to_y(y)
