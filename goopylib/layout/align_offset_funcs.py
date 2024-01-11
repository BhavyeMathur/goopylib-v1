"""
Flex align helper functions
"""

from typing import Callable, Dict


def _get_offset(align: str, whitespace: int, n: int) -> Callable[[int], int]:
    return _align_to_offset_func[align](whitespace, n)


# pylint: disable=unused-argument


def _align_centre_offset(whitespace: int, n: int) -> Callable[[int], int]:
    return lambda i: whitespace // 2


def _align_end_offset(whitespace: int, n: int) -> Callable[[int], int]:
    return lambda i: whitespace

# pylint: enable=unused-argument


def _align_space_around_offset(whitespace: int, n: int) -> Callable[[int], int]:
    offset = whitespace / (2 * n)
    return lambda i: int((i * 2 + 1) * offset)


def _align_space_between_offset(whitespace: int, n: int) -> Callable[[int], int]:
    if n == 1:
        return lambda i: 0

    offset = whitespace / (n - 1)
    return lambda i: int(i * offset)


def _align_space_evenly_offset(whitespace: int, n: int) -> Callable[[int], int]:
    offset = whitespace / (n + 1)
    return lambda i: int((i + 1) * offset)


# pylint: disable-next=unsubscriptable-object
_align_to_offset_func: Dict[str, Callable[[int, int], Callable[[int], int]]] = \
    {"centre":        _align_centre_offset,
     "space-around":  _align_space_around_offset,
     "space-between": _align_space_between_offset,
     "space-evenly":  _align_space_evenly_offset,
     "end":           _align_end_offset}


def _get_item_offset(align: str, row_height: int) -> Callable[[int], int]:
    return _item_align_to_offset_func[align](row_height)


def _item_align_centre_offset(row_height: int) -> Callable[[int], int]:
    return lambda height: (row_height - height) // 2


def _item_align_end_offset(row_height: int) -> Callable[[int], int]:
    return lambda height: row_height - height


# pylint: disable-next=unsubscriptable-object
_item_align_to_offset_func: Dict[str, Callable[[int], Callable[[int], int]]] = \
    {"centre": _item_align_centre_offset,
     "end": _item_align_end_offset}
