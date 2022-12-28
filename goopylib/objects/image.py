"""
Module defining an image object
"""

from typing import Union

import goopylib.ext.image as _image

from goopylib.objects.renderable import Renderable


class Image(Renderable):
    """
    An object representing a textured rectangle - an image

    Args:
        path: the filepath to the image
        p1: the image's center (x, y) in world space
        *args: optional width and height or an optional top-right coordinate (p1 will be bottom-left).

    Raises:
        FileNotFoundError: image was not found
        ValueError: unsupported image format
        TypeError: arguments must be a filepath, a coordinate, and numbers

    Examples:

        .. code-block:: python

            # Create an image at (0, 0) and load size from its file

            >>> Image("filepath.gif", (0, 0))

            # Create an image at (0, 0) with size (100, 200)

            >>> Image("filepath.png", (0, 0), 100, 200)

            # Create an image from (0, 0) to (120, 20)

            >>> Image("filepath.jgp", (0, 0), (120, 20))
    """

    def __init__(self, path: str, p1: tuple[float, float], *args: Union[tuple[float, float], float]):
        """
        An object representing a textured rectangle - an image

        Args:
            path: the filepath to the image
            p1: the image's center (x, y) in world space
            *args: optional width and height or an optional top-right coordinate (p1 will be bottom-left).

        Raises:
            FileNotFoundError: image was not found
            ValueError: unsupported image format
            TypeError: arguments must be a filepath, a coordinate, and numbers

        Examples:

            .. code-block:: python

                # Create an image at (0, 0) and load size from its file

                >>> Image("filepath.gif", (0, 0))

                # Create an image at (0, 0) with size (100, 200)

                >>> Image("filepath.png", (0, 0), 100, 200)

                # Create an image from (0, 0) to (120, 20)

                >>> Image("filepath.jgp", (0, 0), (120, 20))
        """
        self._renderable: Image = _image.Image(path, p1, *args)

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

    def get_path(self) -> str:
        """
        Returns: the filepath used by the image
        """
        return self._renderable.get_path()
