from goopylib.styles import *
from goopylib.constants import *
from goopylib.constants import _root
from goopylib.math.Easing import *

from math import cos, sin, radians


class GraphicsObject:
    """Generic base class for all of the drawable objects"""

    blinking_objects = []
    resizing_objects = []
    animating_objects = {"gliding": [], "rotating": [], "fill": [], "outline": [], "width": [],
                         "skew": [], "contrast": []}

    objects = []
    button_instances = []
    slider_instances = []
    slider_instances_bound = []
    checkbox_instances = []
    cyclebutton_instances = []
    entry_instances = []

    def __init__(self, options=(), style=None, cursor="arrow", window=None):
        # options is a list of strings indicating which options are
        # legal for this object.

        # When an object is drawn, canvas is set to the GraphWin(canvas)
        #    object where it is drawn and id is the TK identifier of the
        #    drawn shape.

        if not isinstance(cursor, str):
            raise GraphicsError(f"\n\nThe cursor must be a string, not {cursor}")
        if not cursor.lower() in CURSORS.keys():
            raise GraphicsError(f"\n\nThe cursor for the window must be one of {list(CURSORS.keys())}, not {cursor}")

        self.id = None

        if style is None:
            self.style = global_style
        else:
            if style in STYLES.keys():
                self.style = style
            else:
                raise GraphicsError(f"\n\nStyle argument must be one of {STYLES.keys()}, not {style}")

        # Config is the dictionary of configuration options for the widget.
        self.config = {}
        for option in options:
            if option not in STYLES[self.style].keys():
                self.config[option] = STYLES["default"][option]
            else:
                self.config[option] = STYLES[self.style][option]

        if "width" in options:
            self.text_width = self.config["width"]

        self.selected_clicks = -1
        self.selected = False
        self.anchor = self.get_anchor()

        self.callbacks = {}

        # -------------------------------------------------------------------------
        # Animation Variables

        self.fill_queue = []
        self.outline_queue = []
        self.width_queue = []
        self.resizing_queue = []
        self.glide_queue = []
        self.rotating_queue = []
        self.skew_queue = []
        self.contrast_queue = []

        self.is_animating_width = False
        self.is_resizing = False
        self.is_gliding = False
        self.is_rotating = False
        self.is_animating_fill = False
        self.is_animating_outline = False
        self.is_animating_skew = False
        self.is_animating_contrast = False

        self.is_blinking = False
        self.blinking_interval = None
        self.last_blink_time = 0

        # -------------------------------------------------------------------------
        # Other Variables

        self.bounds = None
        self.cursor = cursor

        self.is_draggable = (False, False)
        self.is_dragging = False

        self.rotation = 0
        self.x_skew = 0
        self.y_skew = 0

        self.graphwin = None
        self.drawn = False
        if window is not None:
            self.draw(window)

        GraphicsObject.objects.append(self)

    def __repr__(self):
        return "Graphics Object"

    def _reconfig(self, option, setting):
        # Internal method for changing configuration of the object
        # Raises an error if the option does not exist in the config
        #    dictionary for this object
        if option not in self.config:
            raise GraphicsError(f"\n\nThe config you have specified ({option}) is not valid for {self}")
        options = self.config
        options[option] = setting
        if self.graphwin and not self.graphwin.is_closed():
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

    def _rotate(self, dr):
        """updates internal state of object to rotate it r degrees CCW"""
        pass  # must override in subclass

    def _update(self):
        pass  # must override in subclass

    def draw(self, graphwin):

        """Draw the object in graphwin, which should be a GraphWin
        object.  A GraphicsObject may only be drawn into one
        window. Raises an error if attempt made to draw an object that
        is already visible."""

        if graphwin.is_closed():
            return self
        if self.drawn:
            return self

        self.id = self._draw(graphwin, self.config)
        self.graphwin = graphwin
        graphwin.add_item(self)
        if graphwin.autoflush:
            _root.update()

        self.drawn = True

        return self

    def undraw(self, set_blinking=True):

        """Undraw the object (i.e. hide it). Returns silently if the
        object is not currently drawn."""
        if self.drawn:
            try:
                if not self.graphwin.is_closed():
                    self.graphwin.delete(self.id)
                    self.graphwin.del_item(self)
                    if self.graphwin.autoflush:
                        _root.update()
            except ValueError:
                return

            self.drawn = False
            self.id = None
            if self.is_blinking and set_blinking:
                self.animate_blinking(0, animate=False)
        return self

    def redraw(self):
        if self.graphwin.is_open():
            self.undraw()
            self.draw(self.graphwin)
        return self

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_clickable(self, clickable=True):
        if clickable:
            if self not in GraphicsObject.objects:
                GraphicsObject.objects.append(self)
        else:
            if self in GraphicsObject.objects:
                GraphicsObject.objects.remove(self)

        return self

    def set_draggable(self, draggable_x=True, draggable_y=None, callback_x=None, callback_y=None):
        if not isinstance(draggable_x, bool):
            raise GraphicsError(f"\n\nGraphicsError: Draggable X value must be a boolean, not {draggable_x}")
        if not (isinstance(draggable_y, bool) or draggable_y is None):
            raise GraphicsError(f"\n\nGraphicsError: Draggable Y value must be a boolean or None, not {draggable_y}")
        if not (callable(callback_x) or callback_x is None):
            raise GraphicsError(f"\n\nGraphicsError: Callback for x drag must be None or a function, not {callback_x}")
        if not (callable(callback_y) or callback_y is None):
            raise GraphicsError(f"\n\nGraphicsError: Callback for y drag must be None or a function, not {callback_y}")

        self.is_draggable = (draggable_x, draggable_x if draggable_y is None else draggable_y)
        self.callbacks["DraggingX"] = callback_x
        self.callbacks["DraggingY"] = callback_x if callback_y is None else callback_y
        return self

    def set_draggable_x(self, draggable=True, callback=None):
        if not isinstance(draggable, bool):
            raise GraphicsError(f"\n\nGraphicsError: Draggable value must be a boolean, not {draggable}")
        if not (callable(callback) or callback is None):
            raise GraphicsError(f"\n\nGraphicsError: Callback for drag must be None or a function, not {callback}")

        self.is_draggable = (draggable, self.is_draggable[1])
        self.callbacks["DraggingX"] = callback
        return self

    def set_draggable_y(self, draggable=True, callback=None):
        if not isinstance(draggable, bool):
            raise GraphicsError(f"\n\nGraphicsError: Draggable value must be a boolean, not {draggable}")
        if not (callable(callback) or callback is None):
            raise GraphicsError(f"\n\nGraphicsError: Callback for drag must be None or a function, not {callback}")

        self.is_draggable = (self.is_draggable[0], draggable)
        self.callbacks["DraggingY"] = callback
        return self

    def set_selected(self, selected=True):
        self.selected = selected

    # Config Setter Functions
    def set_fill(self, colour):
        """Set interior colour to colour"""
        self._reconfig("fill", colour)
        return self

    def set_outline(self, colour):
        """Set outline colour to colour"""
        self._reconfig("outline", colour)
        return self

    def set_outline_width(self, width):
        """Set line weight to width"""
        self._reconfig("width", width)
        self.text_width = width
        return self

    def set_cursor(self, cursor="arrow"):
        self.cursor = cursor

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_width(self):
        return 0

    def get_height(self):
        return 0

    def get_size(self):
        return self.get_width(), self.get_height()

    def get_anchor(self):
        pass

    def get_cursor(self):
        return self.cursor

    def get_config_options(self):
        return self.config.keys()

    def get_fill(self):
        """Override in GraphicsObject subclasses if fill is a valid config for them"""
        pass

    def get_outline(self):
        """Override in GraphicsObject subclasses if outline is a valid config for them"""
        pass

    def get_outline_width(self):
        """Override in GraphicsObject subclasses if outline is a valid config for them"""
        pass

    def get_x_skew(self):
        return self.x_skew

    def get_y_skew(self):
        return self.y_skew

    def get_skew(self):
        return self.x_skew, self.y_skew

    def get_rotation(self):
        return self.rotation

    # -------------------------------------------------------------------------
    # OBJECT TRANSFORMATION FUNCTIONS

    # Object Moving Functions

    def move(self, dx, dy, align="center"):

        """move object dx units in x direction and dy units in y
        direction"""

        if align == "center":
            self._move(dx, dy)
        elif align == "left":
            self._move(dx + self.get_width() / 2, dy)
        elif align == "right":
            self._move(dx - self.get_width() / 2, dy)
        elif align == "top":
            self._move(dx, dy + self.get_height() / 2)
        elif align == "bottom":
            self._move(dx, dy - self.get_height() / 2)
        elif align == "topleft":
            self._move(dx + self.get_width() / 2, dy + self.get_height() / 2)
        elif align == "topright":
            self._move(dx - self.get_width() / 2, dy + self.get_height() / 2)
        elif align == "bottomleft":
            self._move(dx + self.get_width() / 2, dy - self.get_height() / 2)
        elif align == "bottomright":
            self._move(dx - self.get_width() / 2, dy - self.get_height() / 2)
        if self.drawn:
            if self.graphwin.autoflush:
                self.graphwin.flush()
            self.redraw()
        self._update()
        return self

    def move_to(self, x, y, align="center"):
        self.move(x - self.get_anchor().x, y - self.get_anchor().y, align=align)
        return self

    def move_y(self, dy, align="center"):
        self.move(0, dy, align=align)
        return self

    def move_x(self, dx, align="center"):
        self.move(dx, 0, align=align)
        return self

    def move_to_y(self, y, align="center"):
        self.move(0, y - self.get_anchor().y, align=align)
        return self

    def move_to_x(self, x, align="center"):
        self.move(x - self.get_anchor().x, 0, align=align)
        return self

    def move_to_point(self, p, align="center"):
        self.move_to(p.x, p.y, align=align)
        return self

    def move_forward(self, d):
        self.move(d * sin(radians(self.rotation)), d * cos(radians(self.rotation)))

    def move_backward(self, d):
        self.move_forward(-d)

    def move_left(self, d):
        self.move(d * cos(radians(self.rotation)), d * sin(radians(self.rotation)))

    def move_right(self, d):
        self.move_left(-d)

    # Rotation Transformations
    def rotate(self, dr):
        self.rotation += dr
        self._rotate(dr)
        self._update()
        if self.graphwin is not None:
            self.redraw()

        return self

    def set_rotation(self, r):
        self.rotate(r - self.rotation)
        return self

    # Skewing transformations - these must be overriden in classes that support skewing

    def skew_x(self, scale=0.3, sampling="bicubic", align="center"):
        pass

    def skew_y(self, scale=0.3, sampling="bicubic", align="center"):
        pass

    def skew_xy(self, x_scale=0.3, y_scale=None, sampling="bicubic", x_align="center", y_align=None):
        pass

    def skew(self, scale=0.3, sampling="bicubic", align="center", skew_x=True, skew_y=True):
        self.skew_xy(x_scale=scale if skew_x else 0, y_scale=scale if skew_y else 0,
                     x_align=align if skew_x else "center", y_align=align if skew_y else "center",
                     sampling=sampling)

    # -------------------------------------------------------------------------
    # OBJECT ANIMATING FUNCTION

    @staticmethod
    def check_animation_exists(animations, check_animation, duplicates_metric=("Time", "Initial", "Change")):
        duplicate_exists = False
        for animation in animations:
            duplicate_exists = False
            for metric in duplicates_metric:
                if animation[metric] == animation[metric]:
                    duplicate_exists = True
                else:
                    duplicate_exists = False

            if duplicate_exists:
                return True
        return False

    def animate_blinking(self, interval, animate=True):
        self.is_blinking = animate
        self.blinking_interval = interval
        self.last_blink_time = timetime()

        if animate and self not in GraphicsObject.blinking_objects:
            GraphicsObject.blinking_objects.append(self)
        elif not animate and self in GraphicsObject.blinking_objects:
            GraphicsObject.blinking_objects.remove(self)
        return self

    # Object Gliding Functions
    def glide(self, dx, dy=None, time=1, easing_x=ease_linear(), easing_y=None, allow_duplicate=True,
              duplicates_metric=("Time", "Initial", "Change")):
        for metric in duplicates_metric:
            if metric not in DUPLICATES_METRICS["2D Animation"]:
                raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                    f"{DUPLICATES_METRICS}, not {metric}")
        if dy is None:
            dy = dx
        if easing_y is None:
            easing_y = easing_x

        self.glide_x(time=time, dx=dx, easing=easing_x, _internal_call=True, allow_duplicate=allow_duplicate,
                     duplicates_metric=duplicates_metric)
        self.glide_y(time=time, dy=dy, easing=easing_y, _internal_call=True, allow_duplicate=allow_duplicate,
                     duplicates_metric=duplicates_metric)

        animation_data = {"Time": time, "Start": timetime(), "Update": timetime(), "Initial": self.anchor.clone(),
                          "Change": Point(dx, dy), "EasingX": easing_x, "EasingY": easing_y}

        if not allow_duplicate:
            if not self.check_animation_exists(self.glide_queue, animation_data, duplicates_metric):
                self.glide_queue.append(animation_data)
        else:
            self.glide_queue.append(animation_data)

        return self

    def glide_x(self, dx, time=1, easing=ease_linear(), _internal_call=False, allow_duplicate=True,
                duplicates_metric=("Time", "Initial", "Change")):
        if not (isinstance(dx, int) or isinstance(dx, float)):
            raise GraphicsError("\n\nThe x amount to glide the object by (dx) must be a number "
                                f"(integer or float), not {dx}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to glide the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        if not _internal_call:
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["1D Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_pos = self.anchor.clone()

            for glide in self.glide_queue:
                start += glide["Time"]
                initial_pos = glide["Initial"] + glide["Change"]

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                              "Change": Point(dx, 0), "EasingX": easing, "EasingY": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.glide_queue, animation_data, duplicates_metric):
                    self.glide_queue.append(animation_data)
            else:
                self.glide_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["gliding"]:
            self.is_gliding = True
            GraphicsObject.animating_objects["gliding"].append(self)

        return self

    def glide_y(self, dy, time=1, easing=ease_linear(), _internal_call=False, allow_duplicate=True,
                duplicates_metric=("Time", "Initial", "Change")):
        if not (isinstance(dy, int) or isinstance(dy, float)):
            raise GraphicsError("\n\nThe y amount to glide the object by (dy) must be a number "
                                f"(integer or float), not {dy}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to glide the object for (time) must be a number "
                                f"(integer or float), not {time}")

        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        if not _internal_call:
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["1D Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_pos = self.anchor.clone()

            for glide in self.glide_queue:
                start += glide["Time"]
                initial_pos = glide["Initial"] + glide["Change"]

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                              "Change": Point(0, dy), "EasingX": easing, "EasingY": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.glide_queue, animation_data, duplicates_metric):
                    self.glide_queue.append(animation_data)
            else:
                self.glide_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["gliding"]:
            self.is_gliding = True
            GraphicsObject.animating_objects["gliding"].append(self)

        return self

    def glide_to(self, x, y=None, time=1, easing_x=ease_linear(), easing_y=None, allow_duplicate=True,
                 duplicates_metric=("Time", "Initial", "Change")):
        for metric in duplicates_metric:
            if metric not in DUPLICATES_METRICS["2D Animation"]:
                raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                    f"{DUPLICATES_METRICS}, not {metric}")

        if y is None:
            y = x
        if easing_y is None:
            easing_y = easing_x

        self.glide_x(time=time, dx=x - self.anchor.x, easing=easing_x, _internal_call=True,
                     allow_duplicate=allow_duplicate, duplicates_metric=duplicates_metric)
        self.glide_y(time=time, dy=y - self.anchor.y, easing=easing_y, _internal_call=True,
                     allow_duplicate=allow_duplicate, duplicates_metric=duplicates_metric)

        start = timetime()
        initial_pos = self.anchor.clone()
        for glide in self.glide_queue:
            start += glide["Time"]
            initial_pos = glide["Initial"] + glide["Change"]

        animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                          "Change": Point(x, y) - initial_pos, "EasingX": easing_x, "EasingY": easing_y}

        if not allow_duplicate:
            if not self.check_animation_exists(self.glide_queue, animation_data, duplicates_metric):
                self.glide_queue.append(animation_data)
        else:
            self.glide_queue.append(animation_data)

        return self

    def glide_to_x(self, x, time=1, easing=ease_linear(), allow_duplicate=True,
                   duplicates_metric=("Time", "Initial", "Change")):
        self.glide_x(time=time, dx=x - self.anchor.x, easing=easing, allow_duplicate=allow_duplicate,
                     duplicates_metric=duplicates_metric)
        return self

    def glide_to_y(self, y, time=1, easing=ease_linear(), allow_duplicate=True,
                   duplicates_metric=("Time", "Initial", "Change")):
        self.glide_y(time=time, dy=y - self.anchor.y, easing=easing, allow_duplicate=allow_duplicate,
                     duplicates_metric=duplicates_metric)
        return self

    def glide_to_point(self, p, time=1, easing_x=ease_linear(), easing_y=None, allow_duplicate=True,
                       duplicates_metric=("Time", "Initial", "Change")):
        self.glide_to(x=p.x, y=p.y, time=time, easing_x=easing_x, easing_y=easing_y, allow_duplicate=allow_duplicate,
                      duplicates_metric=duplicates_metric)
        return self

    # Rotating Animations
    def animate_rotate(self, dr, time=1, easing=ease_linear(), allow_duplicate=True,
                       duplicates_metric=("Time", "Initial", "Change")):
        if not (isinstance(dr, int) or isinstance(dr, float)):
            raise GraphicsError("\n\nGraphicsError: The amount to rotate the object by (dr) must be a number "
                                f"(integer or float), not {dr}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nGraphicsError: The time to rotate the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid Function")
        for metric in duplicates_metric:
            if metric not in DUPLICATES_METRICS["1D Animation"]:
                raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                    f"{DUPLICATES_METRICS}, not {metric}")

        start = timetime()
        initial_rotation = self.rotation

        for rotation in self.rotating_queue:
            start += rotation["Time"]
            initial_pos = rotation["Initial"] + rotation["Change"]

        animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_rotation,
                          "Change": dr, "Easing": easing}

        if not allow_duplicate:
            if not self.check_animation_exists(self.rotating_queue, animation_data, duplicates_metric):
                self.rotating_queue.append(animation_data)
        else:
            self.rotating_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["rotating"]:
            GraphicsObject.animating_objects["rotating"].append(self)
            self.is_rotating = True
        return self

    def animate_set_rotation(self, r, time=1, easing=ease_linear(), allow_duplicate=True,
                             duplicates_metric=("Time", "Initial", "Change")):
        self.animate_rotate(r - self.rotation, time=time, easing=easing, allow_duplicate=allow_duplicate,
                            duplicates_metric=duplicates_metric)
        return self

    # Colour Animations
    def animate_change_fill(self, colour_change, time=1, easing=ease_linear(), allow_duplicate=True,
                            duplicates_metric=("Time", "Initial", "Change")):
        if "fill" in self.config.keys():
            if not isinstance(colour_change, tuple):
                raise GraphicsError("\n\nGraphicsError: The colour change for the animation (colour_change) must be a "
                                    f"tuple of length 3 (r, g, b), not {colour_change}")
            if not (isinstance(time, int) or isinstance(time, float)):
                raise GraphicsError("\n\nGraphicsError: The time to rotate the object for (time) must be a number "
                                    f"(integer or float), not {time}")
            if not callable(easing):
                raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid "
                                    f"function")
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["Colour Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_fill = self.get_fill()

            for animation in self.fill_queue:
                start += animation["Time"]
                initial_fill = ColourRGB(animation["Initial"][0] + animation["Change"][0],
                                         animation["Initial"][1] + animation["Change"][1],
                                         animation["Initial"][2] + animation["Change"][2], )

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_fill,
                              "Change": colour_change, "Easing": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.fill_queue, animation_data, duplicates_metric):
                    self.fill_queue.append(animation_data)
            else:
                self.fill_queue.append(animation_data)

            if self not in GraphicsObject.animating_objects["fill"]:
                GraphicsObject.animating_objects["fill"].append(self)
                self.is_animating_fill = True
            return self

        else:
            raise GraphicsError("\n\nGraphicsError: This object doesn't support colour fill animations")

    def animate_set_fill(self, end_colour, time=1, easing=ease_linear(), allow_duplicate=True,
                         duplicates_metric=("Time", "Initial", "Change")):
        if "fill" in self.config.keys():

            initial_fill = self.get_fill()
            for animation in self.fill_queue:
                initial_fill = ColourRGB(animation["Initial"][0] + animation["Change"][0],
                                         animation["Initial"][1] + animation["Change"][1],
                                         animation["Initial"][2] + animation["Change"][2], )

            self.animate_change_fill((end_colour[0] - initial_fill[0],
                                      end_colour[1] - initial_fill[1],
                                      end_colour[2] - initial_fill[2],), time=time, easing=easing,
                                     allow_duplicate=allow_duplicate, duplicates_metric=duplicates_metric)
            return self
        else:
            raise GraphicsError("\n\nGraphicsError: This object doesn't support colour fill animations")

    def animate_change_outline(self, colour_change, time=1, easing=ease_linear(), allow_duplicate=True,
                               duplicates_metric=("Time", "Initial", "Change")):
        if "outline" in self.config.keys():
            if not isinstance(colour_change, tuple):
                raise GraphicsError("\n\nGraphicsError: The colour change for the animation (colour_change) must be a "
                                    f"tuple of length 3 (r, g, b), not {colour_change}")
            if not (isinstance(time, int) or isinstance(time, float)):
                raise GraphicsError("\n\nGraphicsError: The time to rotate the object for (time) must be a number "
                                    f"(integer or float), not {time}")
            if not callable(easing):
                raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid "
                                    f"function")
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["Colour Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_outline = self.get_outline()

            for animation in self.outline_queue:
                start += animation["Time"]
                initial_outline = ColourRGB(animation["Initial"][0] + animation["Change"][0],
                                            animation["Initial"][1] + animation["Change"][1],
                                            animation["Initial"][2] + animation["Change"][2], )

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_outline,
                              "Change": colour_change, "Easing": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.outline_queue, animation_data, duplicates_metric):
                    self.outline_queue.append(animation_data)
            else:
                self.outline_queue.append(animation_data)

            if self not in GraphicsObject.animating_objects["outline"]:
                GraphicsObject.animating_objects["outline"].append(self)
                self.is_animating_outline = True

            return self

        else:
            raise GraphicsError("\n\nGraphicsError: This object doesn't support colour outline animations")

    def animate_set_outline(self, end_colour, time=1, easing=ease_linear(), allow_duplicate=True,
                            duplicates_metric=("Time", "Initial", "Change")):
        if "outline" in self.config.keys():

            initial_outline = self.get_outline()
            for animation in self.outline_queue:
                initial_outline = ColourRGB(animation["Initial"][0] + animation["Change"][0],
                                            animation["Initial"][1] + animation["Change"][1],
                                            animation["Initial"][2] + animation["Change"][2])

            self.animate_change_outline((end_colour[0] - initial_outline[0],
                                         end_colour[1] - initial_outline[1],
                                         end_colour[2] - initial_outline[2],), time=time, easing=easing,
                                        allow_duplicate=allow_duplicate, duplicates_metric=duplicates_metric)
            return self
        else:
            raise GraphicsError("\n\nGraphicsError: This object doesn't support colour outline animations")

    # Outline Width Animations
    def animate_change_outline_width(self, width_change, time=1, easing=ease_linear(), allow_duplicate=True,
                                     duplicates_metric=("Time", "Initial", "Change")):
        if not (isinstance(width_change, int) or isinstance(width_change, float)):
            raise GraphicsError("\n\nGraphicsError: The amount to change the outline width by (width_change) must be a "
                                f"number (integer or float), not {width_change}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nGraphicsError: The time to outline_width the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid Function")

        start = timetime()
        initial_width = self.get_outline_width()

        for animation in self.width_queue:
            start += animation["Time"]
            initial_pos = animation["Initial"] + animation["Change"]

        animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_width,
                          "Change": width_change, "Easing": easing}

        if not allow_duplicate:
            if not self.check_animation_exists(self.width_queue, animation_data, duplicates_metric):
                self.width_queue.append(animation_data)
        else:
            self.width_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["width"]:
            GraphicsObject.animating_objects["width"].append(self)
            self.is_animating_width = True
        return self

    def animate_set_outline_width(self, width_change, time=1, easing=ease_linear(), allow_duplicate=True,
                                  duplicates_metric=("Time", "Initial", "Change")):
        self.animate_change_outline_width(width_change - self.get_outline_width(), time=time, easing=easing,
                                          allow_duplicate=allow_duplicate, duplicates_metric=duplicates_metric)
        return self

    # Skew Animations
    def animate_skew_x(self, skew_change, time=1, easing=ease_linear(), allow_duplicate=True,
                       duplicates_metric=("Time", "Initial", "Change"), _internal_call=False):
        if not (isinstance(skew_change, int) or isinstance(skew_change, float)):
            raise GraphicsError("\n\nGraphicsError: The amount to change the skew by (skew_change) must be a "
                                f"number (integer or float), not {skew_change}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nGraphicsError: The time to skew the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid Function")

        if not _internal_call:
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["1D Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_skew = [self.y_skew, self.x_skew]

            for animation in self.skew_queue:
                start += animation["Time"]
                initial_skew[1] = animation["Initial"][1] + animation["Change"][1]
                initial_skew[0] = animation["Initial"][0] + animation["Change"][0]

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_skew,
                              "Change": (skew_change, 0), "EasingX": easing, "EasingY": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.skew_queue, animation_data, duplicates_metric):
                    self.skew_queue.append(animation_data)
            else:
                self.skew_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["skew"]:
            self.is_animating_skew = True
            GraphicsObject.animating_objects["skew"].append(self)

        return self

    def animate_skew_y(self, skew_change, time=1, easing=ease_linear(), allow_duplicate=True,
                       duplicates_metric=("Time", "Initial", "Change"), _internal_call=False):
        if not (isinstance(skew_change, int) or isinstance(skew_change, float)):
            raise GraphicsError("\n\nGraphicsError: The amount to change the skew by (skew_change) must be a "
                                f"number (integer or float), not {skew_change}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nGraphicsError: The time to skew the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid Function")

        if not _internal_call:
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["1D Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_skew = [self.y_skew, self.x_skew]

            for animation in self.skew_queue:
                start += animation["Time"]
                initial_skew[1] = animation["Initial"][1] + animation["Change"][1]
                initial_skew[0] = animation["Initial"][0] + animation["Change"][0]

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_skew,
                              "Change": (0, skew_change), "EasingX": easing, "EasingY": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.skew_queue, animation_data, duplicates_metric):
                    self.skew_queue.append(animation_data)
            else:
                self.skew_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["skew"]:
            self.is_animating_skew = True
            GraphicsObject.animating_objects["skew"].append(self)

        return self

    def animate_skew(self, skew_change_x, skew_change_y, time=1, easing_x=ease_linear(), easing_y=ease_linear(),
                     allow_duplicate=True, duplicates_metric=("Time", "Initial", "Change"), _internal_call=False):
        if not (isinstance(skew_change_x, int) or isinstance(skew_change_x, float)):
            raise GraphicsError("\n\nGraphicsError: The amount to skew in the x direction (skew_change_x) must be a "
                                f"number (integer or float), not {skew_change_x}")
        if not (isinstance(skew_change_y, int) or isinstance(skew_change_y, float)):
            raise GraphicsError("\n\nGraphicsError: The amount to skew in the y direction (skew_change_y) must be a "
                                f"number (integer or float), not {skew_change_y}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nGraphicsError: The time to skew the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing_x):
            raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing_x}) is not a valid Function")
        if not callable(easing_y):
            raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing_y}) is not a valid Function")

        if not _internal_call:
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["2D Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_skew = [self.y_skew, self.x_skew]

            for animation in self.skew_queue:
                start += animation["Time"]
                initial_skew[1] = animation["Initial"][1] + animation["Change"][1]
                initial_skew[0] = animation["Initial"][0] + animation["Change"][0]

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_skew,
                              "Change": (skew_change_x, skew_change_y), "EasingX": easing_x, "EasingY": easing_y}

            if not allow_duplicate:
                if not self.check_animation_exists(self.skew_queue, animation_data, duplicates_metric):
                    self.skew_queue.append(animation_data)
            else:
                self.skew_queue.append(animation_data)

        if self not in GraphicsObject.animating_objects["skew"]:
            self.is_animating_skew = True
            GraphicsObject.animating_objects["skew"].append(self)

        return self

    # Image Specific Functions
    def animate_change_contrast(self, contrast_change, time=1, easing=ease_linear(), allow_duplicate=True,
                                duplicates_metric=("Time", "Initial", "Change")):
        if isinstance(self, Image):
            if not (isinstance(contrast_change, int) or isinstance(contrast_change, float)):
                raise GraphicsError("\n\nGraphicsError: The contrast change for the animation (contrast_change) must be"
                                    f" an integer or float not {contrast_change}")
            if not (isinstance(time, int) or isinstance(time, float)):
                raise GraphicsError("\n\nGraphicsError: The time to change the contrast of the object for (time) must "
                                    f"be a number (integer or float), not {time}")
            if not callable(easing):
                raise GraphicsError(f"\n\nGraphicsError: The Easing Function Provided ({easing}) is not a valid "
                                    f"function")
            for metric in duplicates_metric:
                if metric not in DUPLICATES_METRICS["1D Animation"]:
                    raise GraphicsError("\n\nGraphicsError: Metric in duplicates_metric must be one of "
                                        f"{DUPLICATES_METRICS}, not {metric}")

            start = timetime()
            initial_fill = self.get_contrast()

            for animation in self.fill_queue:
                start += animation["Time"]
                initial_fill = ColourRGB(animation["Initial"][0] + animation["Change"][0],
                                         animation["Initial"][1] + animation["Change"][1],
                                         animation["Initial"][2] + animation["Change"][2], )

            animation_data = {"Time": time, "Start": start, "Update": timetime(), "Initial": initial_fill,
                              "Change": contrast_change, "Easing": easing}

            if not allow_duplicate:
                if not self.check_animation_exists(self.contrast_queue, animation_data, duplicates_metric):
                    self.contrast_queue.append(animation_data)
            else:
                self.contrast_queue.append(animation_data)

            if self not in GraphicsObject.animating_objects["contrast"]:
                GraphicsObject.animating_objects["contrast"].append(self)
                self.is_animating_contrast = True
            return self
        else:
            raise GraphicsError("\n\nGraphicsError: This object doesn't support the contrast animation")

    def animate_set_contrast(self, contrast, time=1, easing=ease_linear(), allow_duplicate=True,
                             duplicates_metric=("Time", "Initial", "Change")):
        if isinstance(self, Image):
            self.animate_change_contrast(contrast - self.contrast, time=time, easing=easing, allow_duplicate=allow_duplicate,
                                         duplicates_metric=duplicates_metric)
            return self
        else:
            raise GraphicsError("\n\nGraphicsError: This object doesn't support the contrast animation")

    # Object Outline Width Animations
    # -------------------------------------------------------------------------
    # OTHER FUNCTIONS

    def is_selected(self):
        selected = self.is_clicked(self.graphwin.get_last_mouse())
        if selected:
            self.selected_clicks = self.graphwin.left_mouse_clicks

        return selected or self.selected_clicks == self.graphwin.left_mouse_clicks

    def is_clicked(self, mouse_pos):
        return False

    # -------------------------------------------------------------------------
    # STATIC METHODS
    # These are called by the GraphWin to update the GraphicsObjects

    @staticmethod
    def on_update(graphwin):
        t = timetime()
        for obj in GraphicsObject.animating_objects["gliding"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.glide_queue[0]["Start"] >= obj.glide_queue[0]["Time"]:
                    obj.move_to(obj.glide_queue[0]["Initial"].x + obj.glide_queue[0]["Change"].x,
                                obj.glide_queue[0]["Initial"].y + obj.glide_queue[0]["Change"].y)

                    obj.glide_queue.pop(0)  # Remove the object from the gliding queue
                    if len(obj.glide_queue) == 0:
                        obj.is_gliding = False
                        GraphicsObject.animating_objects["gliding"].remove(obj)
                else:
                    perX = obj.glide_queue[0]["EasingX"]((t - obj.glide_queue[0]['Start']) / obj.glide_queue[0]['Time'])
                    perY = obj.glide_queue[0]["EasingY"]((t - obj.glide_queue[0]['Start']) / obj.glide_queue[0]['Time'])

                    obj.move_to(obj.glide_queue[0]["Initial"].x + obj.glide_queue[0]["Change"].x * perX,
                                obj.glide_queue[0]["Initial"].y + obj.glide_queue[0]["Change"].y * perY)
                    obj.glide_queue[0]["Update"] = timetime()

        for obj in GraphicsObject.animating_objects["rotating"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.rotating_queue[0]["Start"] >= obj.rotating_queue[0]["Time"]:
                    obj.set_rotation(obj.rotating_queue[0]["Initial"] + obj.rotating_queue[0]["Change"])
                    obj.rotating_queue.pop(0)

                    if len(obj.rotating_queue) == 0:
                        obj.is_rotating = False
                        GraphicsObject.animating_objects["rotating"].remove(obj)
                else:
                    per = obj.rotating_queue[0]["Easing"]((t - obj.rotating_queue[0]["Start"])
                                                          / obj.rotating_queue[0]["Time"])
                    obj.set_rotation(obj.rotating_queue[0]["Initial"] + obj.rotating_queue[0]["Change"] * per)
                    obj.rotating_queue[0]["Update"] = timetime()

        for obj in GraphicsObject.blinking_objects:
            if obj.graphwin == graphwin:
                if t - obj.last_blink > obj.blinking_interval:
                    if obj.drawn:
                        obj.undraw(set_blinking=False)
                    else:
                        obj.draw(graphwin)
                    obj.last_blink = t

        for obj in GraphicsObject.animating_objects["fill"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.fill_queue[0]["Start"] >= obj.fill_queue[0]["Time"]:

                    obj.set_fill(ColourRGB(
                        max([min([obj.fill_queue[0]["Initial"][0] + obj.fill_queue[0]["Change"][0], 255]), 0]),
                        max([min([obj.fill_queue[0]["Initial"][1] + obj.fill_queue[0]["Change"][1], 255]), 0]),
                        max([min([obj.fill_queue[0]["Initial"][2] + obj.fill_queue[0]["Change"][2], 255]), 0])))
                    obj.fill_queue.pop(0)

                    if len(obj.fill_queue) == 0:
                        obj.is_animating_fill = False
                        GraphicsObject.animating_objects["fill"].remove(obj)
                else:
                    per = obj.fill_queue[0]["Easing"]((t - obj.fill_queue[0]["Start"])
                                                      / obj.fill_queue[0]["Time"])

                    red_change = int(obj.fill_queue[0]["Change"][0] * per)
                    blue_change = int(obj.fill_queue[0]["Change"][1] * per)
                    green_change = int(obj.fill_queue[0]["Change"][2] * per)

                    obj.set_fill(ColourRGB(max([min([obj.fill_queue[0]["Initial"][0] + red_change, 255]), 0]),
                                           max([min([obj.fill_queue[0]["Initial"][1] + blue_change, 255]), 0]),
                                           max([min([obj.fill_queue[0]["Initial"][2] + green_change, 255]), 0])))
                    obj.fill_queue[0]["Update"] = timetime()

        for obj in GraphicsObject.animating_objects["outline"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.outline_queue[0]["Start"] >= obj.outline_queue[0]["Time"]:

                    obj.set_outline(ColourRGB(
                        max([min([obj.outline_queue[0]["Initial"][0] + obj.outline_queue[0]["Change"][0], 255]), 0]),
                        max([min([obj.outline_queue[0]["Initial"][1] + obj.outline_queue[0]["Change"][1], 255]), 0]),
                        max([min([obj.outline_queue[0]["Initial"][2] + obj.outline_queue[0]["Change"][2], 255]), 0])))
                    obj.outline_queue.pop(0)

                    if len(obj.outline_queue) == 0:
                        obj.is_animating_outline = False
                        GraphicsObject.animating_objects["outline"].remove(obj)
                else:
                    per = obj.outline_queue[0]["Easing"]((t - obj.outline_queue[0]["Start"])
                                                         / obj.outline_queue[0]["Time"])

                    red_change = int(obj.outline_queue[0]["Change"][0] * per)
                    blue_change = int(obj.outline_queue[0]["Change"][1] * per)
                    green_change = int(obj.outline_queue[0]["Change"][2] * per)

                    obj.set_outline(ColourRGB(max([min([obj.outline_queue[0]["Initial"][0] + red_change, 255]), 0]),
                                              max([min([obj.outline_queue[0]["Initial"][1] + blue_change, 255]), 0]),
                                              max([min([obj.outline_queue[0]["Initial"][2] + green_change, 255]), 0])))
                    obj.outline_queue[0]["Update"] = timetime()

        for obj in GraphicsObject.animating_objects["width"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.width_queue[0]["Start"] >= obj.width_queue[0]["Time"]:
                    obj.set_outline_width(obj.width_queue[0]["Initial"] + obj.width_queue[0]["Change"])
                    obj.width_queue.pop(0)

                    if len(obj.width_queue) == 0:
                        obj.is_width = False
                        GraphicsObject.animating_objects["width"].remove(obj)
                else:
                    per = obj.width_queue[0]["Easing"]((t - obj.width_queue[0]["Start"])
                                                          / obj.width_queue[0]["Time"])
                    obj.set_outline_width(obj.width_queue[0]["Initial"] + obj.width_queue[0]["Change"] * per)
                    obj.width_queue[0]["Update"] = timetime()

        for obj in GraphicsObject.animating_objects["skew"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.skew_queue[0]["Start"] >= obj.skew_queue[0]["Time"]:
                    obj.skew_xy(obj.skew_queue[0]["Initial"][0] + obj.skew_queue[0]["Change"][0],
                                obj.skew_queue[0]["Initial"][1] + obj.skew_queue[0]["Change"][1])

                    obj.skew_queue.pop(0)  # Remove the object from the skewing queue
                    if len(obj.skew_queue) == 0:
                        obj.is_animating_skew = False
                        GraphicsObject.animating_objects["skew"].remove(obj)
                else:
                    perX = obj.skew_queue[0]["EasingX"]((t - obj.skew_queue[0]['Start']) / obj.skew_queue[0]['Time'])
                    perY = obj.skew_queue[0]["EasingY"]((t - obj.skew_queue[0]['Start']) / obj.skew_queue[0]['Time'])

                    obj.skew_xy(obj.skew_queue[0]["Initial"][0] + obj.skew_queue[0]["Change"][0] * perX,
                                obj.skew_queue[0]["Initial"][1] + obj.skew_queue[0]["Change"][1] * perY)
                    obj.skew_queue[0]["Update"] = timetime()
                    
        for obj in GraphicsObject.animating_objects["contrast"]:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.contrast_queue[0]["Start"] >= obj.contrast_queue[0]["Time"]:
                    obj.set_contrast(obj.contrast_queue[0]["Initial"] + obj.contrast_queue[0]["Change"])
                    obj.contrast_queue.pop(0)

                    if len(obj.contrast_queue) == 0:
                        obj.is_animating_contrast = False
                        GraphicsObject.animating_objects["contrast"].remove(obj)
                else:
                    per = obj.contrast_queue[0]["Easing"]((t - obj.contrast_queue[0]["Start"])
                                                          / obj.contrast_queue[0]["Time"])
                    obj.set_contrast(obj.contrast_queue[0]["Initial"] + obj.contrast_queue[0]["Change"] * per)
                    obj.contrast_queue[0]["Update"] = timetime()

        GraphicsObject.on_mouse_motion(graphwin=graphwin)

    @staticmethod
    def on_left_click(graphwin):
        mouse_pos = graphwin.get_last_mouse()

        for obj in GraphicsObject.slider_instances:
            if obj.graphwin == graphwin:
                if obj.line.is_clicked(mouse_pos):
                    if obj.orientation == "vertical":
                        obj.mouse_value(mouse_pos.y)
                    else:
                        obj.mouse_value(mouse_pos.x)

                obj.set_selected(False)

        for obj in GraphicsObject.button_instances:
            if obj.graphwin == graphwin and obj.graphic == obj.clicked_graphic and obj.drawn:
                obj.undraw()
                if not obj.is_disabled:
                    obj.graphic = obj.normal_graphic
                obj.draw(obj.graphwin)

        for obj in GraphicsObject.checkbox_instances:
            if obj.graphwin == graphwin and obj.autoflush:
                if obj.is_clicked(mouse_pos):
                    obj.click()

        for obj in GraphicsObject.cyclebutton_instances:
            if obj.graphwin == graphwin and obj.autoflush:
                if obj.is_clicked(mouse_pos):
                    obj.click()

    @staticmethod
    def on_middle_click(graphwin):
        pass

    @staticmethod
    def on_right_click(graphwin):
        pass

    @staticmethod
    def on_left_press(graphwin):
        mouse_pos = graphwin.check_left_mouse_press(_refresh=False)

        for obj in GraphicsObject.slider_instances:
            if obj.graphwin == graphwin:
                if obj.is_clicked(mouse_pos):
                    obj.set_selected()

        for obj in GraphicsObject.button_instances:
            if obj.graphwin == graphwin and obj.drawn:
                if obj.is_clicked(mouse_pos):
                    obj.graphic.undraw()
                    obj.graphic = obj.clicked_graphic
                    obj._draw(obj.graphwin, ())

        for obj in GraphicsObject.resizing_objects:
            if obj.graphwin == graphwin:
                for bound in obj.resizing_bounds:
                    if obj.resizing_bounds[bound].is_clicked(mouse_pos):
                        obj.is_resizing[bound] = True
                        obj.resizing_anchor = obj.get_anchor()
                        obj.resizing_initial_size = obj.width, obj.height
                    else:
                        obj.is_resizing[bound] = False

        for obj in GraphicsObject.objects:
            if obj.graphwin == graphwin:
                if obj.is_draggable and obj.is_clicked(mouse_pos):
                    obj.is_dragging = True

    @staticmethod
    def on_middle_press(graphwin):
        pass

    @staticmethod
    def on_right_press(graphwin):
        pass

    @staticmethod
    def on_mouse_motion(graphwin):
        if graphwin.is_open():
            mouse_pos = graphwin.check_mouse_motion(_refresh=False)

            for obj in GraphicsObject.button_instances:
                if obj.graphwin == graphwin and obj.drawn:
                    if obj.is_clicked(mouse_pos):
                        if not graphwin.left_mouse_down:
                            if obj.graphic != obj.hover_graphic:
                                obj.undraw()
                                obj.graphic = obj.hover_graphic
                                obj.draw(graphwin)
                        else:
                            if obj.graphic != obj.clicked_graphic:
                                obj.undraw()
                                obj.graphic = obj.clicked_graphic
                                obj.draw(graphwin)

                    elif obj.graphic != obj.normal_graphic and not obj.is_disabled:
                        obj.undraw()
                        obj.graphic = obj.normal_graphic
                        obj.draw(graphwin)

            for obj in GraphicsObject.slider_instances:
                if obj.graphwin == graphwin:
                    if obj.selected:
                        if obj.orientation == "vertical":
                            obj.mouse_value(mouse_pos.y)
                        else:
                            obj.mouse_value(mouse_pos.x)

            hover_count = 0
            for obj in GraphicsObject.objects:
                if obj.graphwin == graphwin and graphwin.is_open():
                    if obj.is_clicked(mouse_pos):
                        graphwin.config(cursor=CURSORS[obj.cursor])
                        hover_count += 1

                    if obj.is_dragging:
                        if graphwin.left_mouse_down:
                            if obj.is_draggable[0]:
                                obj.move_to_x(mouse_pos.x)
                                if obj.callbacks["DraggingX"] is not None:
                                    obj.callbacks["DraggingX"]()
                            if obj.is_draggable[1]:
                                obj.move_to_y(mouse_pos.y)
                                if obj.callbacks["DraggingY"] is not None:
                                    obj.callbacks["DraggingY"]()
                        else:
                            obj.is_dragging = False

            if hover_count == 0:
                graphwin.set_cursor(graphwin.cursor)

            if graphwin.left_mouse_down:
                for obj in GraphicsObject.slider_instances:
                    if obj.graphwin == graphwin and obj.is_clicked(graphwin.get_last_mouse()):
                        if obj.orientation == "vertical":
                            obj.mouse_value(mouse_pos.y)
                        else:
                            obj.mouse_value(mouse_pos.x)

                for obj in GraphicsObject.resizing_objects:
                    if obj.graphwin == graphwin:
                        for bound in obj.resizing_bounds:
                            if obj.is_resizing[bound]:
                                if bound in ["left", "right"]:

                                    w = obj.min_width

                                    dir1 = "right"
                                    dir2 = "left"
                                    if bound == "left":
                                        if mouse_pos.x < obj.resizing_anchor.x + obj.resizing_initial_size[0] / 2 \
                                                - obj.min_width:
                                            w = obj.resizing_anchor.x - mouse_pos.x + obj.resizing_initial_size[0] / 2
                                            obj.resizing_bounds[dir2].move_to_x(mouse_pos.x)
                                        else:
                                            obj.resizing_bounds[dir2].move_to_x(obj.p1.x)

                                    elif bound == "right":
                                        dir1, dir2 = dir2, dir1
                                        if mouse_pos.x > obj.resizing_anchor.x - obj.resizing_initial_size[0] / 2 \
                                                + obj.min_width:
                                            w = mouse_pos.x - obj.resizing_anchor.x + obj.resizing_initial_size[0] / 2
                                            obj.resizing_bounds[dir2].move_to_x(mouse_pos.x)
                                        else:
                                            obj.resizing_bounds[dir2].move_to_x(obj.p2.x)

                                    obj.set_width(w, dir1)

                                    obj.resizing_bounds["top"].set_width(w + obj.bounds_thickness, dir1)
                                    obj.resizing_bounds["bottom"].set_width(w + obj.bounds_thickness, dir1)

                                else:
                                    dir1 = "bottom"
                                    dir2 = "top"
                                    if bound == "top":
                                        if mouse_pos.y < obj.resizing_anchor.y + obj.resizing_initial_size[1] / 2 \
                                                - obj.min_height:
                                            h = obj.resizing_anchor.y - mouse_pos.y + obj.resizing_initial_size[1] / 2
                                            obj.resizing_bounds[dir2].move_to_y(mouse_pos.y)
                                        else:
                                            h = obj.min_height
                                            obj.resizing_bounds[dir2].move_to_y(obj.p1.y)
                                    else:
                                        dir1, dir2 = dir2, dir1
                                        if mouse_pos.y > obj.resizing_anchor.y - obj.resizing_initial_size[1] / 2 \
                                                + obj.min_height:
                                            h = mouse_pos.y - obj.resizing_anchor.y + obj.resizing_initial_size[1] / 2
                                            obj.resizing_bounds[dir2].move_to_y(mouse_pos.y)
                                        else:
                                            h = obj.min_height
                                            obj.resizing_bounds[dir2].move_to_y(obj.p2.y)

                                    obj.set_height(h, dir1)

                                    obj.resizing_bounds["left"].set_height(h + obj.bounds_thickness, dir1)
                                    obj.resizing_bounds["right"].set_height(h + obj.bounds_thickness, dir1)

    @staticmethod
    def on_double_left_click(graphwin):
        pass

    @staticmethod
    def on_double_middle_click(graphwin):
        pass

    @staticmethod
    def on_double_right_click(graphwin):
        pass

    @staticmethod
    def on_triple_left_click(graphwin):
        pass

    @staticmethod
    def on_triple_middle_click(graphwin):
        pass

    @staticmethod
    def on_triple_right_click(graphwin):
        pass

    @staticmethod
    def on_mouse_scroll(e, graphwin):
        for obj in GraphicsObject.slider_instances_bound:
            if obj.graphwin == graphwin:
                if obj.range[0] < int(obj.get_value() + e) < obj.range[1]:
                    obj.set_value(int(obj.get_value() + e))

from goopylib.objects.Image import Image
