import math

# References for this: https://www.youtube.com/watch?v=qhQrRCJ-mVg

def py_bezier_curve(t, control_points):
    size = len(control_points)
    if size > 5:
        sum_x, sum_y = 0, 0

        size = len(control_points) - 1
        for i in range(0, size + 1):
            coeff = py_bernstein_polynomial(i, size, t)
            sum_y += coeff * control_points[i][1]
            sum_x += coeff * control_points[i][0]

        return sum_x, sum_y

    elif size == 2:
        return ((1 - t) * control_points[0][0]) + (t * control_points[1][0]), \
               ((1 - t) * control_points[0][1]) + (t * control_points[1][1])

    elif size == 3:
        t2 = t * t
        t *= 2

        return ((t2 - t + 1) * control_points[0][0]) + (((-2 * t2) + t) * control_points[1][0]) + \
               (t2 * control_points[2][0]), \
               ((t2 - t + 1) * control_points[0][1]) + (((-2 * t2) + t) * control_points[1][1]) + \
               (t2 * control_points[2][1])

    elif size == 4:
        t2 = t * t
        t3 = t2 * t

        t *= 3

        return ((-t3 + (3 * t2) - t + 1) * control_points[0][0]) + \
               (((3 * t3) - (6 * t2) + t) * control_points[1][0]) + \
               (((-3 * t3) + (3 * t2)) * control_points[2][0]) + \
               (t3 * control_points[3][0]), \
               ((-t3 + (3 * t2) - t + 1) * control_points[0][1]) + \
               (((3 * t3) - (6 * t2) + t) * control_points[1][1]) + \
               (((-3 * t3) + (3 * t2)) * control_points[2][1]) + (t3 * control_points[3][1])

    elif size == 5:
        t2 = t * t
        t3 = t2 * t
        t4 = t3 * t

        t *= 4

        return ((t4 - (4 * t3) + (6 * t2) - t + 1) * control_points[0][0]) + \
               (((-4 * t4) + (12 * t3) - (12 * t2) + t) * control_points[1][0]) + \
               (((6 * t4) - (12 * t3) + (6 * t2)) * control_points[2][0]) + \
               (((-4 * t4) + (4 * t3)) * control_points[3][0]) + \
               (t4 * control_points[4][0]), \
               ((t4 - (4 * t3) + (6 * t2) - t + 1) * control_points[0][1]) + \
               (((-4 * t4) + (12 * t3) - (12 * t2) + t) * control_points[1][1]) + \
               (((6 * t4) - (12 * t3) + (6 * t2)) * control_points[2][1]) + \
               (((-4 * t4) + (4 * t3)) * control_points[3][1]) + \
               (t4 * control_points[4][1])

    return 0, 0

def py_rational_bezier_curve(t, weights, control_points):
    sum_x_numerator, sum_y_numerator = 0, 0
    sum_x, sum_y = 0, 0

    for i in range(0, len(control_points)):
        sum_x_numerator += (py_bernstein_polynomial(i, len(control_points) - 1, t) * control_points[i][0] * weights[i])
        sum_x += py_bernstein_polynomial(i, len(control_points) - 1, t) * weights[i]

        sum_y_numerator += (py_bernstein_polynomial(i, len(control_points) - 1, t) * control_points[i][1] * weights[i])
        sum_y += py_bernstein_polynomial(i, len(control_points) - 1, t) * weights[i]

    return sum_x_numerator / sum_x, sum_y_numerator / sum_y


def py_bernstein_polynomial(i, n, t):
    return py_combination(n, i) * (t ** i) * ((1 - t) ** (n - i))


def py_combination(n, k):
    return math.factorial(n) / (math.factorial(k) * math.factorial(n - k))
