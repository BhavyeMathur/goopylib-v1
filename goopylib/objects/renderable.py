"""
Module defining a generic Renderable object
"""

from goopylib.core.window import Window
import goopylib.ext.renderable as _renderable


class Renderable:
    """
    Generic base class for Renderable objects
    """

    def __init__(self):
        """
        Generic base class for Renderable

        Raises:
            NotImplementedError: cannot create a renderable object
        """
        raise NotImplementedError("Cannot create renderable")
        self.window: Window = None

    def draw(self, window: Window):
        """
        Draws the object to a window

        Args:
            window: the Window to draw to

        Raises:
            TypeError: argument must be a Window
            RuntimeError: window has been destroyed
        """
        if isinstance(window, Window):
            self._renderable.draw(window._window)
            self.window = window
        else:
            self._renderable.draw(window)
        return self

    def destroy(self):
        """
        Destroys and undraws the object
        """
        self._renderable.destroy()

    def is_drawn(self) -> bool:
        """
        Returns:
            whether the object has been drawn
        """
        return self._renderable.is_drawn()

    def set_anchor(self, x: float, y: float):
        """
        Sets the anchor (center) of the object to the specified coordinates

        Args:
            x: in world coordinates
            y: in world coordinates

        Raises:
            TypeError: x and y must be numbers
        """
        return self._renderable.set_anchor(x, y)

    def reset_anchor(self):
        """
        Resets the anchor of the object to its center (average of its vertices)
        """
        return self._renderable.reset_anchor()

    def move(self, dx: float, dy: float):
        """
        Moves (translates) the object across the screen

        Args:
            dx: in world coordinates
            dy: in world coordinates

        Raises:
            TypeError: dx and dy must be numbers
        """
        return self._renderable.move(dx, dy)

    def rotate(self, angle: float):
        """
        Rotates the object

        Args:
            angle: in degrees

        Raises:
            TypeError: angle must be a number
        """
        return self._renderable.rotate(angle)

    def scale(self, *args: float):
        """
        Scales the object

        Args:
            *args: a float representing the scale amount. 2 floats to scale the x and y components individually.

        Raises:
            TypeError: scale factor must be numbers
        """
        return self._renderable.zoom(*args)

    def set_size(self, width: float, height: float):
        """
        Sets the dimensions of the object by resizing it

        Args:
            width: in world coordinates
            height: in world coordinates

        Raises:
            TypeError: width and height must be numbers
        """
        return self._renderable.set_size(width, height)

    @property
    def x(self) -> float:
        """
        The x-position of the object's anchor in world coordinates

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.x

    @x.setter
    def x(self, value: float):
        self._renderable.x = value

    @property
    def y(self) -> float:
        """
        The y-position of the object's anchor in world coordinates

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.y

    @y.setter
    def y(self, value: float):
        self._renderable.y = value

    @property
    def position(self) -> tuple[float, float]:
        """
        The position of the object's anchor in world coordinates

        Returns:
            a tuple (x, y) with the position

        Raises:
            TypeError: value must be a tuple of x, y numbers
        """
        return self._renderable.position

    @position.setter
    def position(self, value: tuple[float, float]):
        self._renderable.position = value

    @property
    def rotation(self) -> float:
        """
        The rotation of the object in degrees

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.rotation

    @rotation.setter
    def rotation(self, value: float):
        self._renderable.rotation = value

    @property
    def xscale(self) -> float:
        """
        The x-scale of the object in %

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.xscale

    @xscale.setter
    def xscale(self, value: float):
        self._renderable.xscale = value

    @property
    def yscale(self) -> float:
        """
        The y-scale of the object in %

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.yscale

    @yscale.setter
    def yscale(self, value: float):
        self._renderable.yscale = value

    @property
    def width(self) -> float:
        """
        The width of the object in world coordinates

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.width

    @width.setter
    def width(self, value: float):
        self._renderable.width = value

    @property
    def height(self) -> float:
        """
        The height of the object in world coordinates

        Raises:
            TypeError: value must be a number
        """
        return self._renderable.height

    @height.setter
    def height(self, value: float):
        self._renderable.height = value

    def hide(self, hide=True):
        """
        Hides the object from the window

        Args:
            hide: whether to hide or show

        Raises:
            TypeError: hide must be a boolean
        """
        return self._renderable.hide(hide)

    def show(self):
        """
        Unhides the object if it was hidden
        """
        return self._renderable.show()

    def is_hidden(self) -> bool:
        """
        Returns:
            whether the object is hidden
        """
        return self._renderable.is_hidden()

    def box_contains(self, x: float, y: float):
        """
        Checks if the object's rectangular bounding box contains a point

        Args:
            x: in world coordinates
            y: in world coordinates

        Raises:
            TypeError: x and y must be numbers
        """
        return self._renderable.box_contains(x, y)

    def contains(self, x: float, y: float):
        """
        Checks if the object's bounding box contains a point

        Args:
            x: in world coordinates
            y: in world coordinates

        Raises:
            TypeError: x and y must be numbers
        """
        return self._renderable.contains(x, y)
