from __future__ import annotations
from typing import Literal

_FLEX_WRAP_TYPE = Literal["nowrap", "wrap", "reverse"]
_FLEX_ALIGN_TYPE = Literal["start", "centre", "end", "space-around", "space-between", "space-evenly"]


class _LayoutMode:
    def process_children(self, container: Container, x: int, y: int) -> None:
        raise NotImplemented()

    def get_auto_width(self, container: Container) -> int:
        raise NotImplemented()

    def get_auto_height(self, container: Container) -> int:
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
        elif container.width.unit == "auto":
            container.padding_box.width = container.padding.x + self.get_auto_width(container)
        else:
            raise ValueError()

        if container.height.unit == "px":
            container.padding_box.height = container.height
        elif container.height.unit == "%":
            container.padding_box.height = container.height / 100 * container.parent.content_box.height
        elif container.height.unit == "auto":
            container.padding_box.height = container.padding.y + self.get_auto_height(container)
        else:
            raise ValueError()

        container.content_box.width = container.padding_box.width - container.padding.x
        container.border_box.width = container.padding_box.width + container.border.x
        container.margin_box.width = container.border_box.width + container.margin.x

        container.content_box.height = container.padding_box.height - container.padding.y
        container.border_box.height = container.padding_box.height + container.border.y
        container.margin_box.height = container.border_box.height + container.margin.y

        self._process_flex_items(container)

    def _process_flex_items(self, container: Container):
        x = container.content_box.x1
        y = container.content_box.y1

        max_child_height = 0
        wrap = self._wrap != "nowrap"

        for child in (container.children[::-1] if self._wrap == "reverse" else container.children):

            if wrap:
                if child.width.unit == "px":
                    width = child.width
                elif child.width.unit == "%":
                    width = (child.width * child.parent.content_box.width) // 100
                elif child.width.unit == "auto":
                    width = self.get_auto_width(child)
                else:
                    raise ValueError()
                width += child.margin.x + child.border.x

                if x + width > container.content_box.x2:
                    x = container.content_box.x1
                    y += max_child_height
                    max_child_height = 0

            child.layout.process_children(child, x, y)

            if wrap:
                max_child_height = max(max_child_height, child.margin_box.height)
            x = child.margin_box.x2

    def get_auto_width(self, container: Container) -> int:
        return sum(child.border.x + child.margin.x +
                   (child.width
                    if child.width.unit == "px" else child.padding.x + child.layout.get_auto_width(child))
                   for child in container.children)

    def get_auto_height(self, container: Container) -> int:
        return max(child.border.y + child.margin.y +
                   (child.height
                    if child.height.unit == "px" else child.padding.y + child.layout.get_auto_height(child))
                   for child in container.children)


class FlowLayout(_LayoutMode):
    def __init__(self) -> None:
        pass

    def process_children(self, container: Container, x: int, y: int) -> None:
        pass


from .container import Container
