"""
Module defining rectangle packing algorithms
"""

from __future__ import annotations

from typing import Callable, Optional, Iterator

_Dimensions = tuple[float, float]
_Position = tuple[float, float]
_Rotation = bool
_ID = int

InputRectangles = list[_Dimensions]
_SortedRectangles = tuple[Iterator[_ID], list[_Dimensions]]

PackedRectangles = list[dict[_ID, tuple[_Position, _Rotation]]]
SortingFunction = Callable[[InputRectangles], _SortedRectangles]


def _sorting_func(rectangles: InputRectangles, func: Callable[[tuple[float, float]], float]) -> _SortedRectangles:
    indices = range(len(rectangles))
    indices, rectangles = zip(*sorted(zip(indices, rectangles), reverse=True, key=func))
    return indices.__iter__(), rectangles


def sort_by_width(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0])


def sort_by_height(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][1])


def sort_by_area(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0] * rect[1][1])


def sort_by_perimeter(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0] + rect[1][1])


def sort_by_side_ratio(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: rect[1][0] / rect[1][1])


def sort_by_long_side(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: max(rect[1]))


def sort_by_short_side(rectangles: InputRectangles) -> _SortedRectangles:
    return _sorting_func(rectangles, lambda rect: min(rect[1]))


def pack1D(rectangles: InputRectangles,
           bin_size: float,
           sorting_func: Optional[SortingFunction] = None) -> PackedRectangles:

    # get a list of sorted rectangles with their corresponding indices
    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    packable_space: list[float] = [bin_size]

    # iterate through each rectangle,
    # if the rectangle is bigger than the bin, raise an error.
    # iterate through each bin, if there isn't enough space to fit the rectangle, move to then next bin.
    # if there is enough space, add the rectangle to this bin, reduce the amount of available space
    # if there are no bins that can fit the rectangle, create a new bin
    for width, _ in rectangles:
        if width > bin_size:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of size {bin_size}.")

        for i, size in enumerate(packable_space):
            if width > size:
                continue

            packed[i][indices.__next__()] = ((bin_size - packable_space[i], 0), 0)
            packable_space[i] -= width
            break
        else:
            packed.append({indices.__next__(): ((0, 0), 0)})
            packable_space.append(bin_size - width)

    return packed


# see http://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

class _Shelf:
    def __init__(self, x, y, height, bin_=None):
        self.x = x
        self.y = y
        self.height = height
        self.is_open = True
        self.bin_ = bin_


def pack_shelf_next_fit(rectangles: InputRectangles,
                        bin_width: float,
                        bin_height: float,
                        sorting_func: Optional[SortingFunction] = sort_by_short_side,
                        allow_rotation=True) -> PackedRectangles:

    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    shelf = _Shelf(0, 0, 0)

    rotate = False

    for width, height in rectangles:
        if width > bin_width:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of width {bin_width}.")
        if height > bin_height:
            raise RuntimeError(f"Cannot pack rectangle of height {height} into a bin of height {bin_height}.")

        if allow_rotation:
            if height > width:
                width, height = height, width
                rotate = True
            else:
                rotate = False

            if width <= shelf.height and shelf.x + height <= bin_width:
                width, height = height, width
                rotate = not rotate

        if shelf.x + width > bin_width:  # rectangle doesn't horizontally fit on the current shelf
            if shelf.y + shelf.height + height > bin_height:
                shelf = _Shelf(width, 0, height)
                packed.append({indices.__next__(): ((0, 0), rotate)})
            else:
                shelf = _Shelf(width, shelf.y + shelf.height, height)
                packed[-1][indices.__next__()] = ((0, shelf.y), rotate)

        elif shelf.y + height > bin_height:  # rectangle doesn't vertically fit in the current bin
            shelf = _Shelf(width, 0, height)
            packed.append({indices.__next__(): ((0, 0), rotate)})

        else:  # rectangle fits on the current shelf
            if height > shelf.height:
                shelf.height = height

            packed[-1][indices.__next__()] = ((shelf.x, shelf.y), rotate)
            shelf.x += width

    return packed


