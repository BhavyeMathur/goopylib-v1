"""
Module defining a rectangle object
"""

from __future__ import annotations

from typing import Union, Tuple

from . import Quad


class Rectangle(Quad):
    """
    An object representing a rectangle

    Args:
        p1: a tuple (x, y) in world space
        *args: either annother tuple (x, y) in world space, or the width and height of the rectangle

    Raises:
        TypeError: arguments must be numbers or coordinates

    Examples:

        .. code-block:: python

            # Creates a rectangle centered at (50, 100) with a size of (100, 200)

            >>> Rectangle((0, 0), (100, 200))

            # Creates a rectangle centered at (0, 0) with size (50, 100)

            >>> Rectangle((0, 0), 50, 100)
    """

    def __init__(self, p1: Tuple[float, float], *args: Union[Tuple[float, float], float]) -> None:
        """
        An object representing a rectangle

        Args:
            p1: a tuple (x, y) in world space
            *args: either annother tuple (x, y) in world space, or the width and height of the rectangle

        Raises:
            TypeError: arguments must be numbers or coordinates

        Examples:

            .. code-block:: python

                # Creates a rectangle centered at (50, 100) with a size of (100, 200)

                >>> Rectangle((0, 0), (100, 200))

                # Creates a rectangle centered at (0, 0) with size (50, 100)

                >>> Rectangle((0, 0), 50, 100)
        """
