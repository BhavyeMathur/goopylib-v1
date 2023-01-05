API Reference
=============

goopylib is powerful game, graphics, and GUI library for Python and C++ to build cross-platform applications.
It allows you to unlock the potential of OpenGL and low-level graphics with a high-level, simple-yet-powerful API.

The library includes a few key components such as the :ref:`window<goopylib.window>`, :ref:`colors<goopylib.color>`,
and :ref:`renderable objects<goopylib.objects>` as well as helper classes such as
:ref:`camera controllers<Camera Controller>`, :ref:`easing functions<Easing Functions>`, and more!

To begin, import the library, set-up a controller, and begin drawing objects:

.. code-block:: python

    import goopylib as gp

    window = gp.Window(600, 400, "Here's a window!")
    controller = gp.CameraController(window)

    circle = gp.Circle((0, 0), 30).draw(window)

    while window.is_open():
        controller.update()   # use WASD to move around, QE to rotate, +- to zoom
        gp.update()

    gp.terminate()  # make sure to terminate the library once you're done


**Explore the key submodules:**

* :ref:`goopylib.core`
* :ref:`goopylib.window`
* :ref:`goopylib.objects`
* :ref:`goopylib.scene`
* :ref:`goopylib.color`
* :ref:`goopylib.maths<Easing Functions>`

.. toctree::
    :hidden:

    api_reference/core/core
    api_reference/core/window

    api_reference/objects
    api_reference/scene

    api_reference/color
    api_reference/maths/easing

    api_reference/events/keyboard
    api_reference/events/mouse
