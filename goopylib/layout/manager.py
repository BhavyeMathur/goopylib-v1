from __future__ import annotations

import goopylib.layout.align_offset_funcs as align_offset_funcs
from .container import Container
from .flex import Flex


def process(container: Container, x: int = 0, y: int = 0, _only_direct: bool = False):
    if container.parent is not None and container.parent.flex.direction in {"column", "column-reverse"}:
        x, y = y, x

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

    max_child_size = 0
    row_containers = []
    wrap_queue = []

    def _wrap_content() -> None:
        nonlocal main_pos, cross_pos, max_child_size, wrap_queue

        if not _only_direct:
            _main_align_row(flex, main_content_end - main_pos + main_gap, wrap_queue)
            _cross_align_items_line(flex, max_child_size, wrap_queue)

        cross_pos += max_child_size + cross_gap
        main_pos = main_content_start

        row_containers.append(wrap_queue)
        max_child_size = 0
        wrap_queue = []

    if container.flex.direction == "row":
        main_pos = container.content_box.x1
        cross_pos = container.content_box.y1
        main_gap = flex.column_gap
        cross_gap = flex.row_gap
        rendered_main_size = _get_rendered_width

        main_margin = lambda c: c.margin.x
        main_border = lambda c: c.border.x
        cross_margin_size = lambda c: c.margin_box.height
        main_content_start = container.content_box.x1
        main_content_end = container.content_box.x2
        cross_content_end = container.content_box.y2

    elif container.flex.direction == "column":
        main_pos = container.content_box.y1
        cross_pos = container.content_box.x1
        main_gap = flex.row_gap
        cross_gap = flex.column_gap
        rendered_main_size = _get_rendered_height

        main_margin = lambda c: c.margin.y
        main_border = lambda c: c.border.y
        cross_margin_size = lambda c: c.margin_box.width
        main_content_start = container.content_box.y1
        main_content_end = container.content_box.y2
        cross_content_end = container.content_box.x2

    else:
        raise ValueError(container.flex.direction)

    for child in _get_order_sorted_children(container):
        size = rendered_main_size(child) + main_margin(child) + main_border(child)

        if wrap and (main_pos + size > main_content_end):
            _wrap_content()

        if not _only_direct:
            process(child, main_pos, cross_pos, _only_direct=True)

        wrap_queue.append(child)

        max_child_size = max(max_child_size, cross_margin_size(child))
        main_pos += size + main_gap

    if not _only_direct:
        _wrap_content()
        _cross_align(flex, cross_content_end - cross_pos + cross_gap, row_containers)

        for child in container.children:
            _process_flex_items(child, child.flex, False)


def _get_order_sorted_children(container: Container) -> list[Container]:
    children = sorted(container.children, key=lambda child: child.flex.order)

    if container.flex.wrap == "reverse":
        return children[::-1]
    return children


def _main_align_row(flex: Flex, whitespace: int, items: list[Container]) -> None:
    whitespace = _process_flex_grow(flex, whitespace, items)
    if whitespace < 1:
        return

    if flex.align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.align, whitespace, len(items))

    if flex.direction == "row" or flex.direction == "row-reverse":
        shift = lambda c, distance: c.translate(distance, 0)
    else:
        shift = lambda c, distance: c.translate(0, distance)

    for i, child in enumerate(items):
        shift(child, offset(i))


def _process_flex_grow(flex: Flex, whitespace: int, items: list[Container]) -> int:
    if whitespace < 1:
        return whitespace

    grow_sum = sum(child.flex.grow for child in items)

    if flex.direction == "row" or flex.direction == "row-reverse":
        shift_start = lambda c, distance: c.translate_x1(distance)
        shift_end = lambda c, distance: c.translate_x2(distance)
    else:
        shift_start = lambda c, distance: c.translate_y1(distance)
        shift_end = lambda c, distance: c.translate_y2(distance)

    if grow_sum > 0:
        total_grow = max(1, grow_sum)
        offset = 0

        for child in items:
            shift_start(child, int(offset))
            offset += whitespace * (child.flex.grow / total_grow)
            shift_end(child, int(offset))

        return whitespace - int(offset)
    return whitespace


def _cross_align(flex: Flex, whitespace: int, items: list[list[Container]]) -> None:
    if whitespace < 1:
        return
    if flex.cross_align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.cross_align, whitespace, len(items))

    if flex.direction == "row" or flex.direction == "row-reverse":
        shift = lambda c, distance: c.translate(0, distance)
    else:
        shift = lambda c, distance: c.translate(distance, 0)

    for i, row in enumerate(items):
        for child in row:
            shift(child, offset(i))


def _cross_align_items_line(flex: Flex, line_size: int, items: list[Container]) -> None:
    if flex.item_align == "start":
        return

    if flex.direction == "row" or flex.direction == "row-reverse":
        shift = lambda c, func: c.translate(0, func(c.margin_box.height))
    else:
        shift = lambda c, func: c.translate(func(c.margin_box.width), 0)

    offset = align_offset_funcs._get_item_offset(flex.item_align, line_size)
    for child in items:

        if child.flex.cross_align_self is not None:
            if child.flex.cross_align_self == "start":
                continue
            child_offset = align_offset_funcs._get_item_offset(child.flex.cross_align_self, line_size)
            shift(child, child_offset)
            continue

        shift(child, offset)


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


# TODO test with flex direction column
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


def _get_rendered_height(container: Container) -> int:
    if container.height.unit == "px":
        return container.height
    elif container.height.unit == "%":
        return (container.height * container.parent.content_box.height) // 100
    elif container.height.unit == "auto":
        return _get_auto_height(container)
    else:
        raise ValueError()
