"""
Module defining an image object
"""

from typing import Union

import goopylib.ext.image as _image

from goopylib.objects.renderable import Renderable


class Image(Renderable):
    def __init__(self, path: str, p1: tuple[float, float], *args: Union[tuple[float, float], float]):
        self._renderable: Image = _image.Image(path, p1, *args)

    def set_transparency(self, *args: float):
        self._renderable.set_transparency(*args)

    def get_path(self) -> str:
        return self._renderable.get_path()
