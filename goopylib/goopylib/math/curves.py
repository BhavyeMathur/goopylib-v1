from goopylib.util import GraphicsError
import math

def distance_formula(p1, p2):
    return ((p2[0] - p1[0]) ** 2 + (p2[1] - p1[1]) ** 2) ** 0.5

def linear_curve(t, control_points):
    number_of_points = len(control_points)
    if number_of_points > 1:
        total_distance = sum(distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

        points_interval = 1 / (number_of_points - 1)
        next_point = math.ceil(t / points_interval)

        mu = (t - (points_interval * (next_point - 1))) / points_interval
        mu2 = 1 - mu

        previous_point = control_points[next_point - 1]
        next_point = control_points[next_point]

        return [mu2 * previous_point[0] + mu * next_point[0], mu2 * previous_point[1] + mu * next_point[1]]
    else:
        raise GraphicsError(f"\n\nGraphicsError: must be minimum of 2 control points, not {len(control_points)}")

def cosine_curve(t, control_points):
    number_of_points = len(control_points)
    if number_of_points > 1:
        total_distance = sum(
            distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

        points_interval = 1 / (number_of_points - 1)
        next_point = math.ceil(t / points_interval)

        mu = (t - (points_interval * (next_point - 1))) / points_interval

        previous_point = control_points[next_point - 1]
        next_point = control_points[next_point]

        mu2 = (1 - math.cos(mu * math.pi)) / 2

        return [(1 - mu) * previous_point[0] + mu * next_point[0], (1 - mu2) * previous_point[1] + mu2 * next_point[1]]
    else:
        raise GraphicsError(f"\n\nGraphicsError: must be minimum of 2 control points, not {len(control_points)}")
    
def cubic_curve(t, control_points):
    number_of_points = len(control_points)
    if number_of_points > 1:
        total_distance = sum(
            distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

        points_interval = 1 / (number_of_points - 1)
        next_point = math.ceil(t / points_interval)

        mu = (t - (points_interval * (next_point - 1))) / points_interval

        previous_point = control_points[next_point - 1]
        previous_previous_point = control_points[next_point - 2]
        next_next_point = control_points[(next_point + 1) % number_of_points]
        next_point = control_points[next_point]

        a0 = next_next_point[1] - next_point[1] - previous_previous_point[1] + previous_point[1]
        a1 = previous_previous_point[1] - previous_point[1] - a0
        a2 = next_point[1] - previous_previous_point[1]
        a3 = previous_point[1]

        return [(1 - mu) * previous_point[0] + mu * next_point[0], (a0 * mu ** 3) + (a1 * mu ** 2) + (a2 * mu) + a3]
    else:
        raise GraphicsError(f"\n\nGraphicsError: must be minimum of 2 control points, not {len(control_points)}")

def hermite_curve(t, control_points, tension, bias):
    number_of_points = len(control_points)
    if number_of_points > 1:
        total_distance = sum(
            distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

        points_interval = 1 / (number_of_points - 1)
        next_point = math.ceil(t / points_interval)

        mu = (t - (points_interval * (next_point - 1))) / points_interval

        previous_point = control_points[next_point - 1]
        previous_previous_point = control_points[next_point - 2]
        next_next_point = control_points[(next_point + 1) % number_of_points]
        next_point = control_points[next_point]

        mu2 = mu ** 2
        mu3 = mu ** 3

        m0 = (previous_point[1] - previous_previous_point[1]) * (1 + bias) * (1 - tension) / 2
        m0 += (next_point[1] - previous_point[1]) * (1 - bias) * (1 - tension) / 2
        m1 = (next_point[1] - previous_point[1]) * (1 + bias) * (1 - tension) / 2
        m1 += (next_next_point[1] - next_point[1]) * (1 - bias) * (1 - tension) / 2

        a0 = 2 * mu3 - 3 * mu2 + 1
        a1 = mu3 - 2 * mu2 + mu
        a2 = mu3 - mu2
        a3 = -2 * mu3 + 3 * mu2

        return [(1 - mu) * previous_point[0] + mu * next_point[0], a0 * previous_point[1] + a1 * m0 + a2 * m1 + a3 * next_point[1]]
    else:
        raise GraphicsError(f"\n\nGraphicsError: must be minimum of 2 control points, not {len(control_points)}")
