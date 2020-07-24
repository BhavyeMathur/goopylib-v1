from goopylib.util import GraphicsError
from goopylib.Point import Point

def IsConvex(p1, p2, p3):  # check to see if 3 Points given are convex
    if not (isinstance(p1, Point) and isinstance(p2, Point) and isinstance(p3, Point)):
        raise GraphicsError("\n\nGraphicsError: points given to check whether they are convex must all be Point "
                            f"objects, not {p1}, {p2}, {p3}")
    return not (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) >= 0


def CheckInTriangle(p1, p2, p3, pt):
    if not (isinstance(p1, Point) and isinstance(p2, Point) and isinstance(p3, Point)):
        raise GraphicsError("\n\nGraphicsError: points given for triangle must all be Point "
                            f"objects, not {p1}, {p2}, {p3}")
    if not isinstance(pt, Point):
        raise GraphicsError("\n\nGraphicsError: the point given to check if it is inside the triangle must be a Point"
                            f" object, not {pt}")

    # Code from https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle

    def sign(v1, v2, v3):
        return (v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y)

    d1 = sign(pt, p1, p2)
    d2 = sign(pt, p2, p3)
    d3 = sign(pt, p3, p1)

    return not ((d1 < 0 or d2 < 0 or d3 < 0) and (d1 > 0 or d2 > 0 or d3 > 0))


def IsClockwise(vertex_chain):
    # Code from https://github.com/mrbaozi/triangulation/blob/master/sources/triangulate.py
    sum = (vertex_chain[0].x - vertex_chain[len(vertex_chain) - 1].x) * \
          (vertex_chain[0].y + vertex_chain[len(vertex_chain) - 1].y)
    for i in range(len(vertex_chain) - 1):
        sum += (vertex_chain[i + 1].x - vertex_chain[i].x) * (vertex_chain[i + 1].y + vertex_chain[i].y)
    return sum > 0


def TriangulateEarClipping(vertex_chain):
    if not isinstance(vertex_chain, list):
        raise GraphicsError(f"\n\nGraphicsError: input argument for triangulation must be a list, not {vertex_chain}")
    if len(vertex_chain) == 3:
        return ()
    elif len(vertex_chain) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertex_chain)} vertices are present")

    if not IsClockwise(vertex_chain):
        vertex_chain = vertex_chain[::-1]

    triangles = []
    while len(vertex_chain) > 3:
        size = len(vertex_chain)
        ear_removed = False
        for i, point in enumerate(vertex_chain):
            if not ear_removed:
                p1, p2, p3 = vertex_chain[(i - 1) % size], point, vertex_chain[(i + 1) % size]
                if IsConvex(p1, p2, p3):
                    is_diagonal = True
                    for vertex in vertex_chain:
                        if vertex not in (p1, p2, p3):
                            if not is_diagonal:
                                continue
                            is_diagonal = not CheckInTriangle(p1, p2, p3, vertex)
                    if is_diagonal:
                        vertex_chain.remove(p2)
                        ear_removed = True
                        triangles.append((p1, p2, p3))
    return triangles
