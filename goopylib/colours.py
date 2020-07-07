from goopylib.util import GraphicsError

# Defining Custom  & colour Functions

class Colour:
    def __str__(self):
        return self.colour

    def __repr__(self):
        return self.colour


class ColourRGB(Colour):
    def __init__(self, r, g, b):
        if not (isinstance(r, int) and isinstance(g, int) and isinstance(b, int)):
            raise GraphicsError("\n\nRGB values must be integers!")
        if not (256 > r > -1 and 256 > g > -1 and 256 > b > -1):
            raise GraphicsError(
                "\n\nRGB values must be between 0 & 255 (included), right now {}, {}, {}".format(r, g, b))
        self.colour = "#%02x%02x%02x" % (r, g, b)


class ColourHex(Colour):
    def __init__(self, colour):
        if not isinstance(colour, str):
            raise GraphicsError("\n\nHex value must be a string in format: #rrggbb")
        if len(colour) != 7:
            raise GraphicsError("\n\nThe length of the hex colour string must be 7: '#rrggbb'")
        self.colour = colour


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
