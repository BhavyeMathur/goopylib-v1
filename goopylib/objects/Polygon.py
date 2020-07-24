from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point

from goopylib.styles import *

from goopylib.math.Triangulation import TriangulateEarClipping, CheckInTriangle
from math import radians, sin, cos

class Polygon(GraphicsObject):

    def __init__(self, *points, style=None, fill=None, outline=None, outline_width=None, is_rounded=False, roundness=5,
                 layer=0):

        # if points passed as a list, extract it
        if len(points) == 1 and isinstance(points[0], list):
            points = points[0]
        self.points = points
        if len(self.points) < 3:
            raise GraphicsError(f"\n\nGraphicsError: there must be at least 3 points for the polygon")

        self.is_rounded = is_rounded
        self.sharpness = roundness

        GraphicsObject.__init__(self, options=("fill", "outline", "width"), layer=layer)

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

        if len(self.points) != 3:
            self.triangles = []
            for triangle in TriangulateEarClipping(self.points):
                self.triangles.append(Polygon(*triangle))

    def __repr__(self):
        return "Polygon" + str(tuple(p for p in self.points))

    def _draw(self, canvas, options):
        points = []
        for p in self.points:
            x, y = canvas.to_screen(p.x, p.y)
            points.append(x)
            points.append(y)

        # Rounding code from Francisco Gomes,
        # https://stackoverflow.com/questions/44099594/how-to-make-a-tkinter-canvas-rectangle-with-rounded-corners
        if self.is_rounded:
            # The sharpness here is just how close the sub-points
            # are going to be to the vertex. The more the sharpness,
            # the more the sub-points will be closer to the vertex.
            # (This is not normalized)
            x = points[::2]
            y = points[1::2]

            if self.sharpness < 2:
                self.sharpness = 2

            ratio_multiplier = self.sharpness - 1
            ratio_dividend = self.sharpness

            # Array to store the points
            points = []

            # Iterate over the x points
            for i in range(len(x)):
                # Set vertex
                points.append(x[i])
                points.append(y[i])

                # If it's not the last point
                if i != (len(x) - 1):
                    # Insert submultiples points. The higher the sharpness, the more these points will be
                    # closer to the vertex.
                    points.append((ratio_multiplier * x[i] + x[i + 1]) / ratio_dividend)
                    points.append((ratio_multiplier * y[i] + y[i + 1]) / ratio_dividend)
                    points.append((ratio_multiplier * x[i + 1] + x[i]) / ratio_dividend)
                    points.append((ratio_multiplier * y[i + 1] + y[i]) / ratio_dividend)
                else:
                    # Insert submultiples points.
                    points.append((ratio_multiplier * x[i] + x[0]) / ratio_dividend)
                    points.append((ratio_multiplier * y[i] + y[0]) / ratio_dividend)
                    points.append((ratio_multiplier * x[0] + x[i]) / ratio_dividend)
                    points.append((ratio_multiplier * y[0] + y[i]) / ratio_dividend)
                    # Close the polygon
                    points.append(x[0])
                    points.append(y[0])

        if self.rotation == 90:
            print(points)

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

    def is_clicked(self, mouse_pos):
        if len(self.points) == 3:
            return CheckInTriangle(*self.points, mouse_pos)
        else:
            for triangle in self.triangles:
                if triangle.is_clicked(mouse_pos):
                    return True
        return False

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
        pass
