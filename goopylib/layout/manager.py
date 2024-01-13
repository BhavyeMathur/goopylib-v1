"""
Module with functions to manage goopylib's layout engine
"""

from __future__ import annotations
from typing import List, Optional

from goopylib.layout import align_offset_funcs
from .div import Div
from ._internal import _Dimension
from .flex import Flex


_row_directions = {"row", "row-reverse"}
_column_directions = {"column", "column-reverse"}
_reverse_directions = {"row-reverse", "column-reverse"}


# TODO - Add responsive layouts at different screen sizes (not for v2.0)


def process(div: Div, x: int = 0, y: int = 0, _only_direct: bool = False) -> None:
    """
    Recursively processes a goopylib layout

    Args:
        div: the parent container
        x: the start x-position
        y: the start y-position

        _only_direct: internal use only
    """
    if div.parent is not None and div.parent.flex.direction in _column_directions:
        x, y = y, x

    div.margin_box.x1 = x
    div.margin_box.y1 = y

    div.padding_box.x1 = x + div.margin.left
    div.padding_box.y1 = y + div.margin.top

    div.content_box.x1 = div.padding_box.x1 + div.padding.left
    div.content_box.y1 = div.padding_box.y1 + div.padding.top

    div.padding_box.width = _get_rendered_width(div)
    div.content_box.width = div.padding_box.width - div.padding.x
    div.margin_box.width = div.padding_box.width + div.margin.x

    div.padding_box.height = _get_rendered_height(div)
    div.content_box.height = div.padding_box.height - div.padding.y
    div.margin_box.height = div.padding_box.height + div.margin.y

    if not _only_direct:
        global _rendered_width_cache, _rendered_height_cache

        _rendered_width_cache = {None: {}, "min_width": {}, "max_width": {}}
        _rendered_height_cache = {None: {}, "min_height": {}, "max_height": {}}

        _process_flex_items(div, div.flex)


def _process_flex_items(div: Div, flex: Flex) -> None:
    wrap = flex.wrap != "nowrap"

    if div.classes == "test":
        pass

    max_child_size = 0
    row_divs = []
    wrap_queue = []

    def _wrap_content() -> None:
        nonlocal main_pos, cross_pos, max_child_size, wrap_queue

        _main_align_row(flex, direction, direction * (main_content_end - main_pos) + main_gap, wrap_queue)
        _cross_align_items_line(flex, max_child_size, wrap_queue)

        cross_pos += max_child_size + cross_gap
        main_pos = main_content_start

        row_divs.append(wrap_queue)
        max_child_size = 0
        wrap_queue = []

    if div.flex.direction in _row_directions:
        main_pos = div.content_box.x1
        cross_pos = div.content_box.y1
        main_gap = flex.column_gap
        cross_gap = flex.row_gap
        rendered_main_size = _get_rendered_width

        main_margin = lambda c: c.margin.x
        cross_margin_size = lambda c: c.margin_box.height
        main_content_end = div.content_box.x2
        cross_content_end = div.content_box.y2

    elif div.flex.direction in _column_directions:
        main_pos = div.content_box.y1
        cross_pos = div.content_box.x1
        main_gap = flex.row_gap
        cross_gap = flex.column_gap
        rendered_main_size = _get_rendered_height

        main_margin = lambda c: c.margin.y
        cross_margin_size = lambda c: c.margin_box.width
        main_content_end = div.content_box.y2
        cross_content_end = div.content_box.x2

    else:
        raise ValueError(div.flex.direction)

    if div.flex.direction in _reverse_directions:
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

    for child in _get_order_sorted_children(div):
        size = rendered_main_size(child) + main_margin(child)

        if wrap and _wrap_check():
            _wrap_content()

        process(child, _child_main_pos(), cross_pos, _only_direct=True)

        wrap_queue.append(child)

        max_child_size = max(max_child_size, cross_margin_size(child))
        main_pos += direction * (size + main_gap)

    _wrap_content()
    _cross_align(flex, cross_content_end - cross_pos + cross_gap, row_divs)

    for child in div.children:
        _process_flex_items(child, child.flex)


def _get_order_sorted_children(div: Div) -> List[Div]:
    children = sorted(div.children, key=lambda child: child.flex.order)

    if div.flex.wrap == "reverse":
        return children[::-1]
    return children


def _main_align_row(flex: Flex, direction: int, whitespace: int, items: List[Div]) -> None:
    whitespace = _process_flex_grow(flex, whitespace, items)
    if whitespace < 1:
        return

    if flex.align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.align, whitespace, len(items))

    if flex.direction in _row_directions:
        shift = lambda c, distance: c.translate(direction * distance, 0)
    else:
        shift = lambda c, distance: c.translate(0, direction * distance)

    for i, child in enumerate(items):
        shift(child, offset(i))


def _process_flex_grow(flex: Flex, whitespace: int, items: List[Div]) -> int:
    if whitespace < 1:
        return whitespace

    grow_sum = sum(child.flex.grow for child in items)

    if flex.direction in _row_directions:
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


