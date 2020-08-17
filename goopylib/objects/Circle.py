from goopylib.objects.Oval import Oval
from goopylib.Point import Point

class Circle(Oval):

    def __init__(self, center, radius, bounds=None, style=None, fill=None, outline=None, layer=0, tag=None,
                 outline_width=None, cursor="arrow"):
        p1 = Point(center.x - radius, center.y - radius)
        p2 = Point(center.x + radius, center.y + radius)

        self.center = center

        self.radius = radius
        Oval.__init__(self, center, radius, radius, bounds=bounds, fill=fill, outline=outline, style=style,
                      cursor=cursor, outline_width=outline_width, layer=layer, tag=tag)

    def __repr__(self):
        return f"Circle({self.anchor}, {self.radius})"

    def clone(self):
        other = Circle(self.get_anchor(), self.radius)
        other.config = self.config.copy()
        return other

    def get_radius(self):
        return self.radius

    def is_clicked(self, mouse_pos):
        if mouse_pos is None:
            return False
        if self.bounds is None:
            return ((self.anchor.x - mouse_pos.x) ** 2 + (self.anchor.y - mouse_pos.y) ** 2) ** 0.5 < self.radius
        else:
            return self.bounds.is_clicked(mouse_pos)
