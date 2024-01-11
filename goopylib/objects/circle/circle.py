"""
Module defining a circle object
"""

from __future__ import annotations

from typing import Tuple

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.circle as _circle

from goopylib.objects.ellipse import Ellipse


class Circle(Ellipse):
    """
    An object representing a circle

    Args:
        position: the center (x, y) in world space
        radius: in world space

    Raises:
        TypeError: arguments must be a coordinate and a number
    """

    # pylint: disable-next=super-init-not-called
    def __init__(self, position: Tuple[float, float], radius: float) -> None:
        """
        An object representing a circle

        Args:
            position: the center (x, y) in world space
            radius: the circle's radius

        Raises:
            TypeError: arguments must be a coordinate and a number
        """
        self._renderable: Circle = _circle.Circle(position, radius)
