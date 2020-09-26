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
    if isinstance(t, (float, int)):
        return goopylib.math.CBezierCurve.rational_bezier_curve(t, control_points, weights)
    else:
        raise GraphicsError("\n\nGraphicsError: t parameter for rational bezier curve must be a float or int, "
                            f"not {t}")
