"""
Module defining an ellipse object
"""

from typing import Union

import goopylib.ext.ellipse as _ellipse

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Ellipse(Renderable):
    def __init__(self, p1: tuple[float, float], *args: Union[tuple[float, float], float]):
        self._renderable: Ellipse = _ellipse.Ellipse(p1, *args)

    def set_color(self, *args):
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        self._renderable.set_transparency(*args)
