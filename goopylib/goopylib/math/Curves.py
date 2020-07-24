from goopylib.Point import Point
from goopylib.util import GraphicsError
import math

def LinearCurve(t, control_points):
    if not len(control_points) > 2:
        raise GraphicsError("Length of Control Points must be greater than 2")

    total_distance = control_points[-1].x - control_points[0].x
    time_x = t * total_distance + control_points[0].x

    for i, point in enumerate(control_points):
        if time_x < point.x:
            lower_point = i - 1
            break

    upper_point = lower_point + 1
    points_distance = control_points[lower_point].distance_x(control_points[upper_point])

    x = (1 - t) * control_points[lower_point].x + t * control_points[upper_point].x
    proportion_done = (time_x - control_points[lower_point].x) / points_distance

    return Point(x, (1 - proportion_done) * control_points[lower_point].y + proportion_done * control_points[upper_point].y)

def CosineCurve(t, control_points):
    if not len(control_points) > 2:
        raise GraphicsError("Length of Control Points must be greater than 2")

    total_distance = control_points[-1].x - control_points[0].x
    time_x = t * total_distance + control_points[0].x

    for i, point in enumerate(control_points):
        if time_x < point.x:
            lower_point = i - 1
            break

    upper_point = lower_point + 1
    points_distance = control_points[lower_point].distance_x(control_points[upper_point])

    x = (1 - t) * control_points[lower_point].x + t * control_points[upper_point].x
    proportion_done = (time_x - control_points[lower_point].x) / points_distance

    ft = t * math.pi
    f = (1 - math.cos(ft)) / 2

    return Point(x, lower_point*(1-f) + upper_point*f)
