<div align="center">
  <img src="https://github.com/BhavyeMathur/goopylib/blob/master/branding/logo/goopylib_primary_logo.svg?raw=true" width="500" height="250">
</div>

[![Downloads](https://static.pepy.tech/badge/goopylib)](https://pepy.tech/project/goopylib)
[![PyPI](https://img.shields.io/pypi/v/goopylib?color=0091b5&label=release)](https://pypi.org/project/goopylib/)
![PyPI - Python Version](https://img.shields.io/pypi/pyversions/goopylib?color=00a3b5)
[![PyPI - Wheel](https://img.shields.io/pypi/wheel/goopylib)](https://pypi.org/project/goopylib/#files)
[![GitHub](https://img.shields.io/github/license/BhavyeMathur/goopylib?color=0079b5)](./LICENSE.md)

-----------------

## What is it?
goopylib is powerful game, graphics, and GUI library for Python and C++ to build cross-platform applications.
It allows you to unlock the potential of OpenGL and low-level graphics with a high-level, simple-yet-powerful API.

### Key Features:
 - Cross-Platform & Powerful
 - Fast! Built-in batch-rendering & optimizations
 - Accessible through Python & C++
 - Simple code to create, transform, & animate images, quads, triangles, circles, and more
 - Automatic 2D Orthographic Camera & Camera Controller
 - Window & Mouse events: key & button presses, several callbacks, etc.

#### In Development:
 - Text Rendering
 - GUI Elements
 - Animation Engine
 - Texture Factory
 - Low-Level API Access

#### Future Plans:
 - 2D Rigid-Body Physics Engine
 - Sound & Lighting Engine
 - Profiling Tools
 - Build & Distribution Tools

## Examples

#### Solar System Simulator:
[![https://github.com/BhavyeMathur/goopylib-solar-system-simulation](https://github.com/BhavyeMathur/goopylib-solar-system-simulation/blob/c996a328501aef6e60d205bcf70d956958173d8c/assets/solar-system.gif?raw=true)](https://github.com/BhavyeMathur/goopylib-solar-system-simulation)

#### Brick Breaker:
[![https://github.com/BhavyeMathur/goopylib-brick-breaker](https://github.com/BhavyeMathur/goopylib-brick-breaker/blob/main/assets/img.png?raw=true)](https://github.com/BhavyeMathur/goopylib-brick-breaker)

#### Conway's Game of Life:
[![https://github.com/BhavyeMathur/goopylib-conways-game-of-life](https://github.com/BhavyeMathur/goopylib-conways-game-of-life/blob/main/assets/gif.gif?raw=true)](https://github.com/BhavyeMathur/goopylib-conways-game-of-life)

## Installation

**Requires Python ≥ 3.8.** To install goopylib on Windows or MacOS, use the
[Python Package Index (PyPI)](https://pypi.org/project/goopylib):

```sh
pip install goopylib
```
Wheels for Linux are not currently supported but coming as soon as I can build them!

## Tutorial

Let's start by creating a rectangle on an empty window:

```python
import goopylib as gp

window = gp.Window(700, 500)  # width=700, height=500

# centered at (0, 0), width=100, height=50
rect = gp.Rectangle((0, 0), 100, 50).draw(window)

while window.is_open():
    gp.update()
```

Inside the loop, you can check for events (or define [callbacks](https://goopylib.readthedocs.io/en/latest/api_reference/core/window.html#callback-functions) instead):

```python
while window.is_open():
    if window.check_key(gp.KEY_H):
        rect.hide()
    elif window.check_key(gp.KEY_S):
        rect.show()
    
    mousex, mousey = window.get_mouse_position()
    
    if rect.contains(mousex, mousey):
        print("Hovering over the rectangle!")
        
    gp.update()
```

Draw other shapes or more complex objects:

```python
img = gp.Image("filepath.png", (0, 0)).draw(window)
```

Install a simple camera controller that automatically moves, rotates, and zooms in & out!

```python
controller = gp.CameraController(window)

while window.is_open():
    # ...
    controller.update()
```

## Documentation

The documentation for goopylib can be found [here](https://goopylib.readthedocs.io/en/latest/index.html).
Please submit an issue or email bhavyemathur@gmail.com for any questions!

## Contributing & Usage

Contributions to goopylib are absolutely welcome! Please reach out to me if you have an idea or feature request or
submit a pull request yourself. I'd love to hear if you've used goopylib for a project—maybe we could even add some 
screenshots to a gallery. 

goopylib is licensed under the [Mozilla Public License Version 2.0](./LICENSE.md) which essentially enables you use 
and modify goopylib (commercially or otherwise) as long as you attribute the project! See
[choosealicense.com](https://choosealicense.com/licenses/mpl-2.0/) for more details.
