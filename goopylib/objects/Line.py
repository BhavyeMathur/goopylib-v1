from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib._internal_classes import VectorEquation
from goopylib.styles import *
from goopylib.constants import ARROWS, CAPSTYLES, JOINSTYLES, DASHES

from math import sin, cos, radians, atan

# The Line class is used for drawing straight lines segments between 2 or more points
class Line(GraphicsObject):

    def __init__(self, *p, style=None, outline=None, outline_width=None, arrow=None, capstyle=None, joinstyle=None,
                 cursor="arrow", arrow_shape=None, arrow_scale=None, dash=None, bounds_width=None, layer=0, tag=None):

        self.points = list(p)  # The list of points that define the line segment
        for p in self.points:
            if not isinstance(p, list):  # Checking if all the points specified are indeed list objects
                raise GraphicsError("\n\nGraphicsError: Points for Line class must be lists in the form [x, y], "
                                    f"not {p}")

        if len(p) < 2:  # Making sure there are at least 2 points
            raise GraphicsError(f"\n\nGraphicsError: There must be at least two points to create the line")

        self.low_x, self.low_y = None, None  # These variables are all defined in the get_size() function called below
        self.high_x, self.high_y = None, None  # They store the extreme x & y points farthest from the line's anchor
        self.outline_width, self.height = None, None

        self.get_size()  # Calculates the Width & Height of the line

        self.anchor = None  # The anchor is the center of the line
        self.get_anchor()  # It is calculated as the averages of all the points in the line

        GraphicsObject.__init__(self, options=["joinstyle", "arrowshape", "dash"],
                                cursor=cursor, layer=layer, tag=tag)

        self.arrow_scale_coeff = 1 if arrow_scale is None else arrow_scale

        if arrow is None:
            self.arrow = STYLES["default"]["arrow"]

        elif isinstance(arrow, str):
            arrow = arrow.lower()
            if arrow in ARROWS:  # Check if the Arrow specified is valid
                self.arrow = arrow
            else:
                raise GraphicsError(f"\n\nGraphicsError: capstyle for Line must be one of {ARROWS}, not {arrow}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: arrow option for Line must be one of {ARROWS}, not {arrow}")

        if outline is None:
            self.outline = STYLES["default"]["line outline"]
        elif isinstance(outline, Colour):  # Checking if the option is a colour
            self.outline = outline
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The line outline must be a Colour object , not {outline}")

        if outline_width is None:
            self.outline_width = STYLES["default"]["width"]
        elif isinstance(outline_width, int):  # Checking if the option is an integer
            self.outline_width = outline_width
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The line width must be an integer, not {outline_width}")
        self.arrow_scale = self.outline_width * self.arrow_scale_coeff

        if capstyle is None:
            self.capstyle = STYLES["default"]["capstyle"]
        elif isinstance(capstyle, str):
            capstyle = capstyle.lower()
            if capstyle in CAPSTYLES:
                self.capstyle = capstyle
        else:
            raise GraphicsError(f"\n\nGraphicsError: capstyle for line must be one of {CAPSTYLES}, not {style}")
        
        if joinstyle is None:
            self.joinstyle = STYLES["default"]["joinstyle"]
        elif isinstance(joinstyle, str):
            joinstyle = joinstyle.lower()
            if joinstyle in JOINSTYLES:
                self.joinstyle = joinstyle
        else:
            raise GraphicsError(f"\n\nGraphicsError: joinstyle for line must be one of {JOINSTYLES}, not {joinstyle}")
        
        if arrow_shape is None:
            self.arrow_shape = STYLES["default"]["arrowshape"]
        elif isinstance(arrow_shape, list):  # Check if the Arrow arrow_shape specified is valid
            if arrow_scale:
                arrow_shape = arrow_shape
                for i in range(len(arrow_shape)):
                    arrow_shape[i] = arrow_shape[i] * self.arrow_scale  # Scaling the arrow to match the width of the line
            self.arrow_shape = arrow_shape  # Changing the arrow
        else:
            raise GraphicsError(f"\n\nGraphicsError: arrow shape for line must be a list, not {arrow_shape}")

        if dash is None:  # Checking if the value is none, if it is, it becomes a solid line
            self.dash = None
        else:
            if dash in DASHES:
                self.dash = DASHES[dash]

            elif isinstance(dash, list):
                for num in dash:
                    if 0 < num < 266 and isinstance(num, int):
                        continue
                    else:
                        raise GraphicsError(f"\n\nGraphicsError: custom dash numbers must be integers within 1 & 255")
                self.dash = dash
            else:
                raise GraphicsError(f"\n\nLine dash must be a tuple or a string referencing a dash "
                                    f"(one of {DASHES.keys()}), not {dash}")

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
        points = [canvas.to_screen(point[0], point[1]) for point in self.points]
        return canvas.create_line(points, arrow=self.arrow, fill=self.outline, width=self.outline_width,
                                  capstyle=self.capstyle, joinstyle=self.joinstyle, arrowshape=self.arrow_shape,
                                  dash=self.dash)  # Creating the line!

    def _move(self, dx, dy):
        for i in range(len(self.points)):  # Going through all the points in the line
            self.points[i] += [dx, dy]  # And then moving them
        self.anchor = self.get_anchor()  # Recalculating the center of the line

    def _rotate(self, dr, scaling="bicubic", center=None):
        if center is None:
            center = self.get_anchor()  # Getting the center of rotation

        for point in self.points:
            # Formula from (https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d)
            p = point.clone()
            point[0] = cos(radians(dr)) * (p[0] - center[0]) - sin(radians(dr)) * (p[1] - center[1]) + center[0]
            point[1] = sin(radians(dr)) * (p[0] - center[0]) + cos(radians(dr)) * (p[1] - center[1]) + center[1]

    def _update(self):  # Called by the GraphicsObject class whenever the object rotates/moves and the __init__ function
        # These store the points for the line segments present in the line.
        # As this line object can have more than 2 points, it can be divided into segments of 2 points
        self.segments = [(self.points[i], self.points[i + 1]) for i in range(len(self.points) - 1)]
        self.equations = []  # The variable to store the Vector Equations of the line segments
        for line in self.segments:
            # For more information about these steps, see https://www.desmos.com/calculator/esn97hdwbe
            try:
                slope = (line[0][1] - line[1][1]) / (line[0][0] - line[1][0])  # Finding the slope of the line segment
                shift = - line[0][1] / slope  # Finding the x-shift

                # The height of the line to get it to be the correct amount of wide when rotated
                width = self.bounds_width / (cos(atan(slope)))

                smaller = min([line[0][0], line[1][0]])  # Which point has a smaller/larger x value?
                larger = max([line[0][0], line[1][0]])

                self.equations.append(VectorEquation(  # Creating the Vector Equation of this line segment
                    f"({slope} * (x - {shift} - {line[0][0]}) + {width}/2 > y > "
                    f"{slope} * (x - {shift} - {line[0][0]}) - {width}/2) and ({smaller} < x < {larger})"))

            except GraphicsError:  # The Line is Horizontal

                smaller = min([line[0][1], line[1][1]])  # Which point has a smaller/larger y value?
                larger = max([line[0][1], line[1][1]])

                self.equations.append(VectorEquation(
                    f"({line[0][0] + self.bounds_width/2} > x > {line[1][0] - self.bounds_width/2}) and"
                    f"({larger} > y > {smaller})"))

            except ZeroDivisionError:  # The Line is Vertical

                smaller = min([line[0][0], line[1][0]])  # Which point has a smaller/larger x value?
                larger = max([line[0][0], line[1][0]])

                self.equations.append(VectorEquation(
                    f"({line[0][1] + self.bounds_width/2}> y > {line[0][1] - self.bounds_width/2}) "
                    f"and ({smaller} < x < {larger})"))

        self.get_anchor()

    # -------------------------------------------------------------------------
    # GETTER FUNCTIONS

    def get_anchor(self):
        # To calculate the center, it simply calculates the Average of all the Points
        self.anchor = [0, 0]  # Starts the anchor at (0, 0)
        for point in self.points:
            self.anchor[0] += point[0]  # Sums up all the Point values
            self.anchor[1] += point[1]

        self.anchor[0] //= len(self.points)  # Divides by number of Points
        self.anchor[1] //= len(self.points)

        return self.anchor

    def get_width(self):
        # To calculate the width, it finds the smallest & largest x points and gets the width
        self.low_x = self.points[0][0]  # Setting the High & Low point to the first point
        self.high_x = self.low_x

        for point in self.points[1:]:  # Going through all the other points
            if point[0] < self.low_x:  # Checking if this point is smaller
                self.low_x = point[0]
            elif point[0] > self.high_x:  # Checking if this point is larger
                self.high_x = point[0]
        self.outline_width = abs(self.high_x - self.low_x)  # Getting the width

        return self.outline_width

    def get_height(self):
        # To calculate the height, it finds the smallest & largest y points and gets the height
        self.low_y = self.points[0][1]  # Setting the High & Low point to the first point
        self.high_y = self.low_y

        for point in self.points[1:]:  # Going through all the other points
            if point[1] < self.low_y:  # Checking if this point is smaller
                self.low_y = point[1]
            elif point[1] > self.high_y:  # Checking if this point is larger
                self.high_y = point[1]
        self.height = abs(self.high_y - self.low_y)  # Getting the height

        return self.height

    # These next functions return the value from the Object's config
    def get_outline_width(self):
        return self.outline_width

    def get_fill(self):
        return self.outline

    def get_arrow(self):
        return self.arrow

    def get_outline(self):
        return self.outline

    def get_capstyle(self):
        return self.capstyle

    def get_joinstyle(self):
        return self.joinstyle

    def get_arrow_shape(self):
        return self.arrow_shape

    def get_bounds_width(self):
        return self.bounds_width

    # -------------------------------------------------------------------------
    # SETTER FUNCTIONS

    def set_arrow(self, option):
        if option.lower() in ARROWS:  # Check if the Arrow specified is valid
            self.arrow = option
        else:
            raise GraphicsError(f"\n\nGraphicsError: arrow for line must be one of {ARROWS}, not {option}")

    # These arrow functions reference the set_arrow() function to set the arrow
    def remove_arrows(self):
        self.set_arrow("none")

    def set_arrow_both(self):
        self.set_arrow("both")

    def set_arrow_first(self):
        self.set_arrow("first")

    def set_arrow_last(self):
        self.set_arrow("last")

    def set_outline(self, outline):
        if isinstance(outline, Colour):  # Checking if the option is a colour
            self.outline = outline
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The line outline must be a Colour object , not {outline}")

    def set_outline_width(self, outline_width):
        if isinstance(outline_width, int):  # Checking if the option is an integer
            self.outline_width = outline_width
        else:  # If not, raise an error
            raise GraphicsError(f"\n\nGraphicsError: The line width must be an integer, not {outline_width}")

        self.arrow_scale = self.outline_width * self.arrow_scale_coeff
            
    def set_capstyle(self, style):
        style = style.lower()
        if style in CAPSTYLES:  # Check if the Arrow specified is valid
            self.capstyle = style  # Changing the arrow
        else:
            raise GraphicsError(f"\n\nGraphicsError: capstyle for line must be one of {CAPSTYLES}, not {style}")
    
    def set_joinstyle(self, joinstyle):
        joinstyle = joinstyle.lower()
        if joinstyle in JOINSTYLES:  # Check if the Arrow specified is valid
            self.joinstyle = joinstyle  # Changing the arrow
        else:
            raise GraphicsError(f"\n\nGraphicsError: joinstyle for line must be one of {JOINSTYLES}, not {joinstyle}")
            
    def set_arrow_shape(self, shape, scale=True):
        if isinstance(scale, bool):
            if isinstance(shape, list):  # Check if the Arrow shape specified is valid
                if scale:
                    shape = shape
                    for i in range(len(shape)):
                        shape[i] = shape[i] * self.arrow_scale  # Scaling the arrow to match the width of the line
                self.arrowshape = shape  # Changing the arrow
            else:
                raise GraphicsError(f"\n\nGraphicsError: arrow shape for line must be a list, not {shape}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: scale argument must be a boolean, not {scale}")

    def set_dash(self, dash):
        if dash is None:  # Checking if the value is none, if it is, it becomes a solid line
            self.dash = None
        else:
            if dash in DASHES:
                self.dash = DASHES[dash]

            elif isinstance(dash, list):
                for num in dash:
                    if 0 < num < 266 and isinstance(num, int):
                        continue
                    else:
                        raise GraphicsError(f"\n\nGraphicsError: custom dash numbers must be integers within 1 & 255")
                self.dash = dash
            else:
                raise GraphicsError(f"\n\nLine dash must be a tuple or a string referencing a dash "
                                    f"(one of {DASHES.keys()}), not {dash}")

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
