from __future__ import annotations

from .flex import Flex
from ._internal import _Box, _LRTB, _Dimension, _LRTB_SETTER_TYPE


class Div:
    _context_tree: list[Div] = []
    _instances: list[Div] = []  # could consider making a dictionary

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
                 classes: str | list[str] = "") -> None:

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

        self._children: list[Div] = []
        self._parent: None | Div = Div._context_tree[-1] if len(Div._context_tree) > 0 else None
        if self._parent:
            self._parent._add_child(self)

        Div._instances.append(self)
        self._classes: list[str] = classes.copy() if isinstance(classes, list) else classes.split()
        self._layer: int = self._parent.layer + 1 if self._parent else 0

        # rendered attributes
        self._margin_box = _Box()
        self._padding_box = _Box()
        self._content_box = _Box()

    def __repr__(self) -> str:
        return f"Div({self._classes}) @ ({self._padding_box.start})"

    def __enter__(self) -> Div:
        Div._context_tree.append(self)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:
        Div._context_tree.pop()

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
    def classes(self) -> list[str]:
        return self._classes

    @property
    def layer(self) -> int:
        return self._layer

    @property
    def children(self) -> tuple[Div, ...]:
        return tuple(self._children)

    @property
    def parent(self) -> Div | None:
        return self._parent

    @property
    def flex(self) -> Flex:
        return self._flex

    @flex.setter
    def flex(self, value: Flex) -> None:
        self._flex = value

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
    def get_instances() -> tuple[Div, ...]:
        return tuple(Div._instances)
