from goopylib.objects.Line import Line
from goopylib.math.Interpolations import *
from goopylib.constants import CURVE_INTERPOLATIONS

# The Curved Line class is used for drawing curved lines segments between 2 or more points
# The Curved line class is really just a line split into multiple segments and smoothed to give the illusion of a curve

class CurvedLine(Line):

    def __init__(self, *p, style=None, outline=None, outline_width=None, arrow=None, capstyle=None, joinstyle=None,
                 cursor="arrow", arrow_shape=None, arrow_scale=0.5, dash=None, interpolation="cosine", resolution=5,
                 smooth=True, bounds_width=None, layer=0, tag=None,
                 bias=0, tension=1):  # These last two are only required for hermite interpolation

        if not isinstance(resolution, int):
            raise GraphicsError(f"\n\nGraphicsError: The Resolution for the curved line must be an integer, "
                                f"not {resolution}")
        if resolution < 0:
            raise GraphicsError(f"\n\nGraphicsError: The Resolution for the curved line must be a non-negative integer, "
                                f"not {resolution}")
        if interpolation not in CURVE_INTERPOLATIONS:
            raise GraphicsError("\n\nGraphicsError: The Interpolation for the curved line must be one of "
                                f"{CURVE_INTERPOLATIONS}, not {interpolation}")

        if not (isinstance(bias, float) or isinstance(bias, int)):
            raise GraphicsError(f"\n\nGraphicsError: The bias for the curved line must be an integer or float, "
                                f"not {bias}")
        if not (isinstance(tension, float) or isinstance(tension, int)):
            raise GraphicsError(f"\n\nGraphicsError: The tension for the curved line must be an integer or float, "
                                f"not {tension}")

        self.is_smooth = smooth
        if interpolation == "linear":
            self.is_smooth = False

        self.points = list(p)
        self.points_copy = self.points.copy()

        if interpolation in ["cosine", "linear"]:
            for point in range(len(p) - 1):
                for t in range(1, resolution + 1):
                    tn = t / (resolution + 1)
                    x = self.points[point].x + tn * (self.points[point + 1].x - self.points[point].x)

                    if interpolation == "cosine":
                        new_point = Point(x, CosineInterpolation(self.points[point], self.points[point + 1], tn))
                    else:
                        new_point = Point(x, LinearInterpolation(self.points[point], self.points[point + 1], tn))

                    self.points_copy.insert((point * (resolution + 1)) + t, new_point)

        elif interpolation in ["hermite", "cubic"]:
            self.points.insert(0, self.points[0])
            self.points.insert(-1, self.points[-1])
            self.points_copy = self.points.copy()

            for point in range(1, len(self.points) - 2):
                for t in range(1, resolution + 1):
                    tn = t / (resolution + 1)
                    x = self.points[point].x + tn * (self.points[point + 1].x - self.points[point].x)

                    if interpolation == "cubic":
                        new_point = Point(x, CubicInterpolation(self.points[point - 1], self.points[point],
                                                                self.points[point + 1], self.points[point + 2], tn))
                    else:
                        new_point = Point(x, HermiteInterpolation(self.points[point - 1], self.points[point],
                                                                  self.points[point + 1], self.points[point + 2], tn,
                                                                  tension, bias))

                    self.points_copy.insert((point * (resolution + 1)) + t - resolution, new_point)

            self.points_copy = self.points_copy[1:-1]

        Line.__init__(self, *self.points_copy, style=style, outline=outline, outline_width=outline_width, arrow=arrow,
                      capstyle=capstyle, joinstyle=joinstyle, cursor=cursor, arrow_shape=arrow_shape, tag=tag,
                      arrow_scale=arrow_scale, dash=dash, bounds_width=bounds_width, layer=layer)

    def __repr__(self):
        return f"Curved Line({self.points})"

    def __dir__(self):
        return "see https://github.com/BhavyeMathur/goopylib/wiki/Lines-&-Curved-Lines!"

    def _draw(self, canvas, options):
        # Converting all the coordinates to Window coordinates to account for stretching, changed coords, etc.
        points = [canvas.to_screen(point.x, point.y) for point in self.points]

        return canvas.create_line(points, options, smooth=self.is_smooth)  # Creating the line!
