"""
Module defining a circle object
"""

from goopylib.objects.ellipse import Ellipse
import goopylib.ext.circle as _circle


class Circle(Ellipse):
    def __init__(self, position: tuple[float, float], radius: float):
        self._renderable: Circle = _circle.Circle(position, radius)
