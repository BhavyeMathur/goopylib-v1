"""
Module that defines the Window class.
"""

from typing import Optional

from color import Color
import goopylib.ext.window as _window


# TODO some of the docstrings (especially the callback functions) are essentially plagiarised from GLFW's docs.


class Window:
    """
    Creates a Window that can be used to draw graphics and widgets.

    Args:
        width: in screen coordinates
        height: in screen coordinates
        title: displayed in the title bar
    """

    def __init__(self, width: int, height: int, title: str = "goopylib Window"):
        """
        Creates a Window that can be used to draw graphics and widgets.

        Args:
            width: in screen coordinates
            height: in screen coordinates
            title: displayed in the title bar
        """
        raise NotImplementedError()

    def __repr__(self) -> str:
        raise NotImplementedError()

    def is_closed(self) -> bool:
        """
        Returns whether the Window is closed.
        """
        raise NotImplementedError()

    def is_open(self) -> bool:
        """
        Returns whether the Window is open.
        """
        raise NotImplementedError()

    def is_destroyed(self) -> bool:
        """
        Returns whether the Window has been destroyed.
        """
        raise NotImplementedError()

    def update(self):
        """
        Refreshes the Window.
        """
        raise NotImplementedError()

    def destroy(self):
        """
        Destroys & closes the Window.

        Warning:
            Once the Window is destroyed, accessing its attributes or calling its methods is undefined.
        """
        raise NotImplementedError()

    """Getters & Setters --------------------------------------------------------------------------------------------"""

    # Width
    @property
    def width(self) -> int:
        """
        The width of the Window.

        Returns:
            The width, in screen coordinates, of the Window

        Raises:
            TypeError: width must be an int
            ValueError: width must be greater than 0
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @width.setter
    def width(self, value: int):
        raise NotImplementedError()

    # Height
    @property
    def height(self) -> int:
        """
        The height of the Window.

        Returns:
            The height, in screen coordinates, of the Window

        Raises:
            TypeError: height must be an int
            ValueError: height must be greater than 0
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @height.setter
    def height(self, value: int):
        raise NotImplementedError()

    # Title
    @property
    def title(self) -> str:
        """
        The title of the Window.

        Returns:
            A UTF-8 encoded string representing the Window's title

        Raises:
            TypeError: title must be a str
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @title.setter
    def title(self, value: str):
        raise NotImplementedError()

    # X Position
    @property
    def xpos(self) -> int:
        """
        The x position of the Window.

        Returns:
            The x position, in screen coordinates, of the upper-left corner of the Window on the monitor

        Raises:
            TypeError: xpos must be an int
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @xpos.setter
    def xpos(self, value: int):
        raise NotImplementedError()

    # Y Position
    @property
    def ypos(self) -> int:
        """
        The y position of the Window.

        Returns:
            The y position, in screen coordinates, of the upper-left corner of the Window on the monitor

        Raises:
            TypeError: ypos must be an int
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @ypos.setter
    def ypos(self, value: int):
        raise NotImplementedError()

    # Background Color
    @property
    def background(self) -> Color:
        """
        The background color of the Window.

        Returns:
            a color object

        Raises:
            TypeError: background must be a color
        """
        raise NotImplementedError()

    @background.setter
    def background(self, background: Color):
        raise NotImplementedError()

    # Minimum Width
    @property
    def min_width(self) -> int:
        """
        The minimum width of the Window.

        Defaults to 0.

        Returns:
            The minimum width the window can be resized to.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: min_width must be an int or None
            ValueError: min_width must be greater than or equal to 0
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @min_width.setter
    def min_width(self, value: int):
        raise NotImplementedError()

    # Minimum Height
    @property
    def min_height(self) -> int:
        """
        The minimum height of the Window.

        Defaults to 0.

        Returns:
            The minimum height the window can be resized to.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: min_height must be an int or None
            ValueError: min_height must be greater than or equal to 0
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @min_height.setter
    def min_height(self, value: int):
        raise NotImplementedError()

    # Maximum Width
    @property
    def max_width(self) -> int:
        """
        The maximum width of the Window.

        Defaults to None which represents no maximum width.

        Returns:
            The maximum width the window can be resized to.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: max_width must be an int or None
            ValueError: max_width must be greater than or equal to min_width
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @max_width.setter
    def max_width(self, value: Optional[int]):
        raise NotImplementedError()

    # Maximum Height
    @property
    def max_height(self) -> int:
        """
        The maximum height of the Window.

        Defaults to None which represents no maximum height.

        Returns:
            The maximum height the window can be resized to.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: max_height must be an int or None
            ValueError: max_height must be greater than or equal to min_height
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @max_height.setter
    def max_height(self, value: int):
        raise NotImplementedError()

    # Get & Set Methods
    def set_size(self, width: int, height: int):
        """
        Sets the size of the Window.

        Args:
            width: in screen coordinates
            height: in screen coordinates

        Raises:
            TypeError: width and height must be ints
            ValueError: width and height must be greater than 0
        """
        raise NotImplementedError()

    def set_size_limits(self, min_width: int, min_height: int, max_width: Optional[int], max_height: Optional[int]):
        """
        Sets the minimum and maximum resizable dimensions of the Window.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: All the parameters must be int or None
            ValueError: min_width and min_height must be greater than or equal to 0.
                max_width and max_height must be greater than or equal min_width and min_height
        """
        raise NotImplementedError()

    def set_min_size(self, min_width: Optional[int], min_height: Optional[int]):
        """
        Sets the minimum resizable dimensions of the Window.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: min_width and min_height must be ints
            ValueError: min_width and min_height must be greater than or equal to 0
        """
        raise NotImplementedError()

    def set_max_size(self, max_width: Optional[int], max_height: Optional[int]):
        """
        Sets the maximum resizable dimensions of the Window.

        Note:
            This attribute only applies to resizable Windows

        Raises:
            TypeError: max_width and max_height must be ints or None
            ValueError: max_width and max_height must be greater than or equal to min_width and min_height.
        """
        raise NotImplementedError()

    def setpos(self, xpos: int, ypos: int):
        """
        Sets the position of the top-left of the Window on the screen.

        Args:
            xpos: in screen coordinates
            ypos: in screen coordinates

        Raises:
            TypeError: xpos and ypos must be ints
        """
        raise NotImplementedError()

    def set_aspect_ratio(self, numerator: int, denominator: int):
        """
        Sets the aspect ratio of the Window.

        The aspect ratio is specified as a numerator and denominator, corresponding to the width and height,
        respectively. If you want a window to maintain its current aspect ratio, use its current size as the ratio.

        Set both arguments to None to remove any aspect ratio configuration.

        Raises:
            TypeError: numerator and denominator must be ints or None
            ValueError: numerator and denominator must be greater than 0
        """
        raise NotImplementedError()

    def get_aspect_ratio(self) -> tuple[int, int]:
        """
        Gets the current aspect ratio of the Window.

        Returns:
            A tuple representing the aspect ratio as (numerator, denominator)
        """
        raise NotImplementedError()

    def get_frame_size(self) -> tuple[int, int, int, int]:
        """
        Gets the size, in screen coordinates, of the Window frame.

        Decorated Windows  have title bars and window frames around them. You can retrieve the sizes of these using this
        method. The returned values are the distances, in screen coordinates, from the edges of the content area to the
        corresponding edges of the full window. As they are distances and not coordinates, they are always zero or
        positive.

        Returns:
            The size of the Window's frame in order (left, top, right, bottom)
        """
        raise NotImplementedError()

    def get_content_scale(self) -> tuple[float, float]:
        """
        Gets the scale of the content on the window.

        The content scale is the ratio between the current DPI and the platform's default DPI.

        Returns:
            A tuple representing the content scale as (xscale, yscale)
        """
        raise NotImplementedError()

    def get_framebuffer_size(self) -> tuple[int, int]:
        """
        The size of the framebuffer for the Window.

        Returns:
            A tuple (width, height) representing the dimensions, in pixels, of the framebuffer
        """
        raise NotImplementedError()

    """Window Attributes --------------------------------------------------------------------------------------------"""

    @property
    def resizable(self) -> bool:
        """
        Whether the Window is resizable by the user or not.

        Defaults to False.

        Returns:
            A boolean representing whether the user can resize the window

        Raises:
            TypeError: resizable must be a bool
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @resizable.setter
    def resizable(self, value: bool):
        raise NotImplementedError()

    # Decorated
    @property
    def decorated(self) -> bool:
        """
        Whether the Window has window decorations.

        Defaults to True

        Returns:
            A boolean representing whether the window has decorations like a border, close widget, etc.

        Note:
            An undecorated window will not be resizable by the user

        Raises:
            TypeError: decorated must be a bool
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @decorated.setter
    def decorated(self, value: bool):
        raise NotImplementedError()

    # Floating
    @property
    def floating(self) -> bool:
        """
        Whether the Window is always on top.

        Defaults to False

        Returns:
            A boolean representing whether the window is always on top of other regular windows.

        Raises:
            TypeError: floating must be a bool
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @floating.setter
    def floating(self, value: bool):
        raise NotImplementedError()

    # Auto Minimized
    @property
    def auto_minimized(self) -> bool:
        """
        Whether the Window is automatically minimized when it loses focus.

        Defaults to True

        Returns:
            A boolean representing whether the fullscreen window is always on top of other regular windows.

        Note:
            This attribute only applies to Windows in fullscreen.

        Raises:
            TypeError: auto_minimized must be a bool
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @auto_minimized.setter
    def auto_minimized(self, value: bool):
        raise NotImplementedError()

    # Focused on Show
    @property
    def focused_on_show(self) -> bool:
        """
        Whether the Window gains input focus when it is shown.

        Defaults to True

        Returns:
            A boolean representing whether calling window.show() gives this Window input focus

        Raises:
            TypeError: focused_on_show must be a bool
            RuntimeError: cannot set the attribute of a destroyed window
        """
        raise NotImplementedError()

    @focused_on_show.setter
    def focused_on_show(self, value: bool):
        raise NotImplementedError()

    """Window State Methods -----------------------------------------------------------------------------------------"""

    def restore(self):
        """
        Restores a minimized, maximized, or fullscreen Window back to normal.
        """
        raise NotImplementedError()

    # Fullscreen
    def fullscreen(self):
        """
        Makes the Window enter fullscreen mode.
        """
        raise NotImplementedError()

    def is_fullscreen(self):
        """
        Returns:
             whether the Window is in fullscreen mode.
        """
        raise NotImplementedError()

    # Maximize
    def maximize(self):
        """
        Maximizes the Window.
        """
        raise NotImplementedError()

    def is_maximized(self):
        """
        Returns:
             whether the Window is in maximized mode.
        """
        raise NotImplementedError()

    # Minimize
    def minimize(self):
        """
        Minimizes the Window.
        """
        raise NotImplementedError()

    def is_minimized(self):
        """
        Returns:
             whether the Window is in minimized mode.
        """
        raise NotImplementedError()

    # Visibility
    def show(self):
        """
        Makes the Window visible to the user.
        """
        raise NotImplementedError()

    def hide(self):
        """
        Makes the Window invisible to the user.
        """
        raise NotImplementedError()

    def is_visible(self):
        """
        Returns:
             whether the Window is visible to the user.
        """
        raise NotImplementedError()

    # Input Focus
    def focus(self):
        """
        Gives the Window input focus and brings it to the front.
        """
        raise NotImplementedError()

    def has_focus(self):
        """
        Returns:
             whether the Window has input focus.
        """
        raise NotImplementedError()

    def request_attention(self):
        """
        Requests for the user's attention to the Window.

        The system will highlight the Window, or on platforms where this is not supported, the application as a whole.
        Once the user has given it attention, the system will automatically end the request.
        """
        raise NotImplementedError()

    """Window Input Events ------------------------------------------------------------------------------------------"""

    def is_mouse_hovering(self):
        """
        Returns:
            whether the mouse is hovering over the Window.
        """
        raise NotImplementedError()

    def get_mouse_position(self) -> tuple[float, float]:
        """
        Returns:
            a tuple (xpos, ypos) with the position of the mouse cursor
        """
        raise NotImplementedError()

    def set_cursor_mode(self, mode: Literal["Normal", "Disabled", "Hidden"]):
        raise NotImplementedError()

    def check_shift_key(self) -> bool:
        """
        Returns:
            whether the shift key is being pressed
        """
        raise NotImplementedError()

    def check_control_key(self) -> bool:
        """
        Returns:
            whether the control key is being pressed
        """
        raise NotImplementedError()

    def check_alt_key(self) -> bool:
        """
        Returns:
            whether the alt key is being pressed
        """
        raise NotImplementedError()

    def check_super_key(self) -> bool:
        """
        Returns:
            whether the super key is being pressed
        """
        raise NotImplementedError()

    def check_key(self, keycode: int) -> bool:
        """
        Args:
            keycode: an int corresponding to the keycode

        Returns:
            whether the specified key is being pressed
        """
        raise NotImplementedError()

    def check_mouse_button(self, button: int) -> bool:
        """
        Args:
            button: an int corresponding to the mouse button

        Returns:
            whether the specified mouse button is being pressed
        """
        raise NotImplementedError()

    def check_left_click(self) -> bool:
        """
        Returns:
            whether the left mouse button is being pressed
        """
        raise NotImplementedError()

    def check_middle_click(self) -> bool:
        """
        Returns:
            whether the middle mouse button is being pressed
        """
        raise NotImplementedError()

    def check_right_click(self) -> bool:
        """
        Returns:
            whether the right mouse button is being pressed
        """
        raise NotImplementedError()

    """Window Callback Functions ------------------------------------------------------------------------------------"""

    # Resize Callback
    @property
    def resize_callback(self):
        """
        Callback executed when the Window is resized.

        The callback function receives the new size, in screen coordinates, of the content area of the window when the
        window is resized. It must follow the following template:

        .. code-block:: python

            def resize_callback(width: int, height: int):
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window is resized.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.resize_callback = resize_callback

                while window.is_open():
                    gp.update()
        """
        raise NotImplementedError()

    @resize_callback.setter
    def resize_callback(self, callback: callable):
        raise NotImplementedError()

    # Close Callback
    @property
    def close_callback(self):
        """
        Callback executed when the Window is attempted to be closed.

        The callback function is called directly after the window's close flag has been set. If you wish to be notified
        when the user attempts to close a window, set a close callback. It must follow the following template:

        .. code-block:: python

            def close_callback():
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
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
        """
        Callback executed when the Window is destroyed.

        The callback function is called directly after window.destroy().
        It must follow the following template:

        .. code-block:: python

            def destroy_callback():
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must not take arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message when the window is destroyed.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.destroy_callback = destroy_callback

                window.destroy()  # callback function is called
        """
        raise NotImplementedError()

    @destroy_callback.setter
    def destroy_callback(self, callback: callable):
        raise NotImplementedError()

    # Position Callback
    @property
    def position_callback(self):
        """
        Callback executed when the Window is moved.

        The callback function receives the new position, in screen coordinates, of the upper-left corner of the content
        area when the window is moved. It must follow the following template:

        .. code-block:: python

            def position_callback(xpos: int, ypos: int):
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window is moved.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.position_callback = position_callback

                while window.is_open():
                    gp.update()
        """
        raise NotImplementedError()

    @position_callback.setter
    def position_callback(self, callback: callable):
        raise NotImplementedError()

    # Minimize Callback
    @property
    def minimize_callback(self):
        """
        Callback executed when the Window is minimized.

        The callback function receives a bool representing whether the Window was minimized or restored
        to normal. It must follow the following template:

        .. code-block:: python

            def minimize_callback(minimized: bool):
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 1 argument
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window is minimized.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.minimize_callback = minimize_callback

                while window.is_open():
                    gp.update()
        """
        raise NotImplementedError()

    @minimize_callback.setter
    def minimize_callback(self, callback: callable):
        raise NotImplementedError()

    # Maximize Callback
    @property
    def maximize_callback(self):
        """Callback executed when the Window is maximized.

        The callback function receives a bool representing whether the Window was maximized or restored
        to normal. It must follow the following template:

        .. code-block:: python

            def maximize_callback(maximized: bool):
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 1 argument
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window is maximized.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.maximize_callback = maximize_callback

                while window.is_open():
                    gp.update()
        """
        raise NotImplementedError()

    @maximize_callback.setter
    def maximize_callback(self, callback: callable):
        raise NotImplementedError()

    # Focus Callback
    @property
    def focus_callback(self):
        """Callback executed when the Window gains input focus.

        The callback function receives a bool representing whether the Window gained or lost input focus.
        On most platforms, this means that the callback is called when the user minimizes a window, clicks on a
        window to make it active, or other similar actions.
        It must follow the following template:

        .. code-block:: python

            def focus_callback(focused: bool):
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 1 argument
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window gains or loses input focus.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.focus_callback = focus_callback

                while window.is_open():
                    gp.update()
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

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must not take arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example will print a message whenever the window gains or loses input focus.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.refresh_callback = refresh_callback

                while window.is_open():
                    gp.update()
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
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example sets a Window's content scale callback.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.content_scale_callback = content_scale_callback

                while window.is_open():
                    gp.update()
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
                # code here

        Raises:
            TypeError: cannot set the callback to a non callable
            ValueError: callback function must take 2 arguments
            RuntimeError: cannot set the callback of a destroyed window

        Examples:
            The following example sets a Window's framebuffer size callback.

            .. code-block:: python

                window = gp.Window(500, 500)
                window.framebuffer_size_callback = framebuffer_size_callback

                while window.is_open():
                    gp.update()
        """
        raise NotImplementedError()

    @framebuffer_size_callback.setter
    def framebuffer_size_callback(self, callback: callable):
        raise NotImplementedError()

    # Mouse Motion Callback
    @property
    def mouse_motion_callback(self):
        raise NotImplementedError()

    @mouse_motion_callback.setter
    def mouse_motion_callback(self, callback: callable):
        raise NotImplementedError()

    # Mouse Enter Callback
    @property
    def mouse_enter_callback(self):
        raise NotImplementedError()

    @mouse_enter_callback.setter
    def mouse_enter_callback(self, callback: callable):
        raise NotImplementedError()

    # Scroll Callback
    @property
    def scroll_callback(self):
        raise NotImplementedError()

    @scroll_callback.setter
    def scroll_callback(self, callback: callable):
        raise NotImplementedError()

    # Key Callback
    def set_key_callback(self, keycode: int, callback: callable):
        raise NotImplementedError()

    # Mouse Button Callback
    def set_mouse_button_callback(self, button: int, callback: callable):
        raise NotImplementedError()

    # Left Click Callback
    @property
    def left_click_callback(self):
        raise NotImplementedError()

    @left_click_callback.setter
    def left_click_callback(self, callback: callable):
        raise NotImplementedError()

    # Middle Click Callback
    @property
    def middle_click_callback(self):
        raise NotImplementedError()

    @middle_click_callback.setter
    def middle_click_callback(self, callback: callable):
        raise NotImplementedError()

    # Right Click Callback
    @property
    def right_click_callback(self):
        raise NotImplementedError()

    @right_click_callback.setter
    def right_click_callback(self, callback: callable):
        raise NotImplementedError()

    # Camera & Projection
    def get_camera(self):
        raise NotImplementedError()

    def to_world(self, x: float, y: float):
        raise NotImplementedError()

    def to_screen(self, x: float, y: float):
        raise NotImplementedError()

    @staticmethod
    def update_all():
        raise NotImplementedError()

    @staticmethod
    def destroy_all():
        raise NotImplementedError()
