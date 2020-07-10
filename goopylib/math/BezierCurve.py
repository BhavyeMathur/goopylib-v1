from goopylib.Point import Point
import math
import numpy as np

BezierMatrices = [np.array([[-1, 1], [1, 0]]), np.array([[1, -2, 1], [-2, 2, 0], [1, 0, 0]]),
                  np.array([[-1, 3, -3, 1], [3, -6, 3, 0], [-3, 3, 0, 0], [1, 0, 0, 0]]),
                  np.array([[1, -4, 6, -4, 1], [-4, 12, -12, 4, 0], [6, -12, 6, 0, 0], [-4, 4, 0, 0, 0], [1, 0, 0, 0, 0]])]

# References for this: https://www.youtube.com/watch?v=qhQrRCJ-mVg

def BezierCurve(t, control_points):
    if len(control_points) - 1 > len(BezierMatrices):
        return RawBezierCurve(t, control_points)
    else:
        x_matrix = np.array([point.x for point in control_points])
        y_matrix = np.array([point.y for point in control_points])

        t_matrix = np.array([t ** (len(control_points) - n - 1) for n in range(len(control_points))])
        M = BezierMatrices[len(control_points) - 2]

        return Point(x_matrix.dot(M).dot(t_matrix), y_matrix.dot(M).dot(t_matrix))

def RawBezierCurve(t, control_points):
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
