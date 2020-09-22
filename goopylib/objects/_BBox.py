from goopylib.objects.GraphicsObject import GraphicsObject

from goopylib.styles import *


class BBox(GraphicsObject):
    # Internal base class for objects represented by bounding box
    # (opposite corners) Line segment is a degenerate case.

    resizing_objects = []

    def __init__(self, p1, p2, bounds=None, fill=None, outline=None, outline_width=None, cursor="arrow", layer=0,
                 tag=None):

        self.p1 = p1
        self.p2 = p2

        # These make sure that the p2 is 'after' p1, ie the x & y value of p2 is greater than that of p1
        if self.p1[0] > self.p2[0]:  # Checking if p1's x value is greater than p2's. If so, then swap the values
            self.p1[0], self.p2[0] = self.p2[0], self.p1[0]
        if self.p1[1] > self.p2[1]:  # Checking if p1's y value is greater than p2's. If so, then swap the values
            self.p1[1], self.p2[1] = self.p2[1], self.p1[1]

        self.anchor = [(self.p1[0] + self.p2[0]) // 2, (self.p1[1] + self.p2[1]) // 2]

        GraphicsObject.__init__(self, options=(), cursor=cursor, layer=layer, bounds=bounds, tag=tag)

        # abs(p2[0] - p1[0]) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = self.p2[0] - self.p1[0]
        self.height = self.p2[1] - self.p1[1]

        self.min_width = None
        self.min_height = None
        self.max_width = None
        self.max_height = None

        self.resizing_bounds = {}
        self.is_resizing = {}
        self.bounds_thickness = 0

        if isinstance(fill, Colour):
            self.fill = fill
        else:
            self.fill = STYLES["default"]["fill"]

        if isinstance(outline, Colour):
            self.outline = outline
        else:
            self.outline = STYLES["default"]["outline"]

        if isinstance(outline_width, int):
            self.outline_width = outline_width
        else:
            self.outline_width = STYLES["default"]["width"]

    def __repr__(self):
        return "_BBox"

    def _set_resizable(self, resizables, top_bounds=None, bottom_bounds=None, left_bounds=None, right_bounds=None,
                       thickness=10):
        """Override in subclasses"""
        pass

    def _move(self, dx, dy):
        self.p1[0] += dx
        self.p1[1] += dy
        self.p2[0] += dx
        self.p2[1] += dy

        self.anchor[0] += dx
        self.anchor[1] += dy

    def get_p1(self):
        return self.p1.copy()

    def get_p2(self):
        return self.p2.copy()

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            if mouse_pos is None:
                return False
            else:
                if (self.p1[0] < mouse_pos[0] < self.p2[0] or self.p1[0] > mouse_pos[0] > self.p2[0]) and \
                        (self.p1[1] < mouse_pos[1] < self.p2[1] or self.p1[1] > mouse_pos[1] > self.p2[1]):
                    return True
                else:
                    return False
        else:
            return self.bounds.is_clicked(mouse_pos)

    def set_coords(self, p1, p2):

        self.p1 = p1.copy()
        self.p2 = p2.copy()

        # These make sure that the p2 is 'after' p1, ie the x & y value of p2 is greater than that of p1
        if self.p1[0] > self.p2[0]:  # Checking if p1's x value is greater than p2's. If so, then swap the values
            self.p1[0], self.p2[0] = self.p2[0], self.p1[0]
        if self.p1[1] > self.p2[1]:  # Checking if p1's y value is greater than p2's. If so, then swap the values
            self.p1[1], self.p2[1] = self.p2[1], self.p1[1]

        # abs(p2[0] - p1[0]) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = self.p2[0] - self.p1[0]
        self.height = self.p2[1] - self.p1[1]
        width_scale = (p2[0] - p1[0]) / self.width
        height_scale = (p2[1] - p1[1]) / self.height

        # abs(p2[0] - p1[0]) is not required because the p2 value is always greater than or equal to the p1 value
        self.width = p2[0] - p1[0]
        self.height = p2[1] - p1[1]

        self.anchor = [(self.p1[0] + self.p2[0]) // 2, (self.p1[1] + self.p2[1]) // 2]

        self._update_layer()

        return self

    def set_width(self, width, center="center"):
        if center not in {"center", "right", "left"}:
            raise GraphicsError(
                "\n\nThe center argument for resizing the object (set_outline_width) needs to be one of "
                f'{["center", "right", "left"]}')

        if center == "left":
            self.set_coords(self.p1, self.p2.add_x(width - self.width))

        elif center == "right":
            self.set_coords(self.p1.add_x(-(width - self.width)), self.p2)
        else:
            self.set_coords(self.p1.add_x(-(width / 2 - self.width)), self.p2.add_x(width / 2 - self.width))

        return self

    def set_height(self, height, center="center"):
        if center not in {"center", "top", "bottom"}:
            raise GraphicsError(
                "\n\nThe center argument for resizing the object (set_height) needs to be one of "
                f'{["center", "top", "bottom"]}')

        if center == "top":
            self.set_coords(self.p1, self.p2.add_y(height - self.height))

        elif center == "bottom":
            self.set_coords(self.p1.add_y(-(height - self.height)), self.p2)
        else:
            self.set_coords(self.p1.add_y(-(height / 2 - self.height)), self.p2.add_y(height / 2 - self.height))

        return self

    def get_width(self):
        return self.width

    def get_height(self):
        return self.height

    def get_fill(self):
        return self.fill

    def get_outline(self):
        return self.outline

    def get_outline_width(self):
        return self.outline_width

    def set_dimensions(self, width, height, horizontal_align="center", vertical_align="center"):
        self.set_width(width, horizontal_align)
        self.set_height(height, vertical_align)
        return self

    def set_resizable(self, top=False, left=False, bottom=False, right=False, min_width=40, min_height=40,
                      bounds_width=10, top_bounds=None, bottom_bounds=None, left_bounds=None, right_bounds=None):

        if min_width < 1 or min_height < 1:
            raise GraphicsError(f"\n\nGraphicsError: Minimum height and width of resizable object must be greater than "
                                f"or equal to 1. Right now, min_width={min_width} & min_height={min_height}")

        self.min_width = min_width
        self.min_height = min_height

        self.is_resizing = {"top": top, "left": left, "bottom": bottom, "right": right}

        self._set_resizable([top, bottom, left, right], top_bounds=top_bounds, bottom_bounds=bottom_bounds,
                            left_bounds=left_bounds, right_bounds=right_bounds, thickness=bounds_width)

        if top is False and bottom is False and left is False and right is False:
            if self in GraphicsObject.resizing_objects:
                GraphicsObject.resizing_objects.remove(self)

        elif self not in GraphicsObject.resizing_objects:
            GraphicsObject.resizing_objects.add(self)

        self.bounds_thickness = bounds_width

        return self

    def get_anchor(self):
        return self.anchor
