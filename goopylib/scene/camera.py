"""
Module defining an Orthographic camera
"""

from __future__ import annotations

from typing import TypedDict, NoReturn, Tuple

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.camera as _camera


class _FrozenDict(dict):
    def __hash__(self) -> int:
        return id(self)

    def _immutable(self, *args, **kws) -> NoReturn:
        """Immutable method
        """
        raise TypeError("object is immutable")

    __setitem__ = _immutable
    __delitem__ = _immutable
    clear = _immutable
    update = _immutable
    setdefault = _immutable
    pop = _immutable
    popitem = _immutable


class CameraFrame(TypedDict):
    """
    A dictionary containing the left, right, top, and bottom values of a camera frame
    """
    left: float
    right: float
    top: float
    bottom: float


class CameraFrameSize(TypedDict):
    """
    A dictionary containing the width and height of a camera frame
    """
    width: float
    height: float


class Camera:
    """
    An orthographic camera associated with a Window.

    Args:
        left: left clipping plane
        right: right clipping plane
        bottom: bottom clipping plane
        top: top clipping plane

    Raises:
        TypeError: arguments must be numbers
    """

    __slots__ = ["_camera"]

    def __init__(self, left: float, right: float, bottom: float, top: float) -> None:
        """
        An orthographic camera associated with a Window.

        Args:
            left: left clipping plane
            right: right clipping plane
            bottom: bottom clipping plane
            top: top clipping plane

        Raises:
            TypeError: arguments must be numbers
        """
        self._camera: Camera = _camera.Camera(left, right, bottom, top)

    def set_projection(self, left: float, right: float, bottom: float, top: float) -> None:
        """
        Sets an orthographic projection for the camera

        Args:
            left: left clipping plane
            right: right clipping plane
            bottom: bottom clipping plane
            top: top clipping plane

        Raises:
            TypeError: arguments must be numbers
        """
        self._camera.set_projection(left, right, bottom, top)

    def get_visible_frame(self) -> CameraFrame:
        """
        Returns:
            The currently visible camera frame with left, right, bottom, and top values as a dictionary
        """
        return _FrozenDict(self._camera.get_visible_frame())

    def get_projection_frame(self) -> CameraFrame:
        """
        Returns:
            The camera projection frame (zoom=1) with left, right, bottom, and top values as a dictionary
        """
        return _FrozenDict(self._camera.get_projection_frame())

    def get_visible_width(self) -> float:
        """
        Returns:
            The currently visible camera frame width
        """
        return self._camera.get_visible_width()

    def get_visible_height(self) -> float:
        """
        Returns:
            The currently visible camera frame height
        """
        return self._camera.get_visible_height()

    def get_projection_width(self) -> float:
        """
        Returns:
            The camera projection (zoom=1) width
        """
        return self._camera.get_projection_width()

    def get_projection_height(self) -> float:
        """
        Returns:
            The camera projection (zoom=1) height
        """
        return self._camera.get_projection_height()

    def get_visible_size(self) -> CameraFrameSize:
        """
        Returns:
            The currently visible camera frame width & height as a dictionary
        """
        return _FrozenDict(self._camera.get_visible_size())

    def get_projection_size(self) -> CameraFrameSize:
        """
        Returns:
            The camera projection (zoom=1) width & height as a dictionary
        """
        return _FrozenDict(self._camera.get_projection_size())

    def move(self, dx: float, dy: float) -> None:
        """
        Moves (translate) the camera's position

        Args:
            dx: change in x position
            dy: change in y position

        Raises:
            TypeError: arguments must be numbers
        """
        self._camera.move(dx, dy)

    def rotate(self, angle: float) -> None:
        """
        Rotates the camera

        Args:
            angle: in degrees

        Raises:
            TypeError: angle must be a number
        """
        self._camera.rotate(angle)

    def zoomin(self, value: float) -> None:
        """
        Zooms the camera in. A value less than 1 zooms the camera out.

        Args:
            value: zoom amount

        Raises:
            TypeError: zoom must be a number
        """
        self._camera.zoomin(value)

    @property
    def x(self) -> float:
        """
        The x-position of the camera

        Raises:
            TypeError: value must be a number
        """
        return self._camera.x

    @x.setter
    def x(self, value: float) -> None:
        self._camera.x = value

    @property
    def y(self) -> float:
        """
        The y-position of the camera

        Raises:
            TypeError: value must be a number
        """
        return self._camera.y

    @y.setter
    def y(self, value: float) -> None:
        self._camera.y = value

    @property
    def position(self) -> Tuple[float, float]:
        """
        The position of the camera as an (x, y) tuple

        Raises:
            TypeError: value must be a tuple of numbers
        """
        return self._camera.position

    @position.setter
    def position(self, value: Tuple[float, float]) -> None:
        self._camera.position = value

    @property
    def rotation(self) -> float:
        """
        The rotation of the camera in degrees

        Raises:
            TypeError: value must be a number
        """
        return self._camera.rotation

    @rotation.setter
    def rotation(self, value: float) -> None:
        self._camera.rotation = value

    @property
    def zoom(self) -> float:
        """
        The zoom amount of the camera in %

        Raises:
            TypeError: value must be a number
        """
        return self._camera.zoom

    @zoom.setter
    def zoom(self, value: float) -> None:
        self._camera.zoom = value
