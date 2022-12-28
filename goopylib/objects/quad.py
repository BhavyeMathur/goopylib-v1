"""
Module defining a quad object
"""

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable
# import goopylib.ext.quad as _quad


class Quad(Renderable):
    def __init__(self, *args: tuple[float, float]):
        self._quad: Quad = _quad.Quad(*args)
        super().__init__(self._quad)

    def set_color(self, *args):
        if len(args) == 0:
            raise TypeError("function takes at least 1 arguments (0 given)")
        self._quad.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._quad.set_transparency(*args)
