import time
import math

import os
import warnings
import keyboard

import tkinter as tk

from PIL import ImageTk, ImageFilter
from PIL import Image as Img
from PIL import ImageGrab
from PIL import ImageFont

import sys

"""
Dependencies:

keyboard (will be replaced soon for Mac OSX Support)
PIL (pillow)
fonts

"""

# Done to get rid of bug with Image PIL
if "tkinter" not in sys.modules:
    import tkinter as tk

"""Simple object oriented graphics library

The library is designed to make it very easy for novice programmers to
experiment with computer graphics in an object oriented fashion. It is
written by John Zelle for use with the book "Python Programming: An
Introduction to Computer Science" (Franklin, Beedle & Associates).

The library was further edited by Bhavye Mathur to add more graphic types
 and more functions to allow the user to perform many more operations
 easily.

LICENSE: This is open-source software released under the terms of the
GPL (http://www.gnu.org/licenses/gpl.html).

PLATFORMS: The package is a wrapper around Tkinter and should run on
any platform where Tkinter is available.

INSTALLATION: Put this file somewhere where Python can see it.

OVERVIEW: There are two kinds of objects in the library. The GraphWin
class implements a window where drawing can be done and various
GraphicsObjects are provided that can be drawn into a GraphWin. As a
simple example, here is a complete program to draw a circle of radius
10 centered in a 100x100 window:

--------------------------------------------------------------------
from graphics import *

def main():
    win = GraphWin("My Circle", 100, 100)
    c = Circle(Point(50,50), 10)
    c.draw(win)
    win.getMouse() # Pause to view result
    win.close()    # Close window when done

main()
--------------------------------------------------------------------
GraphWin objects support coordinate transformation through the
setCoords method and mouse and keyboard interaction methods.

The library provides the following graphical objects:
    Point
    Line
    Circle
    Oval
    Rectangle
    Polygon
    Text
    Entry (for text-based input)
    Image

These classes utilize the classes above to create easier usage for specific tasks
Added by Bhavye Mathur:

    SlideBar
    Button
    Checkbox

Various attributes of graphical objects can be set such as
outline-Colour, fill-Colour and line-width. Graphical objects also
support moving and hiding for animation effects.

These graphic objects also contain functions to check whether the object was clicked or not

The library also provides a very simple class for pixel-based image
manipulation, Pixmap. A pixmap can be loaded from a file and displayed
using an Image object. Both getPixel and setPixel methods are provided
for manipulating the image.

DOCUMENTATION: For complete documentation, see Chapter 4 of "Python
Programming: An Introduction to Computer Science" by John Zelle,
published by Franklin, Beedle & Associates.  Also see
http://mcsp.wartburg.edu/zelle/python for a quick reference"""

# TODOs & Future Plans

"""

TODOs & Future Plans

 - Add extensive sounds & music support
 - Test glide, move, drawing, rotating, etc. for composite classes
 - Add more useful errors
 - Add Button event sounds
 - Image Tinting, Transformation, etc.
 - _BBox class rotation
 - Define more custom colours
 - Develop documentation for this library
 - Custom Ease fuctions
 - Animation Paths
 - Develop a graphical software to program using Python & the Graphics Library
 - Try adding support for server communication for multiplayer games
 - Add support for Animated GIFs and Videos
 - Add support for local & online databases
 - Add graphics window max size
 - Custom Cursor support (inside GraphWin, hovering cursor, etc.)
 - Arcs and semi-ellipses.
 - Customizable Title Bars
 - Polygonal Bounding Boxes and Transparency based for PNG images
 - Add a layering system
 - Animated width, height functions for BBox objects
 - Animated image transformation and styling functions
 - Sound, Calculations, and Graphics threading
 - Draggable Objects
 - RGBA Colour Support
 - Hex, CMYK, etc. Support
 - Grid system to divide GraphWin
 - Bind Graphics Objects to other Graphic Objects
 - Add Comments to explain the code
 - Add Support for diagonal SlideBars (any custom points p1, p2)
 - Complete Radio Button & other Composite classes
 - Add more useful error messages
 - Object transformations like skewing and relfections
 - adapt the Graphics Library for Mac OSX
 - Hide Cursor in Entry Object
 - Add an Entry Callback whenever the text is changed, Limit what letters can be typed in (alphabets, nubmeric, etc.)
 - Disable & Enable Input Widgets
 - Test Compound Graphics Classes
 - Blinking Animation

"""

__version__ = "8.2.2"


# Version 8.2.2 7/6/2020
#   * Points are no longer graphic objects
#   * Custom Support for Cursors on the GraphWin & _BBox classes
#   * Added support for colour palettes and added 3 style: default, pycharm darcula, and intellij
#   * Added Assertions to the graphics objects to give better error statements
#   * Added Config functions for all configurations for the Graphics Window class
#   * Added circular and ovular bounding boxes
#   * Added setObjectWidth & Height functions as well as _BBox object resizing functions
#   * Bounding boxes are now represented by graphics objects (_BBox objects)
#   * Fixed bugs with using the mouseEvent functions returning None value and added the refresh argument
#   * Fixed Bug with Graphics Objects resizing when resizing the window
#   * Fixed bug with background not filling colour of the entire region of window (not only the seen region)
#   * Tested the graphics window class
#   * Organized code in the GraphWin
#   * More colour definitions!
#   * ColourHex, ColourCMYK, and ColourRGB classes added

#   * Chaned Version History dates from mm/dd/yyyy to dd/mm/yyyy

# Version 8.2.1 31/5/2020
#   * Added argument assert statements to the Graphics Window class
#   * Added a colour class
#   * Changed all references of 'Color' to 'Colour'

# Version 8.2.0 17/5/2020
#   * Added a window parameter to every Graphics Class that allows the user to draw the window in the class declaration
#   * Added more functions to set the Arrow of a line
#   * You can now set the arrow of a line inside the __init__ function
#   * Removed all the sound functions
#   * Added TODOs

# Version 8.1 25/4/2020
#   * The Image Object now uses the Pillow (PIL) library which gives the user far more ways to manipulate the object
#   * Added the ImageGrp class to Group Images together
#   * Added RadioButtons, & CycleButtons
#   * New & Improved functions to the GraphWin including the ability to resize the window!
#   * Added Glide & GlideTo functions with easing to animate objects!

# Version 8.0 24/11/2019
#     * Added a few more colour definitions
#     * Image scaling functions (zoom & resize) now return the image class & don't require the image to have been drawn
#     * Added ButtonPressed attributes to the GraphWin class to have more variety in mouse events
#     * Added a moveTo function for BBox classes
#     * Made the CheckBox class much easier to work with
#     * Various bug fixes

# Version 7.9 16/9/2019
#     * Added Right, Left and Middle click events to the GraphWin class
#     * Changed GraphWin getKey() and checkKey() functions to use the keyboard library instead of tkinter
#     * Added checkForKeys() function to GraphWin to check for Multiple keys at once
#     * Added attribute setting functions for SlideBar class
#     * Fixed bug of SlideBar class not functioning when p1.(x or y) > p2.(x or y) - x or y depending on orientation
#
#     * Added isClicked() function for points and lines
#     * Added isSelected() function for all GraphicObject children Classes
#     * Added enabled, disabled and read only states to Entry Class and added many more functions
#
#     * GraphicsObject objects now return themselves when the draw() function is called to allow the user to create and
#       draw an object with 1 line of code
#     * Added playSound function which plays music

# Version 7.6 12/9/2019
#     * Fixed Bug of Line class not drawing due to error
#     * Fixed Bug of the Graphics Objects' undraw() function not undrawing
#     * Added SlideBar class
#     * Added a function to get the Mouse Scroll value to graphwin
#     * Removed restrictions on text fonts and size allowing user to use whatever values they want
#     * Added a very basic rectangular Button class

# Version 6.1 29/8/2019
#     * Checkboxes added as a class
#     * Button class added
#     * Fixed bug with isClicked() function that didn't work when x1 > x2 or y1 > y2
#     * Added more Fonts

# Version 6 15/7/2019
#     * added moveTo() function for all graphics objects to specify x & y variables rather than dx & dy
#     * added more parameters for classes to customize them during creation rather than using multiple functions
#     * Defined multiple variables containing colour information to use when colouring object
#     * added more fonts for text objects to use
#     * Implemented a new error for missing values
#     * Added isClicked() function for Image and BBox objects

# Version 5 26/8/2016
#     * update at bottom to fix MacOS issue causing askopenfile() to hang
#     * update takes an optional parameter specifying update rate
#     * Entry objects get focus when drawn
#     * __repr_ for all objects
#     * fixed offset problem in window, made canvas borderless

# Version 4.3 25/4/2014
#     * Fixed Image getPixel to work with Python 3.4, TK 8.6 (tuple type handling)
#     * Added interactive keyboard input (getKey and checkKey) to GraphWin
#     * Modified setCoords to cause redraw of current objects, thus
#       changing the view. This supports scrolling around via setCoords.
#
# Version 4.2 26/4/2011
#     * Modified Image to allow multiple undraws like other GraphicsObjects
# Version 4.1 12/29/2009
#     * Merged Pixmap and Image class. Old Pixmap removed, use Image.

# Version 4.0.1 8/10/2009
#     * Modified the autoflush on GraphWin to default to True
#     * Autoflush check on close, setBackground
#     * Fixed getMouse to flush pending clicks at entry

# Version 4.0 8/2009
#     * Reverted to non-threaded version. The advantages (robustness,
#         efficiency, ability to use with other Tk code, etc.) outweigh
#         the disadvantage that interactive use with IDLE is slightly more
#         cumbersome.
#     * Modified to run in either Python 2.x or 3.x (same file).
#     * Added Image.getPixmap()
#     * Added update() -- stand alone function to cause any pending
#           graphics changes to display.
#
# Version 3.4 16/10/2007
#     Fixed GraphicsError to avoid "exploded" error messages.
# Version 3.3 8/8/2006
#     Added checkMouse method to GraphWin
# Version 3.2.3
#     Fixed error in Polygon init spotted by Andrew Harrington
#     Fixed improper threading in Image constructor
# Version 3.2.2 30/5/2005
#     Cleaned up handling of exceptions in Tk thread. The graphics package
#     now raises an exception if attempt is made to communicate with
#     a dead Tk thread.
# Version 3.2.1 22/5/2005
#     Added shutdown function for tk thread to eliminate race-condition
#        error "chatter" when main thread terminates
#     Renamed various private globals with _
# Version 3.2 5/4/2005
#     Added Pixmap object for simple image manipulation.
# Version 3.1 13/4/2005
#     Improved the Tk thread communication so that most Tk calls
#        do not have to wait for synchonization with the Tk thread.
#        (see _tkCall and _tkExec)
# Version 3.0 30/12/2004
#     Implemented Tk event loop in separate thread. Should now work
#        interactively with IDLE. Undocumented autoflush feature is
#        no longer necessary. Its default is now False (off). It may
#        be removed in a future version.
#     Better handling of errors regarding operations on windows that
#       have been closed.
#     Addition of an isClosed method to GraphWindow class.

# Version 2.2 26/8/2004
#     Fixed cloning bug reported by Joseph Oldham.
#     Now implements deep copy of config info.
# Version 2.1 15/1/2004
#     Added autoflush option to GraphWin. When True (default) updates on
#        the window are done after each action. This makes some graphics
#        intensive programs sluggish. Turning off autoflush causes updates
#        to happen during idle periods or when flush is called.

# Version 2.0
#     Updated Documentation
#     Made Polygon accept a list of Points in constructor
#     Made all drawing functions call TK update for easier animations
#          and to make the overall package work better with
#          Python 2.3 and IDLE 1.0 under Windows (still some issues).
#     Removed vestigial turtle graphics.
#     Added ability to configure font for Entry objects (analogous to Text)
#     Added setTextColour for Text as an alias of setFill
#     Changed to class-style exceptions
#     Fixed cloning of Text objects

# Version 1.6
#     Fixed Entry so StringVar uses _root as master, solves weird
#            interaction with shell in Idle
#     Fixed bug in setCoords. X and Y coordinates can increase in
#           "non-intuitive" direction.
#     Tweaked wm_protocol so window is not resizable and kill box closes.

# Version 1.5
#     Fixed bug in Entry. Can now define entry before creating a
#     GraphWin. All GraphWins are now toplevel windows and share
#     a fixed root (called _root).

# Version 1.4
#     Fixed Garbage collection of Tkinter images bug.
#     Added ability to set text atttributes.
#     Added Entry boxes.


##########################################################################
# Module Exceptions

class GraphicsError(Exception):
    """Generic error class for graphics module exceptions."""
    pass


class GraphicsWarning(Warning):
    pass


OBJ_ALREADY_DRAWN = "Object currently drawn"
UNSUPPORTED_METHOD = "Object doesn't support operation"
BAD_OPTION = "Illegal option value"
MISSING_VALUE = "Missing value required for Object"

# For the list of cursors and thumbnails visit: https://anzeljg.github.io/rin2/book2/2405/docs/tkinter/cursors.html
CURSORS = ["arrow", "based_arrow_down", "based_arrow_up", "boat", "bogosity", "bottom_left_corner",
           "bottom_right_corner", "bottom_side", "bottom_tee", "box_spiral", "center_ptr", "circle", "clock",
           "coffee_mug", "cross", "cross_reverse", "crosshair", "diamond_cross", "dot", "dotbox", "double_arrow",
           "draft_large", "draft_small", "draped_box", "exchange", "fleur", "gobbler", "gumpy", "hand1", "hand2",
           "heart", "icon", "iron_cross", "left_ptr", "left_side", "left_tee", "leftbutton", "ll_angle", "lr_angle",
           "man", "middlebutton", "mouse", "pencil", "pirate", "plus", "question_arrow", "right_ptr", "right_side",
           "right_tee", "rightbutton", "rtl_logo", "sailboat", "sb_down_arrow", "sb_h_double_arrow", "sb_left_arrow",
           "sb_right_arrow", "sb_up_arrow", "sb_v_double_arrow", "shuttle", "sizing", "spider", "spraycan", "star",
           "target", "tcross", "top_left_arrow", "top_left_corner", "top_right_corner", "top_side", "top_tee", "trek",
           "ul_angle", "umbrella", "ur_angle", "watch", "xterm", "x_cursor"]
RELIEF = ["flat", "groove", "raised", "ridge", "solid", "sunken"]

from tkinter import font as tkfonts

##########################################################################
# global variables and functions

_root = tk.Tk()
_root.withdraw()

fonts = tkfonts.families()

_update_lasttime = time.time()


# Other Image Functions


def resource_path(relative_path):
    # Get absolute path to resource, works for dev and for PyInstaller
    try:
        # PyInstaller creates a temp folder and stores path in _MEIPASS
        base_path = sys._MEIPASS
    except AttributeError:
        base_path = os.abspath(".")

    return os.join(base_path, relative_path)


# Defining Custom  & Colour Functions

class Colour:

    def __str__(self):
        return self.colour

    def __repr__(self):
        return self.colour


