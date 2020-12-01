from random import randint as randomrandint

from goopylib.math.Interpolations import *

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

    def __reversed__(self):
        return ColourRGB(self.blue, self.green, self.red)

    def rgb(self):
        return f"rgb {self.red}, {self.blue}, {self.green}"


class ColourRGB(Colour):
    def __init__(self, r, g, b):
        if not (isinstance(r, int) and isinstance(g, int) and isinstance(b, int)):
            raise GraphicsError(f"\n\nGraphicsError: GraphicsError: RGB values must be integers! not {r}, {g}, {b}")
        if not (256 > r > -1 and 256 > g > -1 and 256 > b > -1):
            raise GraphicsError(f"\n\nGraphicsError: RGB values must be between 0 & 255 (included), not {r}, {g}, {b}")
        self.colour = "#%02x%02x%02x" % (r, g, b)
        self.string = f"rgb {r}, {g}, {b}"

        self.red = r
        self.green = g
        self.blue = b


class ColourHex(Colour):
    def __init__(self, colour):
        if not isinstance(colour, str):
            raise GraphicsError("\n\nGraphicsError: Hex value must be a string in format: #rrggbb")
        if len(colour) != 7:
            raise GraphicsError("\n\nGraphicsError: The length of the hex colour string must be 7: '#rrggbb'")
        try:
            if int(colour[1:], 16) > 16777215 or int(colour[1:], 16) < 0:
                raise GraphicsError("\n\nGraphicsError: The colour value must be between #000000 and #ffffff, "
                                    f"not {colour}")
        except ValueError:
            raise GraphicsError(f"\n\nGraphicsError: The colour value must be a hexadecimal string, not {colour}")

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
            raise GraphicsError(f"\n\nGraphicsError: CMYK values must be integers! not {c}, {m}, {y}, {k}")
        if not (101 > c > -1 and 101 > y > -1 and 101 > m > -1 and 101 > k > -1):
            raise GraphicsError("\n\nGraphicsError: CMYK values must be between 0 & 100 (included), "
                                f"not {c}, {m}, {y}, {k}")

        r = 255 * (1 - (c + k) // 100)
        g = 255 * (1 - (m + k) // 100)
        b = 255 * (1 - (y + k) // 100)

        self.colour = "#%02x%02x%02x" % (r, g, b)
        self.string = f"cmyk {c}%, {m}%, {y}%, {k}%"

        self.red = r
        self.green = g
        self.blue = b


class ColourHSV(Colour):
    def __init__(self, h, s, v):
        if isinstance(h, int) and isinstance(s, (float, int)) and isinstance(v, (float, int)):
            if 360 > h > -1:
                if s > 1 or s < 0:
                    raise GraphicsError("\n\nGraphicsError: s value for HSV colour must be between 0 & 1, 1 >= s >= 0, "
                                        f"not {s}")
                if v > 1 or v < 0:
                    raise GraphicsError("\n\nGraphicsError: v value for HSV colour must be between 0 & 1, 1 >= v >= 0, "
                                        f"not {v}")

                c = v * s
                x = c * (1 - abs((h / 60) % 2 - 1))
                m = v - c

                if h < 60:
                    rgb_ = (c, x, 0)
                elif h < 120:
                    rgb_ = (x, c, 0)
                elif h < 180:
                    rgb_ = (0, x, x)
                elif h < 240:
                    rgb_ = (0, x, c)
                elif h < 300:
                    rgb_ = (x, 0, c)
                else:
                    rgb_ = (c, 0, x)
    
                r = int(255 * (rgb_[0] + m))
                g = int(255 * (rgb_[1] + m))
                b = int(255 * (rgb_[2] + m))
    
                self.colour = "#%02x%02x%02x" % (r, g, b)
                self.string = f"hsv {h}°, {s}%, {v}%"
    
                self.red = r
                self.green = g
                self.blue = b
            else:
                raise GraphicsError(f"\n\nGraphicsError: h value for HSV colour must be between 0 & 359, 360 > h >= 0, "
                                    f"not {h}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: HSV values must be integers (H) & floats (S & V)! not {h}, {s}, "
                                f"{v}")


class ColourHSL(Colour):
    def __init__(self, h, s, l):
        if isinstance(h, int) and isinstance(s, (float, int)) and isinstance(l, (float, int)):
            if 360 > h > -1:
                if s > 1 or s < 0:
                    raise GraphicsError("\n\nGraphicsError: s value for HSL colour must be between 0 & 1, 1 >= s >= 0, "
                                        f"not {s}")
                if l > 1 or l < 0:
                    raise GraphicsError("\n\nGraphicsError: l value for HSL colour must be between 0 & 1, 1 >= l >= 0, "
                                        f"not {l}")

                c = (1 - abs(2*l - 1)) * s
                x = c * (1 - abs((h / 60) % 2 - 1))
                m = l - c / 2

                if h < 60:
                    rgb_ = (c, x, 0)
                elif h < 120:
                    rgb_ = (x, c, 0)
                elif h < 180:
                    rgb_ = (0, x, x)
                elif h < 240:
                    rgb_ = (0, x, c)
                elif h < 300:
                    rgb_ = (x, 0, c)
                else:
                    rgb_ = (c, 0, x)

                r = int(255 * (rgb_[0] + m))
                g = int(255 * (rgb_[1] + m))
                b = int(255 * (rgb_[2] + m))

                self.colour = "#%02x%02x%02x" % (r, g, b)
                self.string = f"hsl {h}°, {s}%, {l}%"

                self.red = r
                self.green = g
                self.blue = b
            else:
                raise GraphicsError(f"\n\nGraphicsError: h value for HSL colour must be between 0 & 359, 360 > h >= 0, "
                                    f"not {h}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: HSL values must be integers (H) & floats (S & V)! not {h}, {s}, "
                                f"{l}")


Color = Colour
ColorRGB = ColourRGB
ColorHex = ColourHex
ColorCMYK = ColourCMYK
ColorHSV = ColourHSV
ColorHSL = ColourHSL

# -------------------------------------------------------------------------
# RANDOM COLOUR FUNCTIONS

def random_colour_rgb(red=None, green=None, blue=None):
    if red is None:
        red = randomrandint(0, 255)
    elif isinstance(red, int):
        if red > 255 or red < 0:
            raise GraphicsError(f"\n\nThe red value must be between 0 & 255 inclusive, not {red}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The red value must be an integer or None, not {red}")

    if green is None:
            green = randomrandint(0, 255)
    elif isinstance(green, int):
        if green > 255 or green < 0:
            raise GraphicsError(f"\n\nThe green value must be between 0 & 255 inclusive, not {green}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The green value must be an integer or None, not {green}")

    if blue is None:
        blue = randomrandint(0, 255)
    elif isinstance(blue, int):
        if blue > 255 or blue < 0:
            raise GraphicsError(f"\n\nGraphicsError: The blue value must be between 0 & 255 inclusive, not {blue}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The blue value must be an integer or None, not {blue}")

    return ColourRGB(red, green, blue)

def random_colour_cmyk(c=None, m=None, y=None, k=None):
    if c is None:
        c = randomrandint(0, 100)
    elif isinstance(c, int):
        if c > 100 or c < 0:
            raise GraphicsError(f"\n\nGraphicsError: The c value must be between 0 & 100 inclusive, not {c}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The c value must be an integer or None, not {c}")

    if m is None:
        m = randomrandint(0, 100)
    elif isinstance(m, int):
        if m > 100 or m < 0:
            raise GraphicsError(f"\n\nGraphicsError: The m value must be between 0 & 100 inclusive, not {m}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The m value must be an integer or None, not {m}")

    if y is None:
        y = randomrandint(0, 100)
    elif isinstance(y, int):
        if y > 100 or y < 0:
            raise GraphicsError(f"\n\nGraphicsError: The y value must be between 0 & 100 inclusive, not {y}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: he y value must be an integer or None, not {y}")

    if k is None:
        k = randomrandint(0, 100)
    elif isinstance(k, int):
        if k > 100 or k < 0:
            raise GraphicsError(f"\n\nGraphicsError: The k value must be between 0 & 100 inclusive, not {k}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The k value must be an integer or None, not {k}")

    return ColourCMYK(c, m, y, k)

def random_colour_hex(red=None, green=None, blue=None):
    if red is None:
        red = randomrandint(0, 255)
    else:
        if not isinstance(red, str):
            raise GraphicsError(f"\n\nGraphicsError: The red value must be an string, not {red}")
        if len(red) != 2:
            raise GraphicsError(f"\n\nGraphicsError: The red value must have a length of 2 #rr, not {red}")
        try:
            red = int(red, 16)
        except ValueError:
            raise GraphicsError(f"\n\nGraphicsError: The red value must be a base 16 value, not {red}")

    if green is None:
        green = randomrandint(0, 255)
    else:
        if isinstance(green, str):
            if len(green) == 2:
                try:
                    green = int(green, 16)
                except ValueError:
                    raise GraphicsError(f"\n\nGraphicsError: The green value must be a base 16 value, not {green}")
            else:
                raise GraphicsError(f"\n\nGraphicsError: The green value must have a length of 2 #gg, not {green}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The green value must be an string, not {green}")

    if blue is None:
        blue = randomrandint(0, 255)
    else:
        if isinstance(blue, str):
            if len(blue) == 2:
                try:
                    blue = int(blue, 16)
                except ValueError:
                    raise GraphicsError(f"\n\nGraphicsError: The blue value must be a base 16 value, not {blue}")
            else:
                raise GraphicsError(f"\n\nGraphicsError: The blue value must have a length of 2 #bb, not {blue}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The blue value must be an string, not {blue}")

    if red > 255 or red < 0:
        raise GraphicsError(f"\n\nGraphicsError: The red value must be between 0 & 255 inclusive, not {red}")
    if green > 255 or green < 0:
        raise GraphicsError(f"\n\nGraphicsError: The green value must be between 0 & 255 inclusive, not {green}")
    if blue > 255 or blue < 0:
        raise GraphicsError(f"\n\nGraphicsError: The blue value must be between 0 & 255 inclusive, not {blue}")

    return ColourHex("#%02x%02x%02x" % (red, green, blue))

def random_colour_hsv(h=None, s=None, v=None):
    if h is None:
        h = randomrandint(0, 359)
    elif isinstance(h, int):
        if h > 359 or h < 0:
            raise GraphicsError(f"\n\nGraphicsError: The h value must be between 0 & 100 inclusive, not {h}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The h value must be an integer or None, not {h}")

    if s is None:
        s = randomrandint(0, 100) / 100
    elif isinstance(s, (float, int)):
        if s > 1 or s < 0:
            raise GraphicsError(f"\n\nGraphicsError: The s value must be between 0 & 1 inclusive, not {s}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The s value must be an integer or float or None, not {s}")

    if v is None:
        v = randomrandint(0, 100) / 100
    elif isinstance(v, (float, int)):
        if v > 1 or v < 0:
            raise GraphicsError(f"\n\nGraphicsError: The v value must be between 0 & 1 inclusive, not {v}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The v value must be an integer or float or None, not {v}")

    return ColourHSV(h, s, v)

# L used instead of l because of PEP8
def random_colour_hsl(h=None, s=None, l=None):
    if h is None:
        h = randomrandint(0, 359)
    elif isinstance(h, int):
        if h > 359 or h < 0:
            raise GraphicsError(f"\n\nGraphicsError: The h value must be between 0 & 100 inclusive, not {h}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The h value must be an integer or None, not {h}")

    if s is None:
        s = randomrandint(0, 100) / 100
    elif isinstance(s, (float, int)):
        if s > 1 or s < 0:
            raise GraphicsError(f"\n\nGraphicsError: The s value must be between 0 & 1 inclusive, not {s}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The s value must be an integer or float or None, not {s}")

    if l is None:
        l = randomrandint(0, 100) / 100
    elif isinstance(l, (float, int)):
        if l > 1 or l < 0:
            raise GraphicsError(f"\n\nGraphicsError: The l value must be between 0 & 1 inclusive, not {l}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The l value must be an integer or float or None, not {l}")

    return ColourHSL(h, s, l)

def random_greyscale(start=0, end=255):
    if isinstance(start, int):
        if isinstance(end, int):
            if start < 0 or start > end:
                raise GraphicsError("\n\nGraphicsError: The start value must be between 0 & end, 0 <= start <="
                                    f" {end}, not {start}")
            if end > 255 or end < start:
                raise GraphicsError("\n\nGraphicsError: The end value must be between start & 255, "
                                    f"{start} <= end <= 255, not {end}")

            grey = randomrandint(start, end)
            return ColourRGB(grey, grey, grey)
        else:
            raise GraphicsError(f"\n\nGraphicsError: The end value must be an integer, not {end}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The start value must be an integer, not {start}")


random_color_rgb = random_colour_rgb
random_color_cmyk = random_colour_cmyk
random_color_hex = random_colour_hex
random_color_hsv = random_colour_hsv
random_color_hsl = random_colour_hsl

# -------------------------------------------------------------------------
# COLOUR GRADIENT & INTERPOLATION FUNCTIONS

# Colour Gradients
def colour_gradient(colour_start=ColourRGB(255, 255, 255), colour_end=ColourRGB(0, 0, 0), divisions=10):

    if not isinstance(colour_start, Colour):
        raise GraphicsError("\n\nGraphicsError: The start colour (colour_start) must be a Colour object, "
                            f"not {colour_start}")
    if not isinstance(colour_end, Colour):
        raise GraphicsError(f"\n\nGraphicsError: The end colour (colour_end) must be a Colour object, not {colour_end}")
    if not isinstance(divisions, int):
        raise GraphicsError(f"\n\nGraphicsError: The number of divisions must be an integer, not {divisions}")

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

def color_gradient(color_start=ColourRGB(255, 255, 255), color_end=ColourRGB(0, 0, 0), divisions=10):

    if not isinstance(color_start, Colour):
        raise GraphicsError("\n\nGraphicsError: The start color (color_start) must be a Color object, "
                            f"not {color_start}")
    if not isinstance(color_end, Colour):
        raise GraphicsError(f"\n\nGraphicsError: The end color (color_end) must be a Color object, not {color_end}")
    if not isinstance(divisions, int):
        raise GraphicsError(f"\n\nGraphicsError: The number of divisions must be an integer, not {divisions}")

    red_dist = color_end.red - color_start.red
    green_dist = color_end.green - color_start.green
    blue_dist = color_end.blue - color_start.blue

    cur_red, cur_green, cur_blue = color_start.red, color_start.green, color_start.blue

    gradient = []
    for i in range(divisions - 1):
        gradient.append(ColourRGB(max([0, cur_red]), max([cur_green, 0]), max([cur_blue, 0])))
        cur_red = color_start.red + i * red_dist // divisions
        cur_green = color_start.green + i * green_dist // divisions
        cur_blue = color_start.blue + i * blue_dist // divisions

    gradient.append(color_end)
    return gradient

def colour_gradient_2d(colour_start1=ColourRGB(0, 0, 0), colour_end1=ColourRGB(255, 0, 0),
                       colour_start2=ColourRGB(255, 255, 255), colour_end2=ColourRGB(0, 255, 0),
                       divisions_x=10, divisions_y=10):

    if not isinstance(colour_start1, Colour):
        raise GraphicsError("\n\nGraphicsError: The start colour (colour_start1) must be a Colour object, "
                            f"not {colour_start1}")
    if not isinstance(colour_start2, Colour):
        raise GraphicsError("\n\nGraphicsError: The start colour (colour_start2) must be a Colour object, "
                            f"not {colour_start2}")
    if not isinstance(colour_end1, Colour):
        raise GraphicsError("\n\nGraphicsError: The end colour (colour_end1) must be a Colour object, "
                            f"not {colour_end1}")
    if not isinstance(colour_end2, Colour):
        raise GraphicsError("\n\nGraphicsError: The end colour (colour_end2) must be a Colour object, "
                            f"not {colour_end2}")

    if not isinstance(divisions_x, int):
        raise GraphicsError(f"\n\nGraphicsError: The X divisions (divisions_x) must be an integer, not {divisions_x}")
    if not isinstance(divisions_y, int):
        raise GraphicsError(f"\n\nGraphicsError: The Y divisions (divisions_y) must be an integer, not {divisions_y}")

    top_gradient = colour_gradient(colour_start1, colour_end1, divisions=divisions_x)
    bottom_gradient = colour_gradient(colour_start2, colour_end2, divisions=divisions_x)

    cur_red, cur_green, cur_blue = colour_start1.red, colour_start1.green, colour_start1.blue

    gradient = [[None for _ in range(divisions_y)] for _ in range(divisions_x)]

    for col in range(divisions_x):
        gradient[col][0] = top_gradient[col]
        gradient[col][-1] = bottom_gradient[col]

    for col in range(0, len(gradient)):
        gradient[col] = colour_gradient(gradient[col][0], gradient[col][-1], divisions_y)

    return gradient

def color_gradient_2d(colour_start1=ColourRGB(0, 0, 0), color_end1=ColourRGB(255, 0, 0),
                      color_start2=ColourRGB(255, 255, 255), color_end2=ColourRGB(0, 255, 0),
                      divisions_x=10, divisions_y=10):

    if not isinstance(color_start1, Colour):
        raise GraphicsError("\n\nGraphicsError: The start color (color_start1) must be a Color object, "
                            f"not {color_start1}")
    if not isinstance(color_start2, Colour):
        raise GraphicsError("\n\nGraphicsError: The start color (color_start2) must be a Color object, "
                            f"not {color_start2}")
    if not isinstance(color_end1, Colour):
        raise GraphicsError("\n\nGraphicsError: The end color (color_end1) must be a Color object, "
                            f"not {color_end1}")
    if not isinstance(color_end2, Colour):
        raise GraphicsError("\n\nGraphicsError: The end color (color_end2) must be a Color object, "
                            f"not {color_end2}")

    if not isinstance(divisions_x, int):
        raise GraphicsError(f"\n\nGraphicsError: The X divisions (divisions_x) must be an integer, not {divisions_x}")
    if not isinstance(divisions_y, int):
        raise GraphicsError(f"\n\nGraphicsError: The Y divisions (divisions_y) must be an integer, not {divisions_y}")

    top_gradient = color_gradient(color_start1, color_end1, divisions=divisions_x)
    bottom_gradient = color_gradient(color_start2, color_end2, divisions=divisions_x)

    cur_red, cur_green, cur_blue = color_start1.red, color_start1.green, color_start1.blue

    gradient = [[None for _ in range(divisions_y)] for _ in range(divisions_x)]

    for col in range(divisions_x):
        gradient[col][0] = top_gradient[col]
        gradient[col][-1] = bottom_gradient[col]

    for col in range(0, len(gradient)):
        gradient[col] = color_gradient(gradient[col][0], gradient[col][-1], divisions_y)

    return gradient

# Colour Blending
def blend_colour_linear(colour_start, colour_end, t):
    return ColourRGB(int(LinearInterpolation(colour_start.red, colour_end.red, t)),
                     int(LinearInterpolation(colour_start.green, colour_end.green, t)),
                     int(LinearInterpolation(colour_start.blue, colour_end.blue, t)))

def blend_colour_cosine(colour_start, colour_end, t):
    return ColourRGB(int(CosineInterpolation(colour_start.red, colour_end.red, t)),
                     int(CosineInterpolation(colour_start.green, colour_end.green, t)),
                     int(CosineInterpolation(colour_start.blue, colour_end.blue, t)))

def blend_colour_cubic(colour_start, colour_end, t):
    return ColourRGB(int(CubicInterpolation(colour_start.red, colour_start.red, colour_end.red, colour_end.red, t)),
                     int(CubicInterpolation(colour_start.green, colour_start.green, colour_end.green, colour_end.green, t)),
                     int(CubicInterpolation(colour_start.blue, colour_start.blue, colour_end.blue, colour_end.blue, t)))

def blend_colour_hermite(colour_start, colour_end, t, tension=1, bias=0):
    return ColourRGB(int(HermiteInterpolation(colour_start.red, colour_start.red, colour_end.red, colour_end.red, t,
                                              tension=tension, bias=bias)),
                     int(HermiteInterpolation(colour_start.green, colour_start.green, colour_end.green,
                                              colour_end.green, t, tension=tension, bias=bias)),
                     int(HermiteInterpolation(colour_start.blue, colour_start.blue, colour_end.blue, colour_end.blue, t,
                                              tension=tension, bias=bias)))

# American Spelling Blending

def blend_color_linear(color_start, color_end, t):
    return ColourRGB(int(LinearInterpolation(color_start.red, color_end.red, t)),
                     int(LinearInterpolation(color_start.green, color_end.green, t)),
                     int(LinearInterpolation(color_start.blue, color_end.blue, t)))

def blend_color_cosine(color_start, color_end, t):
    return ColourRGB(int(CosineInterpolation(color_start.red, color_end.red, t)),
                     int(CosineInterpolation(color_start.green, color_end.green, t)),
                     int(CosineInterpolation(color_start.blue, color_end.blue, t)))

def blend_color_cubic(color_start, color_end, t):
    return ColourRGB(int(CubicInterpolation(color_start.red, color_start.red, color_end.red, color_end.red, t)),
                     int(CubicInterpolation(color_start.green, color_start.green, color_end.green, color_end.green, t)),
                     int(CubicInterpolation(color_start.blue, color_start.blue, color_end.blue, color_end.blue, t)))

def blend_color_hermite(color_start, color_end, t, tension=1, bias=0):
    return ColourRGB(int(HermiteInterpolation(color_start.red, color_start.red, color_end.red, color_end.red, t,
                                              tension=tension, bias=bias)),
                     int(HermiteInterpolation(color_start.green, color_start.green, color_end.green,
                                              color_end.green, t, tension=tension, bias=bias)),
                     int(HermiteInterpolation(color_start.blue, color_start.blue, color_end.blue, color_end.blue, t,
                                              tension=tension, bias=bias)))


def rgb_to_hex(red, green, blue):
    return "#%02x%02x%02x" % (red, green, blue)


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
LIGHTER_OLIVE_GREEN = ColourHex("#c4d86c")
LIGHT_OLIVE_GREEN = ColourHex("#b5cf49")
LIGHTISH_OLIVE_GREEN = ColourHex("#a3bf45")
OLIVE_GREEN = ColourHex("#81a140")
DARKISH_OLIVE_GREEN = ColourHex("#74923a")
DARK_OLIVE_GREEN = ColourHex("#617b30")
DARKER_OLIVE_GREEN = ColourHex("#42541f")
DARKEST_OLIVE_GREEN = ColourHex("#2e400b")

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
DARKISH_NAVY_BLUE = ColourRGB(45, 57, 68)
NAVY_BLUE = ColourRGB(40, 57, 81)
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
DARKISH_TURQUOISE = ColourHex("#43937e")
TURQUOISE = ColourHex("#5ca08e")
LIGHTISH_TURQUOISE = ColourHex("#73ad9e")
LIGHT_TURQUOISE = ColourHex("#8abaae")
LIGHTER_TURQUOISE = ColourHex("#a1c8be")
LIGHTEST_TURQUOISE = ColourHex("#b8d5cd")

ABSOLUTE_TURQUOISE = ColourHex("#00ffff")

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

ABSOLUTE_PURPLE = ColourHex("#ff00ff")

LIGHTEST_VIOLET = ColourHex("#d1c4e9")
LIGHTER_VIOLET = ColourHex("#b39ddb")
LIGHT_VIOLET = ColourHex("#9575cd")
LIGHTISH_VIOLET = ColourHex("#7e57c2")
VIOLET = ColourHex("#673ab7")
DARKISH_VIOLET = ColourHex("#5e35b1")
DARK_VIOLET = ColourHex("#512da8")
DARKER_VIOLET = ColourHex("#4527a0")
DARKEST_VIOLET = ColourHex("#311b92")
#yeeeeeeee

GREYS = [BLACK, DARKEST_GREY, DARKER_GREY, DARK_GREY, DARKISH_GREY, GREY, LIGHTISH_GREY, LIGHT_GREY, LIGHTER_GREY,
         LIGHTEST_GREY, DARK_WHITE, WHITE]

BLUE_GREYS = [DARKEST_BLUE_GREY, DARKER_BLUE_GREY, DARK_BLUE_GREY, DARKISH_BLUE_GREY, BLUE_GREY, LIGHTISH_BLUE_GREY,
              LIGHT_BLUE_GREY, LIGHTER_BLUE_GREY, LIGHTEST_BLUE_GREY]

REDS = [DARKEST_RED, DARKER_RED, DARK_RED, DARKISH_RED, RED, LIGHTISH_RED, LIGHT_RED, ABSOLUTE_RED]
PINKS = [PINK, LIGHTISH_PINK, LIGHT_PINK, LIGHTER_PINK, LIGHTEST_PINK]

ORANGES = [MELON_ORANGE, SALAMANDER_ORANGE, SANDSTONE_ORANGE, GINGER_ORANGE, SQUASH_ORANGE, ORANGE, ROYAL_ORANGE,
           TIGER_ORANGE, APRICOT_ORANGE, OCHRE_ORANGE, FIRE_ORANGE, CARROT_ORANGE, PUMPKIN_ORANGE, HONEY_ORANGE]

BROWNS = [DARK_AMBER_BROWN, BRONZE_BROWN, CLAY_BROWN, BURNT_BROWN, LIGHTEST_BROWN, LIGHTER_BROWN, LIGHT_BROWN, BROWN,
          DARKER_BROWN, DARKEST_BROWN]

YELLOWS = [GOLD, GOLDENROD_YELLOW, YELLOW, AMBER_YELLOW, ROYAL_YELLOW, MUSTARD_YELLOW, MELLOW_YELLOW, FLAX_YELLOW,
           CREAM_YELLOW, CHROME_YELLOW, TROMBONE_YELLOW, ABSOLUTE_YELLOW]

OLIVE_GREENS = [DARKEST_OLIVE_GREEN, DARKER_OLIVE_GREEN, DARK_OLIVE_GREEN, DARKISH_OLIVE_GREEN, OLIVE_GREEN,
                LIGHTISH_OLIVE_GREEN, LIGHTEST_OLIVE_GREEN, LIGHTER_OLIVE_GREEN, LIGHT_OLIVE_GREEN]

GREENS = [DARKEST_GREEN, DARKER_GREEN, DARK_GREEN, DARKISH_GREEN, GREEN, LIGHTISH_GREEN, LIGHT_GREEN, LIGHTER_GREEN,
          LIGHTEST_GREEN, ABSOLUTE_GREEN]

NAVY_BLUES = [DARKEST_NAVY_BLUE, DARKER_NAVY_BLUE, DARK_NAVY_BLUE, DARKISH_NAVY_BLUE, NAVY_BLUE, LIGHTISH_NAVY_BLUE,
              LIGHT_NAVY_BLUE, LIGHTER_NAVY_BLUE, LIGHTEST_NAVY_BLUE]

BLUES = [DARKEST_BLUE, DARKER_BLUE, DARK_BLUE, DARKISH_BLUE, BLUE, LIGHTISH_BLUE, LIGHT_BLUE, LIGHTER_BLUE,
         LIGHTEST_BLUE, ABSOLUTE_BLUE]

TURQUOISES = [DARKEST_TURQUOISE, DARKER_TURQUOISE, DARK_TURQUOISE, DARKISH_TURQUOISE, TURQUOISE,
              LIGHTISH_TURQUOISE, LIGHT_TURQUOISE, LIGHTER_TURQUOISE, LIGHTEST_TURQUOISE, ABSOLUTE_TURQUOISE]

PURPLES = [DARKEST_PURPLE, DARKER_PURPLE, DARK_PURPLE, DARKISH_PURPLE, PURPLE, LIGHTISH_PURPLE, LIGHT_PURPLE,
           LIGHTER_PURPLE, LIGHTEST_PURPLE, ABSOLUTE_PURPLE]

VIOLETS = [DARKEST_VIOLET, DARKER_VIOLET, DARK_VIOLET, DARKISH_VIOLET, VIOLET, LIGHTISH_VIOLET, LIGHT_VIOLET,
           LIGHTER_VIOLET, LIGHTEST_VIOLET]

ABSOLUTE_COLOURS = [ABSOLUTE_BLUE, ABSOLUTE_GREEN, ABSOLUTE_RED, ABSOLUTE_YELLOW, ABSOLUTE_PURPLE, ABSOLUTE_TURQUOISE]

WARM_COLOURS = REDS + YELLOWS + BROWNS + ORANGES + PINKS
COOL_COLOURS = PURPLES + VIOLETS + GREENS + OLIVE_GREENS + NAVY_BLUES + BLUES + TURQUOISES

GOOPYLIB_COLOURS = GREYS + BLUE_GREYS + REDS + PINKS + ORANGES + BROWNS + YELLOWS + OLIVE_GREENS + GREENS + NAVY_BLUES \
                   + BLUES + TURQUOISES + PURPLES + VIOLETS

# American Spelling

ABSOLUTE_COLORS = ABSOLUTE_COLOURS

WARM_COLORS = WARM_COLOURS
COOL_COLORS = COOL_COLOURS

GOOPYLIB_COLORS = GOOPYLIB_COLOURS
