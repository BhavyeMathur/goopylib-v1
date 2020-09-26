import goopylib.math.CBezierCurve
from goopylib.util import GraphicsError

def factorial(n):
    return goopylib.math.CBezierCurve.factorial(n)

def combination(n, k):
    return goopylib.math.CBezierCurve.combination(n, k)

def bernstein_polynomial(i, n, t):
    return goopylib.math.CBezierCurve.bernstein_polynomial(i, n, t)

def bezier_curve(t, control_points):
    return goopylib.math.CBezierCurve.bezier_curve(t, control_points)

def rational_bezier_curve(t, control_points, weights):

    if not isinstance(control_points, list):
        raise GraphicsError("\n\nGraphicsError: control_points argument for rational bezier curve must be a list,"
                            f" not {control_points}")
    if not isinstance(weights, list):
        raise GraphicsError(f"\n\nGraphicsError: weights argument for rational bezier curve must be a list, "
                            f"not {weights}")

    if not (isinstance(t, float) or isinstance(t, int)):
        raise GraphicsError("\n\nGraphicsError: t parameter for rational bezier curve must be a float or int, "
                            f"not {t}")

    size = len(control_points)
    if not size == len(weights):
        raise GraphicsError(f"\n\nGraphicsError: the length of weights must match the length of control_points")

    for i in range(size):
        if not isinstance(control_points[i], list):
            raise GraphicsError(f"\n\nGraphicsError: each element of control_points must be a list in the form [x, y], "
                                f"not {control_points[i]} at index {i}")

        if not isinstance(control_points[i][0], int):
            raise GraphicsError(f"\n\nGraphicsError: x element of control_points at index {i} must be an integer, "
                                f"not {control_points[i]}")

        if not isinstance(control_points[i][1], int):
            raise GraphicsError(f"\n\nGraphicsError: y element of control_points at index {i} must be an integer, "
                                f"not {control_points[i]}")

        if not (isinstance(weights[i], float) or isinstance(weights[i], int)):
            raise GraphicsError(f"\n\nGraphicsError: each element of weights must be integers of floats, "
                                f"not {weights[i]} at index {i}")

    return goopylib.math.CBezierCurve.rational_bezier_curve(t, control_points, weights)