class ColourRGB(Colour):
    def __init__(self, r, g, b):
        if not (isinstance(r, int) and isinstance(g, int) and isinstance(b, int)):
            raise GraphicsError("RGB values must be integers!")
        if not (256 > r > -1 and 256 > g > -1 and 256 > b > -1):
            raise GraphicsError("RGB values must be between 0 & 255 (included), right now {}, {}, {}".format(r, g, b))
        self.colour = "#%02x%02x%02x" % (r, g, b)


class ColourHex(Colour):
    def __init__(self, colour):
        if not isinstance(colour, str):
            raise GraphicsError("Hex value must be a string in format: #rrggbb")
        if len(colour) != 7:
            raise GraphicsError("The length of the hex colour string must be 7: '#rrggbb'")
        self.colour = colour


class ColourCMYK(Colour):
    def __init__(self, c, y, m, k):
        if not (isinstance(c, int) and isinstance(y, int) and isinstance(m, int) and isinstance(k, int)):
            raise GraphicsError("CMYK values must be integers!")
        if not (101 > c > -1 and 101 > y > -1 and 101 > m > -1 and 101 > k > -1):
            raise GraphicsError("CMYK values must be between 0 & 100 (included), right now {}, {}, {}, {}".
                                format(c, m, y, k))

        r = 255 * (1 - (c + k) / 100)
        g = 255 * (1 - (m + k) / 100)
        b = 255 * (1 - (y + k) / 100)

        self.colour = "#%02x%02x%02x" % (r, g, b)


# The Blacks, Greys, and Whites
BLACK = ColourRGB(0, 0, 0)
DARKEST_GREY = ColourRGB(37, 37, 37)
DARKER_GREY = ColourRGB(40, 40, 40)
DARK_GREY = ColourRGB(45, 45, 45)

DARKISH_GREY = ColourRGB(60, 60, 60)
GREY = ColourRGB(100, 100, 100)
LIGHT_GREY = ColourRGB(160, 160, 160)
LIGHTER_GREY = ColourRGB(187, 187, 187)

DARK_WHITE = ColourRGB(240, 240, 240)
WHITE = ColourRGB(255, 255, 255)

# Blue-Greys
DARK_BLUE_GREY = ColourRGB(49, 51, 53)
BLUE_GREY = ColourRGB(60, 63, 65)
LIGHT_BLUE_GREY = ColourRGB(173, 175, 177)

# Warm Colours
DARK_RED = ColourRGB(120, 0, 0)
RED = ColourRGB(175, 0, 0)
DARK_ORANGE = ColourRGB(255, 102, 0)
ORANGE = ColourRGB(255, 153, 0)
CHROME_YELLOW = ColourRGB(255, 204, 0)

# Greens
DARK_GREEN = ColourRGB(0, 104, 60)
OLIVE_GREEN = ColourRGB(0, 100, 5)
GREEN = ColourRGB(0, 123, 45)
LIGHT_GREEN = ColourRGB(51, 187, 15)

# Blues
DARK_BLUE = None
BLUE = ColourRGB(0, 153, 255)
CYAN = None

# Purples & Pinks
DARK_PURPLE = None
PURPLE = None
LIGHT_PURPLE = None
PINK = None

globalStyle = "default"

STYLES = {"pycharm darcula": {"primary fill": DARK_GREY, "secondary fill": BLUE_GREY, "background": DARK_GREY,
                              "primary outline": None, "secondary outline": DARK_BLUE_GREY, "accent": LIGHT_BLUE_GREY,

                              "width": 1,
                              "fontColour": LIGHTER_GREY, "justify": "center", "font": "century gothic", "fontSize": 20,
                              "fontStyle": "normal"},

          "intellij": {"primary fill": DARK_GREY, "secondary fill": DARK_WHITE, "background": WHITE,
                       "primary outline": None, "secondary outline": LIGHTER_GREY, "accent": LIGHT_BLUE_GREY,

                       "width": 1,
                       "textColour": LIGHTER_GREY, "justify": "left", "font": ("century gothic", 20, "normal")},

          "default": {"primary fill": CHROME_YELLOW, "secondary fill": RED, "fill": CHROME_YELLOW, "background": WHITE,
                      "primary outline": BLACK, "secondary outline": GREY, "outline": BLACK,

                      "width": "2", "arrow": "none",
                      "textColour": BLACK, "text": "Lorem Ipsum", "justify": "center",
                      "font": "calibri", "fontSize": 5, "fontStyle": "normal", "selectColour": BLUE}
          }


# Add other colour definitions here!

############################################################################
# Graphics classes start here

def setStyle(style="default"):
    global globalStyle

    assert style in STYLES.keys(), "The style specified does not exist, must be one of {}".format(list(STYLES.keys()))
    globalStyle = style


def getScreenSize():
    return _root.winfo_screenwidth(), _root.winfo_screenheight()


