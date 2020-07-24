from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib._internal_classes import VectorEquation
from goopylib.Point import Point
from goopylib.styles import *
from goopylib.constants import ARROWS, CAPSTYLES, JOINSTYLES, DASHES

from math import sin, cos, radians, atan

# The Line class is used for drawing straight lines segments between 2 or more points
class Line(GraphicsObject):

    def __init__(self, *p, style=None, outline=None, outline_width=None, arrow=None, capstyle=None, joinstyle=None,
                 cursor="arrow", arrow_shape=None, arrow_scale=0.5, dash=None, bounds_width=None, layer=0, tag=None):

        self.points = list(p)  # The list of points that define the line segment
        for i, p in enumerate(self.points):
            if not isinstance(p, Point):  # Checking if all the points specified are indeed Point objects
                raise GraphicsError(f"\n\nGraphicsError: Points for Line class must be Points, not {p} at index {i}")

        if len(p) < 2:  # Making sure there are at least 2 points
            raise GraphicsError(f"\n\nGraphicsError: There must be at least two points to create the line")

        self.low_x, self.low_y = None, None  # These variables are all defined in the get_size() function called below
        self.high_x, self.high_y = None, None  # They store the extreme x & y points farthest from the line's anchor
        self.width, self.height = None, None

        self.get_size()  # Calculates the Width & Height of the line

        self.anchor = None  # The anchor is the center of the line
        self.get_anchor()  # It is calculated as the averages of all the points in the line

        GraphicsObject.__init__(self, options=["arrow", "width", "fill", "capstyle", "joinstyle", "arrowshape", "dash"],
                                cursor=cursor, layer=0, tag=tag)

        self.arrow_scale_coeff = arrow_scale

        self.set_arrow(arrow)  # Setting the options of the line: arrow, outline colour, and outline width
        self.set_outline(outline)
        self.set_outline_width(outline_width)
        self.set_dash(dash)

        self.arrow_scale = self.get_outline_width() * arrow_scale

        self.set_capstyle(capstyle)  # Setting the cap & join styles of the line
        self.set_joinstyle(joinstyle)
        self.set_arrow_shape(arrow_shape, scale=bool(arrow_scale))

        self.bounds_width = None
        self.set_bounds_width(bounds_width)

        self.segments = None  # These 2 variables are defined in the _update() method
        self.equations = None
        self._update()

        # This makes sure that if the user uses the set_fill() function on the line, it references set_outline()
        self.set_fill = self.set_outline

    def __repr__(self):
        return f"Line({self.points})"

    def __dir__(self):
        return "see https://github.com/BhavyeMathur/goopylib/wiki/Lines-&-Curved-Lines!"

    def _draw(self, canvas, options):
        # Converting all the coordinates to Window coordinates to account for stretching, changed coords, etc.
        points = [canvas.to_screen(point.x, point.y) for point in self.points]

        return canvas.create_line(points, options)  # Creating the line!

    def _move(self, dx, dy):
        for i in range(len(self.points)):  # Going through all the points in the line
            self.points[i] += Point(dx, dy)  # And then moving them
        self.anchor = self.get_anchor()  # Recalculating the center of the line

    def _rotate(self, dr, center=None):
        if center is None:
            center = self.get_anchor()  # Getting the center of rotation

        for point in self.points:
            # Formula from (https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d)
            p = point.clone()
            point.x = cos(radians(dr)) * (p.x - center.x) - sin(radians(dr)) * (p.y - center.y) + center.x
            point.y = sin(radians(dr)) * (p.x - center.x) + cos(radians(dr)) * (p.y - center.y) + center.y

    def _update(self):  # Called by the GraphicsObject class whenever the object rotates/moves and the __init__ function
        # These store the points for the line segments present in the line.
        # As this line object can have more than 2 points, it can be divided into segments of 2 points
        self.segments = [(self.points[i], self.points[i + 1]) for i in range(len(self.points) - 1)]
        self.equations = []  # The variable to store the Vector Equations of the line segments
        for line in self.segments:
            # For more information about these steps, see https://www.desmos.com/calculator/esn97hdwbe

            try:
                slope = line[0].slope(line[1])  # Finding the slope of the line segment
                shift = - line[0].y / slope  # Finding the x-shift

                # The height of the line to get it to be the correct amount of wide when rotated
                width = self.bounds_width / (cos(atan(slope)))

                smaller = min([line[0].x, line[1].x])  # Which point has a smaller/larger x value?
                larger = max([line[0].x, line[1].x])

                self.equations.append(VectorEquation(  # Creating the Vector Equation of this line segment
                    f"({slope} * (x - {shift} - {line[0].x}) + {width}/2 > y > "
                    f"{slope} * (x - {shift} - {line[0].x}) - {width}/2) and ({smaller} < x < {larger})"))

            except GraphicsError:  # The Line is Vertical

                smaller = min([line[0].y, line[1].y])  # Which point has a smaller/larger y value?
                larger = max([line[0].y, line[1].y])

                self.equations.append(VectorEquation(
                    f"({line[0].x + self.bounds_width/2} > x > {line[1].x - self.bounds_width/2}) and"
                    f"({larger} > y > {smaller})"))

            except ZeroDivisionError:  # The Line is Horizontal

                smaller = min([line[0].x, line[1].x])  # Which point has a smaller/larger x value?
                larger = max([line[0].x, line[1].x])

                self.equations.append(VectorEquation(
                    f"({line[0].y + self.bounds_width/2}> y > {line[0].y - self.bounds_width/2}) "
                    f"and ({smaller} < x < {larger})"))

        self.get_anchor()

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
        # To calculate the center, it simply calculates the Average of all the Points
        self.anchor = Point(0, 0)  # Starts the anchor at (0, 0)
        for point in self.points:
            self.anchor += point  # Sums up all the Point values

        self.anchor /= len(self.points)  # Divides by number of Points

        return self.anchor

    def get_width(self):
        # To calculate the width, it finds the smallest & largest x points and gets the width
        self.low_x = self.points[0].x  # Setting the High & Low point to the first point
        self.high_x = self.low_x

        for point in self.points[1:]:  # Going through all the other points
            if point.x < self.low_x:  # Checking if this point is smaller
                self.low_x = point.x
            elif point.x > self.high_x:  # Checking if this point is larger
                self.high_x = point.x
        self.width = abs(self.high_x - self.low_x)  # Getting the width

        return self.width

    def get_height(self):
        # To calculate the height, it finds the smallest & largest y points and gets the height
        self.low_y = self.points[0].y  # Setting the High & Low point to the first point
        self.high_y = self.low_y

        for point in self.points[1:]:  # Going through all the other points
            if point.y < self.low_y:  # Checking if this point is smaller
                self.low_y = point.y
            elif point.y > self.high_y:  # Checking if this point is larger
                self.high_y = point.y
        self.height = abs(self.high_y - self.low_y)  # Getting the height

        return self.height

    # These next functions return the value from the Object's config
    def get_outline_width(self):
        return self.config["width"]

    def get_fill(self):
        return self.config["fill"]

    def get_arrow(self):
        return self.config["arrow"]

    def get_outline(self):
        return self.config["fill"]

    def get_capstyle(self):
        return self.config["capstyle"]

    def get_joinstyle(self):
        return self.config["joinstyle"]
    
    def get_arrow_shape(self):
        return self.config["arrowshape"]

    def get_bounds_width(self):
        return self.bounds_width

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_arrow(self, option):
        if option is not None:  # If the Option is None, set the arrow to default arrow
            if option.lower() not in ARROWS:  # Check if the Arrow specified is valid
                raise GraphicsError(f"\n\nGraphicsError: capstyle for line must be one of {ARROWS}, not {option}")
            elif option in STYLES[self.style].keys():  # Checking if the option is a key referencing the object's style
                self._reconfig("arrow", STYLES[self.style][option])
            else:
                self._reconfig("arrow", option)  # Changing the arrow
        else:
            self._reconfig("arrow", STYLES[self.style]["arrow"])

    # These arrow functions reference the set_arrow() function to set the arrow
    def remove_arrows(self):
        self.set_arrow("none")

    def set_arrow_both(self):
        self.set_arrow("none")

    def set_arrow_first(self):
        self.set_arrow("none")

    def set_arrow_last(self):
        self.set_arrow("none")

    def set_outline(self, outline):
        if outline is not None:  # If the option is None, set the outline to the default outline
            if isinstance(outline, Colour):  # Checking if the option is a colour
                self._reconfig("fill", outline)
            elif outline in STYLES[self.style].keys():  # Checking if the option is a key referencing a style
                self._reconfig("fill", STYLES[self.style][outline])
            else:  # If not, raise an error
                raise GraphicsError("\n\nGraphicsError: The line outline must be either a Colour or a string referencing a "
                                    f"colour style, not {outline}")
        else:
            self._reconfig("fill", STYLES[self.style]["line outline"])

    def set_outline_width(self, outline_width):
        if outline_width is not None:  # If the option is None, set the outline to the default width
            if isinstance(outline_width, int):  # Checking if the option is an integer
                self._reconfig("width", outline_width)
            elif outline_width in STYLES[self.style].keys():  # Checking if the option is a key referencing a style
                self._reconfig("width", STYLES[self.style][outline_width])
            else:  # If not, raise an error
                raise GraphicsError(f"\n\nGraphicsError: The line width must be an integer, not {outline_width}")
        else:
            self._reconfig("width", STYLES[self.style]["line width"])

        self.arrow_scale = self.get_outline_width() * self.arrow_scale_coeff
            
    def set_capstyle(self, style):
        if style is not None:  # If the Option is None, set the capstyle to default capstyle
            if style.lower() not in CAPSTYLES:  # Check if the Arrow specified is valid
                raise GraphicsError(f"\n\nGraphicsError: capstyle for line must be one of {CAPSTYLES}, not {style}")
            elif style in STYLES[self.style].keys():  # Checking if the style is a key referencing the object's style
                self._reconfig("capstyle", STYLES[self.style][style])
            else:
                self._reconfig("capstyle", style)  # Changing the arrow
        else:
            self._reconfig("capstyle", STYLES[self.style]["capstyle"])
    
    def set_joinstyle(self, style):
        if style is not None:  # If the Option is None, set the joinstyle to default joinstyle
            if style.lower() not in JOINSTYLES:  # Check if the Arrow specified is valid
                raise GraphicsError(f"\n\nGraphicsError: joinstyle for line must be one of {JOINSTYLES}, not {style}")
            elif style in STYLES[self.style].keys():  # Checking if the style is a key referencing the object's style
                self._reconfig("joinstyle", STYLES[self.style][style])
            else:
                self._reconfig("joinstyle", style)  # Changing the arrow
        else:
            self._reconfig("joinstyle", STYLES[self.style]["joinstyle"])
            
    def set_arrow_shape(self, shape, scale=True):
        if not isinstance(scale, bool):
            raise GraphicsError(f"\n\nGraphicsError: scale argument must be a boolean, not {scale}")

        if shape is not None:  # If the option is None, set the arrow shape to default arrow shape
            if not isinstance(shape, str):
                if not (isinstance(shape, tuple) or isinstance(shape, list)):  # Check if the Arrow shape specified is valid
                    raise GraphicsError("\n\nGraphicsError: arrow shape for line must be one of tuple of length 3, "
                                        f"not {shape}")
                elif len(shape) != 3:
                    raise GraphicsError("\n\nGraphicsError: arrow shape for line must be one of tuple of length 3, "
                                        f"not {shape}")
                else:
                    if scale:
                        shape = list(shape)
                        for i in range(len(shape)):
                            shape[i] = shape[i] * self.arrow_scale  # Scaling the arrow to match the width of the line
                        self._reconfig("arrowshape", shape)  # Changing the arrow
                    else:
                        self._reconfig("arrowshape", shape)  # Changing the arrow

            else:  # It is a string
                if shape in STYLES[self.style].keys():  # Checking if the style is a key referencing the object's style
                    if scale:
                        shape = list(STYLES[self.style][shape])
                        for i in range(len(shape)):
                            shape[i] = shape[i] * self.arrow_scale # Scaling the arrow to match the width of the line
                        self._reconfig("arrowshape", shape)  # Changing the arrow
                    else:
                        self._reconfig("arrowshape", STYLES[self.style][shape])
                else:
                    raise GraphicsError("\n\nGraphicsError: arrow shape for line must be one of tuple of length 3 or a "
                                        f"string referencing a style, not {shape}")
        else:
            if scale:
                shape = list(STYLES[self.style]["arrowshape"])
                for i in range(len(shape)):
                    shape[i] = shape[i] * self.arrow_scale
                self._reconfig("arrowshape", shape)  # Changing the arrow
            else:
                self._reconfig("arrowshape", STYLES[self.style]["arrowshape"])

    def set_dash(self, dash):
        if dash is not None:  # Checking if the value is none, if it is, it becomes a solid line
            if isinstance(dash, str):
                if dash in STYLES[self.style].keys():
                    self._reconfig("dash", STYLES[self.style][dash])
                elif dash not in DASHES.keys():
                    raise GraphicsError(f"\n\nGraphicsError: Dash must be one of {DASHES.keys()}, not {dash}")
                else:
                    self._reconfig("dash", DASHES[dash])

            elif isinstance(dash, list) or isinstance(dash, tuple) or dash is None:
                if dash is not None:
                    for num in dash:
                        if (not 0 < num < 266) or not isinstance(num, int):
                            raise GraphicsError(f"\n\nGraphicsError: custom dash numbers must be integers within 1 & 255")
                self._reconfig("dash", dash)

            else:
                raise GraphicsError(f"\n\nLine dash must be a tuple or a string referencing a dash "
                                    f"(one of {DASHES.keys()}) or a style (or None for no dash), not {dash}")

    def set_bounds_width(self, width):
        if width is None:
            self.bounds_width = self.get_outline_width()
        else:
            if not (isinstance(width, float) or isinstance(width, int)):
                raise GraphicsError("\n\nGraphicsError: The bounds width for the line must be an integer or float, "
                                    f"not {width}")
            self.bounds_width = width

    # -------------------------------------------------------------------------
    # OTHER FUNCTIONS

    def is_clicked(self, mouse_pos):
        # Go through every line segment equation  and check if that segment has been clicked
        for eq in self.equations:
            if eq.is_clicked(mouse_pos):
                return True
        return False
