"""
Use this module for simple random color generation in different formats.
"""

from __future__ import annotations

from random import randint as _randint
from random import random as _random

from goopylib.color.color import ColorRGB, ColorHex, ColorCMYK, ColorHSV, ColorHSL
from goopylib.color.conversions import rgb_to_hex


# Random Colors

def random_rgb() -> ColorRGB:
    """
    Returns:
         a random RGB color
    """
    return ColorRGB(_randint(0, 255), _randint(0, 255), _randint(0, 255))


def random_hex() -> ColorHex:
    """
    Returns:
         a random Hexadecimal color
    """
    return ColorHex(rgb_to_hex(_randint(0, 255), _randint(0, 255), _randint(0, 255)))


def random_cmyk() -> ColorCMYK:
    """
    Returns:
         a random CMYK color
    """
    return ColorCMYK(_random(), _random(), _random(), _random())


def random_hsv() -> ColorHSV:
    """
    Returns:
        a random HSV color
    """
    return ColorHSV(_randint(0, 360), _random(), _random())


def random_hsl() -> ColorHSL:
    """
    Returns:
         a random HSL color
    """
    return ColorHSL(_randint(0, 360), _random(), _random())