class GraphWin(tk.Canvas):
    """A GraphWin is a toplevel window for displaying graphics."""
    canvases = []  # a list of all instances of this class

    def __init__(self, title="Graphics Window", width=800, height=600, xPos=70, yPos=80, style=None, bkColour=None,
                 icon=None, autoflush=True, resizableWidth=False, minWidth=300, resizableHeight=False, minHeight=200,
                 cursor="arrow", borderRelief="flat", borderWidth=0):

        if not isinstance(title, str):
            raise GraphicsError("The window's title must be a string")
        if not (isinstance(icon, str) or icon is None):
            raise GraphicsError("The window icon must be a string (path to .ico texture) or None, currently icon={}"
                                .format(icon))
        if not (isinstance(bkColour, Colour) or isinstance(bkColour, str) or bkColour is None):
            raise GraphicsError("The window's background Colour (bkColour) must be a Colour or string referencing a" +
                                "style colour")
        if not isinstance(autoflush, bool):
            raise GraphicsError("Auto-flush must be a boolean")
        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError("The window's width must be a number (integer or float)")
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError("The window's height must be a number (integer or float)")
        if not isinstance(resizableWidth, bool):
            raise GraphicsError("resizableWidth must be a boolean")
        if not isinstance(resizableHeight, bool):
            raise GraphicsError("resizableHeight must be a boolean")
        if not isinstance(minWidth, int):
            raise GraphicsError("The window's minimum width (minWidth) must be an integer")
        if not isinstance(minHeight, int):
            raise GraphicsError("The window's minimum height (minHeight) must be an integer")
        if not (isinstance(xPos, int) or isinstance(xPos, float)):
            raise GraphicsError("The window x-position (xPos) must be an integer")
        if not (isinstance(yPos, int) or isinstance(yPos, float)):
            raise GraphicsError("The window y-position (yPos) must be an integer")
        if not isinstance(cursor, str):
            raise GraphicsError("The cursor must be a string")
        if not cursor.lower() in CURSORS:
            raise GraphicsError("The cursor for the window is not valid, must be one of {}".format(CURSORS))
        if not isinstance(borderRelief, str):
            raise GraphicsError("The border relief (borderRelief) must be a string")
        if not borderRelief.lower() in RELIEF:
            raise GraphicsError("The relief for the window border is not valid, must be one of {}".format(RELIEF))
        if not isinstance(borderWidth, int):
            raise GraphicsError("The window's border Width must be an integer")

        if style is None:
            style = globalStyle
        elif style not in STYLES.keys():
            raise GraphicsError("The style you have specified ({}) is not valid. Must be one of {}".
                                format(style, list(STYLES.keys())))

        if width < minWidth:
            minWidth = width
            warning = "\n\nWindow width (width={}) is less than window's minimum width (minWidth={}. Window minimum width has been set to {})".format(
                width, minWidth, width)
            warnings.warn(warning, GraphicsWarning)

        if height < minHeight:
            minHeight = height
            warning = "\n\nWindow height (height={}) is less than window's minimum height (minHeight={}. Window minimum height has been set to {})".format(
                height, minHeight, height)
            warnings.warn(warning, GraphicsWarning)

        master = tk.Toplevel(_root)
        master.protocol("WM_DELETE_WINDOW", self.close)

        if not isinstance(bkColour, Colour):
            if bkColour in STYLES[style].keys():
                self.bkColour = STYLES[style]["background"]
            elif bkColour is None:
                self.bkColour = STYLES["default"]["background"]
        else:
            self.bkColour = bkColour

        tk.Canvas.__init__(self, master, width=_root.winfo_screenwidth(), height=_root.winfo_screenheight(),
                           highlightthickness=0, bd=borderWidth,
                           bg=self.bkColour, cursor=cursor.lower(), relief=borderRelief)

        self.master.config(width=width, height=height)

        self.trans = None
        self.closed = False
        self.autoflush = autoflush

        self.master.title(title)
        self.title = title
        self.cursor = cursor.lower()

        self.borderWidth = borderWidth
        self.borderRelief = borderRelief

        self.setBackground(self.bkColour)

        self.master.geometry('%dx%d+%d+%d' % (width, height, xPos, yPos))
        self.master.minsize(int(minWidth), int(minHeight))
        self.master.resizable(resizableWidth, resizableHeight)

        self.minWidth = minWidth
        self.minHeight = minHeight
        self.center = Point(width / 2, height / 2)

        if icon is not None:
            self.master.iconbitmap(icon)

        self.pack()

        self.imgs = 0

        self.items = []

        self.mouseLeftClick = None
        self.mouseMiddleClick = None
        self.mouseRightClick = None

        self.mouseLeftPress = None
        self.mouseRightPress = None
        self.mouseMiddlePress = None

        self.leftMouseClicks = 0
        self.middleMouseClicks = 0
        self.rightMouseClicks = 0

        self.lastMouse = None
        self.mousePos = None

        self.leftDown = False
        self.rightDown = False
        self.middleDown = False
        self.mouseIn = False

        self.bind("<Button-1>", self._onLeftClick)
        self.bind("<Button-2>", self._onMiddleClick)
        self.bind("<Button-3>", self._onRightClick)

        self.bind("<ButtonRelease-1>", self._onLeftRelease)
        self.bind("<ButtonRelease-2>", self._onMiddleRelease)
        self.bind("<ButtonRelease-3>", self._onRightRelease)

        self.bind("<ButtonPress-1>", self._onLeftPress)
        self.bind("<ButtonPress-2>", self._onMiddlePress)
        self.bind("<ButtonPress-3>", self._onRightPress)

        self.bind("<Motion>", self._onMouseMotion)
        self.bind_all("<MouseWheel>", self._onMouseWheel)
        self.bind("<Enter>", self._onMouseIn)
        self.bind("<Leave>", self._onMouseOut)
        self._mouseCallback = None

        self.mouseWheel = 0
        self.mouseScroll = 0
        self.lastKey = ""

        self.height = height
        self.width = width

        master.lift()

        if autoflush:
            _root.update()
        self.canvases.append(self)

        self.setCoords(0, 0, width, height)

    def __repr__(self):
        if self.isClosed():
            return "<Closed GraphWin>"
        else:
            return "GraphWin('{}', {}, {})".format(self.master.title(), self.getWidth(), self.getHeight())

    def __str__(self):
        return repr(self)

    def __checkOpen(self):
        if self.closed:
            raise GraphicsError("window is closed")

    def setMouseHandler(self, func):
        self._mouseCallback = func

    def getPosition(self):
        return Point(self.master.winfo_rootx(), self.master.winfo_rooty())

    def setBackground(self, colour):
        """Set background Colour of the window"""

        assert isinstance(colour, Colour), "The window's background Colour must be a Colour class"

        self.bkColour = colour
        self.__checkOpen()
        self.master.config(bg=colour)
        self.__autoflush()

    def setBorderWidth(self, width):

        assert isinstance(width, int), "The width argument must be an integer"

        self.borderWidth = width
        self.__checkOpen()
        self.master.config(bd=width)
        self.__autoflush()

    def setBorderRelief(self, relief):

        assert isinstance(relief, str), "The relief argument must be a string"
        assert relief.lower() in RELIEF, "The relief for the window border is not valid, must be one of {}".format(
            RELIEF)

        self.borderRelief = relief
        self.__checkOpen()
        self.master.config(relief=relief)
        self.__autoflush()

    def setCursor(self, cursor):

        assert isinstance(cursor, str), "The cursor argument must be a string"
        assert cursor.lower() in CURSORS, "The cursor argument must be one of {}".format(CURSORS)

        self.__checkOpen()
        self.cursor = cursor
        self.config(cursor=cursor)
        self.__autoflush()

    def setResizable(self, resizableWidth=True, resizableHeight=True):
        if not isinstance(resizableWidth, bool):
            raise GraphicsError("resizableWidth must be a boolean")
        if not isinstance(resizableHeight, bool):
            raise GraphicsError("resizableHeight must be a boolean")

        self.master.resizable(resizableWidth, resizableHeight)

    def setIcon(self, icon):

        if not isinstance(icon, str):
            raise GraphicsError("Icon must be a string to the path of the .ico file")

        self.__checkOpen()
        self.master.iconbitmap(icon)
        self.__autoflush()

    def setTitle(self, title):

        if not isinstance(title, str):
            raise GraphicsError("Title argument in setTitle function must be a string")

        self.title = title
        self.__checkOpen()
        self.master.title(title)
        self.__autoflush()

    def setWidth(self, width):

        if not isinstance(width, int):
            raise GraphicsError("Width argument must be an integer")

        if width < self.minWidth:
            self.minWidth = width
            warning = "\n\nWindow width (width={}) is less than window's minimum width (minWidth={}. Window minimum width has been set to {})".format(
                width, self.minWidth, width)
            warnings.warn(warning, GraphicsWarning)

            self.master.minsize(self.minWidth, self.minHeight)

        self.width = width
        self.__checkOpen()
        self.master.config(width=width)
        self.__autoflush()

    def setHeight(self, height):

        if not isinstance(height, int):
            raise GraphicsError("Height argument must be an integer")

        if height < self.minHeight:
            self.minHeight = height
            warning = "\n\nWindow height (height={}) is less than window's minimum height (minHeight={}. Window minimum height has been set to {})".format(
                height, self.minHeight, height)
            warnings.warn(warning, GraphicsWarning)

            self.master.minsize(self.minWidth, self.minHeight)

        self.height = height
        self.__checkOpen()
        self.master.config(height=height)
        self.__autoflush()

    def setMinHeight(self, height):

        if not isinstance(height, int):
            raise GraphicsError("Height argument must be an integer")

        self.minHeight = height
        if height > self.height:
            warning = "\n\nMinimum height (minHeight={}) is greater than the window's current height (height={})." + \
                      "Window's height has been set to {})".format(height, self.height, height)
            warnings.warn(warning, GraphicsWarning)
            self.setHeight(height)

    def setMinWidth(self, width):

        if not isinstance(width, int):
            raise GraphicsError("Width argument must be an integer")

        self.minWidth = width
        if width > self.width:
            warning = "\n\nMinimum width (minWidth={}) is greater than the window's current width (width={})." + \
                      "Window's width has been set to {})".format(width, self.width, width)
            warnings.warn(warning, GraphicsWarning)
            self.setWidth(width)

    def setSize(self, width, height):
        if not isinstance(height, int):
            raise GraphicsError("Height argument must be an integer")
        if not isinstance(width, int):
            raise GraphicsError("Width argument must be an integer")
        self.setHeight(height)
        self.setWidth(width)

    def setMinSize(self, minWidth, minHeight):
        if not isinstance(minHeight, int):
            raise GraphicsError("Height argument must be an integer")
        if not isinstance(minWidth, int):
            raise GraphicsError("Width argument must be an integer")
        self.setMinHeight(minHeight)
        self.setMinWidth(minWidth)

    def setCoords(self, x1, y1, x2, y2):
        """Set coordinates of window to run from (x1,y1) in the
        upper-left corner to (x2,y2) in the lower-right corner."""
        if not ((isinstance(x1, int) or isinstance(x1, float)) and (isinstance(y1, int) or isinstance(y1, float)) and
                (isinstance(x2, int) or isinstance(x2, float)) and (isinstance(y2, int) or isinstance(y2, float))):
            raise GraphicsError("Coordinate Arguments must be numbers (integers or floats)")
        self.trans = Transform(self.getWidth(), self.getHeight(), x1, y2, x2, y1)
        self.center = Point(abs((x2 - x1) / 2), abs((y2 - y1) / 2))
        self.redraw()

    def close(self):
        """Close the window"""

        if self.closed:
            return
        self.closed = True
        self.master.destroy()
        GraphWin.canvases.remove(self)
        self.__autoflush()

    def isClosed(self):
        return self.closed

    def isOpen(self):
        return not self.closed

    def __autoflush(self):
        if self.autoflush:
            _root.update()
            self.updateWin()

    def plot(self, x, y, colour=BLACK):
        """Set pixel (x,y) to the given Colour"""

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("x & y position must be numbers (integers, or floats)")
        if not (isinstance(colour, str) or isinstance(colour, Colour)):
            raise GraphicsError("Colour argument must be either a string or Colour object type")

        self.__checkOpen()
        xs, ys = self.toScreen(x, y)
        self.create_line(xs, ys, xs + 1, ys, fill=colour)
        self.__autoflush()

    def plotPixel(self, x, y, colour="black"):
        """Set pixel raw (independent of window coordinates) pixel
        (x,y) to Colour"""

        if not (isinstance(x, int) and isinstance(y, int)):
            raise GraphicsError("x & y position must be integers")
        if not (isinstance(colour, str) or isinstance(colour, Colour)):
            raise GraphicsError("Colour argument must be either a string or Colour object type")

        self.__checkOpen()
        self.create_line(x, y, x + 1, y, fill=colour)
        self.__autoflush()

    def flush(self):
        """Update drawing to the window"""
        self.__checkOpen()
        self.update_idletasks()

    def updateWin(self):
        self.update()

        GraphicsObject._onUpdate(self)

    def saveCanvas(self, height=None, width=None):
        x = self.master.winfo_rootx() + 20
        y = self.master.winfo_rooty() + 25

        if height is None:
            y1 = y + self.height * 5 / 4
        else:
            y1 = y + height * 5 / 4

        if width is None:
            x1 = x + self.width * 5 / 4
        else:
            x1 = x + width * 5 / 4

        self.imgs += 1
        return ImageGrab.grab().crop((x, y, x1, y1)).save("{}{}.png".format(self.title, self.imgs - 1))

    def getSize(self):
        return self.getWidth(), self.getHeight()

    # TRIGGER MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def _onLeftClick(self, e):
        if self.isOpen():
            self.mouseLeftClick = e.x, e.y
            self.lastMouse = self.trans.world(e.x, e.y)

            self.leftMouseClicks += 1

            if self._mouseCallback:
                self._mouseCallback(Point(e.x, e.y))

            GraphicsObject._onLeftClick(self)

    def _onMiddleClick(self, e):
        if self.isOpen():
            self.mouseMiddleClick = e.x, e.y
            self.lastMouseX = self.trans.world(e.x, e.y)

            self.middleMouseClicks += 1

            if self._mouseCallback:
                self._mouseCallback(Point(e.x, e.y))

            GraphicsObject._onMiddleClick()

    def _onRightClick(self, e):
        if self.isOpen():
            self.mouseRightClick = e.x, e.y
            self.lastMouse = self.trans.world(e.x, e.y)

            self.rightMouseClicks += 1

            if self._mouseCallback:
                self._mouseCallback(Point(e.x, e.y))

            GraphicsObject._onRightClick()

    # TRIGGER MOUSE RELEASE FUNCTIONS
    # -------------------------------------------------------------------------

    def _onLeftRelease(self, e):
        if self.isOpen():
            self.leftDown = False
            self._onLeftClick(e)

    def _onMiddleRelease(self, e):
        if self.isOpen():
            self.middleDown = False
            self._onMiddleClick(e)

    def _onRightRelease(self, e):
        if self.isOpen():
            self.rightDown = False
            self._onRightClick(e)

    # TRIGGER MOUSE PRESS FUNCTIONS
    # -------------------------------------------------------------------------

    def _onLeftPress(self, e):
        if self.isOpen():
            self.mouseLeftPress = e.x, e.y
            self.lastMouse = self.mouseLeftPress
            self.leftDown = True

            GraphicsObject._onLeftPress(self)

    def _onMiddlePress(self, e):
        if self.isOpen():
            self.middleDown = True

            self.mouseMiddlePress = e.x, e.y
            self.lastMouse = self.mouseMiddlePress

    def _onRightPress(self, e):
        if self.isOpen():
            self.rightDown = True

            self.mouseRightPress = e.x, e.y
            self.lastMouse = self.mouseRightPress

    # OTHER TRIGGER MOUSE FUNCTIONS
    # -------------------------------------------------------------------------

    def _onMouseMotion(self, e):
        if self.isOpen():
            self.mousePos = self.trans.world(e.x, e.y)

            if self.mouseIn:
                GraphicsObject._onMouseMotion(self)

    def _onMouseWheel(self, e):
        if self.isOpen():
            self.mouseWheel = e.delta
            GraphicsObject._onMouseWheel(e.delta / 120, self)

    def _onMouseIn(self, e):
        self.mouseIn = True

    def _onMouseOut(self, e):
        self.mouseIn = False

    # GET MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def getLeftMousePress(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mousePos = None

        while mousePos is None:
            mousePos = self.checkLeftMousePress()
            self.update()

            if self.isClosed(): break

        return mousePos

    def getMiddleMousePress(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mousePos = None

        while mousePos is None:
            mousePos = self.checkMiddleMousePress()
            self.update()

            if self.isClosed(): break

        return mousePos

    def getRightMousePress(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mousePos = None

        while mousePos is None:
            mousePos = self.checkRightMousePress()
            self.update()

            if self.isClosed(): break

        return mousePos

    # GET MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def getLeftMouseClick(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mousePos = None

        while mousePos is None:
            mousePos = self.checkLeftMouseClick()
            self.update()

            if self.isClosed():
                break

        return mousePos

    def getMiddleMouseClick(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mousePos = None

        while mousePos is None:
            mousePos = self.checkMiddleMouseClick()
            self.update()

            if self.isClosed(): break

        return mousePos

    def getRightMouseClick(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mousePos = None

        while mousePos is None:
            mousePos = self.checkRightMouseClick()
            self.update()

            if self.isClosed(): break

        return mousePos

    # MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def checkLeftMouseClick(self, refresh=True):

        if self.isClosed():
            pass
        if self.mouseLeftClick is not None and not self.isClosed():
            x, y = self.toWorld(self.mouseLeftClick[0], self.mouseLeftClick[1])

            if refresh:
                self.mouseLeftClick = None
            return Point(x, y)
        else:
            return None

    def checkMiddleMouseClick(self, refresh=True):

        if self.isClosed():
            pass
        if self.mouseMiddleClick is not None and not self.isClosed():
            x, y = self.toWorld(self.mouseMiddleClick[0], self.mouseMiddleClick[1])

            if refresh:
                self.mouseMiddleClick = None
            return Point(x, y)
        else:
            return None

    def checkRightMouseClick(self, refresh=True):

        if self.isClosed():
            pass
        if self.mouseRightClick is not None and not self.isClosed():
            x, y = self.toWorld(self.mouseRightClick[0], self.mouseRightClick[1])

            if refresh:
                self.mouseRightClick = None
            return Point(x, y)
        else:
            return None

    # MOUSE PRESS FUNCTIONS
    # -------------------------------------------------------------------------

    def checkLeftMousePress(self, refresh=True):
        if self.isClosed():
            pass
        if self.mouseLeftPress is not None and not self.isClosed():
            x, y = self.toWorld(self.mouseLeftPress[0], self.mouseLeftPress[1])

            if refresh:
                self.mouseLeftPress = None
            return Point(x, y)
        else:
            return None

    def checkMiddleMousePress(self, refresh=True):
        if self.mouseMiddlePress is not None and not self.Closed():
            x, y = self.toWorld(self.mouseMiddlePress[0], self.mouseMiddlePress[1])

            if refresh:
                self.mouseMiddlePress = None

            return Point(x, y)
        else:
            return None

    def checkRightMousePress(self, refresh=True):
        if self.mouseRightPress is not None and not self.Closed():
            x, y = self.toWorld(self.mouseRightPress[0], self.mouseRightPress[1])

            if refresh:
                self.mouseRightPress = None

            return Point(x, y)
        else:
            return None

    # OTHER MOUSE FUNCTIONS
    # -------------------------------------------------------------------------

    def checkMouseWheel(self):
        if self.isClosed():
            return None
        else:
            self.update()
            self.mouseScroll += self.mouseWheel / 120
            self.mouseWheel = 0

            return self.mouseScroll

    def getLastMouse(self):
        if self.lastMouse is not None:
            return Point(self.lastMouse[0], self.lastMouse[1])
        else:
            return

    def checkMouseMotion(self, refresh=True):
        if self.mousePos is not None:
            x, y = self.mousePos

            if refresh:
                self.mousePos = None

            return Point(x, y)
        else:
            return

    def checkLeftMouseDown(self):
        return self.leftDown

    def checkRightMouseDown(self):
        return self.rightDown

    def checkMiddleMouseDown(self):
        return self.middleDown

    # KEYBOARD FUNCTIONS
    # -------------------------------------------------------------------------

    def getKey(self, key):
        """Wait for user to press a key and return it as a string."""
        while not self.checkKey(key):
            time.sleep(.1)  # give up thread

        return True

    def checkKey(self, key):
        """Return last key pressed or None if no key pressed since last call"""
        if self.isClosed():
            raise GraphicsError("checkKey in closed window")

        if keyboard.is_pressed(key):
            return True
        else:
            return False

    def checkAllKeys(self, *keys):
        keyDown = True
        for key in keys:
            if keyDown:
                keyDown = self.checkKey(key)
            else:
                return False

        return True

    def checkKeys(self, *keys):
        for key in keys:
            if self.checkKey(key):
                return True

        return False

    def getHeight(self):
        """Return the height of the window"""
        self.height = self.master.winfo_height()
        return self.height

    def getWidth(self):
        """Return the width of the window"""
        self.width = self.master.winfo_width()
        return self.width

    def toScreen(self, x, y):
        trans = self.trans
        if trans:
            return self.trans.screen(x, y)
        else:
            return x, y

    def toWorld(self, x, y):
        trans = self.trans
        if trans:
            return self.trans.world(x, y)
        else:
            return x, y

    def addItem(self, item):
        self.items.append(item)

    def delItem(self, item):
        self.items.remove(item)

    def redraw(self):
        for item in self.items[:]:
            item.undraw()
            item.draw(self)
        self.update()

    def clear(self):
        for item in self.items[:]:
            item.undraw()

        if self.autoflush:
            self.update()


class Transform:
    """Internal class for 2-D coordinate transformations"""

    def __init__(self, w, h, xlow, ylow, xhigh, yhigh):
        # w, h are width and height of window
        # (xlow,ylow) coordinates of lower-left [raw (0,h-1)]
        # (xhigh,yhigh) coordinates of upper-right [raw (w-1,0)]
        xspan = (xhigh - xlow)
        yspan = (yhigh - ylow)
        self.xbase = xlow
        self.ybase = yhigh
        self.xscale = xspan / w
        self.yscale = yspan / h

    def screen(self, x, y):
        # Returns x,y in screen (actually window) coordinates
        xs = (x - self.xbase) / self.xscale
        ys = (self.ybase - y) / self.yscale
        return int(xs + 0.5), int(ys + 0.5)

    def world(self, xs, ys):
        # Returns xs,ys in world coordinates
        x = xs * self.xscale + self.xbase
        y = self.ybase - ys * self.yscale
        return x, y


class VectorEquation:
    def __init__(self, equation):
        self.equation = equation

    def __repr__(self):
        return self.equation

    def isClicked(self, mousePos):
        if mousePos is not None:
            x, y = mousePos.x, mousePos.y
            return eval(self.equation)


class GraphicsObject:
    """Generic base class for all of the drawable objects"""
    glidingObjects = []
    rotatingObjects = []
    resizingObjects = []
    blinkingObjects = []
    objects = []

    def __init__(self, options=(), style=None, cursor="arrow", window=None):
        # options is a list of strings indicating which options are
        # legal for this object.

        # When an object is drawn, canvas is set to the GraphWin(canvas)
        #    object where it is drawn and id is the TK identifier of the
        #    drawn shape.

        self.id = None

        if style is not None:
            self.style = style
        else:
            self.style = globalStyle

        # config is the dictionary of configuration options for the widget.
        self.config = {}
        for option in options:
            if option not in STYLES[self.style].keys():
                self.config[option] = STYLES["default"][option]
            else:
                self.config[option] = STYLES[self.style][option]

        if "width" in options:
            self.textWidth = self.config["width"]

        self.selectedClicks = -1
        self.selected = False
        self.anchor = self.getAnchor()

        self.isGliding = False
        self.glideQueue = []

        self.rotatingStart = None
        self.rotatingTime = None
        self.rotatingDist = None
        self.rotatingUpdate = None
        self.rotatingDest = None
        self.rotatingEasing = None
        self.rotatingInitial = None
        self.rotatingArgs = None
        self.isRotating = False
        self.rotation = 0

        self.resizingFactor = None
        self.resizingEasing = None
        self.isResizing = None

        self.resizingTime = None
        self.resizingUpdate = None
        self.resizingStart = None
        self.resizingArgs = None

        self.isBlinking = False
        self.blinkingInterval = None
        self.lastBlink = 0

        self.bounds = None

        assert isinstance(cursor, str), "The cursor argument must be a string"
        assert cursor.lower() in CURSORS, "The cursor argument must be one of {}".format(CURSORS)
        self.cursor = cursor

        self.graphwin = None
        self.drawn = False
        if window is not None:
            self.draw(window)

        GraphicsObject.objects.append(self)

    def __repr__(self):
        return "Graphics Object"

    def setClickable(self, clickable=True):
        if clickable:
            if self not in GraphicsObject.objects:
                GraphicsObject.objects.append(self)
        else:
            if self in GraphicsObject.objects:
                GraphicsObject.objects.remove(self)

        return self

    def setSelected(self, selected=True):
        self.selected = selected

    def setFill(self, colour):
        """Set interior Colour to Colour"""
        self._reconfig("fill", colour)
        return self

    def setOutline(self, colour):
        """Set outline Colour to Colour"""
        self._reconfig("outline", colour)
        return self

    def setWidth(self, width):
        """Set line weight to width"""
        self._reconfig("width", width)
        self.textWidth = width
        return self

    def draw(self, graphwin):

        """Draw the object in graphwin, which should be a GraphWin
        object.  A GraphicsObject may only be drawn into one
        window. Raises an error if attempt made to draw an object that
        is already visible."""

        if graphwin.isClosed():
            return self

        if self.drawn:
            return self

        self.graphwin = graphwin

        self.id = self._draw(graphwin, self.config)
        graphwin.addItem(self)
        if graphwin.autoflush:
            _root.update()

        self.drawn = True

        return self

    def setCursor(self, cursor="arrow"):
        self.cursor = cursor

    def animateBlinking(self, interval, animate=True):
        self.isBlinking = animate
        self.blinkingInterval = interval
        self.lastBlink = time.time()

        if animate and self not in GraphicsObject.blinkingObjects:
            GraphicsObject.blinkingObjects.append(self)
        elif not animate and self in GraphicsObject.blinkingObjects:
            GraphicsObject.blinkingObjects.remove(self)

    def undraw(self, setBlinking=True):

        """Undraw the object (i.e. hide it). Returns silently if the
        object is not currently drawn."""
        if self.drawn:
            try:
                if not self.graphwin.isClosed():
                    self.graphwin.delete(self.id)

                    self.graphwin.delItem(self)
                    if self.graphwin.autoflush:
                        _root.update()
            except ValueError:
                return

            self.drawn = False
            self.id = None
            if self.isBlinking and setBlinking:
                self.animateBlinking(0, animate=False)
        return self

    def setRotation(self, r):
        self.rotate(r - self.rotation)
        return self

    def getAnchor(self):
        pass

    def rotate(self, dr):
        self._rotate(dr)
        if self.graphwin is not None:
            self.redraw()

        return self

    def _rotate(self, dr):
        """updates internal state of object to rotate it r degrees CCW"""
        pass  # must override in subclass

    def move(self, dx, dy):

        """move object dx units in x direction and dy units in y
        direction"""

        self._move(dx, dy)
        if self.graphwin is not None:
            self.redraw()
        return self

    def moveTo(self, x, y):
        self.move(x - self.getAnchor().x, y - self.getAnchor().y)
        return self

    def moveY(self, dy):
        self.move(0, dy)
        return self

    def moveX(self, dx):
        self.move(dx, 0)
        return self

    def moveToY(self, y):
        self.move(0, y - self.getAnchor().y)
        return self

    def moveToX(self, x):
        self.move(x - self.getAnchor().x, 0)
        return self

    def glide(self, dx, dy, t, easing="Linear", args=None, frames="Frames"):
        if frames not in ["Time", "Frames"]:
            raise GraphicsError("frames parameter must be either 'Time' or 'Frames' not '{}'".format(frames))

        if len(self.glideQueue) == 0:
            lastT = time.time()
            lastDest = self.getAnchor().clone()
        else:
            lastT = self.glideQueue[len(self.glideQueue) - 1]["Start"] + self.glideQueue[len(self.glideQueue) - 1][
                "Time"]
            lastDest = self.glideQueue[len(self.glideQueue) - 1]["Dest"]

        self.glideQueue.append({"Dest": lastDest + Point(dx, dy),
                                "Initial": lastDest,
                                "Dist": Point(dx, dy),
                                "Easing": easing,
                                "Time": t,
                                "Update": lastT,
                                "Start": lastT,
                                "Args": args,
                                "Frames": frames})
        self.isGliding = True

        if self not in GraphicsObject.glidingObjects:
            GraphicsObject.glidingObjects.append(self)
        return self

    def glideTo(self, x, y, t, easing="Linear", args=None, frames="Frames"):
        if len(self.glideQueue) == 0:
            lastDest = self.getAnchor().clone()
        else:
            lastDest = self.glideQueue[len(self.glideQueue) - 1]["Dest"]

        self.glide(x - lastDest.x, y - lastDest.y, t, easing, args, frames)
        return self

    def glideToPoint(self, p, t, easing="Linear", args=None, frames="Frames"):
        self.glideTo(p.x, p.y, t, easing, args, frames)

    def animateSetRotation(self, r, t, easing="Linear", args=None, frames="Frames"):
        self.animateRotate(r - self.rotation, t, easing, args, frames)
        return self

    def _reconfig(self, option, setting):
        # Internal method for changing configuration of the object
        # Raises an error if the option does not exist in the config
        #    dictionary for this object
        if option not in self.config:
            raise GraphicsError(UNSUPPORTED_METHOD)
        options = self.config
        options[option] = setting
        if self.graphwin and not self.graphwin.isClosed():
            self.graphwin.itemconfig(self.id, options)
            if self.graphwin.autoflush:
                _root.update()

    def _draw(self, canvas, options):
        """draws appropriate figure on canvas with options provided
        Returns Tk id of item drawn"""
        pass  # must override in subclass

    def _move(self, dx, dy):
        """updates internal state of object to move it dx,dy units"""
        pass  # must override in subclass

    def redraw(self):
        if self.graphwin.isOpen():
            self.undraw()
            self.draw(self.graphwin)
        return self

    def isSelected(self):
        selected = self.isClicked(self.graphwin.getLastMouse())
        if selected:
            self.selectedClicks = self.graphwin.leftMouseClicks

        return selected or self.selectedClicks == self.graphwin.leftMouseClicks

    @staticmethod
    def _onUpdate(graphwin):
        t = time.time()
        for obj in GraphicsObject.glidingObjects:
            if obj.graphwin == graphwin and obj.drawn:
                if not obj.glideQueue[0]["Frames"] == "Time":
                    t = obj.glideQueue[0]["Update"] + 0.05

                if t - obj.glideQueue[0]["Start"] >= obj.glideQueue[0]["Time"]:
                    obj.isGliding = False
                    obj.glideQueue.pop(0)
                    if len(obj.glideQueue) == 0:
                        GraphicsObject.glidingObjects.remove(obj)
                else:
                    args = ""
                    if obj.glideQueue[0]["Args"] is not None:
                        args = ", {}".format(obj.glideQueue[0]["Args"])

                    per = eval("ease{}((obj.glideQueue[0]['Update'] - obj.glideQueue[0]['Start'])/"
                               "obj.glideQueue[0]['Time']{})".format(obj.glideQueue[0]["Easing"], args))
                    per = min([1, per])

                    obj.moveTo(obj.glideQueue[0]["Initial"].x + obj.glideQueue[0]["Dist"].x * per,
                               obj.glideQueue[0]["Initial"].y + obj.glideQueue[0]["Dist"].y * per)

                    if obj.glideQueue[0]["Frames"] == "Time":
                        obj.glideQueue[0]["Update"] = time.time()
                    else:
                        obj.glideQueue[0]["Update"] += 0.05

        t = time.time()
        for obj in GraphicsObject.rotatingObjects:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.rotatingStart >= obj.rotatingTime:
                    obj.isRotating = False
                    GraphicsObject.rotatingObjects.remove(obj)
                else:
                    args = ""
                    if obj.rotatingArgs is not None:
                        for arg in obj.rotatingArgs.split(","):
                            args += ", {}".format(arg)

                    per = eval(
                        f"ease{obj.rotatingEasing}((obj.rotatingUpdate - obj.rotatingStart)/obj.rotatingTime{args})")
                    obj.setRotation(obj.rotatingInitial + obj.rotatingDist * per)
                    obj.rotatingUpdate = t

        for obj in GraphicsObject.resizingObjects:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.resizingStart >= obj.resizingTime:
                    obj.isResizing = False
                    GraphicsObject.resizingObjects.remove(obj)
                else:
                    args = ""
                    if obj.resizingArgs is not None:
                        for arg in obj.resizingArgs.split(","):
                            args += ", {}".format(arg)

                    obj.resizeFactor(1 + obj.resizingFactor * ((t - obj.resizingStart)/obj.resizingTime),
                                     setInitialSize=False)
                    obj.resizingUpdate = t

        for obj in GraphicsObject.blinkingObjects:
            if obj.graphwin == graphwin:
                if t - obj.lastBlink > obj.blinkingInterval:
                    if obj.drawn:
                        obj.undraw(setBlinking=False)
                    else:
                        obj.draw(graphwin)
                    obj.lastBlink = t

    @staticmethod
    def _onLeftClick(graphwin):
        mousePos = graphwin.getLastMouse()

        for obj in SlideBar.slideBars:
            if obj.graphwin == graphwin:
                if obj.line.isClicked(mousePos):
                    if obj.orientation == "vertical":
                        obj.mouseValue(mousePos.y)
                    else:
                        obj.mouseValue(mousePos.x)

                obj.setSelected(False)

        for obj in Button.buttons:
            if obj.graphwin == graphwin and obj.graphic == obj.graphicClicked and obj.drawn:
                obj.undraw()
                if not obj.disabled:
                    obj.graphic = obj.graphicNormal
                obj.draw(obj.graphwin)

        for obj in CheckBox.checkBoxes:
            if obj.graphwin == graphwin:
                if obj.isClicked(mousePos):
                    obj.click()

    @staticmethod
    def _onLeftPress(graphwin):
        mousePos = graphwin.checkLeftMousePress(refresh=False)

        for obj in SlideBar.slideBars:
            if obj.graphwin == graphwin:
                if obj.isClicked(mousePos):
                    obj.setSelected()

        for obj in Button.buttons:
            if obj.graphwin == graphwin and obj.drawn:
                if obj.isClicked(mousePos):
                    obj.graphic.undraw()
                    obj.graphic = obj.graphicClicked
                    obj.draw(obj.graphwin)

        for obj in CheckBox.checkBoxes:
            if obj.graphwin == graphwin:
                obj.undraw()
                obj.graphic = obj.graphicClicked
                obj.draw(obj.graphwin)

        for obj in _BBox.resizingObjects:
            if obj.graphwin == graphwin:
                for bound in obj.resizingBounds:
                    if obj.resizingBounds[bound].isClicked(mousePos):
                        obj.isResizing[bound] = True
                        obj.resizingAnchor = obj.getAnchor()
                        obj.resizingInitialSize = obj.width, obj.height
                    else:
                        obj.isResizing[bound] = False

    @staticmethod
    def _onMouseMotion(graphwin):
        if graphwin.isOpen():
            mousePos = graphwin.checkMouseMotion(refresh=False)

            for obj in Button.buttons:
                if obj.graphwin == graphwin and obj.drawn:
                    if obj.isClicked(mousePos):
                        if not graphwin.leftDown:
                            if obj.graphic != obj.graphicHover:
                                obj.undraw()
                                obj.graphic = obj.graphicHover
                                obj.draw(graphwin)
                        else:
                            if obj.graphic != obj.graphicClicked:
                                obj.undraw()
                                obj.graphic = obj.graphicClicked
                                obj.draw(graphwin)

                    elif obj.graphic != obj.graphicNormal and not obj.disabled:
                        obj.undraw()
                        obj.graphic = obj.graphicNormal
                        obj.draw(graphwin)

            for obj in CheckBox.checkBoxes:
                if obj.graphwin == graphwin:
                    if obj.isClicked(mousePos):
                        if not graphwin.leftDown:
                            if obj.graphic != obj.graphicHover:
                                obj.undraw()
                                obj.graphic = obj.graphicHover
                                obj.draw(graphwin)

                    elif obj.graphic != obj.graphicNormal:
                        obj.graphic.undraw()
                        obj.graphic = obj.graphicNormal
                        obj.graphic.draw(graphwin)

            for obj in SlideBar.slideBars:
                if obj.graphwin == graphwin:
                    if obj.selected:
                        if obj.orientation == "vertical":
                            obj.mouseValue(mousePos.y)
                        else:
                            obj.mouseValue(mousePos.x)

            hoverCount = 0
            for obj in GraphicsObject.objects:
                if obj.graphwin == graphwin and graphwin.isOpen():
                    if obj.isClicked(mousePos):
                        graphwin.config(cursor=obj.cursor)
                        hoverCount += 1

            if hoverCount == 0:
                graphwin.setCursor(graphwin.cursor)

            if graphwin.leftDown:
                for obj in SlideBar.slideBars:
                    if obj.graphwin == graphwin and obj.isClicked(graphwin.getLastMouse()):
                        if obj.orientation == "vertical":
                            obj.mouseValue(mousePos.y)
                        else:
                            obj.mouseValue(mousePos.x)

                for obj in _BBox.resizingObjects:
                    if obj.graphwin == graphwin:
                        for bound in obj.resizingBounds:
                            if obj.isResizing[bound]:
                                if bound in ["left", "right"]:

                                    dir1 = "right"
                                    dir2 = "left"
                                    if bound == "left":
                                        if mousePos.x < obj.resizingAnchor.x + obj.resizingInitialSize[0] / 2:
                                            w = obj.resizingAnchor.x - mousePos.x + obj.resizingInitialSize[0] / 2

                                    elif bound == "right":
                                        dir1, dir2 = dir2, dir1
                                        if mousePos.x > obj.resizingAnchor.x - obj.resizingInitialSize[0] / 2:
                                            w = mousePos.x - obj.resizingAnchor.x + obj.resizingInitialSize[0] / 2

                                    obj.setObjectWidth(w, dir1)
                                    obj.resizingBounds[dir2].moveToX(mousePos.x)

                                    obj.resizingBounds["top"].setObjectWidth(w + obj.boundsThickness, dir1)
                                    obj.resizingBounds["bottom"].setObjectWidth(w + obj.boundsThickness, dir1)

                                else:
                                    dir1 = "bottom"
                                    dir2 = "top"
                                    if bound == "top":
                                        if mousePos.y < obj.resizingAnchor.y + obj.resizingInitialSize[1] / 2:
                                            h = obj.resizingAnchor.y - mousePos.y + obj.resizingInitialSize[1] / 2

                                    else:
                                        dir1, dir2 = dir2, dir1
                                        if mousePos.y > obj.resizingAnchor.y - obj.resizingInitialSize[1] / 2:
                                            h = mousePos.y - obj.resizingAnchor.y + obj.resizingInitialSize[1] / 2

                                    obj.setObjectHeight(h, dir1)
                                    obj.resizingBounds[dir2].moveToY(mousePos.y)

                                    obj.resizingBounds["left"].setObjectHeight(h + obj.boundsThickness, dir1)
                                    obj.resizingBounds["right"].setObjectHeight(h + obj.boundsThickness, dir1)

    @staticmethod
    def _onMiddleClick():
        pass

    @staticmethod
    def _onRightClick():
        pass

    @staticmethod
    def _onMouseWheel(e, graphwin):
        for obj in SlideBar.slideBarsBound:
            if obj.graphwin == graphwin:
                if obj.range[0] < int(obj.getValue() + e) < obj.range[1]:
                    obj.setValue(int(obj.getValue() + e))


class Point:
    def __init__(self, x, y):

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("x (x={}) & y (y={}) positions must be integers".format(x, y))

        self.x = float(x)
        self.y = float(y)

    def __repr__(self):
        return "Point({}, {})".format(self.x, self.y)

    def __mul__(self, other):
        try:
            return Point(self.x * other.x, self.y * other.y)
        except AttributeError:
            return Point(self.x * other, self.y * other)

    def __add__(self, other):
        try:
            return Point(self.x + other.x, self.y + other.y)
        except AttributeError:
            return Point(self.x + other, self.y + other)

    def _move(self, dx, dy):
        self.x = self.x + dx
        self.y = self.y + dy

    def distance(self, p2):

        if not isinstance(p2, Point):
            raise GraphicsError("p2 argument for distance calculation must be a Point class")
        return math.sqrt((p2.x - self.x) ** 2 + (p2.y - self.y) ** 2)

    def distanceX(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError("p2 argument for distance calculation must be a Point class")
        return p2.x - self.x

    def distanceY(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError("p2 argument for distance calculation must be a Point class")
        return p2.y - self.y

    def clone(self):
        return Point(self.x, self.y)

    def swap(self):
        t = self.y
        self.y = self.x
        self.x = t

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def addY(self, dy):
        self.y += dy
        return self

    def addX(self, dx):
        self.x += dx
        return self

    def setX(self, x):
        self.x = x
        return self

    def setY(self, y):
        self.y = y
        return self

    def getAnchor(self):
        return self


class _BBox(GraphicsObject):
    # Internal base class for objects represented by bounding box
    # (opposite corners) Line segment is a degenerate case.

    resizingObjects = []

    def __init__(self, p1, p2, bounds=None, style=None, fill=None,
                 outline=None, width=None, options=("fill", "outline", "width"), cursor="arrow", window=None):

        if not isinstance(bounds, _BBox) and bounds is not None:
            raise GraphicsError("Bounds argument must be another Graphics Object (Rectangle, " +
                                "Rounded Rectangle, Circle, Line, or Oval), right now, bounds={}".format(bounds))

        self.p1 = p1.clone()
        self.p2 = p2.clone()

        if not isinstance(self, Line):
            x1 = p1.x
            x2 = p2.x
            y1 = p1.y
            y2 = p2.y

            if x1 > x2:
                self.p1.x = x2
                self.p2.x = x1

            if y1 > y2:
                self.p1.y = y2
                self.p2.y = y1

        GraphicsObject.__init__(self, style=style, options=options, cursor=cursor, window=window)

        # abs(p2.x - p1.x) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = self.p2.x - self.p1.x
        self.height = self.p2.y - self.p1.y

        self.minWidth = None
        self.minHeight = None
        self.maxWidth = None
        self.maxHeight = None

        self.resizingBounds = {}
        self.isResizing = {}
        self.boundsThickness = 0

        if fill is not None:
            if isinstance(fill, str):
                if fill not in STYLES[self.style]:
                    raise GraphicsError(
                        "The fill argument (right now, fill='{}') must be inside the object's style ({}). One of: {}".
                            format(fill, self.style, STYLES[self.style]))
                self.setFill(STYLES[self.style][fill])
            else:
                if not isinstance(fill, Colour):
                    raise GraphicsError("The fill argument (right now, fill='{}') must either be a string or a Colour "
                                        "Class".format(fill))

                self.setFill(fill)

        if outline is not None:
            if isinstance(outline, str):
                self.setOutline(STYLES[self.style][outline])
            else:
                self.setOutline(outline)

        if width is not None:
            if isinstance(width, str):
                self.setWidth(STYLES[self.style][width])
            else:
                self.setWidth(width)

    def __repr__(self):
        return "BBox"

    def _update(self):
        pass

    def _setResizable(self, resizables, thickness=10):
        pass

    def showBounds(self):
        self.boundsObject = Rectangle(self.bounds.p1, self.bounds.p2, outline=CHROME_YELLOW, width=0,
                                      cursor=self.cursor).draw(self.graphwin)

    def hideBounds(self):
        self.boundsObject.undraw()

    def _move(self, dx, dy):
        self.p1.x = self.p1.x + dx
        self.p1.y = self.p1.y + dy
        self.p2.x = self.p2.x + dx
        self.p2.y = self.p2.y + dy

        self.anchor = self.getAnchor()
        self._update()

    def getP1(self):
        return self.p1.clone()

    def getP2(self):
        return self.p2.clone()

    def getCenter(self):
        p1 = self.p1
        p2 = self.p2
        return Point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0)

    def isClicked(self, mousePos):
        if self.bounds is None:
            if mousePos is not None:
                if (self.p1.x < mousePos.x < self.p2.x or self.p1.x > mousePos.x > self.p2.x) and \
                        (self.p1.y < mousePos.y < self.p2.y or self.p1.y > mousePos.y > self.p2.y):
                    return True
                else:
                    return False
        else:
            return self.bounds.isClicked(mousePos)

    def getAnchor(self):
        return Point((self.p1.x + self.p2.x) / 2, (self.p1.y + self.p2.y) / 2)

    def resetBounds(self):
        self.bounds = _BBox(self.p1, self.p2)

    def setBounds(self, p1, p2):
        self.bounds = _BBox(p1, p2)

    def setCoords(self, p1, p2):

        x1 = p1.x
        x2 = p2.x
        y1 = p1.y
        y2 = p2.y

        if x1 > x2:
            p1.x = x2
            p2.x = x1

        if y1 > y2:
            p1.y = y2
            p2.y = y1

        self.p1 = p1.clone()
        self.p2 = p2.clone()

        widthScale = (p2.x - p1.x) / self.width
        heightScale = (p2.y - p1.y) / self.height

        # abs(p2.x - p1.x) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = p2.x - p1.x
        self.height = p2.y - p1.y

        self.anchor = Point((self.p1.x + self.p2.x) / 2, (self.p1.y + self.p2.y) / 2)

        if self.drawn:
            self.redraw()

        self._update()

        return widthScale, heightScale

    def setObjectWidth(self, width, center="center"):
        if center not in ["center", "right", "left"]:
            raise GraphicsError("The center argument for resizing the object (setObjectWidth) needs to be one of {}"
                                .format(["center", "right", "left"]))

        if center == "left":
            widthScale, _ = self.setCoords(self.p1, self.p2.addX(width - self.width))

        elif center == "right":
            widthScale, _ = self.setCoords(self.p1.addX(-(width - self.width)), self.p2)
        else:
            widthScale, _ = self.setCoords(self.p1.addX(-(width / 2 - self.width)),
                                           self.p2.addX(width / 2 - self.width))

        if self.bounds is not None:
            self.bounds.setObjectWidth(widthScale * self.bounds.width, center)

        return self

    def setObjectHeight(self, height, center="center"):
        if center not in ["center", "top", "bottom"]:
            raise GraphicsError("The center argument for resizing the object (setObjectHeight) needs to be one of {}"
                                .format(["center", "top", "bottom"]))

        if center == "top":
            _, heightScale = self.setCoords(self.p1, self.p2.addY(height - self.height))

        elif center == "bottom":
            _, heightScale = self.setCoords(self.p1.addY(-(height - self.height)), self.p2)
        else:
            _, heightScale = self.setCoords(self.p1.addY(-(height / 2 - self.height)),
                                            self.p2.addY(height / 2 - self.height))

        if self.bounds is not None:
            self.bounds.setObjectWidth(heightScale * self.bounds.height, center)

        return self

    def setObjectDimensions(self, width, height, widthCenter="center", heightCenter="center"):
        self.setObjectWidth(width, widthCenter)
        self.setObjectHeight(height, heightCenter)
        return self

    def setResizable(self, top=False, left=False, bottom=False, right=False, minWidth=40, minHeight=40, boundsWidth=10):
        self._setResizable([top, bottom, left, right], thickness=boundsWidth)
        _BBox.resizingObjects.append(self)
        self.boundsThickness = boundsWidth

        return self


class Rectangle(_BBox):

    def __init__(self, p1, p2, bounds=None, style=None, fill=None, outline=None, width=None,
                 cursor="arrow", window=None):
        _BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, width=width,
                       style=style, cursor=cursor, window=window)

        self.equation = VectorEquation("abs((x - {})/{} + (y - {})/{}) + abs((x - {})/{} - (y - {})/{}) < 2".
                                       format(self.anchor.x, self.width / 2, self.anchor.y, self.height / 2,
                                              self.anchor.x,
                                              self.width / 2, self.anchor.y, self.height / 2))

        """
        self.equation = VectorEquation("(abs((x - {})/{} + (y - {})/{}) + abs((x - {})/{} - (y - {})/{}) < 2) and not "
                                       "(abs((x - {})/(0.5*{}) + (y - {})/(0.5*{})) + abs((x - {})/(0.5*{}) - (y - {})/(0.5*{})) < 2)".
                                       format(self.anchor.x, self.width/2, self.anchor.y, self.height/2, self.anchor.x,
                                              self.width/2, self.anchor.y, self.height/2,

                                              self.anchor.x, self.width/2, self.anchor.y, self.height/2, self.anchor.x,
                                              self.width/2, self.anchor.y, self.height/2))"""

    def __repr__(self):
        return "Rectangle({}, {})".format(str(self.p1), str(self.p2))

    def _setResizable(self, resizables, thickness=10):
        self.resizingBounds = {}
        if resizables[0]:
            self.resizingBounds["top"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                   Point(self.p2.x + thickness / 2, self.p1.y + thickness / 2),
                                                   cursor="sb_v_double_arrow")
        if resizables[1]:
            self.resizingBounds["bottom"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y - thickness / 2),
                                                      Point(self.p1.x - thickness / 2, self.p2.y + thickness / 2),
                                                      cursor="sb_v_double_arrow")
        if resizables[2]:
            self.resizingBounds["left"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                    Point(self.p1.x + thickness / 2, self.p2.y + thickness / 2),
                                                    cursor="sb_h_double_arrow")
        if resizables[3]:
            self.resizingBounds["right"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y + thickness / 2),
                                                     Point(self.p2.x - thickness / 2, self.p1.y - thickness / 2),
                                                     cursor="sb_h_double_arrow")

        for obj in self.resizingBounds.values():
            obj.graphwin = self.graphwin
            obj.draw(self.graphwin)

    def _draw(self, canvas, options):
        p1 = self.p1
        p2 = self.p2

        x1, y1 = canvas.toScreen(p1.x, p1.y)
        x2, y2 = canvas.toScreen(p2.x, p2.y)

        for obj in self.resizingBounds.values():
            obj.graphwin = self.graphwin

        return canvas.create_rectangle(x1, y1, x2, y2, options)

    def clone(self):
        other = Rectangle(self.p1, self.p2)
        other.config = self.config.copy()
        return other

    def isClicked(self, mousePos):
        if self.bounds is None:
            return self.equation.isClicked(mousePos)
        else:
            return self.bounds.isClicked(mousePos)

    def _update(self):
        self.equation = VectorEquation("abs((x - {})/{} + (y - {})/{}) + abs((x - {})/{} - (y - {})/{}) < 2".
                                       format(self.anchor.x, self.width / 2, self.anchor.y, self.height / 2,
                                              self.anchor.x,
                                              self.width / 2, self.anchor.y, self.height / 2))


class RoundedRectangle(_BBox):

    def __init__(self, p1, p2, radius, bounds=None, style=None, fill=None, outline=None,
                 width=None, cursor="arrow", window=None):
        self.p1 = p1
        self.p2 = p2

        self.points = [Point(p1.x + radius, p1.y),
                       Point(p1.x + radius, p1.y),
                       Point(p2.x - radius, p1.y),
                       Point(p2.x - radius, p1.y),
                       Point(p2.x, p1.y),
                       Point(p2.x, p1.y + radius),
                       Point(p2.x, p1.y + radius),
                       Point(p2.x, p2.y - radius),
                       Point(p2.x, p2.y - radius),
                       Point(p2.x, p2.y),
                       Point(p2.x - radius, p2.y),
                       Point(p2.x - radius, p2.y),
                       Point(p1.x + radius, p2.y),
                       Point(p1.x + radius, p2.y),
                       Point(p1.x, p2.y),
                       Point(p1.x, p2.y - radius),
                       Point(p1.x, p2.y - radius),
                       Point(p1.x, p1.y + radius),
                       Point(p1.x, p1.y + radius),
                       Point(p1.x, p1.y)]
        self.graphic = Polygon(self.points)

        _BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, width=width, cursor=cursor,
                       window=window)

    def _draw(self, canvas, options):
        self.graphic.draw(canvas)

    def undraw(self):
        self.graphic.undraw()


class Oval(_BBox):

    def __init__(self, center, radius1, radius2, bounds=None, style=None, fill=None, outline=None, width=None,
                 cursor="arrow", window=None):

        p1 = Point(center.x - radius1, center.y - radius2)
        p2 = Point(center.x + radius1, center.y + radius2)

        self.radius1 = radius1
        self.radius2 = radius2

        _BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, width=width, style=style, cursor=cursor,
                       window=window)

        self.equation = VectorEquation("(((x-{})**2)/({}**2))+(((y-{})**2)/({}**2)) < 1".format(center.x, radius1,
                                                                                                center.y, radius2))

    def __repr__(self):
        return "Oval({}, {})".format(str(self.p1), str(self.p2))

    def clone(self):
        other = Oval(self.p1, self.p2)
        other.config = self.config.copy()
        return other

    def _draw(self, canvas, options):
        p1 = self.p1
        p2 = self.p2
        x1, y1 = canvas.toScreen(p1.x, p1.y)
        x2, y2 = canvas.toScreen(p2.x, p2.y)
        return canvas.create_oval(x1, y1, x2, y2, options)

    def _setResizable(self, resizables, thickness=10):
        self.resizingBounds = {}
        if resizables[0]:
            self.resizingBounds["top"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                   Point(self.p2.x + thickness / 2, self.p1.y + thickness / 2),
                                                   cursor="sb_v_double_arrow")
        if resizables[1]:
            self.resizingBounds["bottom"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y - thickness / 2),
                                                      Point(self.p1.x - thickness / 2, self.p2.y + thickness / 2),
                                                      cursor="sb_v_double_arrow")
        if resizables[2]:
            self.resizingBounds["left"] = Rectangle(Point(self.p1.x - thickness / 2, self.p1.y - thickness / 2),
                                                    Point(self.p1.x + thickness / 2, self.p2.y + thickness / 2),
                                                    cursor="sb_h_double_arrow")
        if resizables[3]:
            self.resizingBounds["right"] = Rectangle(Point(self.p2.x + thickness / 2, self.p2.y + thickness / 2),
                                                     Point(self.p2.x - thickness / 2, self.p1.y - thickness / 2),
                                                     cursor="sb_h_double_arrow")

    def isClicked(self, mousePos):
        if self.bounds is None:
            return self.equation.isClicked(mousePos)
        else:
            return self.bounds.isClicked(mousePos)

    def _update(self):
        self.equation = VectorEquation("(((x-{})**2)/({}**2))+(((y-{})**2)/({}**2)) < 1".format(self.anchor.x,
                                                                                                self.radius1,
                                                                                                self.anchor.y,
                                                                                                self.radius2))


