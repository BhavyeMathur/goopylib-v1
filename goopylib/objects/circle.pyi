"""
Module defining a circle object
"""

from __future__ import annotations

from typing import Tuple

from . import Ellipse


class Circle(Ellipse):
    """
    An object representing a circle

    Args:
        p1: the center (x, y) in world space
        radius: in world space

    Raises:
        TypeError: arguments must be a coordinate and a number
    """

    def __init__(self, p1: Tuple[float, float], radius: float) -> None:
        """
        An object representing a circle

        Args:
            p1: the center (x, y) in world space
            radius: the circle's radius

        Raises:
            TypeError: arguments must be a coordinate and a number
        """
