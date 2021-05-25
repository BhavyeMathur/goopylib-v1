![goopylib Logo](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Documentation/goopylibLogo-Secondary.png)

Goopylib is a simple-yet-powerful 2D graphics framework built on top of Tkinter capable of creating good-looking, modern
GUIs, games, and animations.

This graphics library is built upon John Zelle's graphics.py package which he made for use with his textbook "Python 
Programming: An Introduction to Computer Science". Over the past 2 years, I have worked on editing this library to add 
more features to use with making my GUIs and games. My aim while editing was to create a powerful medium to
enable me to create good-looking graphics within Python and I have spent a lot of time making sure this is the case.
Thus, this is a very intuitive, simple to use package with the potential of growing into one of the best Python 
Graphics Libraries. 

If you would want to contribute to this library by suggesting features, reporting bugs, or adding changes yourself, 
please do so. I would love it if you would use this library in your projects and do make sure to tell me about them! 

Goopylib is also compatible with [auto-py-to-exe](https://pypi.org/project/auto-py-to-exe/) also known as Pyinstaller. 
This compatibility mainly means that all paths to textures & sounds are automatically converted into the absolute paths 
which you don't have to worry about! This means that you will be able to convert applications written with goopylib into
executables with, hopefully, no errors.  

To know more about goopylib, watch the following video:

[![goopylib Introduction Video Thumbnail](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Documentation/YouTube/%231%20-%20IntroductionThumbnail.png)](https://www.youtube.com/watch?v=x54SQk2eA08)

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
from goopylib.math.py_bezier_curve import py_bezier_curve # The other modules are 'Interpolation', & 'BSpline'
# or
from goopylib.objects.Rectangle import Rectangle  # For a list of graphics objects, look at the documentation
```

To access elements of goopylib like the Point & GraphWin classes, Colours, etc. use this:

```python
from goopylib.colours import *

from goopylib.Window import Window
from goopylib.Point import Point
```

### Projects made using goopylib

I have not supplied the code for these projects because of their scale, but, if you want
 to look at example projects with code, open the Examples folder.

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

**3. WROS - Website Recipe Organization System**

This was an application I created for my mother as part of a school project to help her organize recipes for her website. It was the largest GUI project I worked on with goopylib. It took 7 days to make and demonstrates how goopylib can be used to create proffessional appliations such as this one. 

![WROS Screenshot](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/WROS-RecipeEditor.png)

[Watch here for more](https://www.youtube.com/watch?v=dhgYgPUObv0)

**4. Activity Club Selection App**

My school has these weekly activity clubs where we all go to well, do activities. And every year, we sign up for 
activities using a pen & paper. Writing down our choices, handing them over to our teachers and waiting for them to sort 
through hundreds of entries and assign everybody a club - but not this year. This year I made an activity club selection 
app using the goopylib library that would automatically do all this work for you! 

Goopylib is compatible with auto-py-to-exe which means you can easily convert any program into a .exe file and mail it 
to anyone to use. Now mind you, this was made with an older version of goopylib so it did not contain lots of animations 
and visual feedback, but here is a screenshot anyways:

![Activity Selection App Screenshot](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Examples/ActivtySelectionApp.png)

### Documentation

There are plans to create a detailed documentation for this library both in the form of YouTube videos and a writen documentation which has begun at: https://github.com/BhavyeMathur/goopylib/wiki

## Contributions

1. Reblochon Masque, https://stackoverflow.com/questions/62715279/creating-rounded-edges-for-a-polygon-in-python - 3rd 
July 2020 - Help with creating rounded polygon corners
2. [spectraldoy](https://github.com/spectraldoy) - 3rd July 2020 - Helping me choose a name! we went through a lot of options... pyraphics, oreopy,
 pyllustrate, guipy... barnacle...
3. John Zelle - Creating the graphics.py package which formed the basis for my library.

4. Nico Schertler, https://stackoverflow.com/questions/62738195/python-zerodivisionerror-in-open-uniform-b-spline-curve 
- 4th July 2020 - Helped fix a ZeroDivisionError with Open Unifrom B-Splines
5. Bryan Oakley, https://stackoverflow.com/questions/62740726/tkinter-polygons-width-not-being-set-to-zero-even-though-
specified/62741739#62741739 - 4th July 2020 - Helped fix bug with Polygons drawing their outlines even though the width
 is 0 
 
6. Atlast435, https://stackoverflow.com/questions/62751626/tkinter-rotated-resizing-cursor - 6th July 2020 - Helped 
expand the list of supported cursors by refering me to a documentation.
7. Sinoroc, https://stackoverflow.com/questions/62772377/python-package-does-not-get-created-in-site-packages-folder? -
 7th July 2020 - Helped fix bug with Packaging
8. Cool Cloud, https://stackoverflow.com/questions/62809413/hide-text-cursor-in-tkinter-entry - 9th July 2020 - Helped 
with hiding & showing the Entry cursor

9. Bryan Oakley, https://stackoverflow.com/questions/62809413/hide-text-cursor-in-tkinter-entry - 9th July 2020 - Helped 
with Unfocusing the Entry widget when the user clicks elsewhere
10. Bryan Oakley, https://stackoverflow.com/questions/62836960/what-interpolation-does-tkinter-use-for-curves - 10th 
July 2020 - Helped with answering a question about smoothing in Tkinter

11. Mihir Raddi, Ved Sanyal, Haaziq Kazi, and [spectraldoy](https://github.com/spectraldoy) - 12th September - For their valuable feedback on goopylib's 
logo which developed into what it is currently due to their help!

12. Antti Haapala, 
https://stackoverflow.com/questions/63980828/error-when-compiling-cpython-c2440-function-cannot-convert-from-pyobject-t - 21st September 2020 - Helped fix error with compiling CPython BezierCurve module

13. lcarus3, 
https://stackoverflow.com/questions/63978464/error-when-compiling-cpython-cannot-convert-from-pylongobject-to-pyobject -
 21st September 2020 - Helped fix bug with compiling CPython BezierCurve module code

## Version History

### v1.1

There are probably still a lot of bugs in the release version, but I moved onto Version 1.1 because I started working 
on converting goopylib code to Cython & C and also building a Sound Engine for goopylib 1.2

#### 1.1.313-alpha25 5th May - 25th May 2021

* Fixed bug with the `Rectangle` class's `copy()` function not creating a copy of the position lists and just creating a 
new reference
* Fixed bug with the `Colour` class's `__eq__()` and `__nq__()` functions raising an `AttributeError` when comparing 
against a non-`Colour` object
* Fixed the `hex_to_rgb()` and `_hex_to_rgb()` functions to return a tuple, not generator
* Fixed bug with the `hex_to_hsl()` and `hex_to_hsv()` functions both returning CMYK values
* Created new colour converter testing functions

* Changed `Window` `__repr__()` function to use `"Window"` and not `"GraphWin"`
* Renamed the `Window` `is_resizable()`, `is_width_resizable()`, and `is_height_resizable()` to use `get` instead
* The `Window` `get_resizable()` function now returns a `tuple` not a `list`
* Removed the `Window` `__str__()` function since `__repr__()` defined the same thing
* Added `Window` getter function testing functions
* Fixed bugs with all the CMYK colour conversion functions

* Changed the `GraphicsError` in the `Window`'s `__check_open()` function to include the string `"GraphicsError"` at the
 start and return `True` if the window is open
 * Added `_check__check_open()` and `_check__autoflush()` methods to the `Window` class to check the functionality of 
 private methods
 
 * Removed the `Window` `start_move()` and `stop_move()` methods until I can figure out what they do
 * Removed the `Window` `draw_bounds()` function because it wasn't required.
 * Fixed the `Window` `get_pos()`, `get_x_pos()`, and `get_y_pos()` functions to return the value relative to 0, 0
 * Replaced all instances of the deprecated `Point` class usages with lists in `Window.py`
 * The `Window` `set_background()` method no longer uses styles
 * Changed `Window` `get_bk_colour()` method to `get_background()` to be consistent with the setter
 * `Window` background colours can not be inputted as hex strings
 * Removed all auto-flush checks in the `Window` methods because its private method `__autoflush()` also does that
 
 * Renamed the variable `RELIEF` to `BORDER_RELIEFS`
 * The `Window` `set_icon()` method now accepts icons in the local folder too
 * Added 3 getter methods to the `Window` class: `get_draggable()`, `get_x_draggable_x()`, `get_y_draggable()`
 * Added 5 getter methods to the `Window` class: `get_top_right()`, `get_top_left()`, `get_bottom_right()`,
 `get_bottom_left()`, and `get_center()`
 * Fixed bug with the `GraphicsObject` get animation time left functions raising a `TypeError`
 
 * Fixed error with the `Text` `clone()` method trying to clone a `None` type bounds object
 * Added 5 getter methods to the `_BBox` classes: `get_top_right()`, `get_top_left()`, `get_bottom_right()`,
 `get_bottom_left()`, `get_left()`, `get_right()`, `get_bottom()`, `get_top()`
 
 * Fixed the colour definition of `DARKISH_TURQUOISE` from a purple colour to a turquoise colour
 * Internally changed how the button `Button` class keeps a track of its current state (normal, hover, or clicked)
 * Redefined the `_update_lasttime` variable which was removed for an unknown reason
 
#### 1.1.282-alpha24 29th March - 7th April 2021

* Fixed bug with the `Line` requiring a type `list` for dashes, not `tuple`
* Fixed bug with the `Line` class ensuring that the integers for custom dashes are less than `266`, not `256`
* The `Line`, `Polygon`, and `Rectangle` class now create a copy of all the points entered

* `triangulation.py` no longer uses the deprecated Point class
* Fixed bug with the `__update_lasttime` variable not being defined in `util.py`

#### 1.1.277-alpha23 20th December 2020 - 13th March 2021

* Added C implementations of conversion functions to convert between colour formats
* The default values for colour arguments in the Python Colour classes is now 0 to mimic the behaviour of the C classes

* Removed print statement from the Window class mistakenly left there for debugging
* Removed creation of the `a0` variable inside `CubicInterpolation()` since it wasn't needed
* Renamed all the functions inside `interpolations.py` to follow the Python naming convention
* Renamed all the functions inside `curves.py` to follow the Python naming convention

* All the functions inside `curves.py` no longer use the `Point` class for creating their curves
* Removed debugging print statement from `GraphicsObject.py`

* Fixed error with the `linear_curve()` and `cosine_curve()` functions not working properly
* All interpolation functions now accept points in the form `[x, y]`
* Added a `cubic_curve()` and `hermite_curve()` function to interpolate between control points

* Fixed bug with the `CurvedLine` class not drawing its options
* Added an example file for the interpolation curve functions

* Added DPI awareness scaling for the Windows OS
* Added functions to enable and disable the DPI awareness: `enable_dpi_awareness()` and `disable_dpi_awareness()`
* Fixed the `colour_gradient()`function because it wasn't working when there were 3 divisions

* Changed the roundness of rounded rectangle to work better than before. The amount of roundness now refers to the 
radius of the roundness
* Implemented the `__getitem__()` functions for the Colour classes to override indexing
* Added `set_fill()`, `set_outline_width()`, and `set_outline()` functions to the `_BBox` class
* Added an `is_enabled()` and `is_disabled()` function to the `Button` and `CycleButton` (and `Checkbox`) classes
* The `CycleButton` (and `Checkbox`) class now defaults to the current graphic if no disabled graphic is present

* The `Text` class now defaults the font colour to the default `'font colour'` option, not to default `'outline'`
* Fixed bug with the `Rectangle` `clone()` function throwing an error when the object has no defined bounds

* Fixed bug with the `Polygon` class still using the deprecated `Point` class
* Fixed bug with the `Polygon` `__init__()` not using the fill, outline, and outline width arguments correctly
* Reimplemented the `Polygon` `set_fill()`, `set_outline()`, and `set_outline_width()` functions properly

* Fixed bug with the `Line` class not working with layers
* Implemented the `get_fill()`, `get_outline()`, and `get_outline_width()` functions for the `Polygon` class fixing 
other bugs as a result
* Added rotation functions to the `Text` class
* All non-getter `Text` class functions now return `self`
* Fixed bug with the `GraphicsObject` class not checking if an object is draggable properly, led to performance upgrade
 on mouse presses

#### 1.1.246-alpha22 10th December 2020

* Implemented all remaining PyNumberMethod methods for the C `Colour` class
* Changed the `Colour` class's `__round__()` method to round up to 255 when the colour value is greater than 127, 
compared to the previous 128
* Updated the link to the goopylib Colour doc in the `Colour` class's `__dir__()` function
* Defined the `__dir__()`, `__round__()`, `__reversed__()`, & `__contains__()` functions for the C `Colour` class

* Added a separate  `__contains__()` method for the `ColourHex()` class
* Fixed the `Colour_richcompare()` method of the C `Colour` class for the `==` & `!=` operations
* Renamed the `update_values()` method of the `Colour` classes to `__update_values()`
* Fixed circular import with importing the `Window` while important the `GraphicsObject` module without importing the 
`Window` module yourself

* Fixed issue with incorrectly named module import in `goopylib.sound.waves.py`
* Fixed error with the `Window` class incorrectly initializing because the root wasn't updating, see 
https://stackoverflow.com/questions/34373533/winfo-width-returns-1-even-after-using-pack

#### 1.1.236-alpha21 6th-9th December 2020 - 18212 lines of code!

* Fixed warning with the `string` attribute of the C implementation of the `ColourHex` class in which the `PyObject*` 
was being defined to a `char[7]`. It is now defined to a `PyUnicode` object.
* Changed `abs()` to `fabs()` in `colours.c` when it took a `float` argument
* The `hexstring` variable in the `rgb_to_hex()` function in `colours.c` is now static to avoid returning a 'address of 
stack memory associated with local variable'

* Renamed all the modules in goopylib.math & all C extensions with the Python naming convention 
(lowercase & underscores)
* Fixed bug with the goopylib C extension modules raising errors when being imported
* Removed the `__get_item__()` & `__len__()` functions of the `Colour` class as they didn't make a lot of sense to keep

* Simplified expressions to check for valid arguments in `colours.py` and made them run faster by removing unneeded 
`not`s
* Renamed `Sound.py` to `sound.py` to follow the Python naming convention
* Added argument validation to all functions in `colours.py` to ensure the user has entered the correct types

* Fixed bug with the `Colour` class incorrectly executing the `__contains__()` function
* Every `Colour` subclass has separate `__contains__()`, `__round__()__`, `__iter__()`, & `__copy__()` methods 
* Changed `max([...])` to `max(...)` inside the `colour_gradient()` & `color_gradient()` functions to make them faster

* Added another set of colour conversions with a `_` prefix, these functions do not validate arguments
* The Colour types in `colours.c` now use a `PyObject *` to store the hex colour string of a colour instance as opposed
 to the previous use of a `char[7]`
* Fixed error with the C colours module not compiling when `PyNumberMethods` of the Colour type were specified in the 
module INIT

* The C `ColourHSV` & `ColourHSL` types now take integer arguments for the S & V, and S & L values just like the Python
 classes
* Fixed the conversion from HSV to RGB and HSL to RGB in the initialization functions of `ColourHSV` & `ColoursHSL` in 
`colours.c` 
* Moved the error checking from the `bezier_curve.py` interface to `c_bezier_curve.c` making it faster
* The `factorial()` function defined in `c_bezier_curve.c` is no longer accessible from Python 
(use standard `math.factorial()` instead)
* Defined all unary PyNumberMethods for the C implementation of the `Colour` class as well as nb_add, nb_subtract, 
nb_multiply, nb_remainder, nb_divmod, & nb_power. All other PyNumberMethods return an empty `Colour` class

#### 1.1.216-alpha20 1st-3rd December 2020

* Fixed bug with the `ColourHSL` & `ColourHSV` classes not correctly converting to RGB values properly when 
`120 <= h < 180`
* Added a C implementation of the `ColourHSV` & `ColourHSL` classes to `colours.c`
* The Colour type in `colours.c` finally overrides the number protocol (for operations like addition, subtraction, etc.)

* Fixed mispelt argument name `color_start1` in the `color_gradient_2d()` function 
* Changed the `__init_subclass__()` method in the `Colour` class to just a `__init__()` method as the previous wasn't 
required

* Moved the default instance variable definitions in the `Colour` class outside the `__init__()` function and to static 
variables
* Allowed the C implementation of the `rgb_to_hex()` function to be accessible from Python
* Changed the docstrings of the `CBezierCurve` module functions to show what the output type of each function is

* Added a `hex_digit_to_int()` function to `colours.c` that allows you to convert a hexadecimal digit to a base-10 int
* The `Colour` types implemented in C are now actually semi-usable. 
* Removed the `__format__()` method from the `Colour` class because it wasn't required

* Changed the C-implementation of the `Colour` type's `__repr__()` method to match the Python implementation
* Fixed misordered format values in the `rgb()` method of the `Colour` class
* Reordered the PyNumber Methods of the `Colour` class to follow the order described here: 
https://docs.python.org/3/c-api/typeobj.html?highlight=tp_#c.PyNumberMethods


* Changed the `__hex__()` method of the `Colour` class to return a `ColourHex` instance of the same colour as which the 
function is used on
* Made the `Colour` class PyNumber Methods faster by replacing the  `min([255, ...])` for if statements
* Using the multiplication operator on a `Colour` instance will now make sure that the rgb values for the colour are less 
than 256

* You can no longer perform operations with floats and `Colour` objects
* The `pow()` function with `Colour` objects now accepts a `Colour` type value for the modulo argument
* `Colour` object PyNumber Methods now set the red, green, or blue value to 0 if the resulting value from operation is 
less than 0

* Added functions to convert between colour types: `hex_to_rgb()`, `cmyk_to_rgb()`, `hsv_to_rgb()`, `hsl_to_rgb()`, 
`rgb_to_cmyk()`, `rgb_to_hsl()`, `rgb_to_hsv()`, `hex_to_cmyk()`, `hex_to_hsl()`, `hex_to_hsv()`, `cmyk_to_hex()`, 
`cmyk_to_hsl()`, `cmyk_to_hsv()`, `hsv_to_hex()`, `hsv_to_cmyk()`, `hsv_to_hsl()`, `hsl_to_hex()`, `hsl_to_cmyk()`, & 
`hsl_to_hsl()`

* Copied the `Colour` class's `__floordiv__()` function to its `__truediv__()` one to use `"/"` in the error message 
rather than `"//"s`

* The `ColourHSL` & `ColourHSV` classes now only accept integer values representing percentages for H & L, and H & V to 
make it consistent with `ColourCMYK`
* Simplified the conversion of inputs to RGB for the `ColourCMYK`, `ColourHSV`, & `ColourHSL` classes by removing 3 
redundant variables

* Fixed bug with the `Colour` classes not updating their string & hex value when performed operations on. This meant 
that operations on colours had no real effect.

* Renamed the colour `ABSOLUTE_TURQUOISE` to `ABSOLUTE_CYAN`
* `colours.py` now uses the `round()` function to round outputs of operations/functions on colours to the nearest 
integer rather than the previous `int()` which sometimes gave errors of +-1

* Fixed a bug in the `ColourCMYK()` class where the CMYK colours were not being properly converted to RGB
* Renamed the `Colour` class's `rgb()` function to `rgb_string()`
* Added methods to return a `Colour` instance's colours in different colour models: `hex_string()`, `cmyk_string()`, 
`hsv_string()`, `hsl_string()`

* Added methods to the `Colour` class to convert the colour into another colour type: `to_rgb_colour()`, 
`to_hex_colour()`, `to_cmyk_colour()`, `to_hsl_colour()`, `to_hsv_colour()`

* There are now separate PyNumber methods for each `Colour` subclass (except `ColourRGB`) whose return values are the 
type the operation is performed on
* All goopylib pre-defined colours use the `ColourRGB` class (some previously used `ColourHex`) as it is the most 
efficient `Colour` subclass

* Fixed the ordering of `ColourCMYK` arguments from `c, y, m, k` to `c, m, y, k`
* Changed the `__lshift__()` & `__rshift__()` methods of the `Colour` class to ensure that the returned value is within 
permitted bounds for a colour

* Added setter functions for `Colour` subclasses to set individual colour arguments
* Operations on Colours of the same type (RGB & RGB, HSL & HSL, etc.) are now performed argument-wise for that colour, 
ie h1 + h2, s1 + s2, v1 + v2 for HSL + HSL rather than converting to RGB first.

* The inplace PyNumber methods of the `Colour` subclasses (except for `ColourRGB` & `ColourHex`) now follow the same 
rules as the normal PyNumber methods

#### 1.1.177-alpha19 4th-27th November 2020

* You can now use the `set_text()` function for `Entry` objects even if the `Entry` hasn't been drawn
* Fixed the `RandomColourRGB()` function to no longer raise errors if the user hasn't specified the RGB values
* Optimized the error checking in the `RandomColourRGB()` & `RandomGreyscale()` functions by reducing the number of 
`not` & `!=`

* Simplified the `RandomColourCMYK()` function and optimized it like with the `RandomColourRGB()` one
* The `RandomColourHex()` function now works if the user hasn't supplied hex values for r, g, & b and optimized the 
function to execute faster

* Added a new lists to contain all of `GREENS`, `PURPLES`, etc. and for `WARM COLOURS` and `COOL COLOURS`
* Added a list of all goopylib colours objects

* Added HSV colours to goopylib: a `ColourHSV` class & `RandomColourHSV()` function
* Changed all the `GraphicsError`s in `colours.py` to be raised with a `"GraphicsError:"` prefix
* The `ColourCMYK` class is now printed as `"cmyk c%, m%, y%, k%"` rather than the previous `"cmyk c, m, y, k"`
 
* The Internal goopylib classes no longer use the `Point` class in favour of an iterable
* Added a few more (7) colour definitions to complete the existing colour scales
* Added HSL colours to goopylib: a `ColourHSL` class & `RandomColourHSL()` function

* Renamed all the functions inside `colours.py` to follow the Python naming convention
* Added American spelling (`color`) equivalents of everything in `colours.py` which references the original functions
* Renamed the `blend_BLENDINGTYPE()` functions to `blend_colour_BLENDINGTYPE()` and added their American equivalents.

* Moved the `random` module's import statement above the `goopylib.math.Interpolations` import statement in `colours.py` 
to abide by PEP8
* Created a `color.py` file which simply imports everything from `colours.py`
* The `Colour` class now raises a `TypeError` if the modulo value for the `pow()` function is of an unsupported type
* The `abs()` function on a `Colour` instance now returns an integer value colour

#### 1.1.158-alpha18 3rd November 2020

* The `is_clicked()` function of the `GraphicsObject` class returns whether or not the object's `bounds` were clicked. 
If it has no bounds, it returns `False`

* Made the `RadioButton` class an iterable
* You can now use the `len()` function on `RadioButton` and `CycleButton` objects
* The `RadioButton` and `CycleButton` classes are now subscriptable
* Added an `anchor` attribute to the `CycleButton` class to support gliding

* The `RadioButton` and `CycleButton` classes now support movement and gliding functions
* The `get_anchor()` function of the `CycleButton` class now returns the value from its states' `get_anchor()` function,
 not the `anchor` attribute itself
 
 * The `is_clicked()` function in the `Image()` class now uses integer division (`//`) rather than float division (`/`)
  to make it slightly faster and also pre-calculates the divisions to perform half the division operations
  
 * Fixed bug with the `RadioButton` & `CycleButton` class not changing their anchors when moving
 * Fixed bug with all the `GraphicsObject`glide functions adding 2 lists together instead of their elements
 * The `RadioButton` class now raises an error if the user has specified 0 states
 
 * Added a `get_anchor()` function to the `RadioButton` class
 * Fixed bug with `Button` objects not defining their `anchor` during the initialization
 * The `change_graphic()` function of the `Button` class now allows you to set graphics to `None`
 
 * The `GraphicObject` class now raises an error if the user tries to glide an object which does not support it
 * Renamed the `allow_only_numeric()` function of the `Entry` to `allow_only_positive_integer()` and added 2 new 
 functions: `allow_only_numeric()` and `allow_only_integer()`

#### 1.1.142-alpha17 1st-2nd November 2020

* Fixed bug with the default Image Texture path being `textures_other/` instead of `textures/`
* Fixed bug with every `GraphicsObject` entering an infinite loop when the user sets the objects' layer to not 0

* Added `animate_resize()` and `animate_resize_factor()` functions to the `GraphicsObject` class
* Added a `get_state()` function to the `RadioButton` class
* You can now specify custom bounds for a `Checkbox` instance

* Fixed bug with the Text object's `is_clicked()` function not working properly when the text is not center-aligned 
* Fixed bug with the `GraphicsObject` class raising an error when you try to destroy an object twice

* Added a `set_state()` function to the `RadioButton` class

#### 1.1.134-alpha15 27th October 2020

* Added a `try except` clause when importing the sound subpackage to handle for MacOS Users
* The goopylib `__init__.py` file not longer imports everything. 

#### 1.1.132-alpha14 4th-20th October 2020 

* Fixed bug with the `AnimatedImage` class not defining its `anchor` attribute
* Added a try & except clause for the `CBezierCurve` import statement as some people were facing errors importing it.

#### 1.1.130-alpha13 29th September-3rd October 2020

* Renamed the `open` argument of the `UniformBSpline()` function to `is_open` to avoid the same name as the 
built-in function
* `BSpline.py` no longer uses the `Point` class for any of its functions

* Fixed a bug with the `Line` class's `set_arrow_first()`, `set_arrow_last()`, & `set_arrow_both` functions removing 
all arrows
* The `Line` class's `set_arrow()` function now displays the correct error
* Made the setter functions for the `Line` class run faster by getting rid of `not`s and restructuring the code
* The `Line` class no longer uses a `GraphicsObject` config to store data opting instead for internal variables

* Fixed an error with the closed `UniformBSpline()` function working incorrectly
* Renamed the `UniformBSpline()` & `CoxDeBoorRecursion` functions to `uniform_bspline()` & `cox_de_boor_recursion` 
respectively to conform with Python Convention & PEP 8

* The `Line` class no longer uses styles

#### 1.1.121-alpha12 27th-28th September 2020

* Changed the if-else statements for the easing functions from `if t is not None:` to `if t is None:` and switched the
 code (from else-if and if-else) to reduce the amount of `not`s called and improve performance.

* Removed an unnecessary `+` symbol from `+r`, `+g`, `+b` from the `ColourRGB()` `__init__` function.
* Started working a C-implementation of `colours.py` - Added the 4 colour classes and `rgb_to_hex()` function.
* Added a `rgb_to_hex()` function to `colours.py`

* Removed the `__bytes__()`, `__oct__()`, `__ceil__()`, and `__floor__() functions from `Colour` object as they are 
mostly unnecessary

* The `Arc`, `CurvedLine`, `Entry`, & `Circle` classes no longer use `Point` objects opting instead for lists in the 
form `[x, y]`
* You can no longer assign a style to `Circle`, `Entry`, `Arc`, `Text`, & `CurvedLine` objects
* Added a `rotate_to_face()` function to the `GraphicsObject` that rotates an object to face another
* Removed a check from the `GraphicsObject` class that checked if the cursor provided was a `str` because another check 
already made sure that the cursor was part of a set of options

* Removed the style argument from the `GraphicsObject` class's `__init__()` function
* `Text` objects no longer use the old system of configs for every `GraphicsObject`. They have shifted to just using 
variables

* The `Text` object getter functions now call `_update_layer()` internally to fix bug with a manual redrawing required
* Changed the `Text` object's `clone()` function to copy all the attributes properly
* All the `GraphicsErrors` raised in `Text.py` now start with `"\n\nGraphicsError: "`

#### 1.1.107-alpha11 24th-26th September 2020

* The BSpline module no longer uses the Point class. It returns the spline as a list in the form `[x, y]`
* Removed an unnecessary and unused definition of `_ease_liner()` from `Easing.py`
* Renamed the `Easing.py` module to `PyEasing.py` and renamed all functions in it to have a suffix of `py_`

* Added a `BezierCurve.py` file to serve as an interface between Python & the C Extensions
* Few more optimizations to the `bezier_curve()` function to make it run a little bit quicker

![Bezier Curve Speed Comparision](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Documentation/Tests/BezierCurve-Comparision.png)

* Added a C implementation of the `rational_bezier_curve()` function 
* Optimized the `py_rational_bezier_curve()` function a lot

![Rational Bezier Curve Speed Comparision](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Documentation/Tests/RationalBezierCurve-Comparision.png)

* The `py_rational_bezier_curve()` function takes the `control_points` argument before the `weights` to make it more 
consistent with the other functions

* Added a `MANIFEST.in` file to include the `.pyd` C-extension modules which weren't being packaged properly
* The CPython Interface functions now raise errors if the arguments provided are bigger than what C can accurately 
provide results for

* Moved most argument checking statements to the C implementation to increase the performance of the CPython Interface
 functions.
 
 ![Speed Comparision](https://raw.githubusercontent.com/BhavyeMathur/goopylib/master/Documentation/Tests/RationalBezierCurve-OptimizedInterface.png)

* Added argument and error checks to the `bezier_curve()`, `berstein_polynomial()`, and `combination()` functions
* The C extension packages now correctly package as a module with the goopylib package

#### 1.1.94-alpha10 23rd September 2020 - 11740 lines

* If no parameter is supplied to a GraphicObject's `draw()` function, it checks if it has been previously drawn and if 
so, draws to the same window

* Fixed bug with the Rectangle using its `width` variable (defines how wide the rectangle is) instead of `outline_width`
 (defines the thickness of the outline) to draw the outline
 
* The Window & AnimatedImages objects do not use the Point class anymore opting instead for a list in form `[x, y]`
* Window attributes related to size & position now have to `ints` instead of the previously acceptable `int` or `float`
* The Window's `max_width` & `max_height` variables are `None` by default which means the user can choose to not define 
a max size

* Added a check to ensure that the Window's `min_height` and `min_width` are greater than 0 and changed the check from
 `... not > 0` to `... < 1`
 
 * Window objects no longer use styles
 * Fixed bug with wrongly spelt `filter_more_enhance_edge()` as `more_enhance_edge()` inside the AnimatedImage class

* Added a C implementation of the `PyRawBezierCurve()` function to make it run much faster.  
* Added optimizations for the `PyBezierCurve()` function for curves with a degree less than 6. 
* `numpy` is no longer a goopylib dependency

* Renamed the Python implementations of the Bezier Curve functions to follow the Python Convention
* Removed the `py_raw_bezier_curve()` & `raw_bezier_curve()` functions as they were only meant to be used internally
 and moved their code directly into where they were being called

#### 1.1.80-alpha9 18th-22nd September 2020

* Renamed the Window's `update_win()` function to just `update()`
* The rectangle class doesn't define a list of points inside the `__init__()` function anymore, rather, it does it in 
the `draw()` function

* Added a C implementation for the Factorial, Combination, & BernsteinPolynomial functions
* Renamed all the functions (`Combination`, `BernsteinPolynomial`, `RawBezierCurve`, `RationalBezierCurve`, 
`BezierCurve`) inside BezierCurve.py to have a suffix `Py` in front to avoid confusion with the C functions. 

* The `PyRawBezierCurve()`, `PyRationalBezierCurve()`, & `PyBezierCurve()` functions now return a tuple `(x, y)` 
instead of `Point(x, y)`
* Made the `PyRawBezierCurve()` function more efficient and faster by calculating the size of the `control_points` once 
rather than every iteration

* Made the `PyRawBezierCurve()` function more efficient by calculating the `berstein_polynomial` once every iteration 
and using the stored value

* The Rectangle class raises exceptions if proper arguments aren't supplied
* Removed an unused VectorEquation import statement from the Rectangle class
* You can now provide bounds arguments for the Rectangle `set_resizable()` function to define custom bounds in each 
direction
* Removed the `show_bounds` argument from the _BBox's `set_resizable()` function

* Added an `undraw_bounds()` function to the GraphicsObject class to undraw any drawn bounds
* Removed the `show_bounds()` and `hide_bounds()` functions from the _BBox class as these are already defined in the 
GraphicsObject class

* Fixed bug with the _BBox's `set_resizable()` function being able to add the objects to the GraphicsObject's 
`resizing_objects` set multiple times and not removing objects from it if the object is set to be not resizable.

* Removed an unused Line module import statement from _BBox.py and a VectorEquation module import statement from 
Rectangle.py

* _BBox & Line objects now use floor division to find the anchor of itself to give an integer result rather than a 
float.
* The Rectangle, Oval, and _BBox classes no longer use the Point class. This aims towards a shift from deprecating the point 
class in favour of length-2 list `[x, y]`

* Removed the `reset_bounds()` function from the _BBox class as its functionality is not required.
* You can no longer assign a style value to any of the _BBox classes. This is a step towards deprecating the largely 
useless styles

* The Rectangle's `_draw()` function now draws a Polygon shaped like a rectangle only if the rectangle is rounded, 
otherwise, it draws a rectangle

* Fixed the Rectangle's `clone()` function to transfer all the previous Rectangle's attributes over properly

* More misc changes to the GraphicsObject & Oval classes

#### 1.1.59-alpha8 10th-15th September 2020

* The Window and Image classes now use the absolute path to open icons and filepaths to make themselves compatible with 
auto-py-to-exe

* Added functionality to the Radio Button class
* The Checkbox now only checks if its graphic has been clicked if its bound is None. otherwise, it returns whether or 
not its bound was clicked.
* Removed the Checkbox's `is_clicked()` function because its superclass (CycleButton) already defines it
* Removed the CycleButton's `_update_layer()` function because its superclass (GraphicsObject) already defines it

* Removed an unnecessary `checkbox_instances` variable from the GraphicsObject class as the checkbox now works under
 the CycleButton class
* Fixed bug with the Checkbox's `set_state()` function setting the opposite state
 
* Created the official goopylib logo
* Made destroying compound GraphicObject classes much more efficient
* Added more destroy all instances functions to the Window class 

#### 1.1.50-alpha7 5th-7th September 2020

* If the distance to move an object is 0 for both x & y, the `_move()` function does not execute.
* Changed a lot about how objects are drawn to fix bug with the layering system
* Optimized Entry box movement to make it much faster

* Fixed bug with Checkboxes not changing states properly
* Closing a window now binds another window to mouse & key functions
* The Entry, MultilineEntry, and Text objects' `set_text()` function now converts the text given to a string 
* The MultilinEntry now raises an error if the user tries to use the `get_text()` function when the object is not drawn

* Fixed bug with the Window's `update_win()` function not working properly.

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
