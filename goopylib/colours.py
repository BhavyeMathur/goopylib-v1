from goopylib.util import GraphicsError
from goopylib.math.Interpolations import *

from random import randint as randomrandint

# -------------------------------------------------------------------------
# COLOUR CLASSES

class Colour:
    def __init_subclass__(cls, **kwargs):
        cls.colour = None
        cls.string = "colour"

        cls.red = 0
        cls.green = 0
        cls.blue = 0

    def __str__(self):
        return self.colour

    def __format__(self, format_spec):
        return self.string

    def __repr__(self):
        return self.string

    def __abs__(self):
        c_value = (self.red + self.green + self.blue) / 3
        return ColourRGB(c_value, c_value, c_value)

    def __sub__(self, other):
        if isinstance(other, Colour):
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue
        elif isinstance(other, int) or isinstance(other, float):
            red = self.red - other
            green = self.green - other
            blue = self.blue - other
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and {type(other)}'. Must be a Colour or int or float")

        return ColourRGB(max([red, 0]), max([green, 0]), max([blue, 0]))

    def __add__(self, other):
        if isinstance(other, Colour):
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue
        elif isinstance(other, int) or isinstance(other, float):
            red = (self.red + other) // 1
            green = (self.green + other) // 1
            blue = (self.blue + other) // 1
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and {type(other)}'. Must be a Colour or int or float")

        return ColourRGB(min([red, 255]), min([green, 255]), min([blue, 255]))

    def __mul__(self, other):
        if isinstance(other, Colour):
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue
        elif isinstance(other, int) or isinstance(other, float):
            red = (self.red * other) // 1
            green = (self.green * other) // 1
            blue = (self.blue * other) // 1
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and {type(other)}'. "
                            f"Must be a Colour or int or float")

        return ColourRGB(red, green, blue)

    def __floordiv__(self, other):
        if isinstance(other, Colour):
            red = self.red // other.red
            green = self.green // other.green
            blue = self.blue // other.blue
        elif isinstance(other, int) or isinstance(other, float):
            red = (self.red // other) // 1
            green = (self.green // other) // 1
            blue = (self.blue // other) // 1
        else:
            raise TypeError(f"unsupported operand type(s) for //: 'Colour' and {type(other)}'. Must be a Colour or int or float")

        return ColourRGB(red, green, blue)

    def __truediv__(self, other):
        return self // other

    def __mod__(self, other):
        if isinstance(other, Colour):
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue
        elif isinstance(other, int) or isinstance(other, float):
            red = (self.red % other) // 1
            green = (self.green % other) // 1
            blue = (self.blue % other) // 1
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and {type(other)}'. Must be a Colour or int or float")

        return ColourRGB(red, green, blue)
    
    def __pow__(self, power, modulo=None):
        if isinstance(power, Colour):
            red = pow(self.red, power.red, modulo)
            green = pow(self.green ** power.green, modulo)
            blue = pow(self.blue ** power.blue, modulo)
        elif isinstance(power, int) or isinstance(power, float):
            red = (pow(self.red ** power, modulo)) // 1
            green = (pow(self.green ** power, modulo)) // 1
            blue = (pow(self.blue ** power, modulo)) // 1
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and {type(power)}'. Must be a Colour or int or float")

        return ColourRGB(red, green, blue)

    def __neg__(self):
        return ColourRGB(255 - self.red, 255 - self.green, 255 - self.blue)

    def __pos__(self):
        return ColourRGB(self.red, self.green, self.blue)

    def __lshift__(self, other):
        if isinstance(other, Colour):
            red = self.red << other.red
            green = self.green << other.green
            blue = self.blue << other.blue
        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = green, blue, red
        else:
            raise TypeError(f"unsupported operand type(s) for <<: 'Colour' and {type(other)}'. Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __rshift__(self, other):
        if isinstance(other, Colour):
            red = self.red >> other.red
            green = self.green >> other.green
            blue = self.blue >> other.blue
        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = blue, red, green
        else:
            raise TypeError(f"unsupported operand type(s) for >>: 'Colour' and {type(other)}'. Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __xor__(self, other):
        if isinstance(other, Colour):
            red = self.red ^ other.red
            green = self.green ^ other.green
            blue = self.blue ^ other.blue
        elif isinstance(other, int):
            red = self.red ^ other
            green = self.green ^ other
            blue = self.blue ^ other
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and {type(other)}'. Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __and__(self, other):
        if isinstance(other, Colour):
            red = self.red & other.red
            green = self.green & other.green
            blue = self.blue & other.blue
        elif isinstance(other, int):
            red = self.red & other
            green = self.green & other
            blue = self.blue & other
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and {type(other)}'. Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __or__(self, other):
        if isinstance(other, Colour):
            red = self.red | other.red
            green = self.green | other.green
            blue = self.blue | other.blue
        elif isinstance(other, int):
            red = self.red | other
            green = self.green | other
            blue = self.blue | other
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and {type(other)}'. Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __invert__(self):
        return -self

    def __bool__(self):
        return self.colour != "#000000"

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
        if not isinstance(other, Colour):
            raise TypeError(f"'<' not supported between instances of 'Colour' and '{other}'.")
        return self.red + self.green + self.blue < other.red + other.green + other.blue

    def __le__(self, other):
        if not isinstance(other, Colour):
            raise TypeError(f"'<=' not supported between instances of 'Colour' and '{other}'.")
        return self.red + self.green + self.blue <= other.red + other.green + other.blue

    def __gt__(self, other):
        if not isinstance(other, Colour):
            raise TypeError(f"'>' not supported between instances of 'Colour' and '{other}'.")
        return self.red + self.green + self.blue > other.red + other.green + other.blue

    def __ge__(self, other):
        if not isinstance(other, Colour):
            raise TypeError(f"'>=' not supported between instances of 'Colour' and '{other}'.")
        return self.red + self.green + self.blue >= other.red + other.green + other.blue

    def __eq__(self, other):
        return self.colour == other.colour

    def __ne__(self, other):
        return self.colour != other.colour

    def __ceil__(self):
        return -(-self // 1)

    def __floor__(self):
        return self // 1

    def __divmod__(self, other):
        return self // other, self % other

    def __iadd__(self, other):
        self.red, self.green, self.blue = self + other
        return self

    def __hex__(self):
        return hex(self.red), hex(self.green), hex(self.blue)

    def __ilshift__(self, other):
        self.red, self.green, self.blue = self << other
        return self

    def __irshift__(self, other):
        self.red, self.green, self.blue = self >> other
        return self

    def __imod__(self, other):
        self.red, self.green, self.blue = self % other
        return self

    def __imul__(self, other):
        self.red, self.green, self.blue = self * other
        return self

    def __ior__(self, other):
        self.red, self.green, self.blue = self | other
        return self

    def __ipow__(self, other):
        self.red, self.green, self.blue = self ** other
        return self

    def __isub__(self, other):
        self.red, self.green, self.blue = self - other
        return self

    def __iand__(self, other):
        self.red, self.green, self.blue = self & other
        return self

    def __ifloordiv__(self, other):
        self.red, self.green, self.blue = self // other
        return self

    def __dir__(self):
        return "see https://github.com/BhavyeMathur/goopylib/wiki/Colours-in-Goopy!"

    def __ixor__(self, other):
        self.red, self.green, self.blue = self ^ other
        return self

    def __round__(self, n=None):
        red = 255 if self.red > 128 else 0
        green = 255 if self.green > 128 else 0
        blue = 255 if self.blue > 128 else 0

        return ColourRGB(red, green, blue)

    def __len__(self):
        return 3

    def __getitem__(self, item):
        if item > 2:
            raise IndexError(f"\n\nColour index must be less than 3, not {item}")
        return (self.red, self.green, self.blue)[item]

    def __iter__(self):
        for c in (self.red, self.green, self.blue):
            yield c

    def __itruediv__(self, other):
        self.red, self.green, self.blue = self / other
        return self

    def __oct__(self):
        return oct(self.red), oct(self.green), oct(self.blue)

    def __reversed__(self):
        return ColourRGB(self.blue, self.green, self.red)

    def rgb(self):
        return f"rgb {self.red}, {self.blue}, {self.green}"


class ColourRGB(Colour):
    def __init__(self, r, g, b):
        if not (isinstance(r, int) and isinstance(g, int) and isinstance(b, int)):
            raise GraphicsError("\n\nRGB values must be integers!")
        if not (256 > r > -1 and 256 > g > -1 and 256 > b > -1):
            raise GraphicsError(f"\n\nRGB values must be between 0 & 255 (included), right now {r}, {g}, {b}")
        self.colour = "#%02x%02x%02x" % (r, g, b)
        self.string = f"rgb {r}, {g}, {b}"

        self.red = +r
        self.green = +g
        self.blue = +b


class ColourHex(Colour):
    def __init__(self, colour):
        if not isinstance(colour, str):
            raise GraphicsError("\n\nHex value must be a string in format: #rrggbb")
        if len(colour) != 7:
            raise GraphicsError("\n\nThe length of the hex colour string must be 7: '#rrggbb'")
        try:
            if int(colour[1:], 16) > 16777215 or int(colour[1:], 16) < 0:
                raise GraphicsError(f"\n\nThe colour value must be between #000000 and #ffffff, not {colour}")
        except ValueError:
            raise GraphicsError(f"\n\nThe colour value must be a hexadecimal string, not {colour}")

        self.colour = colour
        self.string = self.colour

        colour = colour[1:]
        rgb = [int(colour[i:i+2], 16) for i in (0, 2, 4)]
        self.red = rgb[0]
        self.green = rgb[1]
        self.blue = rgb[2]


class ColourCMYK(Colour):
    def __init__(self, c, y, m, k):
        if not (isinstance(c, int) and isinstance(y, int) and isinstance(m, int) and isinstance(k, int)):
            raise GraphicsError(f"\n\nCMYK values must be integers! not {c}, {m}, {y}, {k}")
        if not (101 > c > -1 and 101 > y > -1 and 101 > m > -1 and 101 > k > -1):
            raise GraphicsError(f"\n\nCMYK values must be between 0 & 100 (included), not {c}, {m}, {y}, {k}")

        r = 255 * (1 - (c + k) // 100)
        g = 255 * (1 - (m + k) // 100)
        b = 255 * (1 - (y + k) // 100)

        self.colour = "#%02x%02x%02x" % (r, g, b)
        self.string = f"cmyk {c}, {m}, {y}, {k}"

        self.red = r
        self.green = g
        self.blue = b


# -------------------------------------------------------------------------
# RANDOM COLOUR FUNCTIONS

def RandomColourRGB(red=None, green=None, blue=None):
    if not isinstance(red, int):
        raise GraphicsError(f"\n\nThe red value must be an integer, not {red}")
    if not isinstance(green, int):
        raise GraphicsError(f"\n\nThe green value must be an integer, not {green}")
    if not isinstance(blue, int):
        raise GraphicsError(f"\n\nThe blue value must be an integer, not {blue}")

    if red > 255 or red < 0:
        raise GraphicsError(f"\n\nThe red value must be between 0 & 255 inclusive, not {red}")
    if green > 255 or green < 0:
        raise GraphicsError(f"\n\nThe green value must be between 0 & 255 inclusive, not {green}")
    if blue > 255 or blue < 0:
        raise GraphicsError(f"\n\nThe blue value must be between 0 & 255 inclusive, not {blue}")

    if red is None:
        red = randomrandint(0, 255)
    if green is None:
        green = randomrandint(0, 255)
    if blue is None:
        blue = randomrandint(0, 255)
    return ColourRGB(red, green, blue)

def RandomColourCMYK(c=None, m=None, y=None, k=None):
    if c is not None:
        if not isinstance(c, int):
            raise GraphicsError(f"\n\nThe c value must be an integer, not {c}")
        if c > 100 or c < 0:
            raise GraphicsError(f"\n\nThe c value must be between 0 & 100 inclusive, not {c}")
    else:
        c = randomrandint(0, 100)

    if m is not None:
        if not isinstance(m, int):
            raise GraphicsError(f"\n\nThe m value must be an integer, not {m}")
        if m > 100 or m < 0:
            raise GraphicsError(f"\n\nThe m value must be between 0 & 100 inclusive, not {m}")
    else:
        m = randomrandint(0, 100)

    if y is not None:
        if not isinstance(y, int):
            raise GraphicsError(f"\n\nThe y value must be an integer, not {y}")
        if y > 100 or y < 0:
            raise GraphicsError(f"\n\nThe y value must be between 0 & 100 inclusive, not {y}")
    else:
        y = randomrandint(0, 100)

    if k is not None:
        if not isinstance(k, int):
            raise GraphicsError(f"\n\nThe k value must be an integer, not {k}")
        if k > 100 or k < 0:
            raise GraphicsError(f"\n\nThe k value must be between 0 & 100 inclusive, not {k}")
    else:
        k = randomrandint(0, 100)

    return ColourCMYK(c, m, y, k)

def RandomColourHex(red=None, green=None, blue=None):
    if red is not None:
        if not isinstance(red, str):
            raise GraphicsError(f"\n\nThe red value must be an string, not {red}")
        if len(red) != 2:
            raise GraphicsError(f"\n\nThe red value must have a length of 2 #rr, not {red}")
        try:
            red = int(red, 16)
        except ValueError:
            raise GraphicsError(f"\n\nThe red value must be a base 16 value, not {red}")
    else:
        red = randomrandint(0, 255)

    if green is not None:
        if not isinstance(green, str):
            raise GraphicsError(f"\n\nThe green value must be an string, not {green}")
        if len(green) != 2:
            raise GraphicsError(f"\n\nThe green value must have a length of 2 #gg, not {green}")
        try:
            green = int(green, 16)
        except ValueError:
            raise GraphicsError(f"\n\nThe green value must be a base 16 value, not {green}")
    else:
        green = randomrandint(0, 255)

    if blue is not None:
        if not isinstance(blue, str):
            raise GraphicsError(f"\n\nThe blue value must be an string, not {blue}")
        if len(blue) != 2:
            raise GraphicsError(f"\n\nThe blue value must have a length of 2 #bb, not {blue}")
        try:
            blue = int(blue, 16)
        except ValueError:
            raise GraphicsError(f"\n\nThe blue value must be a base 16 value, not {blue}")
    else:
        blue = randomrandint(0, 255)

    if red > 255 or red < 0:
        raise GraphicsError(f"\n\nThe red value must be between 0 & 255 inclusive, not {red}")
    if green > 255 or green < 0:
        raise GraphicsError(f"\n\nThe green value must be between 0 & 255 inclusive, not {green}")
    if blue > 255 or blue < 0:
        raise GraphicsError(f"\n\nThe blue value must be between 0 & 255 inclusive, not {blue}")

    return ColourHex("#%02x%02x%02x" % (red, green, blue))

def RandomGreyscale(start=0, end=255):
    if not isinstance(start, int):
        raise GraphicsError(f"\n\nThe start value must be an integer, not {start}")
    if not isinstance(end, int):
        raise GraphicsError(f"\n\nThe end value must be an integer, not {end}")
    if start < 0 or start > end:
        raise GraphicsError(f"\n\nThe start value must be between 0 & end, 0 <= start <= {end}, not {start}")
    if end > 255 or end < start:
        raise GraphicsError(f"\n\nThe end value must be between start & 255, {start} <= end <= 255, not {end}")

    grey = randomrandint(start, end)
    return ColourRGB(grey, grey, grey)

# -------------------------------------------------------------------------
# COLOUR GRADIENT & INTERPOLATION FUNCTIONS

# Colour Gradients
def ColourGradient(colour_start=ColourRGB(255, 255, 255), colour_end=ColourRGB(0, 0, 0), divisions=10):

    if not isinstance(colour_start, Colour):
        raise GraphicsError(f"\n\nThe start colour (colour_start) must be a Colour object, not {colour_start}")
    if not isinstance(colour_end, Colour):
        raise GraphicsError(f"\n\nThe end colour (colour_end) must be a Colour object, not {colour_end}")
    if not isinstance(divisions, int):
        raise GraphicsError(f"\n\nThe number of divisions must be an integer, not {divisions}")

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

    if not isinstance(colour_start1, Colour):
        raise GraphicsError(f"\n\nThe start colour (colour_start1) must be a Colour object, not {colour_start1}")
    if not isinstance(colour_start2, Colour):
        raise GraphicsError(f"\n\nThe start colour (colour_start2) must be a Colour object, not {colour_start2}")
    if not isinstance(colour_end1, Colour):
        raise GraphicsError(f"\n\nThe end colour (colour_end1) must be a Colour object, not {colour_end1}")
    if not isinstance(colour_end2, Colour):
        raise GraphicsError(f"\n\nThe end colour (colour_end2) must be a Colour object, not {colour_end2}")

    if not isinstance(divisions_x, int):
        raise GraphicsError(f"\n\nThe X divisions (divisions_x) must be an integer, not {divisions_x}")
    if not isinstance(divisions_y, int):
        raise GraphicsError(f"\n\nThe Y divisions (divisions_y) must be an integer, not {divisions_y}")

    top_gradient = ColourGradient(colour_start1, colour_end1, divisions=divisions_x)
    bottom_gradient = ColourGradient(colour_start2, colour_end2, divisions=divisions_x)

    cur_red, cur_green, cur_blue = colour_start1.red, colour_start1.green, colour_start1.blue

    gradient = [[None for _ in range(divisions_y)] for _ in range(divisions_x)]

    for col in range(divisions_x):
        gradient[col][0] = top_gradient[col]
        gradient[col][-1] = bottom_gradient[col]

    for col in range(0, len(gradient)):
        gradient[col] = ColourGradient(gradient[col][0], gradient[col][-1], divisions_y)

    return gradient

# Colour Blending
def BlendLinear(colour_start, colour_end, t):
    return ColourRGB(int(LinearInterpolation(colour_start.red, colour_end.red, t)),
                     int(LinearInterpolation(colour_start.green, colour_end.green, t)),
                     int(LinearInterpolation(colour_start.blue, colour_end.blue, t)))

def BlendCosine(colour_start, colour_end, t):
    return ColourRGB(int(CosineInterpolation(colour_start.red, colour_end.red, t)),
                     int(CosineInterpolation(colour_start.green, colour_end.green, t)),
                     int(CosineInterpolation(colour_start.blue, colour_end.blue, t)))

def BlendCubic(colour_start, colour_end, t):
    return ColourRGB(int(CubicInterpolation(colour_start.red, colour_start.red, colour_end.red, colour_end.red, t)),
                     int(CubicInterpolation(colour_start.green, colour_start.green, colour_end.green, colour_end.green, t)),
                     int(CubicInterpolation(colour_start.blue, colour_start.blue, colour_end.blue, colour_end.blue, t)))

def BlendHermite(colour_start, colour_end, t, tension=1, bias=0):
    return ColourRGB(int(HermiteInterpolation(colour_start.red, colour_start.red, colour_end.red, colour_end.red, t,
                                              tension=tension, bias=bias)),
                     int(HermiteInterpolation(colour_start.green, colour_start.green, colour_end.green,
                                              colour_end.green, t, tension=tension, bias=bias)),
                     int(HermiteInterpolation(colour_start.blue, colour_start.blue, colour_end.blue, colour_end.blue, t,
                                              tension=tension, bias=bias)))


# -------------------------------------------------------------------------
# COLOUR DEFINITIONS

# The Blacks, Greys, and Whites
BLACK = ColourRGB(0, 0, 0)
DARKEST_GREY = ColourRGB(30, 30, 30)
DARKER_GREY = ColourRGB(40, 40, 40)
DARK_GREY = ColourRGB(45, 45, 45)

DARKISH_GREY = ColourRGB(60, 60, 60)
GREY = ColourRGB(100, 100, 100)
LIGHTISH_GREY = ColourRGB(130, 130, 130)
LIGHT_GREY = ColourRGB(160, 160, 160)
LIGHTER_GREY = ColourRGB(187, 187, 187)
LIGHTEST_GREY = ColourRGB(210, 210, 210)

DARK_WHITE = ColourRGB(240, 240, 240)
WHITE = ColourRGB(255, 255, 255)

# Blue-Greys
DARKEST_BLUE_GREY = ColourRGB(30, 32, 34)
DARKER_BLUE_GREY = ColourRGB(40, 42, 44)
DARK_BLUE_GREY = ColourRGB(49, 51, 53)

DARKISH_BLUE_GREY = ColourRGB(55, 57, 59)
BLUE_GREY = ColourRGB(63, 75, 86)
LIGHTISH_BLUE_GREY = ColourRGB(83, 95, 106)
LIGHT_BLUE_GREY = ColourRGB(103, 115, 126)
LIGHTER_BLUE_GREY = ColourRGB(133, 145, 156)
LIGHTEST_BLUE_GREY = ColourRGB(173, 185, 196)

# Warm Colours
DARKEST_RED = ColourRGB(48, 11, 8)
DARKER_RED = ColourRGB(64, 13, 9)
DARK_RED = ColourRGB(99, 18, 12)

DARKISH_RED = ColourRGB(143, 23, 12)
RED = ColourRGB(194, 22, 6)
LIGHTISH_RED = ColourRGB(224, 66, 52)
LIGHT_RED = ColourRGB(255, 94, 79)

PINK = ColourRGB(255, 122, 110)
LIGHTISH_PINK = ColourRGB(255, 133, 122)
LIGHT_PINK = ColourRGB(255, 161, 153)
LIGHTER_PINK = ColourRGB(255, 194, 189)
LIGHTEST_PINK = ColourRGB(255, 224, 222)

ABSOLUTE_RED = ColourRGB(255, 0, 0)


# Orange & Brown Shades from: https://graf1x.com/shades-of-orange-color-palette/
# ORANGES
MELON_ORANGE = ColourRGB(247, 152, 98)
SALAMANDER_ORANGE = ColourRGB(240, 94, 35)
SANDSTONE_ORANGE = ColourRGB(215, 144, 44)
GINGER_ORANGE = ColourRGB(190, 85, 4)
SQUASH_ORANGE = ColourRGB(203, 92, 13)

ORANGE = ColourRGB(252, 102, 0)
ROYAL_ORANGE = ColourRGB(249, 129, 42)
TIGER_ORANGE = ColourRGB(253, 106, 2)
APRICOT_ORANGE = ColourRGB(239, 130, 13)
OCHRE_ORANGE = ColourRGB(204, 119, 34)
FIRE_ORANGE = ColourRGB(253, 165, 15)
CARROT_ORANGE = ColourRGB(239, 114, 21)
PUMPKIN_ORANGE = ColourRGB(255, 116, 23)
HONEY_ORANGE = ColourRGB(235, 150, 5)

# BROWNS

DARK_AMBER_BROWN = ColourRGB(136, 48, 0)
BRONZE_BROWN = ColourRGB(177, 86, 15)
CLAY_BROWN = ColourRGB(129, 63, 11)
BURNT_BROWN = ColourRGB(150, 64, 0)

LIGHTEST_BROWN = ColourRGB(168, 145, 113)
LIGHTER_BROWN = ColourRGB(145, 119, 83)
LIGHT_BROWN = ColourRGB(122, 91, 47)
BROWN = ColourRGB(156, 91, 0)
DARKER_BROWN = ColourRGB(94, 62, 18)
DARKEST_BROWN = ColourRGB(64, 38, 3)

# YELLOWS
# From https://graf1x.com/shades-of-yellow-color-palette-chart/

GOLD = ColourRGB(249, 166, 2)
GOLDENROD_YELLOW = ColourRGB(218, 165, 32)
YELLOW = ColourRGB(252, 226, 5)

AMBER_YELLOW = ColourRGB(255, 191, 0)
ROYAL_YELLOW = ColourRGB(250, 218, 94)
MUSTARD_YELLOW = ColourRGB(254, 220, 86)
MELLOW_YELLOW = ColourRGB(248, 222, 126)
FLAX_YELLOW = ColourRGB(238, 220, 130)
CREAM_YELLOW = ColourRGB(255, 253, 208)
CHROME_YELLOW = ColourRGB(255, 204, 0)
TROMBONE_YELLOW = ColourRGB(210, 181, 91)

ABSOLUTE_YELLOW = ColourRGB(255, 255, 0)

# Greens

LIGHTEST_OLIVE_GREEN = ColourHex("#d2e190")
LIGHTER_OLIVE_GREEN = ColourHex("#b5cf49")
LIGHT_OLIVE_GREEN = ColourHex("#a3bf45")
OLIVE_GREEN = ColourHex("#81a140")
DARK_OLIVE_GREEN = ColourHex("#74923a")
DARKER_OLIVE_GREEN = ColourHex("#617b30")
DARKEST_OLIVE_GREEN = ColourHex("#42541f")

LIGHTEST_GREEN = ColourHex("#c8e6c9")
LIGHTER_GREEN = ColourHex("#a5d6a7")
LIGHT_GREEN = ColourHex("#81c784")
LIGHTISH_GREEN = ColourHex("#66bb6a")
GREEN = ColourHex("#4caf50")
DARKISH_GREEN = ColourHex("#43a047")
DARK_GREEN = ColourHex("#388e3c")
DARKER_GREEN = ColourHex("#2e7d32")
DARKEST_GREEN = ColourHex("#1b5e20")

ABSOLUTE_GREEN = ColourRGB(0, 255, 0)

# Blues
DARKEST_NAVY_BLUE = ColourRGB(20, 27, 34)
DARKER_NAVY_BLUE = ColourRGB(30, 37, 44)
DARK_NAVY_BLUE = ColourRGB(38, 45, 56)
NAVY_BLUE = ColourRGB(45, 57, 68)
LIGHTISH_NAVY_BLUE = ColourHex("#23395d")
LIGHT_NAVY_BLUE = ColourRGB(45, 67, 103)
LIGHTER_NAVY_BLUE = ColourRGB(65, 87, 123)
LIGHTEST_NAVY_BLUE = ColourRGB(85, 107, 143)

LIGHTEST_BLUE = ColourHex("#e3f2fd")
LIGHTER_BLUE = ColourHex("#bbdefb")
LIGHT_BLUE = ColourHex("#90caf9")
LIGHTISH_BLUE = ColourHex("#64b5f6")
BLUE = ColourHex("#21a5f5")
DARKISH_BLUE = ColourHex("#1e88e5")
DARK_BLUE = ColourHex("#1976d2")
DARKER_BLUE = ColourHex("#1565c0")
DARKEST_BLUE = ColourHex("#0c46a0")

ABSOLUTE_BLUE = ColourRGB(0, 0, 255)

DARKEST_TURQUOISE = ColourRGB(0, 56, 41)
DARKER_TURQUOISE = ColourHex("#006a4e")
DARK_TURQUOISE = ColourHex("#2e856e")
TURQUOISE = ColourHex("#5ca08e")
LIGHT_TURQUOISE = ColourHex("#8abaae")
LIGHTER_TURQUOISE = ColourHex("#b8d5cd")

# Purples & Violets
LIGHTEST_PURPLE = ColourHex("#e1bee7")
LIGHTER_PURPLE = ColourHex("#ce93d8")
LIGHT_PURPLE = ColourHex("#ba68c8")
LIGHTISH_PURPLE = ColourHex("#ab47bc")
PURPLE = ColourHex("#9c27b0")
DARKISH_PURPLE = ColourHex("#8e24aa")
DARK_PURPLE = ColourHex("#7b1fa2")
DARKER_PURPLE = ColourHex("#6a1b9a")
DARKEST_PURPLE = ColourHex("#4a148c")

LIGHTEST_VIOLET = ColourHex("#d1c4e9")
LIGHTER_VIOLET = ColourHex("#b39ddb")
LIGHT_VIOLET = ColourHex("#9575cd")
LIGHTISH_VIOLET = ColourHex("#7e57c2")
VIOLET = ColourHex("#673ab7")
DARKISH_VIOLET = ColourHex("#5e35b1")
DARK_VIOLET = ColourHex("#512da8")
DARKER_VIOLET = ColourHex("#4527a0")
DARKEST_VIOLET = ColourHex("#311b92")
