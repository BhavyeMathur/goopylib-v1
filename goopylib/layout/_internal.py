from __future__ import annotations
from typing import Union, Literal, get_args


_UNITS = Literal["px", "%", "auto"]
_LRTB_SETTER_TYPE = Union[int, tuple[int], tuple[int, int], tuple[int, int, int], tuple[int, int, int, int]]


class _LRTB:
    def __init__(self, left: int, right: int, top: int, bottom: int):
        self._left = left
        self._right = right
        self._top = top
        self._bottom = bottom

        self._x = self._left + self._right
        self._y = self._top + self._bottom

    @property
    def left(self) -> int:
        return self._left

    @left.setter
    def left(self, value: int):
        self._left = value
        self._x = self.left + self._right

    @property
    def right(self) -> int:
        return self._right

    @right.setter
    def right(self, value: int):
        self._right = value
        self._x = self.left + self._right

    @property
    def top(self) -> int:
        return self._top

    @top.setter
    def top(self, value: int):
        self._top = value
        self._y = self._top + self._bottom

    @property
    def bottom(self) -> int:
        return self._bottom

    @bottom.setter
    def bottom(self, value: int):
        self._bottom = value
        self._y = self._top + self._bottom

    @property
    def x(self) -> int:
        return self._x

    @property
    def y(self) -> int:
        return self._y

    def set_values(self, value: _LRTB_SETTER_TYPE) -> None:
        if isinstance(value, int):
            self.left = value
            self.right = value
            self.top = value
            self.bottom = value

        elif len(value) == 1:
            self.set_values(value[0])

        elif len(value) == 2:
            self.top = value[0]
            self.bottom = value[0]
            self.left = value[1]
            self.right = value[1]

        elif len(value) == 3:
            self.top = value[0]
            self.right = value[1]
            self.left = value[1]
            self.bottom = value[2]

        elif len(value) == 4:
            self.top = value[0]
            self.right = value[1]
            self.bottom = value[2]
            self.left = value[3]


class _Box:
    def __init__(self) -> None:
        self._x1: int = 0
        self._x2: int = 0
        self._y1: int = 0
        self._y2: int = 0

        self._width: int = 0
        self._height: int = 0

    @property
    def x1(self) -> int:
        return self._x1

    @x1.setter
    def x1(self, value: int):
        self._x1 = value
        self._width = self._x2 - self._x1

    @property
    def y1(self) -> int:
        return self._y1

    @y1.setter
    def y1(self, value: int):
        self._y1 = value
        self._height = self._y2 - self._y1

    @property
    def x2(self) -> int:
        return self._x2

    @x2.setter
    def x2(self, value: int):
        self._x2 = value
        self._width = self._x2 - self._x1

    @property
    def y2(self) -> int:
        return self._y2

    @y2.setter
    def y2(self, value: int):
        self._y2 = value
        self._height = self._y2 - self._y1

    @property
    def width(self) -> int:
        return self._width

    @width.setter
    def width(self, value: int):
        self._x2 = self._x1 + value
        self._width = value

    @property
    def height(self) -> int:
        return self._height

    @height.setter
    def height(self, value: int):
        self._y2 = self._y1 + value
        self._height = value

    @property
    def start(self) -> tuple[int, int]:
        return self._x1, self._y1

    @property
    def end(self) -> tuple[int, int]:
        return self._x2, self._y2

    def translate(self, dx: int, dy: int) -> None:
        self._x1 += dx
        self._x2 += dx
        self._y1 += dy
        self._y2 += dy


class _Dimension(int):
    def __new__(cls, value: int | str) -> int:
        x = int.__new__(cls, _Dimension._parse_dimension(value)[0])
        return x

    def __init__(self, value: int | str):
        self._dimension, self._unit = _Dimension._parse_dimension(value)
        super().__init__()

    @property
    def unit(self) -> _UNITS:
        return self._unit

    @staticmethod
    def _parse_dimension(dim: str | int) -> tuple[int, _UNITS]:
        if dim == "auto":
            return 0, "auto"

        if isinstance(dim, int):
            return dim, "px"

        for unit in get_args(_UNITS):
            if dim.endswith(unit):
                return int(dim[:-len(unit)]), unit

        raise ValueError(dim)
