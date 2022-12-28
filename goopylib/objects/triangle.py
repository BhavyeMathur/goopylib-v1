"""
Module defining a triangle object
"""

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable
import goopylib.ext.triangle as _triangle


class Triangle(Renderable):
    def __init__(self, *args: tuple[float, float]):
        self._triangle = _triangle.Triangle(*args)
        super().__init__(self._triangle)

    def set_color(self, *args: Color):
        pass

    def set_transparency(self, *args: float):
        pass
