from __future__ import annotations

import goopylib.layout.align_offset_funcs as align_offset_funcs


def process(container: Container, x: int = 0, y: int = 0, _only_direct: bool = False):
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
        container.padding_box.width = container.padding.x + _get_auto_width(container)
    else:
        raise ValueError()

    container.content_box.width = container.padding_box.width - container.padding.x
    container.border_box.width = container.padding_box.width + container.border.x
    container.margin_box.width = container.border_box.width + container.margin.x

    if container.height.unit == "px":
        container.padding_box.height = container.height
    elif container.height.unit == "%":
        container.padding_box.height = container.height / 100 * container.parent.content_box.height
    elif container.height.unit == "auto":
        container.padding_box.height = container.padding.y + _get_auto_height(container)
    else:
        raise ValueError()

    container.content_box.height = container.padding_box.height - container.padding.y
    container.border_box.height = container.padding_box.height + container.border.y
    container.margin_box.height = container.border_box.height + container.margin.y

    _process_flex_items(container, container.flex, _only_direct)


def _process_flex_items(container: Container, flex: Flex, _only_direct: bool):
    wrap = flex.wrap != "nowrap"

    x = container.content_box.x1
    y = container.content_box.y1

    max_child_height = 0
    row_containers = []

    wrap_queue = []

    xspace = container.content_box.width
    yspace = container.content_box.height

    def _end_row() -> None:
        nonlocal x, y, max_child_height, xspace, yspace, wrap_queue

        x = container.content_box.x1
        y += max_child_height

        _horizontal_align_row(flex, xspace, wrap_queue)
        _align_items_row(flex, max_child_height, wrap_queue)

        row_containers.append(wrap_queue)
        wrap_queue = []

        xspace = container.content_box.width
        yspace -= max_child_height
        max_child_height = 0

    for child in (container.children[::-1] if flex.wrap == "reverse" else container.children):

        if wrap:
            width = _get_container_rendered_width(container) + child.margin.x + child.border.x
            if x + width > container.content_box.x2:
                _end_row()

        if not _only_direct:
            child.process(x, y, True)
            xspace -= child.margin_box.width

        wrap_queue.append(child)

        max_child_height = max(max_child_height, child.margin_box.height)
        x = child.margin_box.x2

    _end_row()
    _vertical_align(flex, yspace, row_containers)

    if not _only_direct:
        for child in container.children:
            child.process(*child.margin_box.start)


def _horizontal_align_row(flex: Flex, whitespace: int, items: list[Container]) -> None:
    if whitespace < 1:
        return
    if flex.align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.align, whitespace, len(items))
    for i, child in enumerate(items):
        child.translate(offset(i), 0)


def _vertical_align(flex: Flex, whitespace: int, items: list[list[Container]]) -> None:
    if whitespace < 1:
        return
    if flex.cross_align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.cross_align, whitespace, len(items))
    for i, row in enumerate(items):
        for child in row:
            child.translate(0, offset(i))


def _align_items_row(flex: Flex, row_height: int, items: list[Container]) -> None:
    if flex.item_align == "start":
        return

    offset = align_offset_funcs._get_item_offset(flex.item_align, row_height)
    for child in items:
        child.translate(0, offset(child.margin_box.height))


def _get_auto_width(container: Container) -> int:
    if len(container.children) == 0:
        return 0

    return sum(child.border.x + child.margin.x +
               (child.width if child.width.unit == "px" else child.padding.x + _get_auto_width(child))
               for child in container.children)


def _get_auto_height(container: Container) -> int:
    if len(container.children) == 0:
        return 0

    if container.flex.wrap != "nowrap" and container.width.unit != "auto":
        height = 0
        max_row_height = 0
        xspace = container.content_box.width

        for child in container.children:
            width = _get_container_rendered_width(container) + child.margin.x + child.border.x
            xspace -= width

            if xspace < 0:
                xspace = container.content_box.width - width
                height += max_row_height
                max_row_height = 0

            max_row_height = max(max_row_height, child.border.y + child.margin.y
                                 + (child.height if child.height.unit == "px"
                                    else child.padding.y + _get_auto_height(child)))

        return height + max_row_height

    return max(child.border.y + child.margin.y +
               (child.height if child.height.unit == "px" else child.padding.y + _get_auto_height(child))
               for child in container.children)


def _get_container_rendered_width(container: Container):
    if container.width.unit == "px":
        return container.width
    elif container.width.unit == "%":
        return (container.width * container.parent.content_box.width) // 100
    elif container.width.unit == "auto":
        return _get_auto_width(container)
    else:
        raise ValueError()
    

from .container import Container
from .flex import Flex