class Circle(Oval):

    def __init__(self, center, radius, bounds=None, style=None, fill=None, outline=None,
                 width=None, cursor="arrow", window=None):
        p1 = Point(center.x - radius, center.y - radius)
        p2 = Point(center.x + radius, center.y + radius)

        self.center = center

        self.radius = radius
        Oval.__init__(self, center, radius, radius, bounds=bounds, fill=fill, outline=outline, width=width, style=style,
                      cursor=cursor,
                      window=window)

        self.equation = VectorEquation("(x-{})**2 + (y-{})**2 < {}**2".format(self.center.x, self.center.y, radius))

    def __repr__(self):
        return super().__repr__()

    def clone(self):
        other = Circle(self.getCenter(), self.radius)
        other.config = self.config.copy()
        return other

    def getRadius(self):
        return self.radius

    def _update(self):
        self.equation = VectorEquation("(x-{})**2 + (y-{})**2 < {}**2".format(self.center.x, self.center.y,
                                                                              self.radius))


class Arc(GraphicsObject):
    def __init__(self, p1, angle, radius, radius2=None, style=None, fill=None, outline=None, width=None, cursor="arrow",
                 window=None):
        self.angle = angle

        GraphicsObject.__init__(self, style=style, options=["fill", "outline", "width"], cursor=cursor, window=window)

        self.anchor = p1

        self.radius1 = radius
        if radius2 is None:
            self.radius2 = radius

        # self.equation = VectorEquation()

    def _draw(self, canvas, options):
        pass


