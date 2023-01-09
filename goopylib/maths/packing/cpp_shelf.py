"""
Module defining rectangle packing using shelf-based algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

from __future__ import annotations

from typing import Optional, Callable

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.shelf as _shelf

from .packing import SortingFunction, Item, Bin, ShelvedBin, sort_by_short_side, sort_by_long_side


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
        if isinstance(bin, ShelvedBin):
            self._shelf = _shelf.Shelf(vertical_offset, bin._bin)
        else:
            self._shelf = _shelf.Shelf(vertical_offset, bin)

    def __repr__(self) -> str:
        return self._shelf.__repr__()

    def packed_area(self) -> float:
        """
        Returns:
            the amount of area that has been packed into this shelf
        """
        return self._shelf.packed_area()


# Shelf Packing Algorithms

def pack_next_fit(items: list[Item],
                  bin_width: float,
                  bin_height: float,
                  sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_next_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_first_fit(items: list[Item],
                   bin_width: float,
                   bin_height: float,
                   sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_first_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_scored_fit(items: list[Item],
                    bin_width: float,
                    bin_height: float,
                    scoring_function: Callable[[Shelf, Item], float],
                    sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_scored_fit(items, bin_width, bin_height, scoring_function, sorting, allow_rotation)


def pack_best_width_fit(items: list[Item],
                        bin_width: float,
                        bin_height: float,
                        sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_best_width_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_worst_width_fit(items: list[Item],
                         bin_width: float,
                         bin_height: float,
                         sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_worst_width_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_best_height_fit(items: list[Item],
                         bin_width: float,
                         bin_height: float,
                         sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_best_height_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_worst_height_fit(items: list[Item],
                          bin_width: float,
                          bin_height: float,
                          sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_worst_height_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_best_area_fit(items: list[Item],
                       bin_width: float,
                       bin_height: float,
                       sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_best_area_fit(items, bin_width, bin_height, sorting, allow_rotation)


def pack_worst_area_fit(items: list[Item],
                        bin_width: float,
                        bin_height: float,
                        sorting: Optional[SortingFunction] = sort_by_short_side(descending=True),
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
    return _shelf.pack_worst_area_fit(items, bin_width, bin_height, sorting, allow_rotation)


# Oriented Shelf Algorithms

def pack_oriented_next_fit(items: list[Item],
                           bin_width: float,
                           bin_height: float,
                           sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                           orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Next Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_next_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_first_fit(items: list[Item],
                            bin_width: float,
                            bin_height: float,
                            sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                            orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using Shelf First Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_first_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_scored_fit(items: list[Item],
                             bin_width: float,
                             bin_height: float,
                             scoring_function: Callable[[Shelf, Item], float],
                             sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                             orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        scoring_function: a function that scores shelf candidates for placing items

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_scored_fit(items, bin_width, bin_height, scoring_function, sorting, orient_vertically)


def pack_oriented_best_width_fit(items: list[Item],
                                 bin_width: float,
                                 bin_height: float,
                                 sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                                 orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_best_width_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_worst_width_fit(items: list[Item],
                                  bin_width: float,
                                  bin_height: float,
                                  sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                                  orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Width Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_worst_width_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_best_height_fit(items: list[Item],
                                  bin_width: float,
                                  bin_height: float,
                                  sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                                  orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Height Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_best_height_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_worst_height_fit(items: list[Item],
                                   bin_width: float,
                                   bin_height: float,
                                   sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                                   orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst-Height Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_worst_height_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_best_area_fit(items: list[Item],
                                bin_width: float,
                                bin_height: float,
                                sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                                orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Best Area Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_best_area_fit(items, bin_width, bin_height, sorting, orient_vertically)


def pack_oriented_worst_area_fit(items: list[Item],
                                 bin_width: float,
                                 bin_height: float,
                                 sorting: Optional[SortingFunction] = sort_by_long_side(descending=True),
                                 orient_vertically: bool = True) -> list[Bin]:
    """
    Packs a list of rectangular items into bins using the Shelf Worst Area Fit algorithm.

    Args:
        items: list of items
        bin_width: of each bin
        bin_height: of each bin

        sorting: function used to sort the items. Set to None to disable sorting.
        orient_vertically: whether items are oriented vertically or horizontally.

    Returns:
        a list of bins with packed items.
    """
    return _shelf.pack_oriented_worst_area_fit(items, bin_width, bin_height, sorting, orient_vertically)

# pylint: enable=redefined-builtin
