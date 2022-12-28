"""
Module defining a quad object
"""

import goopylib.ext.quad as _quad

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Quad(Renderable):
    """
    An object representing a quad with 4 vertices.

    Args:
        p1: a tuple (x, y) with the 1st coordinate in world space
        p2: a tuple (x, y) with the 2nd coordinate in world space
        p3: a tuple (x, y) with the 3rd coordinate in world space
        p4: a tuple (x, y) with the 4th coordinate in world space

    Raises:
        TypeError: p1, p2, p3, and p4 must be (x, y) tuples of numbers
    """

    def __init__(self, p1: tuple[float, float],
                 p2: tuple[float, float],
                 p3: tuple[float, float],
                 p4: tuple[float, float]):
        """
        An object representing a quad with 4 vertices.

        Args:
            p1: a tuple (x, y) with the 1st coordinate in world space
            p2: a tuple (x, y) with the 2nd coordinate in world space
            p3: a tuple (x, y) with the 3rd coordinate in world space
            p4: a tuple (x, y) with the 4th coordinate in world space

        Raises:
            TypeError: p1, p2, p3, and p4 must be (x, y) tuples of numbers
        """
        self._renderable: Quad = _quad.Quad(p1, p2, p3, p4)

    def set_color(self, *args):
        """
        Sets the fill color of the object

        Args:
            *args: a color or 4 colors corresponding to each vertex

        Raises:
            TypeError: arguments must be colors
        """
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        """
        Sets the transparency of the object

        Args:
            *args: a float or 4 floats corresponding to bottom-left, bottom-right, top-right, and top-left

        Raises:
            TypeError: arguments must be floats
            ValueError: transparency must be between 0 and 1
        """
        self._renderable.set_transparency(*args)
