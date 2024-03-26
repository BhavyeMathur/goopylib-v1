"""
Module defining a generic Renderable object
"""

from __future__ import annotations

from typing import Tuple, Union

from goopylib.core.window import Window


class Renderable:
    """
    This is the base class from which all goopylib objects are derived.
    The methods provided can be called by any other goopylib objects.
    """

    def __init__(self) -> None:
        """
        This is the base class from which all goopylib objects are derived.
        The methods provided can be called by any other goopylib objects.

        Raises:
            NotImplementedError: cannot directly initialize a Renderable
        """

    def __repr__(self) -> str:
        pass

    def draw(self, window: Window) -> Renderable:
        """
        Draws the object to a window

        Args:
            window: the Window to draw to

        Raises:
            TypeError: argument must be a Window
            RuntimeError: window has been destroyed
        """

    def destroy(self) -> None:
        """
        Destroys and undraws the object
        """

    def is_drawn(self) -> bool:
        """
        Returns:
            whether the object has been drawn
        """

    def set_anchor(self, x: float, y: float) -> None:
        """
        Sets the anchor (center) of the object to the specified coordinates

        Args:
            x: in world coordinates
            y: in world coordinates

        Raises:
            TypeError: x and y must be numbers
        """

    def reset_anchor(self) -> None:
        """
        Resets the anchor of the object to its center (average of its vertices)
        """

    def move(self, dx: float, dy: float) -> None:
        """
        Moves (translates) the object across the screen

        Args:
            dx: in world coordinates
            dy: in world coordinates

        Raises:
            TypeError: dx and dy must be numbers
        """

    def rotate(self, angle: float) -> None:
        """
        Rotates the object

        Args:
            angle: in degrees

        Raises:
            TypeError: angle must be a number
        """

    def scale(self, *args: float) -> None:
        """
        Scales the object

        Args:
            *args: a float representing the scale amount. 2 floats to scale the x and y components individually.

        Raises:
            TypeError: scale factor must be numbers
        """

    def set_size(self, width: float, height: float) -> None:
        """
        Sets the dimensions of the object by resizing it

        Args:
            width: in world coordinates
            height: in world coordinates

        Raises:
            TypeError: width and height must be numbers
        """

    @property
    def window(self) -> Union[Window, None]:
        """
        The window the object is drawn to (or None)
        """

    @property
    def x(self) -> float:
        """
        The x-position of the object's anchor in world coordinates

        Raises:
            TypeError: value must be a number
        """

    @x.setter
    def x(self, value: float) -> None:
        pass

    @property
    def y(self) -> float:
        """
        The y-position of the object's anchor in world coordinates

        Raises:
            TypeError: value must be a number
        """

    @y.setter
    def y(self, value: float) -> None:
        pass

    @property
    def z(self) -> float:
        """
        The z-position of the object

        Raises:
            TypeError: value must be a number
        """

    @z.setter
    def z(self, value: float) -> None:
        pass

    @property
    def position(self) -> Tuple[float, float]:
        """
        The position of the object's anchor in world coordinates

        Returns:
            a tuple (x, y) with the position

        Raises:
            TypeError: value must be a tuple of x, y numbers
        """

    @position.setter
    def position(self, value: Tuple[float, float]) -> None:
        pass

    @property
    def rotation(self) -> float:
        """
        The rotation of the object in degrees

        Raises:
            TypeError: value must be a number
        """

    @rotation.setter
    def rotation(self, value: float) -> None:
        pass

    @property
    def xscale(self) -> float:
        """
        The x-scale of the object in %

        Raises:
            TypeError: value must be a number
        """

    @xscale.setter
    def xscale(self, value: float) -> None:
        pass

    @property
    def yscale(self) -> float:
        """
        The y-scale of the object in %

        Raises:
            TypeError: value must be a number
        """

    @yscale.setter
    def yscale(self, value: float) -> None:
        pass

    @property
    def width(self) -> float:
        """
        The width of the object in world coordinates

        Raises:
            TypeError: value must be a number
        """

    @width.setter
    def width(self, value: float) -> None:
        pass

    @property
    def height(self) -> float:
        """
        The height of the object in world coordinates

        Raises:
            TypeError: value must be a number
        """

    @height.setter
    def height(self, value: float) -> None:
        pass

    def hide(self, hide=True) -> None:
        """
        Hides the object from the window

        Args:
            hide: whether to hide or show

        Raises:
            TypeError: hide must be a boolean
        """

    def show(self) -> None:
        """
        Unhides the object if it was hidden
        """

    def is_hidden(self) -> bool:
        """
        Returns:
            whether the object is hidden
        """

    def is_opaque(self) -> bool:
        """
        Returns:
            whether the object is completely opaque
        """

    def box_contains(self, x: float, y: float) -> bool:
        """
        Checks if the object's rectangular bounding box contains a point

        Args:
            x: in world coordinates
            y: in world coordinates

        Raises:
            TypeError: x and y must be numbers
        """

    def contains(self, x: float, y: float) -> bool:
        """
        Checks if the object's bounding box contains a point

        Args:
            x: in world coordinates
            y: in world coordinates

        Raises:
            TypeError: x and y must be numbers
        """
