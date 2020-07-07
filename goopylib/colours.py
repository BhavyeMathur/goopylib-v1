from goopylib.util import GraphicsError
from random import randint as randomrandint

# Defining Custom  & colour Functions

class Colour:
    def __init_subclass__(cls, **kwargs):
        cls.colour = None

        cls.red = 0
        cls.green = 0
        cls.blue = 0

    def __str__(self):
        return self.colour

    def __repr__(self):
        return self.colour

    def __abs__(self):
        c_value = (self.red + self.green + self.blue) / 3
        return ColourRGB(c_value, c_value, c_value)

    def __sub__(self, other):
        try:
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue
        except AttributeError:
            red = self.red - other
            green = self.green - other
            blue = self.blue - other

        return ColourRGB(abs(red), abs(green), abs(blue))

    def __add__(self, other):
        try:
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue
        except AttributeError:
            red = self.red + other
            green = self.green + other
            blue = self.blue + other

        return ColourRGB(red, green, blue)

    def __mul__(self, other):
        try:
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue
        except AttributeError:
            red = self.red * other
            green = self.green * other
            blue = self.blue * other

        return ColourRGB(red, green, blue)

    def __floordiv__(self, other):
        try:
            red = self.red // other.red
            green = self.green // other.green
            blue = self.blue // other.blue
        except AttributeError:
            red = self.red // other
            green = self.green // other
            blue = self.blue // other

        return ColourRGB(red, green, blue)

    def __truediv__(self, other):
        return self // other

    def __mod__(self, other):
        try:
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue
        except AttributeError:
            red = self.red % other
            green = self.green % other
            blue = self.blue % other

        return ColourRGB(red, green, blue)
    
    def __pow__(self, power, modulo=None):
        try:
            red = self.red ** power.red
            green = self.green ** power.green
            blue = self.blue ** power.blue
        except AttributeError:
            red = self.red ** power
            green = self.green ** power
            blue = self.blue ** power

        return ColourRGB(red, green, blue) % modulo

    def __neg__(self):
        return ColourRGB(255 - self.red, 255 - self.green, 255 - self.blue)

    def __pos__(self):
        return ColourRGB(self.red, self.green, self.blue)

    def __lshift__(self, other):
        try:
            red = self.red << other.red
            green = self.green << other.green
            blue = self.blue << other.blue
        except AttributeError:
            red = self.red << other
            green = self.green << other
            blue = self.blue << other

        return ColourRGB(red, green, blue)

    def __rshift__(self, other):
        try:
            red = self.red >> other.red
            green = self.green >> other.green
            blue = self.blue >> other.blue
        except AttributeError:
            red = self.red >> other
            green = self.green >> other
            blue = self.blue >> other

        return ColourRGB(red, green, blue)

    def __xor__(self, other):
        try:
            red = self.red ^ other.red
            green = self.green ^ other.green
            blue = self.blue ^ other.blue
        except AttributeError:
            red = self.red ^ other
            green = self.green ^ other
            blue = self.blue ^ other

        return ColourRGB(red, green, blue)

    def __invert__(self):
        return -self

    def __and__(self, other):
        try:
            red = self.red & other.red
            green = self.green & other.green
            blue = self.blue & other.blue
        except AttributeError:
            red = self.red & other
            green = self.green & other
            blue = self.blue & other

        return ColourRGB(red, green, blue)
    
    def __or__(self, other):
        try:
            red = self.red | other.red
            green = self.green | other.green
            blue = self.blue | other.blue
        except AttributeError:
            red = self.red | other
            green = self.green | other
            blue = self.blue | other

        return ColourRGB(red, green, blue)

    def __bool__(self):
        if self.colour != "#000000":
            return True
        return False

    def __bytes__(self):
        return bytes(self.colour)

    def __contains__(self, item):
        if self.red == item or self.blue == item or self.green == item:
            return True
        elif item in self.colour[1:3] or item in self.colour[3:5] or item in self.colour[5:7]:
            return True
        elif isinstance(item, Colour):
            return item == self
        return False

    def __copy__(self):
        return ColourRGB(self.red, self.green, self.blue)

    def __lt__(self, other):
        return self.red + self.green + self.blue < other.red + other.green + other.blue

    def __le__(self, other):
        return self.red + self.green + self.blue <= other.red + other.green + other.blue

    def __gt__(self, other):
        return self.red + self.green + self.blue > other.red + other.green + other.blue

    def __ge__(self, other):
        return self.red + self.green + self.blue >= other.red + other.green + other.blue

    def __eq__(self, other):
        return self.colour == other.colour

    def __ne__(self, other):
        return self.colour != other.colour


class ColourRGB(Colour):
    def __init__(self, r, g, b):
        if not (isinstance(r, int) and isinstance(g, int) and isinstance(b, int)):
            raise GraphicsError("\n\nRGB values must be integers!")
        if not (256 > r > -1 and 256 > g > -1 and 256 > b > -1):
            raise GraphicsError(
                "\n\nRGB values must be between 0 & 255 (included), right now {}, {}, {}".format(r, g, b))
        self.colour = "#%02x%02x%02x" % (r, g, b)

        self.red = +r
        self.green = +g
        self.blue = +b


