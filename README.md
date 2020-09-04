# Goopylib

### Projects made using goopylib

As these are entire projects with a lot of code and non-goopylib elements, I have not supplied the code. But, if you want
 to look at example projects with code, skip to the 'Examples' section.

**1. A Pac-Man Recreation**

I worked on this as a school project and used the goopylib library to create fully functional Pac-Man Game! (and an arcade 
too!) Pac-Man runs around while the ghosts (all animated of course) chase after him! He must collect all the pellets and 
fruits to go on to the next level.

![Pac-Man Screenshot](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/Pac-Man.png)

**2. Multiplayer UNO**

During the COVID-19 Pandemic, my friends and I often hopped on a call and played a few games together: one such, was
 UNO. But the app we used was very laggy and didn't really function well. So I took it upon myself to create a 
 Multiplayer UNO game in 5 days or less - and I succeeded on day 6... *"but day indices start at 0 so it was really the 
 fifth day..."*. 

The game allows 2-7 players to play together and the graphics animate the cards, rotate them randomly, make them travel 
to the centre (as opposed to just instantly moving there) and more.

Here is a screenshot of the game:

![UNO Screenshot](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/MultiplayerUNO.png)

Avatar graphics are from freepik.com

**3. Activity Club Selection App**

My school has these weekly activity clubs where we all go to well, do activities. And every year, we sign up for 
activities using a pen & paper. Writing down our choices, handing them over to our teachers and waiting for them to sort 
through hundreds of entries and assign everybody a club - but not this year. This year I made an activity club selection 
app using the goopylib library that would automatically do all this work for you! 

Goopylib is compatible with auto-py-to-exe which means you can easily convert any program into a .exe file and mail it 
to anyone to use. Now mind you, this was made with an older version of goopylib so it did not contain lots of animations 
and visual feedback, but here is a screenshot anyways:

![Activity Selection App Screenshot](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/ActivtySelectionApp.png)

## Introduction
Goopylib is a simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern
 GUIs, games, and animations.

This graphics library is built upon John Zelle's graphics.py package which he made for use with his textbook "Python 
Programming: An Introduction to Computer Science". Over the past 2 years, I have worked on editing this library to add 
more features to use with making my GUIs and games. My entire aim while editing was to create a powerful medium to
 enable me to create good-looking graphics within Python and I have spent a lot of time making sure this is the case. 
 Thus, this is a very intuitive, simple to use package with the potential of growing into one of the best Python 
 Graphics Libraries. 

If you would want to contribute to this library by suggesting features, reporting bugs, or adding changes yourself, 
please do so. I would love it if you would use this library in your projects and do make sure to tell me about them! 
Right now, this is very much an alpha stage - there are many bugs, many features that aren't compatible with each other, 
and a ton of things to do differently, but this will all be fixed with future releases. 

