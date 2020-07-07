import time

from goopylib.Point import Point

from goopylib.styles import *
from goopylib.constants import *
from goopylib.constants import _root

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

        self.rotating_start = None
        self.rotating_time = None
        self.rotating_dist = None
        self.rotating_update = None
        self.rotating_dest = None
        self.rotating_easing = None
        self.rotating_initial = None
        self.rotating_args = None
        self.is_rotating = False
        self.rotation = 0

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

    def set_clickable(self, clickable=True):
        if clickable:
            if self not in GraphicsObject.objects:
                GraphicsObject.objects.append(self)
        else:
            if self in GraphicsObject.objects:
                GraphicsObject.objects.remove(self)

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

        self.graphwin = graphwin

        self.id = self._draw(graphwin, self.config)
        graphwin.add_item(self)
        if graphwin.autoflush:
            _root.update()

        self.drawn = True

        return self

    def set_cursor(self, cursor="arrow"):
        self.cursor = cursor

    def animate_blinking(self, interval, animate=True):
        self.is_blinking = animate
        self.blinking_interval = interval
        self.last_blink_time = time.time()

        if animate and self not in GraphicsObject.blinking_objects:
            GraphicsObject.blinking_objects.append(self)
        elif not animate and self in GraphicsObject.blinking_objects:
            GraphicsObject.blinking_objects.remove(self)

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

    def set_rotation(self, r):
        self.rotate(r - self.rotation)
        return self

    def get_anchor(self):
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

    def move_to(self, x, y):
        self.move(x - self.get_anchor().x, y - self.get_anchor().y)
        return self

    def move_y(self, dy):
        self.move(0, dy)
        return self

    def move_x(self, dx):
        self.move(dx, 0)
        return self

    def move_to_y(self, y):
        self.move(0, y - self.get_anchor().y)
        return self

    def move_to_x(self, x):
        self.move(x - self.get_anchor().x, 0)
        return self

    def glide(self, dx, dy, t, easing="Linear", args=None, frames="Frames"):
        if frames not in ["Time", "Frames"]:
            raise GraphicsError("\n\nframes parameter must be either 'Time' or 'Frames' not '{}'".format(frames))

        if len(self.glide_queue) == 0:
            last_t = time.time()
            last_dest = self.get_anchor().clone()
        else:
            last_t = self.glide_queue[len(self.glide_queue) - 1]["Start"] + self.glide_queue[len(self.glide_queue) - 1][
                "Time"]
            last_dest = self.glide_queue[len(self.glide_queue) - 1]["Dest"]

        self.glide_queue.append({"Dest": last_dest + Point(dx, dy),
                                "Initial": last_dest,
                                "Dist": Point(dx, dy),
                                "Easing": easing,
                                "Time": t,
                                "Update": last_t,
                                "Start": last_t,
                                "Args": args,
                                "Frames": frames})
        self.is_gliding = True

        if self not in GraphicsObject.gliding_objects:
            GraphicsObject.gliding_objects.append(self)
        return self

    def glide_to(self, x, y, t, easing="Linear", args=None, frames="Frames"):
        if len(self.glide_queue) == 0:
            last_dest = self.get_anchor().clone()
        else:
            last_dest = self.glide_queue[len(self.glide_queue) - 1]["Dest"]

        self.glide(x - last_dest.x, y - last_dest.y, t, easing, args, frames)
        return self

    def glide_to_point(self, p, t, easing="Linear", args=None, frames="Frames"):
        self.glide_to(p.x, p.y, t, easing, args, frames)

    def animate_rotate(self, dr, t, easing="Linear", args=None, frames="Frames"):
        pass

    def animate_set_rotation(self, r, t, easing="Linear", args=None, frames="Frames"):
        self.animate_rotate(r - self.rotation, t, easing, args, frames)
        return self

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
        t = time.time()
        for obj in GraphicsObject.gliding_objects:
            if obj.graphwin == graphwin and obj.drawn:
                if not obj.glide_queue[0]["Frames"] == "Time":
                    t = obj.glide_queue[0]["Update"] + 0.05

                if t - obj.glide_queue[0]["Start"] >= obj.glide_queue[0]["Time"]:
                    obj.is_gliding = False
                    obj.glide_queue.pop(0)
                    if len(obj.glide_queue) == 0:
                        GraphicsObject.gliding_objects.remove(obj)
                else:
                    args = ""
                    if obj.glide_queue[0]["Args"] is not None:
                        args = ", {}".format(obj.glide_queue[0]["Args"])

                    per = eval("ease{}((obj.glide_queue[0]['Update'] - obj.glide_queue[0]['Start'])/"
                               "obj.glide_queue[0]['Time']{})".format(obj.glide_queue[0]["Easing"], args))
                    per = min([1, per])

                    obj.move_to(obj.glide_queue[0]["Initial"].x + obj.glide_queue[0]["Dist"].x * per,
                                obj.glide_queue[0]["Initial"].y + obj.glide_queue[0]["Dist"].y * per)

                    if obj.glide_queue[0]["Frames"] == "Time":
                        obj.glide_queue[0]["Update"] = time.time()
                    else:
                        obj.glide_queue[0]["Update"] += 0.05

        t = time.time()
        for obj in GraphicsObject.rotating_objects:
            if obj.graphwin == graphwin and obj.drawn:
                if t - obj.rotating_start >= obj.rotating_time:
                    obj.is_rotating = False
                    GraphicsObject.rotating_objects.remove(obj)
                else:
                    args = ""
                    if obj.rotating_args is not None:
                        for arg in obj.rotating_args.split(","):
                            args += ", {}".format(arg)

                    per = eval(
                        f"ease{obj.rotating_easing}((obj.rotating_update - obj.rotating_start)/obj.rotating_time{args})")
                    obj.set_rotation(obj.rotating_initial + obj.rotating_dist * per)
                    obj.rotating_update = t

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
                    obj.draw(obj.graphwin)

        for obj in GraphicsObject.resizing_objects:
            if obj.graphwin == graphwin:
                for bound in obj.resizing_bounds:
                    if obj.resizing_bounds[bound].is_clicked(mouse_pos):
                        obj.is_resizing[bound] = True
                        obj.resizing_anchor = obj.get_anchor()
                        obj.resizing_initial_size = obj.width, obj.height
                    else:
                        obj.is_resizing[bound] = False

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
                    if obj.is_clicked(mouse_pos):
                        graphwin.config(cursor=CURSORS[obj.cursor])
                        hover_count += 1

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
    def on_middle_click():
        pass

    @staticmethod
    def on_right_click():
        pass

    @staticmethod
    def on_mouse_scroll(e, graphwin):
        for obj in GraphicsObject.slider_instances_bound:
            if obj.graphwin == graphwin:
                if obj.range[0] < int(obj.get_value() + e) < obj.range[1]:
                    obj.set_value(int(obj.get_value() + e))
