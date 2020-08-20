from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *

from goopylib.math.Triangulation import TriangulateEarClipping
from math import radians, sin, cos

class Polygon(GraphicsObject):
    def __init__(self, *points, style=None, fill=None, outline=None, outline_width=None, is_rounded=False, roundness=5,
                 layer=0, tag=None):

        # if points passed as a list, extract it
        if len(points) == 1 and isinstance(points[0], list):
            points = points[0]
        self.points = points
        if len(self.points) < 3:
            raise GraphicsError(f"\n\nGraphicsError: there must be at least 3 points for the polygon")

        self.is_rounded = is_rounded
        self.sharpness = roundness

        self.low_x, self.low_y = None, None  # These variables are all defined in the get_size() function called below
        self.high_x, self.high_y = None, None  # They store the extreme x & y points farthest from the line's anchor
        self.width, self.height = None, None

        self.calculate_dimensions()

        GraphicsObject.__init__(self, options=("fill", "outline", "width"), layer=layer, tag=tag)

        if isinstance(fill, Colour):
            self.fill = fill
        elif fill in STYLES[self.style].keys():
            self.fill = STYLES[self.style][fill]
        else:
            if "fill" in STYLES[self.style].keys():
                self.fill = STYLES[self.style]["fill"]
            else:
                self.fill = STYLES["default"]["fill"]
        self.set_fill(self.fill)

        if isinstance(outline, Colour):
            self.outline = outline
        elif outline in STYLES[self.style].keys():
            self.outline = STYLES[self.style][outline]
        else:
            if "outline" in STYLES[self.style].keys():
                self.outline = STYLES[self.style]["outline"]
            else:
                self.outline = STYLES["default"]["outlien"]
        self.set_outline(self.outline)

        if isinstance(outline_width, int):
            self.outline_width = outline_width
        elif outline_width in STYLES[self.style].keys():
            self.outline_width = STYLES[self.style][outline_width]
        else:
            if "width" in STYLES[self.style].keys():
                self.outline_width = STYLES[self.style]["width"]
            else:
                self.outline_width = STYLES["default"]["width"]
        self.set_outline_width(self.outline_width)

        self.triangles = None
        self.triangulate()

    def __repr__(self):
        return f"Polygon({self.points})"

    def _draw(self, canvas, options):
        points = []
        for p in self.points:
            x, y = canvas.to_screen(p.x, p.y)
            points.append(x)
            points.append(y)

        if options["width"] == 0:
            options["outline"] = options["fill"]
        return canvas.create_polygon(points, options, smooth=self.is_rounded)

    def _move(self, dx, dy):
        for p in self.points:
            p.move(dx, dy)

    def _rotate(self, dr, sampling="bicubic", center=None):
        if center is None:
            center = self.get_anchor()

        self.move(-center.x, -center.y)

        points = []
        for p in self.points:
            points.append(Point(cos(radians(dr)) * p.x - sin(radians(dr)) * p.y + center.x,
                                sin(radians(dr)) * p.x + cos(radians(dr)) * p.y + center.y))
        self.points = points

    def clone(self):
        other = Polygon(*self.points)
        other.config = self.config.copy()
        return other

    def flip_x(self):
        return self

    def get_points(self):
        return list(map(Point.clone, self.points))

    def calculate_dimensions(self):
        # To calculate the width, it finds the smallest & largest x points and gets the width
        self.low_x = self.points[0].x  # Setting the High & Low point to the first point
        self.high_x = self.low_x

        for point in self.points[1:]:  # Going through all the other points
            if point.x < self.low_x:  # Checking if this point is smaller
                self.low_x = point.x
            elif point.x > self.high_x:  # Checking if this point is larger
                self.high_x = point.x
        self.width = abs(self.high_x - self.low_x)  # Getting the width

        # To calculate the height, it finds the smallest & largest y points and gets the height
        self.low_y = self.points[0].y  # Setting the High & Low point to the first point
        self.high_y = self.low_y

        for point in self.points[1:]:  # Going through all the other points
            if point.y < self.low_y:  # Checking if this point is smaller
                self.low_y = point.y
            elif point.y > self.high_y:  # Checking if this point is larger
                self.high_y = point.y
        self.height = abs(self.high_y - self.low_y)  # Getting the height

    def get_width(self):
        return self.width

    def get_height(self):
        return self.height

    def is_clicked(self, pos):
        if pos is None:
            return False
        else:
            if self.bounds is None:
                width = self.get_width() / 2
                height = self.get_height() / 2
    
                # Check if point in Rectangular Bounding Box
                if self.anchor.x - width < pos.x < self.anchor.x + width and \
                   self.anchor.y - height < pos.y < self.anchor.y + height:
    
                    """
                    # Ray Casting Algorithm
                    # Code Modified from
                    # https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
                    intersections = 0
                    size = len(self.points)
    
                    v2p1 = (self.anchor.x - width - 1, pos.y)
                    for side in range(size):
                        v1p1 = self.points[side]
                        v1p2 = self.points[(side + 1) % size]
    
                        a1 = v1p2.y - v1p1.y
                        b1 = v1p1.x - v1p2.x
                        c1 = (v1p2.x * v1p1.y) - (v1p1.x * v1p2.y)
    
                        d1 = (a1 * pos.x) + (b1 * pos.y) + c1
                        d2 = (a1 * v2p1[0]) + (b1 * v2p1[1]) + c1
                        if d1 == 0 and d2 == 0:
                            a2 = v2p1[1] - pos.y
                            b2 = pos.x - v2p1[0]
                            c2 = (v2p1[0] * pos.y) - (pos.x * v2p1[1])
    
                            d1 = (a2 * v1p1.x) + (b2 * v1p1.y) + c2
                            d2 = (a2 * v1p2.x) + (b2 * v1p2.y) + c2
    
                            if d1 == 0 and d2 == 0:
                                intersections += 1
    
                    return intersections % 1 == 1
                    """
                    if len(self.points) == 3:
                        p1, p2, p3 = self.points
                        d1 = (pos.x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (pos.y - p2.y)
                        d2 = (pos.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (pos.y - p3.y)
                        d3 = (pos.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (pos.y - p1.y)

                        return not ((d1 < 0 or d2 < 0 or d3 < 0) and (d1 > 0 or d2 > 0 or d3 > 0))
                    else:
                        for triangle in self.triangles:
                            if triangle.is_clicked(pos):
                                return True
                else:
                    return False
            else:
                return self.bounds.is_clicked(pos)

    def get_anchor(self):
        x = 0
        y = 0
        for point in self.points:
            x += point.x
            y += point.y

        x /= len(self.points)
        y /= len(self.points)

        return Point(x, y)

    def triangulate(self):
        if self.triangles is None and len(self.points) != 3:
            self.triangles = []
            for triangle in TriangulateEarClipping(list(self.points)):
                self.triangles.append(Polygon(*triangle))
