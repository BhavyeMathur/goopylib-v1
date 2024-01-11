"""
Module defining an image object
"""

from __future__ import annotations

from typing import Union, Tuple
from os.path import isabs, dirname

import __main__

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.image as _image

from goopylib.objects.rectangle import Rectangle


class Image(Rectangle):
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

    # pylint: disable-next=super-init-not-called
    def __init__(self, path: str, p1: Tuple[float, float], *args: Union[Tuple[float, float], float]) -> None:
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
        if not isabs(path):
            path = f"{dirname(__main__.__file__)}/{path}"
        self._renderable: Image = _image.Image(path, p1, *args)

    def get_path(self) -> str:
        """
        Returns: the filepath used by the image
        """
        return self._renderable.get_path()
