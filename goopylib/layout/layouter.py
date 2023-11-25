from .container import Container


def process_container(container: Container, x=0, y=0):
    container.margin_box.x1 = x
    container.margin_box.y1 = y

    container.margin_box.width = container.margin.x + get_rendered_dimension(container, "width")
    container.margin_box.height = container.margin.y + get_rendered_dimension(container, "height")

    container.rendered_width = get_rendered_dimension(container, "width")
    container.rendered_height = get_rendered_dimension(container, "height")

    if container.display == "flex":
        _process_flex_children(container, x + container.padding_left, y - container.padding_top)

    return x + container.rendered_width + container.margin_right, y - container.margin_bottom


def _process_flex_children(container, x, y):
    max_child_height = 0
    wrap_queue = []

    for child in container.children:
        if container.flex_wrap != "nowrap":
            next_x = x + get_rendered_dimension(child, "width") + child.margin_left + child.margin_right
            if next_x > container.x + container.rendered_width - container.padding_right:
                _align_flex_wrap_queue(container, wrap_queue)

                x = container.x + container.padding_left
                y -= max_child_height
                max_child_height = 0

                wrap_queue = []

        x, _ = process_container(child, x, y)

        if container.flex_wrap != "nowrap":
            wrap_queue.append(child)
            max_child_height = max(max_child_height, child.rendered_height + child.margin_top + child.margin_bottom)

    _align_flex_wrap_queue(container, wrap_queue)
    return x, y


def _align_flex_wrap_queue(container, wrap_queue):
    if container.flex_align == "start":
        return

    wrap_width = sum(child.rendered_width for child in wrap_queue)
    whitespace = container.rendered_width - wrap_width - container.padding_left - container.padding_right

    if container.flex_align == "space-around":
        _align_flex_wrap_queue_space_around(whitespace, wrap_queue)
    elif container.flex_align == "space-between":
        _align_flex_wrap_queue_space_between(whitespace, wrap_queue)
    elif container.flex_align == "space-evenly":
        _align_flex_wrap_queue_space_evenly(whitespace, wrap_queue)

    elif container.flex_align == "centre":
        _align_flex_wrap_queue_centre(whitespace, wrap_queue)
    elif container.flex_align == "end":
        _align_flex_wrap_queue_end(whitespace, wrap_queue)


def _align_flex_wrap_queue_centre(whitespace, wrap_queue):
    xoffset = whitespace / 2
    for child in wrap_queue:
        child.x += xoffset


def _align_flex_wrap_queue_end(whitespace, wrap_queue):
    for child in wrap_queue:
        child.x += whitespace


def _align_flex_wrap_queue_space_around(whitespace, wrap_queue):
    xoffset = whitespace / (2 * len(wrap_queue))

    x = wrap_queue[0].x
    for child in wrap_queue:
        x += xoffset
        child.x = x
        x += child.rendered_width + xoffset


def _align_flex_wrap_queue_space_between(whitespace, wrap_queue):
    xoffset = whitespace / (len(wrap_queue) - 1)

    x = wrap_queue[0].x
    for child in wrap_queue:
        child.x = x
        x += child.rendered_width + xoffset


def _align_flex_wrap_queue_space_evenly(whitespace, wrap_queue):
    xoffset = whitespace / (len(wrap_queue) + 1)

    x = wrap_queue[0].x + xoffset
    for child in wrap_queue:
        child.x = x
        x += child.rendered_width + xoffset


def get_rendered_dimension(container: Container, axis: str) -> int:
    dimension = getattr(container, axis)
    unit = getattr(container, f"{axis}_unit")

    if unit == "px":
        return dimension

    elif unit == "%":
        parent = container.parent
        parent_dim = getattr(parent.content_box, axis)

        return dimension / 100 * parent_dim
