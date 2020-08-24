from goopylib.util import GraphicsError
from goopylib.Point import Point

def is_reflex(p1, p2, p3):  # check to see if 3 Points given are convex
    return not (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0]) >= 0


def check_in_triangle(p1, p2, p3, pt):
    if pt is None:
        return False

    # Code from https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle

    def sign(v1, v2, v3):
        return (v1[0] - v3[0]) * (v2[1] - v3[1]) - (v2[0] - v3[0]) * (v1[1] - v3[1])

    d1 = sign(pt, p1, p2)
    d2 = sign(pt, p2, p3)
    d3 = sign(pt, p3, p1)

    return not ((d1 < 0 or d2 < 0 or d3 < 0) and (d1 > 0 or d2 > 0 or d3 > 0))


def contains_no_other_points(p1, p2, p3, vertex_chain):
    for vertex in vertex_chain:
        if vertex not in (p1, p2, p3):
            if check_in_triangle(p1, p2, p3, vertex):
                return False
    return True


def is_clockwise(vertex_chain):
    # Code from https://github.com/mrbaozi/triangulation/blob/master/sources/triangulate.py
    sum = (vertex_chain[0].x - vertex_chain[len(vertex_chain) - 1].x) * \
          (vertex_chain[0].y + vertex_chain[len(vertex_chain) - 1].y)
    for i in range(len(vertex_chain) - 1):
        sum += (vertex_chain[i + 1].x - vertex_chain[i].x) * (vertex_chain[i + 1].y + vertex_chain[i].y)
    return sum > 0

