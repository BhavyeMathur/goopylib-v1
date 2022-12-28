"""
Module defining a quad object
"""

import goopylib.ext.quad as _quad

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Quad(Renderable):
    def __init__(self, p1: tuple[float, float],
                 p2: tuple[float, float],
                 p3: tuple[float, float],
                 p4: tuple[float, float]):
        self._renderable: Quad = _quad.Quad(p1, p2, p3, p4)

    def set_color(self, *args):
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._renderable.set_transparency(*args)
