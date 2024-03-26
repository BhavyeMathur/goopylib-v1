"""
Module defining a line object
"""

from __future__ import annotations

from typing import NoReturn, Tuple, Union

from . import Quad


class Line(Quad):
    """
    An object representing a line connecting 2 points together.

    Args:
        p1: a tuple (x, y) with the 1st coordinate in world space
        p2: a tuple (x, y) with the 2nd coordinate in world space

    Raises:
        TypeError: p1 and p2 must be (x, y) tuples of numbers
    """

    def __init__(self, p1: Tuple[float, float], p2: Tuple[float, float], thickness: float = 5) -> None:
        """
        An object representing a line connecting 2 points together.

        Args:
            p1: a tuple (x, y) with the 1st coordinate in world space
            p2: a tuple (x, y) with the 2nd coordinate in world space
            thickness: the thickness of the line in world coordinates. Defaults to 5.

        Raises:
            TypeError: p1 and p2 must be (x, y) tuples of numbers
        """

    @property
    def thickness(self) -> float:
        """
        The thickness of the line in world coordinates

        Raises:
            TypeError: value must be a number
        """

    @thickness.setter
    def thickness(self, value: float) -> None:
        pass

    @property
    def p3(self) -> NoReturn:
        """
        Unimplemented for lines
        """

    @p3.setter
    def p3(self, value: Tuple[float, float]) -> NoReturn:
        pass

    @property
    def p4(self) -> NoReturn:
        """
        Unimplemented for lines
        """

    @p4.setter
    def p4(self, value: Tuple[float, float]) -> NoReturn:
        pass

    @property
    def transparency(self) -> Union[float, Tuple[float, float], Tuple[float, float, float, float]]:
        """
        The transparency of the object at each vertex between 0 (transparent) and 1 (opaque)

        Raises:
            TypeError: transparency must be a float or tuple of floats
            ValueError: transparency must be between 0 and 1
        """

    @transparency.setter
    def transparency(self, value: Union[float, Tuple[float, float], Tuple[float, float, float, float]]) -> None:
        pass
