"""
Flex propreties object for the layout engine
"""

from __future__ import annotations
from typing import Literal, Optional


# pylint: disable=invalid-name

_FLEX_WRAP_TYPE = Literal["nowrap", "wrap", "reverse"]
_FLEX_ALIGN_TYPE = Literal["start", "centre", "end", "space-around", "space-between", "space-evenly"]
_FLEX_ITEM_ALIGN_TYPE = Literal["start", "centre", "end"]
_FLEX_DIRECTION_TYPE = Literal["row", "row-reverse", "column", "column-reverse"]

# pylint: enable=invalid-name


class Flex:
    """
    A class storing a container's flex properties
    """

    __slots__ = ["_wrap", "_align", "_cross_align", "_item_align", "_row_gap", "_column_gap", "_direction", "_order",
                 "_grow", "_cross_align_self"]

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
                 cross_align_self: Optional[_FLEX_ALIGN_TYPE] = None) -> None:
        """
        A class storing a container's flex properties
        
        Args:
            wrap: type of flex-wrap ("nowrap", "wrap", or "reverse")
            align: alignment along primary axis
            cross_align: alignment along secondary axis
            item_align: alignment of children container along secondary axis ("start", "centre", or "end")
            row_gap: gap between each row
            column_gap: gap between each column
            direction: direction of flex ("row", "column" or "*-reverse")
            
            order: the order of this container in parent's flexbox
            grow: the amount this container grows to occupy space in the parent's flexbox
            cross_align_self: alignment of this container to override parent's "item_align" property
        """
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
        """
        Type of flex-wrap ("nowrap", "wrap", or "reverse")
        """
        return self._wrap

    @wrap.setter
    def wrap(self, value: _FLEX_WRAP_TYPE):
        self._wrap = value

    @property
    def align(self) -> _FLEX_ALIGN_TYPE:
        """
        Alignment along primary axis
        """
        return self._align

    @align.setter
    def align(self, value: _FLEX_ALIGN_TYPE):
        self._align = value

    @property
    def cross_align(self) -> _FLEX_ALIGN_TYPE:
        """
        Alignment along secdonary axis
        """
        return self._cross_align

    @cross_align.setter
    def cross_align(self, value: _FLEX_ALIGN_TYPE):
        self._cross_align = value

    @property
    def item_align(self) -> _FLEX_ALIGN_TYPE:
        """
        Alignment of children container along secondary axis ("start", "centre", or "end")
        """
        return self._item_align

    @item_align.setter
    def item_align(self, value: _FLEX_ITEM_ALIGN_TYPE):
        self._item_align = value

    @property
    def row_gap(self) -> int:
        """
        The gap between each row
        """
        return self._row_gap

    @row_gap.setter
    def row_gap(self, value: int):
        self._row_gap = value

    @property
    def column_gap(self) -> int:
        """
        The gap between each column
        """
        return self._column_gap

    @column_gap.setter
    def column_gap(self, value: int):
        self._column_gap = value

    @property
    def direction(self) -> _FLEX_DIRECTION_TYPE:
        """
        Direction of flex ("row", "column" or "*-reverse")
        """
        return self._direction

    @direction.setter
    def direction(self, value: _FLEX_DIRECTION_TYPE):
        self._direction = value

    @property
    def order(self) -> int:
        """
        The order of this container in parent's flexbox
        """
        return self._order

    @order.setter
    def order(self, value: int):
        self._order = value

    @property
    def grow(self) -> float:
        """
        The amount this container grows to occupy space in the parent's flexbox
        """
        return self._grow

    @grow.setter
    def grow(self, value: float):
        self._grow = value

    @property
    def cross_align_self(self) -> Optional[_FLEX_ALIGN_TYPE]:
        """
        Alignment of this container along the secondary axis to override parent's "item_align" property
        """
        return self._cross_align_self

    @cross_align_self.setter
    def cross_align_self(self, value: Optional[_FLEX_ALIGN_TYPE]):
        self._cross_align_self = value
