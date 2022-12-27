"""
Module defining a generic Renderable object
"""

from goopylib.core.window import Window
import goopylib.ext.renderable as _renderable


class Renderable:
    def __init__(self, arg: _renderable.Renderable):
        if isinstance(arg, _renderable.Renderable):
            self._renderable: Renderable = arg
        else:
            raise NotImplementedError("Cannot create renderable")

    def draw(self, window: Window):
        if isinstance(window, Window):
            return self._renderable.draw(window._window)
        else:
            raise TypeError(f"'Window' argument expected, got '{type(window)}'")

    def destroy(self):
        return self._renderable.destroy()

    def is_drawn(self) -> bool:
        return self._renderable.is_drawn()

    def set_anchor(self, x: float, y: float):
        return self._renderable.set_anchor(x, y)

    def reset_anchor(self):
        return self._renderable.reset_anchor()

    def move(self, dx: float, dy: float):
        return self._renderable.move(dx, dy)

    def rotate(self, angle: float):
        return self._renderable.rotate(angle)

    def scale(self, *args: float):
        return self._renderable.scale(*args)

    def set_size(self, width: float, height: float):
        return self._renderable.set_size(width, height)

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

    @property
    def position(self) -> tuple[float, float]:
        return self._renderable.position

    @position.setter
    def position(self, value: tuple[float, float]):
        self._renderable.position = value

    @property
    def rotation(self) -> float:
        return self._renderable.rotation

    @rotation.setter
    def rotation(self, value: float):
        self._renderable.rotation = value

    @property
    def xscale(self) -> float:
        return self._renderable.xscale

    @xscale.setter
    def xscale(self, value: float):
        self._renderable.xscale = value

    @property
    def yscale(self) -> float:
        return self._renderable.yscale

    @yscale.setter
    def yscale(self, value: float):
        self._renderable.yscale = value

    @property
    def width(self) -> float:
        return self._renderable.width

    @width.setter
    def width(self, value: float):
        self._renderable.width = value

    @property
    def height(self) -> float:
        return self._renderable.height

    @height.setter
    def height(self, value: float):
        self._renderable.height = value

    def hide(self, hide=True):
        return self._renderable.hide(hide)

    def show(self):
        return self._renderable.show()

    def is_hidden(self) -> bool:
        return self._renderable.is_hidden()

    def box_contains(self, x: float, y: float):
        return self._renderable.box_contains(x, y)

    def contains(self, x: float, y: float):
        return self._renderable.contains(x, y)
