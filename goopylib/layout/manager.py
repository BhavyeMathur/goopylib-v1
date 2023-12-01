from __future__ import annotations

import goopylib.layout.align_offset_funcs as align_offset_funcs
from .container import Container, _Dimension
from .flex import Flex


def process(container: Container, x: int = 0, y: int = 0, _only_direct: bool = False):
    _rendered_width_cache[None].clear()
    _rendered_width_cache["min_width"].clear()
    _rendered_width_cache["max_width"].clear()
    _rendered_height_cache[None].clear()
    _rendered_height_cache["min_height"].clear()
    _rendered_height_cache["max_height"].clear()

    if container.parent is not None and container.parent.flex.direction in {"column", "column-reverse"}:
        x, y = y, x

    container.margin_box.x1 = x
    container.margin_box.y1 = y

    container.padding_box.x1 = x + container.margin.left
    container.padding_box.y1 = y + container.margin.top

    container.content_box.x1 = container.padding_box.x1 + container.padding.left
    container.content_box.y1 = container.padding_box.y1 + container.padding.top

    container.padding_box.width = _get_rendered_width(container)
    container.content_box.width = container.padding_box.width - container.padding.x
    container.margin_box.width = container.padding_box.width + container.margin.x

    container.padding_box.height = _get_rendered_height(container)
    container.content_box.height = container.padding_box.height - container.padding.y
    container.margin_box.height = container.padding_box.height + container.margin.y

    if not _only_direct:
        _process_flex_items(container, container.flex)


def _process_flex_items(container: Container, flex: Flex):
    wrap = flex.wrap != "nowrap"

    if container.tag == "test":
        pass

    max_child_size = 0
    row_containers = []
    wrap_queue = []

    def _wrap_content() -> None:
        nonlocal main_pos, cross_pos, max_child_size, wrap_queue

        _main_align_row(flex, direction, direction * (main_content_end - main_pos) + main_gap, wrap_queue)
        _cross_align_items_line(flex, max_child_size, wrap_queue)

        cross_pos += max_child_size + cross_gap
        main_pos = main_content_start

        row_containers.append(wrap_queue)
        max_child_size = 0
        wrap_queue = []

    if container.flex.direction.startswith("row"):
        main_pos = container.content_box.x1
        cross_pos = container.content_box.y1
        main_gap = flex.column_gap
        cross_gap = flex.row_gap
        rendered_main_size = _get_rendered_width

        main_margin = lambda c: c.margin.x
        cross_margin_size = lambda c: c.margin_box.height
        main_content_end = container.content_box.x2
        cross_content_end = container.content_box.y2

    elif container.flex.direction.startswith("column"):
        main_pos = container.content_box.y1
        cross_pos = container.content_box.x1
        main_gap = flex.row_gap
        cross_gap = flex.column_gap
        rendered_main_size = _get_rendered_height

        main_margin = lambda c: c.margin.y
        cross_margin_size = lambda c: c.margin_box.width
        main_content_end = container.content_box.y2
        cross_content_end = container.content_box.x2

    else:
        raise ValueError(container.flex.direction)

    if container.flex.direction.endswith("reverse"):
        main_pos, main_content_end = main_content_end, main_pos
        direction = -1

        def _wrap_check() -> bool:
            return main_pos - size < main_content_end

        def _child_main_pos() -> int:
            return main_pos - size
    else:
        direction = 1

        def _wrap_check() -> bool:
            return main_pos + size > main_content_end

        def _child_main_pos() -> int:
            return main_pos

    main_content_start = main_pos

    for child in _get_order_sorted_children(container):
        size = rendered_main_size(child) + main_margin(child)

        if wrap and _wrap_check():
            _wrap_content()

        process(child, _child_main_pos(), cross_pos, _only_direct=True)

        wrap_queue.append(child)

        max_child_size = max(max_child_size, cross_margin_size(child))
        main_pos += direction * (size + main_gap)

    _wrap_content()
    _cross_align(flex, cross_content_end - cross_pos + cross_gap, row_containers)

    for child in container.children:
        _process_flex_items(child, child.flex)


def _get_order_sorted_children(container: Container) -> list[Container]:
    children = sorted(container.children, key=lambda child: child.flex.order)

    if container.flex.wrap == "reverse":
        return children[::-1]
    return children


