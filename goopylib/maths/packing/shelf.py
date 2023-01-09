"""
Module defining rectangle packing using shelf-based algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

from __future__ import annotations

from typing import Optional, Callable

from .packing import _SortingFunction, Item, Bin, ShelvedBin, sort_by_short_side, sort_by_long_side


# Bin shadows the Python built-in 'bin', but until I can think
# of a better name to call it, I'm going to stick with bin.
# pylint: disable=redefined-builtin


class Shelf:
    """
    Class representing a single shelf (row) for shelf-based packing algorithms

    Args:
        vertical_offset: the vertical position of the shelf
        bin: the bin associated with the shelf
    """

    def __init__(self, vertical_offset: float, bin: ShelvedBin) -> None:
        """
        Class representing a single shelf (row) for shelf-based packing algorithms

        Args:
            vertical_offset: the vertical position of the shelf
            bin: the bin associated with the shelf
        """

        self.width: float = bin.width
        self.height: float = 0

        self.packed_width: float = 0
        self.available_width: float = self.width

        self.vertical_offset: float = vertical_offset

        self.is_open = True
        self.bin: Bin = bin
        self.items: list[Item] = []

    def __repr__(self) -> str:
        return f"Shelf(offset={self.vertical_offset}, packed={self.packed_width}) with {len(self.items)} items"

    def _fits(self, item: Item) -> bool:
        """
        Returns:
            if an item fits inside this shelf.
        """
        if self.is_open:
            return item.width <= self.available_width and self.vertical_offset + item.height <= self.bin.height
        else:
            return item.width <= self.available_width and item.height <= self.height

    def _fits_above(self, item: Item) -> bool:
        """
        Returns:
            if an item will fit on a level above this shelf.
        """
        return self.vertical_offset + self.height + item.height <= self.bin.height

    def _add(self, item: Item) -> None:
        """
        Adds an item to this shelf.
        """
        item._x = self.packed_width
        item._y = self.vertical_offset
        self.bin._add(item)
        self.items.append(item)

        if item.height > self.height:
            self.height = item.height

        self.packed_width += item.width
        self.available_width -= item.width

    def _close(self) -> None:
        """
        Closes this shelf and locks its height.
        """
        self.is_open = False

    def packed_area(self) -> float:
        """
        Returns:
            the amount of area that has been packed into this shelf
        """
        if self.is_open:
            return self.packed_width * self.height
        else:
            return self.width * self.height


# Shelf Packing Algorithms

def pack_next_fit(items: list[Item],
                  bin_width: float,
                  bin_height: float,
                  sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                  allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Next Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    if sorting:
        items = sorting(items)

    bins: list[ShelvedBin] = [ShelvedBin(width=bin_width, height=bin_height)]
    shelf = bins[-1].open_shelf

    for item in items:
        if allow_rotation and (item.is_vertical() != (item.long_side <= shelf.height)):
            item._rotate()

        if shelf._fits(item):
            shelf._add(item)
            continue

        if shelf._fits_above(item):
            shelf = bins[-1]._add_shelf()
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            shelf = bins[-1].open_shelf

        if allow_rotation and item.is_vertical():
            item._rotate()
        shelf._add(item)

    return bins


def pack_first_fit(items: list[Item],
                   bin_width: float,
                   bin_height: float,
                   sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                   allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using Shelf First Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    if sorting:
        items = sorting(items)

    bins: list[ShelvedBin] = [ShelvedBin(width=bin_width, height=bin_height)]

    def _add_to_bin() -> bool:
        for shelf in bin:
            if allow_rotation and (item.is_vertical() != (item.long_side <= shelf.height)):
                item._rotate()

            if shelf._fits(item):
                shelf._add(item)
                return True

        if shelf._fits_above(item):  # noqa W0631, each bin has at least 1 shelf
            if allow_rotation and item.is_vertical():
                item._rotate()
            bin._add_shelf()._add(item)
            return True

        return False

    for item in items:
        for bin in bins:
            if _add_to_bin():
                break
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))

            if allow_rotation and item.is_vertical():
                item._rotate()
            bins[-1].open_shelf._add(item)

    return bins


def pack_scored_fit(items: list[Item],
                    bin_width: float,
                    bin_height: float,
                    scoring_function: Callable[[Shelf, Item], float],
                    sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                    allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        scoring_function: a function that scores shelf candidates for placing items

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    if sorting:
        items = sorting(items)

    bins: list[ShelvedBin] = [ShelvedBin(width=bin_width, height=bin_height)]

    def _score(shelf, obj) -> None:
        nonlocal best_shelf, best_score, best_orientation

        score = scoring_function(shelf, obj)
        if score > best_score:
            best_shelf = shelf
            best_score = score
            best_orientation = item.is_rotated()

    def _add_to_bin() -> None:
        for shelf in bin:
            if allow_rotation and (item.is_vertical() != (item.long_side <= shelf.height)):
                item._rotate()

            if shelf._fits(item):
                _score(shelf, item)

        # pylint: disable-next=undefined-loop-variable
        if best_shelf is None and shelf._fits_above(item):  # noqa W0631, each bin has at least 1 shelf
            shelf = bin._add_shelf()

            if allow_rotation and item.is_vertical():
                item._rotate()

            _score(shelf, item)

    for item in items:
        best_shelf = None
        best_score = float("-inf")
        best_orientation = False  # un-rotated

        for bin in bins:
            _add_to_bin()

        if best_shelf is None:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))

            if allow_rotation and item.is_vertical():
                item._rotate()

            best_shelf = bins[-1].open_shelf
            best_orientation = item.is_rotated()

        if item.is_rotated() != best_orientation:
            item._rotate()

        best_shelf._add(item)

    return bins


def pack_best_width_fit(items: list[Item],
                        bin_width: float,
                        bin_height: float,
                        sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                        allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    return pack_scored_fit(items=items,
                           bin_width=bin_width,
                           bin_height=bin_height,
                           scoring_function=lambda shelf, obj: obj.width - shelf.available_width,
                           sorting=sorting,
                           allow_rotation=allow_rotation)


def pack_worst_width_fit(items: list[Item],
                         bin_width: float,
                         bin_height: float,
                         sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                         allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    return pack_scored_fit(items=items,
                           bin_width=bin_width,
                           bin_height=bin_height,
                           scoring_function=lambda shelf, obj: shelf.available_width - obj.width,
                           sorting=sorting,
                           allow_rotation=allow_rotation)


def pack_best_height_fit(items: list[Item],
                         bin_width: float,
                         bin_height: float,
                         sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                         allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Height Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    return pack_scored_fit(items=items,
                           bin_width=bin_width,
                           bin_height=bin_height,
                           scoring_function=lambda shelf, obj: obj.height - shelf.height,
                           sorting=sorting,
                           allow_rotation=allow_rotation)


def pack_worst_height_fit(items: list[Item],
                          bin_width: float,
                          bin_height: float,
                          sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                          allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Height Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    return pack_scored_fit(items=items,
                           bin_width=bin_width,
                           bin_height=bin_height,
                           scoring_function=lambda shelf, obj: shelf.height - obj.height,
                           sorting=sorting,
                           allow_rotation=allow_rotation)


def pack_best_area_fit(items: list[Item],
                       bin_width: float,
                       bin_height: float,
                       sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                       allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Area Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    return pack_scored_fit(items=items,
                           bin_width=bin_width,
                           bin_height=bin_height,
                           scoring_function=lambda shelf, obj:
                           (shelf.packed_width + obj.width) * max(obj.height, shelf.height),
                           sorting=sorting,
                           allow_rotation=allow_rotation)


def pack_worst_area_fit(items: list[Item],
                        bin_width: float,
                        bin_height: float,
                        sorting: Optional[_SortingFunction] = sort_by_short_side(descending=True),
                        allow_rotation: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Area Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        allow_rotation: whether items are allowed to be rotated.

    Returns:
        a list of bins with packed items.
    """
    return pack_scored_fit(items=items,
                           bin_width=bin_width,
                           bin_height=bin_height,
                           scoring_function=lambda shelf, obj:
                           -(shelf.packed_width + obj.width) * max(obj.height, shelf.height),
                           sorting=sorting,
                           allow_rotation=allow_rotation)


