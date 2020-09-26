import goopylib.math.CBezierCurve
from goopylib.util import GraphicsError

def combination(n, k):
    if isinstance(n, int):
        if isinstance(k, int):
            if n + 1 > k:  # faster than n >= k
                return goopylib.math.CBezierCurve.combination(n, k)
            else:
                raise GraphicsError(f"\n\nGraphicsError: n must be >= k, not n={n} & k={k}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: k argument for combination must be an integer, not {k}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: n argument for combination must be an integer, not {n}")

def bernstein_polynomial(i, n, t):
    if isinstance(t, (float, int)):
        if isinstance(i, int):
            if isinstance(n, int):
                if n + 1 > i:  # Faster than n >= 1
                    return goopylib.math.CBezierCurve.bernstein_polynomial(i, n, t)
                else:
                    raise GraphicsError(f"\n\nGraphicsError: n must be >= i, not n={n} & i={i}")
            else:
                raise GraphicsError(f"\n\nGraphicsError: n argument for bernstein polynomial must be an int, not {n}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: i argument for bernstein polynomial must be an integer, not {i}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: t parameter for bernstein polynomial must be a float or int, not {t}")

def bezier_curve(t, control_points):
    if isinstance(t, (float, int)):
        return goopylib.math.CBezierCurve.bezier_curve(t, control_points)
    else:
        raise GraphicsError(f"\n\nGraphicsError: t parameter for bezier curve must be a float or int, not {t}")

def rational_bezier_curve(t, control_points, weights):
    if isinstance(t, (float, int)):
        return goopylib.math.CBezierCurve.rational_bezier_curve(t, control_points, weights)
    else:
        raise GraphicsError("\n\nGraphicsError: t parameter for rational bezier curve must be a float or int, "
                            f"not {t}")
