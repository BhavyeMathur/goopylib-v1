from goopylib.objects.CurvedLine import CurvedLine
from goopylib.Point import Point
from goopylib.util import GraphicsError

import math

class Arc(CurvedLine):
    def __init__(self, p, start_angle, end_angle, radius, radius2=None, style=None, outline=None, outline_width=None,
                 cursor="arrow", arrow=None, resolution=10, smooth=True, bounds_width=10, layer=0, tag=None):

        if not isinstance(p, Point):
            raise GraphicsError(f"\n\nGraphicsError: Anchor Point (p) for Arc must be a Point Object, not {p}")
        
        if not (isinstance(start_angle, int) or isinstance(start_angle, float)):
            raise GraphicsError(f"\n\nGraphicsError: start_angle must be an integer or float, not {start_angle}")
        if not (isinstance(end_angle, int) or isinstance(end_angle, float)):
            raise GraphicsError(f"\n\nGraphicsError: end_angle must be an integer or float, not {end_angle}")
        
        if not (isinstance(radius, int) or isinstance(radius, float)):
            raise GraphicsError(f"\n\nGraphicsError: Arc radius must be an integer or float, not {radius}")
        if radius2 is not None:
            if not (isinstance(radius2, int) or isinstance(radius2, float)):
                raise GraphicsError(f"\n\nGraphicsError: Arc radius2 must be an integer or float, not {radius2}")
        
        self.start_angle = start_angle
        self.end_angle = end_angle

        self.anchor = p

        self.radius1 = radius
        if radius2 is None:
            self.radius2 = radius
        else:
            self.radius2 = radius

        angle_change = (end_angle - start_angle) / resolution

        range_end = 90 / angle_change
        decimal_points = min([len(str(range_end).split('.')[1]), 3])

        x_coeff = sum([abs(math.cos(math.radians(i * angle_change + start_angle)))
                       for i in range(int(range_end * 10 ** decimal_points))])
        y_coeff = sum([abs(math.sin(math.radians(i * angle_change + start_angle)))
                       for i in range(int(range_end * 10 ** decimal_points))])

        x_coeff /= 10 ** decimal_points
        y_coeff /= 10 ** decimal_points

        angle_change = (end_angle - start_angle) / resolution

        x_change = self.radius1 / 2 / x_coeff
        y_change = self.radius2 / 2 / y_coeff

        self.points = [p - Point(x_change/2, self.radius2 / 2)]

        for i in range(resolution):
            cur_angle = (i * angle_change) + start_angle
            self.points.append(self.points[-1] + Point(x_change * math.cos(math.radians(cur_angle)),
                                                       y_change * math.sin(math.radians(cur_angle))))

        CurvedLine.__init__(self, *self.points, style=style, outline=outline, outline_width=outline_width, arrow=arrow,
                            resolution=0, interpolation="spline", smooth=smooth, bounds_width=bounds_width, layer=layer,
                            tag=tag)
