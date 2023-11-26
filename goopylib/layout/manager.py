from __future__ import annotations

import goopylib.layout.align_offset_funcs as align_offset_funcs
from .container import Container
from .flex import Flex


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

    if container.tag == "square-container":
        pass

    def _end_row() -> None:
        nonlocal x, y, max_child_height, wrap_queue

        if not _only_direct:
            _horizontal_align_row(flex, container.content_box.x2 - x + flex.column_gap, wrap_queue)
            _align_items_row(flex, max_child_height, wrap_queue)

        y += max_child_height + flex.row_gap
        x = container.content_box.x1
        max_child_height = 0

        row_containers.append(wrap_queue)
        wrap_queue = []

    for child in _get_order_sorted_children(container):
        width = _get_rendered_width(child) + child.margin.x + child.border.x

        if wrap:
            if x + width > container.content_box.x2:
                _end_row()

        if not _only_direct:
            process(child, x, y, _only_direct=True)

        wrap_queue.append(child)

        max_child_height = max(max_child_height, child.margin_box.height)
        x += width + flex.column_gap

    if not _only_direct:
        _end_row()
        _vertical_align(flex, container.content_box.y2 - y, row_containers)

        for child in container.children:
            _process_flex_items(child, child.flex, False)


def _get_order_sorted_children(container: Container) -> list[Container]:
    children = sorted(container.children, key=lambda child: child.flex.order)

    if container.flex.wrap == "reverse":
        return children[::-1]
    return children


def _horizontal_align_row(flex: Flex, whitespace: int, items: list[Container]) -> None:
    if whitespace < 1:
        return

    grow_sum = sum(child.flex.grow for child in items)

    if grow_sum > 0:
        total_grow = max(1, grow_sum)
        offset = 0

        for child in items:
            child.translate_x1(int(offset))
            offset += whitespace * (child.flex.grow / total_grow)
            child.translate_x2(int(offset))

        whitespace -= int(offset)

    if grow_sum >= 1:
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
               (child.width
                if child.width.unit == "px" else child.padding.x + _get_auto_width(child))
               for child in container.children) + container.flex.column_gap * (len(container.children) - 1)


def _get_auto_height(container: Container) -> int:
    if len(container.children) == 0:
        return 0

    if container.flex.wrap != "nowrap" and container.width.unit != "auto":
        return _get_auto_wrap_height(container)

    return max(child.border.y + child.margin.y +
               (child.height
                if child.height.unit == "px" else child.padding.y + _get_auto_height(child))
               for child in container.children)


def _get_auto_wrap_height(container: Container) -> int:
    height = 0
    max_row_height = 0
    xspace = container.content_box.width

    for child in container.children:
        width = _get_rendered_width(child) + child.margin.x + child.border.x
        xspace -= width
        if xspace < 0:
            xspace = container.content_box.width - width
            height += max_row_height + container.flex.row_gap
            max_row_height = 0

        max_row_height = max(max_row_height, child.border.y + child.margin.y
                             + (child.height if child.height.unit == "px"
                                else child.padding.y + _get_auto_height(child)))

    return height + max_row_height


def _get_rendered_width(container: Container) -> int:
    if container.width.unit == "px":
        return container.width
    elif container.width.unit == "%":
        return (container.width * container.parent.content_box.width) // 100
    elif container.width.unit == "auto":
        return _get_auto_width(container)
    else:
        raise ValueError()
