from __future__ import annotations
from typing import Union, Literal, get_args

from .flex import Flex


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


class Container:
    _context_tree: list[Container] = []
    _containers: list[Container] = []  # could consider making a dictionary

    def __init__(self,
                 width: int | str,
                 height: int | str,
                 margin: _LRTB_SETTER_TYPE = (0, 0, 0, 0),
                 padding: _LRTB_SETTER_TYPE = (0, 0, 0, 0),
                 flex: Flex = Flex("nowrap", "start", "start"),
                 min_width: int | str = "auto",
                 min_height: int | str = "auto",
                 max_width: int | str = "100%",
                 max_height: int | str = "100%",
                 tag: str = "") -> None:

        self._width = _Dimension(width)
        self._height = _Dimension(height)

        self._min_width = _Dimension(min_width)
        self._min_height = _Dimension(min_height)
        self._max_width = _Dimension(max_width)
        self._max_height = _Dimension(max_height)

        self._margin = _LRTB(0, 0, 0, 0)  # TODO % margin & padding
        self._padding = _LRTB(0, 0, 0, 0)

        self._margin.set_values(margin)
        self._padding.set_values(padding)

        self._flex = flex

        self._children: list[Container] = []
        self._parent: None | Container = Container._context_tree[-1] if len(Container._context_tree) > 0 else None
        if self._parent:
            self._parent._add_child(self)

        Container._containers.append(self)
        self._tag: str = tag
        self._id: int = len(Container._containers)
        self._layer: int = self._parent.layer + 1 if self._parent else 0

        # rendered attributes
        self._margin_box = _Box()
        self._padding_box = _Box()
        self._content_box = _Box()

    def __repr__(self) -> str:
        return f"Container({self._tag}) @ ({self._padding_box.start})"

    def __enter__(self) -> Container:
        Container._context_tree.append(self)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:
        Container._context_tree.pop()

    def _add_child(self, child) -> None:
        self._children.append(child)

    @property
    def margin_box(self) -> _Box:
        return self._margin_box

    @property
    def padding_box(self) -> _Box:
        return self._padding_box

    @property
    def content_box(self) -> _Box:
        return self._content_box

    @property
    def margin(self) -> _LRTB:
        return self._margin

    @margin.setter
    def margin(self, value: _LRTB_SETTER_TYPE) -> None:
        self._margin.set_values(value)

    @property
    def padding(self) -> _LRTB:
        return self._padding

    @padding.setter
    def padding(self, value: _LRTB_SETTER_TYPE) -> None:
        self._padding.set_values(value)

    @property
    def width(self) -> _Dimension:
        return self._width

    @width.setter
    def width(self, value: int | str) -> None:
        self._width = _Dimension(value)

    @property
    def height(self) -> _Dimension:
        return self._height

    @height.setter
    def height(self, value: int | str) -> None:
        self._height = _Dimension(value)

    @property
    def min_width(self) -> _Dimension:
        return self._min_width

    @min_width.setter
    def min_width(self, value: int | str) -> None:
        self._min_width = _Dimension(value)

    @property
    def min_height(self) -> _Dimension:
        return self._min_height

    @min_height.setter
    def min_height(self, value: int | str) -> None:
        self._min_height = _Dimension(value)

    @property
    def max_width(self) -> _Dimension:
        return self._max_width

    @max_width.setter
    def max_width(self, value: int | str) -> None:
        self._max_width = _Dimension(value)

    @property
    def max_height(self) -> _Dimension:
        return self._max_height

    @max_height.setter
    def max_height(self, value: int | str) -> None:
        self._max_height = _Dimension(value)

    @property
    def tag(self) -> str:
        return self._tag

    @property
    def layer(self) -> int:
        return self._layer

    @property
    def children(self) -> tuple[Container, ...]:
        return tuple(self._children)

    @property
    def parent(self) -> Container | None:
        return self._parent

    @property
    def flex(self) -> Flex:
        return self._flex

    @flex.setter
    def flex(self, value: Flex) -> None:
        self._flex = value

    @property
    def id(self) -> int:
        return self._id

    def translate(self, dx: int, dy: int) -> None:
        self.margin_box.translate(dx, dy)
        self.padding_box.translate(dx, dy)
        self.content_box.translate(dx, dy)

    def translate_x1(self, dx: int) -> None:
        self.margin_box.x1 += dx
        self.padding_box.x1 += dx
        self.content_box.x1 += dx

    def translate_x2(self, dx: int) -> None:
        self.margin_box.x2 += dx
        self.padding_box.x2 += dx
        self.content_box.x2 += dx

    def translate_y1(self, dy: int) -> None:
        self.margin_box.y1 += dy
        self.padding_box.y1 += dy
        self.content_box.y1 += dy

    def translate_y2(self, dy: int) -> None:
        self.margin_box.y2 += dy
        self.padding_box.y2 += dy
        self.content_box.y2 += dy

    @staticmethod
    def get_containers() -> tuple[Container, ...]:
        return tuple(Container._containers)