class Line(_BBox):

    def __init__(self, p1, p2, bounds=None, style=None, outline=None, width=None, arrow=None, cursor="arrow",
                 window=None):

        self.setOutline = self.setFill

        _BBox.__init__(self, p1, p2, bounds=bounds, outline=outline, width=width, style=style,
                       options=["arrow", "width", "fill"], cursor=cursor, window=window)

        if arrow is not None:
            try:
                self.setArrow(STYLES[self.style][arrow])
            except KeyError:
                self.setArrow(arrow)
        else:
            self.setArrow(self.config["arrow"])

    def __repr__(self):
        return "Line({}, {})".format(str(self.p1), str(self.p2))

    def clone(self):
        other = Line(self.p1, self.p2)
        other.config = self.config.copy()
        return other

    def _draw(self, canvas, options):
        p1 = self.p1
        p2 = self.p2
        x1, y1 = canvas.toScreen(p1.x, p1.y)
        x2, y2 = canvas.toScreen(p2.x, p2.y)
        self.graphwin = canvas
        return canvas.create_line(x1, y1, x2, y2, options)

    def setArrow(self, option):
        if option.lower() not in ["first", "last", "both", "none"]:
            raise GraphicsError(BAD_OPTION)
        self._reconfig("arrow", option)

    def removeArrows(self):
        self.setArrow("none")

    def setArrowBoth(self):
        self.setArrow("none")

    def setArrowFirst(self):
        self.setArrow("none")

    def setArrowLast(self):
        self.setArrow("none")


