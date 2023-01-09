"""
Module defining rectangle packing algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

from __future__ import annotations

from typing import Callable, Iterator, NoReturn

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.packing as _packing


# Bin shadows the Python built-in 'bin', but until I can think
# of a better name to call it, I'm going to stick with bin.
# pylint: disable=redefined-builtin


class Item:
    """
    Class representing a rectangular object to be packed.
    """

    def __init__(self, width: float, height: float) -> None:
        self._item: Item = _packing.Item(width, height)

    def is_vertical(self) -> bool:
        """
        Returns:
            whether the item is oriented vertically
        """
        return self._item.is_vertical()

    def is_horizontal(self) -> bool:
        """
        Returns:
            whether the item is oriented horizontally
        """
        return self._item.is_horizontal()

    def is_rotated(self) -> bool:
        """
        Returns:
            whether the item has been rotated
        """
        return self._item.is_rotated()

    def area(self) -> float:
        """
        Returns:
            the area of the item
        """
        return self._item.area()

    def p1(self) -> tuple[float, float]:
        """
        Returns:
            the bottom-left coordinate of the item
        """
        return self._item.p1()

    def p2(self) -> tuple[float, float]:
        """
        Returns:
            the top-right coordinate of the item
        """
        return self._item.p2()

    @property
    def x(self) -> float:
        """
        Returns:
            the x-position of the item
        """
        return self._item.x

    @x.setter
    def x(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def y(self) -> float:
        """
        Returns:
            the y-position of the item
        """
        return self._item.y

    @y.setter
    def y(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def width(self) -> float:
        """
        Returns:
            the width of the item
        """
        return self._item.width

    @width.setter
    def width(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def height(self) -> float:
        """
        Returns:
            the height of the item
        """
        return self._item.height

    @height.setter
    def height(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def long_side(self) -> float:
        """
        Returns:
            the long-side of the item
        """
        return self._item.long_side

    @long_side.setter
    def long_side(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")

    @property
    def short_side(self) -> float:
        """
        Returns:
            the short-side of the item
        """
        return self._item.short_side

    @short_side.setter
    def short_side(self, value: float) -> NoReturn:
        raise TypeError("Cannot change item!")


class Bin:
    """
    Class representing the maximum area in which to pack Items
    """

    def __init__(self, width: float, height: float) -> None:
        self._bin = _packing.bin(width, height)

    def packing_ratio(self) -> float:
        """
        Returns:
            the % packing ratio of this shelf (between 0-1)
        """
        return self._bin.packing_ratio()

    def items(self) -> list[Item]:
        """
        Returns:
            the items part of the bin
        """
        return self._bin.items()

    @property
    def width(self) -> float:
        """
        Returns:
            the width of the bin
        """
        return self._bin.width

    @width.setter
    def width(self, value: float) -> NoReturn:
        raise TypeError("Cannot change bin!")

    @property
    def height(self) -> float:
        """
        Returns:
            the height of the bin
        """
        return self._bin.height

    @height.setter
    def height(self, value: float) -> NoReturn:
        raise TypeError("Cannot change bin!")


class ShelvedBin(Bin):
    """
    Class representing the maximum area in which to pack Items broken down into shelves

    Args:
        width: of the bin
        height: of the bin
    """

    # pylint: disable-next=super-init-not-called
    def __init__(self, width: float, height: float) -> None:
        """
        Class representing the maximum area in which to pack Items broken down into shelves

        Args:
            width: of the bin
            height: of the bin
        """
        self._bin = _packing.ShelvedBin(width, height)

    def __iter__(self) -> Iterator[Shelf]:
        return self._bin.__iter__()

    def packing_ratio(self) -> float:
        """
        Returns:
            the % packing ratio of this shelf (between 0-1)
        """
        return self._bin.packing_ratio()


# Sorting Algorithms


SortingFunction = Callable[[list[Item]], list[Item]]


def sort_by_width(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their width
    """
    return _packing.sort_by_width(descending)


def sort_by_height(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their height
    """
    return _packing.sort_by_height(descending)


def sort_by_perimeter(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their perimeter
    """
    return _packing.sort_by_perimeter(descending)


def sort_by_area(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their area
    """
    return _packing.sort_by_area(descending)


def sort_by_side_ratio(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their side ratio
    """
    return _packing.sort_by_ratio(descending)


def sort_by_long_side(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their long side
    """
    return _packing.sort_by_long_side(descending)


def sort_by_short_side(descending: bool = False) -> SortingFunction:
    """
    Args:
        descending: in descending order?

    Returns:
        a function to sort list of items by their short side
    """
    return _packing.sort_by_short_side(descending)


# pylint: enable=redefined-builtin

from .cpp_shelf import Shelf
