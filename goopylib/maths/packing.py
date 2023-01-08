"""
Module defining rectangle packing algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

from __future__ import annotations

from typing import Optional, Callable, Iterator


# Bin shadows the Python built-in 'bin', but until I can think
# of a better name to call it, I'm going to stick with bin.


class Item:
    """
    Class representing a rectangular object to be packed.
    """

    items: int = 0

    def __init__(self, width: float, height: float) -> None:
        self.width: float = width
        self.height: float = height

        if width > height:
            self.long_side: float = width
            self.short_side: float = height
        else:
            self.long_side: float = height
            self.short_side: float = width

        self.x: float = -1
        self.y: float = -1
        self.rotated = False

        self.ID = Item.items
        Item.items += 1

    def rotate(self) -> None:
        """
        Swaps the Item's width and height, ie rotates by 90 degrees.
        """
        self.width, self.height = self.height, self.width
        self.rotated = not self.rotated

    def is_vertical(self) -> bool:
        """
        Returns:
            whether the item is oriented vertically
        """
        return self.height > self.width

    def is_horizontal(self) -> bool:
        """
        Returns:
            whether the item is oriented horizontally
        """
        return self.width > self.height

    def area(self) -> float:
        """
        Returns:
            the area of the item
        """
        return self.width * self.height

    def p1(self) -> tuple[float, float]:
        """
        Returns:
            the bottom-left coordinate of the item
        """
        return self.x, self.y

    def p2(self) -> tuple[float, float]:
        """
        Returns:
            the top-right coordinate of the item
        """
        return self.x + self.width, self.y + self.height


class Bin:
    """
    Class representing the maximum area in which to pack Items
    """

    bins: int = 0

    def __init__(self, width: float, height: float) -> None:
        self.width: float = width
        self.height: float = height

        self.items: list[Item] = []

        self.ID = Bin.bins
        Bin.bins += 1

    def add(self, item: Item) -> None:
        """
        Adds an item to this bin.
        """
        self.items.append(item)

    def packing_ratio(self) -> float:
        """
        Returns:
            the % packing ratio of this shelf (between 0-1)
        """
        return sum(map(Item.area, self.items)) / (self.width * self.height)


class ShelvedBin(Bin):
    """
    Class representing the maximum area in which to pack Items broken down into shelves

    Args:
        width: of the bin
        height: of the bin
    """

    def __init__(self, width: float, height: float) -> None:
        """
        Class representing the maximum area in which to pack Items broken down into shelves

        Args:
            width: of the bin
            height: of the bin
        """

        super().__init__(width, height)

        self.open_shelf: Shelf = Shelf(vertical_offset=0, bin=self)
        self.shelves: list[Shelf] = [self.open_shelf]

    def __iter__(self) -> Iterator[Shelf]:
        return self.shelves.__iter__()

    def add_shelf(self) -> Shelf:
        """
        Adds a new shelf to this Bin and closes the previously open shelf.

        Returns:
            the newly added shelf.
        """
        self.open_shelf.close()
        self.open_shelf = Shelf(vertical_offset=self.open_shelf.vertical_offset + self.open_shelf.height, bin=self)
        self.shelves.append(self.open_shelf)

        return self.open_shelf

    def packing_ratio(self) -> float:
        """
        Returns:
            the % packing ratio of this shelf (between 0-1)
        """
        if self.ID == Bin.bins - 1:  # this is the latest bin
            return sum(map(Item.area, self.items)) / sum(map(Shelf.packed_area, self.shelves))
        else:
            return sum(map(Item.area, self.items)) / (self.width * self.height)


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

    def fits(self, item: Item) -> bool:
        """
        Returns:
            if an item fits inside this shelf.
        """
        if self.is_open:
            return item.width <= self.available_width and self.vertical_offset + item.height <= self.bin.height
        else:
            return item.width <= self.available_width and item.height <= self.height

    def fits_above(self, item: Item) -> bool:
        """
        Returns:
            if an item will fit on a level above this shelf.
        """
        return self.vertical_offset + self.height + item.height <= self.bin.height

    def add(self, item: Item) -> None:
        """
        Adds an item to this shelf.
        """
        item.x = self.packed_width
        item.y = self.vertical_offset
        self.bin.add(item)
        self.items.append(item)

        if item.height > self.height:
            self.height = item.height

        self.packed_width += item.width
        self.available_width -= item.width

    def close(self) -> None:
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


# Sorting Algorithms


_SortingFunction = Callable[[list[Item]], list[Item]]


def sort_by_width(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their width
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width)

    return _sort


def sort_by_height(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their height
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.height)

    return _sort


def sort_by_perimeter(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their perimeter
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width + item.height)

    return _sort


def sort_by_area(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their area
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width * item.height)

    return _sort


def sort_by_side_ratio(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their side ratio
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width / item.height)

    return _sort


def sort_by_long_side(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their long side
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.long_side)

    return _sort


def sort_by_short_side(descending: bool = False) -> Callable[[list[Item]], list[Item]]:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their short side
    """

    def _sort(items: list[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.short_side)

    return _sort


# Shelf Packing Algorithms

def pack_shelf_next_fit(items: list[Item],
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
            item.rotate()

        if shelf.fits(item):
            shelf.add(item)
            continue

        elif shelf.fits_above(item):
            shelf = bins[-1].add_shelf()
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            shelf = bins[-1].open_shelf

        if allow_rotation and item.is_vertical():
            item.rotate()
        shelf.add(item)

    return bins


def pack_shelf_first_fit(items: list[Item],
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
                item.rotate()

            if shelf.fits(item):
                shelf.add(item)
                return True
        else:
            if shelf.fits_above(item):  # noqa W0631, each bin has at least 1 shelf
                shelf = bin.add_shelf()

                if allow_rotation and item.is_vertical():
                    item.rotate()
                shelf.add(item)

                return True

    for item in items:
        for bin in bins:
            if _add_to_bin():
                break
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))

            if allow_rotation and item.is_vertical():
                item.rotate()
            bins[-1].open_shelf.add(item)

    return bins


def pack_shelf_scored_fit(items: list[Item],
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
            best_orientation = item.rotated

    def _add_to_bin() -> None:
        for shelf in bin:
            if allow_rotation and (item.is_vertical() != (item.long_side <= shelf.height)):
                item.rotate()

            if shelf.fits(item):
                _score(shelf, item)

        if best_shelf is None and shelf.fits_above(item):  # noqa W0631, each bin has at least 1 shelf
            shelf = bin.add_shelf()

            if allow_rotation and item.is_vertical():
                item.rotate()

            _score(shelf, item)

    for item in items:
        best_shelf = None
        best_score = float("-inf")
        best_orientation = False  # un-rotated

        for bin in bins:
            _add_to_bin()

        if best_shelf is None:  # noqa W0631
            bins.append(ShelvedBin(width=bin_width, height=bin_height))

            if allow_rotation and item.is_vertical():
                item.rotate()

            best_shelf = bins[-1].open_shelf
            best_orientation = item.rotated

        if item.rotated != best_orientation:
            item.rotate()

        best_shelf.add(item)  # noqa W0631

    return bins


def pack_shelf_best_width_fit(items: list[Item],
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
    return pack_shelf_scored_fit(items=items,
                                 bin_width=bin_width,
                                 bin_height=bin_height,
                                 scoring_function=lambda shelf, obj: obj.width - shelf.available_width,
                                 sorting=sorting,
                                 allow_rotation=allow_rotation)


def pack_shelf_worst_width_fit(items: list[Item],
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
    return pack_shelf_scored_fit(items=items,
                                 bin_width=bin_width,
                                 bin_height=bin_height,
                                 scoring_function=lambda shelf, obj: shelf.available_width - obj.width,
                                 sorting=sorting,
                                 allow_rotation=allow_rotation)


def pack_shelf_best_height_fit(items: list[Item],
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
    return pack_shelf_scored_fit(items=items,
                                 bin_width=bin_width,
                                 bin_height=bin_height,
                                 scoring_function=lambda shelf, obj: obj.height - shelf.height,
                                 sorting=sorting,
                                 allow_rotation=allow_rotation)


def pack_shelf_worst_height_fit(items: list[Item],
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
    return pack_shelf_scored_fit(items=items,
                                 bin_width=bin_width,
                                 bin_height=bin_height,
                                 scoring_function=lambda shelf, obj: shelf.height - obj.height,
                                 sorting=sorting,
                                 allow_rotation=allow_rotation)


def pack_shelf_best_area_fit(items: list[Item],
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
    return pack_shelf_scored_fit(items=items,
                                 bin_width=bin_width,
                                 bin_height=bin_height,
                                 scoring_function=lambda shelf, obj:
                                 (shelf.packed_width + obj.width) * max(obj.height, shelf.height),
                                 sorting=sorting,
                                 allow_rotation=allow_rotation)


# Oriented Shelf Algorithms

def pack_shelf_oriented_next_fit(items: list[Item],
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
            item.rotate()

        if shelf.fits(item):
            shelf.add(item)
            continue

        elif shelf.fits_above(item):
            shelf = bins[-1].add_shelf()
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            shelf = bins[-1].open_shelf

        shelf.add(item)

    return bins


def pack_shelf_oriented_first_fit(items: list[Item],
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
                item.rotate()

            if shelf.fits(item):
                shelf.add(item)
                return True
        else:
            if shelf.fits_above(item):  # noqa W0631, each bin has at least 1 shelf
                shelf = bin.add_shelf()
                shelf.add(item)

                return True

    for item in items:
        for bin in bins:
            if _add_to_bin():
                break
        else:
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            bins[-1].open_shelf.add(item)

    return bins


def pack_shelf_oriented_scored_fit(items: list[Item],
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
            if shelf.fits(item):
                _score(shelf, item)

        if best_shelf is None and shelf.fits_above(item):  # noqa W0631, each bin has at least 1 shelf
            shelf = bin.add_shelf()

            _score(shelf, item)

    for item in items:
        if orientation_vertical == item.is_horizontal():
            item.rotate()

        best_shelf = None
        best_score = float("-inf")

        for bin in bins:
            _add_to_bin()

        if best_shelf is None:  # noqa W0631
            bins.append(ShelvedBin(width=bin_width, height=bin_height))
            best_shelf = bins[-1].open_shelf

        best_shelf.add(item)  # noqa W0631

    return bins


def pack_shelf_oriented_best_width_fit(items: list[Item],
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
    return pack_shelf_oriented_scored_fit(items=items,
                                          bin_width=bin_width,
                                          bin_height=bin_height,
                                          scoring_function=lambda shelf, obj: obj.width - shelf.available_width,
                                          sorting=sorting,
                                          orientation_vertical=orientation_vertical)


def pack_shelf_oriented_worst_width_fit(items: list[Item],
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
    return pack_shelf_oriented_scored_fit(items=items,
                                          bin_width=bin_width,
                                          bin_height=bin_height,
                                          scoring_function=lambda shelf, obj: shelf.available_width - obj.width,
                                          sorting=sorting,
                                          orientation_vertical=orientation_vertical)


def pack_shelf_oriented_best_height_fit(items: list[Item],
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
    return pack_shelf_oriented_scored_fit(items=items,
                                          bin_width=bin_width,
                                          bin_height=bin_height,
                                          scoring_function=lambda shelf, obj: obj.height - shelf.height,
                                          sorting=sorting,
                                          orientation_vertical=orientation_vertical)


def pack_shelf_oriented_worst_height_fit(items: list[Item],
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
    return pack_shelf_oriented_scored_fit(items=items,
                                          bin_width=bin_width,
                                          bin_height=bin_height,
                                          scoring_function=lambda shelf, obj: shelf.height - obj.height,
                                          sorting=sorting,
                                          orientation_vertical=orientation_vertical)


def pack_shelf_oriented_best_area_fit(items: list[Item],
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
    return pack_shelf_oriented_scored_fit(items=items,
                                          bin_width=bin_width,
                                          bin_height=bin_height,
                                          scoring_function=lambda shelf, obj:
                                          (shelf.packed_width + obj.width) * max(obj.height, shelf.height),
                                          sorting=sorting,
                                          orientation_vertical=orientation_vertical)
