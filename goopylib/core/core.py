"""
This is goopylib's most important module. It defines core and miscellaneous functions that allow you to configure and
use the library. The module is automatically imported and initializes the underlying API.

It can be used to configure global settings, initialize/terminate the library, and gather runtime or compilation
information about goopylib.
"""

from __future__ import annotations

# pylint: disable-next=no-name-in-module, import-error
import goopylib.ext.core as _core


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


def update() -> None:
    """Updates goopylib and its windows.

    Examples:
        The following is a standard goopylib mainloop:

        .. code-block:: python

            window = gp.Window(500, 500)

            while window.is_open():
                gp.update()
    """
    _core.update()


def update_on_event() -> None:
    """Updates goopylib every time an event occurs.
    These can be key presses, cursor movement, window resizing, or others.
    """
    _core.update_on_event()


def update_timeout(timeout: float = 0) -> None:
    """Updates goopylib after a duration has passed.

    Args:
        timeout: the duration (seconds) to wait between updates.

    Raises:
        ValueError: if timeout is less than 0
    """
    _core.update_timeout(timeout)


def set_buffer_swap_interval(interval: int) -> None:
    """Sets the rate of swapping window buffers.

    Args:
        interval: the number of refreshes to wait before swapping buffers.

    Raises:
        TypeError: if a non-integer value is passed.
        ValueError: if interval is less than 0
    """
    return _core.set_buffer_swap_interval(interval)


def get_refresh_rate() -> int:
    """Returns the refresh rate of the primary monitor.

    Returns:
        the refresh rate in Hertz

    Raises:
        RuntimeError: if goopylib has not been initialized
    """
    return _core.get_refresh_rate()


def get_screen_width() -> int:
    """Returns the width of the primary monitor.

    Returns:
        the screen width in screen coordinates

    Raises:
        RuntimeError: if goopylib has not been initialized
    """
    return _core.get_screen_width()


def get_screen_height() -> int:
    """Returns the height of the primary monitor.

    Returns:
        the screen height in screen coordinates

    Raises:
        RuntimeError: if goopylib has not been initialized
    """
    return _core.get_screen_height()


def number_of_monitors() -> int:
    """Returns the number of monitors connected.

    Raises:
        RuntimeError: if goopylib has not been initialized
    """
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


init()
