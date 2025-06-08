"""
Module defining an ellipse object
"""

from __future__ import annotations

from typing import Union, Tuple

from . import Renderable


class Ellipse(Renderable):
    """
    An object representing an ellipse or oval

    Args:
        p1: a tuple (x, y) with the coordinate in world space
        *args: either annother tuple (x, y) in world space, or the x and y radii of the ellipse

    Raises:
        TypeError: arguments must be numbers or coordinates

    Examples:

        .. code-block:: python

            # Creates an ellipse centered at (50, 100) with a size of (100, 200)

            >>> Ellipse((0, 0), (100, 200))

            # Creates an ellipse centered at (0, 0) with radii (50, 100)

            >>> Ellipse((0, 0), 50, 100)
    """

    def __init__(self, p1: Tuple[float, float], *args: Union[Tuple[float, float], float]) -> None:
        """
        An object representing an ellipse or oval

        Args:
            p1: a tuple (x, y) in world space
            *args: either annother tuple (x, y) in world space, or the x and y radii of the ellipse

        Raises:
            TypeError: arguments must be numbers or coordinates

        Examples:

            .. code-block:: python

                # Creates an ellipse centered at (50, 100) with a size of (100, 200)

                >>> Ellipse((0, 0), (100, 200))

                # Creates an ellipse centered at (0, 0) with radii (50, 100)

                >>> Ellipse((0, 0), 50, 100)
        """

    def set_color(self, *args) -> None:
        """
        Sets the fill color of the object

        Args:
            *args: a color or 4 colors corresponding to bottom-left, bottom-right, top-right, and top-left

        Raises:
            TypeError: arguments must be colors
        """

    @property
    def transparency(self) -> Union[float, Tuple[float, float, float, float]]:
        """
        The transparency of the object at each vertex between 0 (transparent) and 1 (opaque)

        Raises:
            TypeError: transparency must be a float or tuple of floats
            ValueError: transparency must be between 0 and 1
        """

    @transparency.setter
    def transparency(self, value: Union[float, Tuple[float, float, float, float]]) -> None:
        pass
