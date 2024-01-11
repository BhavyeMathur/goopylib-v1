"""
Module defining a line object
"""

from __future__ import annotations

from typing import NoReturn, Tuple, Union

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.line as _line

from goopylib.objects.quad import Quad


class Line(Quad):
    """
    An object representing a line connecting 2 points together.

    Args:
        p1: a tuple (x, y) with the 1st coordinate in world space
        p2: a tuple (x, y) with the 2nd coordinate in world space

    Raises:
        TypeError: p1 and p2 must be (x, y) tuples of numbers
    """

    # pylint: disable-next=super-init-not-called
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
        self._renderable: Line = _line.Line(p1, p2, thickness)

    @property
    def thickness(self) -> float:
        """
        The thickness of the line in world coordinates

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.thickness

    @thickness.setter
    def thickness(self, value: float) -> None:
        self._renderable.thickness = value

    @property
    def p3(self) -> NoReturn:
        """
        Unimplemented for lines
        """
        raise NotImplementedError("p3 property is not implemented for lines")

    @p3.setter
    def p3(self, value: Tuple[float, float]) -> NoReturn:
        raise NotImplementedError("p3 property is not implemented for lines")

    @property
    def p4(self) -> NoReturn:
        """
        Unimplemented for lines
        """
        raise NotImplementedError("p4 property is not implemented for lines")

    @p4.setter
    def p4(self, value: Tuple[float, float]) -> NoReturn:
        raise NotImplementedError("p4 property is not implemented for lines")

    @property
    def transparency(self) -> Union[float, Tuple[float, float], Tuple[float, float, float, float]]:
        """
        The transparency of the object at each vertex between 0 (transpareny) and 1 (opaque)

        Raises:
            TypeError: transparency must be a float or tuple of floats
            ValueError: transparency must be between 0 and 1
        """
        return self._renderable.transparency

    @transparency.setter
    def transparency(self, value: Union[float, Tuple[float, float], Tuple[float, float, float, float]]) -> None:
        self._renderable.transparency = value
