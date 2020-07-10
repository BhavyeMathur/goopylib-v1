from goopylib.Point import Point

def UniformBSpline(t, control_points, degree=3, open=True):
    sum_x, sum_y = 0, 0
    knot_vector = [x for x in range(len(control_points) + 2 + degree)]\

    if degree > len(control_points) - 1:
        degree = len(control_points) - 1

    if open:
        knot_vector = [x for x in range(len(control_points) - degree + 1)]
        for _ in range(degree):
            knot_vector.insert(0, knot_vector[0])
            knot_vector.insert(-1, knot_vector[-1])

    for i in range(len(control_points)):
        sum_x += CoxDeBoorRecursion(i, degree, t, knot_vector) * control_points[i].x
        sum_y += CoxDeBoorRecursion(i, degree, t, knot_vector) * control_points[i].y

    return Point(sum_x, sum_y)


def CoxDeBoorRecursion(i, j, t, knot_vector):
    if j == 0:
        return 1 if knot_vector[i] <= t < knot_vector[i + 1] else 0

    d1 = (knot_vector[i + j] - knot_vector[i])
    a = ((t - knot_vector[i]) / d1 * CoxDeBoorRecursion(i, j - 1, t, knot_vector)) if d1 > 0 else 0

    d2 = (knot_vector[i + j + 1] - knot_vector[i + 1])
    b = (((knot_vector[i + j + 1] - t) / d2) * CoxDeBoorRecursion(i + 1, j - 1, t, knot_vector)) if d2 > 0 else 0
    return a + b
