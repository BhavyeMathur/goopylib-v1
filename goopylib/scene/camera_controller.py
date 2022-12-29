"""
Module defining the Camera Controller helper class
"""

from goopylib.core.window import *

import goopylib.ext.camera_controller as _controller


class CameraController:
    """
    Controller class that automatically manages camera movement, rotation, and zoom.

    This is a helper class that wraps around a Window's camera and provides basic but quick functionality.

    Args:
        window: the window to use

    Raises
        TypeError: window must be a goopylib Window
    """

    def __init__(self, window: Window):
        """
        Controller class that automatically manages camera movement, rotation, and zoom.

        This is a helper class that wraps around a Window's camera and provides basic but quick functionality

        Args:
            window: the window to use

        Raises
            TypeError: window must be a goopylib Window
        """

        self._window: Window = window
        if isinstance(window, Window):
            self._controller: CameraController = _controller.CameraController(self._window._window)
        else:
            self._controller: CameraController = _controller.CameraController(self._window)
    
    def update(self):
        """
        Updates the controller. Call this method in the mainloop.
        """
        self._controller.update()
    
    def enable_movement(self, value: bool):
        """
        Enables automatic camera movement when the control keys are pressed.

        Args:
            value: whether to enable or disable movement

        Raises:
            TypeError: value must be a boolean
        """
        self._controller.enable_movement(value)

    def enable_rotation(self, value: bool):
        """
        Enables automatic camera rotation when the control keys are pressed.

        Args:
            value: whether to enable or disable rotation

        Raises:
            TypeError: value must be a boolean
        """
        self._controller.enable_rotation(value)

    def enable_zoom(self, value: bool):
        """
        Enables automatic camera zooming when the control keys are pressed.

        Args:
            value: whether to enable or disable zooming

        Raises:
            TypeError: value must be a boolean
        """
        self._controller.enable_zoom(value)
    
    def invert_movement(self, value: bool):
        """
        Inverts camera movement.

        Args:
            value: whether to invert the movement

        Raises:
            TypeError: value must be a boolean
        """
        self._controller.invert_movement(value)
    
    def invert_rotation(self, value: bool):
        """
        Inverts camera rotation.

        Args:
            value: whether to invert the rotation

        Raises:
            TypeError: value must be a boolean
        """
        self._controller.invert_rotation(value)
    
    @property
    def horizontal_speed(self) -> float:
        """
        The horizontal movement speed of the camera.

        Returns:
            the horizontal movement speed

        Raises:
            TypeError: speed must be a number
        """
        return self._controller.horizontal_speed

    @horizontal_speed.setter
    def horizontal_speed(self, value: float):
        self._controller.horizontal_speed = value

    @property
    def vertical_speed(self) -> float:
        """
        The vertical movement speed of the camera.

        Returns:
            the vertical movement speed

        Raises:
            TypeError: speed must be a number
        """
        return self._controller.vertical_speed

    @vertical_speed.setter
    def vertical_speed(self, value: float):
        self._controller.vertical_speed = value

    @property
    def rotate_speed(self) -> float:
        """
        The rotational speed of the camera.

        Returns:
            the rotation speed

        Raises:
            TypeError: speed must be a number
        """
        return self._controller.rotate_speed

    @rotate_speed.setter
    def rotate_speed(self, value: float):
        self._controller.rotate_speed = value

    @property
    def zoom_speed(self) -> float:
        """
        The zoom speed of the camera.

        Returns:
            the zoom speed

        Raises:
            TypeError: speed must be a number
        """
        return self._controller.zoom_speed

    @zoom_speed.setter
    def zoom_speed(self, value: float):
        self._controller.zoom_speed = value

    def use_wasd(self):
        """
        Binds the WASD keys for camera movement.
        """
        self._controller.use_wasd()

    def use_arrows(self):
        """
        Binds the arrow keys for camera movement.
        """
        self._controller.use_arrows()

    def set_movement_keys(self, up: int, left: int, down: int, right: int):
        """
        Sets the keys used for camera movement.

        Args:
            up: key to use for moving up
            left: key to use for moving left
            down: key to use for moving down
            right: key to use for moving right

        Raises:
            TypeError: arguments must be keys
        """
        self._controller.set_movement_keys(up, left, down, right)

    def set_rotation_keys(self, clockwise: int, anticlockwise: int):
        """
        Sets the keys used for camera rotation.

        Args:
            clockwise: key to use for clockwise rotation
            anticlockwise: key to use for anticlockwise rotation

        Raises:
            TypeError: arguments must be keys
        """
        self._controller.set_rotation_keys(clockwise, anticlockwise)

    def set_zoom_keys(self, zoomin: int, zoomout: int):
        """
        Sets the keys used for camera zooming.

        Args:
            zoomin: key to use for zooming in
            zoomout: key to use for zooming out

        Raises:
            TypeError: arguments must be keys
        """
        self._controller.set_zoom_keys(zoomin, zoomout)
