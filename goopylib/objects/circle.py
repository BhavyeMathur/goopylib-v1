"""
Module defining a circle object
"""

from goopylib.objects.ellipse import Ellipse
import goopylib.ext.circle as _circle


class Circle(Ellipse):
    """
    An object representing a circle

    Args:
        position: the center (x, y) in world space
        radius: in world space

    Raises:
        TypeError: arguments must be a coordinate and a number
    """

    def __init__(self, position: tuple[float, float], radius: float):
        """
        An object representing a circle

        Args:
            position: the center (x, y) in world space
            radius: the circle's radius

        Raises:
            TypeError: arguments must be a coordinate and a number
        """
        self._renderable: Circle = _circle.Circle(position, radius)
