from goopylib.Point import Point

from goopylib.styles import *
from goopylib.constants import *
from goopylib.constants import _root
from goopylib.math.Easing import *


class GraphicsObject:
    """Generic base class for all of the drawable objects"""
    gliding_objects = []
    rotating_objects = []
    resizing_objects = []
    blinking_objects = []

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

        self.id = None

        if style is not None:
            self.style = style
        else:
            self.style = global_style

        # config is the dictionary of configuration options for the widget.
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

        self.is_gliding = False
        self.glide_queue = []

        self.callbacks = {}

        self.rotating_queue = []
        self.is_rotating = False
        self.rotation = 0

        self.is_draggable = False
        self.is_dragging = False

        self.resizing_factor = None
        self.resizing_easing = None
        self.is_resizing = None

        self.resizing_time = None
        self.resizing_update = None
        self.resizing_start = None
        self.resizing_args = None

        self.is_blinking = False
        self.blinking_interval = None
        self.last_blink_time = 0

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

    def set_clickable(self, clickable=True):
        if clickable:
            if self not in GraphicsObject.objects:
                GraphicsObject.objects.append(self)
        else:
            if self in GraphicsObject.objects:
                GraphicsObject.objects.remove(self)

        return self

    def set_draggable(self, draggable=True, callback=None):
        self.is_draggable = draggable
        self.callbacks["Dragging"] = callback
        return self

    def set_selected(self, selected=True):
        self.selected = selected

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

    def get_width(self):
        return 0

    def get_height(self):
        return 0

    def set_cursor(self, cursor="arrow"):
        self.cursor = cursor

    def get_anchor(self):
        pass

    def animate_blinking(self, interval, animate=True):
        self.is_blinking = animate
        self.blinking_interval = interval
        self.last_blink_time = timetime()

        if animate and self not in GraphicsObject.blinking_objects:
            GraphicsObject.blinking_objects.append(self)
        elif not animate and self in GraphicsObject.blinking_objects:
            GraphicsObject.blinking_objects.remove(self)

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

    # Object Gliding Functions

    def glide(self, dx, dy=None, time=1, easing_x=ease_linear(), easing_y=None):
        if dy is None:
            dy = dx
        if easing_y is None:
            easing_y = easing_x

        self.glide_x(time=time, dx=dx, easing=easing_x, _internal_call=True)
        self.glide_y(time=time, dy=dy, easing=easing_y, _internal_call=True)

        self.glide_queue.append({"Time": time, "Start": timetime(), "Update": timetime(), "Initial": self.anchor.clone(),
                                 "Dist": Point(dx, dy), "EasingX": easing_x, "EasingY": easing_y})

        return self

    def glide_x(self, dx, time=1, easing=ease_linear(), _internal_call=False):
        if not (isinstance(dx, int) or isinstance(dx, float)):
            raise GraphicsError("\n\nThe x amount to glide the object by (dx) must be a number "
                                f"(integer or float), not {dx}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to glide the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        self.is_gliding = True
        if not _internal_call:
            start = timetime()
            initial_pos = self.anchor.clone()

            for glide in self.glide_queue:
                start += glide["Time"]
                initial_pos = glide["Initial"] + glide["Dist"]

            self.glide_queue.append({"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                                     "Dist": Point(dx, 0), "EasingX": easing, "EasingY": easing})

        if self not in GraphicsObject.gliding_objects:
            GraphicsObject.gliding_objects.append(self)

        return self

    def glide_y(self, dy, time=1, easing=ease_linear(), _internal_call=False):
        if not (isinstance(dy, int) or isinstance(dy, float)):
            raise GraphicsError("\n\nThe y amount to glide the object by (dy) must be a number "
                                f"(integer or float), not {dy}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to glide the object for (time) must be a number "
                                f"(integer or float), not {time}")

        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        self.is_gliding = True
        if not _internal_call:
            start = timetime()
            initial_pos = self.anchor.clone()

            for glide in self.glide_queue:
                start += glide["Time"]
                initial_pos = glide["Initial"] + glide["Dist"]

            self.glide_queue.append({"Time": time, "Start": start,
                                     "Update": timetime(), "Initial": initial_pos,
                                     "Dist": Point(0, dy), "EasingX": easing, "EasingY": easing})

        if self not in GraphicsObject.gliding_objects:
            GraphicsObject.gliding_objects.append(self)

        return self

    def glide_to(self, x, y=None, time=1, easing_x=ease_linear(), easing_y=None):
        if y is None:
            y = x
        if easing_y is None:
            easing_y = easing_x

        self.glide_x(time=time, dx=x - self.anchor.x, easing=easing_x, _internal_call=True)
        self.glide_y(time=time, dy=y - self.anchor.y, easing=easing_y, _internal_call=True)

        start = timetime()
        initial_pos = self.anchor.clone()
        for glide in self.glide_queue:
            start += glide["Time"]
            initial_pos = glide["Initial"] + glide["Dist"]

        self.glide_queue.append({"Time": time, "Start": start, "Update": timetime(), "Initial": initial_pos,
                                 "Dist": Point(x, y) - initial_pos, "EasingX": easing_x, "EasingY": easing_y})

        return self

    def glide_to_x(self, x, time=1, easing=ease_linear()):
        self.glide_x(time=time, dx=x - self.anchor.x, easing=easing)
        return self

    def glide_to_y(self, y, time=1, easing=ease_linear()):
        self.glide_y(time=time, dy=y - self.anchor.y, easing=easing)
        return self

    def glide_to_point(self, p, time=1, easing_x=ease_linear(), easing_y=None):
        self.glide_to(x=p.x, y=p.y, time=time, easing_x=easing_x, easing_y=easing_y)
        return self

    def animate_rotate(self, dr, time=1, easing=ease_linear()):
        if not (isinstance(dr, int) or isinstance(dr, float)):
            raise GraphicsError("\n\nThe amount to rotate the object by (dr) must be a number "
                                f"(integer or float), not {dr}")
        if not (isinstance(time, int) or isinstance(time, float)):
            raise GraphicsError("\n\nThe time to rotate the object for (time) must be a number "
                                f"(integer or float), not {time}")
        if not callable(easing):
            raise GraphicsError(f"\n\nThe Easing Function Provided ({easing}) is not a valid Function")

        self.is_rotating = True
        start = timetime()
        initial_rotation = self.rotation

        for rotation in self.rotating_queue:
            start += rotation["Time"]
            initial_pos = rotation["Initial"] + rotation["Rotation"]

        self.rotating_queue.append({"Time": time, "Start": start, "Update": timetime(), "Initial": initial_rotation,
                                    "Rotation": dr, "Easing": easing})

        if self not in GraphicsObject.rotating_objects:
            GraphicsObject.rotating_objects.append(self)

    def animate_set_rotation(self, r, time=1, easing=ease_linear()):
        self.animate_rotate(r - self.rotation, time=time, easing=easing)
        return self

    def rotate(self, dr):
        self._rotate(dr)
        if self.graphwin is not None:
            self.redraw()

        return self

    def set_rotation(self, r):
        self.rotate(r - self.rotation)
        return self

    def redraw(self):
        if self.graphwin.is_open():
            self.undraw()
            self.draw(self.graphwin)
        return self

    def is_selected(self):
        selected = self.is_clicked(self.graphwin.get_last_mouse())
        if selected:
            self.selected_clicks = self.graphwin.left_mouse_clicks

        return selected or self.selected_clicks == self.graphwin.left_mouse_clicks

    def is_clicked(self, mouse_pos):
        return False

    @staticmethod
    def on_update(graphwin):
        t = timetime()
        for obj in GraphicsObject.gliding_objects:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.glide_queue[0]["Start"] >= obj.glide_queue[0]["Time"]:
                    obj.move_to(obj.glide_queue[0]["Initial"].x + obj.glide_queue[0]["Dist"].x,
                                obj.glide_queue[0]["Initial"].y + obj.glide_queue[0]["Dist"].y)

                    obj.glide_queue.pop(0)  # Remove the object from the gliding queue
                    if len(obj.glide_queue) == 0:
                        obj.is_gliding = False
                        GraphicsObject.gliding_objects.remove(obj)
                else:
                    perX = obj.glide_queue[0]["EasingX"]((t - obj.glide_queue[0]['Start']) / obj.glide_queue[0]['Time'])
                    perY = obj.glide_queue[0]["EasingY"]((t - obj.glide_queue[0]['Start']) / obj.glide_queue[0]['Time'])

                    obj.move_to(obj.glide_queue[0]["Initial"].x + obj.glide_queue[0]["Dist"].x * perX,
                                obj.glide_queue[0]["Initial"].y + obj.glide_queue[0]["Dist"].y * perY)
                    obj.glide_queue[0]["Update"] = timetime()

        t = timetime()
        for obj in GraphicsObject.rotating_objects:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.rotating_queue[0]["Start"] >= obj.rotating_queue[0]["Time"]:
                    obj.set_rotation(obj.rotating_queue[0]["Initial"] + obj.rotating_queue[0]["Rotation"])
                    obj.rotating_queue.pop(0)

                    if len(obj.rotating_queue) == 0:
                        obj.is_rotating = False
                        GraphicsObject.rotating_objects.remove(obj)
                else:
                    per = obj.rotating_queue[0]["Easing"]((t - obj.rotating_queue[0]["Start"])
                                                          / obj.rotating_queue[0]["Time"])
                    obj.set_rotation(obj.rotating_queue[0]["Initial"] + obj.rotating_queue[0]["Rotation"] * per)
                    obj.rotating_queue[0]["Update"] = timetime()

        for obj in GraphicsObject.blinking_objects:
            if obj.graphwin == graphwin:
                if t - obj.last_blink > obj.blinking_interval:
                    if obj.drawn:
                        obj.undraw(set_blinking=False)
                    else:
                        obj.draw(graphwin)
                    obj.last_blink = t

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
        mouse_pos = graphwin.check_left_mouse_press(refresh=False)

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
            mouse_pos = graphwin.check_mouse_motion(refresh=False)

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
                    #print(obj)
                    if obj.is_clicked(mouse_pos):
                        graphwin.config(cursor=CURSORS[obj.cursor])
                        hover_count += 1
                    if obj.is_dragging:
                        if graphwin.left_mouse_down:
                            obj.move_to_point(mouse_pos)
                            try:
                                obj.callbacks["Dragging"]()
                            except TypeError:
                                pass
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
