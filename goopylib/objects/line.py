"""
Module defining a line object
"""

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable
import goopylib.ext.line as _line


class Line(Renderable):
    def __init__(self, *args: tuple[float, float]):
        self._line: Line = _line.Line(*args)
        super().__init__(self._line)

    def set_color(self, *args):
        if len(args) == 0:
            raise TypeError("function takes at least 1 arguments (0 given)")
        self._line.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._line.set_transparency(*args)
