from goopylib.util import GraphicsError
from goopylib.Point import Point

from math import degrees, acos

def IsConvex(p1, p2, p3):  # check to see if 3 Points given are convex
    if not (isinstance(p1, Point) and isinstance(p2, Point) and isinstance(p3, Point)):
        raise GraphicsError("\n\nGraphicsError: points given to check whether they are convex must all be Point "
                            f"objects, not {p1}, {p2}, {p3}")
    return not (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) >= 0


def GetInteriorAngle(p1, p2, p3):
    pass


def CheckInTriangle(p1, p2, p3, pt):
    if pt is None:
        return False
    else:
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


def IsClockwise(vertices):
    # Code from https://github.com/mrbaozi/triangulation/blob/master/sources/triangulate.py
    sum = (vertices[0].x - vertices[len(vertices) - 1].x) * \
          (vertices[0].y + vertices[len(vertices) - 1].y)
    for i in range(len(vertices) - 1):
        sum += (vertices[i + 1].x - vertices[i].x) * (vertices[i + 1].y + vertices[i].y)
    return sum > 0


def TriangulateMeister(vertices):
    if not isinstance(vertices, list):
        raise GraphicsError(f"\n\nGraphicsError: input argument for triangulation must be a list, not {vertices}")
    if len(vertices) == 3:
        return ()
    elif len(vertices) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertices)} vertices are present")
    if not IsClockwise(vertices):
        vertices = vertices[::-1]

    triangles = []
    while len(vertices) > 3:
        size = len(vertices)
        ear_removed = False

        for i in range(len(vertices)):
            if not ear_removed:
                p1, p2, p3 = vertices[(i - 1) % size], vertices[i % size], vertices[(i + 1) % size]

                if IsConvex(p1, p2, p3):
                    is_diagonal = True
                    for vertex in vertices:
                        if vertex not in (p1, p2, p3):
                            if not is_diagonal:
                                continue
                            is_diagonal = not CheckInTriangle(p1, p2, p3, vertex)

                    if is_diagonal:
                        vertices.remove(p2)
                        ear_removed = True
                        triangles.append((p1, p2, p3))
    triangles.append(tuple(vertices))
    return triangles


def TriangulateRourke(vertices):
    if not isinstance(vertices, list):
        raise GraphicsError(f"\n\nGraphicsError: input argument for triangulation must be a list, not {vertices}")
    if len(vertices) == 3:
        return ()
    elif len(vertices) < 3:
        raise GraphicsError("\n\nGraphicsError: polygon for triangulation must have at least 3 vertices, currently, "
                            f"only {len(vertices)} vertices are present")
    if IsClockwise(vertices):
        vertices = vertices[::-1]

    size = len(vertices)
    interior_angles = [GetInteriorAngle(vertices[(i - 1) % size], vertices[i], vertices[(i + 1) % size])
                       for i in range(size)]
    print(interior_angles)
    triangles = []

    return triangles
