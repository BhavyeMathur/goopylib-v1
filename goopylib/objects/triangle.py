"""
Module defining a triangle object
"""

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable
import goopylib.ext.triangle as _triangle


class Triangle(Renderable):
    def __init__(self, *args: tuple[float, float]):
        self._triangle: Triangle = _triangle.Triangle(*args)
        super().__init__(self._triangle)

    def set_color(self, *args):
        if len(args) == 0:
            raise TypeError("function takes at least 1 arguments (0 given)")
        self._triangle.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._triangle.set_transparency(*args)
