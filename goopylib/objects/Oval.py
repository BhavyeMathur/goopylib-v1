import goopylib.objects._BBox as gpBBox
from goopylib.objects.Rectangle import Rectangle

from goopylib.util import GraphicsError

class Oval(gpBBox.BBox):

    def __init__(self, center, radius1, radius2, bounds=None, fill=None, outline=None, outline_width=None,
                 cursor="arrow", layer=0, tag=None):

        if not isinstance(center, list):
            raise GraphicsError("\n\nGraphicsError: center argument for Oval must be a list in the form [x, y], "
                                f"not {center}")

        if not isinstance(radius1, int):
            raise GraphicsError(f"\n\nGraphicsError: radius1 argument for Oval must be an integer, not {radius1}")
        if not isinstance(radius2, int):
            raise GraphicsError(f"\n\nGraphicsError: radius2 argument for Oval must be an integer, not {radius2}")

        p1 = [center[0] - radius1, center[1] - radius2]
        p2 = [center[0] + radius1, center[1] + radius2]

        self.radius1 = radius1
        self.radius2 = radius2
        
        self.center = center

        gpBBox.BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, outline_width=outline_width,
                             cursor=cursor, layer=layer, tag=tag)

    def __repr__(self):
        return f"Oval(anchor={self.center}, radius1={self.radius1}, radius2={self.radius2})"

    def clone(self, new_tag=None):
        other = Oval(self.center, self.radius1, self.radius1, bounds=self.bounds.clone(), fill=self.fill,
                     outline=self.outline, outline_width=self.outline_width, cursor=self.cursor, layer=self.layer,
                     tag=new_tag)
        return other

    def _draw(self, canvas, options):
        x1, y1 = canvas.to_screen(self.p1[0], self.p1[1])
        x2, y2 = canvas.to_screen(self.p2[0], self.p2[1])

        return canvas.create_oval(x1, y1, x2, y2, fill=self.fill, outline=self.outline, width=self.outline_width)

    def _set_resizable(self, resizables, top_bounds=None, bottom_bounds=None, left_bounds=None, right_bounds=None,
                       thickness=10):

        # resizables is a list [top, bottom, left, right] where each of its elements are Booleans defining whether the
        # rectangle is resizable in that direction

        self.resizing_bounds = {}  # Stores the bounds of the resizing objects for 'top', 'bottom', 'left', & 'right'
        if resizables[0]:  # Checks if the object is set to be resized from the top
            if top_bounds is None:  # The user hasn't supplied a custom bound
                self.resizing_bounds["top"] = Rectangle([self.p1[0] - thickness / 2, self.p1[1] - thickness / 2],
                                                        [self.p2[0] + thickness / 2, self.p1[1] + thickness / 2],
                                                        cursor="vertical-resizing-arrow")
            elif isinstance(top_bounds, GraphicsObject):  # The user supplied a GraphicsObject as the bound
                self.resizing_bounds["top"] = top_bounds

            elif top_bounds in GraphicsObject.tagged_objects:  # The user supplied a tag referencing a GraphicsObject
                self.resizing_bounds["top"] = GraphicsObject.tagged_objects[top_bounds]

            else:  # The user provided an invalid argument, this raises an error
                raise GraphicsObject("\n\nGraphicsError: Top bound for Rectangle resizing must be a None, "
                                     f"GraphicsObject or tag referencing a GraphicsObject, not {top_bounds}")

        if resizables[1]:  # Checks if the object is set to be resized from the bottom
            if bottom_bounds is None:  # The user hasn't supplied a custom bound
                self.resizing_bounds["bottom"] = Rectangle([self.p2[0] + thickness / 2, self.p2[1] - thickness / 2],
                                                           [self.p1[0] - thickness / 2, self.p2[1] + thickness / 2],
                                                           cursor="vertical-resizing-arrow")
            elif isinstance(bottom_bounds, GraphicsObject):  # The user supplied a GraphicsObject as the bound
                self.resizing_bounds["bottom"] = top_bounds

            elif bottom_bounds in GraphicsObject.tagged_objects:  # The user supplied a tag referencing a GraphicsObject
                self.resizing_bounds["bottom"] = GraphicsObject.tagged_objects[top_bounds]

            else:  # The user provided an invalid argument, this raises an error
                raise GraphicsObject("\n\nGraphicsError: Top bound for Rectangle resizing must be a None, "
                                     f"GraphicsObject or tag referencing a GraphicsObject, not {top_bounds}")

        if resizables[2]:  # Checks if the object is set to be resized from the left
            if left_bounds is None:  # The user hasn't supplied a custom bound
                self.resizing_bounds["left"] = Rectangle([self.p1[0] - thickness / 2, self.p1[1] - thickness / 2],
                                                         [self.p1[0] + thickness / 2, self.p2[1] + thickness / 2],
                                                         cursor="horizontal-resizing-arrow")
            elif isinstance(left_bounds, GraphicsObject):  # The user supplied a GraphicsObject as the bound
                self.resizing_bounds["left"] = left_bounds

            elif left_bounds in GraphicsObject.tagged_objects:  # The user supplied a tag referencing a GraphicsObject
                self.resizing_bounds["left"] = GraphicsObject.tagged_objects[left_bounds]

            else:  # The user provided an invalid argument, this raises an error
                raise GraphicsObject("\n\nGraphicsError: Top bound for Rectangle resizing must be a None, "
                                     f"GraphicsObject or tag referencing a GraphicsObject, not {top_bounds}")

        if resizables[3]:  # Checks if the object is set to be resized from the right
            if right_bounds is None:  # The user hasn't supplied a custom bound
                self.resizing_bounds["right"] = Rectangle([self.p2[0] + thickness / 2, self.p2[1] + thickness / 2],
                                                          [self.p2[0] - thickness / 2, self.p1[1] - thickness / 2],
                                                          cursor="horizontal-resizing-arrow")
            elif isinstance(right_bounds, GraphicsObject):  # The user supplied a GraphicsObject as the bound
                self.resizing_bounds["right"] = right_bounds

            elif right_bounds in GraphicsObject.tagged_objects:  # The user supplied a tag referencing a GraphicsObject
                self.resizing_bounds["right"] = GraphicsObject.tagged_objects[right_bounds]

            else:  # The user provided an invalid argument, this raises an error
                raise GraphicsObject("\n\nGraphicsError: Top bound for Rectangle resizing must be a None, "
                                     f"GraphicsObject or tag referencing a GraphicsObject, not {top_bounds}")

    def is_clicked(self, mouse_pos):
        if mouse_pos is None:
            return False

        if self.bounds is None:
            return (((mouse_pos[0] - self.anchor[0]) ** 2) / self.radius1 ** 2) \
                   + (((mouse_pos[1] - self.anchor[1]) ** 2) / self.radius2 ** 2) < 1
        else:
            return self.bounds.is_clicked(mouse_pos)


from goopylib.objects.GraphicsObject import GraphicsObject