class Polygon(GraphicsObject):

    def __init__(self, *points, style=None, fill=None, outline=None, width=None, window=None):

        # if points passed as a list, extract it
        if len(points) == 1 and isinstance(points[0], list):
            points = points[0]
            points = points[0]
        self.points = list(map(Point.clone, points))
        GraphicsObject.__init__(self, style=style, options=["outline", "width", "fill"], window=window)

    def __repr__(self):
        return "Polygon" + str(tuple(p for p in self.points))

    def clone(self):
        other = Polygon(*self.points)
        other.config = self.config.copy()
        return other

    def getPoints(self):
        return list(map(Point.clone, self.points))

    def _move(self, dx, dy):
        for p in self.points:
            p.move(dx, dy)

    def getAnchor(self):
        x = 0
        y = 0

        for point in self.points:
            x += point.x
            y += point.y

        x /= len(self.points)
        y /= len(self.points)

        return Point(x, y)

    def _draw(self, canvas, options):
        args = [canvas]
        for p in self.points:
            x, y = canvas.toScreen(p.x, p.y)
            args.append(x)
            args.append(y)
        args.append(options)
        return GraphWin.create_polygon(*args, smooth=True)


class Text(GraphicsObject):

    def __init__(self, p, text, style=None, fontSize=None, font=None, fontStyle=None, outline=None, justify="center",
                 window=None):

        self.anchor = p.clone()
        GraphicsObject.__init__(self, style=style, options=["justify", "fill", "text", "font"],
                                window=window)

        if style is None:
            self.style = globalStyle
        else:
            self.style = style

        if isinstance(outline, Colour):
            self.outline = outline
        elif outline in STYLES[self.style].keys():
            self.outline = STYLES[self.style][outline]
        else:
            if "outline" in STYLES[self.style].keys():
                self.outline = STYLES[self.style]["outline"]
            else:
                self.outline = STYLES["default"]["outline"]

        if isinstance(fontSize, int):
            self.fontSize = fontSize
        elif fontSize in STYLES[self.style].keys():
            self.fontSize = STYLES[self.style][fontSize]
        else:
            if "fontSize" in STYLES[self.style].keys():
                self.fontSize = STYLES[self.style]["fontSize"]
            else:
                self.fontSize = STYLES["default"]["fontSize"]

        if fontStyle in STYLES[self.style].keys():
            self.fontStyle = STYLES[self.style][fontStyle]
        elif isinstance(fontStyle, str):
            self.fontStyle = fontStyle
        else:
            if "fontStyle" in STYLES[self.style].keys():
                self.fontStyle = STYLES[self.style]["fontStyle"]
            else:
                self.fontStyle = STYLES["default"]["fontStyle"]

        if font in STYLES[self.style].keys():
            self.font = STYLES[self.style][font]
        elif isinstance(font, str):
            self.font = font
        else:
            if "font" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font"]
            else:
                self.font = STYLES["default"]["font"]

        if justify in STYLES[self.style].keys():
            self.justify = STYLES[self.style][justify]
        elif isinstance(justify, str):
            self.justify = justify
        else:
            if "justify" in STYLES[self.style].keys():
                self.justify = STYLES[self.style]["justify"]
            else:
                self.justify = STYLES["default"]["justify"]

        self.initialFontSize = self.fontSize

        self.setSize(self.fontSize, False)

        self.setFill(self.outline)
        self.setFace(self.font)

        self.setStyle(self.fontStyle)
        self.setOutline = self.setFill

        self.setJustify(self.justify)

        self.setText(text)

    def __repr__(self):
        return "Text({}, '{}')".format(self.anchor, self.getText())

    def _draw(self, canvas, options):
        p = self.anchor
        x, y = canvas.toScreen(p.x, p.y)
        self.setSize(abs(int(self.initialFontSize / canvas.trans.xscale)), False)
        return canvas.create_text(x, y, options)

    def _move(self, dx, dy):
        self.anchor.changeDir(dx, dy)

    def isClicked(self, mousePos):
        return False

    def clone(self):
        other = Text(self.anchor, self.config['text'])
        other.config = self.config.copy()
        return other

    def setText(self, text):
        self._reconfig("text", text)

    def getText(self):
        return self.config["text"]

    def getAnchor(self):
        return self.anchor.clone()

    def setFace(self, face):
        f, s, b = self.config['font']
        self._reconfig("font", (face, s, b))

    def setJustify(self, justify):
        self._reconfig("justify", justify)

    def setSize(self, size, updateInit=True):
        f, s, b = self.font, size, self.fontStyle
        self.fontSize = size

        if updateInit:
            self.initialFontSize = size
        self._reconfig("font", (f, size, b))

    def setStyle(self, style):
        if style in ['bold', 'normal', 'italic', 'bold italic']:
            f, s, b = self.config['font']
            self._reconfig("font", (f, s, style))
        else:
            raise GraphicsError(BAD_OPTION)

    def setTextColour(self, Colour):
        self.setFill(Colour)


class Entry(GraphicsObject):

    def __init__(self, p, textWidth=10, style=None, fill=None, fontColour=None, entry=None, font=None, fontSize=None,
                 outline=None, fontStyle=None, width=None, borderType="flat", password=False, active="NORMAL",
                 window=None, justify="center", cursor="xterm", selectColour=None, defaultText=""):

        self.anchor = p.clone()
        self.textWidth = textWidth
        self.text = tk.StringVar(_root)
        self.text.set("")

        if style is None:
            self.style = globalStyle
        else:
            self.style = style

        if isinstance(fill, Colour):
            self.fill = fill
        elif fill in STYLES[self.style].keys():
            self.fill = STYLES[self.style][fill]
        else:
            if "fill" in STYLES[self.style].keys():
                self.fill = STYLES[self.style]["fill"]
            else:
                self.fill = STYLES["default"]["fill"]

        if isinstance(selectColour, Colour):
            self.selectColour = selectColour
        elif selectColour in STYLES[self.style].keys():
            self.selectColour = STYLES[self.style][selectColour]
        else:
            if "selectColour" in STYLES[self.style].keys():
                self.selectColour = STYLES[self.style]["selectColour"]
            else:
                self.selectColour = STYLES["default"]["selectColour"]

        if isinstance(fontColour, Colour):
            self.fontColour = fontColour
        elif fontColour in STYLES[self.style].keys():
            self.fontColour = STYLES[self.style][fontColour]
        else:
            if "fontColour" in STYLES[self.style].keys():
                self.fontColour = STYLES[self.style]["fontColour"]
            else:
                self.fontColour = STYLES["default"]["fontColour"]

        if isinstance(width, int):
            self.width = width
        elif width in STYLES[self.style].keys():
            self.width = STYLES[self.style][width]
        else:
            if "width" in STYLES[self.style].keys():
                self.width = STYLES[self.style]["width"]
            else:
                self.width = STYLES["default"]["width"]

        if isinstance(fontSize, int):
            self.fontSize = fontSize
        elif fontSize in STYLES[self.style].keys():
            self.fontSize = STYLES[self.style][fontSize]
        else:
            if "fontSize" in STYLES[self.style].keys():
                self.fontSize = STYLES[self.style]["fontSize"]
            else:
                self.fontSize = STYLES["default"]["fontSize"]

        if fontStyle in STYLES[self.style].keys():
            self.fontStyle = STYLES[self.style][fontStyle]
        elif isinstance(fontStyle, str):
            self.fontStyle = fontStyle
        else:
            if "fontStyle" in STYLES[self.style].keys():
                self.fontStyle = STYLES[self.style]["fontStyle"]
            else:
                self.fontStyle = STYLES["default"]["fontStyle"]

        if font in STYLES[self.style].keys():
            self.font = STYLES[self.style][font]
        elif isinstance(font, str):
            self.font = font
        else:
            if "font" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font"]
            else:
                self.font = STYLES["default"]["font"]

        if justify in STYLES[self.style].keys():
            self.justify = STYLES[self.style][justify]
        elif isinstance(justify, str):
            self.justify = justify
        else:
            if "justify" in STYLES[self.style].keys():
                self.justify = STYLES[self.style]["justify"]
            else:
                self.justify = STYLES["default"]["justify"]

        self.fontConfig = (self.font, self.fontSize, self.fontStyle)
        self.entry = entry
        self.borderType = borderType
        if password:
            self.text = "*"
        else:
            self.text = ""
        self.active = "normal"
        self.defaultText = defaultText
        self.cursor = cursor

        self.initialSize = self.fontSize

        GraphicsObject.__init__(self, style=style, options=["fill", "outline"], window=window)

    def __repr__(self):
        return "Entry({}, {})".format(self.anchor, self.textWidth)

    def _onEdit(self):
        pass

    def isClicked(self, mousePos):
        return False

    def disable(self):
        self.active = "disabled"
        if self.entry:
            self.entry.config(state=self.active)

    def enable(self):
        self.active = "normal"
        if self.entry:
            self.entry.config(state=self.active)

    def toggleActive(self):
        self.active = ["normal", "disabled"][["disabled", "normal"].index(self.active)]
        if self.entry:
            self.entry.config(state=self.active)

    def setActive(self, active):
        if active not in ["normal", "disabled", "readonly"]:
            raise GraphicsError("State must be either normal, disabled or readonly")
        self.active = active
        if self.entry:
            self.entry.config(state=self.active)

    def setTextType(self, type):
        self.text = type
        if self.entry:
            self.entry.config(show=self.text)

    def _draw(self, canvas, options):
        p = self.anchor
        x, y = canvas.toScreen(p.x, p.y)
        frm = tk.Frame(canvas.master)

        self.setSize(self.initialSize / canvas.trans.xscale, False)

        self.entry = tk.Entry(frm,
                              width=self.textWidth, textvariable=self.text, bg=self.fill, fg=self.fontColour,
                              bd=self.width, font=self.fontConfig, insertbackground=self.fontColour, show=self.text,
                              state=self.active, justify="center", cursor="xterm", exportselection=0,
                              selectbackground=self.selectColour)
        self.entry.insert(0, self.defaultText)

        self.entry.pack()
        self.entry.focus_set()
        return canvas.create_window(x, y, window=frm)

    def getText(self):
        return self.entry.get()

    def _move(self, dx, dy):
        self.anchor.changeDir(dx, dy)

    def getAnchor(self):
        return self.anchor.clone()

    def clone(self):
        other = Entry(self.anchor, self.textWidth)
        other.config = self.config.copy()
        other.text = tk.StringVar()
        other.text.set(self.text.get())
        other.fill = self.fill
        return other

    def setText(self, t):
        self.entry.insert(0, t)

    def setFill(self, Colour):
        self.fill = Colour
        if self.entry:
            self.entry.config(bg=Colour)

    def _setFontComponent(self, which, value):
        font = (self.font, self.fontSize, self.fontStyle)

        self.fontConfig = list(self.fontConfig)
        self.fontConfig[which] = value

        if self.entry:
            self.entry.config(font=font)

    def setFace(self, face):
        self._setFontComponent(0, face)

    def setSize(self, size, updateSize=True):
        if updateSize:
            self.initialSize = round(size)
        self._setFontComponent(1, round(size))

    def setStyle(self, style):
        self._setFontComponent(2, style)

    def setTextColour(self, Colour):
        self.Colour = Colour
        if self.entry:
            self.entry.config(fg=Colour)

    def setBorderType(self, border):
        if border not in ["flat", "groove", "raised", "ridge", "solid", "sunken"]:
            raise GraphicsError("border type must be flat, groove, raised, ridge, solid, or sunken")
        if self.entry:
            self.borderType = border
            self.entry.config(relief=border)


