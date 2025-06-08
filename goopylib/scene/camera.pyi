"""
Module defining an Orthographic camera
"""

from __future__ import annotations

from typing import Tuple


class CameraFrame:
    @property
    def left(self) -> float:
        """
        Returns:
            the left value of a camera frame
        """

    @property
    def right(self) -> float:
        """
        Returns:
            the right value of a camera frame
        """

    @property
    def bottom(self) -> float:
        """
        Returns:
            the bottom value of a camera frame
        """

    @property
    def top(self) -> float:
        """
        Returns:
            the top value of a camera frame
        """


class CameraFrameSize:
    @property
    def width(self) -> float:
        """
        Returns:
            the width of a camera frame
        """

    @property
    def height(self) -> float:
        """
        Returns:
            the height of a camera frame
        """


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

    def get_visible_frame(self) -> CameraFrame:
        """
        Returns:
            The currently visible camera frame with left, right, bottom, and top values as a dictionary
        """

    def get_projection_frame(self) -> CameraFrame:
        """
        Returns:
            The camera projection frame (zoom=1) with left, right, bottom, and top values as a dictionary
        """

    def get_visible_width(self) -> float:
        """
        Returns:
            The currently visible camera frame width
        """

    def get_visible_height(self) -> float:
        """
        Returns:
            The currently visible camera frame height
        """

    def get_projection_width(self) -> float:
        """
        Returns:
            The camera projection (zoom=1) width
        """

    def get_projection_height(self) -> float:
        """
        Returns:
            The camera projection (zoom=1) height
        """

    def get_visible_size(self) -> CameraFrameSize:
        """
        Returns:
            The currently visible camera frame width & height as a dictionary
        """

    def get_projection_size(self) -> CameraFrameSize:
        """
        Returns:
            The camera projection (zoom=1) width & height as a dictionary
        """

    def move(self, dx: float, dy: float) -> None:
        """
        Moves (translate) the camera's position

        Args:
            dx: change in x position
            dy: change in y position

        Raises:
            TypeError: arguments must be numbers
        """

    def rotate(self, angle: float) -> None:
        """
        Rotates the camera

        Args:
            angle: in degrees

        Raises:
            TypeError: angle must be a number
        """

    def zoomin(self, value: float) -> None:
        """
        Zooms the camera in. A value less than 1 zooms the camera out.

        Args:
            value: zoom amount

        Raises:
            TypeError: zoom must be a number
        """

    @property
    def x(self) -> float:
        """
        The x-position of the camera

        Raises:
            TypeError: value must be a number
        """

    @x.setter
    def x(self, value: float) -> None:
        pass

    @property
    def y(self) -> float:
        """
        The y-position of the camera

        Raises:
            TypeError: value must be a number
        """

    @y.setter
    def y(self, value: float) -> None:
        pass

    @property
    def position(self) -> Tuple[float, float]:
        """
        The position of the camera as an (x, y) tuple

        Raises:
            TypeError: value must be a tuple of numbers
        """

    @position.setter
    def position(self, value: Tuple[float, float]) -> None:
        pass

    @property
    def rotation(self) -> float:
        """
        The rotation of the camera in degrees

        Raises:
            TypeError: value must be a number
        """

    @rotation.setter
    def rotation(self, value: float) -> None:
        pass

    @property
    def zoom(self) -> float:
        """
        The zoom amount of the camera in %

        Raises:
            TypeError: value must be a number
        """

    @zoom.setter
    def zoom(self, value: float) -> None:
        pass