# Runs in O(n^3) time
def triangulate_earclip(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

    vertex_chain = vertex_chain.copy()

    if is_clockwise(vertex_chain):
        vertex_chain.reverse()

    triangles = []
    size = len(vertex_chain)
    while size > 3:
        for i, point in enumerate(vertex_chain):
            p1 = vertex_chain[i - 1]
            p3 = vertex_chain[(i + 1) % size]
            if not is_reflex(p1, point, p3):
                if contains_no_other_points(p1, point, p3, vertex_chain):
                    vertex_chain.remove(point)
                    size -= 1
                    triangles.append((p1, point, p3))

    triangles.append(tuple(vertex_chain))
    return triangles

# Runs in O(n^2) time
# Reference: https://www.geometrictools.com/Documentation/TriangulationByEarClipping.pdf
def triangulate_modified_earclip(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

    vertex_chain = vertex_chain.copy()

    if is_clockwise(vertex_chain):
        vertex_chain.reverse()

    triangles = []
    ear_vertices = []

    reflex_vertices = []
    convex_vertices = []

    size = len(vertex_chain)
    # Complexity of O(n)
    i = 0
    for vertex in vertex_chain:
        if is_reflex(vertex_chain[i - 1], vertex, vertex_chain[(i + 1) % size]):
            reflex_vertices.append(vertex)
        else:
            convex_vertices.append(vertex)
        i += 1

    # Upper Limit Complexity of O(n)
    i = 0
    for vertex in convex_vertices:
        if contains_no_other_points(vertex_chain[i - 1], vertex, vertex_chain[(i + 1) % size], reflex_vertices):
            ear_vertices.append(vertex)
        i += 1

    while size > 9:
        ear_vertex = ear_vertices.pop(0)
        i = vertex_chain.index(ear_vertex)

        prev_vertex = vertex_chain[i - 1]
        next_vertex = vertex_chain[(i + 1) % size]

        vertex_chain.pop(i)
        size -= 1

        triangles.append((prev_vertex, ear_vertex, next_vertex))

        if size > 3:
            if not is_reflex(vertex_chain[i - 2], prev_vertex, next_vertex) and \
                    contains_no_other_points(vertex_chain[i - 2], prev_vertex, next_vertex, reflex_vertices):
                if prev_vertex not in ear_vertices:
                    ear_vertices.append(prev_vertex)
                    if prev_vertex in reflex_vertices:
                        reflex_vertices.remove(prev_vertex)
                        convex_vertices.append(prev_vertex)

            elif prev_vertex in ear_vertices:
                ear_vertices.remove(prev_vertex)
                if prev_vertex in convex_vertices:
                    convex_vertices.remove(prev_vertex)
                    reflex_vertices.append(prev_vertex)

            if (not is_reflex(prev_vertex, next_vertex, vertex_chain[(i + 1) % size])) and \
                    contains_no_other_points(prev_vertex, next_vertex, vertex_chain[(i + 1) % size], reflex_vertices):
                if next_vertex not in ear_vertices:
                    ear_vertices.append(next_vertex)
                    if next_vertex in reflex_vertices:
                        reflex_vertices.remove(next_vertex)
                        convex_vertices.append(next_vertex)

            elif next_vertex in ear_vertices:
                ear_vertices.remove(next_vertex)
                if next_vertex in convex_vertices:
                    convex_vertices.remove(next_vertex)
                    reflex_vertices.append(next_vertex)

        else:
            break

    triangles.append(tuple(vertex_chain))
    return triangles

# Runs in O(n log n) time
# Reference: https://cs.gmu.edu/~jmlien/teaching/09_fall_cs633/uploads/Main/lecture03.pdf
# Reference: https://www.slideserve.com/billy/brute-force-triangulation
# Work in Progress
def triangulate_plane_sweep(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

    vertex_chain = vertex_chain.copy()
    size = len(vertex_chain)

    if is_clockwise(vertex_chain):
        vertex_chain.reverse()

    vertex = vertex_chain[-1]
    vertex2 = vertex_chain[0]

    if vertex2[1] > vertex[1]:
        last_direction = "down"
    elif vertex2[1] == vertex[1]:
        if vertex2[0] > vertex[1]:
            last_direction = "down"
        else:
            last_direction = "up"
    else:
        last_direction = "up"

    vertex_types = []

    for i, vertex in enumerate(vertex_chain):
        vertex2 = vertex_chain[(i + 1) % size]

        is_turn_vertex = False
        if vertex2[1] > vertex[1]:
            if last_direction != "down":
                is_turn_vertex = True
                last_direction = "down"

        elif vertex2[1] == vertex[1]:
            if vertex2[0] > vertex[1]:
                if last_direction != "down":
                    is_turn_vertex = True
                    last_direction = "down"
            else:
                if last_direction != "up":
                    is_turn_vertex = True
                    last_direction = "up"
        else:
            if last_direction != "up":
                is_turn_vertex = True
                last_direction = "up"

        if is_turn_vertex:
            if is_reflex(vertex_chain[i - 1], vertex, vertex2):
                if vertex2[1] < vertex[1]:
                    vertex_types.append("merge")
                elif vertex2[1] == vertex[1] and vertex2[0] > vertex[0]:
                    vertex_types.append("merge")
                else:
                    vertex_types.append("split")
            else:
                if vertex2[1] < vertex[1]:
                    vertex_types.append("end")
                elif vertex2[1] == vertex[1] and vertex2[0] > vertex[0]:
                    vertex_types.append("end")
                else:
                    vertex_types.append("start")
        else:
            vertex_types.append("regular")

    print(vertex_types)

    return triangulate_modified_earclip(vertex_chain)

# ----------------------------------------------------------------
# These are empty functions for now, but are planned in the future.

# Runs in O(n log* n) time
# Reference: http://gamma.cs.unc.edu/SEIDEL/
def triangulate_siedel(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

# Runs in O(n log log n) time
# Reference: https://pdfs.semanticscholar.org/fe11/1fe1d1f73eb006280f4cda839f868d435f73.pdf
def triangulate_tarjan_wyk(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

# Runs in O(n log log n) time
# Reference: https://link.springer.com/content/pdf/10.1007/BF02187846.pdf
def triangulate_wrap_around_partition(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

# Runs in O(n) time
# Reference: https://www.cs.princeton.edu/~chazelle/pubs/polygon-triang.pdf
def triangulate_chazelle(vertex_chain):
    if not isinstance(vertex_chain, list):
        if isinstance(vertex_chain, tuple):
            vertex_chain = list(vertex_chain)
        else:
            raise GraphicsError("\n\nGraphicsError: input argument for triangulation must be a list or tuple,"
                                f" not {vertex_chain}")
    if len(vertex_chain) == 3:
        return [tuple(vertex_chain)]
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")
