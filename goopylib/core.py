"""
Module defining core and miscellaneous functions
"""

from typing import Union


def init():
    """Initializes goopylib internally.

    This function is automatically called when goopylib is imported.

    Raises:
        RuntimeError: if the initialization fails
    """
    raise NotImplementedError()


def terminate():
    """Terminates goopylib internally and destroys all open Windows.

    Note:
        You can reinitialize the library using :func:`gp.init()<goopylib.init>`
    """
    raise NotImplementedError()


def update():
    """Updates goopylib and its windows.

    Examples:
        The following is a standard goopylib mainloop.

        .. code-block:: python

            window = gp.Window(500, 500)

            while window.is_open():
                gp.update()
    """
    raise NotImplementedError()


def update_on_event():
    """Updates goopylib every time an event occurs.
    """
    raise NotImplementedError()


def update_timeout(timeout: Union[float, int] = 0):
    """Updates goopylib after a duration has passed.

    Args:
        timeout: the duration (seconds) to wait between updates. Defaults to `0`.
    """
    raise NotImplementedError()


def glfw_compiled_version() -> str:
    """Returns the version of GLFW that goopylib was compiled with.
    """
    raise NotImplementedError()


def glfw_current_version() -> str:
    """Returns the version of GLFW that is currently running.
    """
    raise NotImplementedError()


def get_refresh_rate() -> int:
    """Returns the refresh rate of the primary monitor.

    Returns:
        int: the refresh rate in Hertz

    Raises:
        RuntimeError: if goopylib has not been initialized

    Examples:
        >>> gp.get_refresh_rate()
        120
    """
    raise NotImplementedError()


def get_screen_width() -> int:
    """Returns the width of the primary monitor.

    Returns:
        int: the screen width in screen coordinates

    Raises:
        RuntimeError: if goopylib has not been initialized

    Examples:
        >>> gp.get_screen_width()
        1512
    """
    raise NotImplementedError()


def get_screen_height() -> int:
    """Returns the height of the primary monitor.

    Returns:
        int: the screen height in screen coordinates

    Raises:
        RuntimeError: if goopylib has not been initialized

    Examples:
        >>> gp.get_screen_height()
        982
    """
    raise NotImplementedError()


def number_of_monitors() -> int:
    """Returns the number of monitors connected.

    Raises:
        RuntimeError: if goopylib has not been initialized

    Examples:
        >>> gp.number_of_monitors()
        1
    """
    raise NotImplementedError()


def set_buffer_swap_interval(*args: int):
    """Sets the minimum number of monitor refreshes the driver should wait from the time before swapping Window buffers.

    Raises:
        TypeError: if a non-integer value is passed.
    """
    raise NotImplementedError()


def opengl_version() -> str:
    """Returns the version of OpenGL being used.
    """
    raise NotImplementedError()