def _cross_align(flex: Flex, whitespace: int, items: List[List[Div]]) -> None:
    if whitespace < 1:
        return
    if flex.cross_align == "start":
        return

    offset = align_offset_funcs._get_offset(flex.cross_align, whitespace, len(items))

    if flex.direction in _row_directions:
        shift = lambda c, distance: c.translate(0, distance)
    else:
        shift = lambda c, distance: c.translate(distance, 0)

    for i, row in enumerate(items):
        for child in row:
            shift(child, offset(i))


def _cross_align_items_line(flex: Flex, line_size: int, items: List[Div]) -> None:
    if flex.item_align == "start":
        return

    if flex.direction in _row_directions:
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


def _get_auto_width(div: Div, attr: Optional[str]) -> int:
    if attr == "min_width":
        return -1
    if len(div.children) == 0:
        return div.padding.x

    if div.flex.direction in _column_directions:
        if div.flex.wrap != "nowrap" and div.height.unit != "auto":
            return div.padding.x + _get_auto_wrap_size(div)

    children_sizes = (child.margin.x + _get_rendered_width(child) for child in div.children)

    if div.flex.direction in _column_directions:
        return div.padding.x + max(children_sizes)

    return div.padding.x + sum(children_sizes) + div.flex.column_gap * (len(div.children) - 1)


def _get_auto_height(div: Div, attr: Optional[str]) -> int:
    if attr == "min_height":
        return -1
    if len(div.children) == 0:
        return div.padding.y

    if div.flex.direction in _row_directions:
        if div.flex.wrap != "nowrap" and div.width.unit != "auto":
            return div.padding.y + _get_auto_wrap_size(div)

    children_sizes = (child.margin.y + _get_rendered_height(child) for child in div.children)

    if div.flex.direction in _row_directions:
        return div.padding.y + max(children_sizes)

    return div.padding.y + sum(children_sizes) + div.flex.row_gap * (len(div.children) - 1)


def _get_auto_wrap_size(div: Div) -> int:
    size = 0
    max_line_size = 0

    if div.flex.direction in _row_directions:
        main_size = _get_rendered_width(div)
        cross_gap = div.flex.row_gap
        cross_size = lambda c: c.margin.y + _get_rendered_height(c)
    else:
        main_size = _get_rendered_height(div)
        cross_gap = div.flex.column_gap
        cross_size = lambda c: c.margin.x + _get_rendered_width(c)

    space = main_size

    for child in div.children:
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


def _get_rendered_width(div: Div, attr: Optional[str] = None) -> int:
    cached = _rendered_width_cache[attr].get(div)
    if cached is not None:
        return cached

    width = div.width if attr is None else getattr(div, attr)

    if width.unit == "px":
        return_val = width
    elif width.unit == "%":
        return_val = _width_percentage_to_pixels(div, attr, width)
    elif width.unit == "auto":
        return_val = div.padding.x + _get_auto_width(div, attr)
    else:
        raise ValueError()

    if attr is None:
        return_val = _get_clamped_width(div, return_val)

    _rendered_width_cache[attr][div] = return_val
    return return_val


def _get_clamped_width(div: Div, width: int) -> int:
    min_width = _get_rendered_width(div, "min_width")
    max_width = _get_rendered_width(div, "max_width")

    if min_width > max_width:
        width = 0
    else:
        width = min(max(width, min_width), max_width)

    return width


def _width_percentage_to_pixels(div: Div, attr: Optional[str], width: _Dimension) -> int:
    if attr == "max_width" and (div.parent is None or div.parent.width.unit == "auto"):
        return 2147483647
    if div.parent is None:
        return 0
    if div.parent.width.unit == "auto":
        return 0  # TODO ? go through all non-auto sister elements, then figure out % (not for v2.0)

    parent_content_width = _get_rendered_width(div.parent) - div.parent.padding.x
    return min((width * parent_content_width) // 100, parent_content_width - div.margin.x)


def _get_rendered_height(div: Div, attr: Optional[str] = None) -> int:
    cached = _rendered_height_cache[attr].get(div)
    if cached:
        return cached

    height = div.height if attr is None else getattr(div, attr)

    if height.unit == "px":
        return_val = height
    elif height.unit == "%":
        return_val = _height_percentage_to_pixels(div, attr, height)
    elif height.unit == "auto":
        return_val = _get_auto_height(div, attr)
    else:
        raise ValueError()

    if attr is not None:
        return_val = _get_clamped_height(div, return_val)

    _rendered_height_cache[attr][div] = return_val
    return return_val


def _get_clamped_height(div: Div, height: int) -> int:
    min_height = _get_rendered_height(div, "min_height")
    max_height = _get_rendered_height(div, "max_height")

    if min_height > max_height:
        height = 0
    else:
        height = min(max(height, min_height), max_height)

    return height


def _height_percentage_to_pixels(div: Div, attr: Optional[str], height: _Dimension) -> int:
    if attr == "max_height" and (div.parent is None or div.parent.height.unit == "auto"):
        return 2147483647
    if div.parent is None:
        return 0
    if div.parent.height.unit == "auto":
        return 0

    parent_content_height = _get_rendered_height(div.parent) - div.parent.padding.y
    return min((height * parent_content_height) // 100, parent_content_height - div.margin.y)
