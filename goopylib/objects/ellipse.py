"""
Module defining a ellipse object
"""

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable
import goopylib.ext.ellipse as _ellipse


class Ellipse(Renderable):
    def __init__(self, *args: tuple[float, float]):
        self._ellipse: Ellipse = _ellipse.Ellipse(*args)
        super().__init__(self._ellipse)

    def set_color(self, *args):
        if len(args) == 0:
            raise TypeError("function takes at least 1 arguments (0 given)")
        self._ellipse.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._ellipse.set_transparency(*args)
