from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *

from goopylib.maths.triangulation import triangulate_modified_earclip
from math import radians, sin, cos

from copy import deepcopy

class Polygon(GraphicsObject):
    def __init__(self, *points, style=None, fill=None, outline=None, outline_width=None, is_rounded=False, roundness=5,
                 layer=0, tag=None):

        self.points = deepcopy(list(points))
        if len(self.points) < 3:
            raise GraphicsError(f"\n\nGraphicsError: there must be at least 3 points for the polygon")

        self.is_rounded = is_rounded
        self.sharpness = roundness

        self.anchor = self.get_anchor()

        self.low_x, self.low_y = None, None  # These variables are all defined in the get_size() function called below
        self.high_x, self.high_y = None, None  # They store the extreme x & y points farthest from the line's anchor
        self.width, self.height = None, None

        self.calculate_dimensions()

        GraphicsObject.__init__(self, options=("fill", "outline", "width"), layer=layer, tag=tag)

        if fill is None:
            self.fill = STYLES["default"]["fill"]
        elif isinstance(fill, Colour):  # Checking if the option is a colour
            self.fill = fill
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The Rectangle fill must be a Colour object , not {fill}")

        if outline is None:
            self.outline = STYLES["default"]["outline"]
        elif isinstance(outline, Colour):  # Checking if the option is a colour
            self.outline = outline
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The rectangle outline must be a Colour object , not {outline}")

        if outline_width is None:
            self.outline_width = STYLES["default"]["width"]
        elif isinstance(outline_width, int):  # Checking if the option is an integer
            self.outline_width = outline_width
        else:  # If not, raise an error
            raise GraphicsError(
                f"\n\nGraphicsError: The rectangle outline width must be an integer, not {outline_width}")

        self.triangles = None

    def __repr__(self):
        return f"Polygon({self.points})"

    def _draw(self, canvas, options):
        points = []
        for p in self.points:
            x, y = canvas.to_screen(p[0], p[1])
            points.append(x)
            points.append(y)

        return canvas.create_polygon(points, options, fill=self.fill, width=self.outline_width, smooth=self.is_rounded,
                                     outline=self.fill if self.outline_width == 0 else self.outline)

    def _move(self, dx, dy):
        for p in self.points:
            p.move(dx, dy)

    def _rotate(self, dr, sampling="bicubic", center=None):
        if center is None:
            center = self.get_anchor()

        self.move(-center[0], -center[1])

        points = []
        for p in self.points:
            points.append(Point(cos(radians(dr)) * p[0] - sin(radians(dr)) * p[1] + center[0],
                                sin(radians(dr)) * p[0] + cos(radians(dr)) * p[1] + center[1]))
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
        self.low_x = self.points[0][0]  # Setting the High & Low point to the first point
        self.high_x = self.low_x

        for point in self.points[1:]:  # Going through all the other points
            if point[0] < self.low_x:  # Checking if this point is smaller
                self.low_x = point[0]
            elif point[0] > self.high_x:  # Checking if this point is larger
                self.high_x = point[0]
        self.width = abs(self.high_x - self.low_x)  # Getting the width

        # To calculate the height, it finds the smallest & largest y points and gets the height
        self.low_y = self.points[0][1]  # Setting the High & Low point to the first point
        self.high_y = self.low_y

        for point in self.points[1:]:  # Going through all the other points
            if point[1] < self.low_y:  # Checking if this point is smaller
                self.low_y = point[1]
            elif point[1] > self.high_y:  # Checking if this point is larger
                self.high_y = point[1]
        self.height = abs(self.high_y - self.low_y)  # Getting the height

    def get_width(self):
        return self.width

    def get_height(self):
        return self.height

    def get_fill(self):
        return self.fill

    def get_outline(self):
        return self.outline

    def get_outline_width(self):
        return self.outline_width

    def is_clicked(self, pos):
        if self.triangles is None:
            self.triangulate()

        if pos is None:
            return False
        else:
            if self.bounds is None:
                width = self.get_width() / 2
                height = self.get_height() / 2
    
                # Check if point in Rectangular Bounding Box
                if self.anchor[0] - width < pos[0] < self.anchor[0] + width and \
                   self.anchor[1] - height < pos[1] < self.anchor[1] + height:
    
                    """
                    # Ray Casting Algorithm
                    # Code Modified from
                    # https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
                    intersections = 0
                    size = len(self.points)
    
                    v2p1 = (self.anchor[0] - width - 1, pos[1])
                    for side in range(size):
                        v1p1 = self.points[side]
                        v1p2 = self.points[(side + 1) % size]
    
                        a1 = v1p2[1] - v1p1[1]
                        b1 = v1p1[0] - v1p2[0]
                        c1 = (v1p2[0] * v1p1[1]) - (v1p1[0] * v1p2[1])
    
                        d1 = (a1 * pos[0]) + (b1 * pos[1]) + c1
                        d2 = (a1 * v2p1[0]) + (b1 * v2p1[1]) + c1
                        if d1 == 0 and d2 == 0:
                            a2 = v2p1[1] - pos[1]
                            b2 = pos[0] - v2p1[0]
                            c2 = (v2p1[0] * pos[1]) - (pos[0] * v2p1[1])
    
                            d1 = (a2 * v1p1[0]) + (b2 * v1p1[1]) + c2
                            d2 = (a2 * v1p2[0]) + (b2 * v1p2[1]) + c2
    
                            if d1 == 0 and d2 == 0:
                                intersections += 1
    
                    return intersections % 1 == 1
                    """
                    if len(self.points) == 3:
                        p1, p2, p3 = self.points
                        d1 = (pos[0] - p2[0]) * (p1[1] - p2[1]) - (p1[0] - p2[0]) * (pos[1] - p2[1])
                        d2 = (pos[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (pos[1] - p3[1])
                        d3 = (pos[0] - p1[0]) * (p3[1] - p1[1]) - (p3[0] - p1[0]) * (pos[1] - p1[1])

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
            x += point[0]
            y += point[1]

        x /= len(self.points)
        y /= len(self.points)

        return [x, y]

    def triangulate(self):
        if self.triangles is None and len(self.points) != 3:
            self.triangles = []
            for triangle in triangulate_modified_earclip(list(self.points)):
                self.triangles.append(Polygon(*triangle))

    def set_fill(self, fill):
        if fill is None:
            self.fill = STYLES["default"]["fill"]
        elif isinstance(fill, Colour):  # Checking if the option is a colour
            self.fill = fill
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The Rectangle fill must be a Colour object , not {fill}")

        self._update_layer()
        return self

    def set_outline(self, outline):
        if outline is None:
            self.outline = STYLES["default"]["outline"]
        elif isinstance(outline, Colour):  # Checking if the option is a colour
            self.outline = outline
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The rectangle outline must be a Colour object , not {outline}")

        self._update_layer()
        return self

    def set_outline_width(self, outline_width):
        if outline_width is None:
            self.outline_width = STYLES["default"]["width"]
        elif isinstance(outline_width, int):  # Checking if the option is an integer
            self.outline_width = outline_width
        else:  # If not, raise an error
            raise GraphicsError(
                f"\n\nGraphicsError: The rectangle outline width must be an integer, not {outline_width}")

        self._update_layer()
        return self
