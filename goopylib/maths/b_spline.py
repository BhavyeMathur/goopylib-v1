def uniform_bspline(t, control_points, degree=3, is_open=True):
    sum_x, sum_y = 0, 0

    size = len(control_points)
    knot_vector = [x for x in range(size + 2 + degree)]\

    if degree > size - 1:
        degree = size - 1

    if is_open:
        knot_vector = [x for x in range(size - degree + 1)]
        for _ in range(degree):
            knot_vector.insert(0, knot_vector[0])
            knot_vector.insert(-1, knot_vector[-1])

    for i in range(0, size):
        coeff = cox_de_boor_recursion(i, degree, t, knot_vector)
        sum_x += coeff * control_points[i][0]
        sum_y += coeff * control_points[i][1]

    return sum_x, sum_y


def cox_de_boor_recursion(i, j, t, knot_vector):
    if j == 0:
        return 1 if knot_vector[i] <= t < knot_vector[i + 1] else 0

    d1 = knot_vector[i + j] - knot_vector[i]
    a = ((t - knot_vector[i]) / d1) * cox_de_boor_recursion(i, j - 1, t, knot_vector)

    d2 = knot_vector[i + j + 1] - knot_vector[i + 1]
    b = ((knot_vector[i + j + 1] - t) / d2) * cox_de_boor_recursion(i + 1, j - 1, t, knot_vector)

    return a + b
