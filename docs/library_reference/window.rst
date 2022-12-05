Window
======

.. currentmodule:: goopylib

.. autoclass:: Window
    :undoc-members:

    .. automethod:: update
    .. automethod:: destroy
    .. automethod:: close
    .. automethod:: is_open
    .. automethod:: is_closed

    ----------

    |

    Window Attributes
    -----------------

    ``Window`` instances have many attributes that can be modified to configure the look of the Window. Here is a list:

    .. autosummary::
        :toctree: generated

        Window.width
        Window.height

        Window.x_position
        Window.y_position

        Window.title

        Window.resizable
        Window.min_width
        Window.min_height
        Window.max_width
        Window.max_height

        Window.decorated
        Window.floating
        Window.auto_minimized
        Window.focused_on_show

        Window.framebuffer_size

    .. automethod:: set_size
    .. automethod:: get_size
    .. automethod:: set_position
    .. automethod:: get_position

    .. note::

        These next attributes only apply to :func:`resizable<goopylib.resizable>` Windows

    .. automethod:: set_size_limits

    ----------

    .. automethod:: get_minimum_size
    .. automethod:: set_minimum_size

    ----------

    .. automethod:: get_maximum_size
    .. automethod:: set_maximum_size

    ----------

    .. automethod:: get_aspect_ratio
    .. automethod:: set_aspect_ratio
    .. automethod:: get_frame_size
    .. automethod:: get_content_scale

    |

    Window State Methods
    --------------------

    .. automethod:: is_fullscreen
    .. automethod:: fullscreen
    .. automethod:: unfullscreen

    ----------

    .. automethod:: is_minimized
    .. automethod:: minimize
    .. automethod:: is_maximized
    .. automethod:: maximize
    .. automethod:: restore

    ----------

    .. automethod:: is_visible
    .. automethod:: show
    .. automethod:: is_hidden
    .. automethod:: hide

    ----------

    .. automethod:: has_focus
    .. automethod:: set_focus
    .. automethod:: request_attention

    ----------

    |

    Window Events
    -------------

    .. automethod:: is_mouse_hovering

|

Callback Functions
------------------

The ``Window`` class provides several callback functions that can be set to execute code whenever certain events take place:

.. autosummary::
    :toctree: generated
    :nosignatures:

    Window.resize_callback
    Window.position_callback
    Window.close_callback
    Window.destroy_callback
    Window.minimize_callback
    Window.maximize_callback
    Window.focus_callback
    Window.refresh_callback
    Window.content_scale_callback
    Window.framebuffer_size_callback

These can be accessed and set like so:

.. code-block:: python

    def callback_function():
        print("Window has been destroyed")

        print(window.destroy_callback)  # default value is None
        window.destroy_callback = callback_function

.. autofunction:: set_buffer_swap_interval
