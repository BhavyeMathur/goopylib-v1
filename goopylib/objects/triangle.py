"""
Module defining a triangle object
"""

import goopylib.ext.triangle as _triangle

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Triangle(Renderable):
    """
    An object representing a triangle with 3 vertices.

    Args:
        p1: a tuple (x, y) with the 1st coordinate in world space
        p2: a tuple (x, y) with the 2nd coordinate in world space
        p3: a tuple (x, y) with the 3rd coordinate in world space

    Raises:
        TypeError: p1, p2, and p3 must be (x, y) tuples of numbers
    """

    def __init__(self, p1: tuple[float, float], p2: tuple[float, float], p3: tuple[float, float]):
        """
        An object representing a triangle with 3 vertices.

        Args:
            p1: a tuple (x, y) with the 1st coordinate in world space
            p2: a tuple (x, y) with the 2nd coordinate in world space
            p3: a tuple (x, y) with the 3rd coordinate in world space

        Raises:
            TypeError: p1, p2, and p3 must be (x, y) tuples of numbers
        """
        self._renderable: Triangle = _triangle.Triangle(p1, p2, p3)

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
            *args: a float or 3 floats corresponding to each vertex

        Raises:
            TypeError: arguments must be floats
            ValueError: transparency must be between 0 and 1
        """
        self._renderable.set_transparency(*args)
