from __future__ import annotations
from typing import Literal

_FLEX_WRAP_TYPE = Literal["nowrap", "wrap", "reverse"]
_FLEX_ALIGN_TYPE = Literal["start", "centre", "end", "space-around", "space-between", "space-evenly"]


class _LayoutMode:
    def process_children(self, container: Container, x: int, y: int) -> None:
        raise NotImplemented()


class FlexLayout(_LayoutMode):
    def __init__(self,
                 wrap: _FLEX_WRAP_TYPE = "nowrap",
                 align: _FLEX_ALIGN_TYPE = "centre",
                 cross_align: _FLEX_ALIGN_TYPE = "centre") -> None:
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

    def process_children(self, container: Container, x: int, y: int) -> None:
        container.margin_box.x1 = x
        container.margin_box.y1 = y

        container.border_box.x1 = x + container.margin.left
        container.border_box.y1 = y + container.margin.top

        container.padding_box.x1 = container.border_box.x1 + container.border.left
        container.padding_box.y1 = container.border_box.y1 + container.border.top

        container.content_box.x1 = container.padding_box.x1 + container.padding.left
        container.content_box.y1 = container.padding_box.y1 + container.padding.top

        if container.width.unit == "px":
            container.padding_box.width = container.width
        elif container.width.unit == "%":
            container.padding_box.width = container.width / 100 * container.parent.content_box.width
        else:
            raise ValueError()

        if container.height.unit == "px":
            container.padding_box.height = container.height
        elif container.height.unit == "%":
            container.padding_box.height = container.height / 100 * container.parent.content_box.height
        else:
            raise ValueError()

        container.content_box.width = container.padding_box.width - container.padding.x
        container.border_box.width = container.padding_box.width + container.border.x
        container.margin_box.width = container.border_box.width + container.margin.x

        container.content_box.height = container.padding_box.height - container.padding.y
        container.border_box.height = container.padding_box.height + container.border.y
        container.margin_box.height = container.border_box.height + container.margin.y

        print(container, container.content_box.height)

        x = container.content_box.x1
        y = container.content_box.y1

        for child in (container.children[::-1] if self._wrap == "reverse" else container.children):
            child.layout.process_children(child, x, y)
            x = child.margin_box.x2


class FlowLayout(_LayoutMode):
    def __init__(self) -> None:
        pass

    def process_children(self, container: Container, x: int, y: int) -> None:
        pass


from .container import Container