def pack_shelf_first_fit(rectangles: InputRectangles,
                         bin_width: float,
                         bin_height: float,
                         sorting_func: Optional[SortingFunction] = sort_by_short_side,
                         allow_rotation=True) -> PackedRectangles:

    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    shelves: list[list[_Shelf]] = [[_Shelf(0, 0, 0)]]
    rotate = False

    for width, height in rectangles:
        rectangle_added = False

        if width > bin_width:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of width {bin_width}.")
        if height > bin_height:
            raise RuntimeError(f"Cannot pack rectangle of height {height} into a bin of height {bin_height}.")

        if allow_rotation:
            if height > width:
                width, height = height, width
                rotate = True
            else:
                rotate = False

        index = indices.__next__()

        for bin_ in range(len(packed)):
            for shelf in shelves[bin_]:

                # if we can store the rectangle vertically, store it vertically
                if allow_rotation and (width <= shelf.height and shelf.x + height <= bin_width):
                    width, height = height, width
                    rotate = not rotate

                elif shelf.x + width > bin_width:  # rectangle doesn't horizontally fit on the current shelf
                    continue

                if shelf.is_open:
                    if shelf.y + height <= bin_height:
                        if height > shelf.height:
                            shelf.height = height

                        packed[bin_][index] = ((shelf.x, shelf.y), rotate)
                        shelf.x += width

                        rectangle_added = True
                        break

                elif height <= shelf.height:  # shelf is closed and rectangle fits vertically on the shelf
                    packed[bin_][index] = ((shelf.x, shelf.y), rotate)
                    shelf.x += width

                    rectangle_added = True
                    break

            else:  # check if new shelf can be created
                new_y = shelf.y + shelf.height

                if new_y + height <= bin_height:  # new shelf can be created
                    shelf.is_open = False

                    packed[bin_][index] = ((0, new_y), rotate)
                    shelves[bin_].append(_Shelf(x=width, y=new_y, height=height))
                    rectangle_added = True

            if rectangle_added:
                break

        else:  # new bin must be added
            shelf.is_open = False

            packed.append({index: ((0, 0), rotate)})
            shelves.append([_Shelf(x=width, y=0, height=height)])

    return packed


def pack_shelf_best_width_fit(rectangles: InputRectangles,
                              bin_width: float,
                              bin_height: float,
                              sorting_func: Optional[SortingFunction] = sort_by_short_side,
                              allow_rotation=True) -> PackedRectangles:

    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    shelves: list[_Shelf] = [_Shelf(0, 0, 0, 0)]

    for width, height in rectangles:
        if width > bin_width:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of width {bin_width}.")
        if height > bin_height:
            raise RuntimeError(f"Cannot pack rectangle of height {height} into a bin of height {bin_height}.")

        if width > height:
            long = width
            short = height
        else:
            long = height
            short = width

        index = indices.__next__()

        minimized_leftover = bin_width
        best_shelf = None
        original_width = width

        for shelf in shelves:
            if allow_rotation:
                if long <= shelf.height and shelf.x + short <= bin_width:
                    width = short
                    height = long
                else:
                    width = long
                    height = short

            if shelf.x + width > bin_width:  # rectangle doesn't horizontally fit on the current shelf
                continue

            if shelf.is_open:
                if shelf.y + height > bin_height:  # rectangle doesn't fit vertically on the current shelf
                    continue
            elif height > shelf.height:  # rectangle doesn't fit vertically on the current (closed) shelf
                continue

            if bin_width - shelf.x - width < minimized_leftover:
                minimized_leftover = bin_width - shelf.x - width
                best_shelf = shelf

        if best_shelf is None:
            if shelf.y + shelf.height + short > bin_height:
                shelves.append(_Shelf(x=0, y=shelf.y + shelf.height, height=0, bin_=shelf.bin_))
                best_shelf = _Shelf(x=0, y=0, height=short, bin_=shelf.bin_ + 1)
                packed.append({})
            else:
                shelf.is_open = False
                best_shelf = _Shelf(x=0, y=shelf.y + shelf.height, height=short, bin_=shelf.bin_)

            shelves.append(best_shelf)
            packed[best_shelf.bin_][index] = ((best_shelf.x, best_shelf.y), long != original_width)
            best_shelf.x += long

        else:
            if allow_rotation:
                if long <= best_shelf.height and best_shelf.x + short <= bin_width:
                    width = short
                    height = long
                else:
                    width = long
                    height = short

            if height > best_shelf.height:
                best_shelf.height = height

            packed[best_shelf.bin_][index] = ((best_shelf.x, best_shelf.y), width != original_width)
            best_shelf.x += width

    return packed


