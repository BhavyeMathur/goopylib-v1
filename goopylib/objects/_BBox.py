from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.Point import Point

from goopylib.styles import *


class BBox(GraphicsObject):
    # Internal base class for objects represented by bounding box
    # (opposite corners) Line segment is a degenerate case.

    resizing_objects = []

    def __init__(self, p1, p2, bounds=None, style=None, fill=None, outline=None, outline_width=None,
                 options=("fill", "outline", "width"), cursor="arrow", layer=0, tag=None):

        self.p1 = p1.clone()
        self.p2 = p2.clone()

        GraphicsObject.__init__(self, style=style, options=options, cursor=cursor, layer=layer, bounds=bounds, tag=tag)

        # abs(p2.x - p1.x) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = self.p2.x - self.p1.x
        self.height = self.p2.y - self.p1.y

        self.min_width = None
        self.min_height = None
        self.max_width = None
        self.max_height = None

        self.resizing_bounds = {}
        self.is_Resizing = {}
        self.bounds_thickness = 0

        if isinstance(fill, Colour):
            self.fill = fill
        elif fill in STYLES[self.style].keys():
            self.fill = STYLES[self.style][fill]
        else:
            if "fill" in STYLES[self.style].keys():
                self.fill = STYLES[self.style]["fill"]
            else:
                self.fill = STYLES["default"]["fill"]
        self.set_fill(self.fill)

        if isinstance(outline, Colour):
            self.outline = outline
        elif outline in STYLES[self.style].keys():
            self.outline = STYLES[self.style][outline]
        else:
            if "outline" in STYLES[self.style].keys():
                self.outline = STYLES[self.style]["outline"]
            else:
                self.outline = STYLES["default"]["outlien"]
        self.set_outline(self.outline)

        if isinstance(outline_width, int):
            self.outline_width = outline_width
        elif outline_width in STYLES[self.style].keys():
            self.outline_width = STYLES[self.style][outline_width]
        else:
            if "width" in STYLES[self.style].keys():
                self.outline_width = STYLES[self.style]["width"]
            else:
                self.outline_width = STYLES["default"]["width"]
        self.set_outline_width(self.outline_width)

    def __repr__(self):
        return "BBox"

    def _update(self):
        pass

    def _set_resizable(self, resizables, thickness=10, show_bounds=False):
        """Override in subclasses"""
        pass

    def show_bounds(self):
        self.bounds_object = BBox(self.bounds.p1, self.bounds.p2, outline=CHROME_YELLOW, outline_width=0,
                                              cursor=self.cursor).draw(self.graphwin)

    def hide_bounds(self):
        self.bounds_object.undraw()

    def _move(self, dx, dy):
        self.p1.x = self.p1.x + dx
        self.p1.y = self.p1.y + dy
        self.p2.x = self.p2.x + dx
        self.p2.y = self.p2.y + dy

        self.anchor = self.get_anchor()
        self._update()

    def get_p1(self):
        return self.p1.clone()

    def get_p2(self):
        return self.p2.clone()

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            if mouse_pos is not None:
                if (self.p1.x < mouse_pos.x < self.p2.x or self.p1.x > mouse_pos.x > self.p2.x) and \
                        (self.p1.y < mouse_pos.y < self.p2.y or self.p1.y > mouse_pos.y > self.p2.y):
                    return True
                else:
                    return False
        else:
            print(self.bounds)
            return self.bounds.is_clicked(mouse_pos)

    def get_anchor(self):
        return Point((self.p1.x + self.p2.x) / 2, (self.p1.y + self.p2.y) / 2)

    def reset_bounds(self):
        self.bounds = BBox(self.p1, self.p2)

    def set_coords(self, p1, p2):

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

        width_scale = (p2.x - p1.x) / self.width
        height_scale = (p2.y - p1.y) / self.height

        # abs(p2.x - p1.x) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = p2.x - p1.x
        self.height = p2.y - p1.y

        self.anchor = Point((self.p1.x + self.p2.x) / 2, (self.p1.y + self.p2.y) / 2)

        if self.drawn:
            self.redraw()

        self._update()

        return width_scale, height_scale

    def set_width(self, width, center="center"):
        if center not in ["center", "right", "left"]:
            raise GraphicsError(
                "\n\nThe center argument for resizing the object (set_outline_width) needs to be one of "
                f'{["center", "right", "left"]}')

        if center == "left":
            width_scale, _ = self.set_coords(self.p1, self.p2.add_x(width - self.width))

        elif center == "right":
            width_scale, _ = self.set_coords(self.p1.add_x(-(width - self.width)), self.p2)
        else:
            width_scale, _ = self.set_coords(self.p1.add_x(-(width / 2 - self.width)),
                                             self.p2.add_x(width / 2 - self.width))

        if self.bounds is not None:
            self.bounds.set_width(width_scale * self.bounds.width, center)

        return self

    def set_height(self, height, center="center"):
        if center not in ["center", "top", "bottom"]:
            raise GraphicsError(
                "\n\nThe center argument for resizing the object (set_height) needs to be one of "
                f'{["center", "top", "bottom"]}')

        if center == "top":
            _, height_scale = self.set_coords(self.p1, self.p2.add_y(height - self.height))

        elif center == "bottom":
            _, height_scale = self.set_coords(self.p1.add_y(-(height - self.height)), self.p2)
        else:
            _, height_scale = self.set_coords(self.p1.add_y(-(height / 2 - self.height)),
                                              self.p2.add_y(height / 2 - self.height))

        if self.bounds is not None:
            self.bounds.set_width(height_scale * self.bounds.height, center)

        return self

    def get_width(self):
        return self.width

    def get_height(self):
        return self.height

    def get_outline(self):
        return self.config["outline"]

    def get_outline_width(self):
        return self.config["width"]

    def set_dimensions(self, width, height, horizontal_align="center", vertical_align="center"):
        self.set_width(width, horizontal_align)
        self.set_height(height, vertical_align)
        return self

    def set_resizable(self, top=False, left=False, bottom=False, right=False, min_width=40, min_height=40,
                      bounds_width=10, show_bounds=False):

        if min_width < 1 or min_height < 1:
            raise GraphicsError(f"\n\nMinimum height and width of resizable object must be greater than or equal to 1. "
                                f"Right now, min_width={min_width} & min_height={min_height}")

        self.min_width = min_width
        self.min_height = min_height

        self.is_resizing = {"top": top, "left": left, "bottom": bottom, "right": right}

        self._set_resizable([top, bottom, left, right], thickness=bounds_width, show_bounds=show_bounds)
        GraphicsObject.resizing_objects.append(self)
        self.bounds_thickness = bounds_width

        return self

    def get_fill(self):
        return self.config["fill"]


import goopylib.objects.Line as gpLine
