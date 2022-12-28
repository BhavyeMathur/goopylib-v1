"""
Module defining a line object
"""

import goopylib.ext.line as _line

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Line(Renderable):
    def __init__(self, p1: tuple[float, float], p2: tuple[float, float]):
        self._renderable: Line = _line.Line(p1, p2)

    def set_color(self, *args):
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._renderable.set_transparency(*args)
