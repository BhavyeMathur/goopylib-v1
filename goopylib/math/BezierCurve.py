from goopylib.Point import Point
import math

# References for this: https://www.youtube.com/watch?v=qhQrRCJ-mVg
def BezierCurve(t, control_points):
    sum_x, sum_y = 0, 0

    for i in range(0, len(control_points)):
        sum_y += BernsteinPolynomial(i, len(control_points) - 1, t) * control_points[i].y
        sum_x += BernsteinPolynomial(i, len(control_points) - 1, t) * control_points[i].x

    return Point(sum_x, sum_y)


def RationalBezierCurve(t, weights, control_points):
    sum_x_numerator, sum_y_numerator = 0, 0
    sum_x, sum_y = 0, 0

    for i in range(0, len(control_points)):
        sum_x_numerator += (BernsteinPolynomial(i, len(control_points) - 1, t) * control_points[i].x * weights[i])
        sum_x += BernsteinPolynomial(i, len(control_points) - 1, t) * weights[i]

        sum_y_numerator += (BernsteinPolynomial(i, len(control_points) - 1, t) * control_points[i].y * weights[i])
        sum_y += BernsteinPolynomial(i, len(control_points) - 1, t) * weights[i]

    return Point(sum_x_numerator / sum_x, sum_y_numerator / sum_y)


def BernsteinPolynomial(i, n, t):
    return Combination(n, i) * (t ** i) * ((1 - t) ** (n - i))


def Combination(n, k):
    return math.factorial(n) / (math.factorial(k) * math.factorial(n - k))