class Image(GraphicsObject):
    idCount = 0
    imageCache = {}  # tk photo images go here to avoid GC while drawn

    def __init__(self, p, filepath, rotation=0, align="center", window=None):

        self.imageId = Image.idCount
        Image.idCount = Image.idCount + 1

        self.texture = "textures/{}".format(filepath)
        self.rotation = rotation

        self.imgPIL = Img.open(self.texture).rotate(self.rotation)
        self.img = ImageTk.PhotoImage(self.imgPIL)

        self.initialWidth = self.getWidth()
        self.initialHeight = self.getHeight()

        self.rotationImg = self.imgPIL
        self.align = align
        
        self.anchor = p.clone()
        
        if align not in ["center", "bottom", "top", "left", "right"]:
            raise GraphicsError(f"Image align must be one of center, bottom, top, left, or right, not {align}")

        self.x = self.anchor.x
        self.y = self.anchor.y
            
        GraphicsObject.__init__(self, [], window=window)

    def __repr__(self):
        return "Image({}, {})".format(self.anchor, self.texture)

    def _draw(self, canvas, options):
        self.imageCache[self.imageId] = self.img  # save a reference

        initWidth = abs(self.initialWidth / canvas.trans.xscale)
        initHeight = abs(self.initialHeight / canvas.trans.yscale)

        width = (math.sin(math.radians(90 - abs(self.rotation))) * initWidth) \
                + (initHeight * math.sin(math.radians(abs(self.rotation))))
        height = (math.sin(math.radians(90 - abs(self.rotation))) * initHeight) \
                 + (initWidth * math.sin(math.radians(abs(self.rotation))))

        p = self.anchor.clone()

        if self.align == "bottom":
            p.addY(self.initialHeight/-2)
        elif self.align == "top":
            p.addY(self.initialHeight/2)
        elif self.align == "left":
            p.addX(self.initialWidth/2)
        elif self.align == "right":
            p.addX(self.initialWidth/-2)

        self.graphwin = canvas
        x, y = canvas.toScreen(p.x, p.y)

        self.resize(width, height, setInitialSize=False)
        return canvas.create_image(x, y, image=self.img)

    def _move(self, dx, dy):
        self.anchor.x += dx
        self.anchor.y += dy

    def update(self):
        try:
            self.img = ImageTk.PhotoImage(self.imgPIL, master=self.graphwin.master)
        except AttributeError:
            self.img = ImageTk.PhotoImage(self.imgPIL)

        if self.graphwin is not None:
            if self.graphwin.autoflush:
                self.graphwin.update()

    def alphaComposite(self, img):
        self.imgPIL = Img.alpha_composite(self.imgPIL, img.imgPIL)
        self.rotationImg = self.imgPIL
        self.update()
        return self

    def blend(self, img, alpha):
        self.imgPIL = Img.blend(self.imgPIL, img.imgPIL, alpha)
        self.rotationImg = self.imgPIL
        self.update()
        return self

    def composite(self, img, imgMask):
        self.imgPIL = Img.composite(self.imgPIL, img.imgPIL, imgMask.img)
        self.rotationImg = self.imgPIL
        self.update()
        return self

    def convertGreyscale(self):
        self.imgPIL = self.imgPIL.convert("LA")
        self.rotationImg = self.imgPIL
        self.update()
        return self

    def convertBinary(self):
        self.imgPIL = self.imgPIl.convert("1")
        self.rotationImg = self.imgPIL
        self.update()
        return self

    def _rotate(self, dr, sampling=Img.BICUBIC, center=None):
        self.rotation += dr
        if center is not None:
            self.imgPIL = self.imgPIL.rotate(angle=self.rotation, resample=sampling, expand=True,
                                             center=(center.x, center.y))
        else:
            self.imgPIL = self.rotationImg.rotate(angle=self.rotation, resample=sampling, expand=True)
        self.update()
        return self

    def animateRotate(self, dr, t, easing="Linear", args=None):
        self.rotatingDest = self.rotation + dr
        self.rotatingInitial = self.rotation
        self.rotatingDist = dr
        self.rotatingEasing = easing

        self.isRotating = True

        self.rotatingTime = t
        self.rotatingUpdate = time.time()
        self.rotatingStart = self.rotatingUpdate
        self.rotatingArgs = args

        GraphicsObject.rotatingObjects.append(self)
        return self

    def setRotation(self, r, sampling=Img.BICUBIC, center=None):
        self.rotate(r - self.rotation)
        return self

    def animateResizeFactor(self, f, t, easing="Linear", args=None):
        self.resizingFactor = f
        self.resizingEasing = easing
        self.isResizing = True

        self.resizingTime = t
        self.resizingUpdate = time.time()
        self.resizingStart = self.resizingUpdate
        self.resizingArgs = args

        GraphicsObject.resizingObjects.append(self)

    def undraw(self, setBlinking=True):
        try:
            del self.imageCache[self.imageId]  # allow gc of tk photo image
        except KeyError:
            pass
        if self.isBlinking and setBlinking:
            self.animateBlinking(0, animate=False)
        GraphicsObject.undraw(self, setBlinking)
        return self

    def getAnchor(self):
        return self.anchor.clone()

    def clone(self):
        other = Image(Point(0, 0), 0, 0)
        other.img = self.img.copy()
        other.anchor = self.anchor.clone()
        other.config = self.config.copy()
        return other

    def getWidth(self):
        """Returns the width of the image in pixels"""
        return self.img.width()

    def getHeight(self):
        """Returns the height of the image in pixels"""
        return self.img.height()

    def getPixel(self, x, y):
        """Returns a list [r,g,b] with the RGB Colour values for pixel (x,y)
        r,g,b are in range(256)

        """
        return self.imgPIL.getpixel((x, y))

    def setPixel(self, x, y, Colour):
        """Sets pixel (x,y) to the given Colour

        """
        self.imgPIL = self.imgPIL.putpixel((x, y), Colour)
        self.img = ImageTk.PhotoImage(self.imgPIL)
        return self

    def save(self, filename):
        """Saves the pixmap image to filename.
        The format for the save image is determined from the filname extension.

        """

    def isClicked(self, mousePos):
        width, height = abs(self.img.width() * self.graphwin.trans.xscale), abs(
            self.img.height() * self.graphwin.trans.yscale)
        if mousePos is not None:
            if (self.anchor.x - width / 2 < mousePos.x < self.anchor.x + width / 2) and (
                    self.anchor.y - height / 2 < mousePos.y < self.anchor.y + height / 2):
                return True
            else:
                return False

    def crop(self, left, top, right, down):
        self.imgPIL = self.imgPIL.crop(box=(left, top, right, down))
        self.update()
        return self

    def resize(self, width, height, sampling=Img.BICUBIC, setInitialSize=True):
        self.imgPIL = self.imgPIL.resize((int(width), int(height)), sampling)

        if setInitialSize:
            self.initialWidth = width
            self.initialHeight = height
        self.update()
        return self

    def resizeFactor(self, factor, sampling=Img.BICUBIC, setInitialSize=True):
        self.resizeWidthFactor(factor, sampling, setInitialSize)
        self.resizeHeightFactor(factor, sampling, setInitialSize)
        return self

    def resizeWidthFactor(self, factor, sampling=Img.BICUBIC, setInitialSize=True):
        self.resize(int(self.getWidth() * factor), self.getHeight(), sampling, setInitialSize)
        return self

    def resizeHeightFactor(self, factor, sampling=Img.BICUBIC, setInitialSize=True):
        self.resize(self.getWidth(), int(self.getHeight() * factor), sampling, setInitialSize)
        return self

    def filterBlur(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.BLUR)
        self.update()
        return self

    def filterBlurBox(self, radius=3):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.BoxBlur(radius))
        self.update()
        return self

    def filterBlurGaussian(self, radius=3):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.GaussianBlur(radius))
        self.update()
        return self

    def filterBlurUnsharp(self, radius=3, percent=150):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.UnsharpMask(radius=radius, percent=percent))
        self.update()
        return self

    def filterContour(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.CONTOUR)
        self.update()
        return self

    def filterDetail(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.DETAIL)
        self.update()
        return self

    def filterEmboss(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.EMBOSS)
        self.update()
        return self

    def filterFindEdges(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.FIND_EDGES)
        self.update()
        return self

    def filterSharpen(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.SHARPEN)
        self.update()
        return self

    def filterSmooth(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.SMOOTH)
        self.update()
        return self

    def filterMoreSmooth(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.SMOOTH_MORE)
        self.update()
        return self

    def filterEnhanceEdge(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.EDGE_ENHANCE)
        self.update()
        return self

    def filterMoreEnhanceEdge(self):
        self.imgPIL = self.imgPIL.filter(filter=ImageFilter.EDGE_ENHANCE_MORE)
        self.update()
        return self


class Image_depr(GraphicsObject):
    idCount = 0
    imageCache = {}  # tk photo images go here to avoid GC while drawn

    def __init__(self, p, *pixmap, graphwin=None, rotation=0):

        GraphicsObject.__init__(self, [])
        self.anchor = p.clone()
        self.imageId = Image.idCount
        Image.idCount = Image.idCount + 1

        self.texture = "textures/{}".format(pixmap[0])

        self.x = p.x
        self.y = p.y
        self.graphwin = graphwin
        self.pixmap = pixmap

        if len(pixmap) == 1:  # file name provided
            self.img = tk.PhotoImage(file=resource_path("textures/{}".format(pixmap[0])), master=_root)
        else:  # width and height provided
            width, height = pixmap
            self.img = tk.PhotoImage(master=_root, width=width, height=height)

    def __repr__(self):
        return "Image({}, {})".format(self.anchor, self.texture)

    def _draw(self, canvas, options):
        p = self.anchor
        self.graphwin = canvas
        x, y = canvas.toScreen(p.x, p.y)
        self.imageCache[self.imageId] = self.img  # save a reference
        return canvas.create_image(x, y, image=self.img)

    def _move(self, dx, dy):
        self.anchor.x += dx
        self.anchor.y += dy

    def moveTo(self, x, y):
        self.move(x - self.x, y - self.y)

    def undraw(self):
        try:
            del self.imageCache[self.imageId]  # allow gc of tk photo image
        except KeyError:
            pass
        GraphicsObject.undraw(self)

    def getAnchor(self):
        return self.anchor.clone()

    def clone(self):
        other = Image(Point(0, 0), 0, 0)
        other.img = self.img.copy()
        other.anchor = self.anchor.clone()
        other.config = self.config.copy()
        return other

    def getWidth(self):
        """Returns the width of the image in pixels"""
        return self.img.width()

    def getHeight(self):
        """Returns the height of the image in pixels"""
        return self.img.height()

    def getPixel(self, x, y):
        """Returns a list [r,g,b] with the RGB Colour values for pixel (x,y)
        r,g,b are in range(256)

        """

        value = self.img.get(x, y)
        if type(value) == type(0):
            return [value, value, value]
        elif type(value) == type((0, 0, 0)):
            return list(value)
        else:
            return list(map(int, value.split()))

    def setPixel(self, x, y, Colour):
        """Sets pixel (x,y) to the given Colour

        """
        self.img.put("{" + Colour + "}", (x, y))

    def save(self, filename):
        """Saves the pixmap image to filename.
        The format for the save image is determined from the filname extension.

        """

        path, name = os.path.split(filename)
        ext = name.split(".")[-1]
        self.img.write(filename, format=ext)

    def isClicked(self, mousePos):
        if mousePos is not None:
            if (self.x - self.img.width() / 2 < mousePos.x < self.x + self.img.width() / 2) and (
                    self.y - self.img.height() / 2 < mousePos.y < self.y + self.img.height() / 2):
                return True
            else:
                return False

    def resize(self, scale):
        self.img = self.img.subsample(scale)
        return self

    def zoom(self, scale):
        self.img = self.img.zoom(scale)
        return self

    def flip(self):
        self.img = self.img.subsample(-1)


class Button:
    buttons = []

    def __init__(self, graphic, graphicHover=None, graphicClicked=None, graphicDisabled=None,
                 disable=False, autoflush=True, label=None, sound=None, window=None):

        self.graphicNormal = graphic

        if graphicHover is not None:
            self.graphicHover = graphicHover
        else:
            self.graphicHover = graphic

        if graphicClicked is not None:
            self.graphicClicked = graphicClicked
        else:
            self.graphicClicked = graphic

        if graphicDisabled is not None:
            self.graphicDisabled = graphicDisabled
        else:
            self.graphicDisabled = graphic

        if not (isinstance(self.graphicNormal, GraphicsObject) and isinstance(self.graphicClicked, GraphicsObject)
                and isinstance(self.graphicDisabled, GraphicsObject) and isinstance(self.graphicHover, GraphicsObject)):
            raise GraphicsError("The graphics all have to be Graphic Objects")

        self.graphic = self.graphicNormal

        self.label = label

        self.disabled = disable

        self.graphwin = None

        if not isinstance(self, CheckBox):
            Button.buttons.append(self)

        GraphicsObject.__init__(self, [], window=window)

    def __repr__(self):
        return "Button({})".format(self.graphic)

    def draw(self, canvas):
        self.graphic.draw(canvas)

        if self.label is not None:
            self.label.draw(canvas)
        self.graphwin = canvas

        self.drawn = True
        return self

    def undraw(self):
        self.graphic.undraw()
        if self.label is not None:
            self.label.undraw()

        self.drawn = False
        return self

    def redraw(self):
        if self.graphic.graphwin is None and self.graphwin is not None:
            self.graphic.graphwin = self.graphwin

        if self.label is not None:
            self.label.redraw()

        self.drawn = True
        self.graphic.redraw()

        return self

    def setGraphic(self, graphic):
        self.undraw()
        if graphic == "Normal":
            self.graphic = self.graphicNormal
        elif graphic == "Hover":
            self.graphic = self.graphicHover
        elif graphic == "Clicked":
            self.graphic = self.graphicClicked
        elif graphic == "Disabled":
            self.graphic = self.graphicDisabled

        self.draw(self.graphwin)

    def animateRotate(self, dr, t, easing="Linear", args=None):
        self.graphicHover.animateRotate(dr, t, easing, args)
        self.graphicNormal.animateRotate(dr, t, easing, args)
        self.graphicClicked.animateRotate(dr, t, easing, args)
        self.graphicDisabled.animateRotate(dr, t, easing, args)

        self.isRotating = True

        if self.label is not None:
            self.label.animateRotate(dr, t, easing, args)

    def move(self, dx, dy):
        self.graphicHover.move(dx, dy)
        self.graphicNormal.move(dx, dy)
        self.graphicClicked.move(dx, dy)
        self.graphicDisabled.move(dx, dy)

        if self.label is not None:
            self.label.move(dx, dy)

    def moveTo(self, x, y):
        self.graphicHover.moveTo(x, y)
        self.graphicNormal.moveTo(x, y)
        self.graphicClicked.moveTo(x, y)
        self.graphicDisabled.moveTo(x, y)

        if self.label is not None:
            self.label.moveTo(x, y)

    def isClicked(self, mousePos):
        return self.graphic.isClicked(mousePos) and not self.disabled

    def setOutline(self, Colour):
        self.graphic.setOutline(Colour)

    def getAnchor(self):
        return self.graphic.anchor

    def setWidth(self, width):
        self.graphic.setWidth(width)

    def setFill(self, Colour):
        self.graphic.setFill(Colour)

    def disable(self):
        self.disabled = True

        self.undraw()
        self.graphic = self.graphicDisabled
        self.draw(self.graphwin)

    def enable(self):
        self.disabled = False

        self.undraw()
        self.graphic = self.graphicNormal
        self.draw(self.graphwin)

    def changeEnabled(self):
        pass

    def setEnabled(self, enable):
        pass

    def changeGraphic(self, graphic=None, graphicHover=None, graphicClicked=None, graphicDisabled=None, label=None):
        self.undraw()
        if graphicHover is not None: self.graphicHover = graphicHover
        if graphic is not None: self.graphicNormal = graphic
        if graphicClicked is not None: self.graphicClicked = graphicClicked
        if graphicDisabled is not None: self.graphicDisabled = graphicDisabled

        if label is not None: self.label = label

        self.draw(self.graphwin)


