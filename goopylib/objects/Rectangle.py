import goopylib.objects._BBox as gpBBox
from goopylib.Point import Point
from goopylib._internal_classes import VectorEquation


class Rectangle(gpBBox.BBox):

    def __init__(self, p1, p2, bounds=None, style=None, fill=None, outline=None, outline_width=None, layer=0,
                 cursor="arrow", is_rounded=False, roundness=5, tag=None):
        gpBBox.BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, outline_width=outline_width,
                             style=style, cursor=cursor, layer=layer, tag=tag)

        self.points = [self.p1.x, self.p1.y, self.p1.x, self.p2.y, self.p2.x, self.p2.y, self.p2.x, self.p1.y]
        self.is_rounded = is_rounded
        self.sharpness = roundness  # Usually values between 2 & 10 work well.

    def __repr__(self):
        return "Rectangle({}, {})".format(str(self.p1), str(self.p2))

    def _set_resizable(self, resizables, thickness=10, show_bounds=False):
        self.resizing_bounds = {}
        if resizables[0]:
            self.resizing_bounds["top"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                    Point(self.p2.x + thickness / 2, self.p1.y + thickness / 2),
                                                    cursor="vertical-resizing-arrow")
        if resizables[1]:
            self.resizing_bounds["bottom"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y - thickness / 2),
                                                       Point(self.p1.x - thickness / 2, self.p2.y + thickness / 2),
                                                       cursor="vertical-resizing-arrow")
        if resizables[2]:
            self.resizing_bounds["left"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                     Point(self.p1.x + thickness / 2, self.p2.y + thickness / 2),
                                                     cursor="horizontal-resizing-arrow")
        if resizables[3]:
            self.resizing_bounds["right"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y + thickness / 2),
                                                      Point(self.p2.x - thickness / 2, self.p1.y - thickness / 2),
                                                      cursor="horizontal-resizing-arrow")

        for obj in self.resizing_bounds.values():
            obj.graphwin = self.graphwin
            if show_bounds:
                obj.draw(self.graphwin)

    def _draw(self, canvas, options):
        points = [self.p1.x, self.p1.y, self.p1.x, self.p2.y, self.p2.x, self.p2.y, self.p2.x, self.p1.y]
        for point in range(len(self.points[::2])):
            points[point * 2], points[point * 2 + 1] = canvas.to_screen(points[point * 2], points[point * 2 + 1])

        # Code modified from Francisco Gomes, https://stackoverflow.com/users/9139005/francisco-gomes

        # The sharpness here is just how close the sub-points
        # are going to be to the vertex. The more the sharpness,
        # the more the sub-points will be closer to the vertex.
        # (This is not normalized)

        x = points[::2]
        y = points[1::2]

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

        for obj in self.resizing_bounds.values():
            obj.graphwin = self.graphwin

        # return canvas.create_rectangle(self.p1.x, self.p1.y, self.p2.x, self.p2.y, options)

        # This is done due to an internal bug in Tkinter where it does not set the width of the polygon..

        if options["width"] == 0:
            options["outline"] = options["fill"]

        return canvas.create_polygon(points, options, smooth=self.is_rounded)

    def clone(self):
        other = Rectangle(self.p1, self.p2)
        other.config = self.config.copy()
        return other

    def is_clicked(self, pos):
        if pos is None:
            return False
        if self.bounds is None:
            width = self.width // 2
            height = self.height // 2
            return self.anchor.x - width < pos.x < self.anchor.x + width and \
                   self.anchor.y - height < pos.y < self.anchor.y + height
        else:
            return self.bounds.is_clicked(pos)
