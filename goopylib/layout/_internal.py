"""
Internal classes used for processing goopylib layouts
"""

from __future__ import annotations
from typing import Union, Literal, Tuple, get_args

# pylint: disable=invalid-name
# pylint: disable=unsubscriptable-object

_UNITS = Literal["px", "%", "auto"]
_LRTB_SETTER_TYPE = Union[int, Tuple[int], Tuple[int, int], Tuple[int, int, int], Tuple[int, int, int, int]]

# pylint: enable=invalid-name


class _LRTB:

    __slots__ = ["_left", "_right", "_top", "_bottom", "_x", "_y"]

    def __init__(self, left: int, right: int, top: int, bottom: int):
        self._left = left
        self._right = right
        self._top = top
        self._bottom = bottom

        self._x = self._left + self._right
        self._y = self._top + self._bottom

    @property
    def left(self) -> int:
        """
        The leftward size of the frame
        """
        return self._left

    @left.setter
    def left(self, value: int):
        self._left = value
        self._x = self._left + self._right

    @property
    def right(self) -> int:
        """
        The rightward size of the frame
        """
        return self._right

    @right.setter
    def right(self, value: int):
        self._right = value
        self._x = self._left + self._right

    @property
    def top(self) -> int:
        """
        The upward size of the frame
        """
        return self._top

    @top.setter
    def top(self, value: int):
        self._top = value
        self._y = self._top + self._bottom

    @property
    def bottom(self) -> int:
        """
        The downward size of the frame
        """
        return self._bottom

    @bottom.setter
    def bottom(self, value: int):
        self._bottom = value
        self._y = self._top + self._bottom

    @property
    def x(self) -> int:
        """
        The width of the frame
        """
        return self._x

    @property
    def y(self) -> int:
        """
        The height of the frame
        """
        return self._y

    def set_values(self, value: _LRTB_SETTER_TYPE) -> None:
        """
        Sets the left, right, top, and bottom sizes of the frame

        Args:
            value: a tuple of values
        """
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
        """
        The start x-position of the box
        """
        return self._x1

    @x1.setter
    def x1(self, value: int):
        self._x1 = value
        self._width = self._x2 - self._x1

    @property
    def y1(self) -> int:
        """
        The start y-position of the box
        """
        return self._y1

    @y1.setter
    def y1(self, value: int):
        self._y1 = value
        self._height = self._y2 - self._y1

    @property
    def x2(self) -> int:
        """
        The end x-position of the box
        """
        return self._x2

    @x2.setter
    def x2(self, value: int):
        self._x2 = value
        self._width = self._x2 - self._x1

    @property
    def y2(self) -> int:
        """
        The end y-position of the box
        """
        return self._y2

    @y2.setter
    def y2(self, value: int):
        self._y2 = value
        self._height = self._y2 - self._y1

    @property
    def width(self) -> int:
        """
        The width of the box
        """
        return self._width

    @width.setter
    def width(self, value: int):
        self._x2 = self._x1 + value
        self._width = value

    @property
    def height(self) -> int:
        """
        The height of the box
        """
        return self._height

    @height.setter
    def height(self, value: int):
        self._y2 = self._y1 + value
        self._height = value

    @property
    def start(self) -> Tuple[int, int]:
        """
        The start coordinates (x, y) of the box
        """
        return self._x1, self._y1

    @property
    def end(self) -> Tuple[int, int]:
        """
        The end coordinates (x, y) of the box
        """
        return self._x2, self._y2

    def translate(self, dx: int, dy: int) -> None:
        """
        Moves the box by (dx, dy)

        Args:
            dx: the x amount to move
            dy: the y amount to move
        """
        self._x1 += dx
        self._x2 += dx
        self._y1 += dy
        self._y2 += dy


class _Dimension(int):

    __slots__ = ["_dimension", "_unit"]

    def __new__(cls, value: Union[int, str]) -> int:
        x = int.__new__(cls, _Dimension._parse_dimension(value)[0])
        return x

    def __init__(self, value: Union[int, str]):
        self._dimension, self._unit = _Dimension._parse_dimension(value)
        super().__init__()

    @property
    def unit(self) -> _UNITS:
        """
        The unit of the dimension (%, px, etc.)
        """
        return self._unit

    @staticmethod
    def _parse_dimension(dim: Union[int, str]) -> Tuple[int, _UNITS]:
        if dim == "auto":
            return 0, "auto"

        if isinstance(dim, int):
            return dim, "px"

        for unit in get_args(_UNITS):
            if dim.endswith(unit):
                return int(dim[:-len(unit)]), unit

        raise ValueError(dim)


# pylint: enable=unsubscriptable-object
