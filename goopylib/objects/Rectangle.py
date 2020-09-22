import goopylib.objects._BBox as gpBBox
from goopylib.util import GraphicsError


class Rectangle(gpBBox.BBox):
    def __init__(self, p1, p2, bounds=None, fill=None, outline=None, outline_width=None, layer=0,
                 cursor="arrow", is_rounded=False, roundness=5, tag=None):

        # This makes sure that the p1 & p2 arguments of the Rectangle are lists, raises an error otherwise
        if not isinstance(p1, list):
            raise GraphicsError("\n\nGraphicsError: p1 argument for Rectangle must be a list in the form [x, y], "
                                f"not {p1}")
        if not isinstance(p2, list):
            raise GraphicsError("\n\nGraphicsError: p2 argument for Rectangle must be a list in the form [x, y], "
                                f"not {p2}")

        # Makes sure that the roundness argument is an integer, raises an error otherwise
        if not isinstance(roundness, int):
            raise GraphicsError("\n\nGraphicsError: roundness argument for Rectangle must be an integer, "
                                f"not {roundness}")

        # A call to the super class to initialize important variables of the Rectangle class.
        gpBBox.BBox.__init__(self, p1, p2, bounds=bounds, fill=fill, outline=outline, outline_width=outline_width,
                             cursor=cursor, layer=layer, tag=tag)

        self.is_rounded = is_rounded  # A variable defining whether the rectangle is rounded
        self.sharpness = roundness  # Usually values between 2 & 10 work well.

    def __repr__(self):
        return f"Rectangle({self.p1}, {self.p2}, tag={self.tag})"

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

    def _draw(self, canvas, options):
        if self.is_rounded:
            points = [self.p1[0], self.p1[1], self.p1[0], self.p2[1], self.p2[0], self.p2[1], self.p2[0], self.p1[1]]
            for point in range(len(points[::2])):
                points[point * 2], points[point * 2 + 1] = canvas.to_screen(points[point * 2], points[point * 2 + 1])

            # Code modified from Francisco Gomes, https://stackoverflow.com/users/9139005/francisco-gomes

            # The sharpness here is just how close the sub-points
            # are going to be to the vertex. The more the sharpness,
            # the more the sub-points will be closer to the vertex.
            # (This is not normalized)

            x = points[::2]
            y = points[1::2]

            if self.sharpness < 2:
                self.sharpness = 2

            ratio_multiplier = self.sharpness - 1
            ratio_dividend = self.sharpness

            # List to store the points
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
                    points.append((ratio_multiplier * x[i] + x[i + 1]) / ratio_dividend)
                    points.append((ratio_multiplier * y[i] + y[i + 1]) / ratio_dividend)
                    points.append((ratio_multiplier * x[i + 1] + x[i]) / ratio_dividend)
                    points.append((ratio_multiplier * y[i + 1] + y[i]) / ratio_dividend)
                else:
                    # Insert submultiples points.
                    points.append((ratio_multiplier * x[i] + x[0]) / ratio_dividend)
                    points.append((ratio_multiplier * y[i] + y[0]) / ratio_dividend)
                    points.append((ratio_multiplier * x[0] + x[i]) / ratio_dividend)
                    points.append((ratio_multiplier * y[0] + y[i]) / ratio_dividend)
                    # Close the polygon
                    points.append(x[0])
                    points.append(y[0])

            # This is done due to an internal bug in Tkinter where it does not set the width of the polygon...
            if self.outline_width == 0:
                self.outline = self.fill

            return canvas.create_polygon(points, width=self.outline_width, fill=self.fill, outline=self.outline,
                                         smooth=self.is_rounded)

        return canvas.create_rectangle(self.p1[0], self.p1[1], self.p2[0], self.p2[1], fill=self.fill,
                                       outline=self.outline, width=self.width)

    def clone(self, new_tag=None):
        other = Rectangle(self.p1, self.p2, fill=self.fill, outline=self.outline, outline_width=self.outline_width,
                          layer=self.layer, cursor=self.cursor, is_rounded=self.is_rounded, roundness=self.sharpness,
                          tag=new_tag, bounds=self.bounds.clone())
        return other

    def is_clicked(self, pos):
        if pos is None:
            return False

        if self.bounds is None:
            width = self.width // 2
            height = self.height // 2
            return self.anchor[0] - width < pos[0] < self.anchor[0] + width and \
                   self.anchor[1] - height < pos[1] < self.anchor[1] + height
        else:
            return self.bounds.is_clicked(pos)


from goopylib.objects.GraphicsObject import GraphicsObject