def pack_shelf_worst_width_fit(rectangles: InputRectangles,
                               bin_width: float,
                               bin_height: float,
                               sorting_func: Optional[SortingFunction] = sort_by_short_side,
                               allow_rotation=True) -> PackedRectangles:

    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    shelves: list[_Shelf] = [_Shelf(0, 0, 0, 0)]

    for width, height in rectangles:
        if width > bin_width:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of width {bin_width}.")
        if height > bin_height:
            raise RuntimeError(f"Cannot pack rectangle of height {height} into a bin of height {bin_height}.")

        if width > height:
            long = width
            short = height
        else:
            long = height
            short = width

        index = indices.__next__()

        maximized_leftover = 0
        best_shelf = None
        original_width = width

        for shelf in shelves:
            if allow_rotation:
                if long <= shelf.height and shelf.x + short <= bin_width:
                    width = short
                    height = long
                else:
                    width = long
                    height = short

            if shelf.x + width > bin_width:  # rectangle doesn't horizontally fit on the current shelf
                continue

            if shelf.is_open:
                if shelf.y + height > bin_height:  # rectangle doesn't fit vertically on the current shelf
                    continue
            elif height > shelf.height:  # rectangle doesn't fit vertically on the current (closed) shelf
                continue

            if bin_width - shelf.x - width > maximized_leftover:
                maximized_leftover = bin_width - shelf.x - width
                best_shelf = shelf

        if best_shelf is None:
            if shelf.y + shelf.height + short > bin_height:
                shelves.append(_Shelf(x=0, y=shelf.y + shelf.height, height=0, bin_=shelf.bin_))
                best_shelf = _Shelf(x=0, y=0, height=short, bin_=shelf.bin_ + 1)
                packed.append({})
            else:
                shelf.is_open = False
                best_shelf = _Shelf(x=0, y=shelf.y + shelf.height, height=short, bin_=shelf.bin_)

            shelves.append(best_shelf)
            packed[best_shelf.bin_][index] = ((best_shelf.x, best_shelf.y), long != original_width)
            best_shelf.x += long

        else:
            if allow_rotation:
                if long <= best_shelf.height and best_shelf.x + short <= bin_width:
                    width = short
                    height = long
                else:
                    width = long
                    height = short

            if height > best_shelf.height:
                best_shelf.height = height

            packed[best_shelf.bin_][index] = ((best_shelf.x, best_shelf.y), width != original_width)
            best_shelf.x += width

    return packed


def pack_shelf_best_height_fit(rectangles: InputRectangles,
                               bin_width: float,
                               bin_height: float,
                               sorting_func: Optional[SortingFunction] = sort_by_short_side,
                               allow_rotation=True) -> PackedRectangles:

    if sorting_func:
        indices, rectangles = sorting_func(rectangles)
    else:
        indices = range(len(rectangles)).__iter__()

    packed: PackedRectangles = [{}]
    shelves: list[_Shelf] = [_Shelf(0, 0, 0, 0)]

    for width, height in rectangles:
        if width > bin_width:
            raise RuntimeError(f"Cannot pack rectangle of width {width} into a bin of width {bin_width}.")
        if height > bin_height:
            raise RuntimeError(f"Cannot pack rectangle of height {height} into a bin of height {bin_height}.")

        if width > height:
            long = width
            short = height
        else:
            long = height
            short = width

        index = indices.__next__()

        minimized_leftover = bin_height
        best_shelf = None
        original_width = width

        for shelf in shelves:
            if allow_rotation:
                if long <= shelf.height and shelf.x + short <= bin_width:
                    width = short
                    height = long
                else:
                    width = long
                    height = short

            if shelf.x + width > bin_width:  # rectangle doesn't horizontally fit on the current shelf
                continue

            if shelf.is_open:
                if shelf.y + height > bin_height:  # rectangle doesn't fit vertically on the current shelf
                    continue
            elif height > shelf.height:  # rectangle doesn't fit vertically on the current (closed) shelf
                continue

            if shelf.height - height < minimized_leftover:
                minimized_leftover = shelf.height - height
                best_shelf = shelf

        # check if the new shelf must be added to the current bin or the next bin
        if best_shelf is None:
            if shelf.y + shelf.height + short > bin_height:
                shelves.append(_Shelf(x=0, y=shelf.y + shelf.height, height=0, bin_=shelf.bin_))
                best_shelf = _Shelf(x=0, y=0, height=short, bin_=shelf.bin_ + 1)
                packed.append({})
            else:
                shelf.is_open = False
                best_shelf = _Shelf(x=0, y=shelf.y + shelf.height, height=short, bin_=shelf.bin_)

            shelves.append(best_shelf)
            packed[best_shelf.bin_][index] = ((best_shelf.x, best_shelf.y), long != original_width)
            best_shelf.x += long

        else:
            if allow_rotation:
                if long <= best_shelf.height and best_shelf.x + short <= bin_width:
                    width = short
                    height = long
                else:
                    width = long
                    height = short

            if height > best_shelf.height:
                best_shelf.height = height

            packed[best_shelf.bin_][index] = ((best_shelf.x, best_shelf.y), width != original_width)
            best_shelf.x += width

    return packed
