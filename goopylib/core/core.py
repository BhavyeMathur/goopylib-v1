"""
This is goopylib's most important module. It defines core and miscellaneous functions that allow you to configure and
use the library. The module is automatically imported and initializes the underlying API.

It can be used to configure global settings, initialize/terminate the library, and gather runtime or compilation
information about goopylib.
"""

from __future__ import annotations

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.core as _core

from goopylib._internal import raise_ as _raise
from goopylib._internal import raise_type_error as _raise_type_error


def init() -> None:
    """Initializes goopylib internally.
    This function is automatically called when goopylib is imported.

    Raises:
        RuntimeError: if the initialization fails
    """
    _core.init()


def terminate() -> None:
    """Terminates goopylib internally and destroys all open windows.
    You should call this function before the program ends.

    Note:
        goopylib can be reinitialized using :func:`gp.init()<goopylib.init>`
    """
    _core.terminate()


def is_initialised() -> bool:
    """Checks if goopylib has been initialised
    """
    return _core.is_initialised()


def update() -> None:
    """Updates goopylib and its windows.

    Examples:
        The following is a standard goopylib mainloop:

        .. code-block:: python

            window = gp.Window(500, 500)

            while window.is_open():
                gp.update()

    Raises:
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")

    _core.update()


def update_on_event() -> None:
    """Updates goopylib every time an event occurs.
    These can be key presses, cursor movement, window resizing, or others.

    Raises:
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")

    _core.update_on_event()


def update_timeout(timeout: float = 0, /) -> None:
    """Updates goopylib after a duration has passed.

    Args:
        timeout: the duration (seconds) to wait between updates.

    Raises:
        TypeError: timeout must be a float/int
        ValueError: timeout must be greater than or equal to 0
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")
    assert isinstance(timeout, (float, int)), _raise_type_error(timeout, "float")
    assert timeout >= 0, _raise(ValueError, f"timeout must be greater than or equal to 0, not {timeout}")

    _core.update_timeout(timeout)


def set_buffer_swap_interval(interval: int, /) -> None:
    """Sets the rate of swapping window buffers.

    Args:
        interval: the number of refreshes to wait before swapping buffers.

    Raises:
        TypeError: interval must be an integer
        ValueError: interval must be greater than or equal to 0
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")
    assert isinstance(interval, int), _raise_type_error(interval, "int")
    assert interval >= 0, _raise(ValueError, f"interval must be greater than or equal to 0, not {interval}")

    return _core.set_buffer_swap_interval(interval)


def get_refresh_rate() -> int:
    """Returns the refresh rate of the primary monitor.

    Returns:
        the refresh rate in Hertz

    Raises:
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")

    return _core.get_refresh_rate()


def get_screen_width() -> int:
    """Returns the width of the primary monitor.

    Returns:
        the screen width in screen coordinates

    Raises:
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")

    return _core.get_screen_width()


def get_screen_height() -> int:
    """Returns the height of the primary monitor.

    Returns:
        the screen height in screen coordinates

    Raises:
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")

    return _core.get_screen_height()


def number_of_monitors() -> int:
    """Returns the number of monitors connected.

    Raises:
        Runtime: goopylib must be initialised first
    """
    assert _core.is_initialised(), _raise(RuntimeError, "goopylib has not been initialised! Use gp.init() first.")

    return _core.number_of_monitors()


def glfw_compiled_version() -> str:
    """Returns the version of GLFW that goopylib was compiled with.
    """
    return _core.glfw_compiled_version()


def glfw_current_version() -> str:
    """Returns the version of GLFW that is currently running.
    """
    return _core.glfw_current_version()


def opengl_version() -> str:
    """Returns the version of OpenGL being used.
    """
    return _core.opengl_version()


if not __debug__:
    # Override module functions & classes with direct access to C API
    # This also means that docstrings are no longer present
    # pylint: disable-next=no-name-in-module, import-error
    from goopylib.ext.core import *

init()
