from goopylib.objects.Oval import Oval
from goopylib.Point import Point

class Circle(Oval):

    def __init__(self, center, radius, bounds=None, fill=None, outline=None, layer=0, tag=None,
                 outline_width=None, cursor="arrow"):
        p1 = [center[0] - radius, center[1] - radius]
        p2 = [center[0] + radius, center[1] + radius]

        self.center = center

        self.radius = radius
        Oval.__init__(self, center, radius, radius, bounds=bounds, fill=fill, outline=outline,
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
            return ((self.anchor[0] - mouse_pos[0]) ** 2 + (self.anchor[1] - mouse_pos[1]) ** 2) ** 0.5 < self.radius
        else:
            return self.bounds.is_clicked(mouse_pos)
