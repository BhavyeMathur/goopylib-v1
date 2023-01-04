goopylib.Window
===============

.. currentmodule:: goopylib.core.window

.. autoclass:: Window
    :undoc-members:

    .. automethod:: is_closed
    .. automethod:: is_open
    .. automethod:: is_destroyed

    .. automethod:: update
    .. automethod:: destroy

    ----------

    Window Attributes
    -----------------

    ``Window`` instances have many attributes that can be modified to configure the look of the Window. Here is a list:

    .. autosummary::
        Window.width
        Window.height

        Window.title

        Window.xpos
        Window.ypos

        Window.background

        Window.min_width
        Window.min_height
        Window.max_width
        Window.max_height

        Window.resizable
        Window.decorated
        Window.floating
        Window.auto_minimized
        Window.focused_on_show

        Window.framebuffer_size

    .. automethod:: set_size
    .. automethod:: set_position
    .. automethod:: get_frame_size
    .. automethod:: get_content_scale
    .. automethod:: get_framebuffer_size

    .. note::

        These next attributes only apply to :func:`resizable<goopylib.window.Window.resizable>` Windows

    .. automethod:: set_size_limits
    .. automethod:: set_minimum_size
    .. automethod:: set_maximum_size

    ----------

    .. automethod:: get_aspect_ratio
    .. automethod:: set_aspect_ratio

    |

    Window State Methods
    --------------------

    .. automethod:: restore
    .. automethod:: fullscreen
    .. automethod:: is_fullscreen

    ----------

    .. automethod:: minimize
    .. automethod:: is_minimized
    .. automethod:: maximize
    .. automethod:: is_maximized

    ----------

    .. automethod:: show
    .. automethod:: hide
    .. automethod:: is_visible

    ----------

    .. automethod:: focus
    .. automethod:: has_focus
    .. automethod:: request_attention

    ----------

    |

    Window Events
    -------------

    .. automethod:: is_mouse_hovering
    .. automethod:: get_mouse_position
    .. automethod:: set_cursor_mode
    .. automethod:: check_shift_key
    .. automethod:: check_control_key
    .. automethod:: check_alt_key
    .. automethod:: check_super_key
    .. automethod:: check_key
    .. automethod:: check_mouse_button
    .. automethod:: check_left_click
    .. automethod:: check_middle_click
    .. automethod:: check_right_click

    |

    Camera & Projection
    -------------------

    .. automethod:: get_camera
    .. automethod:: to_world
    .. automethod:: to_screen

    |

    Static Methods
    --------------

    .. automethod:: update_all
    .. automethod:: destroy_all

|

Callback Functions
------------------

The ``Window`` class provides several callback functions that can be set to execute code whenever certain events take place:

.. autosummary::
    :toctree: generated
    :nosignatures:

    Window.resize_callback
    Window.close_callback
    Window.destroy_callback
    Window.position_callback
    Window.minimize_callback
    Window.maximize_callback
    Window.focus_callback
    Window.refresh_callback
    Window.content_scale_callback
    Window.framebuffer_size_callback
    Window.mouse_motion_callback
    Window.mouse_enter_callback
    Window.scroll_callback
    Window.left_click_callback
    Window.middle_click_callback
    Window.right_click_callback

These can be accessed and set like so:

.. code-block:: python

    def callback_function():
        print("Window has been destroyed")

    print(window.destroy_callback)  # default value is None
    window.destroy_callback = callback_function