# Oriented Shelf Algorithms

def pack_oriented_next_fit(items: list[Item],
                           bin_width: float,
                           bin_height: float,
                           sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                           orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Next Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    if sorting:
        items = sorting(items)

    bins: list[ShelvedBin] = [ShelvedBin(width=bin_width, height=bin_height)]
    shelf = bins[-1].open_shelf

    for item in items:
        if orientation_vertical == item.is_horizontal():
            item._rotate()

        if shelf._fits(item):
            shelf._add(item)
            continue

        elif shelf._fits_above(item):
            shelf = bins[-1]._add_shelf()
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            shelf = bins[-1].open_shelf

        shelf._add(item)

    return bins


def pack_oriented_first_fit(items: list[Item],
                            bin_width: float,
                            bin_height: float,
                            sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                            orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using Shelf First Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    if sorting:
        items = sorting(items)

    bins: list[ShelvedBin] = [ShelvedBin(width=bin_width, height=bin_height)]

    def _add_to_bin() -> bool:
        for shelf in bin:
            if orientation_vertical == item.is_horizontal():
                item._rotate()

            if shelf._fits(item):
                shelf._add(item)
                return True

        if shelf._fits_above(item):  # noqa W0631, each bin has at least 1 shelf
            shelf = bin._add_shelf()
            shelf._add(item)

            return True
        return False

    for item in items:
        for bin in bins:
            if _add_to_bin():
                break
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            bins[-1].open_shelf._add(item)

    return bins


def pack_oriented_scored_fit(items: list[Item],
                             bin_width: float,
                             bin_height: float,
                             scoring_function: Callable[[Shelf, Item], float],
                             sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                             orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        scoring_function: a function that scores shelf candidates for placing items

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    if sorting:
        items = sorting(items)

    bins: list[ShelvedBin] = [ShelvedBin(width=bin_width, height=bin_height)]

    def _score(shelf, obj) -> None:
        nonlocal best_shelf, best_score

        score = scoring_function(shelf, obj)
        if score > best_score:
            best_shelf = shelf
            best_score = score

    def _add_to_bin() -> None:
        for shelf in bin:
            if shelf._fits(item):
                _score(shelf, item)

        # pylint: disable-next=undefined-loop-variable
        if best_shelf is None and shelf._fits_above(item):  # noqa W0631, each bin has at least 1 shelf
            shelf = bin._add_shelf()

            _score(shelf, item)

    for item in items:
        if orientation_vertical == item.is_horizontal():
            item._rotate()

        best_shelf = None
        best_score = float("-inf")

        for bin in bins:
            _add_to_bin()

        if best_shelf is None:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            best_shelf = bins[-1].open_shelf

        best_shelf._add(item)

    return bins


def pack_oriented_best_width_fit(items: list[Item],
                                 bin_width: float,
                                 bin_height: float,
                                 sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                                 orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return pack_oriented_scored_fit(items=items,
                                    bin_width=bin_width,
                                    bin_height=bin_height,
                                    scoring_function=lambda shelf, obj: obj.width - shelf.available_width,
                                    sorting=sorting,
                                    orientation_vertical=orientation_vertical)


def pack_oriented_worst_width_fit(items: list[Item],
                                  bin_width: float,
                                  bin_height: float,
                                  sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                                  orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return pack_oriented_scored_fit(items=items,
                                    bin_width=bin_width,
                                    bin_height=bin_height,
                                    scoring_function=lambda shelf, obj: shelf.available_width - obj.width,
                                    sorting=sorting,
                                    orientation_vertical=orientation_vertical)


def pack_oriented_best_height_fit(items: list[Item],
                                  bin_width: float,
                                  bin_height: float,
                                  sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                                  orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Height Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return pack_oriented_scored_fit(items=items,
                                    bin_width=bin_width,
                                    bin_height=bin_height,
                                    scoring_function=lambda shelf, obj: obj.height - shelf.height,
                                    sorting=sorting,
                                    orientation_vertical=orientation_vertical)


def pack_oriented_worst_height_fit(items: list[Item],
                                   bin_width: float,
                                   bin_height: float,
                                   sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                                   orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Height Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return pack_oriented_scored_fit(items=items,
                                    bin_width=bin_width,
                                    bin_height=bin_height,
                                    scoring_function=lambda shelf, obj: shelf.height - obj.height,
                                    sorting=sorting,
                                    orientation_vertical=orientation_vertical)


def pack_oriented_best_area_fit(items: list[Item],
                                bin_width: float,
                                bin_height: float,
                                sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                                orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Area Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return pack_oriented_scored_fit(items=items,
                                    bin_width=bin_width,
                                    bin_height=bin_height,
                                    scoring_function=lambda shelf, obj:
                                    (shelf.packed_width + obj.width) * max(obj.height, shelf.height),
                                    sorting=sorting,
                                    orientation_vertical=orientation_vertical)


def pack_oriented_worst_area_fit(items: list[Item],
                                 bin_width: float,
                                 bin_height: float,
                                 sorting: Optional[_SortingFunction] = sort_by_long_side(descending=True),
                                 orientation_vertical: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst Area Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orientation_vertical: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return pack_oriented_scored_fit(items=items,
                                    bin_width=bin_width,
                                    bin_height=bin_height,
                                    scoring_function=lambda shelf, obj:
                                    -(shelf.packed_width + obj.width) * max(obj.height, shelf.height),
                                    sorting=sorting,
                                    orientation_vertical=orientation_vertical)

# pylint: enable=redefined-builtin
