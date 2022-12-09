"""
Module that defines core and miscellaneous functions
"""

from typing import Union


def init():
    """Initializes goopylib internally.

    You do not need to call this function unless you have called :func:`gp.terminate()<goopylib.terminate>`.

    Raises:
        ImportError: if the initialization fails
    """
    raise NotImplementedError()


def terminate():
    """Terminates goopylib internally and destroys all open Windows.

    Note:
        You can reinitialize the library using :func:`gp.init()<goopylib.init>`
    """
    raise NotImplementedError()


def update():
    """Updates goopylib.

    Note:
        Internally calls ``glfwPollEvents()`` in C++

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

    Note:
        Internally calls ``glfwWaitEvents()`` in C++
    """
    raise NotImplementedError()


def update_timeout(timeout: Union[float, int] = None):
    """Updates goopylib after a duration has passed.

    Args:
        timeout (float): the rate at which to update goopylib. Defaults to :obj:`None`.

    Note:
        Internally calls ``glfwWaitEventsTimeout()`` in C++
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


def opengl_version() -> str:
    """Returns the version of OpenGL being used.
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

    Note:
        Internally calls ``glfwGetVideoMode(...)->refreshRate`` in C++
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

    Note:
        Internally calls ``glfwGetVideoMode(...)->width`` in C++
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

    Note:
        Internally calls ``glfwGetVideoMode(...)->height`` in C++
    """
    raise NotImplementedError()


def number_of_monitors() -> int:
    """Returns the number of monitors connected.

    Raises:
        RuntimeError: if goopylib has not been initialized

    Examples:
        >>> gp.number_of_monitors()
        1

    Note:
        Internally calls ``glfwGetMonitors(&count)`` in C++
    """
    raise NotImplementedError()
