from goopylib.Point import Point
from goopylib.util import GraphicsError

import math


def linear_interpolation(p0, p1, t):
    if not isinstance(p0, Point):
        raise GraphicsError(f"\n\nGraphicsError: p0 Point to Interpolate between must be a Point object, not {p0}")
    if not isinstance(p1, Point):
        raise GraphicsError(f"\n\nGraphicsError: p1 Point to Interpolate between must be a Point object, not {p1}")
    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")

    return (1 - t) * p0[1] + t * p1[1]

# References for these from http://paulbourke.net/miscellaneous/interpolation/


def cosine_interpolation(p0, p1, t):
    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")

    t = (1 - math.cos(t * math.pi)) / 2
    return (1 - t) * p0[1] + t * p1[1]


def cubic_interpolation(p0, p1, p2, p3, t):
    if not (isinstance(t, int) or isinstance(t, float)):
        raise GraphicsError(f"\n\nGraphicsError: t parameter for interpolation must be an int or float, not {t}")
    if not 0 <= t <= 1:
        raise GraphicsError(f"\n\nGraphicsError: t parameter must be between 0 & 1, 0 <= t <= 1, not {t}")
    
    a0 = p3[1] - p2[1] - p0[1] + p1[1]
    a1 = p0[1] - p1[1] - a0
    a2 = p2[1] - p0[1]
    a3 = p1[1]
    
    return (a0 * t ** 3) + (a1 * t ** 2) + (a2 * t) + a3


def hermite_interpolation(p0, p1, p2, p3, t, tension, bias):
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

    m0 = (p1[1] - p0[1]) * (1 + bias) * (1 - tension) / 2
    m0 += (p2[1] - p1[1]) * (1 - bias) * (1 - tension) / 2
    m1 = (p2[1] - p1[1]) * (1 + bias) * (1 - tension) / 2
    m1 += (p3[1] - p2[1]) * (1 - bias) * (1 - tension) / 2

    a0 = 2 * t3 - 3 * t2 + 1
    a1 = t3 - 2 * t2 + t
    a2 = t3 - t2
    a3 = -2 * t3 + 3 * t2

    return a0 * p1[1] + a1 * m0 + a2 * m1 + a3 * p2[1]


def circular_interpolation(p0, p1, t):
    pass
