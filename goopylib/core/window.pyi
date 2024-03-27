"""
Module that defines the Window class.
"""

from __future__ import annotations

from typing import Union, Tuple

from goopylib.color import Color
from goopylib.scene import Camera


class Window:
    """
    Creates a window that can be used to draw graphics and widgets.

    Args:
        width: in screen coordinates
        height: in screen coordinates
        title: displayed in the title bar
    """

    def __init__(self, width: int, height: int, title: str = "goopylib Window") -> None:
        """
        Creates a window that can be used to draw graphics and widgets.

        Args:
            width: in screen coordinates
            height: in screen coordinates
            title: displayed in the title bar
        """

    def __repr__(self) -> str:
        pass

    def is_closed(self) -> bool:
        """
        Returns:
             whether the window is closed.
        """

    def is_open(self) -> bool:
        """
        Returns:
             whether the window is open.
        """

    def is_destroyed(self) -> bool:
        """
        Returns:
            whether the window has been destroyed.
        """

    def update(self) -> None:
        """
        Refreshes the window.

        Raises:
            RuntimeError: window has been destroyed
        """

    def destroy(self) -> None:
        """
        Destroys & closes the window.

        Warning:
            Once the window is destroyed, accessing its attributes or calling its methods is undefined.
        """

    """Getters & Setters --------------------------------------------------------------------------------------------"""

    @property
    def width(self) -> int:
        """
        The width of the window.

        Returns:
            The width, in screen coordinates, of the window

        Raises:
            TypeError: width must be an int
            ValueError: width must be greater than 0
            RuntimeError: window has been destroyed
        """

    @width.setter
    def width(self, value: int) -> None:
        pass

    @property
    def height(self) -> int:
        """
        The height of the window.

        Returns:
            The height, in screen coordinates, of the window

        Raises:
            TypeError: height must be an int
            ValueError: height must be greater than 0
            RuntimeError: window has been destroyed
        """

    @height.setter
    def height(self, value: int) -> None:
        pass

    @property
    def title(self) -> str:
        """
        The title of the window.

        Returns:
            A UTF-8 encoded string representing the window's title

        Raises:
            TypeError: title must be a str
            RuntimeError: window has been destroyed
        """

    @title.setter
    def title(self, value: str) -> None:
        pass

    @property
    def xpos(self) -> int:
        """
        The x position of the window.

        Returns:
            The x position, in screen coordinates, of the upper-left corner of the window on the monitor

        Raises:
            TypeError: xpos must be an int
            RuntimeError: window has been destroyed
        """

    @xpos.setter
    def xpos(self, value: int) -> None:
        pass

    @property
    def ypos(self) -> int:
        """
        The y position of the window.

        Returns:
            The y position, in screen coordinates, of the upper-left corner of the window on the monitor

        Raises:
            TypeError: ypos must be an int
            RuntimeError: window has been destroyed
        """

    @ypos.setter
    def ypos(self, value: int) -> None:
        pass

    @property
    def position(self) -> Tuple[int, int]:
        """
        An (x, y) tuple representing the position of the top-left of the window on the screen.

        Returns:
            A tuple representing the (xpos, ypos) of the window in screen coordinates

        Raises:
            TypeError: position must be a tuple of integers
            RuntimeError: window has been destroyed
        """

    @position.setter
    def position(self, value: Tuple[int, int]) -> None:
        pass

    @property
    def background(self) -> Color:
        """
        The background color of the window.

        Returns:
            a color object

        Raises:
            TypeError: background must be a color
            RuntimeError: window has been destroyed
        """

    @background.setter
    def background(self, value: Color) -> None:
        pass

    @property
    def min_width(self) -> int:
        """
        The minimum width of the window.

        Defaults to 0.

        Returns:
            The minimum width the window can be resized to.

        Note:
            This attribute only applies to resizable windows.

        Raises:
            TypeError: min_width must be an int or None
            ValueError: min_width must be greater than or equal to 0
            RuntimeError: window has been destroyed
        """

    @min_width.setter
    def min_width(self, value: int) -> None:
        pass

    @property
    def min_height(self) -> int:
        """
        The minimum height of the window.

        Defaults to 0.

        Returns:
            The minimum height the window can be resized to.

        Note:
            This attribute only applies to resizable windows.

        Raises:
            TypeError: min_height must be an int or None
            ValueError: min_height must be greater than or equal to 0
            RuntimeError: window has been destroyed
        """

    @min_height.setter
    def min_height(self, value: int) -> None:
        pass

    @property
    def max_width(self) -> int:
        """
        The maximum width of the window.

        Defaults to None which represents no maximum width.

        Returns:
            The maximum width the window can be resized to.

        Note:
            This attribute only applies to resizable windows.

        Raises:
            TypeError: max_width must be an int or None
            ValueError: max_width must be greater than or equal to min_width
            RuntimeError: window has been destroyed
        """

    @max_width.setter
    def max_width(self, value: Union[int]) -> None:
        pass

    @property
    def max_height(self) -> int:
        """
        The maximum height of the window.

        Defaults to None which represents no maximum height.

        Returns:
            The maximum height the window can be resized to.

        Note:
            This attribute only applies to resizable windows.

        Raises:
            TypeError: max_height must be an int or None
            ValueError: max_height must be greater than or equal to min_height
            RuntimeError: window has been destroyed
        """

    @max_height.setter
    def max_height(self, value: int) -> None:
        pass

    # Get & Set Methods
    def set_size(self, width: int, height: int) -> None:
        """
        Sets the size of the window.

        Args:
            width: in screen coordinates
            height: in screen coordinates

        Raises:
            TypeError: width and height must be integers
            ValueError: width and height must be greater than 0
            RuntimeError: window has been destroyed
        """

    def set_size_limits(self, min_width: int, min_height: int, max_width: int, max_height: int) -> None:
        """
        Sets the minimum and maximum resizable dimensions of the window.

        Note:
            This attribute only applies to resizable windows

        Raises:
            TypeError: All the parameters must be integers or None
            ValueError: min_width and min_height must be greater than or equal to 0.
                max_width and max_height must be greater than or equal min_width and min_height
            RuntimeError: window has been destroyed
        """

    def set_min_size(self, min_width: Union[int], min_height: Union[int]) -> None:
        """
        Sets the minimum resizable dimensions of the window.

        Note:
            This attribute only applies to resizable windows

        Raises:
            TypeError: min_width and min_height must be integers
            ValueError: min_width and min_height must be greater than or equal to 0
            RuntimeError: window has been destroyed
        """

    def set_max_size(self, max_width: Union[int], max_height: Union[int]) -> None:
        """
        Sets the maximum resizable dimensions of the window.

        Note:
            This attribute only applies to resizable windows

        Raises:
            TypeError: max_width and max_height must be integers or None
            ValueError: max_width and max_height must be greater than or equal to min_width and min_height.
            RuntimeError: window has been destroyed
        """

    def set_aspect_ratio(self, numerator: Union[int], denominator: Union[int]) -> None:
        """
        Sets the aspect ratio of the window.

        |

        The aspect ratio is specified as a numerator and denominator, corresponding to the width and height,
        respectively. If you want a window to maintain its current aspect ratio, use its current size as the ratio.

        |

        Set both arguments to None to remove any aspect ratio configuration.

        Raises:
            TypeError: numerator and denominator must be integers or None
            ValueError: numerator and denominator must be greater than 0
            RuntimeError: window has been destroyed
        """

    def get_aspect_ratio(self) -> Tuple[int, int]:
        """
        Gets the current aspect ratio of the window.

        Returns:
            A tuple representing the aspect ratio as (numerator, denominator)

        Raises:
            RuntimeError: window has been destroyed
        """

    def get_frame_size(self) -> Tuple[int, int, int, int]:
        """
        Gets the size, in screen coordinates, of the window frame.

        |

        Decorated windows  have title bars and window frames around them. You can retrieve the sizes of these using this
        method. The returned values are the distances, in screen coordinates, from the edges of the content area to the
        corresponding edges of the full window. As they are distances and not coordinates, they are always zero or
        positive.

        Returns:
            The size of the window's frame in order (left, top, right, bottom)

        Raises:
            RuntimeError: window has been destroyed
        """

    def get_content_scale(self) -> Tuple[float, float]:
        """
        Gets the scale of the content on the window.

        |
        
        The content scale is the ratio between the current DPI and the platform's default DPI.

        Returns:
            A tuple representing the content scale as (xscale, yscale)

        Raises:
            RuntimeError: window has been destroyed
        """

    def get_framebuffer_size(self) -> Tuple[int, int]:
        """
        The size of the framebuffer for the window.
        
        Returns:
            A tuple (width, height) representing the dimensions, in pixels, of the framebuffer

        Raises:
            RuntimeError: window has been destroyed
        """

    """Window Boolean Attributes ------------------------------------------------------------------------------------"""

    @property
    def resizable(self) -> bool:
        """
        Whether the window is resizable by the user or not.

        Defaults to False.

        Returns:
            whether the user can resize the window

        Raises:
            TypeError: resizable must be a bool
            RuntimeError: window has been destroyed
        """

    @resizable.setter
    def resizable(self, value: bool) -> None:
        pass

    @property
    def decorated(self) -> bool:
        """
        Whether the window has window decorations.

        Defaults to True.

        Returns:
            whether the window has decorations like a border, close widget, etc.

        Note:
            An undecorated window will not be resizable by the user

        Raises:
            TypeError: decorated must be a bool
            RuntimeError: window has been destroyed
        """

    @decorated.setter
    def decorated(self, value: bool) -> None:
        pass

    @property
    def floating(self) -> bool:
        """
        Whether the window is always on top.

        Defaults to False.

        Returns:
            whether the window is always on top of other regular windows.

        Raises:
            TypeError: floating must be a bool
            RuntimeError: window has been destroyed
        """

    @floating.setter
    def floating(self, value: bool) -> None:
        pass

    @property
    def auto_minimized(self) -> bool:
        """
        Whether the window is automatically minimized when it loses focus.

        Defaults to True.

        Returns:
            whether the window is automatically minimized when it loses focus.

        Note:
            This attribute only applies to windows in fullscreen.

        Raises:
            TypeError: auto_minimized must be a bool
            RuntimeError: window has been destroyed
        """

    @auto_minimized.setter
    def auto_minimized(self, value: bool) -> None:
        pass

    @property
    def focused_on_show(self) -> bool:
        """
        Whether the window gains input focus when it is shown.

        Defaults to True.

        Returns:
            whether calling Window.show() gives this window input focus

        Raises:
            TypeError: focused_on_show must be a bool
            RuntimeError: window has been destroyed
        """

    @focused_on_show.setter
    def focused_on_show(self, value: bool) -> None:
        pass

    """Window State Methods -----------------------------------------------------------------------------------------"""

    def restore(self) -> None:
        """
        Restores a minimized, maximized, or fullscreen window back to normal.

        Raises:
            RuntimeError: window has been destroyed
        """

    def fullscreen(self) -> None:
        """
        Makes the window enter fullscreen mode.

        Raises:
            RuntimeError: window has been destroyed
        """

    def is_fullscreen(self) -> bool:
        """
        Returns:
             whether the window is in fullscreen mode.

        Raises:
            RuntimeError: window has been destroyed
        """

    def minimize(self) -> None:
        """
        Minimizes the window.

        Raises:
            RuntimeError: window has been destroyed
        """

    def is_minimized(self) -> bool:
        """
        Returns:
             whether the window is in minimized mode.

        Raises:
            RuntimeError: window has been destroyed
        """

    def maximize(self) -> None:
        """
        Maximizes the window.

        Raises:
            RuntimeError: window has been destroyed
        """

    def is_maximized(self) -> bool:
        """
        Returns:
             whether the window is in maximized mode.

        Raises:
            RuntimeError: window has been destroyed
        """

    def show(self) -> None:
        """
        Makes the window visible to the user.

        Raises:
            RuntimeError: window has been destroyed
        """

    def hide(self, hide: bool = True) -> None:
        """
        Makes the window invisible to the user.

        Args:
            hide: whether to hide/show the window

        Raises:
            RuntimeError: window has been destroyed
        """

    def is_visible(self) -> bool:
        """
        Returns:
             whether the window is visible to the user.

        Raises:
            RuntimeError: window has been destroyed
        """

    def focus(self) -> None:
        """
        Gives the window input focus and brings it to the front.

        Raises:
            RuntimeError: window has been destroyed
        """

    def has_focus(self) -> bool:
        """
        Returns:
             whether the window has input focus.

        Raises:
            RuntimeError: window has been destroyed
        """

    def request_attention(self) -> None:
        """
        Requests for the user's attention to the window.
        
        |
        
        The system will highlight the window, or on platforms where this is not supported, the application as a whole.
        Once the user has given it attention, the system will automatically end the request.

        Raises:
            RuntimeError: window has been destroyed
        """

    """Window Input Events ------------------------------------------------------------------------------------------"""

    def is_mouse_hovering(self) -> bool:
        """
        Returns:
            whether the mouse is hovering over the window.

        Raises:
            RuntimeError: window has been destroyed
        """

    def get_mouse_position(self) -> Tuple[float, float]:
        """
        Returns:
            a tuple (xpos, ypos) with the position of the mouse cursor in world coordinates

        Raises:
            RuntimeError: window has been destroyed
        """

    def set_cursor_mode(self, mode: str) -> None:
        """
        Normal:
            makes the cursor visible and behave normally.

        Hidden:
            hides the cursor when it is over the window.

        Disabled:
            hides and grabs the cursor, providing virtual and unlimited cursor movement.

        Args:
            mode: one of "Normal", "Disabled", or "Hidden"

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_mouse_button(self, button: int) -> bool:
        """
        Args:
            button: an int corresponding to the mouse button

        Returns:
            whether the specified mouse button is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_left_click(self) -> bool:
        """
        Returns:
            whether the left mouse button is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_middle_click(self) -> bool:
        """
        Returns:
            whether the middle mouse button is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_right_click(self) -> bool:
        """
        Returns:
            whether the right mouse button is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_shift_key(self) -> bool:
        """
        Returns:
            whether the shift key is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_control_key(self) -> bool:
        """
        Returns:
            whether the control key is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_alt_key(self) -> bool:
        """
        Returns:
            whether the alt key is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_super_key(self) -> bool:
        """
        Returns:
            whether the super key is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    def check_key(self, keycode: int) -> bool:
        """
        Args:
            keycode: an int corresponding to the keycode

        Returns:
            whether the specified key is being pressed

        Raises:
            RuntimeError: window has been destroyed
        """

    """Window Callback Functions ------------------------------------------------------------------------------------"""

    @property
    def resize_callback(self) -> callable:
        """
        Callback executed when the window is resized.
        
        It receives the new size, in screen coordinates, of the window when the window is resized. 
        
        |
        
        .. code-block:: python

            def resize_callback(width: int, height: int) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 2 arguments
            RuntimeError: window has been destroyed
        """

    @resize_callback.setter
    def resize_callback(self, value: callable) -> None:
        pass

    @property
    def close_callback(self) -> callable:
        """
        Callback executed when the window is attempted to be closed.
        
        It is called directly after the window's close flag has been set.
        
        |

        .. code-block:: python

            def close_callback() -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must not take arguments
            RuntimeError: window has been destroyed
        """

    @close_callback.setter
    def close_callback(self, value: callable) -> None:
        pass

    @property
    def destroy_callback(self) -> callable:
        """
        Callback executed when the window is destroyed.

        It is called directly after Window.destroy().
            
        |

        .. code-block:: python

            def destroy_callback() -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must not take arguments
            RuntimeError: window has been destroyed
        """

    @destroy_callback.setter
    def destroy_callback(self, value: callable) -> None:
        pass

    @property
    def position_callback(self) -> callable:
        """
        Callback executed when the window is moved.

        It receives the new position, in screen coordinates, of the upper-left corner of the window.
        
        |

        .. code-block:: python

            def position_callback(xpos: int, ypos: int) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 2 arguments
            RuntimeError: window has been destroyed
        """

    @position_callback.setter
    def position_callback(self, value: callable) -> None:
        pass

    @property
    def minimize_callback(self) -> callable:
        """
        Callback executed when the window is minimized.

        It receives a bool representing whether the window was minimized or restored to normal.
        
        |

        .. code-block:: python

            def minimize_callback(minimized: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @minimize_callback.setter
    def minimize_callback(self, value: callable) -> None:
        pass

    @property
    def maximize_callback(self) -> callable:
        """
        Callback executed when the window is maximized.

        It receives a bool representing whether the window was maximized or restored to normal.
        
        |

        .. code-block:: python

            def maximize_callback(maximized: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @maximize_callback.setter
    def maximize_callback(self, value: callable) -> None:
        pass

    @property
    def focus_callback(self) -> callable:
        """
        Callback executed when the window gains input focus.

        It receives a bool representing whether the window gained or lost input focus.

        |

        On most platforms, this means that the callback is called when the user minimizes a window, clicks on a
        window to make it active, or other similar actions.
        
        |

        .. code-block:: python

            def focus_callback(focused: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @focus_callback.setter
    def focus_callback(self, value: callable) -> None:
        pass

    @property
    def refresh_callback(self) -> callable:
        """
        Callback executed when the window needs refreshing.

        On most platforms, this is called when the size of the window changes through resizing, minimizing, maximizing, 
        and entering fullscreen.
        
        |

        .. code-block:: python

            def refresh_callback() -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must not take arguments
            RuntimeError: window has been destroyed
        """

    @refresh_callback.setter
    def refresh_callback(self, value: callable) -> None:
        pass

    @property
    def content_scale_callback(self) -> callable:
        """
        Callback executed when the window's content scale changes.

        It receives the new content scale of the window.
        
        |

        .. code-block:: python

            def content_scale_callback(xscale: float, yscale: float) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 2 arguments
            RuntimeError: window has been destroyed
        """

    @content_scale_callback.setter
    def content_scale_callback(self, value: callable) -> None:
        pass

    @property
    def framebuffer_size_callback(self) -> callable:
        """
        Callback executed when the window's framebuffer size changes.

        It receives the new size of the window's framebuffer.

        |

        .. code-block:: python

            def framebuffer_size_callback(width: float, height: float) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 2 arguments
            RuntimeError: window has been destroyed
        """

    @framebuffer_size_callback.setter
    def framebuffer_size_callback(self, value: callable) -> None:
        pass

    @property
    def mouse_motion_callback(self) -> callable:
        """
        Callback executed when the mouse moves.

        The callback function receives the position of the mouse.

        |

        .. code-block:: python

            def mouse_motion_callback(xpos: float, ypos: float) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 2 arguments
            RuntimeError: window has been destroyed
        """

    @mouse_motion_callback.setter
    def mouse_motion_callback(self, value: callable) -> None:
        pass

    @property
    def mouse_enter_callback(self) -> callable:
        """
        Callback executed when the mouse enters/exits the window.

        The callback function receives a bool representing whether the mouse entered or exited a window.

        |

        .. code-block:: python

            def mouse_enter_callback(entered: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @mouse_enter_callback.setter
    def mouse_enter_callback(self, value: callable) -> None:
        pass

    @property
    def scroll_callback(self) -> callable:
        """
        Callback executed when the mouse scrolls.

        The callback function receives floats representing the x and y components of the current scroll.

        |

        .. code-block:: python

            def scroll_callback(xscroll: float, yscroll: float) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 2 arguments
            RuntimeError: window has been destroyed
        """

    @scroll_callback.setter
    def scroll_callback(self, value: callable) -> None:
        pass

    def set_key_callback(self, keycode: int, value: callable) -> None:
        """
        Callback executed when a key is pressed.

        It receives an int representing if the key was released (0), pressed (1), or repeated (2)

        |

        .. code-block:: python

            def key_callback(action: int) -> None:
                # code here

        Args:
            keycode: an int corresponding to the key for which to set the callback
            value: the callback function

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    def set_mouse_button_callback(self, button: int, value: callable) -> None:
        """
        Callback executed when a mouse button is pressed.

        It receives a bool representing if the mouse button was pressed.

        |

        .. code-block:: python

            def mouse_button_callback(pressed: bool) -> None:
                # code here

        Args:
            button: an int corresponding to the mouse button for which to set the callback
            value: the callback function

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @property
    def left_click_callback(self) -> callable:
        """
        Callback executed when the left mouse button is clicked.

        The callback function receives a bool representing if the mouse button was pressed.

        |

        .. code-block:: python

            def left_click_callback(pressed: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @left_click_callback.setter
    def left_click_callback(self, value: callable) -> None:
        pass

    @property
    def middle_click_callback(self) -> callable:
        """
        Callback executed when the middle mouse button is clicked.

        The callback function receives a bool representing if the mouse button was pressed.

        |

        .. code-block:: python

            def middle_click_callback(pressed: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @middle_click_callback.setter
    def middle_click_callback(self, value: callable) -> None:
        pass

    @property
    def right_click_callback(self) -> callable:
        """
        Callback executed when the right mouse button is clicked.

        The callback function receives a bool representing if the mouse button was pressed.

        |

        .. code-block:: python

            def right_click_callback(pressed: bool) -> None:
                # code here

        Raises:
            TypeError: callback must be callable
            ValueError: callback function must take 1 argument
            RuntimeError: window has been destroyed
        """

    @right_click_callback.setter
    def right_click_callback(self, value: callable) -> None:
        pass

    def get_camera(self) -> Camera:
        """
        Returns:
            the Camera object associated with the window

        Raises:
            RuntimeError: window has been destroyed
        """

    def to_world(self, x: float, y: float) -> Tuple[float, float]:
        """
        Converts coordinates in screen space to world space.

        |

        (0, 0) is the upper-left of the window in screen space

        (width, height) is the lower-right in screen space

        Returns:
            a tuple (x, y) in world coordinates

        Raises:
            RuntimeError: window has been destroyed
        """

    def to_screen(self, x: float, y: float) -> Tuple[float, float]:
        """
        Converts coordinates in world space to screen space.

        |

        With the default camera projection, (0, 0) is the center in world space.

        Returns:
            a tuple (x, y) in screen coordinates

        Raises:
            RuntimeError: window has been destroyed
        """

    @staticmethod
    def update_all() -> None:
        """
        Updates all the windows currently active.
        """

    @staticmethod
    def destroy_all() -> None:
        """
        Destroys all active windows.
        """
