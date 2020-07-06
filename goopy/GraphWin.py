from tkinter import Canvas as tkCanvas
from tkinter import Toplevel as tkToplevel
import keyboard

from PIL import ImageGrab

import warnings
import time
import os

from goopy.styles import *
from goopy.util import GraphicsError, GraphicsWarning
from goopy.constants import *
from goopy.constants import _root

from goopy.objects.GraphicsObject import GraphicsObject
from goopy.Point import Point
from goopy._internal_classes import Transform

class GraphWin(tkCanvas):
    """A GraphWin is a toplevel window for displaying graphics."""
    instances = []  # a list of all instances of this class

    def __init__(self, title="Graphics Window", width=800, height=600, x_pos=70, y_pos=80, style=None, bk_colour=None,
                 icon=None, autoflush=True, resizable_width=False, min_width=300, resizable_height=False,
                 min_height=200, cursor="arrow", border_relief="flat", border_width=0):

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

        if not (isinstance(x_pos, int) or isinstance(x_pos, float)):
            raise GraphicsError(f"\n\nThe window x-position (x_pos) must be an integer, not {x_pos}")
        if not (isinstance(y_pos, int) or isinstance(y_pos, float)):
            raise GraphicsError(f"\n\nThe window y-position (y_pos) must be an integer, not {y_pos}")

        if not (isinstance(bk_colour, Colour) or isinstance(bk_colour, str) or bk_colour is None):
            raise GraphicsError("The window's background colour (bk_colour) must be a colour or string referencing a"
                                f"style colour, not {bk_colour}")
        if icon is not None:
            if not isinstance(icon, str):
                raise GraphicsError(f"The window icon must be a string (path to .ico texture) or None, not {icon}")
            if not os.path.isfile(f"textures/{icon}"):
                raise GraphicsError(f"The icon path you have specified ({icon}) does not exist. "
                                    f"Check for spelling and make sure this is in the correct directory.")
            if not icon.endswith(".ico"):
                raise GraphicsError("The icon file must be a .ico type. "
                                    "You can use an online converter to convert your file")

        if not isinstance(autoflush, bool):
            raise GraphicsError(f"\n\nAuto-flush must be a boolean, not {autoflush}")

        if not isinstance(resizable_width, bool):
            raise GraphicsError(f"\n\nresizable_width must be a boolean, not {resizable_width}")
        if not isinstance(resizable_height, bool):
            raise GraphicsError(f"\n\nresizable_height must be a boolean, not {resizable_height}")
        if not isinstance(min_width, int):
            raise GraphicsError(f"\n\nThe window's minimum width (min_width) must be an integer, not {min_width}")
        if not isinstance(min_height, int):
            raise GraphicsError(f"\n\nThe window's minimum height (min_height) must be an integer, not {min_height}")

        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS:
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {CURSORS}, not {cursor}")

        if not isinstance(border_relief, str):
            raise GraphicsError(f"\n\nThe border relief (border_relief) must be a string, not {border_relief}")
        if not border_relief.lower() in RELIEF:
            raise GraphicsError(f"\n\nThe relief for the window border must be one of {RELIEF}, not {border_relief}")
        if not isinstance(border_width, int):
            raise GraphicsError(f"\n\nThe window's border width must be an integer, not {border_width}")

        if style is None:
            style = global_style
        elif style not in STYLES.keys():
            raise GraphicsError(f"\n\nThe style you have specified ({style}) is not valid. "
                                f"Must be one of {list(STYLES.keys())}")

        if width < min_width:
            warning = f"\n\nWindow width ({width}) is less than window's minimum width ({min_width}). " \
                      f"Window minimum width has been set to {width}."
            min_width = width
            warnings.warn(warning, GraphicsWarning)

        if height < min_height:
            warning = f"\n\nWindow height ({height}) is less than window's minimum height ({min_height}). " \
                      f"Window minimum height has been set to {height}."
            min_height = height
            warnings.warn(warning, GraphicsWarning)

        master = tkToplevel(_root)
        master.protocol("WM_DELETE_WINDOW", self.close)

        if not isinstance(bk_colour, Colour):
            if bk_colour in STYLES[style].keys():
                self.bk_colour = STYLES[style][bk_colour]
            elif bk_colour is None:
                if "background" in STYLES[style].keys():
                    self.bk_colour = STYLES[style]["background"]
                else:
                    self.bk_colour = STYLES["default"]["background"]
        else:
            self.bk_colour = bk_colour

        tkCanvas.__init__(self, master, width=_root.winfo_screenwidth(), height=_root.winfo_screenheight(),
                          highlightthickness=0, bd=border_width,
                          bg=self.bk_colour, cursor=cursor.lower(), relief=border_relief)

        self.master.config(width=width, height=height)

        self.trans = None
        self.closed = False
        self.autoflush = autoflush

        self.master.title(title)
        self.title = title
        self.cursor = cursor.lower()

        self.border_width = border_width
        self.border_relief = border_relief.lower()

        self.set_background(self.bk_colour)

        self.master.geometry('%dx%d+%d+%d' % (width, height, x_pos, y_pos))
        self.master.minsize(int(min_width), int(min_height))

        self.master.resizable(resizable_width, resizable_height)
        self.is_resizable = [resizable_width, resizable_height]

        self.min_width = min_width
        self.min_height = min_height
        self.center = Point(width / 2, height / 2)

        if icon is not None:
            self.master.iconbitmap(f"textures/{icon}")

        self.pack()

        self.imgs = 0

        self.items = []

        self.mouse_left_click = None
        self.mouse_middle_click = None
        self.mouse_right_click = None

        self.mouse_left_press = None
        self.mouse_right_press = None
        self.mouse_middle_press = None

        self.total_left_mouse_clicks = 0
        self.total_middle_mouse_clicks = 0
        self.total_right_mouse_clicks = 0

        self.last_mouse_event = None
        self.mouse_pos = None

        self.left_mouse_down = False
        self.right_mouse_down = False
        self.middle_mouse_down = False
        self.mouse_in_window = False

        self.bind("<Button-1>", self._on_left_click)
        self.bind("<Button-2>", self._on_middle_click)
        self.bind("<Button-3>", self._on_right_click)

        self.bind("<ButtonRelease-1>", self._on_left_release)
        self.bind("<ButtonRelease-2>", self._on_middle_release)
        self.bind("<ButtonRelease-3>", self._on_right_release)

        self.bind("<ButtonPress-1>", self._on_left_press)
        self.bind("<ButtonPress-2>", self._on_middle_press)
        self.bind("<ButtonPress-3>", self._on_right_press)

        self.bind("<Motion>", self._on_mouse_motion)
        self.bind_all("<MouseWheel>", self._on_mouse_scroll)
        self.bind("<Enter>", self._on_mouse_in)
        self.bind("<Leave>", self._on_mouse_out)
        self._mouse_callback = None

        self.mouse_wheel_pos = 0
        self.mouse_scroll_amount = 0
        self.last_key_pressed = ""

        self.height = height
        self.width = width

        self.style = style

        master.lift()

        if autoflush:
            _root.update()
        self.instances.append(self)

        self.set_coords(0, 0, width, height)

    def __repr__(self):
        if self.is_closed():
            return "<Closed GraphWin>"
        else:
            return "GraphWin('{}', {}, {})".format(self.master.title(), self.get_width(), self.get_height())

    def __str__(self):
        return repr(self)

    def __check_open(self):
        if self.closed:
            raise GraphicsError("\n\nwindow is closed")

    def set_mouse_handler(self, func):
        self._mouse_callback = func

    # Returns the position of the window on the display of the computer
    def get_window_pos(self):
        return Point(self.master.winfo_rootx(), self.master.winfo_rooty())

    # Sets the background colour of the window
    def set_background(self, colour):
        """Set background colour of the window"""

        if not isinstance(colour, Colour):
            if colour in STYLES[self.style].keys():
                self.bk_colour = STYLES[self.style]["background"]
            elif colour is None:
                self.bk_colour = STYLES["default"]["background"]
        else:
            self.bk_colour = colour

        self.__check_open()
        self.master.config(bg=self.bk_colour)
        self.__autoflush()

    def set_border_width(self, width):

        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nThe window's border's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's border's width must be greater than 0, not {width}")

        self.border_width = width
        self.__check_open()
        self.master.config(bd=width)
        self.__autoflush()

    def set_border_relief(self, relief):

        if not isinstance(relief, str):
            raise GraphicsError(f"\n\nThe border relief (relief) must be a string, not {relief}")
        if not relief.lower() in RELIEF:
            raise GraphicsError(f"\n\nThe relief for the window border must be one of {RELIEF}, not {relief}")

        self.border_relief = relief
        self.__check_open()
        self.master.config(relief=relief)
        self.__autoflush()

    def set_cursor(self, cursor):

        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS:
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {CURSORS}, not {cursor}")

        self.__check_open()
        self.cursor = cursor
        self.config(cursor=cursor)
        self.__autoflush()

    def set_resizable(self, resizable_width=True, resizable_height=True):
        self.set_resizable_height(resizable_height)
        self.set_resizable_width(resizable_width)
        return self

    def set_resizable_height(self, resizable_height=True):
        if not isinstance(resizable_height, bool):
            raise GraphicsError(f"\n\nresizable_height must be a boolean, not {resizable_height}")

        self.master.resizable(self.is_resizable[0], resizable_height)
        self.is_resizable[1] = resizable_height
        return self
    
    def set_resizable_width(self, resizable_width=True):
        if not isinstance(resizable_width, bool):
            raise GraphicsError(f"\n\nresizable_height must be a boolean, not {resizable_width}")

        self.master.resizable(resizable_width, self.is_resizable[1])
        self.is_resizable[0] = resizable_width
        return self

    def set_icon(self, icon):
        if not isinstance(icon, str):
            raise GraphicsError(f"The window icon must be a string (path to .ico texture) or None, not {icon}")
        if not os.path.isfile(f"textures/{icon}"):
            raise GraphicsError(f"The icon path you have specified ({icon}) does not exist. "
                                f"Check for spelling and make sure this is in the correct directory.")
        if not icon.endswith(".ico"):
            raise GraphicsError("The icon file must be a .ico type. "
                                "You can use an online converter to convert your file")

        self.__check_open()
        self.master.iconbitmap(icon)
        self.__autoflush()

    def set_title(self, title):
        if not isinstance(title, str):
            raise GraphicsError(f"\n\nThe window's title must be a string, not {title}")

        self.title = title
        self.__check_open()
        self.master.title(title)
        self.__autoflush()

    def set_width(self, width):
        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nThe window's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's width must be greater than 0, not {width}")

        if width < self.min_width:
            self.min_width = width
            warning = f"\n\nWindow width ({width}) is less than window's minimum width ({self.min_width}). " \
                      f"Window minimum width has been set to {width}"
            warnings.warn(warning, GraphicsWarning)

            self.master.minsize(self.min_width, self.min_height)

        self.width = width
        self.__check_open()
        self.master.config(width=self.width)
        self.__autoflush()

    def set_height(self, height):
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError(f"\n\nThe window's height must be a number (integer or float), not {height}")
        if not height > 0:
            raise GraphicsError(f"\n\nThe window's height must be greater than 0, not {height}")

        if height < self.min_height:
            self.min_height = height
            warning = f"\n\nWindow height (height={height}) is less than window's minimum height (min_height=" \
                      f"{self.min_height}). Window's minimum height has been set to {height}"
            warnings.warn(warning, GraphicsWarning)

            self.master.minsize(self.min_width, self.min_height)

        self.height = height
        self.__check_open()
        self.master.config(height=height)
        self.__autoflush()

    def set_min_height(self, height):
        if not isinstance(height, int):
            raise GraphicsError(f"\n\nThe window's minimum height (min_height) must be an integer, not {height}")

        self.min_height = height
        if height > self.height:
            warning = "\n\nMinimum height (min_height={}) is greater than the window's current height (height={})." + \
                      "Window's height has been set to {})".format(height, self.height, height)
            warnings.warn(warning, GraphicsWarning)
            self.set_height(height)

        self.master.minsize(self.min_width, self.min_height)

    def set_min_width(self, width):
        if not isinstance(width, int):
            raise GraphicsError(f"\n\nThe window's minimum width (min_width) must be an integer, not {width}")

        self.min_width = width
        if width > self.width:
            warning = "\n\nMinimum width (min_width={}) is greater than the window's current width (width={})." + \
                      "Window's width has been set to {})".format(width, self.width, width)
            warnings.warn(warning, GraphicsWarning)
            self.set_width(width)

        self.master.minsize(self.min_width, self.min_height)

    def set_size(self, width, height):
        self.set_height(height)
        self.set_width(width)

    def set_min_size(self, min_width, min_height):
        self.set_min_height(min_height)
        self.set_min_width(min_width)

    def set_coords(self, x1, y1, x2, y2):
        """Set coordinates of window to run from (x1,y1) in the
        upper-left corner to (x2,y2) in the lower-right corner."""
        if not ((isinstance(x1, int) or isinstance(x1, float)) and (isinstance(y1, int) or isinstance(y1, float)) and
                (isinstance(x2, int) or isinstance(x2, float)) and (isinstance(y2, int) or isinstance(y2, float))):
            raise GraphicsError("\n\nCoordinate Arguments must be numbers (integers or floats)")
        self.trans = Transform(self.get_width(), self.get_height(), x1, y2, x2, y1)
        self.center = Point(abs((x2 - x1) / 2), abs((y2 - y1) / 2))
        self.redraw()

    def close(self):
        """Close the window"""

        if self.closed:
            return
        self.closed = True
        self.master.destroy()
        GraphWin.instances.remove(self)
        self.__autoflush()

    def is_closed(self):
        return self.closed

    def is_open(self):
        return not self.closed

    def __autoflush(self):
        if self.autoflush:
            _root.update()
            self.update_win(_internal_updating=True)

    def plot(self, x, y, colour=BLACK):
        """Set pixel (x,y) to the given colour"""

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("\n\nx & y position must be numbers (integers, or floats)")
        if not isinstance(colour, Colour):
            if colour in STYLES[self.style].keys():
                colour = STYLES[self.style]["background"]
            elif colour is None:
                colour = STYLES["default"]["background"]

        self.__check_open()
        xs, ys = self.to_screen(x, y)
        self.create_line(xs, ys, xs + 1, ys, fill=colour)
        self.__autoflush()

    def flush(self):
        """Update drawing to the window"""
        self.__check_open()
        self.update_idletasks()

    def update_win(self, _internal_updating=False):
        if self.autoflush and not _internal_updating:
            warnings.warn("Updating the Graphics Object while autoflush is True might lead to issues, either let the "
                          "window update automatically by setting autoflush to True or update it manually",
                          GraphicsWarning)
        self.update()

        GraphicsObject.on_update(self)

    def save_canvas(self, height=None, width=None):
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

    def get_size(self):
        return self.get_width(), self.get_height()

    # TRIGGER MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def _on_left_click(self, e):
        if self.is_open():
            self.mouse_left_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            self.total_left_mouse_clicks += 1

            if self._mouse_callback:
                self._mouse_callback(Point(e.x, e.y))

            GraphicsObject.on_left_click(self)

    def _on_middle_click(self, e):
        if self.is_open():
            self.mouse_middle_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            self.total_middle_mouse_clicks += 1

            if self._mouse_callback:
                self._mouse_callback(Point(e.x, e.y))

            GraphicsObject.on_middle_click()

    def _on_right_click(self, e):
        if self.is_open():
            self.mouse_right_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            self.total_right_mouse_clicks += 1

            if self._mouse_callback:
                self._mouse_callback(Point(e.x, e.y))

            GraphicsObject.on_right_click()

    # TRIGGER MOUSE RELEASE FUNCTIONS
    # -------------------------------------------------------------------------

    def _on_left_release(self, e):
        if self.is_open():
            self.left_mouse_down = False
            self._on_left_click(e)

    def _on_middle_release(self, e):
        if self.is_open():
            self.middle_mouse_down = False
            self._on_middle_click(e)

    def _on_right_release(self, e):
        if self.is_open():
            self.right_mouse_down = False
            self._on_right_click(e)

    # TRIGGER MOUSE PRESS FUNCTIONS
    # -------------------------------------------------------------------------

    def _on_left_press(self, e):
        if self.is_open():
            self.mouse_left_press = e.x, e.y
            self.last_mouse_event = self.mouse_left_press
            self.left_mouse_down = True

            GraphicsObject.on_left_press(self)

    def _on_middle_press(self, e):
        if self.is_open():
            self.middle_mouse_down = True

            self.mouse_middle_press = e.x, e.y
            self.last_mouse_event = self.mouse_middle_press

    def _on_right_press(self, e):
        if self.is_open():
            self.right_mouse_down = True

            self.mouse_right_press = e.x, e.y
            self.last_mouse_event = self.mouse_right_press

    # OTHER TRIGGER MOUSE FUNCTIONS
    # -------------------------------------------------------------------------

    def _on_mouse_motion(self, e):
        if self.is_open():
            self.mouse_pos = self.trans.world(e.x, e.y)

            if self.mouse_in_window:
                GraphicsObject.on_mouse_motion(self)

    def _on_mouse_scroll(self, e):
        if self.is_open():
            self.mouse_wheel_pos = e.delta
            GraphicsObject.on_mouse_scroll(e.delta / 120, self)

    def _on_mouse_in(self, e):
        self.mouse_in_window = True

    def _on_mouse_out(self, e):
        self.mouse_in_window = False

    # GET MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def get_left_mouse_press(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_left_mouse_press()
            self.update()

            if self.is_closed():
                break

        return mouse_pos

    def get_middle_mouse_press(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_middle_mouse_press()
            self.update()

            if self.is_closed():
                break

        return mouse_pos

    def get_right_mouse_press(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_right_mouse_press()
            self.update()

            if self.is_closed():
                break

        return mouse_pos

    # GET MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def get_left_mouse_click(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_left_mouse_click()
            self.update()

            if self.is_closed():
                break

        return mouse_pos

    def get_middle_mouse_click(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_middle_mouse_click()
            self.update()

            if self.is_closed():
                break

        return mouse_pos

    def get_right_mouse_click(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_right_mouse_click()
            self.update()

            if self.is_closed():
                break

        return mouse_pos

    # MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def check_left_mouse_click(self, refresh=True):

        if self.is_closed():
            pass
        if self.mouse_left_click is not None and not self.is_closed():
            x, y = self.to_world(self.mouse_left_click[0], self.mouse_left_click[1])

            if refresh:
                self.mouse_left_click = None
            return Point(x, y)
        else:
            return None

    def check_middle_mouse_click(self, refresh=True):

        if self.is_closed():
            pass
        if self.mouse_middle_click is not None and not self.is_closed():
            x, y = self.to_world(self.mouse_middle_click[0], self.mouse_middle_click[1])

            if refresh:
                self.mouse_middle_click = None
            return Point(x, y)
        else:
            return None

    def check_right_mouse_click(self, refresh=True):

        if self.is_closed():
            pass
        if self.mouse_right_click is not None and not self.is_closed():
            x, y = self.to_world(self.mouse_right_click[0], self.mouse_right_click[1])

            if refresh:
                self.mouse_right_click = None
            return Point(x, y)
        else:
            return None

    # MOUSE PRESS FUNCTIONS
    # -------------------------------------------------------------------------

    def check_left_mouse_press(self, refresh=True):
        if self.is_closed():
            pass
        if self.mouse_left_press is not None and not self.is_closed():
            x, y = self.to_world(self.mouse_left_press[0], self.mouse_left_press[1])

            if refresh:
                self.mouse_left_press = None
            return Point(x, y)
        else:
            return None

    def check_middle_mouse_press(self, refresh=True):
        if self.mouse_middle_press is not None and not self.is_closed():
            x, y = self.to_world(self.mouse_middle_press[0], self.mouse_middle_press[1])

            if refresh:
                self.mouse_middle_press = None

            return Point(x, y)
        else:
            return None

    def check_right_mouse_press(self, refresh=True):
        if self.mouse_right_press is not None and not self.is_closed():
            x, y = self.to_world(self.mouse_right_press[0], self.mouse_right_press[1])

            if refresh:
                self.mouse_right_press = None

            return Point(x, y)
        else:
            return None

    # OTHER MOUSE FUNCTIONS
    # -------------------------------------------------------------------------

    def check_mouse_scroll(self):
        if self.is_closed():
            return None
        else:
            self.update()
            self.mouse_scroll_amount += self.mouse_wheel_pos / 120
            self.mouse_wheel_pos = 0

            return self.mouse_scroll_amount

    def get_last_mouse(self):
        if self.last_mouse_event is not None:
            return Point(self.last_mouse_event[0], self.last_mouse_event[1])
        else:
            return

    def check_mouse_motion(self, refresh=True):
        if self.mouse_pos is not None:
            x, y = self.mouse_pos

            if refresh:
                self.mouse_pos = None

            return Point(x, y)
        else:
            return

    def check_left_mouse_down(self):
        return self.left_mouse_down

    def check_right_mouse_down(self):
        return self.right_mouse_down

    def check_middle_mouse_down(self):
        return self.middle_mouse_down

    # KEYBOARD FUNCTIONS
    # -------------------------------------------------------------------------

    def get_key(self, key):
        """Wait for user to press a key and return it as a string."""
        while not self.check_key(key):
            time.sleep(.1)  # give up thread

        return True

    def check_key(self, key):
        """Return last key pressed or None if no key pressed since last call"""
        if self.is_closed():
            raise GraphicsError("\n\ncheck_key in closed window")

        if keyboard.is_pressed(key):
            return True
        else:
            return False

    def check_all_keys(self, *keys):
        key_down = True
        for key in keys:
            if key_down:
                key_down = self.check_key(key)
            else:
                return False

        return True

    def check_keys(self, *keys):
        for key in keys:
            if self.check_key(key):
                return True

        return False

    def get_height(self):
        """Return the height of the window"""
        self.height = self.master.winfo_height()
        return self.height

    def get_width(self):
        """Return the width of the window"""
        self.width = self.master.winfo_width()
        return self.width

    def to_screen(self, x, y):
        trans = self.trans
        if trans:
            return self.trans.screen(x, y)
        else:
            return x, y

    def to_world(self, x, y):
        trans = self.trans
        if trans:
            return self.trans.world(x, y)
        else:
            return x, y

    def add_item(self, item):
        self.items.append(item)

    def del_item(self, item):
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