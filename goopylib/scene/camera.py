"""
Module defining an Orthographic camera
"""

import goopylib.ext.camera as _camera


class Camera:
    def __init__(self, left: float, right: float, bottom: float, top: float):
        self._camera: Camera = _camera.Camera(left, right, bottom, top)

    def set_projection(self, left: float, right: float, bottom: float, top: float):
        self._camera.set_projection(left, right, bottom, top)

    def move(self, dx: float, dy: float):
        self._camera.move(dx, dy)

    def rotate(self, angle: float):
        self._camera.rotate(angle)

    def zoomin(self, value: float):
        self._camera.zoomin(value)

    @property
    def x(self) -> float:
        return self._camera.x

    @x.setter
    def x(self, value: float):
        self._camera.x = value

    @property
    def y(self) -> float:
        return self._camera.y

    @y.setter
    def y(self, value: float):
        self._camera.y = value

    @property
    def position(self) -> float:
        return self._camera.position

    @position.setter
    def position(self, value: float):
        self._camera.position = value

    @property
    def rotation(self) -> float:
        return self._camera.rotation

    @rotation.setter
    def rotation(self, value: float):
        self._camera.rotation = value

    @property
    def zoom(self) -> float:
        return self._camera.zoom

    @zoom.setter
    def zoom(self, value: float):
        self._camera.zoom = value
