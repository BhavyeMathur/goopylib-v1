"""
Module defining a line object
"""

import goopylib.ext.line as _line

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Line(Renderable):
    """
    An object representing a line connecting 2 points together.

    Args:
        p1: a tuple (x, y) with the 1st coordinate in world space
        p2: a tuple (x, y) with the 2nd coordinate in world space

    Raises:
        TypeError: p1 and p2 must be (x, y) tuples of numbers
    """

    def __init__(self, p1: tuple[float, float], p2: tuple[float, float]):
        """
        An object representing a line connecting 2 points together.

        Args:
            p1: a tuple (x, y) with the 1st coordinate in world space
            p2: a tuple (x, y) with the 2nd coordinate in world space

        Raises:
            TypeError: p1 and p2 must be (x, y) tuples of numbers
        """
        self._renderable: Line = _line.Line(p1, p2)

    def set_color(self, *args):
        """
        Sets the outline color of the line

        Args:
            *args: a color or 2 colors corresponding to each vertex

        Raises:
            TypeError: arguments must be colors
        """
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        """
        Sets the transparency of the object

        Args:
            *args: a float or 2 floats corresponding to each vertex

        Raises:
            TypeError: arguments must be floats
            ValueError: transparency must be between 0 and 1
        """
        self._renderable.set_transparency(*args)
