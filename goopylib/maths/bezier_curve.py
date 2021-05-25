import goopylib.maths.c_bezier_curve


def combination(n, k):
    return goopylib.maths.c_bezier_curve.combination(n, k)


def bernstein_polynomial(i, n, t):
    return goopylib.maths.c_bezier_curve.bernstein_polynomial(i, n, t)


def bezier_curve(t, control_points):
    return goopylib.maths.c_bezier_curve.bezier_curve(t, control_points)


def rational_bezier_curve(t, control_points, weights):
    return goopylib.maths.c_bezier_curve.rational_bezier_curve(t, control_points, weights)
