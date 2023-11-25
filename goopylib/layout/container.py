from __future__ import annotations
from typing import Literal, get_args, Union

_UNITS = Literal["px", "%"]
_DISPLAY_OPTIONS = Literal["flex"]
_FLEX_WRAP_TYPE = Literal["nowrap", "wrap", "reverse"]
_FLEX_ALIGN_TYPE = Literal["start", "centre", "end", "space-around", "space-between", "space-evenly"]

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

    @property
    def height(self) -> int:
        return self._height

    @property
    def start(self) -> tuple[int, int]:
        return self._x1, self._y1

    @property
    def end(self) -> tuple[int, int]:
        return self._x2, self._y2


class Dimension:
    def __init__(self, dimension: str | int):
        self._dimension, self._unit = Dimension._parse_dimension(dimension)

    @property
    def unit(self) -> _UNITS:
        return self._unit

    @staticmethod
    def _parse_dimension(dim: str | int) -> tuple[int, _UNITS]:
        if isinstance(dim, int):
            return dim, "px"

        for unit in get_args(_UNITS):
            if dim.endswith(unit):
                return int(dim[:-len(unit)]), unit

        raise ValueError(dim)


class FlexProps:
    def __init__(self, wrap: _FLEX_WRAP_TYPE, align: _FLEX_ALIGN_TYPE, cross_align: _FLEX_ALIGN_TYPE):
        self._wrap = wrap
        self._align = align
        self._cross_align = cross_align

    @property
    def wrap(self) -> _FLEX_WRAP_TYPE:
        return self._wrap

    @wrap.setter
    def wrap(self, value: _FLEX_WRAP_TYPE):
        self._wrap = value

    @property
    def align(self) -> _FLEX_ALIGN_TYPE:
        return self._align

    @align.setter
    def align(self, value: _FLEX_ALIGN_TYPE):
        self._align = value

    @property
    def cross_align(self) -> _FLEX_ALIGN_TYPE:
        return self._cross_align

    @cross_align.setter
    def cross_align(self, value: _FLEX_ALIGN_TYPE):
        self._cross_align = value


class Container:
    _context_tree: list[Container] = []
    _containers: list[Container] = []  # could consider making a dictionary

    def __init__(self, width, height, tag: str = "") -> None:
        self._width = Dimension(width)
        self._height = Dimension(height)

        self._margin = _LRTB(0, 0, 0, 0)
        self._border = _LRTB(0, 0, 0, 0)
        self._padding = _LRTB(0, 0, 0, 0)

        self._display: _DISPLAY_OPTIONS = "flex"
        self._flex = FlexProps("nowrap", "start", "start")

        self._children: list[Container] = []
        self._parent: None | Container = Container._context_tree[-1] if len(Container._context_tree) > 0 else None
        if self._parent:
            self._parent._add_child(self)

        Container._containers.append(self)
        self._tag: str = tag

        # rendered attributes
        self._margin_box = _Box()
        self._border_box = _Box()
        self._padding_box = _Box()
        self._content_box = _Box()

        # debug attributes
        self.color = None

    def __repr__(self) -> str:
        return f"Container({self._tag}) @ ({self._border_box.start})"

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
    def border_box(self) -> _Box:
        return self._border_box

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
        self._margin.set_values(value)

    @property
    def border(self) -> _LRTB:
        return self._border

    @border.setter
    def border(self, value: _LRTB_SETTER_TYPE) -> None:
        self._margin.set_values(value)

    @property
    def display(self) -> _DISPLAY_OPTIONS:
        return self._display

    @property
    def flex(self) -> FlexProps:
        return self._flex

    @property
    def tag(self) -> str:
        return self._tag

    @property
    def children(self) -> tuple[Container, ...]:
        return tuple(self._children)

    @property
    def parent(self) -> Container | None:
        return self._parent

    @staticmethod
    def get_containers() -> tuple[Container, ...]:
        return tuple(Container._containers)
