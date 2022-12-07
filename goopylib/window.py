"""
Module that defines the Window class.
"""

from typing import Optional
from color import Color


# noinspection PyUnresolvedReferences, PyPep8
class Window:
    """Creates a Window that can be used to draw widgets and graphics.

    Args:
        width: The width, in screen coordinates, of the Window
        height: The height, in screen coordinates, of the Window
        title: The title displayed in the title bar of the Window
    """

    # noinspection PyUnusedLocal
    def __init__(self, width: int, height: int, title: str = "New Window"):
        raise NotImplementedError()

    def __repr__(self) -> str:
        raise NotImplementedError()

    def update(self):
        """Refreshes the Window.

        Note:
            Internally calls ``glClear()``, and ``glfwSwapBuffers()``
        """
        raise NotImplementedError()

    def destroy(self):
        """Destroys & closes the Window.

        Warning:
            The Window cannot be used once destroyed. You can no longer access its attributes or call its methods.
        """
        raise NotImplementedError()

    def close(self):
        """Closes the Window, but does not destroy it.
        """
        raise NotImplementedError()

    def is_open(self):
        """Returns ``True`` if the Window is open.
        """
        raise NotImplementedError()

    def is_closed(self):
        """Returns ``True`` if the Window is closed.
        """
        raise NotImplementedError()

    """Getters & Setters --------------------------------------------------------------------------------------------"""

    # Width
    @property
    def width(self) -> int:
        """The width of the Window.

        Returns:
            The width, in screen coordinates, of the Window

        Note:
            Changing this value will call the Window's :func:`resize_callback<goopylib.resize_callback>`
            if it has been set

        Raises:
            TypeError: ``width`` must be an :obj:`int`
            ValueError: ``width`` must be greater than 0
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will change the width of the Window.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.width
                500
                >>> window.width = 750
                >>> window.width
                750
        """
        raise NotImplementedError()

    @width.setter
    def width(self, value: int):
        raise NotImplementedError()

    # Height
    @property
    def height(self) -> int:
        """The height of the Window.

        Returns:
            The height, in screen coordinates, of the Window

        Note:
            Changing this value will call the Window's :func:`resize_callback<goopylib.resize_callback>`
            if it has been set

        Raises:
            TypeError: ``height`` must be an :obj:`int`
            ValueError: ``height`` must be greater than 0
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will change the height of the Window.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.height
                500
                >>> window.height = 750
                >>> window.height
                750
        """
        raise NotImplementedError()

    @height.setter
    def height(self, value: int):
        raise NotImplementedError()

    # Size
    def get_size(self) -> tuple[int, int]:
        """Gets the width and height of the Window.

        Returns:
            A :obj:`tuple` (width, height) representing the dimensions of the Window
        """
        raise NotImplementedError()

    def set_size(self, width: int, height: int):
        """Sets the width and height, in screen coordinates, of the Window.

        Note:
            Changing this value will call the Window's :func:`resize_callback<goopylib.resize_callback>`
            if it has been set

        Raises:
            TypeError: ``width`` and ``height`` must be of type :obj:`int`
            ValueError: ``width``  and ``height`` must be greater than 0
        """
        raise NotImplementedError()

    # X Position
    @property
    def x_position(self) -> int:
        """The x position of the Window.

        Returns:
            The x position, in screen coordinates, of the upper-left corner of the Window on the monitor

        Note:
            Changing this value will call the Window's
            :func:`position_callback<goopylib.position_callback>` if it has been set

        Raises:
            TypeError: ``x_position`` must be an :obj:`int`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will change the x position of the Window.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.x_position
                506
                >>> window.x_position = 200
                >>> window.x_position
                200
        """
        raise NotImplementedError()

    @x_position.setter
    def x_position(self, value: int):
        raise NotImplementedError()

    # Y Position
    @property
    def y_position(self) -> int:
        """The y position of the Window.

        Returns:
            The y position, in screen coordinates, of the upper-left corner of the Window on the monitor

        Note:
            Changing this value will call the Window's
            :func:`position_callback<goopylib.position_callback>` if it has been set

        Raises:
            TypeError: ``y_position`` must be an :obj:`int`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will change the y position of the Window.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.y_position
                154
                >>> window.y_position = 200
                >>> window.y_position
                200
        """
        raise NotImplementedError()

    @y_position.setter
    def y_position(self, value: int):
        raise NotImplementedError()

    # Position
    def get_position(self) -> tuple[int, int]:
        """Gets the position of the Window.

        Returns:
            A :obj:`tuple` (xpos, ypos), in screen coordinates, representing the position of the top-left corner of the
            Window
        """
        raise NotImplementedError()

    def set_position(self, x_position: int, y_position: int):
        """Sets the position, in screen coordinates, of the top-left of the Window on the screen.

        Note:
            Changing this value will call the Window's
            :func:`position_callback<goopylib.position_callback>` if it has been set

        Raises:
            TypeError: ``x_position`` and ``y_position`` must be of type :obj:`int`
        """
        raise NotImplementedError()

    # Title
    @property
    def title(self) -> str:
        """The title of the Window.

        Returns:
            A UTF-8 encoded string representing the Window's title

        Note:
            Internally calls ``glfwSetWindowTitle()`` in C++

        Raises:
            TypeError: ``title`` must be a :obj:`str`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will change the title of the Window.

            .. code-block:: python

                >>> window = gp.Window(500, 500, "Original Title")
                >>> window.title
                Original Title
                >>> window.title = "New Title"
                >>> window.x_position
                200
        """
        raise NotImplementedError()

    @title.setter
    def title(self, value: str):
        raise NotImplementedError()

    # Resizable
    @property
    def resizable(self) -> bool:
        """Whether the Window is resizable by the user or not.

        Defaults to ``False``.

        Returns:
            A boolean representing whether the user can resize the window

        Note:
            Internally calls ``glfwGetWindowAttrib(GLFW_RESIZABLE)`` and ``glfwSetWindowAttrib(GLFW_RESIZABLE)`` in C++

        Raises:
            TypeError: ``resizable`` must be a :obj:`bool`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will make the Window resizable.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.resizable
                False
                >>> window.resizable = True
        """
        raise NotImplementedError()

    @resizable.setter
    def resizable(self, value: bool):
        raise NotImplementedError()

    # Minimum Width
    @property
    def min_width(self) -> int:
        """The minimum width of the Window.

        Defaults to ``None`` which represents no minimum width. You may set this attribute to an integer or ``None`` to
        remove this size limit.

        Returns:
            The minimum width the window can be resized to. ``None`` if no minimum value is set.

        Note:
            This attribute only applies to :func:`resizable<goopylib.resizable>` Windows

        Note:
            Internally calls ``glfwWindowSizeLimits()`` in C++

        Raises:
            TypeError: ``min_width`` must be an :obj:`int` or :obj:`None`
            ValueError: ``min_width`` must be greater than or equal to 0
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will set this attribute to a non-default value.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.min_width
                None
                >>> window.min_width = 300
        """
        raise NotImplementedError()

    @min_width.setter
    def min_width(self, value: int):
        raise NotImplementedError()

    # Minimum Height
    @property
    def min_height(self) -> int:
        """The minimum height of the Window.

        Defaults to ``None`` which represents no minimum height. You may set this attribute to an integer or ``None`` to
        remove this size limit.

        Returns:
            The minimum height the window can be resized to. ``None`` if no minimum value is set.

        Note:
            This attribute only applies to :func:`resizable<goopylib.resizable>` Windows

        Note:
            Internally calls ``glfwWindowSizeLimits()`` in C++

        Raises:
            TypeError: ``min_height`` must be an :obj:`int` or :obj:`None`
            ValueError: ``min_height`` must be greater than or equal to 0
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will set this attribute to a non-default value.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.min_height
                None
                >>> window.min_height = 300
        """
        raise NotImplementedError()

    @min_height.setter
    def min_height(self, value: int):
        raise NotImplementedError()

    # Maximum Width
    @property
    def max_width(self) -> int:
        """The maximum width of the Window.

        Defaults to ``None`` which represents no maximum width. You may set this attribute to an integer or ``None`` to
        remove this size limit.

        Returns:
            The maximum width the window can be resized to. ``None`` if no maximum value is set.

        Note:
            This attribute only applies to :func:`resizable<goopylib.resizable>` Windows

        Note:
            Internally calls ``glfwWindowSizeLimits()`` in C++

        Warning:
            This attribute must be greater than or equal to :func:`Window.min_width<goopylib.min_width>`

        Raises:
            TypeError: ``max_width`` must be an :obj:`int` or :obj:`None`
            ValueError: ``max_width`` must be greater than or equal to :func:`Window.min_width<goopylib.min_width>`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will set this attribute to a non-default value.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.max_width
                None
                >>> window.max_width = 1000
        """
        raise NotImplementedError()

    @max_width.setter
    def max_width(self, value: int):
        raise NotImplementedError()

    # Maximum Height
    @property
    def max_height(self) -> int:
        """The maximum height of the Window.

        Defaults to ``None`` which represents no maximum height. You may set this attribute to an integer or ``None`` to
        remove this size limit.

        Returns:
            The maximum height the window can be resized to. ``None`` if no maximum value is set.

        Note:
            This attribute only applies to :func:`resizable<goopylib.resizable>` Windows

        Note:
            Internally calls ``glfwWindowSizeLimits()`` in C++

        Warning:
            This attribute must be greater than or equal to :func:`Window.min_height<goopylib.min_height>`

        Raises:
            TypeError: ``max_height`` must be an :obj:`int` or :obj:`None`
            ValueError: ``max_height`` must be greater than or equal to :func:`Window.min_height<goopylib.min_height>`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will set this attribute to a non-default value.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.max_height
                None
                >>> window.max_height = 1000
        """
        raise NotImplementedError()

    @max_height.setter
    def max_height(self, value: int):
        raise NotImplementedError()

    # Size Limits

    def set_size_limits(self, min_width: Optional[int], min_height: Optional[int],
                        max_width: Optional[int], max_height: Optional[int]):
        """Sets the minimum and maximum resizable dimensions of the Window.

        Raises:
            TypeError: All the parameters must be :obj:`int` or :obj:`None`
            ValueError: ``min_width`` and ``min_height`` must be greater than or equal to 0
            ValueError: ``max_width`` and ``max_height`` must be greater than or equal to :func:`Window.min_width<goopylib.min_width>` and :func:`Window.min_height<goopylib.min_height>`
        """
        raise NotImplementedError()

    def get_minimum_size(self) -> tuple[int, int]:
        """Gets the minimum resizable dimensions of the Window.

        Returns:
            A (width, height) pair, in screen coordinates, representing the Window's minimum size.
            Returns ``None`` if the Window has no minimum size.
        """
        raise NotImplementedError()

    def set_minimum_size(self, min_width: Optional[int], min_height: Optional[int]):
        """Sets the minimum resizable dimensions of the Window.

        Raises:
            TypeError: ``min_width`` and ``min_height`` must be :obj:`int` or :obj:`None`
            ValueError: ``min_width`` and ``min_height`` must be greater than or equal to 0
        """
        raise NotImplementedError()

    def get_maximum_size(self) -> tuple[int, int]:
        """Gets the maximum resizable dimensions of the Window.

        Returns:
            A (width, height) pair, in screen coordinates, representing the Window's maximum size.
            Returns ``None`` if the Window has no maximum size.
        """
        raise NotImplementedError()

    def set_maximum_size(self, max_width: Optional[int], max_height: Optional[int]):
        # noinspection PyPep8
        """Sets the maximum resizable dimensions of the Window.

                        Raises:
                            TypeError: ``max_width`` and ``max_height`` must be :obj:`int` or :obj:`None`
                            ValueError: ``max_width`` and ``max_height`` must be greater than or equal to :func:`Window.min_width<goopylib.min_width>` and :func:`Window.min_height<goopylib.min_height>`
                        """
        raise NotImplementedError()

    # Decorated
    @property
    def decorated(self) -> bool:
        """Whether the Window has window decorations.

        Defaults to ``True``

        Returns:
            A boolean representing whether the window has decorations like a border, close widget, etc.

        Note:
            An undecorated window will not be resizable by the user

        Note:
            Internally calls ``glfwGetWindowAttrib(GLFW_DECORATED)`` and ``glfwSetWindowAttrib(GLFW_DECORATED)`` in C++

        Raises:
            TypeError: ``decorated`` must be a :obj:`bool`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will make the Window undecorated and remove its border and close widget.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.decorated
                True
                >>> window.decorated = False
        """
        raise NotImplementedError()

    @decorated.setter
    def decorated(self, value: bool):
        raise NotImplementedError()

    # Floating
    @property
    def floating(self) -> bool:
        """Whether the Window is always on top.

        Defaults to ``False``

        Returns:
            A boolean representing whether the window is always on top of other regular windows.

        Note:
            Internally calls ``glfwGetWindowAttrib(GLFW_FLOATING)`` and ``glfwSetWindowAttrib(GLFW_FLOATING)`` in C++

        Warning:
            Do not use this to implement fullscreen windows.
            Use :func:`Window.fullscreen()<goopylib.fullscreen>` instead.

        Raises:
            TypeError: ``floating`` must be a :obj:`bool`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will make the Window the top-most window.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.floating
                False
                >>> window.floating = True
        """
        raise NotImplementedError()

    @floating.setter
    def floating(self, value: bool):
        raise NotImplementedError()

    # Auto Minimized
    @property
    def auto_minimized(self) -> bool:
        """Whether the Window is automatically minimized when it loses focus.

        Defaults to ``True``

        Returns:
            A boolean representing whether the fullscreen window is always on top of other regular windows.

        Note:
            This attribute only applies to Windows in :func:`fullscreen<goopylib.fullscreen>`

        Note:
            Internally calls ``glfwGetWindowAttrib(GLFW_AUTO_ICONIFY)`` and ``glfwSetWindowAttrib(GLFW_AUTO_ICONIFY)``
            in C++

        Raises:
            TypeError: ``auto_minimized`` must be a :obj:`bool`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will set this attribute to ``False``.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.auto_minimized
                True
                >>> window.auto_minimized = False
        """
        raise NotImplementedError()

    @auto_minimized.setter
    def auto_minimized(self, value: bool):
        raise NotImplementedError()

    # Focused on Show
    @property
    def focused_on_show(self) -> bool:
        """Whether the Window gains input focus when it is shown.

        Defaults to ``True``

        Returns:
            A boolean representing whether calling :func:`Window.show()<goopylib.show>` gives this Window
            input focus

        Note:
            Internally calls ``glfwGetWindowAttrib(GLFW_FOCUS_ON_SHOW)`` and ``glfwSetWindowAttrib(GLFW_FOCUS_ON_SHOW)``
            in C++

        Raises:
            TypeError: ``focused_on_show`` must be a :obj:`bool`
            RuntimeError: cannot set the attribute of a destroyed window

        Examples:
            The following example will set this attribute to ``False``.

            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.focused_on_show
                True
                >>> window.focused_on_show = False
        """
        raise NotImplementedError()

    @focused_on_show.setter
    def focused_on_show(self, value: bool):
        raise NotImplementedError()

    # Framebuffer Size
    def get_framebuffer_size(self) -> tuple[int, int]:
        """The size of the framebuffer for the Window.

        Returns:
            A tuple (width, height) representing the dimensions, in pixels, of the OpenGL framebuffer

        Note:
            Internally calls ``glfwGetFramebufferSize()`` in C++

        Warning:
            This attribute cannot be set to another value

        Raises:
            NotImplementedError: cannot set this attribute to another value

        Examples:
            .. code-block:: python

                >>> window = gp.Window(500, 500)
                >>> window.framebuffer_size
                (1000, 1000)
        """
        raise NotImplementedError()

    # Background Color
    @property
    def background(self) -> Color:
        raise NotImplementedError()

    @background.setter
    def background(self, background: Color):
        raise NotImplementedError()

    # Aspect Ratio
    def set_aspect_ratio(self, numerator: int, denominator: int):
        """Sets the aspect ratio of the Window.

        The aspect ratio is specified as a numerator and denominator, corresponding to the width and height,
        respectively. If you want a window to maintain its current aspect ratio, use its current size as the ratio.

        raise NotImplementedError() ``None`` to both arguments to remove any aspect ratio configuration.

        Raises:
            TypeError: ``numerator`` and ``denominator`` must be :obj:`int` or :obj:`None`
            ValueError: ``numerator`` and ``denominator`` must be greater than 0
        """
        raise NotImplementedError()

    def get_aspect_ratio(self) -> tuple[int, int]:
        """Gets the current aspect ratio of the Window.

        Returns:
            A :obj:`tuple` representing the aspect ratio as a (numerator, denominator) pair
        """
        raise NotImplementedError()

    # Frame Size & Content Scale
    def get_frame_size(self) -> tuple[int, int, int, int]:
        """Gets the size, in screen coordinates, of the Window frame.

        Decorated Windows  have title bars and window frames around them. You can retrieve the sizes of these using this
        method. The returned values are the distances, in screen coordinates, from the edges of the content area to the
        corresponding edges of the full window. As they are distances and not coordinates, they are always zero or
        positive.

        Returns:
            The size of the Window's frame in order (left, top, right, bottom)
        """
        raise NotImplementedError()

    def get_content_scale(self) -> tuple[float, float]:
        """Gets the scale of the content on the window.

        The content scale is the ratio between the current DPI and the platform's default DPI.

        Returns:
            A :obj:`tuple` representing the content scale as a (xscale, yscale) pair
        """
        raise NotImplementedError()

    """Window State Methods -----------------------------------------------------------------------------------------"""

    def is_fullscreen(self):
        """Returns ``True`` if the Window is in fullscreen mode.
        """
        raise NotImplementedError()

    def fullscreen(self):
        """Makes the Window enter fullscreen mode.
        """
        raise NotImplementedError()

    def unfullscreen(self):
        """Makes the Window exit fullscreen mode.
        """
        raise NotImplementedError()

    # Minimize
    def is_minimized(self):
        """Returns ``True`` if the Window is in minimized mode.
        """
        raise NotImplementedError()

    def minimize(self):
        """Minimizes the Window.
        """
        raise NotImplementedError()

    # Maximize
    def is_maximized(self):
        """Returns ``True`` if the Window is in maximized mode.
        """
        raise NotImplementedError()

    def maximize(self):
        """Maximizes the Window.
        """
        raise NotImplementedError()

    # Restore
    def restore(self):
        """Restores a minimized, maximized, or fullscreen Window back to normal.
        """
        raise NotImplementedError()

    # Visibility
    def is_visible(self):
        """Returns ``True`` if the Window is visible to the user.
        """
        raise NotImplementedError()

    def show(self):
        """Makes the Window visible to the user.
        """
        raise NotImplementedError()

    def hide(self):
        """Makes the Window invisible to the user.
        """
        raise NotImplementedError()

    # Input Focus
    def has_focus(self):
        """Returns ``True`` if the Window has input focus.
        """
        raise NotImplementedError()

    def set_focus(self):
        """Gives the Window input focus and brings it to the front.

        Warning:
            Forcing the Window to the top can be disruptive to the user. For a less disruptive way of getting the user's
            attention to the window, see :func:`request_attention<goopylib.request_attention>`.
        """
        raise NotImplementedError()

    def request_attention(self):
        """Requests for the user's attention to the Window.

        The system will highlight the Window, or on platforms where this is not supported,
        the application as a whole. Once the user has given it attention, the system will automatically end the request.
        """
        raise NotImplementedError()

    """Window Events -----------------------------------------------------------------------------------------"""

    def is_mouse_hovering(self):
        """Returns ``True`` if the mouse is hovering over the Window.
        """
        raise NotImplementedError()

    def check_key(self, keycode: int):
        raise NotImplementedError()

    def check_shift_key(self):
        raise NotImplementedError()

    def check_alt_key(self):
        raise NotImplementedError()

    def check_control_key(self):
        raise NotImplementedError()

    def check_super_key(self):
        raise NotImplementedError()

    def set_key_callback(self, keycode: int, callback: callable):
        raise NotImplementedError()

    """Window Callback Functions ------------------------------------------------------------------------------------"""

    # Resize callback
    @property
    def resize_callback(self):
        """Callback executed when the Window is resized.

        The callback function receives the new size, in screen coordinates, of the content area of the window when the
        window is resized. It must follow the following template:

        .. code-block:: python

            def resize_callback(width: int, height: int):
                \"\"\"
                width - resized window width
                height - resized window height
                \"\"\"

        Note:
            Internally calls ``glfwSetWindowSizeCallback()`` in C++

        Warning:
            Do not use this callback to limit the window's size. Use
            :func:`Window.set_size_limits()<goopylib.set_size_limits>` instead

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the user resizes the window.

            .. code-block:: python

                window = gp.Window(500, 500)

                def resize_callback(width, height):
                    print("Window has been resized to", width, height)

                window.resize_callback = resize_callback

                while window.is_open():
                    window.update()

            The callback function is also called when the code changes the size of the window.

            .. code-block:: python

                window.height = 600  # callback function is called
                window.width = 500  # callback function is called
        """
        raise NotImplementedError()

    @resize_callback.setter
    def resize_callback(self, callback: callable):
        raise NotImplementedError()

    # Position Callback
    @property
    def position_callback(self):
        """Callback executed when the Window is moved.

        The callback function receives the new position, in screen coordinates, of the upper-left corner of the content
        area when the window is moved. It must follow the following template:

        .. code-block:: python

            def position_callback(xpos: int, ypos: int):
                \"\"\"
                xpos - the new x position of the window
                ypos - the new y position of the window
                \"\"\"

        Note:
            Internally calls ``glfwSetWindowPosCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the user moves the window.

            .. code-block:: python

                window = gp.Window(500, 500)

                def position_callback(xpos, ypos):
                    print("Window has been moved to", xpos, ypos)

                window.position_callback = position_callback

                while window.is_open():
                    window.update()

            The callback function is also called when the code changes the position of the window.

            .. code-block:: python

                window.x_position = 100  # callback function is called
                window.y_position = 0  # callback function is called
        """
        raise NotImplementedError()

    @position_callback.setter
    def position_callback(self, callback: callable):
        raise NotImplementedError()

    # Close Callback
    @property
    def close_callback(self):
        """Callback executed when the Window is attempted to be closed.

        The callback function is called directly after the window's close flag has been set. If you wish to be notified
        when the user attempts to close a window, set a close callback. It must follow the following template:

        .. code-block:: python

            def close_callback():
                # code here

        Note:
            Internally calls ``glfwSetWindowCloseCallback()`` in C++

        Warnings:
            I have no idea what the functionality is or how it works!

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must not take arguments
            RuntimeError: cannot set the callback of a destroyed window
        """
        raise NotImplementedError()

    @close_callback.setter
    def close_callback(self, callback: callable):
        raise NotImplementedError()

    # Destroy Callback
    @property
    def destroy_callback(self):
        """Callback executed when the Window is destroyed.

        The callback function is called directly after :func:`Window.destroy()<goopylib.destroy>`.
        It must follow the following template:

        .. code-block:: python

            def destroy_callback():
                # code here

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must not take arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message when the window is destroyed.

            .. code-block:: python

                window = gp.Window(500, 500)

                def destroy_callback():
                    print("Window has been destroyed")

                window.destroy_callback = destroy_callback

                window.destroy()  # callback function is called
        """
        raise NotImplementedError()

    @destroy_callback.setter
    def destroy_callback(self, callback: callable):
        raise NotImplementedError()

    # Minimize Callback
    @property
    def minimize_callback(self):
        """Callback executed when the Window is minimized.

        The callback function receives a :obj:`bool` representing whether the Window was minimized or restored
        to normal. It must follow the following template:

        .. code-block:: python

            def minimize_callback(minimized: bool):
                \"\"\"
                minimized - whether the window was minimized (True) or restored (False)
                \"\"\"

        Note:
            Internally calls ``glfwSetWindowIconifyCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 1 argument
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the user minimizes or restores the window.

            .. code-block:: python

                window = gp.Window(500, 500)

                def minimize_callback(minimized):
                    if minimized:
                        print("The Window was minimized")
                    else:
                        print("The Window was restored")

                window.minimize_callback = minimize_callback

                while window.is_open():
                    window.update()

            The callback function is also called when the code minimizes or restores the window

            .. code-block:: python

                window.minimize()  # callback function is called
                window.restore()  # callback function is called
        """
        raise NotImplementedError()

    @minimize_callback.setter
    def minimize_callback(self, callback: callable):
        raise NotImplementedError()

    # Maximize Callback
    @property
    def maximize_callback(self):
        """Callback executed when the Window is maximized.

        The callback function receives a :obj:`bool` representing whether the Window was maximized or restored
        to normal. It must follow the following template:

        .. code-block:: python

            def maximize_callback(maximized: bool):
                \"\"\"
                maximized - whether the window was maximized (True) or restored (False)
                \"\"\"

        Note:
            Internally calls ``glfwSetWindowMaximizeCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 1 argument
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the user maximizes or restores the window.

            .. code-block:: python

                window = gp.Window(500, 500)

                def maximize_callback(maximized):
                    if maximized:
                        print("The Window was maximized")
                    else:
                        print("The Window was restored")

                window.maximize_callback = maximize_callback

                while window.is_open():
                    window.update()

            The callback function is also called when the code maximizes or restores the window

            .. code-block:: python

                window.maximize()  # callback function is called
                window.restore()  # callback function is called
        """
        raise NotImplementedError()

    @maximize_callback.setter
    def maximize_callback(self, callback: callable):
        raise NotImplementedError()

    # Focus Callback
    @property
    def focus_callback(self):
        """Callback executed when the Window gains input focus.

        The callback function receives a :obj:`bool` representing whether the Window gained or lost input focus.
        On most platforms, this means that the callback is called when the user minimizes a window, clicks on a
        window to make it active, or other similar actions.
        It must follow the following template:

        .. code-block:: python

            def focus_callback(focused: bool):
                \"\"\"
                focused - whether the window gained (True) or lost (False) input focus
                \"\"\"

        Note:
            Internally calls ``glfwSetWindowFocusCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 1 argument
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window gains or loses input focus.

            .. code-block:: python

                window = gp.Window(500, 500)

                def focus_callback(focused):
                    if focused:
                        print("The Window gained input focus")
                    else:
                        print("The Window lost input focus")

                window.focus_callback = focus_callback

                while window.is_open():
                    window.update()

            The callback function is also called when the code sets the input focus to the window.

            .. code-block:: python

                window.set_focus()  # callback function is called
        """
        raise NotImplementedError()

    @focus_callback.setter
    def focus_callback(self, callback: callable):
        raise NotImplementedError()

    # Refresh Callback
    @property
    def refresh_callback(self):
        """Callback executed when the Window needs refreshing.

        If you wish to be notified when the contents of a window is damaged and needs to be refreshed, set a window
        refresh callback. On most platforms, this is called when the size of the window changes through resizing,
        minimizing, maximizing, and entering fullscreen. It must follow the following template:

        .. code-block:: python

            def refresh_callback():
                # code here

        Note:
            Internally calls ``glfwSetWindowRefreshCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must not take arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window gains or loses input focus.

            .. code-block:: python

                window = gp.Window(500, 500)

                def refresh_callback():
                    print("Refresh the window")

                window.refresh_callback = refresh_callback

                while window.is_open():
                    window.update()
        """
        raise NotImplementedError()

    @refresh_callback.setter
    def refresh_callback(self, callback: callable):
        raise NotImplementedError()

    # Content Scale Callback
    @property
    def content_scale_callback(self):
        """Callback executed when the Window's content scale changes.

        If you wish to be notified when the content scale of a window changes, whether because of a system setting
        change or because it was moved to a monitor with a different scale, set a content scale callback.
        The callback function receives the new content scale of the window.

        It must follow the following template:

        .. code-block:: python

            def content_scale_callback(xscale: float, yscale: float):
                \"\"\"
                xscale - the new x-axis content scale
                yscale - the new y-axis content scale
                \"\"\"

        Note:
            Internally calls ``glfwSetWindowContentScaleCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example sets a Window's content scale callback.

            .. code-block:: python

                window = gp.Window(500, 500)

                def content_scale_callback(xscale, yscale):
                    print("Window has new scaling", xscale, yscale)

                window.content_scale_callback = content_scale_callback

                while window.is_open():
                    window.update()
        """
        raise NotImplementedError()

    @content_scale_callback.setter
    def content_scale_callback(self, callback: callable):
        raise NotImplementedError()

    # Framebuffer Size Callback
    @property
    def framebuffer_size_callback(self):
        """Callback executed when the Window's framebuffer size changes.

        If you wish to be notified when the framebuffer of a window is resized, whether by the user or the system, set a
        framebuffer size callback.
        The callback function receives the new size of the window's framebuffer.

        It must follow the following template:

        .. code-block:: python

            def framebuffer_size_callback(width: float, height: float):
                \"\"\"
                width - the new width of the framebuffer
                height - the new height of the framebuffer
                \"\"\"

        Note:
            Internally calls ``glfwSetFramebufferSizeCallback()`` in C++

        Raises:
            TypeError: cannot set the callback to a non :obj:`callable`
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example sets a Window's framebuffer size callback.

            .. code-block:: python

                window = gp.Window(500, 500)

                def framebuffer_size_callback(width, height):
                    print("Window has a new framebuffer size", width, height)

                window.framebuffer_size_callback = framebuffer_size_callback

                while window.is_open():
                    window.update()
        """
        raise NotImplementedError()

    @framebuffer_size_callback.setter
    def framebuffer_size_callback(self, callback: callable):
        raise NotImplementedError()


# noinspection PyUnusedLocal
def set_buffer_swap_interval(value: int):
    """Sets the minimum number of monitor refreshes the driver should wait from the time before swapping Window buffers.

    Note:
        Internally calls ``glfwSwapInterval(...)`` in C++
    """
    raise NotImplementedError()