def _main_align_row(flex: Flex, direction: int, whitespace: int, items: list[Container]) -> None:
    whitespace = _process_flex_grow(flex, whitespace, items)
    if whitespace < 1:
        return

    if flex.align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.align, whitespace, len(items))

    if flex.direction == "row" or flex.direction == "row-reverse":
        shift = lambda c, distance: c.translate(direction * distance, 0)
    else:
        shift = lambda c, distance: c.translate(0, direction * distance)

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

    if container.flex.direction == "column" or container.flex.direction == "column-reverse":
        if container.flex.wrap != "nowrap" and container.height.unit != "auto":
            return _get_auto_wrap_size(container)

    children_sizes = (child.margin.x + _get_rendered_width(child) for child in container.children)

    if container.flex.direction == "column" or container.flex.direction == "column-reverse":
        return max(children_sizes)

    return sum(children_sizes) + container.flex.column_gap * (len(container.children) - 1)


def _get_auto_height(container: Container) -> int:
    if len(container.children) == 0:
        return 0

    if container.flex.direction == "row" or container.flex.direction == "row-reverse":
        if container.flex.wrap != "nowrap" and container.width.unit != "auto":
            return _get_auto_wrap_size(container)

    children_sizes = (child.margin.y + _get_rendered_height(child) for child in container.children)

    if container.flex.direction == "row" or container.flex.direction == "row-reverse":
        return max(children_sizes)

    return sum(children_sizes) + container.flex.row_gap * (len(container.children) - 1)


def _get_auto_wrap_size(container: Container) -> int:
    size = 0
    max_line_size = 0

    if container.flex.direction == "row" or container.flex.direction == "row-reverse":
        main_size = _get_rendered_width(container)
        cross_gap = container.flex.row_gap
        cross_size = lambda c: c.margin.y + _get_rendered_height(c)
    else:
        main_size = _get_rendered_height(container)
        cross_gap = container.flex.column_gap
        cross_size = lambda c: c.margin.x + _get_rendered_width(c)

    space = main_size

    for child in container.children:
        child_size = _get_rendered_width(child) + child.margin.x
        space -= child_size
        if space < 0:
            space = main_size - child_size
            size += max_line_size + cross_gap
            max_line_size = 0

        max_line_size = max(max_line_size, cross_size(child))

    return size + max_line_size


_rendered_width_cache = {None: {}, "min_width": {}, "max_width": {}}
_rendered_height_cache = {None: {}, "min_height": {}, "max_height": {}}


def _get_rendered_width(container: Container, attr: None | str = None) -> int:
    cached = _rendered_width_cache[attr].get(container)
    if cached:
        return cached

    width = container.width if attr is None else getattr(container, attr)

    if width.unit == "px":
        return_val = width
    elif width.unit == "%":
        if attr == "max_width" and (container.parent is None or container.parent.width.unit == "auto"):
            return_val = 2147483647
        else:
            return_val = _width_percentage_to_pixels(container, width)
    elif width.unit == "auto":
        if attr == "min_width":
            return_val = -1
        else:
            return_val = container.padding.x + _get_auto_width(container)
    else:
        raise ValueError()

    if attr is not None:
        _rendered_width_cache[attr][container] = return_val
        return return_val

    min_width = _get_rendered_width(container, "min_width")
    max_width = _get_rendered_width(container, "max_width")
    if min_width > max_width:
        return_val = 0

    return_val = min(max(return_val, min_width), max_width)
    _rendered_width_cache[attr][container] = return_val
    return return_val


def _width_percentage_to_pixels(container: Container, width: _Dimension) -> int:
    if container.parent is None:
        return 0
    if container.parent.width.unit == "auto":
        return 0  # TODO go through all non-auto sister elements, then figure out %

    parent_content_width = _get_rendered_width(container.parent) - container.parent.padding.x
    return min((width * parent_content_width) // 100, parent_content_width - container.margin.x)


def _get_rendered_height(container: Container, attr: None | str = None) -> int:
    cached = _rendered_height_cache[attr].get(container)
    if cached:
        return cached

    height = container.height if attr is None else getattr(container, attr)

    if height.unit == "px":
        return_val = height
    elif height.unit == "%":
        if attr == "max_height" and (container.parent is None or container.parent.height.unit == "auto"):
            return_val = 2147483647
        else:
            return_val = _height_percentage_to_pixels(container, height)
    elif height.unit == "auto":
        if attr == "min_height":
            return_val = -1
        else:
            return_val = container.padding.y + _get_auto_height(container)
    else:
        raise ValueError()

    if attr is not None:
        _rendered_height_cache[attr][container] = return_val
        return return_val

    min_height = _get_rendered_height(container, "min_height")
    max_height = _get_rendered_height(container, "max_height")

    return_val = min(max(return_val, min_height), max_height)
    _rendered_height_cache[attr][container] = return_val
    return return_val


def _height_percentage_to_pixels(container: Container, height: _Dimension) -> int:
    if container.parent is None:
        return 0
    if container.parent.height.unit == "auto":
        return 0

    parent_content_height = _get_rendered_height(container.parent) - container.parent.padding.y
    return min((height * parent_content_height) // 100, parent_content_height - container.margin.y)
