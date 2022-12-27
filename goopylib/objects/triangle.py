from core.window import Window
from src.ext.archive.texture import Texture


class Triangle:
    def __init__(self, *args: tuple[float, float]):
        self._x: float = 0
        self._y: float = 0
        self._xscale: float = 0
        self._yscale: float = 0
        self._rotation: float = 0
        self._fill: Texture = Texture()

    """Getters & Setters --------------------------------------------------------------------------------------------"""

    # X Position
    @property
    def x(self) -> float:
        return self._x

    @x.setter
    def x(self, value: float):
        pass

    # Y Position
    @property
    def y(self) -> float:
        return self._y

    @y.setter
    def y(self, value: float):
        pass

    # Rotation
    @property
    def rotation(self) -> float:
        return self._rotation

    @rotation.setter
    def rotation(self, value: float):
        pass

    # X Scale
    @property
    def xscale(self) -> float:
        return self._xscale

    @xscale.setter
    def xscale(self, value: float):
        pass

    # Y Scale
    @property
    def yscale(self) -> float:
        return self._yscale

    @yscale.setter
    def yscale(self, value: float):
        pass

    # Fill
    @property
    def fill(self) -> Texture:
        return self._fill

    @fill.setter
    def fill(self, value):
        pass

    """Methods ------------------------------------------------------------------------------------------------------"""

    def draw(self, *args: Window):
        pass

    def move(self, *args: float):
        pass

    def scale(self, *args: float):
        pass