Goopylib is also compatible with [auto-py-to-exe](https://pypi.org/project/auto-py-to-exe/) also known as Pyinstaller. 
This compatibility mainly means that all paths to textures & sounds are automatically converted into the absolute paths 
which you don't have to worry about! This means that you will be able to convert applications written with goopylib into
executables with, hopefully, no errors.  

If you want to contact me, you can drop me an email at: bhavyemathur@gmail.com or post an issue on the issues tab.

### Installation

The Primary method to install this library is from [PyPi](https://pypi.org/project/goopylib/) via pip:

```terminal
pip install goopylib
```
 or 
 
 ```terminal
 pip3 install goopylib
 ```
 
 This will install Goopylib and all the requirements for it to run. You can then import the library as shown next.

An alternative method to use this library is very simple to use especially if you want access to the source code, all 
you need is the folder called 'goopylib' and the requirements. This just includes the 
[Pillow](https://pypi.org/project/Pillow/) (PIL) module which you can download individually. 

Download the folder and place it wherever you want access to the library. 

Then, simply import as so:

```python

from goopylib.imports import *
# or
import goopylib as gp

```

The first allows you to import everything that is part of the library, but if you want only specific classes 
z& functions, read on. 


### Organization

Goopylib is organized into a few different files and depending on what you want to do, you can import these files. 
There are 5 subpackages in goopylib: objects, math, sound, physics, & applications. 

To import these, type:

```python
from goopylib.math.BezierCurve import BezierCurve # The other modules are 'Interpolation', & 'BSpline'
# or
from goopylib.objects.Rectangle import Rectangle  # For a list of graphics objects, look at the documentation
```

To access elements of goopylib like the Point & GraphWin classes, Colours, etc. use this:

```python
from goopylib.colours import *

from goopylib.Window import Window
from goopylib.Point import Point
```


### Documentation

There are plans to create a detailed documentation for this library both in the form of YouTube videos and a written
 document and the creation of the documentation has begun at: https://github.com/BhavyeMathur/goopylib/wiki


### Examples

These examples with the code and required textures are included in folders for you to download and try out for 
yourselves!

1. This is a simple, modern, light Login Page that can be used for your application. It demonstrates the usage of 
Checkbox, Entries, and Buttons to take input from the user and was made entirely with just 60 lines of code!. 

This includes giving the user visual feedback if they hover over a button, making sure the user has entered a valid 
input, a functional tab to change from registering to signing up, and more

![GUI Screenshot](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/ModernUI-LoginPage%20Example/ExampleScreenshot.png)

2. Also provided is a very simple animation of Pac-Man being chased by some ghosts and it was created with just 13 lines 
of code! This really is an example of how simple animations such as these can help make a really good game or project. 

Goopylib also has functionality for other animations such as moving to locations, rotating animations, and a lot more. 
It also contains easy-to-use easing functions like those you would find in a professional animator.

![Pac-Man Animation Example](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/Pac-Man-Animation%20Example/Pac-ManAnimation.png)


## Contributions

1. Reblochon Masque, https://stackoverflow.com/questions/62715279/creating-rounded-edges-for-a-polygon-in-python - 3rd July 2020 - Help with creating rounded polygon corners
2. Spectral Doy - 3rd July 2020 - Helpin~~~~g me choose a name! we went through a lot of options... pyraphics, oreopy, pyllustrate, guipy... barnacle...
3. John Zelle - Creating the graphics.py package which formed the basis for my library.

4. Nico Schertler, https://stackoverflow.com/questions/62738195/python-zerodivisionerror-in-open-uniform-b-spline-curve - 4th July 2020 - Helped fix a ZeroDivisionError with Open Unifrom B-Splines
5. Bryan Oakley, https://stackoverflow.com/questions/62740726/tkinter-polygons-width-not-being-set-to-zero-even-though-specified/62741739#62741739 - 4th July 2020 - Helped fix bug with Polygons drawing their outlines even though the width is 0 
6. Atlast435, https://stackoverflow.com/questions/62751626/tkinter-rotated-resizing-cursor - 6th July 2020 - Helped expand the list of supported cursors by refering me to a documentation.
7. Sinoroc, https://stackoverflow.com/questions/62772377/python-package-does-not-get-created-in-site-packages-folder? - 7th July 2020 - Helped fix bug with Packaging
8. Cool Cloud, https://stackoverflow.com/questions/62809413/hide-text-cursor-in-tkinter-entry - 9th July 2020 - Helped with hiding & showing the Entry cursor
9. Bryan Oakley, https://stackoverflow.com/questions/62809413/hide-text-cursor-in-tkinter-entry - 9th July 2020 - Helped with Unfocusing the Entry widget when the user clicks elsewhere
10. Bryan Oakley, https://stackoverflow.com/questions/62836960/what-interpolation-does-tkinter-use-for-curves - 10th July 2020 - Helped with answering a question about smoothing in Tkinter

## Version History

Unfortunately, online school (Grade 9!!!) has started and so updates won't be coming out as frequently as before, sorry!

### v1.1

There are probably still a lot of bugs in the release version, but I moved onto Version 1.1 because I started working 
on a Sound Engine for goopylib which I want to be part of 1.1

#### 1.1.43-alpha6 3rd-4th September 2020

* Fixed `destroy()` function with Buttons
* Fixed bug with the Button's `move()` functions not working properly due to bug with the anchor being moved twice
* Added more getter functions to the Entry & MultilineEntry classes
* Added more setter functions to the MultilineEntry class

* Fixed bug with Checkbox state changing not undrawing the previous state properly
* Fixed more bugs with the Checkbox not undrawing when changing sate when using non-button states
* You can now bind the state of a Checkbox to the state of another

* Fixed the state argument in Checkboxes which was setting its state to the opposite state of the one inputted
* Added a setter & getter function for text inside a multiline entry

#### 1.1.35-alpha5 1st-2nd September 2020 

* Fixed AttributeError in the _BBox `set_resizable()` function because of using the `append()` function on a set, 
should have been `add()`
* Added a max_characters variable to the Entry class to control the max number of characters the user can enter
* Added a multiline entry class to create... multi-line entries.

* You can use tags for setting bounds for GraphicsObjects
* Added Dragging functions for the Window class
* Added bounding bounds for the Window class
* Added getter functions to get the position of the window

#### 1.1.28-alpha4 22nd August 2020

* Fixed bug with Window destroy all instance functions raising RunTime Errors

* The Ear Clipping Triangulation function now creates a copy of the input vertex chain
* The Ear Clipping Triangulation function now returns a list of the input vertices if their length is 3, ie 
`[(edge1, edge2, edge3)]` and not `(edge1, edge2, edge3)`
* Made the Ear Clipping Algorithm run a little bit faster than before
* The Triangulation Algorithms now accept tuples of vertices rather than just lists

* The GraphicsObject `has_moved()` function now returns False if the object has just been created
* Added a modified ear clipping algorithm for triangulating polygons that runs in O(n^2) time

* Started work on plane sweep triangulation algorithm which runs in O(n log n) time

#### 1.1.20-alpha3 20th-21st August 2020

* Made Animated Image moving much faster
* Added an optional parameter to the GraphWin's `update_win()` function to control how often a window updates
* Renamed the GraphWin class to Window

* You can now use a Window object as movement bounds for objects
* The Rectangle Class now reorganizes it's point coordinate values to be lowest for p1
* Fixed bug with the Window `get_coords()` function not returning the values in the proper order

#### 1.1.14-alpha2 18th-19th August 2020

* Fixed some text set attribute functions to work properly
* Fixed the text justify attribute to work properly with 1 line of text
* Replaced the `.format()` function in the Text `__repr__()` function with a f-string

* Added clicking bounds for the entry & button objects
* Added an `is_clicked()` function for Text objects
* You can now align Entry objects to left, right, top, bottom, etc. positions

* Fixed bug with AttributeError for the Rectangle `is_clicked()` function is mouse_pos is None

#### 1.1.7-alpha1 17th August 2020

* Fixed bug with Button not undrawing hover graphic when the user stopped hovering over the object
* Removed print statement in the GraphicsObject class
* Fixed bug with CycleButtons with AnimatedImages as states not working properly

#### 1.1.5-alpha0 7th-8th August 2020

* Added a Sound class that plays, pauses, crops, & destroys sounds. You can play multiple sounds & get data for each 
sound
* Added `__init__.py` files to the physics & sound subpackages
* Added `create_sin_wave()`, `create_square_wave()`, and `create_sawtooth_wave()` functions to create a simple sounds

* You can now create sounds by simply inputting a list of frequencies into a function. 
* Added numpy as a dependency as it is used for matrix multiplication in the Bezier Curve functions (soon to be removed 
though)

#### 

### v1.0

#### 1.0.226 3rd August 2020

* Added a `has_moved()` to the GraphicsObject class to check if the object has moved from the last call
* Fixed instances of misspelt lines to line which was causing a name error

* Got rid of the Image cache in the Image class as it was mainly unnecessary
* Added empty physics & sounds folders to goopylib

#### 1.0.222-beta 2nd August 2020

* Fixed bug with Cycle Button raising AttributeError when changing state and created but not drawn
* Fixed bug with Animated Image drawing itself when redrawing
* Fixed bug with the Cycle Button's `set_state()` function not working properly when the object wasn't drawn

* Added `__iter__` function to the Animated Image and Cycle Button classes
* Added a `set_bounds()` function to the GraphicsObject class
* The Cycle Button's `is_clicked()` function now checks if its the bounds if it is not None

* Checking for Obstacle & Movement Bounds collisions now uses the Graphic's Movement Bounds if they are not None
* Added layering functions to the Animated Image class

#### 1.0.214-beta 1st August 2020

* The Animated Image sets its autoflush to False whenever it is bound to another object
* Fixed bug with the CycleButton (& Checkbox) `draw()` function not working properly when no graphwin is provided
* Fixed recursion bug with layering in CycleButtons (& Checkboxes)
 
* The Image `__repr__()` function now returns the filepath in "
* Fixed bug with Image not updating itself for transformations after being drawn

* Added transformation functions for the CycleButton class
* Fixed bug with not allowing duplicate animations not working properly
* Fixed bug with GraphicsObject gliding not working properly in queues
* Fixed bug with rotation animations not working properly in queues and the `animate_set_rotation()` function

* Added a "Final" metric to check if animations are the same

#### 1.0.204-beta 31st July 2020

* Added a `set_default_sampling()` function to the Image class to set the default sampling
* Added a `set_texture_path()` function to the Image class
* Fixed bug with Image not redrawing after flipping

* Fixed bug with the GraphicsObject `is_selected()` function raising an error
* The CheckBox class now inherits from the CycleButton class (it's a special case of 2 states)

#### 1.0.199-beta 26th-28th July 2020

* Fixed bug with GraphicsObject raising error if the directional move functions weren't provided with a callback 
function
* Adding functions to enable the obstacles of an object: `set_obstacles_enabled()`, `disable_obstacles()`, 
`enable_obstacles()`, and `toggle_obstacles_enabled()`
* Replaced the for loops in goopylib with the `map()` function wherever in the GraphWin class possible to improve 
performance
* Added an `undraw_obstacles()` function 

* Added `animating_blur_time_left()` and `check_is_animating_blur()` functions to the GraphicsObject class
* Fixed bug with objects not animating properly
* Fixed bug with objects not blinking when gliding

* Optimized the Animated Image and Cycle Button drawing functions and a lot more

      Tested 60,000 frames on a test game as opposed to v1.0.190-beta's 20,000 frames
      FPS increased from ~7200 FPS to ~39470 FPS
      
      Trial 1: 1.542 secs, 38910.506 FPS
      Trial 2: 1.49 secs, 40268.456 FPS
      Trial 3: 1.633 secs, 36742.192 FPS
      Trial 4: 1.445 secs, 41522.491 FPS
      Trial 5: 1.491 secs, 40241.449 FPS
      
      Average: 1.520 secs, 39468.491 FPS
      
* Added a callback function for incrementing Animated Image frames
      
#### 1.0.190-beta 25th July 2020 

* Added a `set_object()` function to the CycleButton class to set the state to a GraphicsObject
* The Image class destroys itself before updating to save on memory and stop the drops in FPS as time went on
* Added a `bind_frame_to()` function to the Animated Image class to synchronize the frames of multiple objects

* More Optimizations (for performance values before, check previous version history)

      These were tested on 20,000 frames as opposed to yesterday's 2400 frames
      FPS increased from ~3040 FPS to ~7200 FPS
      
      Trial 1: 2.845 secs, 7029.877 FPS
      Trial 2: 2.774 secs, 7209.805 FPS
      Trial 3: 2.598 secs, 7698.229 FPS
      Trial 4: 2.535 secs, 7889.546 FPS
      Trial 5: 3.146 secs, 6357.279 FPS
      
      Average: 2.78 secs, 7195.28 FPS
      
* Fixed bug with Images not resizing properly to fit the window scale
* Added a `copy_movement_bounds_from()` & `set_allow_movement_looping()` function
* Added a callback argument for movement collisions

#### 1.0.183-beta 24th July 2020

* Fixed bug with Polygon Triangulation where the last triangle wasn't added to the list of triangles
* Added a `copy_obstacles_from()` function to copy the obstacles of another object
* Added object tagging which allows the user to access a GraphicsObject through tags (can be strings, ints, etc.)
* Objects now store their instances in sets to make the code faster
* The Animated Image class now calls the `_move()` function of the Image objects and not the `move()` function
* Performance Upgrades! tested 2400 frames on test game with cProfile:
 
      FPS increased from ~650 FPS to ~3040 FPS
      
      BEFORE: -------------------------
      
      Trial 1: 4.025 secs, 596.273 FPS
      Trial 2: 3.959 secs, 606.214 FPS
      Trial 3: 3.663 secs, 655.201 FPS
      Trial 4: 3.013 secs, 796.548 FPS
      Trial 5: 3.864 secs, 621.118 FPS
      
      Average: 3.705 secs, 647.808 FPS
      
      AFTER: --------------------------
      
      Trial 1: 0.871 secs, 2755.454 FPS
      Trial 2: 0.686 secs, 3498.542 FPS
      Trial 3: 0.749 secs, 3204.272 FPS
      Trial 4: 0.928 secs, 2586.207 FPS
      Trial 5: 0.712 secs, 3370.787 FPS
            
      Average: 0.789 secs, 3041.054 FPS
      
* The _BBox objects' `is_clicked()` functions run about 2841.3% (~285x) faster faster!
* Added `get_height()` and `get_width()` functions to the Polygon class
* The Polygon `get_height()` and `get_width()` functions no longer recalculate the height & width 

* Reorganized the if statement arguments to reduce processing time in the `_on_mouse_motion()` function
* Transform class `screen()` function now returns a float object
* The GraphicsObject doesn't iterate through all the objects now, only the ones that are required to improve performance

#### 1.0.172-beta 23rd July 2020

* Added the ear clipping triangulation algorithm to goopylib.math 
* The GraphWin functions that don't return anything now return self
* The GraphWin's `set_coords()` function no longer redraws the window if autoflush is False
* Added destroy and undraw all instance functions to destroy all of specific GraphicsObjects

* Fixed the bounds argument to work correctly with the Circle's `is_clicked()` function
* Every GraphicsObject moves & rotates its bounds when the transformation is performed on the object
* Added Simple Polygonal Bounding Boxes

#### 1.0.166-beta 21st-22nd July 2020

Sorry, but I haven't been able to get out as many changes today. I've been working on creating YouTube videos for goopy
which should come out soon!

* Added a `set_enabled()` function to the CycleButton class
* Added layering functions to the CycleButton class to override the behaviour of state objects
* The Image & Animated Image `__repr__()` functions now return a shorter string with the smallest filepath
* Fixed code to change the value of the object layer when the `set_layer()` function is called
* The layering system now checks if an object has been drawn before drawing it on top

* Performance upgrades (on test code, update time from 0.0008 secs to 0.0003) to the layering system
* More Performance upgrades to stop the unnecessary redrawing of Graphics Objects (on test code, update time from 0.0003 
secs to .00013 secs)
* Changed all lists in constants.py to be sets to increase performance 
([wiki.python.org](https://wiki.python.org/moin/PythonSpeed))
* Changed the directional move functions to correctly align with intuitive axes (forward being up, not down)
* Image rotation now happens clockwise instead of anticlockwise

* Added a `set_movement_bounds()` method to the GraphicsObject class to confine the movement of an object
* Added a `destroy()` function to the GraphicsObject class to completely remove an object
* Added object rotation for Polygons

#### 1.0.153-beta 20th July 2020 - 7852 lines of code

* Fixed bug with Images rotating twice the amount than they should be
* The GraphicsObject class now uses a dictionary to store the animation queues 
* Fixed the contrast animation for images to work properly after it wasn't due to an internal bug
* Added animation functions for Images to change the blur of the image

* Image blurring & filter functions now work correctly with rotation and other transformations
* Fixed bug with Image blurring animation functions not using easing correctly
* Added a layering system to draw graphics in front of and behind others!
* Added functions for the layering system: `move_up_layer()`, `move_down_layer()`, `set_layer()`, and 
`get_layer_objects()`
* Added errors to the GraphicsObject class and fixed some errors in the GraphWin class

#### 1.0.144-beta 19th July 2020

* Fixed Bug with AnimatedImages with not incrementing the frame when being drawn r epeatedly 
* An object no longer rotates if the amount to rotate by is 0 (or if the rotation is already the amount specified)
* Fixed bug with AnimatedImage redrawing after being undrawn by the user
* Fixed bug with GraphicsObjects continuing to blink after being undrawn

* Added some getter functions to the AnimatedImage class: `get_current_frame()`, `get_all_frames()`, `get_frame()`,
 `get_number_of_frames()`
* Added `decrement_frame()` and `set_frame()` functions to the AnimatedImage class
* Added `get_x_pos()` and `get_y_pos()` functions to the GraphicsObject class

* Added functions to check if a GraphicsObject is animating or blinking
* Added functions to check the time left for GraphicsObject animations
* Replaced the variables for GraphicsObject blinking with a dictionary
* Added a `number_of_blinks` argument for the `animate_blinking()` function to stop the blinking after some time

#### 1.0.133-beta 18th July 2020

* Removed the window parameter from all the GraphicsObjects. To draw, the `draw()` function must be called separately.
* Added the SolidArc class to the imports.py imports
* Added an `_draw()` function to the SolidArc class
* Fixed the blinking function to work with the Circle GraphicsObject
* Added functions to the GraphWin check if at least 1 of the keys provided was pressed

* Performance upgrade for Goopylib when many objects are drawn on the GraphWin
* GraphWin setter functions only update the window if the window's `autoflush` is `True`
* The GraphWin doesn't call the `time.time()` function inside the `update_win()` if it is not gliding
* More Performance Upgrades for the `_on_mouse_motion()` static method for the GraphicsObject (from ~0.05 secs/call to
 ~0.0 secs)
* Added an AnimationImage GraphicsObject to create Images which go through multiple frames
* Improved Performance for Animating Images (tested on my Pac-Man game, brought down time for 1 loop cycle from ~0.13 
secs to ~0.05 secs)

* Added a `blink_graphic` to the `animate_blinking()` function to set a specific graphic when blinking rather than just 
undrawing it (which happens when it is set to None)

#### 1.0.121-beta 16th July 2020

* Fixed flashing image bug when rotating and skewing the image at the same time
* Fixed bug with Image skewing oddly when it is not rotating
* Added empty skewing functions to the GraphicsObject class to be overriden by subclasses that support it

* Added Animate Skew functions to the GraphicsObject class
* Added a `get_contrast()` function to the Image class, and a `get_rotation()` function for the GraphicsObject class
* Fixed error strings in the Image class to display the correct error
* Added animation functions for changing & setting the contrast of Images

#### 1.0.114-beta 15th July 2020

* Fixed bug with Images as Button graphics not scaling to fit the Window's Coordinates
* Removed the `get_size()` function from the Image class and added it to the GraphicsObject class
* Added Errors to the Image class to make sure the user has specified the correct arguments
* Added flipping functions to the Image class: `flip()`, `flip_xy()`, `flip_x()`, `flip_y()`, `transpose()`, &
 `transverse()`

* Added `get_mode()` and `get_format()` methods to the Image class
* Fixed the image get size functions to return the size of the PIL image rather than itself (useful for transformations
 & stuff)
* Added skewing function to the Image class: `skew()`, `skew_x()`, `skew_y()`, and `scew_xy()` (This was so confusing to 
implement...)
* Added `set_contrast()`, `change_contrast()`, `reset_contrast()`, and `get_contrast()` functions to the Image object
* The Image now keeps its contrast settings while rotating after the contrast has been changed

#### 1.0.107-beta 13th-14th July 2020 - 6632 lines of code

* Added functionality to the Arc class which now inherits from the Curved Line class which means it has all the
 functionality of the line class too!
* Added an empty Solid Arc class
* Added the Arc Wiki

* Performance upgrade to the Image class when drawing it. It no longer updates itself (because it's not required) 
causing image drawing to be much faster
* Added `move_forward()`, `move_backward()`, `move_left()`, `move_right()` functions to the GraphicsObject class
* Added `get_screen_width()` and  `get_screen_height()` function to util.py
* Added `get_cursor()` & `get_config_options()` functions to the GraphicsObject class

* All GraphicsObject animation function return themselves
* Added new animation functions! `animate_change_fill()` and `animate_set_fill()`
* Added a `blend_colour()` function to colours.py to allow for Interpolating between Colours
* Added compatibility for Colours to be performed operations on with floats
* Fixed bug with the `ease_bounce()` function raising an `TypeError`
* Added even more animation functions! `animate_change_outline()` and `animate_set_outline()`

* Added `get_mouse_pos()` and `check_keys_down` functions to the GraphWin
* The user can now specify if they want duplicate animations and they can give a duplicates metric to specify what a
 duplicate is
* Renamed all the arguments for animations such as `Rotation`, `Distance`, `Colour Change`, etc. to just `Change`
* Added a `check_animation_exists()` function to the GraphWin to check if an animation already exists
* Animation functions for changing width: `animate_change_outline_width()` and `animate_set_outline_width()`

* Added axis-based dragging functions with callbacks: `set_draggable_x()` and `set_draggable_y()`
* Added `resize_to_fit()`, `resize_to_fit_width()`, & `resize_to_height()` functions to the image class to resize itself
 to the size of another object
* Added `resize_width()` and `resize_height()` to resize only 1 dimension of the image

* Added a `get_aspect_ratio()` function to the Image class
* Fixed bug in Image class with the image undrawing when resized or the internal `img_PIL` changed.
* Added an option to preserve the aspect ratio of an image while resizing
* Added an align to image cropping to align the image to a certain side/corner

* Added Errors to the Image class `__init__` function
 

#### 1.0.81-beta 12th July 2020

* Added a `slope()` function to the Point class to calculate the slope of a line between 2 points
* Added an `is_clicked()` function to the Line Object
* The GraphicsObject class now calls the `_update()` function for all the GraphicsObject when they are moved or rotated
* Added `get_size()`, `get_width()`, and `get_height()` functions to the Line Object

* Fixed bug with the mouse cursor not changing when the mouse is still, but the GraphicsObject is moving
* The Line object now checks if the arrow option specified is a key in its style
* Added Comments to the Line Class
* Added `arrowshape`, `capstyle` & `joinstyle` arguments to the Line class
* Added a `arrow_scale` argument to the line class that scales the arrow based on its based
* Added Line dashing with a few definitions of dashes already provided

* Created the Line Wiki
* Added a try-except clause to the Line Vector Equation definition to handle vertical lines (undefined slope)
* Fixed bug with Polygon not filling itself the specified colour

* Renamed the Linear & Cosine Interpolation function to `Linear/CosineCurve()` functions
* Added new Linear, Cosine, Cubic, and Hermite Interpolation functions that interpolate between 2 points
* The Goopy `imports.py` files now import the CurvedLine class too
* Added a `CURVE_INTERPOLATIONS` variable to the `constants.py` file

* Added cosine, linear, and cubic interpolation to the Curved Line class - it's actually a curved line now!
* Added a `bounds_width` argument to the Line classes that determines how close a mouse click has to be to be considered 
 clicking the line
* Added getter & setter function for the `bounds_width` argument of the Line classes

#### 1.0.65-beta 11th July 2020 - 6290 lines of code

* Added more getter functions to the GraphWin class
* Every function in the GraphWin class now raises a GraphicsError if the user hasn't provided the correct arguments
* GraphWin get mouse functions now call `update_win()` rather than `update()`
* Renamed the internal argument `refresh` to `_refresh` for the GraphWin
* The GraphWin now checks if `autoflush` is True before updating when the `redraw()`function is called.

* Added key click, press, and a lot more related functions to the GraphWin
* Added the Point class Wiki
* The Line class can now have multiple points as the input

* Every function in the colours.py now raises a GraphicsError if the user hasn't provided the correct arguments
* Fixed bug with line not drawing arrow
* Proofread the Line class, fixed misc bugs with it, etc.

* Added rotation functions for the Line class
* Added a check to the GraphicsObject class to make sure the cursor argument is valid

#### 1.0.54-beta 10th July 2020

* Changed the Circle class `__repr__` function
* Added an align parameter to the GraphicsObject move function to move an object 'left-aligned' or right, top, bottom, 
etc.
* Added `get_height()` and `get_width()` functions to _BBox
* The Button class now inherits from the GraphicsObject class
* Defined all the rotate functions for the button as well as `get_height()` and `get_width()` functions

* Fixed bug with Button movement
* Button is_clicked() function returns False if the button hasn't been drawn

* Renamed the `BezierCurve()` function to `RawBezierCurve()` and created a faster `BezierCurve()` function that uses 
matrices
* Added Linear & Cosine Interpolation Functions
* Worked on a graphical application to allow users to create their own custom ease functions

* The Line Object is no longer a subclass of _BBox but rather it's own object
* Added a Curved Line Object

* Added Mangling Functions to the `Point` class and added more to the `Colour` class
* Changed the `__pow__` function for colours and Points to use `pow(a, b, m)` and not `a ** b % m`
* Removed the `_move()` function from the Point class because it is no longer a GraphicsObject (v6.10-dev)

* Every function in the Point class now raises a GraphicsError if the user hasn't provided the correct argument
* The GraphWin checks for the icon texture in the local directory if it does not exist in the textures/ folder

#### 1.0.39-beta 9th July 2020

* Added a few functions to the Entry widget through which the user can only allow certain characters to be entered
* If the texture of an image is not in a textures folder, the Image class will search in the local folder
* Image resizing now takes the ceiling of the width & height and not the floor (int() gives floor)
* Fixed bug with Image shrinking when rotating over 90 degrees
* Fixed bug with Image vibrating when animating rotate

* Fixed bug with is_gliding causing an AttributeError when creating graphwin
* Renamed Interpolations.py to Easing.py

* The Entry does not set the focus to itself when it is drawn
* Added `get_width()` & `get_height()` functions to the Entry
* The Entry Widget unfocuses itself when the user clicks somewhere else

* Added a GraphWin Wiki! (mainly cause I felt guilty that the people who liked Goopy (4 stars!) wouldn't be able to use 
it)
* The GraphWin returns itself for functions where it didn't (unless it is returning something else)
* Added a `move_to_point()` function for the GraphWin

* Fixed bug with Image not resizing to canvas scaling
* Made CycleButtons semi-functional by adding `draw()`, `undraw()`, `click()`, and `is_clicked()` functions
* Added a file browsing window to get the name of a file

* You can now drag objects! The `set_draggable()` function allows for callbacks too.

#### 1.0.25-beta 8th July 2020

* Added a imports file for the objects & math sub-packages
* Fixed bug with Text config raising errors
* Added RandomColourCMYK() & RandomColourHex() functions and renamed RandomColour() to RandomColourRGB()

* Changed Goopy to only work with Python > 3.6 because of the use of f-strings
* Created the Colours wiki
* Added ABSOLUTE_ RED, GREEN, & BLUE as Colours
* Lshift (<<) and Rshift (>>) operators on Colours with Integers now shifts the RGB values to be GBR, BRG, etc.

* Added a get_bk_colour() function to the GraphWin
* Added a lot more Colours
* Fixed the 2 examples to work with the Library and made them match the Python Convention
* Renamed the getScreenSize() function with Python Convention

* GraphWins now convert their min & max size args to integers

#### 1.0.17-beta - 7th July 2020

* Released Version 1.0.7a6 as a PyPi package for everyone to install!
* Updated README to include new installation method

* Added Double & Triple Mouse Click Functions to the GraphWin
* Added Double & Triple Mouse Click Event Functions to the GraphicsObject class

* Added glide(), glide_x(), glide_y(), glide_to(), glide_to_x(), and glide_to_y() functions to the graphwin
* Fixed GraphicsObject gliding functions to work with the new easing.
* Added a check to make sure the easing provided is a function
* Added glide_to_point() easing function for the GraphWin
* You can now not supply a value for y or dy for the glide() & glide_to() functions to make the object glide equally in 
both directions
* You can now supply different easings for the y & x gliding

* Removed keyboard module dependency
* Added a subtract function for the Point class
* Fixed Bug with glide functions in queue and different easing for x & y

* Added a RandomColour() function that returns a random colour
* Added Mangling Functions to the Colour classes
* Added a Colour Gradient function that returns a list of colours to create a smooth gradient
* Added a 2D Colour Gradient function that returns a 2D Gradient

#### 1.0.0-alpha to 1.0.6-alpha - 6th July 2020

* Added move_to(), move_to_x(), move_to_y(), move(), move_x(), and move_y() functions to the GraphWin class to move a 
window on the screen
* Added seperate Cursor Lists for All, Windows, & Mac OSx 
* Expanded the Cursor List to include all available cursors
* Added a Cursor Dictionary to reference the Cursors with more intuitive names like 'up-down arrow' rather than 
'sb_h_double_arrow'

* Added Closure functions for all the interpolations so that the user can 1. Get a value of the interpolation, or 2.
 Get the function with predifined parameters other than time for use in animations internally
* Created the Cursors Wiki Page

* Various Bug Fixes from changing the naming convention & splitting files


### v6.11-dev

#### 6.11.11 to 6.11.29 to 1.0.0-alpha - 4th-5th July 2020

* Added a callback function to the Entry object which will allow for features like controlling what text the user can 
type in there, prompt text, etc.
* Added a promptText attribute to the Entry which displays text before the user has typed and disappears when he/she 
starts typing
* Added a new style key 'entry width' which deafults to 0 to make Entries look better with less manual configuration
* Entry now raises and error if you try to getText() when it is not drawn, or the GraphWin is closed

* Added a set_enabled() and toggle_enabled() function for Buttons

* Point adding & setting functions don't mutate the point itself now, instead they return a clone of the point with the 
operations performed
* Added a getState() function to the checkbox which returns its current state

* Added functions for finding Bezier Curves, Bernstein Polynomials, & 'nCk' (combinations) to create better curves
* Added Open & Closed Uniform B-Spline curve functions
* Added a Rational Bezier Curve Function for weighted Curves

* Fixed Bug with Polygon drawing outline even though the width is specified to be 0
* Fixed Bug with an error being caused if you rotated more than 180 deg. (Any angle (deg) whose sin < 0)
* Fixed os.isfile() reference to os.path.isfile()
* Fixed GraphWin self.Closed() references to self.isClosed()
* Fixed Misc Bugs & Naming Issues
* Fixed Line set arrow functions

* Split Goopy into multiple files! 
* Renamed everything to follow Python Convention! (These 2 things took a lot of time...)

* Renamed the GraphicsObject update functions to be non-protected 
* Made everything in Goopy abide by the PEP 8 standard

#### 6.11.0 to 6.11.10 - 3rd July 2020

* Removed the Image_depr class which was used as a backup until the new class using the Pillow library was created
* Removed the ToDos, Version History, and Introduction from Goop.py and moved it to the README file

* Closed issue regarding adding new colour formats after adding Hex & CMYK support in v6.10
* Fixed the GraphWin's setBackground() function to work with colours referencing a style
* Fixed bug with the GraphWin not referencing the global style properly

* Warning added to warn the user if they are both calling the updateWin() function manually and the autoflush of the 
GraphWin is set to True
* While resizing a rectangle, you can set the min. width & height beyond which, the rectangle cannot be resized 
* A GraphicsError is now raised if the minWidth & minHeight arguments of the setResizable() function are < 1

* The Rectangle class now draws a rectangle using a polygon rather than directly to allow for rounded edges
* Removed the RoundedRectangle class and built its functionality into the Rectangle class

* Added Errors to the setStyle() function & GraphWin class to make sure the user has entered the correct arguments


### v6.10-dev

* Points are no longer graphic objects
* Custom Support for Cursors on the GraphWin & _BBox classes
* Added support for colour palettes and added 3 style: default, pycharm darcula, and intellij
* Added Assertions to the graphics objects to give better error statements
* Added Config functions for all configurations for the Graphics Window class
* Added circular and ovular bounding boxes
* Added setObjectWidth & Height functions as well as _BBox object resizing functions
* Bounding boxes are now represented by graphics objects (_BBox objects)
* Fixed bugs with using the mouseEvent functions returning None value and added the refresh argument
* Fixed Bug with Graphics Objects resizing when resizing the window
* Fixed bug with background not filling colour of the entire region of window (not only the seen region)
* Tested the graphics window class
* Organized code in the GraphWin
* More colour definitions!
* ColourHex, ColourCMYK, and ColourRGB classes added

* Changed Version History dates from mm/dd/yyyy to dd/mm/yyyy

### v6.9-dev 31/5/2020
* Added argument assert statements to the Graphics Window class
* Added a colour class
* Changed all references of 'Color' to 'Colour'

### v6.8 17/5/2020
* Added a window parameter to every Graphics Class that allows the user to draw the window in the class declaration
* Added more functions to set the Arrow of a line
* You can now set the arrow of a line inside the __init__ function
* Removed all the sound functions
* Added TODOs

### v6.7-dev 25/4/2020
* The Image Object now uses the Pillow (PIL) library which gives the user far more ways to manipulate the object
* Added the ImageGrp class to Group Images together
* Added RadioButtons, & CycleButtons
* New & Improved functions to the GraphWin including the ability to resize the window!
* Added Glide & GlideTo functions with easing to animate objects!

### v6.6-dev 24/11/2019
* Added a few more colour definitions
* Image scaling functions (zoom & resize) now return the image class & don't require the image to have been drawn
* Added ButtonPressed attributes to the GraphWin class to have more variety in mouse events
* Added a moveTo function for BBox classes
* Made the CheckBox class much easier to work with
* Various bug fixes

### v6.5-dev 16/9/2019
* Added Right, Left and Middle click events to the GraphWin class
* Changed GraphWin getKey() and checkKey() functions to use the keyboard library instead of tkinter
* Added checkForKeys() function to GraphWin to check for Multiple keys at once
* Added attribute setting functions for SlideBar class
* Fixed bug of SlideBar class not functioning when p1.(x or y) > p2.(x or y) - x or y depending on orientation

* Added isClicked() function for points and lines
* Added isSelected() function for all GraphicObject children Classes
* Added enabled, disabled and read only states to Entry Class and added many more functions

* GraphicsObject objects now return themselves when the draw() function is called to allow the user to create and
draw an object with 1 line of code
* Added playSound function which plays music

### v6.2-dev 12/9/2019
* Fixed Bug of Line class not drawing due to error
* Fixed Bug of the Graphics Objects' undraw() function not undrawing
* Added SlideBar class
* Added a function to get the Mouse Scroll value to graphwin
* Removed restrictions on text fonts and size allowing user to use whatever values they want
* Added a very basic rectangular Button class

### v6.1-dev 29/8/2019
* Checkboxes added as a class
* Button class added
* Fixed bug with isClicked() function that didn't work when x1 > x2 or y1 > y2
* Added more Fonts

### v6-dev 15/7/2019
* added moveTo() function for all graphics objects to specify x & y variables rather than dx & dy
* added more parameters for classes to customize them during creation rather than using multiple functions
* Defined multiple variables containing colour information to use when colouring object
* added more fonts for text objects to use
* Implemented a new error for missing values
* Added isClicked() function for Image and BBox objects
