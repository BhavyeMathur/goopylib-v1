"""
Module defining a quad object
"""

from __future__ import annotations

from typing import Union, Tuple

# pylint: disable-next=no-name-in-module, import-error
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

    # pylint: disable-next=super-init-not-called
    def __init__(self, p1: Tuple[float, float],
                 p2: Tuple[float, float],
                 p3: Tuple[float, float],
                 p4: Tuple[float, float]):
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

    # TODO color should be a @property & color get methods (v2.0.x)
    def set_color(self, *args) -> None:
        """
        Sets the fill color of the object

        Args:
            *args: a color or 4 colors corresponding to each vertex

        Raises:
            TypeError: arguments must be colors
        """
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    @property
    def p1(self) -> Tuple[float, float]:
        """
        The position of the object's 1st vertex in world coordinates

        Returns:
            a tuple (x, y) with the position

        Raises:
            TypeError: value must be a tuple of x, y numbers
        """
        return self._renderable.p1

    @p1.setter
    def p1(self, value: Tuple[float, float]) -> None:
        self._renderable.p1 = value

    @property
    def p2(self) -> Tuple[float, float]:
        """
        The position of the object's 2nd vertex in world coordinates

        Returns:
            a tuple (x, y) with the position

        Raises:
            TypeError: value must be a tuple of x, y numbers
        """
        return self._renderable.p2

    @p2.setter
    def p2(self, value: Tuple[float, float]) -> None:
        self._renderable.p2 = value

    @property
    def p3(self) -> Tuple[float, float]:
        """
        The position of the object's 3rd vertex in world coordinates

        Returns:
            a tuple (x, y) with the position

        Raises:
            TypeError: value must be a tuple of x, y numbers
        """
        return self._renderable.p3

    @p3.setter
    def p3(self, value: Tuple[float, float]) -> None:
        self._renderable.p3 = value

    @property
    def p4(self) -> Tuple[float, float]:
        """
        The position of the object's 4th vertex in world coordinates

        Returns:
            a tuple (x, y) with the position

        Raises:
            TypeError: value must be a tuple of x, y numbers
        """
        return self._renderable.p4

    @p4.setter
    def p4(self, value: Tuple[float, float]) -> None:
        self._renderable.p4 = value

    @property
    def transparency(self) -> Union[float, Tuple[float, float, float, float]]:
        """
        The transparency of the object at each vertex between 0 (transpareny) and 1 (opaque)

        Raises:
            TypeError: transparency must be a float or tuple of floats
            ValueError: transparency must be between 0 and 1
        """
        return self._renderable.transparency

    @transparency.setter
    def transparency(self, value: Union[float, Tuple[float, float, float, float]]) -> None:
        self._renderable.transparency = value
