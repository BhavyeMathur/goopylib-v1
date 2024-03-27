"""
This is goopylib's central module. It defines core and miscellaneous functions that allow you to configure and
use the library. The module is automatically imported and initializes the underlying API.

It can be used to configure global settings, initialize/terminate the library, and gather runtime or compilation
information about goopylib.
"""

from __future__ import annotations


def init() -> None:
    """Initializes goopylib internally.
    This function is automatically called when goopylib is imported.

    Raises:
        RuntimeError: if the initialization fails
    """


def terminate() -> None:
    """Terminates goopylib internally and destroys all open windows.
    You should call this function before the program ends.

    Note:
        goopylib can be reinitialized using :func:`gp.init()<goopylib.init>`
    """


def is_initialized() -> bool:
    """Checks if goopylib has been initialized
    """


def has_active_context() -> bool:
    """Checks if goopylib has an active context (window)
    """


def update() -> None:
    """Updates goopylib and its windows.

    Examples:
        The following is a standard goopylib mainloop:

        .. code-block:: python

            window = gp.Window(500, 500)

            while window.is_open():
                gp.update()

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def update_on_event() -> None:
    """Updates goopylib every time an event occurs.
    These can be key presses, cursor movement, window resizing, or others.

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def update_timeout(timeout: float = 0, /) -> None:
    """Updates goopylib after a duration has passed.

    Args:
        timeout: the duration (seconds) to wait between updates.

    Raises:
        TypeError: timeout must be a float/int
        ValueError: timeout must be greater than or equal to 0
        RuntimeError: goopylib must be initialized first
    """


def set_buffer_swap_interval(interval: int, /) -> None:
    """Sets the rate of swapping window buffers.

    Args:
        interval: the number of refreshes to wait before swapping buffers.

    Raises:
        TypeError: interval must be an integer
        ValueError: interval must be greater than or equal to 0
        RuntimeError: goopylib must be initialized first and have an active context (window)
    """


def get_refresh_rate() -> int:
    """Returns the refresh rate of the primary monitor.

    Returns:
        the refresh rate in Hertz

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def get_screen_width() -> int:
    """Returns the width of the primary monitor.

    Returns:
        the screen width in screen coordinates

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def get_screen_height() -> int:
    """Returns the height of the primary monitor.

    Returns:
        the screen height in screen coordinates

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def get_number_of_monitors() -> int:
    """Returns the number of monitors connected.

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def get_time() -> float:
    """Returns the time since goopylib was initialized

    Raises:
        RuntimeError: goopylib must be initialized first
    """


def glfw_compiled_version() -> str:
    """Returns the version of GLFW that goopylib was compiled with.
    """


def glfw_current_version() -> str:
    """Returns the version of GLFW that is currently running.
    """


def opengl_version() -> str:
    """Returns the version of OpenGL being used.
    
    Raises:
        RuntimeError: goopylib must have an active context (window)
    """