class ColourHex(Colour):
    def __init__(self, colour):
        if not isinstance(colour, str):
            raise GraphicsError("\n\nHex value must be a string in format: #rrggbb")
        if not 6 <= len(colour) <= 7:
            raise GraphicsError("\n\nThe length of the hex colour string must be 6: 'rrggbb'")

        if len(colour) == 6:
            self.colour = f"#{self.colour}"
        self.colour = colour

        colour = colour[1:]
        rgb = [int(colour[i:i+2], 16) for i in (0, 2, 4)]
        self.red = rgb[0]
        self.green = rgb[1]
        self.blue = rgb[2]


class ColourCMYK(Colour):
    def __init__(self, c, y, m, k):
        if not (isinstance(c, int) and isinstance(y, int) and isinstance(m, int) and isinstance(k, int)):
            raise GraphicsError("\n\nCMYK values must be integers!")
        if not (101 > c > -1 and 101 > y > -1 and 101 > m > -1 and 101 > k > -1):
            raise GraphicsError(f"\n\nCMYK values must be between 0 & 100 (included), right now {c}, {m}, {y}, {k}")

        r = 255 * (1 - (c + k) / 100)
        g = 255 * (1 - (m + k) / 100)
        b = 255 * (1 - (y + k) / 100)

        self.colour = "#%02x%02x%02x" % (r, g, b)

        self.red = r
        self.green = g
        self.blue = b


def RandomColour():
    return ColourRGB(randomrandint(0, 255), randomrandint(0, 255), randomrandint(0, 255))


def ColourGradient(colour_start=ColourRGB(255, 255, 255), colour_end=ColourRGB(0, 0, 0), divisions=10):
    red_dist = colour_end.red - colour_start.red
    green_dist = colour_end.green - colour_start.green
    blue_dist = colour_end.blue - colour_start.blue

    cur_red, cur_green, cur_blue = colour_start.red, colour_start.green, colour_start.blue

    gradient = []
    for i in range(divisions - 1):
        gradient.append(ColourRGB(max([0, cur_red]), max([cur_green, 0]), max([cur_blue, 0])))
        cur_red = colour_start.red + i * red_dist // divisions
        cur_green = colour_start.green + i * green_dist // divisions
        cur_blue = colour_start.blue + i * blue_dist // divisions

    gradient.append(colour_end)
    return gradient

def ColourGradient2D(colour_start1=ColourRGB(0, 0, 0), colour_end1=ColourRGB(255, 0, 0),
                     colour_start2=ColourRGB(255, 255, 255), colour_end2=ColourRGB(0, 255, 0),
                     divisions_x=10, divisions_y=10):

    top_gradient = ColourGradient(colour_start1, colour_end1, divisions=divisions_x)
    bottom_gradient = ColourGradient(colour_start2, colour_end2, divisions=divisions_x)

    cur_red, cur_green, cur_blue = colour_start1.red, colour_start1.green, colour_start1.blue

    gradient = [[None for _ in range(divisions_y)] for _ in range(divisions_x)]

    for col in range(divisions_x):
        gradient[col][0] = top_gradient[col]
        gradient[col][-1] = bottom_gradient[col]

    for col in range(len(gradient) - 70, len(gradient)):
        gradient[col] = ColourGradient(gradient[col][0], gradient[col][-1], divisions_y)

    return gradient


# The Blacks, Greys, and Whites
BLACK = ColourRGB(0, 0, 0)
DARKEST_GREY = ColourRGB(37, 37, 37)
DARKER_GREY = ColourRGB(40, 40, 40)
DARK_GREY = ColourRGB(45, 45, 45)

DARKISH_GREY = ColourRGB(60, 60, 60)
GREY = ColourRGB(100, 100, 100)
LIGHT_GREY = ColourRGB(160, 160, 160)
LIGHTER_GREY = ColourRGB(187, 187, 187)

DARK_WHITE = ColourRGB(240, 240, 240)
WHITE = ColourRGB(255, 255, 255)

# Blue-Greys
DARK_BLUE_GREY = ColourRGB(49, 51, 53)
BLUE_GREY = ColourRGB(60, 63, 65)
LIGHT_BLUE_GREY = ColourRGB(83, 95, 106)
LIGHTEST_BLUE_GREY = ColourRGB(173, 175, 177)

# Warm Colours
DARK_RED = ColourRGB(120, 0, 0)
RED = ColourRGB(175, 0, 0)
DARK_ORANGE = ColourRGB(255, 102, 0)
ORANGE = ColourRGB(255, 153, 0)
CHROME_YELLOW = ColourRGB(255, 204, 0)

# Greens
DARK_GREEN = ColourRGB(0, 104, 60)
OLIVE_GREEN = ColourRGB(0, 100, 5)
GREEN = ColourRGB(0, 123, 45)
LIGHT_GREEN = ColourRGB(51, 187, 15)

# Blues
DARKEST_NAVY_BLUE = ColourRGB(20, 27, 34)
DARKER_NAVY_BLUE = ColourRGB(30, 37, 44)
DARK_NAVY_BLUE = ColourRGB(38, 45, 56)
NAVY_BLUE = ColourRGB(45, 57, 68)
BLUE = ColourRGB(0, 153, 255)
CYAN = None

TURQUOISE = ColourRGB(79, 227, 194)

# Purples & Pinks
DARK_PURPLE = None
PURPLE = None
LIGHT_PURPLE = None
PINK = None
