"""
Module defining an Orthographic camera
"""

import goopylib.ext.camera as _camera


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

    def __init__(self, left: float, right: float, bottom: float, top: float):
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

    def set_projection(self, left: float, right: float, bottom: float, top: float):
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

    def move(self, dx: float, dy: float):
        """
        Moves (translate) the camera's position

        Args:
            dx: change in x position
            dy: change in y position

        Raises:
            TypeError: arguments must be numbers
        """
        self._camera.move(dx, dy)

    def rotate(self, angle: float):
        """
        Rotates the camera

        Args:
            angle: in degrees

        Raises:
            TypeError: angle must be a number
        """
        self._camera.rotate(angle)

    def zoomin(self, value: float):
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
    def x(self, value: float):
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
    def y(self, value: float):
        self._camera.y = value

    @property
    def position(self) -> float:
        """
        The position of the camera as an (x, y) tuple

        Raises:
            TypeError: value must be a tuple of numbers
        """
        return self._camera.position

    @position.setter
    def position(self, value: float):
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
    def rotation(self, value: float):
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
    def zoom(self, value: float):
        self._camera.zoom = value
