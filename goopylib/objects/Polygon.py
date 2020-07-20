from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point

class Polygon(GraphicsObject):

    def __init__(self, *points, style=None, fill=None, outline=None, width=None, is_rounded=False, roundness=5,
                 layer=0):

        # if points passed as a list, extract it
        if len(points) == 1 and isinstance(points[0], list):
            points = points[0]
            points = points[0]
        self.points = points
        self.is_rounded = is_rounded

        self.sharpness = roundness
        self.set_fill(fill)

        GraphicsObject.__init__(self, options=("fill", "outline", "width"), layer=layer)

    def __repr__(self):
        return "Polygon" + str(tuple(p for p in self.points))

    def _draw(self, canvas, options):
        points = []
        for p in self.points:
            x, y = canvas.to_screen(p.x, p.y)
            points.append(x)
            points.append(y)

        # Code modified from Francisco Gomes, https://stackoverflow.com/users/9139005/francisco-gomes

        # The sharpness here is just how close the sub-points
        # are going to be to the vertex. The more the sharpness,
        # the more the sub-points will be closer to the vertex.
        # (This is not normalized)
        x = points[::2]
        y = points[1::2]

        # Rounding code from Francisco Gomes,
        # https://stackoverflow.com/questions/44099594/how-to-make-a-tkinter-canvas-rectangle-with-rounded-corners
        if self.is_rounded:
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

        if options["width"] == 0:
            options["font_colour"] = options["fill"]

        return canvas.create_polygon(points, options, smooth=self.is_rounded)

    def clone(self):
        other = Polygon(*self.points)
        other.config = self.config.copy()
        return other

    def get_points(self):
        return list(map(Point.clone, self.points))

    def is_clicked(self, mouse_pos):
        return False

    def _move(self, dx, dy):
        for p in self.points:
            p.move(dx, dy)

    def get_anchor(self):
        x = 0
        y = 0
        for point in self.points:
            x += point.x
            y += point.y

        x /= len(self.points)
        y /= len(self.points)

        return Point(x, y)
