"""
Module defining rectangle packing algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

from __future__ import annotations

from typing import Callable, NoReturn, Optional, Tuple, List


# Bin shadows the Python built-in 'bin', but until I can think
# of a better name to call it, I'm going to stick with bin.
# pylint: disable=redefined-builtin
# pylint: disable=unsubscriptable-object


class Item:
    """
    Class representing a rectangular object to be packed.
    """

    __slots__ = ["_width", "_height", "_long_side", "_short_side", "_x", "_y", "_rotated", "_id"]

    items: int = 0

    def __init__(self, width: float, height: float) -> None:
        self._width: float = width
        self._height: float = height

        if width > height:
            self._long_side: float = width
            self._short_side: float = height
        else:
            self._long_side: float = height
            self._short_side: float = width

        self._x: float = -1
        self._y: float = -1
        self._rotated = False

        self._id = Item.items
        Item.items += 1

    def rotate(self) -> None:
        """
        Swaps the Item's width and height, ie rotates by 90 degrees.
        """
        self._width, self._height = self._height, self._width
        self._rotated = not self._rotated

    def is_vertical(self) -> bool:
        """
        Returns:
            whether the item is oriented vertically
        """
        return self._height > self._width

    def is_horizontal(self) -> bool:
        """
        Returns:
            whether the item is oriented horizontally
        """
        return self._width > self._height

    def is_rotated(self) -> bool:
        """
        Returns:
            whether the item has been rotated
        """
        return self._rotated

    def area(self) -> float:
        """
        Returns:
            the area of the item
        """
        return self._width * self._height

    def p1(self) -> Tuple[float, float]:
        """
        Returns:
            the bottom-left coordinate of the item
        """
        return self._x, self._y

    def p2(self) -> Tuple[float, float]:
        """
        Returns:
            the top-right coordinate of the item
        """
        return self._x + self._width, self._y + self._height

    @property
    def x(self) -> float:
        """
        Returns:
            the x-position of the item
        """
        return self._x

    @x.setter
    def x(self, value: float) -> NoReturn:
        self._x = value

    @property
    def y(self) -> float:
        """
        Returns:
            the y-position of the item
        """
        return self._y

    @y.setter
    def y(self, value: float) -> NoReturn:
        self._y = value

    @property
    def width(self) -> float:
        """
        Returns:
            the width of the item
        """
        return self._width

    @width.setter
    def width(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def height(self) -> float:
        """
        Returns:
            the height of the item
        """
        return self._height

    @height.setter
    def height(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def long_side(self) -> float:
        """
        Returns:
            the long-side of the item
        """
        return self._long_side

    @long_side.setter
    def long_side(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def short_side(self) -> float:
        """
        Returns:
            the short-side of the item
        """
        return self._short_side

    @short_side.setter
    def short_side(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")


class Bin:
    """
    Class representing the maximum area in which to pack Items
    """

    __slots__ = ["_width", "_height", "_items", "_id"]

    bins: int = 0

    def __init__(self, width: float, height: float) -> None:
        self._width: float = width
        self._height: float = height

        self._items: List[Item] = []

        self._id = Bin.bins
        Bin.bins += 1

    def _add(self, item: Item) -> None:
        """
        Adds an item to this bin.
        """
        self._items.append(item)

    def packing_ratio(self) -> float:
        """
        Returns:
            the % packing ratio of this shelf (between 0-1)
        """
        return sum(map(Item.area, self._items)) / (self._width * self._height)

    def items(self) -> List[Item]:
        """
        Returns:
            the items part of the bin
        """
        return self._items.copy()

    @property
    def width(self) -> float:
        """
        Returns:
            the width of the bin
        """
        return self._width

    @width.setter
    def width(self, value: float) -> NoReturn:
        raise TypeError("Cannot change bin!")

    @property
    def height(self) -> float:
        """
        Returns:
            the height of the bin
        """
        return self._height

    @height.setter
    def height(self, value: float) -> NoReturn:
        raise TypeError("Cannot change bin!")


class PackingAlgorithm:
    """
    A class representing a rectangle packing algorithm.

    Args:
        bin_width: the maximum width of the packed bin
        bin_height: the maximum height of the packed bin
    """

    __slots__ = ["_bin_width", "_bin_height", "_bins"]

    def __init__(self, bin_width: float, bin_height: float):
        """
        A class representing a rectangle packing algorithm.

        Args:
            bin_width: the maximum width of the packed bin
            bin_height: the maximum height of the packed bin
        """
        self._bin_width = bin_width
        self._bin_height = bin_height
        self._bins: List[Bin] = []

    def pack(self, item: Item, **kwargs) -> None:
        """
        Packs a rectangular item using this algorithm.

        Args:
            item: the item to pack
            **kwargs:
        """
        raise NotImplementedError()

    def pack_all(self, items: List[Item], sorting: Optional[SortingFunction], **kwargs) -> None:
        """
        Packs a list of rectangular items into bins.

        Args:
            items: the list of items
            sorting: a sorting function to use, otherwise None.
            **kwargs:
        """
        if sorting:
            items = sorting(items)

        for item in items:
            self.pack(item, **kwargs)

    def bins(self) -> Tuple[Bin]:
        """
        Returns:
            a list of bins with packed items.
        """
        return tuple(self._bins)


# Sorting Algorithms


SortingFunction = Callable[[List[Item]], List[Item]]


def sort_by_width(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their width
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width)

    return _sort


def sort_by_height(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their height
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.height)

    return _sort


def sort_by_perimeter(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their perimeter
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width + item.height)

    return _sort


def sort_by_area(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their area
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width * item.height)

    return _sort


def sort_by_side_ratio(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their side ratio
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.width / item.height)

    return _sort


def sort_by_long_side(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their long side
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.long_side)

    return _sort


def sort_by_short_side(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their short side
    """

    def _sort(items: List[Item]):
        return sorted(items, reverse=descending, key=lambda item: item.short_side)

    return _sort


# pylint: enable=redefined-builtin
# pylint: enable=unsubscriptable-object
