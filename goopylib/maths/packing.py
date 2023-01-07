"""
Module defining rectangle packing algorithms
"""

from typing import Callable, Optional, Iterator

InputRectangles = list[tuple[float, float]]
SortedRectangles = tuple[Iterator[int], list[tuple[float, float]]]
PackedRectangles = list[dict[int, tuple[float, float]]]
SortingFunction = Callable[[InputRectangles], SortedRectangles]


def _sorting_func(rectangles: InputRectangles, func: Callable[[tuple[float, float]], float]) -> SortedRectangles:
    indices = range(len(rectangles))
    indices, rectangles = zip(*sorted(zip(indices, rectangles), reverse=True, key=func))
    return indices.__iter__(), rectangles


def sort_by_width(rectangles: InputRectangles) -> SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0])


def sort_by_height(rectangles: InputRectangles) -> SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][1])


def sort_by_area(rectangles: InputRectangles) -> SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0] * rect[1][1])


def sort_by_perimeter(rectangles: InputRectangles) -> SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0] + rect[1][1])


def sort_by_side_ratio(rectangles: InputRectangles) -> SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0] / rect[1][1])


def pack1D(rectangles: InputRectangles,
           bin_size: float,
           sorting_func: Optional[SortingFunction] = sort_by_width) -> PackedRectangles:

    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    packable_space: list[float] = [bin_size]

    for rect, (width, _) in enumerate(rectangles):
        if width > bin_size:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of size {bin_size}.")

        for i, size in enumerate(packable_space):
            if width > size:
                continue

            packed[i][indices.__next__()] = (bin_size - packable_space[i], 0)
            packable_space[i] -= width
            break
        else:
            packed.append({indices.__next__(): (0, 0)})
            packable_space.append(bin_size - width)

    return packed
