from __future__ import annotations
from typing import Literal


_FLEX_WRAP_TYPE = Literal["nowrap", "wrap", "reverse"]
_FLEX_ALIGN_TYPE = Literal["start", "centre", "end", "space-around", "space-between", "space-evenly"]
_FLEX_ITEM_ALIGN_TYPE = Literal["start", "centre", "end"]
_FLEX_DIRECTION_TYPE = Literal["row", "row-reverse", "column", "column-reverse"]


class Flex:
    def __init__(self,
                 wrap: _FLEX_WRAP_TYPE = "nowrap",
                 align: _FLEX_ALIGN_TYPE = "start",
                 cross_align: _FLEX_ALIGN_TYPE = "start",
                 item_align: _FLEX_ITEM_ALIGN_TYPE = "start",
                 row_gap: int = 0,
                 column_gap: int = 0,
                 direction: _FLEX_DIRECTION_TYPE = "row",
                 
                 order: int = 0,
                 grow: float = 0,
                 cross_align_self: None | _FLEX_ALIGN_TYPE = None) -> None:
        self._wrap = wrap
        self._align = align
        self._cross_align = cross_align
        self._item_align = item_align
        self._row_gap = row_gap
        self._column_gap = column_gap
        self._direction = direction

        self._order = order
        self._grow = grow
        self._cross_align_self = cross_align_self

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

    @property
    def item_align(self) -> _FLEX_ALIGN_TYPE:
        return self._item_align

    @item_align.setter
    def item_align(self, value: _FLEX_ITEM_ALIGN_TYPE):
        self._item_align = value

    @property
    def row_gap(self) -> int:
        return self._row_gap

    @row_gap.setter
    def row_gap(self, value: int):
        self._row_gap = value

    @property
    def column_gap(self) -> int:
        return self._column_gap

    @column_gap.setter
    def column_gap(self, value: int):
        self._column_gap = value

    @property
    def direction(self) -> _FLEX_DIRECTION_TYPE:
        return self._direction

    @direction.setter
    def direction(self, value: _FLEX_DIRECTION_TYPE):
        self._direction = value

    @property
    def order(self) -> int:
        return self._order

    @order.setter
    def order(self, value: int):
        self._order = value

    @property
    def grow(self) -> float:
        return self._grow

    @grow.setter
    def grow(self, value: float):
        self._grow = value

    @property
    def cross_align_self(self) -> None | _FLEX_ALIGN_TYPE:
        return self._cross_align_self

    @cross_align_self.setter
    def cross_align_self(self, value: None | _FLEX_ALIGN_TYPE):
        self._cross_align_self = value
