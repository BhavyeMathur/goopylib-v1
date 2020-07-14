from goopylib.Point import Point
from goopylib.util import GraphicsError

import math

class Interpolations:
    pass

def LinearInterpolation(p0, p1, t):
    if not isinstance(p0, Point):
        raise GraphicsError(f"\n\nGraphicsError: p0 Point to Interpolate between must be a Point object, not {p0}")
    if not isinstance(p1, Point):
        raise GraphicsError(f"\n\nGraphicsError: p1 Point to Interpolate between must be a Point object, not {p1}")
    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")

    return (1 - t) * p0.y + t * p1.y

# References for these from http://paulbourke.net/miscellaneous/interpolation/

def CosineInterpolation(p0, p1, t):
    if not isinstance(p0, Point):
        raise GraphicsError(f"\n\nGraphicsError: p0 Point to Interpolate between must be a Point object, not {p0}")
    if not isinstance(p1, Point):
        raise GraphicsError(f"\n\nGraphicsError: p1 Point to Interpolate between must be a Point object, not {p1}")
    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")

    t = (1 - math.cos(t * math.pi)) / 2
    return (1 - t) * p0.y + t * p1.y

def CubicInterpolation(p0, p1, p2, p3, t):
    for i, p in enumerate([p0, p1, p2, p3]):
        if not isinstance(p, Point):
            raise GraphicsError(f"\n\nGraphicsError: p{i} Point to Interpolate between must be a Point object, not {p}")

    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")
    
    a0 = p3.y - p2.y - p0.y + p1.y
    a1 = p0.y - p1.y - a0
    a2 = p2.y - p0.y
    a3 = p1.y
    
    return (a0 * t ** 3) + (a1 * t ** 2) + (a2 * t) + a3

def HermiteInterpolation(p0, p1, p2, p3, t, tension, bias):
    for i, p in enumerate([p0, p1, p2, p3]):
        if not isinstance(p, Point):
            raise GraphicsError(f"\n\nGraphicsError: p{i} Point to Interpolate between must be a Point object, not {p}")

    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")

    if not (isinstance(tension, int) or isinstance(tension, float)):
        raise GraphicsError(f"\n\nGraphicsError: tension for interpolation must be an int or float, not {tension}")
    if not (isinstance(bias, int) or isinstance(bias, float)):
        raise GraphicsError(f"\n\nGraphicsError: bias for interpolation must be an int or float, not {bias}")

    t2 = t ** 2
    t3 = t ** 3

    m0 = (p1.y - p0.y) * (1 + bias) * (1 - tension) / 2
    m0 += (p2.y - p1.y) * (1 - bias) * (1 - tension) / 2
    m1 = (p2.y - p1.y) * (1 + bias) * (1 - tension) / 2
    m1 += (p3.y - p2.y) * (1 - bias) * (1 - tension) / 2

    a0 = 2 * t3 - 3 * t2 + 1
    a1 = t3 - 2 * t2 + t
    a2 = t3 - t2
    a3 = -2 * t3 + 3 * t2

    return a0 * p1.y + a1 * m0 + a2 * m1 + a3 * p2.y

def CircularInterpolation(p0, p1, t):
    pass
