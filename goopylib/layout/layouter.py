from .layout_modes import *


def process_container(container: Container):
    assert container.parent is None
    assert container.width.unit == "px"

    container.layout.process_children(container, 0, 0)


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
