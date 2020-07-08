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

# Done to get rid of bug with Image PIL
if "tkinter" not in sys.modules:
    import tkinter as tk

__version__ = "6.10-dev"


class GraphicsError(Exception):
    """Generic error class for graphics module exceptions."""
    pass


class GraphicsWarning(Warning):
    pass


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

##########################################################################
# global variables and functions

_root = tk.Tk()
_root.withdraw()

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
            raise GraphicsError("\n\nRGB values must be integers!")
        if not (256 > r > -1 and 256 > g > -1 and 256 > b > -1):
            raise GraphicsError(
                "\n\nRGB values must be between 0 & 255 (included), right now {}, {}, {}".format(r, g, b))
        self.colour = "#%02x%02x%02x" % (r, g, b)


class ColourHex(Colour):
    def __init__(self, colour):
        if not isinstance(colour, str):
            raise GraphicsError("\n\nHex value must be a string in format: #rrggbb")
        if len(colour) != 7:
            raise GraphicsError("\n\nThe length of the hex colour string must be 7: '#rrggbb'")
        self.colour = colour


class ColourCMYK(Colour):
    def __init__(self, c, y, m, k):
        if not (isinstance(c, int) and isinstance(y, int) and isinstance(m, int) and isinstance(k, int)):
            raise GraphicsError("\n\nCMYK values must be integers!")
        if not (101 > c > -1 and 101 > y > -1 and 101 > m > -1 and 101 > k > -1):
            raise GraphicsError("\n\nCMYK values must be between 0 & 100 (included), right now {}, {}, {}, {}".
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
LIGHT_BLUE_GREY = ColourRGB(83, 95, 106)
LIGHTEST_BLUE_GREY = ColourRGB(173, 175, 177)

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
DARK_NAVY_BLUE = ColourRGB(38, 45, 56)
NAVY_BLUE = ColourRGB(45, 57, 68)
BLUE = ColourRGB(0, 153, 255)
CYAN = None

TURQOISE = ColourRGB(79, 227, 194)

# Purples & Pinks
DARK_PURPLE = None
PURPLE = None
LIGHT_PURPLE = None
PINK = None

globalStyle = "default"

STYLES = {"pycharm darcula": {"primary fill": DARK_GREY, "secondary fill": BLUE_GREY, "background": DARK_GREY,
                              "primary font_colour": None, "secondary font_colour": DARK_BLUE_GREY, "accent": LIGHT_BLUE_GREY,

                              "width": 1,
                              "fontColour": LIGHTER_GREY, "justify": "center", "font_face": "century gothic", "fontSize": 20,
                              "fontStyle": "normal"},

          "intellij": {"primary fill": DARK_GREY, "secondary fill": DARK_WHITE, "background": WHITE,
                       "primary font_colour": None, "secondary font_colour": LIGHTER_GREY, "accent": LIGHT_BLUE_GREY,

                       "width": 1,
                       "textColour": LIGHTER_GREY, "justify": "left", "font_face": ("century gothic", 20, "normal")},

          "default": {"primary fill": CHROME_YELLOW, "secondary fill": RED, "fill": CHROME_YELLOW, "background": WHITE,
                      "primary font_colour": BLACK, "secondary font_colour": GREY, "font_colour": BLACK,

                      "width": "2", "arrow": "none", "entry width": 0,
                      "textColour": BLACK, "text": "Lorem Ipsum", "justify": "center",
                      "font_face": "calibri", "fontSize": 5, "fontStyle": "normal", "fontColour": BLACK,
                      "selectColour": BLUE},
          }


# Add other colour definitions here!

############################################################################
# Graphics classes start here

def setStyle(style="default"):
    global globalStyle

    if style not in STYLES.keys():
        raise GraphicsError(f"The style specified ({style}) does not exist, must be one of {list(STYLES.keys())}")
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
            raise GraphicsError(f"\n\nThe window's title must be a string, not {title}")

        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nThe window's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's width must be greater than 0, not {width}")
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError(f"\n\nThe window's height must be a number (integer or float), not {height}")
        if not height > 0:
            raise GraphicsError(f"\n\nThe window's height must be greater than 0, not {height}")

        if not (isinstance(xPos, int) or isinstance(xPos, float)):
            raise GraphicsError(f"\n\nThe window x-position (xPos) must be an integer, not {xPos}")
        if not (isinstance(yPos, int) or isinstance(yPos, float)):
            raise GraphicsError(f"\n\nThe window y-position (yPos) must be an integer, not {yPos}")

        if not (isinstance(bkColour, Colour) or isinstance(bkColour, str) or bkColour is None):
            raise GraphicsError("The window's background Colour (bkColour) must be a Colour or string referencing a"
                                f"style colour, not {bkColour}")
        if icon is not None:
            if not isinstance(icon, str):
                raise GraphicsError("The window icon must be a string (path to .ico texture) or None, not {icon}")
            if not os.isfile(f"textures/{icon}"):
                raise GraphicsError(f"The icon path you have specified ({icon}) does not exist. "
                                    f"Check for spelling and make sure this is in the correct directory.")
            if not icon.endswith(".ico"):
                raise GraphicsError("The icon file must be a .ico type. "
                                    "You can use an online converter to convert your file")

        if not isinstance(autoflush, bool):
            raise GraphicsError(f"\n\nAuto-flush must be a boolean, not {autoflush}")

        if not isinstance(resizableWidth, bool):
            raise GraphicsError(f"\n\nresizableWidth must be a boolean, not {resizableWidth}")
        if not isinstance(resizableHeight, bool):
            raise GraphicsError(f"\n\nresizableHeight must be a boolean, not {resizableHeight}")
        if not isinstance(minWidth, int):
            raise GraphicsError(f"\n\nThe window's minimum width (minWidth) must be an integer, not {minWidth}")
        if not isinstance(minHeight, int):
            raise GraphicsError(f"\n\nThe window's minimum height (minHeight) must be an integer, not {minHeight}")

        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS:
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {CURSORS}, not {cursor}")

        if not isinstance(borderRelief, str):
            raise GraphicsError(f"\n\nThe border relief (borderRelief) must be a string, not {borderRelief}")
        if not borderRelief.lower() in RELIEF:
            raise GraphicsError(f"\n\nThe relief for the window border must be one of {RELIEF}, not {borderRelief}")
        if not isinstance(borderWidth, int):
            raise GraphicsError(f"\n\nThe window's border width must be an integer, not {borderWidth}")

        if style is None:
            style = globalStyle
        elif style not in STYLES.keys():
            raise GraphicsError(f"\n\nThe style you have specified ({style}) is not valid. "
                                f"Must be one of {list(STYLES.keys())}")

        if width < minWidth:
            warning = f"\n\nWindow width ({width}) is less than window's minimum width ({minWidth}). " \
                      f"Window minimum width has been set to {width}."
            minWidth = width
            warnings.warn(warning, GraphicsWarning)

        if height < minHeight:
            warning = f"\n\nWindow height ({height}) is less than window's minimum height ({minHeight}). " \
                      f"Window minimum height has been set to {height}."
            minHeight = height
            warnings.warn(warning, GraphicsWarning)

        master = tk.Toplevel(_root)
        master.protocol("WM_DELETE_WINDOW", self.close)

        if not isinstance(bkColour, Colour):
            if bkColour in STYLES[style].keys():
                self.bkColour = STYLES[style][bkColour]
            elif bkColour is None:
                if "background" in STYLES[style].keys():
                    self.bkColour = STYLES[style]["background"]
                else:
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
        self.borderRelief = borderRelief.lower()

        self.setBackground(self.bkColour)

        self.master.geometry('%dx%d+%d+%d' % (width, height, xPos, yPos))
        self.master.minsize(int(minWidth), int(minHeight))
        self.master.resizable(resizableWidth, resizableHeight)

        self.minWidth = minWidth
        self.minHeight = minHeight
        self.center = Point(width / 2, height / 2)

        if icon is not None:
            self.master.iconbitmap(f"textures/{icon}")

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
            raise GraphicsError("\n\nwindow is closed")

    def setMouseHandler(self, func):
        self._mouseCallback = func

    # Returns the position of the window on the display of the computer
    def getPosition(self):
        return Point(self.master.winfo_rootx(), self.master.winfo_rooty())

    # Sets the background colour of the window
    def setBackground(self, colour):
        """Set background Colour of the window"""

        if not isinstance(colour, Colour):
            if colour in STYLES[self.style].keys():
                self.bkColour = STYLES[self.style]["background"]
            elif colour is None:
                self.bkColour = STYLES["default"]["background"]
        else:
            self.bkColour = colour

        self.__checkOpen()
        self.master.config(bg=self.bkColour)
        self.__autoflush()

    def setBorderWidth(self, width):

        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nThe window's border's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's border's width must be greater than 0, not {width}")

        self.borderWidth = width
        self.__checkOpen()
        self.master.config(bd=width)
        self.__autoflush()

    def setBorderRelief(self, relief):

        if not isinstance(relief, str):
            raise GraphicsError(f"\n\nThe border relief (relief) must be a string, not {relief}")
        if not relief.lower() in RELIEF:
            raise GraphicsError(f"\n\nThe relief for the window border must be one of {RELIEF}, not {relief}")

        self.borderRelief = relief
        self.__checkOpen()
        self.master.config(relief=relief)
        self.__autoflush()

    def setCursor(self, cursor):

        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS:
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {CURSORS}, not {cursor}")

        self.__checkOpen()
        self.cursor = cursor
        self.config(cursor=cursor)
        self.__autoflush()

    def setResizable(self, resizableWidth=True, resizableHeight=True):
        if not isinstance(resizableWidth, bool):
            raise GraphicsError(f"\n\nresizableWidth must be a boolean, not {resizableWidth}")
        if not isinstance(resizableHeight, bool):
            raise GraphicsError(f"\n\nresizableHeight must be a boolean, not {resizableHeight}")

        self.master.resizable(resizableWidth, resizableHeight)

    def setIcon(self, icon):

        if not isinstance(icon, str):
            raise GraphicsError("The window icon must be a string (path to .ico texture) or None, not {icon}")
        if not os.isfile(f"textures/{icon}"):
            raise GraphicsError(f"The icon path you have specified ({icon}) does not exist. "
                                f"Check for spelling and make sure this is in the correct directory.")
        if not icon.endswith(".ico"):
            raise GraphicsError("The icon file must be a .ico type. "
                                "You can use an online converter to convert your file")

        self.__checkOpen()
        self.master.iconbitmap(icon)
        self.__autoflush()

    def setTitle(self, title):
        if not isinstance(title, str):
            raise GraphicsError(f"\n\nThe window's title must be a string, not {title}")

        self.title = title
        self.__checkOpen()
        self.master.title(title)
        self.__autoflush()

    def setWidth(self, width):
        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nThe window's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's width must be greater than 0, not {width}")

        if width < self.minWidth:
            self.minWidth = width
            warning = f"\n\nWindow width ({width}) is less than window's minimum width ({self.minWidth}). " \
                      f"Window minimum width has been set to {width}"
            warnings.warn(warning, GraphicsWarning)

            self.master.minsize(self.minWidth, self.minHeight)

        self.width = width
        self.__checkOpen()
        self.master.config(width=self.width)
        self.__autoflush()

    def setHeight(self, height):
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError(f"\n\nThe window's height must be a number (integer or float), not {height}")
        if not height > 0:
            raise GraphicsError(f"\n\nThe window's height must be greater than 0, not {height}")

        if height < self.minHeight:
            self.minHeight = height
            warning = "\n\nWindow height (height={}) is less than window's minimum height (minHeight={}). " \
                      "Window minimum height has been set to {}".format(
                height, self.minHeight, height)
            warnings.warn(warning, GraphicsWarning)

            self.master.minsize(self.minWidth, self.minHeight)

        self.height = height
        self.__checkOpen()
        self.master.config(height=height)
        self.__autoflush()

    def setMinHeight(self, height):
        if not isinstance(height, int):
            raise GraphicsError(f"\n\nThe window's minimum height (minHeight) must be an integer, not {height}")

        self.minHeight = height
        if height > self.height:
            warning = "\n\nMinimum height (minHeight={}) is greater than the window's current height (height={})." + \
                      "Window's height has been set to {})".format(height, self.height, height)
            warnings.warn(warning, GraphicsWarning)
            self.setHeight(height)

        self.master.minsize(self.minWidth, self.minHeight)

    def setMinWidth(self, width):
        if not isinstance(width, int):
            raise GraphicsError(f"\n\nThe window's minimum width (minWidth) must be an integer, not {width}")

        self.minWidth = width
        if width > self.width:
            warning = "\n\nMinimum width (minWidth={}) is greater than the window's current width (width={})." + \
                      "Window's width has been set to {})".format(width, self.width, width)
            warnings.warn(warning, GraphicsWarning)
            self.setWidth(width)

        self.master.minsize(self.minWidth, self.minHeight)

    def setSize(self, width, height):
        self.setHeight(height)
        self.setWidth(width)

    def setMinSize(self, minWidth, minHeight):
        self.setMinHeight(minHeight)
        self.setMinWidth(minWidth)

    def setCoords(self, x1, y1, x2, y2):
        """Set coordinates of window to run from (x1,y1) in the
        upper-left corner to (x2,y2) in the lower-right corner."""
        if not ((isinstance(x1, int) or isinstance(x1, float)) and (isinstance(y1, int) or isinstance(y1, float)) and
                (isinstance(x2, int) or isinstance(x2, float)) and (isinstance(y2, int) or isinstance(y2, float))):
            raise GraphicsError("\n\nCoordinate Arguments must be numbers (integers or floats)")
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
            self.updateWin(_internalUpdating=True)

    def plot(self, x, y, colour=BLACK):
        """Set pixel (x,y) to the given Colour"""

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("\n\nx & y position must be numbers (integers, or floats)")
        if not isinstance(colour, Colour):
            if colour in STYLES[self.style].keys():
                colour = STYLES[self.style]["background"]
            elif colour is None:
                colour = STYLES["default"]["background"]

        self.__checkOpen()
        xs, ys = self.toScreen(x, y)
        self.create_line(xs, ys, xs + 1, ys, fill=colour)
        self.__autoflush()

    def flush(self):
        """Update drawing to the window"""
        self.__checkOpen()
        self.update_idletasks()

    def updateWin(self, _internalUpdating=False):
        if self.autoflush and not _internalUpdating:
            warnings.warn("Updating the Graphics Object while autoflush is True might lead to issues, either let the "
                          "window update automatically by setting autoflush to True or update it manually",
                          GraphicsWarning)
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
            raise GraphicsError("\n\ncheckKey in closed window")

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
        """Set font_colour Colour to Colour"""
        self._reconfig("font_colour", colour)
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
        if self.drawn:
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
            raise GraphicsError("\n\nframes parameter must be either 'Time' or 'Frames' not '{}'".format(frames))

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
            raise GraphicsError(f"\n\nThe config you have specified ({option}) is not valid for {self}")
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

                    obj.resizeFactor(1 + obj.resizingFactor * ((t - obj.resizingStart) / obj.resizingTime),
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
            if obj.graphwin == graphwin and obj.autoflush:
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
                                        if mousePos.x < obj.resizingAnchor.x + obj.resizingInitialSize[0] / 2 \
                                                - obj.minWidth:
                                            w = obj.resizingAnchor.x - mousePos.x + obj.resizingInitialSize[0] / 2
                                            obj.resizingBounds[dir2].moveToX(mousePos.x)
                                        else:
                                            w = obj.minWidth
                                            obj.resizingBounds[dir2].moveToX(obj.p1.x)

                                    elif bound == "right":
                                        dir1, dir2 = dir2, dir1
                                        if mousePos.x > obj.resizingAnchor.x - obj.resizingInitialSize[0] / 2 \
                                                + obj.minWidth:
                                            w = mousePos.x - obj.resizingAnchor.x + obj.resizingInitialSize[0] / 2
                                            obj.resizingBounds[dir2].moveToX(mousePos.x)
                                        else:
                                            w = obj.minWidth
                                            obj.resizingBounds[dir2].moveToX(obj.p2.x)

                                    obj.setObjectWidth(w, dir1)

                                    obj.resizingBounds["top"].setObjectWidth(w + obj.boundsThickness, dir1)
                                    obj.resizingBounds["bottom"].setObjectWidth(w + obj.boundsThickness, dir1)

                                else:
                                    dir1 = "bottom"
                                    dir2 = "top"
                                    if bound == "top":
                                        if mousePos.y < obj.resizingAnchor.y + obj.resizingInitialSize[1] / 2 \
                                                - obj.minHeight:
                                            h = obj.resizingAnchor.y - mousePos.y + obj.resizingInitialSize[1] / 2
                                            obj.resizingBounds[dir2].moveToY(mousePos.y)
                                        else:
                                            h = obj.minHeight
                                            obj.resizingBounds[dir2].moveToY(obj.p1.y)
                                    else:
                                        dir1, dir2 = dir2, dir1
                                        if mousePos.y > obj.resizingAnchor.y - obj.resizingInitialSize[1] / 2 \
                                                + obj.minHeight:
                                            h = mousePos.y - obj.resizingAnchor.y + obj.resizingInitialSize[1] / 2
                                            obj.resizingBounds[dir2].moveToY(mousePos.y)
                                        else:
                                            h = obj.minHeight
                                            obj.resizingBounds[dir2].moveToY(obj.p2.y)

                                    obj.setObjectHeight(h, dir1)

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
            raise GraphicsError("\n\nx (x={}) & y (y={}) positions must be integers".format(x, y))

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
            raise GraphicsError("\n\np2 argument for distance calculation must be a Point class")
        return math.sqrt((p2.x - self.x) ** 2 + (p2.y - self.y) ** 2)

    def distanceX(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError("\n\np2 argument for distance calculation must be a Point class")
        return p2.x - self.x

    def distanceY(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError("\n\np2 argument for distance calculation must be a Point class")
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

    def moveY(self, dy):
        self.y += dy
        return self

    def moveX(self, dx):
        self.x += dx
        return self

    def move(self, dx, dy):
        self.y += dy
        self.x += dx
        return self

    def moveTo(self, x, y):
        self.x = x
        self.y = y
        return self

    def add(self, dx, dy):
        return self.clone().move(dx, dy)

    def set(self, x, y):
        return self.clone().moveTo(x, y)

    def moveToX(self, x):
        self.x = x
        return self

    def moveToY(self, y):
        self.y = y
        return self

    def getAnchor(self):
        return self

    def addY(self, dy):
        return self.clone().moveY(dy)

    def addX(self, dx):
        return self.clone().moveX(dx)

    def setX(self, x):
        return self.clone().moveToX(x)

    def setY(self, y):
        return self.clone().moveToY(y)


class _BBox(GraphicsObject):
    # Internal base class for objects represented by bounding box
    # (opposite corners) Line segment is a degenerate case.

    resizingObjects = []

    def __init__(self, p1, p2, bounds=None, style=None, fill=None,
                 outline=None, width=None, options=("fill", "font_colour", "width"), cursor="arrow", window=None):

        if not isinstance(bounds, _BBox) and bounds is not None:
            raise GraphicsError("\n\nBounds argument must be another Graphics Object (Rectangle, " +
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

        if isinstance(fill, Colour):
            self.fill = fill
        elif fill in STYLES[self.style].keys():
            self.fill = STYLES[self.style][fill]
        else:
            if "fill" in STYLES[self.style].keys():
                self.fill = STYLES[self.style]["fill"]
            else:
                self.fill = STYLES["default"]["fill"]
        self.setFill(self.fill)

        if isinstance(outline, Colour):
            self.outline = outline
        elif outline in STYLES[self.style].keys():
            self.outline = STYLES[self.style][outline]
        else:
            if "font_colour" in STYLES[self.style].keys():
                self.outline = STYLES[self.style]["font_colour"]
            else:
                self.outline = STYLES["default"]["font_colour"]
        self.setOutline(self.outline)

        if isinstance(width, int):
            self.outlineWidth = width
        elif width in STYLES[self.style].keys():
            self.outlineWidth = STYLES[self.style][width]
        else:
            if "width" in STYLES[self.style].keys():
                self.outlineWidth = STYLES[self.style]["width"]
            else:
                self.outlineWidth = STYLES["default"]["width"]
        self.setWidth(self.outlineWidth)

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
            raise GraphicsError("\n\nThe center argument for resizing the object (setObjectWidth) needs to be one of {}"
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
            raise GraphicsError(
                "\n\nThe center argument for resizing the object (setObjectHeight) needs to be one of {}"
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

    def setResizable(self, top=False, left=False, bottom=False, right=False, minWidth=40, minHeight=40, boundsWidth=10,
                     showBounds=False):

        if minWidth < 1 or minHeight < 1:
            raise GraphicsError(f"\n\nMinimum height and width of resizable object must be greater than or equal to 1. "
                                f"Right now, minWidth={minWidth} & minHeight={minHeight}")

        self.minWidth = minWidth
        self.minHeight = minHeight

        self._setResizable([top, bottom, left, right], thickness=boundsWidth, showBounds=showBounds)
        _BBox.resizingObjects.append(self)
        self.boundsThickness = boundsWidth

        return self


class Rectangle(_BBox):

    def __init__(self, p1, p2, bounds=None, style=None, fill=None, outline=None, width=None,
                 cursor="arrow", isRounded=False, cornerSharpness=5, window=None):
        _BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, width=width,
                       style=style, cursor=cursor, window=window)

        self.equation = VectorEquation(f"abs((x - {self.anchor.x})/{self.width / 2} + (y - {self.anchor.y})/"
                                       f"{self.height / 2}) + abs((x - {self.anchor.x})/{self.width / 2} - "
                                       f"(y - {self.anchor.y})/{self.height / 2}) < 2")

        self.points = [self.p1.x, self.p1.y, self.p1.x, self.p2.y, self.p2.x, self.p2.y, self.p2.x, self.p1.y]
        self.isRounded = isRounded
        self.sharpness = cornerSharpness  # Usually values between 2 & 10 work well.

    def __repr__(self):
        return "Rectangle({}, {})".format(str(self.p1), str(self.p2))

    def _setResizable(self, resizables, thickness=10, showBounds=False):
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
            if showBounds:
                obj.draw(self.graphwin)

    def roundCornersRect(self, canvas, ratio=0.1, npts=12):

        # Code courtesy of Reblochon Masque,
        # https://stackoverflow.com/questions/62715279/creating-rounded-edges-for-a-polygon-in-python

        x0, x1 = self.p1.x, self.p2.x
        y0, y1 = self.p1.y, self.p1.y

        r = min(x1 - x0, y1 - y0) * ratio

        items = []

        tld = x0, y0 + r
        tlr = x0 + r, y0
        item = canvas.create_arc(x0, y0, x0 + 2 * r, y0 + 2 * r, start=90, extent=90, fill=self.config["fill"],
                                 outline=self.config["fill"], style=tk.ARC)
        items.append(item)

        trl = x1 - r, y0
        trd = x1, y0 + r
        item = canvas.create_line(*tlr, *trl, fill=self.config["fill"])
        items.append(item)
        item = canvas.create_arc(x1 - 2 * r, y0, x1, y0 + 2 * r, start=0, extent=90, fill=self.config["fill"],
                                 outline=self.config["fill"], style=tk.ARC)
        items.append(item)

        bru = x1, y1 - r
        brl = x1 - r, y1
        item = canvas.create_line(*trd, *bru, fill=self.config["fill"])
        items.append(item)
        item = canvas.create_arc(x1 - 2 * r, y1 - 2 * r, x1, y1, start=270, extent=90, fill=self.config["fill"],
                                 outline=self.config["fill"], style=tk.ARC)
        items.append(item)

        blr = x0 + r, y1
        blu = x0, y1 - r
        item = canvas.create_line(*brl, *blr, fill=self.config["fill"])
        items.append(item)
        item = canvas.create_arc(x0, y1 - 2 * r, x0 + 2 * r, y1, start=180, extent=90, fill=self.config["fill"],
                                 outline=self.config["font_colour"], style=tk.ARC)
        items.append(item)
        item = canvas.create_line(*blu, *tld, fill=self.config["fill"])
        items.append(item)

        for item_ in items:
            for _item in items:
                canvas.addtag_withtag(item_, _item)

        return items

    def _draw(self, canvas, options):
        points = self.points.copy()
        for point in range(len(self.points[::2])):
            points[point * 2], points[point * 2 + 1] = canvas.toScreen(points[point * 2], points[point * 2 + 1])

        # Code modified from Francisco Gomes, https://stackoverflow.com/users/9139005/francisco-gomes

        # The sharpness here is just how close the sub-points
        # are going to be to the vertex. The more the sharpness,
        # the more the sub-points will be closer to the vertex.
        # (This is not normalized)

        x = points[::2]
        y = points[1::2]

        # Rounding code from Francisco Gomes,
        # https://stackoverflow.com/questions/44099594/how-to-make-a-tkinter-canvas-rectangle-with-rounded-corners
        if self.isRounded:
            if self.sharpness < 2:
                self.sharpness = 2

            ratioMultiplier = self.sharpness - 1
            ratioDividend = self.sharpness

            # Array to store the points
            points = []

            # Iterate over the x points
            for i in range(len(x)):
                # Set vertex
                points.append(x[i])
                points.append(y[i])

                # If it's not the last point
                if i != (len(x) - 1):
                    # Insert submultiples points. The higher the sharpness, the more these points will be
                    # closer to the vertex.
                    points.append((ratioMultiplier * x[i] + x[i + 1]) / ratioDividend)
                    points.append((ratioMultiplier * y[i] + y[i + 1]) / ratioDividend)
                    points.append((ratioMultiplier * x[i + 1] + x[i]) / ratioDividend)
                    points.append((ratioMultiplier * y[i + 1] + y[i]) / ratioDividend)
                else:
                    # Insert submultiples points.
                    points.append((ratioMultiplier * x[i] + x[0]) / ratioDividend)
                    points.append((ratioMultiplier * y[i] + y[0]) / ratioDividend)
                    points.append((ratioMultiplier * x[0] + x[i]) / ratioDividend)
                    points.append((ratioMultiplier * y[0] + y[i]) / ratioDividend)
                    # Close the polygon
                    points.append(x[0])
                    points.append(y[0])

        for obj in self.resizingBounds.values():
            obj.graphwin = self.graphwin

        # return canvas.create_rectangle(self.p1.x, self.p1.y, self.p2.x, self.p2.y, options)

        # This is done due to an internal bug in Tkinter where it does not set the width of the polygon..

        if options["width"] == 0:
            options["font_colour"] = options["fill"]

        return canvas.create_polygon(points, options, smooth=self.isRounded)

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
        self.points = [self.p1.x, self.p1.y, self.p1.x, self.p2.y, self.p2.x, self.p2.y, self.p2.x, self.p1.y]


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
        self.equation = VectorEquation("(x-{})**2 + (y-{})**2 < {}**2".format(self.anchor.x, self.anchor.y,
                                                                              self.radius))


class Arc(GraphicsObject):
    def __init__(self, p1, angle, radius, radius2=None, style=None, fill=None, outline=None, width=None, cursor="arrow",
                 window=None):
        self.angle = angle

        GraphicsObject.__init__(self, style=style, options=["fill", "font_colour", "width"], cursor=cursor, window=window)

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
            raise GraphicsError("\n\nArrow option for line must be one of ['first', 'last', 'both', 'none']")
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

    def __init__(self, points, style=None, fill=None, outline=None, width=None, isRounded=False, roundSharpness=5,
                 window=None):

        # if points passed as a list, extract it
        if len(points) == 1 and isinstance(points[0], list):
            points = points[0]
            points = points[0]
        print(points)
        self.points = points
        self.isRounded = isRounded

        self.sharpness = roundSharpness

        GraphicsObject.__init__(self, style=style, options=["font_colour", "width", "fill"], window=window)

    def __repr__(self):
        return "Polygon" + str(tuple(p for p in self.points))

    def clone(self):
        other = Polygon(*self.points)
        other.config = self.config.copy()
        return other

    def getPoints(self):
        return list(map(Point.clone, self.points))

    def isClicked(self, mousePos):
        return False

    def _move(self, dx, dy):
        for p in self.points:
            p.move(dx, dy)

    def getAnchor(self):
        x = 0
        y = 0

        print(self.points)
        for point in self.points:
            x += point.x
            y += point.y

        x /= len(self.points)
        y /= len(self.points)

        return Point(x, y)

    def _draw(self, canvas, options):
        points = []
        for p in self.points:
            x, y = canvas.toScreen(p.x, p.y)
            points.append(x)
            points.append(y)

        # Code modified from Francisco Gomes, https://stackoverflow.com/users/9139005/francisco-gomes

        # The sharpness here is just how close the sub-points
        # are going to be to the vertex. The more the sharpness,
        # the more the sub-points will be closer to the vertex.
        # (This is not normalized)
        x = points[::2]
        y = points[1::2]

        # Rounding code from Francisco Gomes,
        # https://stackoverflow.com/questions/44099594/how-to-make-a-tkinter-canvas-rectangle-with-rounded-corners
        if self.isRounded:
            if self.sharpness < 2:
                self.sharpness = 2

            ratioMultiplier = self.sharpness - 1
            ratioDividend = self.sharpness

            # Array to store the points
            points = []

            # Iterate over the x points
            for i in range(len(x)):
                # Set vertex
                points.append(x[i])
                points.append(y[i])

                # If it's not the last point
                if i != (len(x) - 1):
                    # Insert submultiples points. The higher the sharpness, the more these points will be
                    # closer to the vertex.
                    points.append((ratioMultiplier * x[i] + x[i + 1]) / ratioDividend)
                    points.append((ratioMultiplier * y[i] + y[i + 1]) / ratioDividend)
                    points.append((ratioMultiplier * x[i + 1] + x[i]) / ratioDividend)
                    points.append((ratioMultiplier * y[i + 1] + y[i]) / ratioDividend)
                else:
                    # Insert submultiples points.
                    points.append((ratioMultiplier * x[i] + x[0]) / ratioDividend)
                    points.append((ratioMultiplier * y[i] + y[0]) / ratioDividend)
                    points.append((ratioMultiplier * x[0] + x[i]) / ratioDividend)
                    points.append((ratioMultiplier * y[0] + y[i]) / ratioDividend)
                    # Close the polygon
                    points.append(x[0])
                    points.append(y[0])

        if options["width"] == 0:
            options["font_colour"] = options["fill"]

        return canvas.create_polygon(points, options, smooth=self.isRounded)


class Text(GraphicsObject):

    def __init__(self, p, text, style=None, fontSize=None, font=None, fontStyle=None, outline=None, justify="center",
                 window=None):

        self.anchor = p.clone()
        GraphicsObject.__init__(self, style=style, options=["justify", "fill", "text", "font_face"],
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
            if "font_colour" in STYLES[self.style].keys():
                self.outline = STYLES[self.style]["font_colour"]
            else:
                self.outline = STYLES["default"]["font_colour"]

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
            if "font_face" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font_face"]
            else:
                self.font = STYLES["default"]["font_face"]

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
        f, s, b = self.config['font_face']
        self._reconfig("font_face", (face, s, b))

    def setJustify(self, justify):
        self._reconfig("justify", justify)

    def setSize(self, size, updateInit=True):
        f, s, b = self.font, size, self.fontStyle
        self.fontSize = size

        if updateInit:
            self.initialFontSize = size
        self._reconfig("font_face", (f, size, b))

    def setStyle(self, style):
        if style in ['bold', 'normal', 'italic', 'bold italic']:
            f, s, b = self.config['font_face']
            self._reconfig("font_face", (f, s, style))
        else:
            raise GraphicsError("Text stlye must be one of ['bold', 'normal', 'italic', 'bold italic']")

    def setTextColour(self, Colour):
        self.setFill(Colour)


class Entry(GraphicsObject):

    def __init__(self, p, textWidth=10, style=None, fill=None, fontColour=None, entry=None, font=None, fontSize=None,
                 outline=None, fontStyle=None, width=None, borderType="flat", password=False, active="NORMAL",
                 window=None, justify="center", cursor="xterm", selectColour=None, promptText=""):

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
                self.width = STYLES[self.style]["entry width"]
            else:
                self.width = STYLES["default"]["entry width"]

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
            if "font_face" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font_face"]
            else:
                self.font = STYLES["default"]["font_face"]

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
            self.textType = "*"
        else:
            self.textType = ""
        self.active = "normal"
        self.cursor = cursor
        self.promptText = promptText

        self.initialSize = self.fontSize
        self.edited = False

        GraphicsObject.__init__(self, style=style, options=["fill", "font_colour"], window=window)

    def __repr__(self):
        return "Entry({}, {})".format(self.anchor, self.textWidth)

    def _onEdit(self, e):
        if not self.edited:
            self.edited = True
            self.setText(self.getText().replace(self.promptText, "", 1))

            if self.textType == "*":
                self.entry.config(show="*")

    def _onEnter(self, e):
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
            raise GraphicsError("\n\nState must be either normal, disabled or readonly")
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
                              bd=self.width, font=self.fontConfig, insertbackground=self.fontColour, show=self.textType,
                              state=self.active, justify=self.justify, cursor="xterm", exportselection=0,
                              selectbackground=self.selectColour)

        if not self.edited:
            self.entry.insert(0, self.promptText)
            self.entry.config(show="")
        self.entry.pack()
        self.entry.focus_set()

        self.entry.bind("<Return>", self._onEnter)
        self.entry.bind("<Key>", self._onEdit)

        return canvas.create_window(x, y, window=frm)

    def getText(self):
        if self.drawn and self.graphwin.isOpen():
            return self.entry.get()
        else:
            raise GraphicsError(f"\n\nEntry can only return text when it is drawn and the window is open. Window Open"
                                f"? {self.graphwin.isOpen()}, Drawn? {self.drawn}")

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
        self.entry.delete(0, tk.END)
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
            raise GraphicsError("\n\nBorder type must be one of "
                                "['flat', 'groove', 'raised', 'ridge', 'solid', 'sunken']")
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
            raise GraphicsError(f"\n\nImage align must be one of center, bottom, top, left, or right, not {align}")

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
            p.addY(self.initialHeight / -2)
        elif self.align == "top":
            p.addY(self.initialHeight / 2)
        elif self.align == "left":
            p.addX(self.initialWidth / 2)
        elif self.align == "right":
            p.addX(self.initialWidth / -2)

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

    def __init__(self, trueGraphic, falseGraphic, trueGraphicHover=None, falseGraphicHover=None, autoflush=True,
                 trueGraphicClicked=None, falseGraphicClicked=None, graphicDisabled=None, state=True, window=None):

        self.state = state
        self.autoflush = autoflush

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

    def getState(self):
        return self.state

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
                raise GraphicsError("\n\nThe states must all be Graphic Objects")

        self.graphwin = None
        self.graphic = states[state]

        GraphicsObject.__init__(self, [], window=window)

    def changeGraphic(self, element, value):
        self.states[element] = value

    def append(self, state):
        self.states.append(state)

    def remove(self, state):
        if state not in self.states:
            raise GraphicsError("\n\nThe state to remove is not an existing state of this cycle button")

        self.states.remove(state)

    def pop(self, index):
        if index < 0:
            raise GraphicsError("\n\nThe given index is a negative number")

        elif index > len(self.states) - 1:
            raise GraphicsError("\n\nThe specified index cannot be removed as it does not exist")

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
            raise GraphicsError(
                f"\n\nSlide Bar value must between min/max values: {minimum} < value ({value}) < {maximum}")

        self.anchor = p.clone()

        self.maximum = maximum
        self.minimum = minimum

        if self.minimum > self.maximum:
            self.minimum, self.maximum = self.maximum, self.minimum
        elif self.minimum == self.maximum:
            raise GraphicsError("\n\nMinimum and Maximum value cannot be the same")

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
                f"\n\nValue to set the Slider Bar must be within {self.minimum} and {self.maximum} not {value}")
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


# References for this: https://www.youtube.com/watch?v=qhQrRCJ-mVg
def BezierCurve(t, controlPoints):
    global bezierPoints

    sumX, sumY = 0, 0

    if len(bezierPoints) == 0:
        bezierPoints = [[] for _ in range(len(controlPoints))]

    for i in range(0, len(controlPoints)):
        sumY += BernsteinPolynomial(i, len(controlPoints) - 1, t) * controlPoints[i].y
        sumX += BernsteinPolynomial(i, len(controlPoints) - 1, t) * controlPoints[i].x
        bezierPoints[i].append((BernsteinPolynomial(i, len(controlPoints) - 1, t)))

    return Point(sumX, sumY)


def RationalBezierCurve(t, weights, controlPoints):
    global bezierPoints

    sumXNumerator, sumYNumerator = 0, 0
    sumX, sumY = 0, 0

    if len(bezierPoints) == 0:
        bezierPoints = [[] for _ in range(len(controlPoints))]

    for i in range(0, len(controlPoints)):
        sumXNumerator += (BernsteinPolynomial(i, len(controlPoints) - 1, t) * controlPoints[i].x * weights[i])
        sumX += BernsteinPolynomial(i, len(controlPoints) - 1, t) * weights[i]

        sumYNumerator += (BernsteinPolynomial(i, len(controlPoints) - 1, t) * controlPoints[i].y * weights[i])
        sumY += BernsteinPolynomial(i, len(controlPoints) - 1, t) * weights[i]

        bezierPoints[i].append((BernsteinPolynomial(i, len(controlPoints) - 1, t)))

    return Point(sumXNumerator / sumX, sumYNumerator / sumY)


def BernsteinPolynomial(i, n, t):
    return Combination(n, i) * (t ** i) * ((1 - t) ** (n - i))


def Combination(n, k):
    return math.factorial(n) / (math.factorial(k) * math.factorial(n - k))


def UniformBSpline(t, controlPoints, open=False):
    global splinePoints

    sumX, sumY = 0, 0
    degree = 2
    knotVector = [x for x in range(len(controlPoints) + 2 + degree)]

    if len(splinePoints) == 0:
        splinePoints = [[] for _ in range(len(controlPoints))]

    if open:
        knotVector = [x for x in range(len(controlPoints) - degree + 1)]
        for _ in range(degree):
            knotVector.insert(0, knotVector[0])
            knotVector.insert(-1, knotVector[-1])

    for i in range(len(controlPoints)):
        sumX += CoxDeBoorRecursion(i, degree, t, knotVector) * controlPoints[i].x
        sumY += CoxDeBoorRecursion(i, degree, t, knotVector) * controlPoints[i].y

        splinePoints[i].append(CoxDeBoorRecursion(i, degree, t, knotVector))

    return Point(sumX, sumY)


def CoxDeBoorRecursion(i, j, t, knotVector):
    if j == 0:
        return 1 if knotVector[i] <= t < knotVector[i + 1] else 0

    d1 = (knotVector[i + j] - knotVector[i])
    a = ((t - knotVector[i]) / d1 * CoxDeBoorRecursion(i, j - 1, t, knotVector)) if d1 > 0 else 0

    d2 = (knotVector[i + j + 1] - knotVector[i + 1])
    b = (((knotVector[i + j + 1] - t) / d2) * CoxDeBoorRecursion(i + 1, j - 1, t, knotVector)) if d2 > 0 else 0
    return a + b
