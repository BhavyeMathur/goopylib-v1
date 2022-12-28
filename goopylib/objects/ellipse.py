"""
Module defining an ellipse object
"""

from typing import Union

import goopylib.ext.ellipse as _ellipse

from goopylib.color.color import Color
from goopylib.objects.renderable import Renderable


class Ellipse(Renderable):
    """
    An object representing an ellipse or oval

    Args:
        p1: a tuple (x, y) with the a coordinate in world space
        *args: either annother tuple (x, y) in world space, or the x and y radii of the ellipse

    Raises:
        TypeError: arguments must be numbers or coordinates

    Examples:

        .. code-block:: python

            # Creates an ellipse centered at (50, 100) with a size of (100, 200)

            >>> Ellipse((0, 0), (100, 200))

            # Creates an ellipse centered at (0, 0) with radii (50, 100)

            >>> Ellipse((0, 0), 50, 100)
    """

    def __init__(self, p1: tuple[float, float], *args: Union[tuple[float, float], float]):
        """
        An object representing an ellipse or oval

        Args:
            p1: a tuple (x, y) in world space
            *args: either annother tuple (x, y) in world space, or the x and y radii of the ellipse

        Raises:
            TypeError: arguments must be numbers or coordinates

        Examples:

            .. code-block:: python

                # Creates an ellipse centered at (50, 100) with a size of (100, 200)

                >>> Ellipse((0, 0), (100, 200))

                # Creates an ellipse centered at (0, 0) with radii (50, 100)

                >>> Ellipse((0, 0), 50, 100)
        """
        self._renderable: Ellipse = _ellipse.Ellipse(p1, *args)

    def set_color(self, *args):
        """
        Sets the fill color of the object

        Args:
            *args: a color or 4 colors corresponding to bottom-left, bottom-right, top-right, and top-left

        Raises:
            TypeError: arguments must be colors
        """
        self._renderable.set_color(*(arg._color if isinstance(arg, Color) else arg for arg in args))

    def set_transparency(self, *args: float):
        """
        Sets the transparency of the object

        Args:
            *args: a float or 4 floats corresponding to bottom-left, bottom-right, top-right, and top-left

        Raises:
            TypeError: arguments must be floats
            ValueError: transparency must be between 0 and 1
        """
        self._renderable.set_transparency(*args)
