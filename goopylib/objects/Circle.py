from goopylib.objects.Oval import Oval
from goopylib.Point import Point
from goopylib._internal_classes import VectorEquation

class Circle(Oval):

    def __init__(self, center, radius, bounds=None, style=None, fill=None, outline=None, layer=0,
                 outline_width=None, cursor="arrow"):
        p1 = Point(center.x - radius, center.y - radius)
        p2 = Point(center.x + radius, center.y + radius)

        self.center = center

        self.radius = radius
        Oval.__init__(self, center, radius, radius, bounds=bounds, fill=fill, outline=outline, style=style,
                      cursor=cursor, outline_width=outline_width, layer=layer)

        self.equation = VectorEquation("(x-{})**2 + (y-{})**2 < {}**2".format(self.center.x, self.center.y, radius))

    def __repr__(self):
        return f"Circle({self.anchor}, {self.radius})"

    def clone(self):
        other = Circle(self.get_anchor(), self.radius)
        other.config = self.config.copy()
        return other

    def get_radius(self):
        return self.radius

    def _update(self):
        self.equation = VectorEquation("(x-{})**2 + (y-{})**2 < {}**2".format(self.anchor.x, self.anchor.y,                                                                              self.radius))