class CheckBox(Button):
    checkBoxes = []

    def __init__(self, trueGraphic, falseGraphic, trueGraphicHover=None, falseGraphicHover=None,
                 trueGraphicClicked=None, falseGraphicClicked=None, graphicDisabled=None, state=True, window=None):

        self.state = state

        #

        self.trueGraphic = trueGraphic
        if trueGraphicHover is not None:
            self.trueGraphicHover = trueGraphicHover
        else:
            self.trueGraphicHover = trueGraphic

        if trueGraphicClicked is not None:
            self.trueGraphicClicked = trueGraphicClicked
        else:
            self.trueGraphicClicked = trueGraphic

        #

        self.falseGraphic = falseGraphic
        if falseGraphicHover is not None:
            self.falseGraphicHover = falseGraphicHover
        else:
            self.falseGraphicHover = falseGraphic

        if falseGraphicClicked is not None:
            self.falseGraphicClicked = falseGraphicClicked
        else:
            self.falseGraphicClicked = falseGraphic

        if graphicDisabled is not None:
            self.graphicDisabled = graphicDisabled
        else:
            self.graphicDisabled = falseGraphic

        self.graphwin = None
        self.drawn = False

        if self.state:
            super().__init__(self.trueGraphic, self.trueGraphicHover, self.trueGraphicClicked, self.graphicDisabled)
        else:
            super().__init__(self.falseGraphic, self.falseGraphicHover, self.falseGraphicClicked,
                             self.graphicDisabled)

        CheckBox.checkBoxes.append(self)

        if window is not None:
            self.draw(window)

    def __repr__(self):
        return "CheckBox({}, {})".format(self.trueGraphic, self.falseGraphic)

    def draw(self, canvas):
        self.graphwin = canvas

        self.graphic.draw(canvas)
        self.drawn = True

        return self

    def moveTo(self, x, y):
        self.graphic.moveTo(x, y)

    def setState(self, state):
        self.graphic.undraw()
        self.state = state

        if self.state:
            self.changeGraphic(self.trueGraphic, self.trueGraphicHover, self.trueGraphicClicked,
                               self.graphicDisabled)

        else:
            self.changeGraphic(self.falseGraphic, self.falseGraphicHover, self.falseGraphicClicked,
                               self.graphicDisabled)

    def getAnchor(self):
        return self.graphic.anchor

    def changeState(self):
        self.setState(not self.state)

    def click(self):
        self.changeState()

    def changeGraphics(self, trueGraphic=None, trueGraphicHover=None, trueGraphicClicked=None, falseGraphic=None,
                       falseGraphicHover=None, falseGraphicClicked=None, graphicDisabled=None):

        self.graphic.undraw()

        if trueGraphic is not None: self.trueGraphic = trueGraphic
        if trueGraphicHover is not None: self.trueGraphicHover = trueGraphicHover
        if trueGraphicClicked is not None: self.trueGraphicClicked = trueGraphicClicked

        if falseGraphic is not None: self.falseGraphic = falseGraphic
        if falseGraphicHover is not None: self.falseGraphicHover = falseGraphicHover
        if falseGraphicClicked is not None: self.falseGraphicClicked = falseGraphicClicked

        if graphicDisabled is not None: self.graphicDisabled = graphicDisabled

        if self.state:
            self.changeGraphic(self.trueGraphic, self.trueGraphicHover, self.trueGraphicClicked,
                               self.graphicDisabled)

        else:
            self.changeGraphic(self.falseGraphic, self.falseGraphicHover, self.falseGraphicClicked,
                               self.graphicDisabled)

        self.graphic.draw(self.graphwin)


class CycleButton:
    def __init__(self, state, *states, window):
        self.states = list(states)
        self.state = state

        self.label = None

        for obj in states:
            if not isinstance(obj, GraphicsObject):
                raise GraphicsError("The states must all be Graphic Objects")

        self.graphwin = None
        self.graphic = states[state]

        GraphicsObject.__init__(self, [], window=window)

    def changeGraphic(self, element, value):
        self.states[element] = value

    def append(self, state):
        self.states.append(state)

    def remove(self, state):
        if state not in self.states:
            raise GraphicsError("The state to remove is not an existing state of this cycle button")

        self.states.remove(state)

    def pop(self, index):
        if index < 0:
            raise GraphicsError("The given index is a negative number")

        elif index > len(self.states) - 1:
            raise GraphicsError("The specified index cannot be removed as it does not exist")

        self.states.pop(index)

    def getAnchor(self):
        return self.graphic.anchor

    def rotate(self, dr):
        for graphic in self.states:
            graphic.rotate(dr)

    def setRotation(self, r):
        for graphic in self.states:
            graphic.setRotation(r)

    def animateRotate(self, dr, t, easing="Linear", args=None):

        self.rotatingDest = self.rotation + dr
        self.rotatingInitial = self.rotation
        self.rotatingDist = dr
        self.rotatingEasing = easing

        self.isRotating = True

        self.rotatingTime = t
        self.rotatingUpdate = time.time()
        self.rotatingStart = self.rotatingUpdate
        self.rotatingArgs = args

        GraphicsObject.rotatingObjects.append(self)
        return self


class SlideBar:
    slideBars = []
    slideBarsBound = []

    def __init__(self, p, length, orientation, minimum, maximum, value, pointer, step=1, style=None, outline=None,
                 width=None, text=None, label="Value "):

        self.range = [minimum - 1, maximum + 1]
        self.state = value - minimum

        if not self.range[1] > value > self.range[0]:
            raise GraphicsError(f"Slide Bar value must between min/max values: {minimum} < value ({value}) < {maximum}")

        self.anchor = p.clone()

        self.maximum = maximum
        self.minimum = minimum

        if self.minimum > self.maximum:
            self.minimum, self.maximum = self.maximum, self.minimum
        elif self.minimum == self.maximum:
            raise GraphicsError("Minimum and Maximum value cannot be the same")

        if orientation == "vertical":
            self.p1 = Point(self.anchor.x, self.anchor.y - length / 2)
            self.p2 = Point(self.anchor.x, self.anchor.y + length / 2)

            self.scale = self.p1.distanceY(self.p2) / (self.maximum - self.minimum)
            self.valuePoints = [y * self.scale + self.p1.y for y in range(int((maximum - minimum + 1) / step))]
        else:
            self.p1 = Point(self.anchor.x - length / 2, self.anchor.y)
            self.p2 = Point(self.anchor.x + length / 2, self.anchor.y)

            self.scale = self.p1.distanceX(self.p2) / (self.maximum - self.minimum)
            self.valuePoints = [x * self.scale + self.p1.x for x in range(int((maximum - minimum + 1) / step))]

        self.graphwin = None
        self.drawn = False
        self.selected = False

        self.orientation = orientation
        self.length = length
        self.step = step

        self.pointer = pointer
        self.text = text
        self.line = None

        self.style = style
        self.outline = outline
        self.width = width

        self.style = style
        self.label = label

        self.setValue(value)
        self.reload()

        SlideBar.slideBars.append(self)

    def __repr__(self):
        return "SlideBar({}, {}, {}-{})".format(self.p1, self.p2, self.minimum, self.maximum)

    def setSelected(self, selected=True):
        self.selected = selected

    def draw(self, canvas):
        self.graphwin = canvas

        if self.text is not None:
            self.text.draw(canvas)

        self.line.draw(canvas)
        self.pointer.draw(canvas)

        self.drawn = True
        return self

    def getAnchor(self):
        return self.anchor

    def reload(self):

        self.line = Line(self.p1, self.p2, style=self.style, outline=self.outline, width=self.width)

        if self.text is not None:
            self.text.setText(f"{self.label}{self.state}")

        try:
            selectedClicks = self.pointer.selectedClicks
        except AttributeError:
            selectedClicks = -1

        if self.orientation == "vertical":
            self.pointer.moveTo(self.anchor.x, ((self.state - self.minimum) * self.scale) + self.p1.y)
        else:
            self.pointer.moveTo(((self.state - self.minimum) * self.scale) + self.p1.x, self.anchor.y)

        self.pointer.selectedClicks = selectedClicks

    def undraw(self):
        self.line.undraw()

        if self.text is not None:
            self.text.undraw()
        self.pointer.undraw()
        self.drawn = False

    def redraw(self):
        self.undraw()
        self.reload()
        self.draw(self.graphwin)

    def setValue(self, value):
        if value < self.minimum or value > self.maximum:
            raise GraphicsError(
                f"Value to set the Slider Bar must be within {self.minimum} and {self.maximum} not {value}")
        self.state = value
        try:
            self.redraw()
        except AttributeError:
            self.reload()

    def changeValue(self, value):
        self.setValue(self.state + value)

    def mouseValue(self, mousePos):
        self.setValue(self.minimum + self.valuePoints.index(min(self.valuePoints, key=lambda x: abs(x - mousePos)))
                      * self.step)

    def move(self, dx, dy):
        self.undraw()

        self.line.move(dx, dy)
        if self.text is not None:
            self.text.move(dx, dy)
        self.pointer.move(dx, dy)

        self.p1 = Point(self.p1.x + dx, self.p1.y + dy)
        self.p2 = Point(self.p2.x + dx, self.p2.y + dy)

        self.draw(self.graphwin)

    def isClicked(self, mousePos):
        return self.pointer.isClicked(mousePos) or self.line.isClicked(mousePos)

    def isSelected(self):
        return self.pointer.isSelected()

    def getValue(self):
        return self.state

    def bindMouseWheel(self, state=True):
        if state:
            if self not in self.slideBarsBound:
                self.slideBarsBound.append(self)
        else:
            if self in self.slideBarsBound:
                self.slideBarsBound.remove(self)


class RadioButton:
    def __init__(self, **boxes):
        self.boxes = boxes

    def draw(self):
        pass

    def undraw(self):
        pass

    def redraw(self):
        pass

    def setState(self):
        pass


# Time Related Functions

def update(rate=None):
    global _update_lasttime
    if rate:
        now = time.time()
        pauseLength = 1 / rate - (now - _update_lasttime)
        if pauseLength > 0:
            time.sleep(pauseLength)
            _update_lasttime = now + pauseLength
        else:
            _update_lasttime = now

    _root.update()


def wait(t):
    time.sleep(t)


# Interpolation Functions

def easeLinear(t):
    return t


def easePolyIn(t, power=2):
    return t ** power


def easePolyOut(t, power=2):
    return 1 - (t ** power)


def easePoly(t, power=2):
    t *= 2
    if t < 1:
        return t ** power
    else:
        return 2 - ((2 - t) ** power)


def easeSinIn(t):
    return 1 - math.cos(t * math.pi * 0.5)


def easeSinOut(t):
    return math.sin(t * math.pi * 0.5)


def easeSin(t):
    return 1 - math.cos(math.pi * t) / 2


def easeCircleIn(t, factor=0.5):
    return 1 - (1 - t * t) ** factor


def easeCircleOut(t, factor=0.5):
    return 1 - easeCircleIn(1 - t, factor)


def easeCircle(t, factorIn=0.5, factorOut=0.5):
    t *= 2
    if t <= 1:
        return (1 - (1 - t * t) ** factorIn) / 2
    else:
        return ((1 - (t - 2) * (t - 2)) ** factorOut + 1) / 2


def easeBackIn(t, factor=1.70158):
    return t * t * ((factor + 1) * t - factor)


def easeBackOut(t, factor=1.70158):
    return 1 - (1 - t) ** 2 * ((factor + 1) * (1 - t) - factor)


def easeBack(t, factorIn=1.70158, factorOut=1.70158):
    t *= 2
    if t < 1:
        return (t * t * ((factorIn + 1) * t - factorIn)) / 2
    else:
        return ((t - 2) ** 2 * ((factorOut + 1) * (t - 2) + factorOut) + 2) / 2


def easeBounceIn(t, bounces=None):
    return 1 - easeBounceOut(1 - t, bounces)


def easeBounceOut(t, bounces=None):
    if bounces is None:
        bounces = [4 / 11, 6 / 11, 8 / 11, 3 / 4, 9 / 11, 10 / 11, 15 / 16, 21 / 22, 63 / 64]

    bounces.insert(0, 1 / bounces[0] / bounces[0])
    if t < bounces[1]:
        return bounces[0] * t * t
    else:
        for i in range(3, len(bounces) - 2, 3):
            if t < bounces[i]:
                t -= bounces[i - 1]
                return bounces[0] * t * t + bounces[i + 1]

    t -= bounces[len(bounces) - 2]
    return bounces[0] * t * t + bounces[len(bounces) - 1]


def easeBounce(t, bouncesIn=None, bouncesOut=None):
    t *= 2
    if t <= 1:
        return (1 - easeBounceOut(1 - t, bouncesIn)) / 2
    else:
        return (easeBounceOut(t - 1, bouncesOut) + 1) / 2


def easeElasticIn(t, period=0.2, amplitude=1):
    period = period / math.tau

    a = max([amplitude, 1])
    s = math.asin(1 / (a)) * (period)

    return a * (2 ** (10 * (t - 1))) * math.sin((s - t) / period)


def easeElasticOut(t, period=0.2, amplitude=1):
    return 1 - easeElasticIn(1 - t, period, amplitude)


def easeElastic(t, periodIn=0.2, amplitudeIn=1, periodOut=0.2, amplitudeOut=1):
    t = t * 2 - 1

    if t < 0:
        p = periodIn / math.tau
        a = max([amplitudeIn, 1])
        s = math.asin(1 / a) * p

        return a * 2 ** (10 * t) * math.sin((s - t) / p)

    else:
        p = periodOut / math.tau
        a = max([amplitudeOut, 1])
        s = math.asin(1 / a) * p

        return 2 - a * 2 ** (-10 * t) * math.sin((s + t) / p) / 2


def easeExponentialIn(t, base=2):
    return base ** (10 * t - 10)


def easeExponentialOut(t, base=2):
    return 1 - (base ** (-10 * t))


def easeExponential(t, baseIn=2, baseOut=2):
    t *= 2
    if t <= 1:
        return (baseIn ** (10 * t - 10)) / 2
    else:
        return (2 - baseOut ** (10 - 10 * t)) / 2
