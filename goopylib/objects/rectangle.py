"""
Module defining a rectangle object
"""

from typing import Union

import goopylib.ext.rectangle as _rectangle

from goopylib.objects.quad import Quad


class Rectangle(Quad):
    def __init__(self, *args: Union[tuple[float, float], float]):
        self._renderable: Rectangle = _rectangle.Rectangle(*args)
