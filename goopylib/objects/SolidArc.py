from goopylib.Point import Point
from goopylib.objects.GraphicsObject import GraphicsObject

import math

class SolidArc(GraphicsObject):
    def __init__(self, p, start_angle, end_angle, radius, radius2=None, style=None, outline=None, outline_width=None,
                 cursor="arrow", arrow=None, resolution=10, smooth=True, layer=0, tag=None):

        self.start_angle = start_angle
        self.end_angle = end_angle

        self.anchor = p

        self.radius1 = radius
        if radius2 is None:
            self.radius2 = radius
        else:
            self.radius2 = radius2

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

        GraphicsObject.__init__(self, style=style, options=["outline", "width", "fill"], tag=tag)

    def _draw(self, canvas, options):
        return canvas.create_polygon(self.points, options)
