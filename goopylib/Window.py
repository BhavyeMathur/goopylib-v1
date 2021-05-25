from tkinter import Canvas as tkCanvas
from tkinter import Toplevel as tkToplevel

from PIL import ImageGrab  # Required to take snapshots of the GraphWin to save as an Image

import warnings
from os.path import isfile as osisfile
from time import time as timetime

from goopylib.styles import *
from goopylib.util import GraphicsError, GraphicsWarning, resource_path
from goopylib.constants import _root, BORDER_RELIEFS, CURSORS
from goopylib.math.easing import *

from goopylib._internal_classes import Transform


class Window(tkCanvas):
    """A Window is a toplevel window for displaying graphics."""
    instances = []  # a list of all instances of this class

    # Most of the parameters are self explanatory, but for those that might not be:

    # Resizable Height & Width: Whether you can resize the window by pulling its sides
    # Autoflush: The window will update automatically if True
    # Style: The colour styles have attributes called 'background-colour' which the window will use if bk_colour=None
    def __init__(self, title="New Goopylib Window", width=800, height=600, min_width=1, min_height=1, max_width=None,
                 max_height=None, x_pos=0, y_pos=0, resizable_width=False, resizable_height=False, bounds=None,
                 bk_colour=None, icon=None, autoflush=False, cursor="arrow", border_relief="flat",
                 border_width=0, remove_title_bar=False):

        # Making sure all the arguments are valid and raising errors if not

        if not isinstance(title, str):
            raise GraphicsError(f"\n\nThe window's title must be a string, not {title}")

        if not isinstance(width, int):
            raise GraphicsError(f"\n\nThe window's width must be an integer, not {width}")
        if width < 1:
            raise GraphicsError(f"\n\nThe window's width must be greater than 0, not {width}")
        if not isinstance(height, int):
            raise GraphicsError(f"\n\nThe window's height must be an integer, not {height}")
        if height < 1:
            raise GraphicsError(f"\n\nThe window's height must be greater than 0, not {height}")

        if not isinstance(x_pos, int):
            raise GraphicsError(f"\n\nThe window x-position (x_pos) must be an integer, not {x_pos}")
        if not isinstance(y_pos, int):
            raise GraphicsError(f"\n\nThe window y-position (y_pos) must be an integer, not {y_pos}")

        if not (isinstance(bk_colour, Colour) or bk_colour is None):
            raise GraphicsError("The window's background colour (bk_colour) must be None or a Colour Objector, "
                                f"not {bk_colour}")
        if icon is not None:
            if not isinstance(icon, str):
                raise GraphicsError(f"The window icon must be a string (path to .ico texture) or None, not {icon}")
            if not icon.endswith(".ico"):
                raise GraphicsError("The icon file must be a .ico type. "
                                    "You can use an online converter to convert your file")

        if not isinstance(min_width, int):
            raise GraphicsError(f"\n\nThe window's minimum width (min_width) must be an integer, not {min_width}")
        if min_width < 1:
            raise GraphicsError(f"\n\nThe window's minimum width must be greater than 0, not {min_width}")

        if not isinstance(min_height, int):
            raise GraphicsError(f"\n\nThe window's minimum height (min_height) must be an integer, not {min_height}")
        if min_height < 1:
            raise GraphicsError(f"\n\nThe window's minimum height must be greater than 0, not {min_height}")

        if max_width is not None:
            if isinstance(max_width, int):
                if min_width > max_width:
                    raise GraphicsError(
                        f"Window's minimum width ({min_width}) is larger than its maximum width ({max_width})")

                if width > max_width:
                    warning = f"\n\nWindow width ({width}) is greater than window's maximum width ({max_width}). " \
                              f"Window maximum width has been set to {width}."
                    max_width = width
                    warnings.warn(warning, GraphicsWarning)

            else:
                raise GraphicsError(f"\n\nThe window's maximum width (max_width) must be an integer, not {max_width}")

        if max_height is not None:
            if isinstance(max_height, int):
                if min_height > max_height:
                    raise GraphicsError(f"Window's minimum height ({min_height}) is larger than its maximum height "
                                        f"({max_height})'")

                if height > max_height:
                    warning = f"\n\nWindow height ({height}) is greater than window's maximum height ({max_height}). " \
                              f"Window maximum height has been set to {height}."
                    max_height = height
                    warnings.warn(warning, GraphicsWarning)

            else:
                raise GraphicsError("\n\nThe window's maximum height (max_height) must be an integer, "
                                    f"not {max_height}")

        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS.keys():
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {list(CURSORS.keys())}, not {cursor}")

        if not isinstance(border_relief, str):
            raise GraphicsError(f"\n\nThe border relief (border_relief) must be a string, not {border_relief}")
        if not border_relief.lower() in BORDER_RELIEFS:
            raise GraphicsError(f"\n\nThe relief for the window border must be one of {BORDER_RELIEFS}, not {border_relief}")
        if not isinstance(border_width, int):
            raise GraphicsError(f"\n\nThe window's border width must be an integer, not {border_width}")

        if bounds is not None and not isinstance(bounds, GraphicsObject):
            raise GraphicsError(f"\n\nThe window's bounds must be a GraphicsObject, not {bounds}")

        # Making sure that the parameters provided for the dimensions of the window don't contradict with each other.
        # If they do, this raises a warning and sets the dimensions to the correct value

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

        master = tkToplevel(_root)  # Actually creating the window
        master.protocol("WM_DELETE_WINDOW", self.close)  # Close the window if the X button is pressed

        # Assigning a background colour, this goes through multiple checks to assign a possible value:
        #   1. The user has directly provided a colour
        #   2. The colour provided is a colour tag in the window's style
        #   3. If not, choose the background colour tag of the window's style
        #   4. If this does not exist, choose the default background colour
        if isinstance(bk_colour, Colour):
            self.bk_colour = bk_colour
        else:
            self.bk_colour = STYLES["default"]["background"]

        # Setting most of the attributes of the window
        # We set the width & height of the window to be the screen size to get rid of a bug with resizing,
        # then setting the window coordinates

        tkCanvas.__init__(self, master, width=width, height=height,
                          highlightthickness=0, bd=border_width,
                          bg=self.bk_colour, cursor=CURSORS[cursor.lower()], relief=border_relief)
        self.master.config(width=width, height=height)  # Changing the dimensions to be correct

        self.master.title(title)  # Setting the title of the widow
        self.title = title

        self.master.geometry('%dx%d+%d+%d' % (width, height, x_pos, y_pos))  # Setting the X & Y position of the window
        self.height = height
        self.width = width
        self.center = [width / 2, height / 2]

        self.min_width = min_width
        self.min_height = min_height
        self.master.minsize(self.min_width, self.min_height)  # Minimum size of the window

        self.max_width = max_width
        self.max_height = max_height
        self.master.maxsize(self.max_width, self.max_height)  # Maximum size of the window

        self.master.resizable(resizable_width, resizable_height)  # Is the window resizable?
        self.is_resizable = [resizable_width, resizable_height]

        self.is_gliding = False

        # The Transform Class for the window
        # This helps transform any coordinates into window coordinates (world) or absolute coords (screen)
        self.trans = None
        self.closed = False
        self.autoflush = autoflush

        self.cursor = cursor.lower()
        self.current_cursor = self.cursor

        self.border_width = border_width
        self.border_relief = border_relief.lower()

        if icon is not None:  # Setting the Icon of the Window
            if osisfile(resource_path(f"textures/{icon}")):
                self.master.iconbitmap(resource_path(f"textures/{icon}"))
            else:
                self.master.iconbitmap(resource_path(f"{icon}"))

        self.pack()

        self.imgs = 0  # Number of Images in this window
        self.items = []  # All the Graphics Objects in this window

        # Mouse Related Variables

        self.mouse_left_click = None  # These are all coordinates of these events
        self.mouse_middle_click = None
        self.mouse_right_click = None

        self.mouse_double_left_click = None
        self.mouse_double_middle_click = None
        self.mouse_double_right_click = None

        self.mouse_triple_left_click = None
        self.mouse_triple_middle_click = None
        self.mouse_triple_right_click = None

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

        self.master.bind("<1>", lambda event: event.widget.focus_set())
        self.bind("<Button-1>", self._on_left_click)  # These functions are called whenever these events happen
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

        self.bind("<Double-Button-1>", self._on_left_double_click)
        self.bind("<Double-Button-2>", self._on_middle_double_click)
        self.bind("<Double-Button-3>", self._on_right_double_click)

        self.bind("<Triple-Button-1>", self._on_left_triple_click)
        self.bind("<Triple-Button-2>", self._on_middle_triple_click)
        self.bind("<Triple-Button-3>", self._on_right_triple_click)

        self._mouse_callback = None
        
        self.is_draggable_x = False
        self.is_draggable_y = False
        self.is_dragging = False
        self.bounds = bounds

        self.mouse_wheel_pos = 0
        self.mouse_scroll_amount = 0

        # Keyboard Variables

        self.last_key_pressed = None
        self.last_key_clicked = None

        self.key_pressed_with_shift = None
        self.key_pressed_with_alt = None
        self.key_pressed_with_control = None

        self.keys_down = {*()}
        self.keys_clicked = {*()}

        self.bind("<KeyPress>", self._on_key_press)
        self.bind("<Shift-KeyPress>", self._on_shift_key_press)
        self.bind("<Alt-KeyPress>", self._on_alt_key_press)
        self.bind("<Control-KeyPress>", self._on_control_key_press)

        self.bind("<KeyRelease>", self._on_key_release)

        # Animation Variables

        self.is_gliding = False  # Is the window gliding?
        self.glide_queue = []  # The next locations for the window to glide to

        master.lift()  # No idea what this does, does anyone know?
        Window.instances.append(self)

        _root.update_idletasks()

        self.set_coords(0, 0, width, height)
        self.x_pos = x_pos
        self.y_pos = y_pos

        if remove_title_bar:
            master.overrideredirect(True)

        self.last_update = 0

    def __repr__(self):
        if self.closed:
            return f"Closed Window({self.title})"
        else:
            return f"Window('{self.master.title()}', {self.master.winfo_width()}x{self.master.winfo_height()})"

    def _check__check_open(self):
        try:
            return self.__check_open()
        except GraphicsError:
            return False

    def _check__autoflush(self):
        return self.__autoflush()

    def __check_open(self):
        if self.closed:
            raise GraphicsError("\n\nGraphicsError: window is closed")
        return True

    def is_closed(self):
        return self.closed

    def is_open(self):
        return not self.closed

    # This is called automatically whenever the window needs to update
    def __autoflush(self):
        if self.autoflush:
            return _root.update()
        return False

    def __set_mouse_handler(self, func):
        self._mouse_callback = func
        
    # -------------------------------------------------------------------------
    # CALLBACK KEYBOARD FUNCTIONS

    def _on_key_release(self, e):
        if e.keysym in self.keys_down:
            self.keys_down.remove(e.keysym)
        if e.keysym not in self.keys_clicked:
            self.keys_clicked.add(e.keysym)

    def _on_key_press(self, e):
        self.last_key_pressed = e.keysym
        if e.keysym not in self.keys_down:
            self.keys_down.add(e.keysym)

    def _on_shift_key_press(self, e):
        self.key_pressed_with_shift = e.keysym

    def _on_alt_key_press(self, e):
        self.key_pressed_with_alt = e.keysym

    def _on_control_key_press(self, e):
        self.key_pressed_with_control = e.keysym

    # -------------------------------------------------------------------------
    # CALLBACK MOUSE FUNCTIONS

    # Double Click
    def _on_left_double_click(self, e):
        if self.is_open():
            self.mouse_double_left_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_double_left_click(self)

    def _on_middle_double_click(self, e):
        if self.is_open():
            self.mouse_double_middle_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_double_middle_click(self)

    def _on_right_double_click(self, e):
        if self.is_open():
            self.mouse_double_right_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_double_right_click(self)

    # Triple Click

    def _on_left_triple_click(self, e):
        if self.is_open():
            self.mouse_triple_left_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_triple_left_click(self)

    def _on_middle_triple_click(self, e):
        if self.is_open():
            self.mouse_triple_middle_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_triple_middle_click(self)

    def _on_right_triple_click(self, e):
        if self.is_open():
            self.mouse_triple_right_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_triple_right_click(self)

    # Single Click

    def _on_left_click(self, e):
        if self.is_open():
            self.mouse_left_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            self.total_left_mouse_clicks += 1

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_left_click(self)

    def _on_middle_click(self, e):
        if self.is_open():
            self.mouse_middle_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            self.total_middle_mouse_clicks += 1

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_middle_click(self)

    def _on_right_click(self, e):
        if self.is_open():
            self.mouse_right_click = e.x, e.y
            self.last_mouse_event = self.trans.world(e.x, e.y)

            self.total_right_mouse_clicks += 1

            if self._mouse_callback:
                self._mouse_callback([e.x, e.y])

            GraphicsObject.on_right_click(self)

    # Mouse Release

    def _on_left_release(self, e):
        if self.is_open():
            self.left_mouse_down = False
            self.is_dragging = False
            self._on_left_click(e)

    def _on_middle_release(self, e):
        if self.is_open():
            self.middle_mouse_down = False
            self._on_middle_click(e)

    def _on_right_release(self, e):
        if self.is_open():
            self.right_mouse_down = False
            self._on_right_click(e)

    #  Mouse Press

    def _on_left_press(self, e):
        if self.is_open():
            self.mouse_left_press = e.x, e.y
            self.last_mouse_event = self.mouse_left_press
            self.left_mouse_down = True

            if self.bounds is None or self.bounds.is_clicked([e.x, e.y]):
                self.is_dragging = True

                self.last_drag_x = e.x
                self.last_drag_y = e.y
                
            GraphicsObject.on_left_press(self)

    def _on_middle_press(self, e):
        if self.is_open():
            self.middle_mouse_down = True

            self.mouse_middle_press = e.x, e.y
            self.last_mouse_event = self.mouse_middle_press

            GraphicsObject.on_middle_press(self)

    def _on_right_press(self, e):
        if self.is_open():
            self.right_mouse_down = True

            self.mouse_right_press = e.x, e.y
            self.last_mouse_event = self.mouse_right_press

            GraphicsObject.on_right_press(self)

    # Other Mouse Functions

    def _on_mouse_motion(self, e):
        if self.is_open():
            self.mouse_pos = self.trans.world(e.x, e.y)
            if self.left_mouse_down:
                if self.is_dragging:
                    self.move(e.x - self.last_drag_x if self.is_draggable_x else 0,
                              e.y - self.last_drag_y if self.is_draggable_y else 0)

    def _on_mouse_scroll(self, e):
        self.mouse_wheel_pos = e.delta
        GraphicsObject.on_mouse_scroll(e.delta / 120, self)

    def _on_mouse_in(self, e):
        self.mouse_in_window = True

    def _on_mouse_out(self, e):
        self.mouse_in_window = False

    """
    def start_move(self, event):
        self.x = event.x
        self.y = event.y

    def stop_move(self, event):
        self.x = None
        self.y = None

    def draw_bounds(self):
        self.bounds.draw(self)
        return self
    
    """

    # WINDOW MOVING & GLIDING FUNCTIONS
    # -------------------------------------------------------------------------

    # Change position by amount
    def move(self, dx, dy):
        self.move_x(dx)
        self.move_y(dy)
        return self

    def move_x(self, dx):
        if not (isinstance(dx, int) or isinstance(dx, float)):
            raise GraphicsError("\n\nThe amount to move the window in the x-direction (dx) must be a number "
                                f"(integer or float), not {dx}")
        self.x_pos += dx
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, self.x_pos, self.y_pos))
        return self

    def move_y(self, dy):
        if not (isinstance(dy, int) or isinstance(dy, float)):
            raise GraphicsError("\n\nThe amount to move the window in the y-direction (dy) must be a number "
                                f"(integer or float), not {dy}")
        self.y_pos += dy
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, self.x_pos, self.y_pos))
        return self

    # Set position to
    def move_to(self, x, y):
        self.move_to_x(x)
        self.move_to_y(y)
        return self

    def move_to_x(self, x):
        if not (isinstance(x, int) or isinstance(x, float)):
            raise GraphicsError("\n\nThe x location to move the window to (x) must be a number "
                                f"(integer or float), not {x}")
        self.x_pos = x
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, self.x_pos, self.y_pos))
        return self

    def move_to_y(self, y):
        if not (isinstance(y, int) or isinstance(y, float)):
            raise GraphicsError("\n\nThe y location to move the window to (y) must be a number "
                                f"(integer or float), not {y}")
        self.y_pos = y
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, self.x_pos, self.y_pos))
        return self

    def move_to_point(self, p):
        if not isinstance(p, list):
            raise GraphicsError(f"\n\nGraphicsError: point argument (p) must be a list in the form [x, y] , not {p}")
        self.move_to(p[0], p[1])
        return self

    # Gliding Functions

    def glide(self, dx, dy=None, time=1, easing_x=py_ease_linear(), easing_y=None):
        if dy is None:
            dy = dx
        if easing_y is None:
            easing_y = easing_x

        self.glide_x(time=time, dx=dx, easing=easing_x, _internal_call=True)
        self.glide_y(time=time, dy=dy, easing=easing_y, _internal_call=True)

        self.glide_queue.append({"Time": time, "Start": timetime(),
                                 "Update": timetime(), "Initial": [self.x_pos, self.y_pos],
                                 "Dist": [dx, dy], "EasingX": easing_x, "EasingY": easing_y})

        return self

    def glide_x(self, dx, time=1, easing=py_ease_linear(), _internal_call=False):
        if not (isinstance(dx, int) or isinstance(dx, float)):
            raise GraphicsError("\n\nThe x amount to glide the window by (dx) must be a number "
                                f"(integer or float), not {dx}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to glide the window for (time) must be a number "
                                f"(integer or float), not {time}")

        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        self.is_gliding = True
        if not _internal_call:
            start = timetime()
            initial_pos = [self.x_pos, self.y_pos]

            for glide in self.glide_queue:
                start += glide["Time"]
                initial_pos = glide["Initial"] + glide["Dist"]

            self.glide_queue.append({"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                                     "Dist": [dx, 0], "EasingX": easing, "EasingY": easing})

        return self

    def glide_y(self, dy, time=1, easing=py_ease_linear(), _internal_call=False):
        if not (isinstance(dy, int) or isinstance(dy, float)):
            raise GraphicsError("\n\nThe y amount to glide the window by (dy) must be a number "
                                f"(integer or float), not {dy}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to glide the window for (time) must be a number "
                                f"(integer or float), not {time}")

        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        self.is_gliding = True
        if not _internal_call:
            start = timetime()
            initial_pos = [self.x_pos, self.y_pos]

            for glide in self.glide_queue:
                start += glide["Time"]
                initial_pos = glide["Initial"] + glide["Dist"]

            self.glide_queue.append({"Time": time, "Start": start,
                                     "Update": timetime(), "Initial": initial_pos,
                                     "Dist": [0, dy], "EasingX": easing, "EasingY": easing})

        return self

    def glide_to(self, x, y=None, time=1, easing_x=py_ease_linear(), easing_y=None):
        if y is None:
            y = x
        if easing_y is None:
            easing_y = easing_x

        self.glide_x(time=time, dx=x - self.x_pos, easing=easing_x, _internal_call=True)
        self.glide_y(time=time, dy=y - self.y_pos, easing=easing_y, _internal_call=True)

        start = timetime()
        initial_pos = [self.x_pos, self.y_pos]
        for glide in self.glide_queue:
            start += glide["Time"]
            initial_pos = glide["Initial"] + glide["Dist"]

        self.glide_queue.append({"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                                 "Dist": [x - initial_pos[0], y - initial_pos[1]], "EasingX": easing_x, "EasingY": easing_y})

        return self

    def glide_to_x(self, x, time=1, easing=py_ease_linear()):
        return self.glide_x(time=time, dx=x - self.x_pos, easing=easing)

    def glide_to_y(self, y, time=1, easing=py_ease_linear()):
        return self.glide_y(time=time, dy=y - self.y_pos, easing=easing)

    def glide_to_point(self, p, time=1, easing_x=py_ease_linear(), easing_y=None):
        if not isinstance(p, list):
            raise GraphicsError(f"\n\nGraphicsError: point argument (p) must be a list in the form [x, y] , not {p}")
        return self.glide_to(x=p[0], y=p[1], time=time, easing_x=easing_x, easing_y=easing_y)

    # GETTER FUNCTIONS
    # -------------------------------------------------------------------------

    # Returns the position of the window on the display of the computer
    def get_pos(self):
        return self.x_pos, self.y_pos

    def get_x_pos(self):
        return self.x_pos
    
    def get_y_pos(self):
        return self.y_pos

    def get_background(self):
        return self.bk_colour

    def get_bk_colour(self):
        raise GraphicsError("\n\nGraphicsError: deprecated function get_bk_colour(), use get_background() instead")

    def get_border_width(self):
        return self.border_width

    def get_border_relief(self):
        return self.border_relief

    def get_window_cursor(self):
        return self.cursor

    def get_current_cursor(self):
        return self.current_cursor

    def get_resizable(self):
        return self.is_resizable[0], self.is_resizable[1]

    def get_width_resizable(self):
        return self.is_resizable[0]

    def get_height_resizable(self):
        return self.is_resizable[1]

    def get_draggable(self):
        return self.is_draggable_x, self.is_draggable_y

    def get_x_draggable(self):
        return self.is_draggable_x

    def get_y_draggable(self):
        return self.is_draggable_y

    def get_size(self):
        return self.get_width(), self.get_height()

    def get_width(self):
        """Return the width of the window"""
        self.width = self.master.winfo_width()
        return self.width

    def get_height(self):
        """Return the height of the window"""
        self.height = self.master.winfo_height()
        return self.height

    def get_min_size(self):
        return self.min_width, self.min_height

    def get_min_width(self):
        return self.min_width

    def get_min_height(self):
        return self.min_height

    def get_max_size(self):
        return self.max_width, self.max_height

    def get_max_width(self):
        return self.max_width

    def get_max_height(self):
        return self.max_height

    def get_title(self):
        return self.title

    def get_coords(self):
        return [self.trans.x_base, self.trans.y_base], [self.trans.other_x, self.trans.other_x]

    def get_top_left(self):
        return [self.trans.x_base, self.trans.y_base]

    def get_top_right(self):
        return [self.trans.other_x, self.trans.y_base]

    def get_bottom_right(self):
        return [self.trans.other_x, self.trans.other_y]

    def get_bottom_left(self):
        return [self.trans.x_base, self.trans.other_y]

    def get_center(self):
        return [abs(self.trans.other_x - self.trans.x_base) // 2, abs(self.trans.other_y - self.trans.y_base) // 2]

    # SETTER FUNCTIONS
    # -------------------------------------------------------------------------

    # Sets the background colour of the window
    def set_background(self, colour):
        """Set background colour of the window"""

        if isinstance(colour, Colour):
            self.bk_colour = colour
        elif isinstance(colour, str):
            self.bk_colour = ColourHex(colour)
        else:
            raise GraphicsError(f"\n\nGraphicsError: invalid background colour {colour}, must be a Colour object")

        self.__check_open()
        self.master.config(bg=self.bk_colour)
        return self

    def set_border_width(self, width):

        if not (isinstance(width, (float, int))):
            raise GraphicsError(f"\n\nThe window's border's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's border's width must be greater than 0, not {width}")

        self.border_width = width
        self.__check_open()
        self.master.config(bd=width)
        self.__autoflush()
        return self

    def set_border_relief(self, relief):
        if not isinstance(relief, str):
            raise GraphicsError(f"\n\nThe border relief (relief) must be a string, not {relief}")
        relief = relief.lower()
        if not relief in BORDER_RELIEFS:
            raise GraphicsError(f"\n\nThe relief for the window border must be one of {BORDER_RELIEFS}, not {relief}")

        self.border_relief = relief
        self.__check_open()
        self.master.config(relief=relief)
        self.__autoflush()
        return self

    def set_cursor(self, cursor, _internal_call=False):
        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS.keys():
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {list(CURSORS.keys())}, not {cursor}")

        self.__check_open()
        if _internal_call:
            self.current_cursor = cursor.lower()
        else:
            self.cursor = cursor.lower()

        self.config(cursor=CURSORS[cursor])
        self.__autoflush()
        return self

    def set_icon(self, icon):
        if not isinstance(icon, str):
            raise GraphicsError(f"The window icon must be a string (path to .ico texture) or None, not {icon}")
        if not (osisfile(f"textures/{icon}") or osisfile(f"{icon}")):
            raise GraphicsError(f"The icon path you have specified ({icon}) does not exist. "
                                f"Check for spelling and make sure this is in the correct directory.")
        if not icon.endswith(".ico"):
            raise GraphicsError("The icon file must be a .ico type. "
                                "You can use an online converter to convert your file")

        self.__check_open()
        self.master.iconbitmap(icon)
        self.__autoflush()
        return self

    def set_title(self, title):
        if not isinstance(title, str):
            raise GraphicsError(f"\n\nThe window's title must be a string, not {title}")

        self.title = title
        self.__check_open()
        self.master.title(title)
        self.__autoflush()
        return self
    
    def set_draggable(self, draggable=True):
        self.is_draggable_x = draggable
        self.is_draggable_y = draggable
        return self

    def set_draggable_x(self, draggable=True):
        self.is_draggable_x = draggable
        return self

    def set_draggable_y(self, draggable=True):
        self.is_draggable_y = draggable
        return self

    def set_bounds(self, bounds):
        if not isinstance(bounds, GraphicsObject):
            raise GraphicsError(f"\n\nThe window's bounds must be a GraphicsObject, not {bounds}")
        self.bounds = bounds
        return self

    # Dimensions Related

    def set_width(self, width):
        if not (isinstance(width, int) or isinstance(width, float)):
            raise GraphicsError(f"\n\nThe window's width must be a number (integer or float), not {width}")
        if not width > 0:
            raise GraphicsError(f"\n\nThe window's width must be greater than 0, not {width}")

        if width < self.min_width:
            self.min_width = width
            warning = f"\n\nWindow width ({width}) is less than window's minimum width ({self.min_width}). " \
                      f"Window minimum width has been set to {width}"
            raise GraphicsError(warning)

        elif width > self.max_width:
            warning = f"\n\nWindow width ({width}) is greater than window's maximum width ({self.max_width}). " \
                      f"Window maximum width has been set to {width}."
            max_width = width
            raise GraphicsError(warning)

        self.width = width
        self.__check_open()
        self.master.config(width=self.width)
        self.__autoflush()
        return self

    def set_height(self, height):
        if not (isinstance(height, int) or isinstance(height, float)):
            raise GraphicsError(f"\n\nThe window's height must be a number (integer or float), not {height}")
        if not height > 0:
            raise GraphicsError(f"\n\nThe window's height must be greater than 0, not {height}")

        if height < self.min_height:
            self.min_height = height
            warning = f"\n\nWindow height (height={height}) is less than window's minimum height (min_height=" \
                      f"{self.min_height}). Window's minimum height has been set to {height}"
            raise GraphicsError(warning)

        elif height > self.max_height:
            warning = f"\n\nWindow height ({height}) is greater than window's maximum height ({self.max_height}). " \
                      f"Window maximum height has been set to {height}."
            max_height = height
            raise GraphicsError(warning)

        self.height = height
        self.__check_open()
        self.master.config(height=height)
        self.__autoflush()
        return self

    def set_min_height(self, min_height):
        if not (isinstance(min_height, int) or isinstance(min_height, float)):
            raise GraphicsError(f"\n\nThe window's minimum height (min_height) must be a number (integer or float), "
                                f"not {min_height}")

        if min_height > self.max_height:
            raise GraphicsError(f"Minimum height ({min_height}) is larger than the window's maximum height"
                                f"({self.max_height})")

        self.min_height = min_height
        if min_height > self.height:
            warning = "\n\nMinimum height (min_height={}) is greater than the window's current height (height={})." + \
                      "Window's height has been set to {})".format(min_height, self.height, min_height)

            raise GraphicsError(warning)

        self.master.minsize(self.min_width, self.min_height)
        return self

    def set_min_width(self, min_width):
        if not (isinstance(min_width, int) or isinstance(min_width, float)):
            raise GraphicsError(f"\n\nThe window's minimum min_width (min_width) must be a number (integer or float), "
                                f"not {min_width}")

        if min_width > self.max_width:
            raise GraphicsError(f"Minimum width ({min_width}) is larger than the window's maximum width"
                                f"({self.max_width})")

        self.min_width = min_width
        if min_width > self.width:
            warning = "\n\nMinimum min_width (min_width={}) is greater than the window's current min_width (min_width={})." + \
                      "Window's min_width has been set to {})".format(min_width, self.width, min_width)
            raise GraphicsError(warning)

        self.master.minsize(self.min_width, self.min_height)
        return self

    def set_size(self, width, height):
        self.set_height(height)
        return self.set_width(width)

    def set_min_size(self, min_width, min_height):
        self.set_min_width(min_width)
        return self.set_min_height(min_height)

    def set_max_size(self, max_width, max_height):
        self.set_max_width(max_width)
        return self.set_max_height(max_height)

    def set_max_width(self, max_width):
        if not (isinstance(max_width, int) or isinstance(max_width, float)):
            raise GraphicsError(f"\n\nThe window's maximum width (max_width) must be a number (integer or float), "
                                f"not {max_width}")

        if max_width < self.min_width:
            raise GraphicsError(f"The Maximum Width ({max_width}) is less than the Window's minimum "
                                f"width ({self.min_width})")

        if self.width > max_width:
            warning = f"\n\nWindow's width ({self.width}) is greater than maximum width ({max_width}). " \
                      f"Maximum width has been set to {self.width}."
            self.max_width = self.width
            raise GraphicsError(warning)

        self.max_width = max_width
        self.master.maxsize(self.max_width, self.max_width)
        return self

    def set_max_height(self, max_height):
        if not (isinstance(max_height, int) or isinstance(max_height, float)):
            raise GraphicsError(f"\n\nThe window's maximum height (max_height) must be a number (integer or float), "
                                f"not {max_height}")

        if max_height < self.min_height:
            raise GraphicsError(f"The Maximum Height ({max_height}) is less than the Window's minimum "
                                f"height ({self.min_height})")

        if self.height > max_height:
            warning = f"\n\nWindow's height ({self.height}) is greater than maximum height ({max_height}). " \
                      f"Maximum height has been set to {self.height}."
            self.max_height = self.height
            raise GraphicsError(warning)

        self.max_height = max_height
        self.master.maxsize(self.max_width, self.max_height)
        return self

    def set_resizable(self, resizable_width=True, resizable_height=True):
        self.set_resizable_height(resizable_height)
        return self.set_resizable_width(resizable_width)

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

    def set_coords(self, x1, y1, x2, y2):
        """Set coordinates of window to run from (x1,y1) in the
        upper-left corner to (x2,y2) in the lower-right corner."""
        if not ((isinstance(x1, int) or isinstance(x1, float)) and (isinstance(y1, int) or isinstance(y1, float)) and
                (isinstance(x2, int) or isinstance(x2, float)) and (isinstance(y2, int) or isinstance(y2, float))):
            raise GraphicsError("\n\nCoordinate Arguments must be numbers (integers or floats)")

        self.trans = Transform(self.get_width(), self.get_height(), x1, y2, x2, y1)
        self.center = [abs((x2 - x1) / 2), abs((y2 - y1) / 2)]

        return self

    # OTHER WINDOW FUNCTIONS
    # -------------------------------------------------------------------------

    def close(self):
        """Close the window"""

        if self.closed:
            return
        self.master.destroy()
        self.closed = True
        self.__autoflush()
        Window.instances.remove(self)

        if len(Window.instances) > 0:
            Window.instances[0].master.bind("<1>", lambda event: event.widget.focus_set())
            Window.instances[0].bind("<Button-1>", Window.instances[0]._on_left_click)  # These functions are called whenever these events happen
            Window.instances[0].bind("<Button-2>", Window.instances[0]._on_middle_click)
            Window.instances[0].bind("<Button-3>", Window.instances[0]._on_right_click)

            Window.instances[0].bind("<ButtonRelease-1>", Window.instances[0]._on_left_release)
            Window.instances[0].bind("<ButtonRelease-2>", Window.instances[0]._on_middle_release)
            Window.instances[0].bind("<ButtonRelease-3>", Window.instances[0]._on_right_release)

            Window.instances[0].bind("<ButtonPress-1>", Window.instances[0]._on_left_press)
            Window.instances[0].bind("<ButtonPress-2>", Window.instances[0]._on_middle_press)
            Window.instances[0].bind("<ButtonPress-3>", Window.instances[0]._on_right_press)

            Window.instances[0].bind("<Motion>", Window.instances[0]._on_mouse_motion)
            Window.instances[0].bind_all("<MouseWheel>", Window.instances[0]._on_mouse_scroll)
            Window.instances[0].bind("<Enter>", Window.instances[0]._on_mouse_in)
            Window.instances[0].bind("<Leave>", Window.instances[0]._on_mouse_out)

            Window.instances[0].bind("<Double-Button-1>", Window.instances[0]._on_left_double_click)
            Window.instances[0].bind("<Double-Button-2>", Window.instances[0]._on_middle_double_click)
            Window.instances[0].bind("<Double-Button-3>", Window.instances[0]._on_right_double_click)

            Window.instances[0].bind("<Triple-Button-1>", Window.instances[0]._on_left_triple_click)
            Window.instances[0].bind("<Triple-Button-2>", Window.instances[0]._on_middle_triple_click)
            Window.instances[0].bind("<Triple-Button-3>", Window.instances[0]._on_right_triple_click)

            Window.instances[0].bind("<KeyPress>", Window.instances[0]._on_key_press)
            Window.instances[0].bind("<Shift-KeyPress>", Window.instances[0]._on_shift_key_press)
            Window.instances[0].bind("<Alt-KeyPress>", Window.instances[0]._on_alt_key_press)
            Window.instances[0].bind("<Control-KeyPress>", Window.instances[0]._on_control_key_press)

            Window.instances[0].bind("<KeyRelease>", Window.instances[0]._on_key_release)

        return self

    def plot(self, x, y, colour=BLACK):
        """Set pixel (x,y) to the given colour"""

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("\n\nx & y position must be numbers (integers, or floats)")
        if not isinstance(colour, Colour):
            if colour in STYLES[self.style].keys():
                colour = STYLES[self.style][colour]
            else:
                raise GraphicsError(f"Colour Argument must be a Colour or string referencing a style, not {colour}")

        self.__check_open()
        xs, ys = self.to_screen(x, y)
        self.create_line(xs, ys, xs + 1, ys, fill=colour)
        self.__autoflush()
        return self

    def flush(self):
        """Update drawing to the window"""
        self.__check_open()
        self.update_idletasks()
        return self

    def update(self, rate=None, _internal_updating=False):
        if rate is None or timetime() - self.last_update > 1 / rate:
            if self.is_gliding:
                t = timetime()

                # Check if the window is gliding for every interval of time or every frame
                # To cope with lag, you might use time to glide irrespective of how many frames passed

                # Check if the window should still be gliding
                if t - self.glide_queue[0]["Start"] >= self.glide_queue[0]["Time"]:
                    self.move_to(self.glide_queue[0]["Initial"][0] + self.glide_queue[0]["Dist"][0],
                                 self.glide_queue[0]["Initial"][1] + self.glide_queue[0]["Dist"][1])

                    self.glide_queue.pop(0)  # Remove the object from the gliding queue
                    if len(self.glide_queue) == 0:
                        self.is_gliding = False
                else:

                    perX = self.glide_queue[0]["EasingX"]((t - self.glide_queue[0]['Start']) / self.glide_queue[0]['Time'])
                    perY = self.glide_queue[0]["EasingY"]((t - self.glide_queue[0]['Start']) / self.glide_queue[0]['Time'])

                    self.move_to(self.glide_queue[0]["Initial"][0] + self.glide_queue[0]["Dist"][0] * perX,
                                 self.glide_queue[0]["Initial"][1] + self.glide_queue[0]["Dist"][1] * perY)

                    self.glide_queue[0]["Update"] = timetime()

            GraphicsObject.on_update(self)

            tkCanvas.update(self)

            self.last_update = timetime()
        return self

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

    # GET MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def get_left_mouse_press(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_left_mouse_press()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_middle_mouse_press(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_middle_mouse_press()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_right_mouse_press(self):
        """Wait for mouse click and return Point object representing
        the click"""

        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_right_mouse_press()
            self.update()

            if self.closed:
                break

        return mouse_pos

    # GET MOUSE CLICK FUNCTIONS
    # -------------------------------------------------------------------------

    def get_left_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_left_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_middle_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_middle_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_right_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_right_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    # Double Mouse Click

    def get_double_left_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_double_left_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_double_middle_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_double_middle_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_double_right_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_double_right_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    # Triple Mouse Click

    def get_triple_left_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_triple_left_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_triple_middle_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_triple_middle_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    def get_triple_right_mouse_click(self):
        mouse_pos = None

        while mouse_pos is None:
            mouse_pos = self.check_triple_right_mouse_click()
            self.update()

            if self.closed:
                break

        return mouse_pos

    # CHECK MOUSE FUNCTIONS
    # -------------------------------------------------------------------------

    def check_left_mouse_click(self, _refresh=True):
        if self.mouse_left_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_left_click[0], self.mouse_left_click[1])

        if _refresh:
            self.mouse_left_click = None
        return [x, y]

    def check_middle_mouse_click(self, _refresh=True):
        if self.mouse_middle_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_middle_click[0], self.mouse_middle_click[1])

        if _refresh:
            self.mouse_middle_click = None
        return [x, y]

    def check_right_mouse_click(self, _refresh=True):
        if self.mouse_right_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_right_click[0], self.mouse_right_click[1])

        if _refresh:
            self.mouse_right_click = None
        return [x, y]

    # Double Mouse Clicks

    def check_double_left_mouse_click(self, _refresh=True):
        if self.mouse_double_left_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_double_left_click[0], self.mouse_double_left_click[1])

        if _refresh:
            self.mouse_double_left_click = None
        return [x, y]

    def check_double_middle_mouse_click(self, _refresh=True):
        if self.mouse_double_middle_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_double_middle_click[0], self.mouse_double_middle_click[1])

        if _refresh:
            self.mouse_double_middle_click = None
        return [x, y]

    def check_double_right_mouse_click(self, _refresh=True):
        if self.mouse_double_right_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_double_right_click[0], self.mouse_double_right_click[1])

        if _refresh:
            self.mouse_double_right_click = None
        return [x, y]

    # Triple Mouse Clicks

    def check_triple_left_mouse_click(self, _refresh=True):
        if self.mouse_triple_left_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_triple_left_click[0], self.mouse_triple_left_click[1])

        if _refresh:
            self.mouse_triple_left_click = None
        return [x, y]

    def check_triple_middle_mouse_click(self, _refresh=True):
        if self.mouse_triple_middle_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_triple_middle_click[0], self.mouse_triple_middle_click[1])

        if _refresh:
            self.mouse_triple_middle_click = None
        return [x, y]

    def check_triple_right_mouse_click(self, _refresh=True):
        if self.mouse_triple_right_click is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_triple_right_click[0], self.mouse_triple_right_click[1])

        if _refresh:
            self.mouse_triple_right_click = None
        return [x, y]

    # Mouse Press

    def check_left_mouse_press(self, _refresh=True):
        if self.mouse_left_press is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_left_press[0], self.mouse_left_press[1])

        if _refresh:
            self.mouse_left_press = None
        return [x, y]

    def check_middle_mouse_press(self, _refresh=True):
        if self.mouse_left_press is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_middle_press[0], self.mouse_middle_press[1])

        if _refresh:
            self.mouse_middle_press = None

        return [x, y]

    def check_right_mouse_press(self, _refresh=True):
        if self.mouse_left_press is None or self.closed:
            return None

        x, y = self.to_world(self.mouse_right_press[0], self.mouse_right_press[1])

        if _refresh:
            self.mouse_right_press = None

        return [x, y]

    # OTHER MOUSE FUNCTIONS
    # -------------------------------------------------------------------------

    def check_mouse_scroll(self):
        if self.closed:
            return None
        else:
            self.update()
            self.mouse_scroll_amount += self.mouse_wheel_pos / 120
            self.mouse_wheel_pos = 0

            return self.mouse_scroll_amount

    def get_last_mouse(self):
        if self.last_mouse_event is not None:
            return [self.last_mouse_event[0], self.last_mouse_event[1]]
        else:
            return

    def check_mouse_motion(self, _refresh=True):
        if self.mouse_pos is not None:
            x, y = self.mouse_pos

            if _refresh:
                self.mouse_pos = None

            return [x, y]
        else:
            return

    def get_mouse_position(self):
        if self.mouse_pos is not None:
            x, y = self.mouse_pos
            return [x, y]
        else:
            return

    # Mouse Down Functions

    def check_left_mouse_down(self):
        return self.left_mouse_down

    def check_right_mouse_down(self):
        return self.right_mouse_down

    def check_middle_mouse_down(self):
        return self.middle_mouse_down

    # KEYBOARD FUNCTIONS
    # -------------------------------------------------------------------------

    def get_key_press(self):
        """Wait for user to press a key and return it as a string."""
        while self.check_key_press(_refresh=False) is None:
            self.update()
        return self.check_key_press()

    def get_key_click(self):
        """Wait for user to press a key and return it as a string."""
        while not self.check_key_click(_refresh=False):
            self.update()
        return self.check_key_click()

    def get_key_with_shift_pressed(self):
        while self.check_key_with_shift_pressed(_refresh=False) is None:
            self.update()
        return self.check_key_with_shift_pressed()

    def get_key_with_alt_pressed(self):
        while self.check_key_with_alt_pressed(_refresh=False) is None:
            self.update()
        return self.check_key_with_alt_pressed()
    
    def get_key_with_control_pressed(self):
        while self.check_key_with_control_pressed(_refresh=False) is None:
            self.update()
        return self.check_key_with_control_pressed()

    def check_key_press(self, _refresh=True):
        """Return last key pressed or None if no key pressed since last call"""
        key = self.last_key_pressed
        if _refresh:
            self.last_key_pressed = None
        return key

    def check_key_click(self, _refresh=True):
        key = self.last_key_clicked
        if _refresh:
            self.last_key_clicked = None
        return key

    def check_keys_down(self):
        return self.keys_down

    def check_key_with_shift_pressed(self, _refresh=True):
        key = self.key_pressed_with_shift
        if _refresh:
            self.key_pressed_with_shift = None
        return key

    def check_key_with_alt_pressed(self, _refresh=True):
        key = self.key_pressed_with_alt
        if _refresh:
            self.key_pressed_with_alt = None
        return key

    def check_key_with_control_pressed(self, _refresh=True):
        key = self.key_pressed_with_control
        if _refresh:
            self.key_pressed_with_control = None
        return key

    def check_for_all_keys_pressed(self, *keys, _refresh=True):
        return self.keys_down.issuperset(keys)

    def check_for_all_keys_clicked(self, *keys, _refresh=True):
        return self.keys_clicked.issuperset(keys)

    def check_for_keys_pressed(self, *keys, _refresh=True):
        for key in keys:
            if key in self.keys_down:
                return True
        return False

    def check_for_keys_clicked(self, *keys, _refresh=True):
        for key in keys:
            if key in self.keys_clicked:
                return True
        return False

    # INTERNAL FUNCTIONS
    # -------------------------------------------------------------------------

    def to_screen(self, x, y):
        if not (isinstance(x, int) or isinstance(x, float)):
            raise GraphicsError(f"X coord to convert to screen coordinate must be a number (int or float), not {x}")
        if not (isinstance(y, int) or isinstance(y, float)):
            raise GraphicsError(f"Y coord to convert to screen coordinate must be a number (int or float), not {y}")
        trans = self.trans
        if trans:
            return self.trans.screen(x, y)
        else:
            return x, y

    def to_world(self, x, y):
        if not (isinstance(x, int) or isinstance(x, float)):
            raise GraphicsError(f"X coordinate to convert to world coordinate must be a number (int or float), not {x}")
        if not (isinstance(y, int) or isinstance(y, float)):
            raise GraphicsError(f"Y coordinate to convert to world coordinate must be a number (int or float), not {y}")
        trans = self.trans
        if trans:
            return self.trans.world(x, y)
        else:
            return x, y

    def add_item(self, item):
        self.items.append(item)

    def del_item(self, item):
        self.items.remove(item)

    # Redraw everything on this window
    def redraw(self):
        for item in self.items:
            item.redraw()
        if self.autoflush:
            self.update()
        return self

    # Destroying Functions

    def destroy_all(self):
        self.delete("all")
        return self

    def destroy_item(self, item):
        self.delete(item)

    def destroy_all_instances(self, obj):
        if not issubclass(obj, GraphicsObject):
            raise GraphicsError(f"\n\nGraphicsError: obj instance to destroy must be a GraphicsObject, not {obj}")

        for instance in GraphicsObject.objects.copy():
            if isinstance(instance, obj) and instance.graphwin == self:
                instance.destroy()
        return self

    def destroy_all_lines(self):
        for instance in GraphicsObject.objects.copy():
            if "Line" in instance.__repr__() and instance.graphwin == self:
                instance.destroy()
        return self

    def destroy_all_circles(self):
        for instance in GraphicsObject.objects.copy():
            if "Circle" in instance.__repr__() and instance.graphwin == self:
                instance.destroy()
        return self

    def destroy_all_rectangles(self):
        for instance in GraphicsObject.objects.copy():
            if "Rectangle" in instance.__repr__() and instance.graphwin == self:
                instance.destroy()
        return self

    def destroy_all_ovals(self):
        for instance in GraphicsObject.objects.copy():
            if "Oval" in instance.__repr__() and instance.graphwin == self:
                instance.destroy()
        return self

    def destroy_all_images(self):
        for instance in GraphicsObject.objects.copy():
            if "Image" in instance.__repr__() and instance.graphwin == self:
                instance.destroy()
        return self
    
    def destroy_all_radiobuttons(self):
        for instance in GraphicsObject.radiobutton_instances.copy():
            GraphicsObject.objects.remove(instance)
            instance.destroy()

        GraphicsObject.radiobutton_instances = {*()}
        return self
    
    def destroy_all_cyclebuttons(self):
        for instance in GraphicsObject.cyclebutton_instances.copy():
            GraphicsObject.objects.remove(instance)
            instance.destroy()
        GraphicsObject.cyclebutton_instances = {*()}
        return self
    
    def destroy_all_entries(self):
        for instance in GraphicsObject.entry_instances.copy():
            GraphicsObject.objects.remove(instance)
            instance.destroy()
        GraphicsObject.entry_instances = {*()}
        return self

    def destroy_all_buttons(self):
        for instance in GraphicsObject.button_instances.copy():
            GraphicsObject.objects.remove(instance)
            instance.destroy()
        GraphicsObject.button_instances = {*()}
        return self
    
    def destroy_all_animated_images(self):
        for instance in GraphicsObject.animated_image_instances.copy():
            GraphicsObject.objects.remove(instance)
            instance.destroy()
        GraphicsObject.animated_image_instances = {*()}
        return self


from goopylib.objects.GraphicsObject import GraphicsObject
