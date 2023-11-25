from __future__ import annotations
from typing import Literal

from .container import Container


_FLEX_WRAP_TYPE = Literal["nowrap", "wrap", "reverse"]
_FLEX_ALIGN_TYPE = Literal["start", "centre", "end", "space-around", "space-between", "space-evenly"]
_FLEX_ITEM_ALIGN_TYPE = Literal["start", "centre", "end"]


class Flex:
    def __init__(self,
                 wrap: _FLEX_WRAP_TYPE = "nowrap",
                 align: _FLEX_ALIGN_TYPE = "start",
                 cross_align: _FLEX_ALIGN_TYPE = "start",
                 item_align: _FLEX_ITEM_ALIGN_TYPE = "start") -> None:
        self._wrap = wrap
        self._align = align
        self._cross_align = cross_align
        self._item_align = item_align

        self._container = None

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
        return self._item_align

    @cross_align.setter
    def cross_align(self, value: _FLEX_ALIGN_TYPE):
        self._item_align = value

    @property
    def item_align(self) -> _FLEX_ALIGN_TYPE:
        return self._item_align

    @item_align.setter
    def item_align(self, value: _FLEX_ITEM_ALIGN_TYPE):
        self._item_align = value

    def process_children(self, x: int, y: int, _only_direct: bool = False) -> None:
        _FlexManager(self._container, self).process_children(x, y, _only_direct)


from .flex_manager import _FlexManager
