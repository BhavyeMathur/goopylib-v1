from random import randint as randomrandint

from goopylib.math.interpolations import *


# -------------------------------------------------------------------------
# COLOUR CLASSES

class Colour:
    colour = None
    string = "colour"

    red = 0
    green = 0
    blue = 0

    def __init__(self):
        pass

    def __repr__(self):
        return self.string

    def __str__(self):
        return self.colour

    # PyNumber Methods

    def __add__(self, other):
        if isinstance(other, Colour):
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue

        elif isinstance(other, int):
            red = self.red + other
            green = self.green + other
            blue = self.blue + other
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

    def __sub__(self, other):
        if isinstance(other, Colour):
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue
        elif isinstance(other, int):
            red = self.red - other
            green = self.green - other
            blue = self.blue - other
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

    def __mul__(self, other):
        if isinstance(other, Colour):
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue
        elif isinstance(other, int):
            red = self.red * other
            green = self.green * other
            blue = self.blue * other
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

    def __mod__(self, other):
        if isinstance(other, Colour):
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue
        elif isinstance(other, int):
            red = self.red % other
            green = self.green % other
            blue = self.blue % other
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(0 if red < 0 else red,
                         0 if green < 0 else green,
                         0 if blue < 0 else blue)

    def __divmod__(self, other):
        return self // other, self % other

    def __pow__(self, power, modulo=None):
        if isinstance(power, Colour):
            if isinstance(modulo, Colour):
                red = pow(self.red, power.red, modulo.red)
                green = pow(self.green ** power.green, modulo.green)
                blue = pow(self.blue ** power.blue, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red, power.red, modulo)
                green = pow(self.green ** power.green, modulo)
                blue = pow(self.blue ** power.blue, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")

        elif isinstance(power, int):
            if isinstance(modulo, Colour):
                red = pow(self.red ** power, modulo.red)
                green = pow(self.green ** power, modulo.green)
                blue = pow(self.blue ** power, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red ** power, modulo)
                green = pow(self.green ** power, modulo)
                blue = pow(self.blue ** power, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")
        else:
            raise TypeError(
                f"unsupported operand type(s) for **: 'Colour' and '{type(power)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

    def __neg__(self):
        return ColourRGB(255 - self.red, 255 - self.green, 255 - self.blue)

    def __pos__(self):
        return ColourRGB(self.red, self.green, self.blue)

    def __abs__(self):
        c_value = (self.red + self.green + self.blue) // 3
        return ColourRGB(c_value, c_value, c_value)

    def __bool__(self):
        return self.colour != "#000000"

    def __invert__(self):
        return -self

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
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

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
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

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
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

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
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

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
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourRGB(255 if red > 255 else (0 if red < 0 else red),
                         255 if green > 255 else (0 if green < 0 else green),
                         255 if blue > 255 else (0 if blue < 0 else blue))

    # inplace PyNumber Methods

    def __iadd__(self, other):
        self.red, self.green, self.blue = self + other
        self.__update_values()
        return self

    def __isub__(self, other):
        self.red, self.green, self.blue = self - other
        self.__update_values()
        return self

    def __imul__(self, other):
        self.red, self.green, self.blue = self * other
        self.__update_values()
        return self

    def __imod__(self, other):
        self.red, self.green, self.blue = self % other
        self.__update_values()
        return self

    def __ipow__(self, other):
        self.red, self.green, self.blue = self ** other
        self.__update_values()
        return self

    def __ilshift__(self, other):
        self.red, self.green, self.blue = self << other
        self.__update_values()
        return self

    def __irshift__(self, other):
        self.red, self.green, self.blue = self >> other
        self.__update_values()
        return self

    def __iand__(self, other):
        self.red, self.green, self.blue = self & other
        self.__update_values()
        return self

    def __ixor__(self, other):
        self.red, self.green, self.blue = self ^ other
        self.__update_values()
        return self

    def __ior__(self, other):
        self.red, self.green, self.blue = self | other
        self.__update_values()
        return self

    def __floordiv__(self, other):
        if isinstance(other, Colour):
            red = self.red // other.red
            green = self.green // other.green
            blue = self.blue // other.blue
        elif isinstance(other, int):
            red = self.red // other
            green = self.green // other
            blue = self.blue // other
        else:
            raise TypeError(f"unsupported operand type(s) for '//': 'Colour' and '{type(other)}'. "
                            "Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __truediv__(self, other):
        if isinstance(other, Colour):
            red = self.red // other.red
            green = self.green // other.green
            blue = self.blue // other.blue
        elif isinstance(other, int):
            red = self.red // other
            green = self.green // other
            blue = self.blue // other
        else:
            raise TypeError(f"unsupported operand type(s) for '/': 'Colour' and '{type(other)}'. "
                            "Must be a Colour or int")

        return ColourRGB(red, green, blue)

    def __ifloordiv__(self, other):
        self.red, self.green, self.blue = self // other
        self.__update_values()
        return self

    def __itruediv__(self, other):
        self.red, self.green, self.blue = self / other
        self.__update_values()
        return self

    # Rich Compare Methods

    def __lt__(self, other):
        if isinstance(other, Colour):
            return self.red + self.green + self.blue < other.red + other.green + other.blue
        raise TypeError(f"'<' not supported between instances of 'Colour' and '{other}'.")

    def __le__(self, other):
        if isinstance(other, Colour):
            return self.red + self.green + self.blue <= other.red + other.green + other.blue
        raise TypeError(f"'<=' not supported between instances of 'Colour' and '{other}'.")

    def __gt__(self, other):
        if isinstance(other, Colour):
            return self.red + self.green + self.blue > other.red + other.green + other.blue
        raise TypeError(f"'>' not supported between instances of 'Colour' and '{other}'.")

    def __ge__(self, other):
        if isinstance(other, Colour):
            return self.red + self.green + self.blue >= other.red + other.green + other.blue
        raise TypeError(f"'>=' not supported between instances of 'Colour' and '{other}'.")

    def __eq__(self, other):
        return self.colour == other.colour

    def __ne__(self, other):
        return self.colour != other.colour

    # Other Overriding Methods

    def __contains__(self, item):
        return self.red == item or self.blue == item or self.green == item

    def __copy__(self):
        return ColourRGB(self.red, self.green, self.blue)

    def __hex__(self):
        return ColourHex("#%02x%02x%02x" % (self.red, self.green, self.blue))

    def __dir__(self):
        return "see https://github.com/BhavyeMathur/goopylib/wiki/Colours-in-goopylib!"

    def __round__(self, n=None):
        red = 255 if self.red > 127 else 0
        green = 255 if self.green > 127 else 0
        blue = 255 if self.blue > 127 else 0

        return ColourRGB(red, green, blue)

    def __iter__(self):
        for c in (self.red, self.green, self.blue):
            yield c

    def __reversed__(self):
        return ColourRGB(self.blue, self.green, self.red)

    def __update_values(self):
        self.string = f"rgb {self.red}, {self.green}, {self.blue}"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)
        return self

    def rgb_string(self):
        return f"rgb {self.red}, {self.green}, {self.blue}"

    def hex_string(self):
        return self.colour

    def cmyk_string(self):
        red = self.red / 255
        green = self.green / 255
        blue = self.blue / 255

        k = 1 - max(red, green, blue)
        k_inverse = 1 - k

        c = round(100 * (k_inverse - red) / k_inverse)
        m = round(100 * (k_inverse - green) / k_inverse)
        y = round(100 * (k_inverse - blue) / k_inverse)
        k = round(100 * k)

        return f"cmyk {c}%, {m}%, {y}%, {k}%"

    def hsl_string(self):
        red = self.red / 255
        green = self.green / 255
        blue = self.blue / 255

        cmax = max(red, green, blue)
        cmin = min(red, green, blue)

        delta = cmax - cmin

        L = 0.5 * (cmax + cmin)

        if delta == 0:
            h = 0
            s = 0
        elif cmax == red:
            h = 60 * (((green - blue) / delta) % 6)
            s = delta / (1 - abs(2 * L - 1))
        elif cmax == green:
            h = 60 * (((blue - red) / delta) + 2)
            s = delta / (1 - abs(2 * L - 1))
        else:
            h = 60 * (((red - green) / delta) + 4)
            s = delta / (1 - abs(2 * L - 1))

        return f"hsl {round(h)}°, {round(100 * s)}%, {round(L * 100)}%"

    def hsv_string(self):
        red = self.red / 255
        green = self.green / 255
        blue = self.blue / 255

        cmax = max(red, green, blue)
        cmin = min(red, green, blue)

        delta = cmax - cmin

        if delta == 0:
            h = 0
        elif cmax == red:
            h = 60 * (((green - blue) / delta) % 6)
        elif cmax == green:
            h = 60 * (((blue - red) / delta) + 2)
        else:
            h = 60 * (((red - green) / delta) + 4)

        s = 0 if cmax == 0 else (delta / cmax)

        return f"hsv {round(h)}°, {round(100 * s)}%, {round(100 * cmax)}%"

    def rgb(self):
        return self.red, self.green, self.blue

    def hex(self):
        return self.colour

    def cmyk(self):
        red = self.red / 255
        green = self.green / 255
        blue = self.blue / 255

        k = 1 - max(red, green, blue)
        k_inverse = 1 - k

        c = round(100 * (k_inverse - red) / k_inverse)
        m = round(100 * (k_inverse - green) / k_inverse)
        y = round(100 * (k_inverse - blue) / k_inverse)
        k = round(100 * k)

        return c, m, y, k

    def hsl(self):
        red = self.red / 255
        green = self.green / 255
        blue = self.blue / 255

        cmax = max(red, green, blue)
        cmin = min(red, green, blue)

        delta = cmax - cmin

        L = 0.5 * (cmax + cmin)

        if delta == 0:
            h = 0
            s = 0
        elif cmax == red:
            h = 60 * (((green - blue) / delta) % 6)
            s = delta / (1 - abs(2 * L - 1))
        elif cmax == green:
            h = 60 * (((blue - red) / delta) + 2)
            s = delta / (1 - abs(2 * L - 1))
        else:
            h = 60 * (((red - green) / delta) + 4)
            s = delta / (1 - abs(2 * L - 1))

        return round(h), round(100 * s), round(L * 100)

    def hsv(self):
        red = self.red / 255
        green = self.green / 255
        blue = self.blue / 255

        cmax = max(red, green, blue)
        cmin = min(red, green, blue)

        delta = cmax - cmin

        if delta == 0:
            h = 0
        elif cmax == red:
            h = 60 * (((green - blue) / delta) % 6)
        elif cmax == green:
            h = 60 * (((blue - red) / delta) + 2)
        else:
            h = 60 * (((red - green) / delta) + 4)

        s = 0 if cmax == 0 else (delta / cmax)

        return round(h), round(100 * s), round(100 * cmax)

    def to_rgb_colour(self):
        return ColourRGB(self.red, self.green, self.blue)

    def to_hex_colour(self):
        return ColourHex(self.colour)

    def to_cmyk_colour(self):
        return ColourCMYK(*self.cmyk())

    def to_hsl_colour(self):
        return ColourHSL(*self.hsl())

    def to_hsv_colour(self):
        return ColourHSV(*self.hsv())

    def set_red(self, value):
        if isinstance(value, int):
            if 256 > value > -1:
                self.red = value
                self.__update_values()
            else:
                raise GraphicsError("\n\nGraphicsError: red value for set_red() function must be between 0 & 255, "
                                    f"inclusive, 0 <= red <= 255, not {value}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: red value for set_red() function must be an integer, not {value}")
        return self

    def set_green(self, value):
        if isinstance(value, int):
            if 256 > value > -1:
                self.green = value
                self.__update_values()
            else:
                raise GraphicsError("\n\nGraphicsError: green value for set_green() function must be between 0 & 255, "
                                    f"inclusive, 0 <= green <= 255, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: green value for set_green() function must be an integer, "
                                f"not {value}")
        return self

    def set_blue(self, value):
        if isinstance(value, int):
            if 256 > value > -1:
                self.blue = value
                self.__update_values()
            else:
                raise GraphicsError("\n\nGraphicsError: blue value for set_blue() function must be between 0 & 255, "
                                    f"inclusive, 0 <= blue <= 255, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: blue value for set_blue() function must be an integer, "
                                f"not {value}")
        return self


class ColourRGB(Colour):
    def __init__(self, r, g, b):
        if isinstance(r, int) and isinstance(g, int) and isinstance(b, int):
            if 256 > r > -1 and 256 > g > -1 and 256 > b > -1:
                super().__init__()

                self.colour = "#%02x%02x%02x" % (r, g, b)
                self.string = f"rgb {r}, {g}, {b}"

                self.red = r
                self.green = g
                self.blue = b
            else:
                raise GraphicsError(
                    f"\n\nGraphicsError: RGB values must be between 0 & 255 (included), not {r}, {g}, {b}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: GraphicsError: RGB values must be integers! not {r}, {g}, {b}")


class ColourHex(Colour):

    def __init__(self, colour):
        if isinstance(colour, str):
            if len(colour) == 7:
                try:
                    decimal_number = int(colour[1:], 16)
                    if decimal_number > 16777215 or decimal_number < 0:
                        raise GraphicsError("\n\nGraphicsError: The colour value must be between #000000 and #ffffff, "
                                            f"not {colour}")
                except ValueError:
                    raise GraphicsError(
                        f"\n\nGraphicsError: The colour value must be a hexadecimal string, not {colour}")
            else:
                raise GraphicsError("\n\nGraphicsError: The length of the hex colour string must be 7: '#rrggbb'")
        else:
            raise GraphicsError("\n\nGraphicsError: Hex value must be a string in format: #rrggbb")

        super().__init__()

        self.colour = colour
        self.string = self.colour

        rgb = [int(colour[i:i + 2], 16) for i in (1, 3, 5)]

        self.red = rgb[0]
        self.green = rgb[1]
        self.blue = rgb[2]

    # PyNumber Methods

    def __add__(self, other):
        if isinstance(other, Colour):
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue
        elif isinstance(other, int):
            red = self.red + other
            green = self.green + other
            blue = self.blue + other
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

    def __sub__(self, other):
        if isinstance(other, Colour):
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue
        elif isinstance(other, int):
            red = self.red - other
            green = self.green - other
            blue = self.blue - other
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mul__(self, other):
        if isinstance(other, Colour):
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue
        elif isinstance(other, int):
            red = self.red * other
            green = self.green * other
            blue = self.blue * other
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mod__(self, other):
        if isinstance(other, Colour):
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue
        elif isinstance(other, int):
            red = self.red % other
            green = self.green % other
            blue = self.blue % other
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (0 if red < 0 else red,
                                            0 if green < 0 else green,
                                            0 if blue < 0 else blue))

    def __pow__(self, power, modulo=None):
        if isinstance(power, Colour):
            if isinstance(modulo, Colour):
                red = pow(self.red, power.red, modulo.red)
                green = pow(self.green ** power.green, modulo.green)
                blue = pow(self.blue ** power.blue, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red, power.red, modulo)
                green = pow(self.green ** power.green, modulo)
                blue = pow(self.blue ** power.blue, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")

        elif isinstance(power, int):
            if isinstance(modulo, Colour):
                red = pow(self.red ** power, modulo.red)
                green = pow(self.green ** power, modulo.green)
                blue = pow(self.blue ** power, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red ** power, modulo)
                green = pow(self.green ** power, modulo)
                blue = pow(self.blue ** power, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")
        else:
            raise TypeError(
                f"unsupported operand type(s) for **: 'Colour' and '{type(power)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

    def __neg__(self):
        return ColourHex("#%02x%02x%02x" % (255 - self.red, 255 - self.green, 255 - self.blue))

    def __pos__(self):
        return ColourHex(self.colour)

    def __abs__(self):
        c_value = (self.red + self.green + self.blue) // 3
        return ColourHex("#%02x%02x%02x" % (c_value, c_value, c_value))

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
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (red, green, blue))

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
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (red, green, blue))

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
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

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
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

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
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHex("#%02x%02x%02x" % (255 if red > 255 else (0 if red < 0 else red),
                                            255 if green > 255 else (0 if green < 0 else green),
                                            255 if blue > 255 else (0 if blue < 0 else blue)))

    def __contains__(self, item):
        return (self.red == item or self.blue == item or self.green == item) or (item in self.colour)

    def __update_values(self):
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)
        self.string = self.colour
        return self


class ColourCMYK(Colour):
    def __init__(self, c, m, y, k):
        if isinstance(c, int) and isinstance(m, int) and isinstance(y, int) and isinstance(k, int):
            if 101 > c > -1 and 101 > m > -1 and 101 > y > -1 and 101 > k > -1:
                super().__init__()

                self.red = round(255 * (1 - (c + k) / 100))
                self.green = round(255 * (1 - (m + k) / 100))
                self.blue = round(255 * (1 - (y + k) / 100))

                self.cyan = c
                self.magenta = m
                self.yellow = y
                self.key = k

                self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)
                self.string = f"cmyk {c}%, {m}%, {y}%, {k}%"
            else:
                raise GraphicsError("\n\nGraphicsError: CMYK values must be between 0 & 100 (included), "
                                    f"not {c}, {m}, {y}, {k}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: CMYK values must be integers! not {c}, {m}, {y}, {k}")

    # PyNumber Methods

    def __add__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan + other.cyan
            magenta = self.magenta + other.magenta
            yellow = self.yellow + other.yellow
            key = self.key + other.key

            return ColourCMYK(100 if cyan > 100 else cyan,
                              100 if magenta > 100 else magenta,
                              100 if yellow > 100 else yellow,
                              100 if key > 100 else key)

        elif isinstance(other, Colour):
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue

        elif isinstance(other, int):
            red = self.red + other
            green = self.green + other
            blue = self.blue + other
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __sub__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan - other.cyan
            magenta = self.magenta - other.magenta
            yellow = self.yellow - other.yellow
            key = self.key - other.key

            return ColourCMYK(0 if cyan < 0 else cyan,
                              0 if magenta < 0 else magenta,
                              0 if yellow < 0 else yellow,
                              0 if key < 0 else key)

        elif isinstance(other, Colour):
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue

        elif isinstance(other, int):
            red = self.red - other
            green = self.green - other
            blue = self.blue - other
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mul__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan * other.cyan
            magenta = self.magenta * other.magenta
            yellow = self.yellow * other.yellow
            key = self.key * other.key

            return ColourCMYK(100 if cyan > 100 else cyan,
                              100 if magenta > 100 else magenta,
                              100 if yellow > 100 else yellow,
                              100 if key > 100 else key)

        elif isinstance(other, Colour):
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue

        elif isinstance(other, int):
            red = self.red * other
            green = self.green * other
            blue = self.blue * other
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mod__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan % other.cyan
            magenta = self.magenta % other.magenta
            yellow = self.yellow % other.yellow
            key = self.key % other.key

            return ColourCMYK(cyan, magenta, yellow, key)

        elif isinstance(other, Colour):
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue

        elif isinstance(other, int):
            red = self.red % other
            green = self.green % other
            blue = self.blue % other
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(0 if red < 0 else red,
                                        0 if green < 0 else green,
                                        0 if blue < 0 else blue))

    def __pow__(self, power, modulo=None):
        if isinstance(power, ColourCMYK):
            if isinstance(modulo, int):
                cyan = pow(self.cyan, power.cyan, modulo)
                magenta = pow(self.magenta, power.magenta, modulo)
                yellow = pow(self.yellow, power.yellow, modulo)
                key = pow(self.key, power.key, modulo)

            elif isinstance(modulo, ColourCMYK):
                cyan = pow(self.cyan, power.cyan, modulo.cyan)
                magenta = pow(self.magenta, power.magenta, modulo.magenta)
                yellow = pow(self.yellow, power.yellow, modulo.yellow)
                key = pow(self.key, power.key, modulo.key)

            else:
                raise TypeError(f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}' when power is"
                                f" a ColourCMYK'. Must be a ColourCMYK or int")

            return ColourCMYK(100 if cyan > 100 else cyan,
                              100 if magenta > 100 else magenta,
                              100 if yellow > 100 else yellow,
                              100 if key > 100 else key)

        elif isinstance(power, Colour):
            if isinstance(modulo, Colour):
                red = pow(self.red, power.red, modulo.red)
                green = pow(self.green ** power.green, modulo.green)
                blue = pow(self.blue ** power.blue, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red, power.red, modulo)
                green = pow(self.green ** power.green, modulo)
                blue = pow(self.blue ** power.blue, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")

        elif isinstance(power, int):
            if isinstance(modulo, Colour):
                red = pow(self.red ** power, modulo.red)
                green = pow(self.green ** power, modulo.green)
                blue = pow(self.blue ** power, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red ** power, modulo)
                green = pow(self.green ** power, modulo)
                blue = pow(self.blue ** power, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and '{type(power)}'. "
                            "Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __neg__(self):
        return ColourCMYK(*_rgb_to_cmyk(255 - self.red, 255 - self.green, 255 - self.blue))

    def __pos__(self):
        return ColourCMYK(*_rgb_to_cmyk(self.red, self.green, self.blue))

    def __abs__(self):
        c_value = (self.red + self.green + self.blue) // 3
        return ColourCMYK(*_rgb_to_cmyk(c_value, c_value, c_value))

    def __lshift__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan << other.cyan
            magenta = self.magenta << other.magenta
            yellow = self.yellow << other.yellow
            key = self.key << other.key

            return ColourCMYK(100 if cyan > 100 else (0 if cyan < 0 else cyan),
                              100 if magenta > 100 else (0 if magenta < 0 else magenta),
                              100 if yellow > 100 else (0 if yellow < 0 else yellow),
                              100 if key > 100 else (0 if key < 0 else key))

        elif isinstance(other, Colour):
            red = self.red << other.red
            green = self.green << other.green
            blue = self.blue << other.blue

        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = green, blue, red
        else:
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __rshift__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan >> other.cyan
            magenta = self.magenta >> other.magenta
            yellow = self.yellow >> other.yellow
            key = self.key >> other.key

            return ColourCMYK(100 if cyan > 100 else (0 if cyan < 0 else cyan),
                              100 if magenta > 100 else (0 if magenta < 0 else magenta),
                              100 if yellow > 100 else (0 if yellow < 0 else yellow),
                              100 if key > 100 else (0 if key < 0 else key))

        elif isinstance(other, Colour):
            red = self.red >> other.red
            green = self.green >> other.green
            blue = self.blue >> other.blue

        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = blue, red, green
        else:
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __and__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan & other.cyan
            magenta = self.magenta & other.magenta
            yellow = self.yellow & other.yellow
            key = self.key & other.key

            return ColourCMYK(100 if cyan > 100 else (0 if cyan < 0 else cyan),
                              100 if magenta > 100 else (0 if magenta < 0 else magenta),
                              100 if yellow > 100 else (0 if yellow < 0 else yellow),
                              100 if key > 100 else (0 if key < 0 else key))

        elif isinstance(other, Colour):
            red = self.red & other.red
            green = self.green & other.green
            blue = self.blue & other.blue

        elif isinstance(other, int):
            red = self.red & other
            green = self.green & other
            blue = self.blue & other
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __xor__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan ^ other.cyan
            magenta = self.magenta ^ other.magenta
            yellow = self.yellow ^ other.yellow
            key = self.key ^ other.key

            return ColourCMYK(100 if cyan > 100 else (0 if cyan < 0 else cyan),
                              100 if magenta > 100 else (0 if magenta < 0 else magenta),
                              100 if yellow > 100 else (0 if yellow < 0 else yellow),
                              100 if key > 100 else (0 if key < 0 else key))

        elif isinstance(other, Colour):
            red = self.red ^ other.red
            green = self.green ^ other.green
            blue = self.blue ^ other.blue

        elif isinstance(other, int):
            red = self.red ^ other
            green = self.green ^ other
            blue = self.blue ^ other
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    def __or__(self, other):
        if isinstance(other, ColourCMYK):
            cyan = self.cyan | other.cyan
            magenta = self.magenta | other.magenta
            yellow = self.yellow | other.yellow
            key = self.key | other.key

            return ColourCMYK(100 if cyan > 100 else (0 if cyan < 0 else cyan),
                              100 if magenta > 100 else (0 if magenta < 0 else magenta),
                              100 if yellow > 100 else (0 if yellow < 0 else yellow),
                              100 if key > 100 else (0 if key < 0 else key))

        elif isinstance(other, Colour):
            red = self.red | other.red
            green = self.green | other.green
            blue = self.blue | other.blue

        elif isinstance(other, int):
            red = self.red | other
            green = self.green | other
            blue = self.blue | other
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourCMYK(*_rgb_to_cmyk(255 if red > 255 else (0 if red < 0 else red),
                                        255 if green > 255 else (0 if green < 0 else green),
                                        255 if blue > 255 else (0 if blue < 0 else blue)))

    # inplace PyNumber Methods

    def __iadd__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan += other.cyan
            self.magenta += other.magenta
            self.yellow += other.yellow
            self.key += other.key

            if self.cyan > 100:
                self.cyan = 100
            if self.magenta > 100:
                self.magenta = 100
            if self.yellow > 100:
                self.yellow = 100
            if self.key > 100:
                self.key = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red += other.red
            self.green += other.green
            self.blue += other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red += other
            self.green += other
            self.blue += other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __isub__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan -= other.cyan
            self.magenta -= other.magenta
            self.yellow -= other.yellow
            self.key -= other.key

            if self.cyan < 0:
                self.cyan = 0
            if self.magenta < 0:
                self.magenta = 0
            if self.yellow < 0:
                self.yellow = 0
            if self.key < 0:
                self.key = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red -= other.red
            self.green -= other.green
            self.blue -= other.blue

            if self.red < 0:
                self.red = 0
            if self.green < 0:
                self.green = 0
            if self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red -= other
            self.green -= other
            self.blue -= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __imul__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan *= other.cyan
            self.magenta *= other.magenta
            self.yellow *= other.yellow
            self.key *= other.key

            if self.cyan > 100:
                self.cyan = 100
            if self.magenta > 100:
                self.magenta = 100
            if self.yellow > 100:
                self.yellow = 100
            if self.key > 100:
                self.key = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red *= other.red
            self.green *= other.green
            self.blue *= other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red *= other
            self.green *= other
            self.blue *= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __imod__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan %= other.cyan
            self.magenta %= other.magenta
            self.yellow %= other.yellow
            self.key %= other.key

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red %= other.red
            self.green %= other.green
            self.blue %= other.blue

        elif isinstance(other, int):
            self.cyan %= other
            self.magenta %= other
            self.yellow %= other
            self.key %= other

            if self.cyan < 0:
                self.cyan = 0
            if self.magenta < 0:
                self.magenta = 0
            if self.yellow < 0:
                self.yellow = 0
            if self.key < 0:
                self.key = 0
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __ipow__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan **= other.cyan
            self.magenta **= other.magenta
            self.yellow **= other.yellow
            self.key **= other.key

            if self.cyan > 100:
                self.cyan = 100
            if self.magenta > 100:
                self.magenta = 100
            if self.yellow > 100:
                self.yellow = 100
            if self.key > 100:
                self.key = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red += other.red
            self.green += other.green
            self.blue += other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red += other
            self.green += other
            self.blue += other

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and '{type(other)}'. "
                            "Must be a Colour or int")

        self.__update_values()

    def __ilshift__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan <<= other.cyan
            self.magenta <<= other.magenta
            self.yellow <<= other.yellow
            self.key <<= other.key

            if self.cyan > 100:
                self.cyan = 100
            elif self.cyan < 0:
                self.cyan = 0

            if self.magenta > 100:
                self.magenta = 100
            elif self.magenta < 0:
                self.magenta = 0

            if self.yellow > 100:
                self.yellow = 100
            elif self.yellow < 0:
                self.yellow = 0

            if self.key > 100:
                self.key = 100
            elif self.key < 0:
                self.key = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red <<= other.red
            self.green <<= other.green
            self.blue <<= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            for _ in range(other):
                self.red, self.green, self.blue = self.green, self.blue, self.red
        else:
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __irshift__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan >>= other.cyan
            self.magenta >>= other.magenta
            self.yellow >>= other.yellow
            self.key >>= other.key

            if self.cyan > 100:
                self.cyan = 100
            elif self.cyan < 0:
                self.cyan = 0

            if self.magenta > 100:
                self.magenta = 100
            elif self.magenta < 0:
                self.magenta = 0

            if self.yellow > 100:
                self.yellow = 100
            elif self.yellow < 0:
                self.yellow = 0

            if self.key > 100:
                self.key = 100
            elif self.key < 0:
                self.key = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red >>= other.red
            self.green >>= other.green
            self.blue >>= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            for _ in range(other):
                self.red, self.green, self.blue = self.blue, self.red, self.green
        else:
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __iand__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan &= other.cyan
            self.magenta &= other.magenta
            self.yellow &= other.yellow
            self.key &= other.key

            if self.cyan > 100:
                self.cyan = 100
            elif self.cyan < 0:
                self.cyan = 0

            if self.magenta > 100:
                self.magenta = 100
            elif self.magenta < 0:
                self.magenta = 0

            if self.yellow > 100:
                self.yellow = 100
            elif self.yellow < 0:
                self.yellow = 0

            if self.key > 100:
                self.key = 100
            elif self.key < 0:
                self.key = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red &= other.red
            self.green &= other.green
            self.blue &= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red &= other
            self.green &= other
            self.blue &= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __ixor__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan ^= other.cyan
            self.magenta ^= other.magenta
            self.yellow ^= other.yellow
            self.key ^= other.key

            if self.cyan > 100:
                self.cyan = 100
            elif self.cyan < 0:
                self.cyan = 0

            if self.magenta > 100:
                self.magenta = 100
            elif self.magenta < 0:
                self.magenta = 0

            if self.yellow > 100:
                self.yellow = 100
            elif self.yellow < 0:
                self.yellow = 0

            if self.key > 100:
                self.key = 100
            elif self.key < 0:
                self.key = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red ^= other.red
            self.green ^= other.green
            self.blue ^= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red ^= other
            self.green ^= other
            self.blue ^= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __ior__(self, other):
        if isinstance(other, ColourCMYK):
            self.cyan |= other.cyan
            self.magenta |= other.magenta
            self.yellow |= other.yellow
            self.key |= other.key

            if self.cyan > 100:
                self.cyan = 100
            elif self.cyan < 0:
                self.cyan = 0

            if self.magenta > 100:
                self.magenta = 100
            elif self.magenta < 0:
                self.magenta = 0

            if self.yellow > 100:
                self.yellow = 100
            elif self.yellow < 0:
                self.yellow = 0

            if self.key > 100:
                self.key = 100
            elif self.key < 0:
                self.key = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red |= other.red
            self.green |= other.green
            self.blue |= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red |= other
            self.green |= other
            self.blue |= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __contains__(self, item):
        return self.cyan == item or self.magenta == item or self.yellow == item or self.key == item

    def __copy__(self):
        return ColourCMYK(self.cyan, self.magenta, self.yellow, self.key)

    def __round__(self, n=None):
        cyan = 100 if self.cyan > 49 else 0
        magenta = 100 if self.magenta > 49 else 0
        yellow = 100 if self.yellow > 49 else 0
        key = 100 if self.key > 49 else 0

        return ColourCMYK(cyan, magenta, yellow, key)

    def __iter__(self):
        for c in (self.cyan, self.magenta, self.yellow, self.key):
            yield c

    def _update_on_operation(self):
        self.red, self.green, self.blue = _cmyk_to_rgb(self.cyan, self.magenta, self.yellow, self.key)

        self.string = f"cmyk {self.cyan}%, {self.magenta}%, {self.yellow}%, {self.key}%"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)

    def __update_values(self):
        self.cyan, self.magenta, self.yellow, self.key = _rgb_to_cmyk(self.red, self.green, self.blue)
        self.string = f"cmyk {self.cyan}%, {self.magenta}%, {self.yellow}%, {self.key}%"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)

        return self

    def set_cyan(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.cyan = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: cyan value for set_cyan() function must be between 0 & 255, "
                                    f"inclusive, 0 <= cyan <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: cyan value for set_cyan() function must be an integer, "
                                f"not {value}")

        return self

    def set_magenta(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.magenta = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: magenta value for set_magenta() function must be between "
                                    f"0 & 255, inclusive, 0 <= magenta <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: magenta value for set_magenta() function must be an integer, "
                                f"not {value}")

        return self

    def set_yellow(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.yellow = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: yellow value for set_yellow() function must be between 0 & 255,"
                                    f" inclusive, 0 <= yellow <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: yellow value for set_yellow() function must be an integer, "
                                f"not {value}")

        return self

    def set_key(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.key = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: key value for set_key() function must be between 0 & 255, "
                                    f"inclusive, 0 <= key <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: key value for set_key() function must be an integer, "
                                f"not {value}")

        return self


class ColourHSV(Colour):
    def __init__(self, h, s, v):
        if isinstance(h, int) and isinstance(s, int) and isinstance(v, int):
            if 360 > h > -1:
                if s > 100 or s < 0:
                    raise GraphicsError("\n\nGraphicsError: s value for HSV colour must be between 0 & 100, "
                                        f"100 >= s >= 0, not {s}")
                if v > 100 or v < 0:
                    raise GraphicsError("\n\nGraphicsError: v value for HSV colour must be between 0 & 100, "
                                        f"100 >= v >= 0, not {v}")

                super().__init__()

                self.string = f"hsv {h}°, {s}%, {v}%"

                s /= 100
                v /= 100

                c = v * s
                x = c * (1 - abs((h / 60) % 2 - 1))
                m = v - c

                if h < 60:
                    rgb_ = (c, x, 0)
                elif h < 120:
                    rgb_ = (x, c, 0)
                elif h < 180:
                    rgb_ = (0, c, x)
                elif h < 240:
                    rgb_ = (0, x, c)
                elif h < 300:
                    rgb_ = (x, 0, c)
                else:
                    rgb_ = (c, 0, x)

                self.red = int(255 * (rgb_[0] + m))
                self.green = int(255 * (rgb_[1] + m))
                self.blue = int(255 * (rgb_[2] + m))

                self.hue = h
                self.saturation = s
                self.value = v

                self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)

            else:
                raise GraphicsError(f"\n\nGraphicsError: h value for HSV colour must be between 0 & 359, 360 > h >= 0, "
                                    f"not {h}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: HSV values must be integers (H) & floats (S & V)! not {h}, {s}, "
                                f"{v}")

    # PyNumber Methods

    def __add__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue + other.hue
            saturation = self.saturation + other.saturation
            value = self.value + other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else saturation,
                             100 if value > 100 else value)

        elif isinstance(other, Colour):
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue

        elif isinstance(other, int):
            red = self.red + other
            green = self.green + other
            blue = self.blue + other
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __sub__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue - other.hue
            saturation = self.saturation - other.saturation
            value = self.value - other.value

            return ColourHSV(hue % 360,
                             0 if saturation < 0 else saturation,
                             0 if value < 0 else value)

        elif isinstance(other, Colour):
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue

        elif isinstance(other, int):
            red = self.red - other
            green = self.green - other
            blue = self.blue - other
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mul__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue * other.hue
            saturation = self.saturation * other.saturation
            value = self.value * other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else saturation,
                             100 if value > 100 else value)

        elif isinstance(other, Colour):
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue

        elif isinstance(other, int):
            red = self.red * other
            green = self.green * other
            blue = self.blue * other
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mod__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue % other.hue
            saturation = self.saturation % other.saturation
            value = self.value % other.value

            return ColourHSV(hue, saturation, value)

        elif isinstance(other, Colour):
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue

        elif isinstance(other, int):
            red = self.red % other
            green = self.green % other
            blue = self.blue % other
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __pow__(self, power, modulo=None):
        if isinstance(power, ColourHSV):
            if isinstance(modulo, int):
                hue = pow(self.hue, power.hue, modulo)
                saturation = pow(self.saturation, power.saturation, modulo)
                value = pow(self.value, power.value, modulo)

            elif isinstance(modulo, ColourHSV):
                hue = pow(self.hue, power.hue, modulo.hue)
                saturation = pow(self.saturation, power.saturation, modulo.saturation)
                value = pow(self.value, power.value, modulo.value)

            else:
                raise TypeError(f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}' when power is"
                                f" a ColourHSV'. Must be a ColourHSV or int")

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else saturation,
                             100 if value > 100 else value)

        elif isinstance(power, Colour):
            if isinstance(modulo, Colour):
                red = pow(self.red, power.red, modulo.red)
                green = pow(self.green ** power.green, modulo.green)
                blue = pow(self.blue ** power.blue, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red, power.red, modulo)
                green = pow(self.green ** power.green, modulo)
                blue = pow(self.blue ** power.blue, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")

        elif isinstance(power, int):
            if isinstance(modulo, Colour):
                red = pow(self.red ** power, modulo.red)
                green = pow(self.green ** power, modulo.green)
                blue = pow(self.blue ** power, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red ** power, modulo)
                green = pow(self.green ** power, modulo)
                blue = pow(self.blue ** power, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and '{type(power)}'. "
                            "Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __neg__(self):
        return ColourHSV(*_rgb_to_hsv(255 - self.red, 255 - self.green, 255 - self.blue))

    def __pos__(self):
        return ColourHSV(*_rgb_to_hsv(self.red, self.green, self.blue))

    def __abs__(self):
        c_value = (self.red + self.green + self.blue) // 3
        return ColourHSV(*_rgb_to_hsv(c_value, c_value, c_value))

    def __lshift__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue << other.hue
            saturation = self.saturation << other.saturation
            value = self.value << other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if value > 100 else (0 if value < 0 else value))

        elif isinstance(other, Colour):
            red = self.red << other.red
            green = self.green << other.green
            blue = self.blue << other.blue

        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = green, blue, red
        else:
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __rshift__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue >> other.hue
            saturation = self.saturation >> other.saturation
            value = self.value >> other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if value > 100 else (0 if value < 0 else value))

        elif isinstance(other, Colour):
            red = self.red >> other.red
            green = self.green >> other.green
            blue = self.blue >> other.blue

        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = blue, red, green
        else:
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __and__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue & other.hue
            saturation = self.saturation & other.saturation
            value = self.value & other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if value > 100 else (0 if value < 0 else value))

        elif isinstance(other, Colour):
            red = self.red & other.red
            green = self.green & other.green
            blue = self.blue & other.blue

        elif isinstance(other, int):
            red = self.red & other
            green = self.green & other
            blue = self.blue & other
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __xor__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue ^ other.hue
            saturation = self.saturation ^ other.saturation
            value = self.value ^ other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if value > 100 else (0 if value < 0 else value))

        elif isinstance(other, Colour):
            red = self.red ^ other.red
            green = self.green ^ other.green
            blue = self.blue ^ other.blue

        elif isinstance(other, int):
            red = self.red ^ other
            green = self.green ^ other
            blue = self.blue ^ other
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __or__(self, other):
        if isinstance(other, ColourHSV):
            hue = self.hue | other.hue
            saturation = self.saturation | other.saturation
            value = self.value | other.value

            return ColourHSV(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if value > 100 else (0 if value < 0 else value))

        elif isinstance(other, Colour):
            red = self.red | other.red
            green = self.green | other.green
            blue = self.blue | other.blue

        elif isinstance(other, int):
            red = self.red | other
            green = self.green | other
            blue = self.blue | other
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSV(*_rgb_to_hsv(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    # inplace PyNumber Methods

    def __iadd__(self, other):
        if isinstance(other, ColourHSV):
            self.hue += other.hue
            self.saturation += other.saturation
            self.value += other.value

            if self.hue > 360:
                self.hue %= 360
            if self.saturation > 100:
                self.saturation = 100
            if self.value > 100:
                self.value = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red += other.red
            self.green += other.green
            self.blue += other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red += other
            self.green += other
            self.blue += other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __isub__(self, other):
        if isinstance(other, ColourHSV):
            self.hue -= other.hue
            self.saturation -= other.saturation
            self.value -= other.value

            if self.hue < 0:
                self.hue %= 360
            if self.saturation < 0:
                self.saturation = 0
            if self.value < 0:
                self.value = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red -= other.red
            self.green -= other.green
            self.blue -= other.blue

            if self.red < 0:
                self.red = 0
            if self.green < 0:
                self.green = 0
            if self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red -= other
            self.green -= other
            self.blue -= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __imul__(self, other):
        if isinstance(other, ColourHSV):
            self.hue *= other.hue
            self.saturation *= other.saturation
            self.value *= other.value

            if self.hue > 360:
                self.hue %= 360
            if self.saturation > 100:
                self.saturation = 100
            if self.value > 100:
                self.value = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red *= other.red
            self.green *= other.green
            self.blue *= other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red *= other
            self.green *= other
            self.blue *= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __imod__(self, other):
        if isinstance(other, ColourHSV):
            self.hue %= other.hue
            self.saturation %= other.saturation
            self.value %= other.value

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red %= other.red
            self.green %= other.green
            self.blue %= other.blue

        elif isinstance(other, int):
            self.hue %= other
            self.saturation %= other
            self.value %= other
            self.key %= other

            if self.hue < 0:
                self.hue %= 360
            if self.saturation < 0:
                self.saturation = 0
            if self.value < 0:
                self.value = 0
            if self.key < 0:
                self.key = 0
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __ipow__(self, other):
        if isinstance(other, ColourHSV):
            self.hue **= other.hue
            self.saturation **= other.saturation
            self.value **= other.value

            if self.hue > 360:
                self.hue %= 360
            if self.saturation > 100:
                self.saturation = 100
            if self.value > 100:
                self.value = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red += other.red
            self.green += other.green
            self.blue += other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red += other
            self.green += other
            self.blue += other

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and '{type(other)}'. "
                            "Must be a Colour or int")

        self.__update_values()

    def __ilshift__(self, other):
        if isinstance(other, ColourHSV):
            self.hue <<= other.hue
            self.saturation <<= other.saturation
            self.value <<= other.value

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.value > 100:
                self.value = 100
            elif self.value < 0:
                self.value = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red <<= other.red
            self.green <<= other.green
            self.blue <<= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            for _ in range(other):
                self.red, self.green, self.blue = self.green, self.blue, self.red
        else:
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __irshift__(self, other):
        if isinstance(other, ColourHSV):
            self.hue >>= other.hue
            self.saturation >>= other.saturation
            self.value >>= other.value

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.value > 100:
                self.value = 100
            elif self.value < 0:
                self.value = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red >>= other.red
            self.green >>= other.green
            self.blue >>= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            for _ in range(other):
                self.red, self.green, self.blue = self.blue, self.red, self.green
        else:
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __iand__(self, other):
        if isinstance(other, ColourHSV):
            self.hue &= other.hue
            self.saturation &= other.saturation
            self.value &= other.value

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.value > 100:
                self.value = 100
            elif self.value < 0:
                self.value = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red &= other.red
            self.green &= other.green
            self.blue &= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red &= other
            self.green &= other
            self.blue &= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __ixor__(self, other):
        if isinstance(other, ColourHSV):
            self.hue ^= other.hue
            self.saturation ^= other.saturation
            self.value ^= other.value

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.value > 100:
                self.value = 100
            elif self.value < 0:
                self.value = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red ^= other.red
            self.green ^= other.green
            self.blue ^= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red ^= other
            self.green ^= other
            self.blue ^= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __ior__(self, other):
        if isinstance(other, ColourHSV):
            self.hue |= other.hue
            self.saturation |= other.saturation
            self.value |= other.value

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.value > 100:
                self.value = 100
            elif self.value < 0:
                self.value = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red |= other.red
            self.green |= other.green
            self.blue |= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red |= other
            self.green |= other
            self.blue |= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        self.__update_values()

    def __contains__(self, item):
        return self.hue == item or self.saturation == item or self.value == item

    def __copy__(self):
        return ColourHSV(self.hue, self.saturation, self.value)

    def __round__(self, n=None):
        hue = 360 if self.hue > 179 else 0
        saturation = 100 if self.saturation > 49 else 0
        value = 100 if self.value > 49 else 0

        return ColourHSV(hue, saturation, value)

    def __iter__(self):
        for c in (self.hue, self.saturation, self.value):
            yield c

    def _update_on_operation(self):
        self.red, self.green, self.blue = _hsv_to_rgb(self.hue, self.saturation, self.value)

        self.string = f"hsv {self.hue}°, {self.saturation}%, {self.value}%"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)

    def __update_values(self):
        h, s, v = _rgb_to_hsv(self.red, self.green, self.blue)
        self.string = f"hsv {h}°, {s}%, {v}%"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)
        return self

    def set_hue(self, value):
        if isinstance(value, int):
            if 360 > value > -1:
                self.hue = value
            else:
                self.hue = value % 360
            self._update_on_operation()
        else:
            raise GraphicsError(f"\n\nGraphicsError: hue value for set_hue() function must be an integer, not {value}")

        return self

    def set_saturation(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.saturation = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: saturation value for set_saturation() function must be between "
                                    f"0 & 255, inclusive, 0 <= saturation <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: saturation value for set_saturation() function must be an integer, "
                                f"not {value}")

        return self

    def set_value(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.value = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: value for set_value() function must be between 0 & 255, "
                                    f"inclusive, 0 <= value <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: value for set_value() function must be an integer, "
                                f"not {value}")

        return self


class ColourHSL(Colour):
    def __init__(self, h, s, L):
        if isinstance(h, int) and isinstance(s, int) and isinstance(L, int):
            if 360 > h > -1:
                if s > 100 or s < 0:
                    raise GraphicsError("\n\nGraphicsError: s value for HSL colour must be between 0 & 100, "
                                        f"100 >= s >= 0, not {s}")
                if L > 100 or L < 0:
                    raise GraphicsError("\n\nGraphicsError: L value for HSL colour must be between 0 & 100, "
                                        f"100 >= L >= 0, not {L}")

                super().__init__()

                self.string = f"hsl {h}°, {s}%, {L}%"

                L /= 100
                s /= 100

                c = (1 - abs(2 * L - 1)) * s
                x = c * (1 - abs((h / 60) % 2 - 1))
                m = L - c / 2

                if h < 60:
                    rgb_ = (c, x, 0)
                elif h < 120:
                    rgb_ = (x, c, 0)
                elif h < 180:
                    rgb_ = (0, c, x)
                elif h < 240:
                    rgb_ = (0, x, c)
                elif h < 300:
                    rgb_ = (x, 0, c)
                else:
                    rgb_ = (c, 0, x)

                self.red = round(255 * (rgb_[0] + m))
                self.green = round(255 * (rgb_[1] + m))
                self.blue = round(255 * (rgb_[2] + m))

                self.hue = h
                self.saturation = s
                self.luminance = L

                self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)
            else:
                raise GraphicsError(f"\n\nGraphicsError: h value for HSL colour must be between 0 & 359, 360 > h >= 0, "
                                    f"not {h}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: HSL values must be integers (H) & floats (S & V)! not {h}, {s}, "
                                f"{L}")

    # PyNumber Methods

    def __add__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue + other.hue
            saturation = self.saturation + other.saturation
            luminance = self.luminance + other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else saturation,
                             100 if luminance > 100 else luminance)

        elif isinstance(other, Colour):
            red = self.red + other.red
            green = self.green + other.green
            blue = self.blue + other.blue

        elif isinstance(other, int):
            red = self.red + other
            green = self.green + other
            blue = self.blue + other
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __sub__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue - other.hue
            saturation = self.saturation - other.saturation
            luminance = self.luminance - other.luminance

            return ColourHSL(hue % 360,
                             0 if saturation < 0 else saturation,
                             0 if luminance < 0 else luminance)

        elif isinstance(other, Colour):
            red = self.red - other.red
            green = self.green - other.green
            blue = self.blue - other.blue

        elif isinstance(other, int):
            red = self.red - other
            green = self.green - other
            blue = self.blue - other
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mul__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue * other.hue
            saturation = self.saturation * other.saturation
            luminance = self.luminance * other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else saturation,
                             100 if luminance > 100 else luminance)

        elif isinstance(other, Colour):
            red = self.red * other.red
            green = self.green * other.green
            blue = self.blue * other.blue

        elif isinstance(other, int):
            red = self.red * other
            green = self.green * other
            blue = self.blue * other
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __mod__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue % other.hue
            saturation = self.saturation % other.saturation
            luminance = self.luminance % other.luminance

            return ColourHSL(hue, saturation, luminance)

        elif isinstance(other, Colour):
            red = self.red % other.red
            green = self.green % other.green
            blue = self.blue % other.blue

        elif isinstance(other, int):
            red = self.red % other
            green = self.green % other
            blue = self.blue % other
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __pow__(self, power, modulo=None):
        if isinstance(power, ColourHSL):
            if isinstance(modulo, int):
                hue = pow(self.hue, power.hue, modulo)
                saturation = pow(self.saturation, power.saturation, modulo)
                luminance = pow(self.luminance, power.luminance, modulo)

            elif isinstance(modulo, ColourHSL):
                hue = pow(self.hue, power.hue, modulo.hue)
                saturation = pow(self.saturation, power.saturation, modulo.saturation)
                luminance = pow(self.luminance, power.luminance, modulo.luminance)

            else:
                raise TypeError(f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}' when power is"
                                f" a ColourHSL'. Must be a ColourHSL or int")

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else saturation,
                             100 if luminance > 100 else luminance)

        elif isinstance(power, Colour):
            if isinstance(modulo, Colour):
                red = pow(self.red, power.red, modulo.red)
                green = pow(self.green ** power.green, modulo.green)
                blue = pow(self.blue ** power.blue, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red, power.red, modulo)
                green = pow(self.green ** power.green, modulo)
                blue = pow(self.blue ** power.blue, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")

        elif isinstance(power, int):
            if isinstance(modulo, Colour):
                red = pow(self.red ** power, modulo.red)
                green = pow(self.green ** power, modulo.green)
                blue = pow(self.blue ** power, modulo.blue)
            elif isinstance(modulo, int):
                red = pow(self.red ** power, modulo)
                green = pow(self.green ** power, modulo)
                blue = pow(self.blue ** power, modulo)
            else:
                raise TypeError(
                    f"unsupported operand type(s) for 'modulo': 'Colour' and '{type(modulo)}'. Must be a Colour or int")
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and '{type(power)}'. "
                            "Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __neg__(self):
        return ColourHSL(*_rgb_to_hsl(255 - self.red, 255 - self.green, 255 - self.blue))

    def __pos__(self):
        return ColourHSL(*_rgb_to_hsl(self.red, self.green, self.blue))

    def __abs__(self):
        c_luminance = (self.red + self.green + self.blue) // 3
        return ColourHSL(*_rgb_to_hsl(c_luminance, c_luminance, c_luminance))

    def __lshift__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue << other.hue
            saturation = self.saturation << other.saturation
            luminance = self.luminance << other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if luminance > 100 else (0 if luminance < 0 else luminance))

        elif isinstance(other, Colour):
            red = self.red << other.red
            green = self.green << other.green
            blue = self.blue << other.blue

        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = green, blue, red
        else:
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __rshift__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue >> other.hue
            saturation = self.saturation >> other.saturation
            luminance = self.luminance >> other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if luminance > 100 else (0 if luminance < 0 else luminance))

        elif isinstance(other, Colour):
            red = self.red >> other.red
            green = self.green >> other.green
            blue = self.blue >> other.blue

        elif isinstance(other, int):
            red, green, blue = self.red, self.green, self.blue
            for _ in range(other):
                red, green, blue = blue, red, green
        else:
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __and__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue & other.hue
            saturation = self.saturation & other.saturation
            luminance = self.luminance & other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if luminance > 100 else (0 if luminance < 0 else luminance))

        elif isinstance(other, Colour):
            red = self.red & other.red
            green = self.green & other.green
            blue = self.blue & other.blue

        elif isinstance(other, int):
            red = self.red & other
            green = self.green & other
            blue = self.blue & other
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __xor__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue ^ other.hue
            saturation = self.saturation ^ other.saturation
            luminance = self.luminance ^ other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if luminance > 100 else (0 if luminance < 0 else luminance))

        elif isinstance(other, Colour):
            red = self.red ^ other.red
            green = self.green ^ other.green
            blue = self.blue ^ other.blue

        elif isinstance(other, int):
            red = self.red ^ other
            green = self.green ^ other
            blue = self.blue ^ other
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    def __or__(self, other):
        if isinstance(other, ColourHSL):
            hue = self.hue | other.hue
            saturation = self.saturation | other.saturation
            luminance = self.luminance | other.luminance

            return ColourHSL(hue % 360,
                             100 if saturation > 100 else (0 if saturation < 0 else saturation),
                             100 if luminance > 100 else (0 if luminance < 0 else luminance))

        elif isinstance(other, Colour):
            red = self.red | other.red
            green = self.green | other.green
            blue = self.blue | other.blue

        elif isinstance(other, int):
            red = self.red | other
            green = self.green | other
            blue = self.blue | other
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

        return ColourHSL(*_rgb_to_hsl(255 if red > 255 else (0 if red < 0 else red),
                                      255 if green > 255 else (0 if green < 0 else green),
                                      255 if blue > 255 else (0 if blue < 0 else blue)))

    # inplace PyNumber Methods

    def __iadd__(self, other):
        if isinstance(other, ColourHSL):
            self.hue += other.hue
            self.saturation += other.saturation
            self.luminance += other.luminance

            if self.hue > 360:
                self.hue %= 360
            if self.saturation > 100:
                self.saturation = 100
            if self.luminance > 100:
                self.luminance = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red += other.red
            self.green += other.green
            self.blue += other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red += other
            self.green += other
            self.blue += other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __isub__(self, other):
        if isinstance(other, ColourHSL):
            self.hue -= other.hue
            self.saturation -= other.saturation
            self.luminance -= other.luminance

            if self.hue < 0:
                self.hue %= 360
            if self.saturation < 0:
                self.saturation = 0
            if self.luminance < 0:
                self.luminance = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red -= other.red
            self.green -= other.green
            self.blue -= other.blue

            if self.red < 0:
                self.red = 0
            if self.green < 0:
                self.green = 0
            if self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red -= other
            self.green -= other
            self.blue -= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __imul__(self, other):
        if isinstance(other, ColourHSL):
            self.hue *= other.hue
            self.saturation *= other.saturation
            self.luminance *= other.luminance

            if self.hue > 360:
                self.hue %= 360
            if self.saturation > 100:
                self.saturation = 100
            if self.luminance > 100:
                self.luminance = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red *= other.red
            self.green *= other.green
            self.blue *= other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red *= other
            self.green *= other
            self.blue *= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __imod__(self, other):
        if isinstance(other, ColourHSL):
            self.hue %= other.hue
            self.saturation %= other.saturation
            self.luminance %= other.luminance

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red %= other.red
            self.green %= other.green
            self.blue %= other.blue

        elif isinstance(other, int):
            self.hue %= other
            self.saturation %= other
            self.luminance %= other
            self.key %= other

            if self.hue < 0:
                self.hue %= 360
            if self.saturation < 0:
                self.saturation = 0
            if self.luminance < 0:
                self.luminance = 0
            if self.key < 0:
                self.key = 0
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __ipow__(self, other):
        if isinstance(other, ColourHSL):
            self.hue **= other.hue
            self.saturation **= other.saturation
            self.luminance **= other.luminance

            if self.hue > 360:
                self.hue %= 360
            if self.saturation > 100:
                self.saturation = 100
            if self.luminance > 100:
                self.luminance = 100

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red += other.red
            self.green += other.green
            self.blue += other.blue

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255

        elif isinstance(other, int):
            self.red += other
            self.green += other
            self.blue += other

            if self.red > 255:
                self.red = 255
            if self.green > 255:
                self.green = 255
            if self.blue > 255:
                self.blue = 255
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Colour' and '{type(other)}'. "
                            "Must be a Colour or int")

    def __ilshift__(self, other):
        if isinstance(other, ColourHSL):
            self.hue <<= other.hue
            self.saturation <<= other.saturation
            self.luminance <<= other.luminance

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.luminance > 100:
                self.luminance = 100
            elif self.luminance < 0:
                self.luminance = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red <<= other.red
            self.green <<= other.green
            self.blue <<= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            for _ in range(other):
                self.red, self.green, self.blue = self.green, self.blue, self.red
        else:
            raise TypeError(
                f"unsupported operand type(s) for <<: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __irshift__(self, other):
        if isinstance(other, ColourHSL):
            self.hue >>= other.hue
            self.saturation >>= other.saturation
            self.luminance >>= other.luminance

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.luminance > 100:
                self.luminance = 100
            elif self.luminance < 0:
                self.luminance = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red >>= other.red
            self.green >>= other.green
            self.blue >>= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            for _ in range(other):
                self.red, self.green, self.blue = self.blue, self.red, self.green
        else:
            raise TypeError(
                f"unsupported operand type(s) for >>: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __iand__(self, other):
        if isinstance(other, ColourHSL):
            self.hue &= other.hue
            self.saturation &= other.saturation
            self.luminance &= other.luminance

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.luminance > 100:
                self.luminance = 100
            elif self.luminance < 0:
                self.luminance = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red &= other.red
            self.green &= other.green
            self.blue &= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red &= other
            self.green &= other
            self.blue &= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __ixor__(self, other):
        if isinstance(other, ColourHSL):
            self.hue ^= other.hue
            self.saturation ^= other.saturation
            self.luminance ^= other.luminance

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.luminance > 100:
                self.luminance = 100
            elif self.luminance < 0:
                self.luminance = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red ^= other.red
            self.green ^= other.green
            self.blue ^= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red ^= other
            self.green ^= other
            self.blue ^= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __ior__(self, other):
        if isinstance(other, ColourHSL):
            self.hue |= other.hue
            self.saturation |= other.saturation
            self.luminance |= other.luminance

            if self.hue > 360:
                self.hue %= 360
            elif self.hue < 0:
                self.hue %= 360

            if self.saturation > 100:
                self.saturation = 100
            elif self.saturation < 0:
                self.saturation = 0

            if self.luminance > 100:
                self.luminance = 100
            elif self.luminance < 0:
                self.luminance = 0

            self._update_on_operation()

        elif isinstance(other, Colour):
            self.red |= other.red
            self.green |= other.green
            self.blue |= other.blue

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0

        elif isinstance(other, int):
            self.red |= other
            self.green |= other
            self.blue |= other

            if self.red > 255:
                self.red = 255
            elif self.red < 0:
                self.red = 0

            if self.green > 255:
                self.green = 255
            elif self.green < 0:
                self.green = 0

            if self.blue > 255:
                self.blue = 255
            elif self.blue < 0:
                self.blue = 0
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Colour' and '{type(other)}'. Must be a Colour or int")

    def __contains__(self, item):
        return self.hue == item or self.saturation == item or self.luminance == item

    def __copy__(self):
        return ColourHSL(self.hue, self.saturation, self.luminance)

    def __round__(self, n=None):
        hue = 360 if self.hue > 179 else 0
        saturation = 100 if self.saturation > 49 else 0
        luminance = 100 if self.luminance > 49 else 0

        return ColourHSL(hue, saturation, luminance)

    def __iter__(self):
        for c in (self.hue, self.saturation, self.luminance):
            yield c

    def _update_on_operation(self):
        self.red, self.green, self.blue = _hsv_to_rgb(self.hue, self.saturation, self.luminance)

        self.string = f"hsv {self.hue}°, {self.saturation}%, {self.luminance}%"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)

    def __update_values(self):
        h, s, L = _rgb_to_hsl(self.red, self.green, self.blue)
        self.string = f"hsv {h}°, {s}%, {L}%"
        self.colour = "#%02x%02x%02x" % (self.red, self.green, self.blue)
        return self

    def set_hue(self, value):
        if isinstance(value, int):
            if 360 > value > -1:
                self.hue = value
            else:
                self.hue = value % 360
            self._update_on_operation()
        else:
            raise GraphicsError(f"\n\nGraphicsError: hue value for set_hue() function must be an integer, not {value}")

        return self

    def set_saturation(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.saturation = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: saturation value for set_saturation() function must be between "
                                    f"0 & 255, inclusive, 0 <= saturation <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: saturation value for set_saturation() function must be an integer, "
                                f"not {value}")

        return self

    def set_luminance(self, value):
        if isinstance(value, int):
            if 101 > value > -1:
                self.luminance = value
                self._update_on_operation()
            else:
                raise GraphicsError("\n\nGraphicsError: luminance for set_luminance() function must be between 0 & 255,"
                                    f" inclusive, 0 <= luminance <= 100, not {value}")
        else:
            raise GraphicsError("\n\nGraphicsError: luminance for set_luminance() function must be an integer, "
                                f"not {value}")

        return self


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


# L used instead of L because of PEP8
def random_colour_hsl(h=None, s=None, L=None):
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

    if L is None:
        L = randomrandint(0, 100) / 100
    elif isinstance(L, (float, int)):
        if L > 1 or L < 0:
            raise GraphicsError(f"\n\nGraphicsError: The L value must be between 0 & 1 inclusive, not {L}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: The L value must be an integer or float or None, not {L}")

    return ColourHSL(h, s, L)


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
    if isinstance(colour_start, Colour):
        if isinstance(colour_end, Colour):
            if isinstance(divisions, int):
                red_dist = colour_end.red - colour_start.red
                green_dist = colour_end.green - colour_start.green
                blue_dist = colour_end.blue - colour_start.blue

                cur_red, cur_green, cur_blue = colour_start.red, colour_start.green, colour_start.blue

                gradient = []
                for i in range(divisions - 1):
                    gradient.append(ColourRGB(max(0, cur_red), max(cur_green, 0), max(cur_blue, 0)))
                    cur_red = colour_start.red + i * red_dist // divisions
                    cur_green = colour_start.green + i * green_dist // divisions
                    cur_blue = colour_start.blue + i * blue_dist // divisions

                gradient.append(colour_end)
                return gradient
            else:
                raise GraphicsError(f"\n\nGraphicsError: The number of divisions must be an integer, not {divisions}")
        else:
            raise GraphicsError(
                f"\n\nGraphicsError: The end colour (colour_end) must be a Colour object, not {colour_end}")
    else:
        raise GraphicsError("\n\nGraphicsError: The start colour (colour_start) must be a Colour object, "
                            f"not {colour_start}")


def color_gradient(color_start=ColourRGB(255, 255, 255), color_end=ColourRGB(0, 0, 0), divisions=10):
    if isinstance(color_start, Colour):
        if isinstance(color_end, Colour):
            if isinstance(divisions, int):
                red_dist = color_end.red - color_start.red
                green_dist = color_end.green - color_start.green
                blue_dist = color_end.blue - color_start.blue

                cur_red, cur_green, cur_blue = color_start.red, color_start.green, color_start.blue

                gradient = []
                for i in range(divisions - 1):
                    gradient.append(ColourRGB(max(0, cur_red), max(cur_green, 0), max(cur_blue, 0)))
                    cur_red = color_start.red + i * red_dist // divisions
                    cur_green = color_start.green + i * green_dist // divisions
                    cur_blue = color_start.blue + i * blue_dist // divisions

                gradient.append(color_end)
                return gradient
            else:
                raise GraphicsError(f"\n\nGraphicsError: The number of divisions must be an integer, not {divisions}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The end color (color_end) must be a Color object, not {color_end}")
    else:
        raise GraphicsError("\n\nGraphicsError: The start color (color_start) must be a Color object, "
                            f"not {color_start}")


def colour_gradient_2d(colour_start1=ColourRGB(0, 0, 0), colour_end1=ColourRGB(255, 0, 0),
                       colour_start2=ColourRGB(255, 255, 255), colour_end2=ColourRGB(0, 255, 0),
                       divisions_x=10, divisions_y=10):
    if isinstance(colour_start1, Colour):
        if isinstance(colour_start2, Colour):
            if isinstance(colour_end1, Colour):
                if isinstance(colour_end2, Colour):
                    if isinstance(divisions_x, int):
                        if isinstance(divisions_y, int):
                            top_gradient = colour_gradient(colour_start1, colour_end1, divisions=divisions_x)
                            bottom_gradient = colour_gradient(colour_start2, colour_end2, divisions=divisions_x)

                            gradient = [[None for _ in range(divisions_y)] for _ in range(divisions_x)]

                            for col in range(divisions_x):
                                gradient[col][0] = top_gradient[col]
                                gradient[col][-1] = bottom_gradient[col]

                            for col in range(len(gradient)):
                                gradient[col] = colour_gradient(gradient[col][0], gradient[col][-1], divisions_y)

                            return gradient
                        else:
                            raise GraphicsError("\n\nGraphicsError: The Y divisions (divisions_y) must be an integer, "
                                                f"not {divisions_y}")
                    else:
                        raise GraphicsError(
                            f"\n\nGraphicsError: The X divisions (divisions_x) must be an integer, not {divisions_x}")
                else:
                    raise GraphicsError("\n\nGraphicsError: The end colour (colour_end2) must be a Colour object, "
                                        f"not {colour_end2}")
            else:
                raise GraphicsError("\n\nGraphicsError: The end colour (colour_end1) must be a Colour object, "
                                    f"not {colour_end1}")
        else:
            raise GraphicsError("\n\nGraphicsError: The start colour (colour_start2) must be a Colour object, "
                                f"not {colour_start2}")
    else:
        raise GraphicsError("\n\nGraphicsError: The start colour (colour_start1) must be a Colour object, "
                            f"not {colour_start1}")


def color_gradient_2d(color_start1=ColorRGB(0, 0, 0), color_end1=ColorRGB(255, 0, 0),
                      color_start2=ColorRGB(255, 255, 255), color_end2=ColorRGB(0, 255, 0),
                      divisions_x=10, divisions_y=10):
    if isinstance(color_start1, Color):
        if isinstance(color_start2, Color):
            if isinstance(color_end1, Color):
                if isinstance(color_end2, Color):
                    if isinstance(divisions_x, int):
                        if isinstance(divisions_y, int):
                            top_gradient = color_gradient(color_start1, color_end1, divisions=divisions_x)
                            bottom_gradient = color_gradient(color_start2, color_end2, divisions=divisions_x)

                            gradient = [[None for _ in range(divisions_y)] for _ in range(divisions_x)]

                            for col in range(divisions_x):
                                gradient[col][0] = top_gradient[col]
                                gradient[col][-1] = bottom_gradient[col]

                            for col in range(0, len(gradient)):
                                gradient[col] = color_gradient(gradient[col][0], gradient[col][-1], divisions_y)

                            return gradient
                        else:
                            raise GraphicsError("\n\nGraphicsError: The Y divisions (divisions_y) must be an integer, "
                                                f"not {divisions_y}")
                    else:
                        raise GraphicsError(
                            f"\n\nGraphicsError: The X divisions (divisions_x) must be an integer, not {divisions_x}")
                else:
                    raise GraphicsError("\n\nGraphicsError: The end color (color_end2) must be a Color object, "
                                        f"not {color_end2}")
            else:
                raise GraphicsError("\n\nGraphicsError: The end color (color_end1) must be a Color object, "
                                    f"not {color_end1}")
        else:
            raise GraphicsError("\n\nGraphicsError: The start color (color_start2) must be a Color object, "
                                f"not {color_start2}")
    else:
        raise GraphicsError("\n\nGraphicsError: The start color (color_start1) must be a Color object, "
                            f"not {color_start1}")


# Colour Blending
def blend_colour_linear(start, end, t):
    if isinstance(start, Colour):
        if isinstance(end, Colour):
            return ColourRGB(round(LinearInterpolation(start.red, end.red, t)),
                             round(LinearInterpolation(start.green, end.green, t)),
                             round(LinearInterpolation(start.blue, end.blue, t)))
        else:
            raise GraphicsError(f"\n\nGraphicsError: end colour for blending must be a Colour instance, not {end}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: start colour for blending must be a Colour instance, not {start}")


def blend_colour_cosine(start, end, t):
    if isinstance(start, Colour):
        if isinstance(end, Colour):
            return ColourRGB(round(CosineInterpolation(start.red, end.red, t)),
                             round(CosineInterpolation(start.green, end.green, t)),
                             round(CosineInterpolation(start.blue, end.blue, t)))
        else:
            raise GraphicsError(f"\n\nGraphicsError: end colour for blending must be a Colour instance, not {end}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: start colour for blending must be a Colour instance, not {start}")


def blend_colour_cubic(start, end, t):
    if isinstance(start, Colour):
        if isinstance(end, Colour):
            return ColourRGB(round(CubicInterpolation(start.red, start.red, end.red,
                                                      end.red, t)),
                             round(CubicInterpolation(start.green, start.green, end.green,
                                                      end.green, t)),
                             round(CubicInterpolation(start.blue, start.blue, end.blue,
                                                      end.blue, t)))
        else:
            raise GraphicsError(f"\n\nGraphicsError: end colour for blending must be a Colour instance, not {end}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: start colour for blending must be a Colour instance, not {start}")


def blend_colour_hermite(start, end, t, tension=1, bias=0):
    if isinstance(start, Colour):
        if isinstance(end, Colour):
            return ColourRGB(round(HermiteInterpolation(start.red, start.red, end.red,
                                                        end.red, t, tension=tension, bias=bias)),
                             round(HermiteInterpolation(start.green, start.green, end.green,
                                                        end.green, t, tension=tension, bias=bias)),
                             round(HermiteInterpolation(start.blue, start.blue, end.blue,
                                                        end.blue, t, tension=tension, bias=bias)))
        else:
            raise GraphicsError(f"\n\nGraphicsError: end colour for blending must be a Colour instance, not {end}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: start colour for blending must be a Colour instance, not {start}")


# American Spelling Blending

blend_color_linear = blend_colour_linear
blend_color_cosine = blend_colour_cosine
blend_color_cubic = blend_colour_cubic
blend_color_hermite = blend_colour_hermite


# -------------------------------------------------------------------------
# COLOUR TYPE CONVERSIONS (with argument checking)


# RGB to other format

def rgb_to_hex(red, green, blue):
    if isinstance(red, int):
        if isinstance(green, int):
            if isinstance(blue, int):
                if red < 0 or red > 255:
                    raise GraphicsError("\n\nGraphicsError: red value for RGB to Hex conversion must be between "
                                        f"0 & 255, inclusive, 0 <= red <= 255, not {red}")
                elif green < 0 or green > 255:
                    raise GraphicsError("\n\nGraphicsError: green value for RGB to Hex conversion must be between "
                                        f"0 & 255, inclusive, 0 <= green <= 255, not {green}")
                elif blue < 0 or blue > 255:
                    raise GraphicsError("\n\nGraphicsError: blue value for RGB to Hex conversion must be "
                                        f"between 0 & 255, inclusive, 0 <= blue <= 255, not {blue}")
            else:
                raise GraphicsError("\n\nGraphicsError: blue value for conversion from RGB to Hex must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: green value for conversion from RGB to Hex must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: red value for conversion from RGB to Hex must be an integer")

    return "#%02x%02x%02x" % (red, green, blue)


def rgb_to_cmyk(red, green, blue):
    if isinstance(red, int):
        if isinstance(green, int):
            if isinstance(blue, int):
                if red < 0 or red > 255:
                    raise GraphicsError("\n\nGraphicsError: red value for RGB to CMYK conversion must be between "
                                        f"0 & 255, inclusive, 0 <= red <= 255, not {red}")
                else:
                    if green < 0 or green > 255:
                        raise GraphicsError("\n\nGraphicsError: green value for RGB to CMYK conversion must be between "
                                            f"0 & 255, inclusive, 0 <= green <= 255, not {green}")
                    else:
                        if blue < 0 or blue > 255:
                            raise GraphicsError("\n\nGraphicsError: blue value for RGB to CMYK conversion must be "
                                                f"between 0 & 255, inclusive, 0 <= blue <= 255, not {blue}")
            else:
                raise GraphicsError("\n\nGraphicsError: blue value for conversion from RGB to CMYK must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: green value for conversion from RGB to CMYK must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: red value for conversion from RGB to CMYK must be an integer")

    return _rgb_to_cmyk(red, green, blue)


def rgb_to_hsl(red, green, blue):
    if isinstance(red, int):
        if isinstance(green, int):
            if isinstance(blue, int):
                if red < 0 or red > 255:
                    raise GraphicsError("\n\nGraphicsError: red value for RGB to HSL conversion must be between "
                                        f"0 & 255, inclusive, 0 <= red <= 255, not {red}")
                else:
                    if green < 0 or green > 255:
                        raise GraphicsError("\n\nGraphicsError: green value for RGB to HSL conversion must be between "
                                            f"0 & 255, inclusive, 0 <= green <= 255, not {green}")
                    else:
                        if blue < 0 or blue > 255:
                            raise GraphicsError("\n\nGraphicsError: blue value for RGB to HSL conversion must be "
                                                f"between 0 & 255, inclusive, 0 <= blue <= 255, not {blue}")
            else:
                raise GraphicsError("\n\nGraphicsError: blue value for conversion from RGB to HSL must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: green value for conversion from RGB to HSL must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: red value for conversion from RGB to HSL must be an integer")

    return _rgb_to_hsl(red, green, blue)


def rgb_to_hsv(red, green, blue):
    if isinstance(red, int):
        if isinstance(green, int):
            if isinstance(blue, int):
                if red < 0 or red > 255:
                    raise GraphicsError("\n\nGraphicsError: red value for RGB to HSV conversion must be between "
                                        f"0 & 255, inclusive, 0 <= red <= 255, not {red}")
                else:
                    if green < 0 or green > 255:
                        raise GraphicsError("\n\nGraphicsError: green value for RGB to HSV conversion must be between "
                                            f"0 & 255, inclusive, 0 <= green <= 255, not {green}")
                    else:
                        if blue < 0 or blue > 255:
                            raise GraphicsError("\n\nGraphicsError: blue value for RGB to HSV conversion must be "
                                                f"between 0 & 255, inclusive, 0 <= blue <= 255, not {blue}")
            else:
                raise GraphicsError("\n\nGraphicsError: blue value for conversion from RGB to HSV must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: green value for conversion from RGB to HSV must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: red value for conversion from RGB to HSV must be an integer")

    return _rgb_to_hsv(red, green, blue)


# Hex to other format

def hex_to_rgb(hexstring):
    if isinstance(hexstring, str):
        if len(hexstring) == 7:
            try:
                int(hexstring[1:], 16)
            except ValueError:
                raise GraphicsError(
                    f"\n\nGraphicsError: The hexstring value must be a hexadecimal string, not {hexstring}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The length of the hexstring must be 7: '#rrggbb', not {hexstring}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: Hex value must be a string in format: #rrggbb, not {hexstring}")

    return (int(hexstring[i:i + 2], 16) for i in (1, 3, 5))


def hex_to_cmyk(hexstring):
    if isinstance(hexstring, str):
        if len(hexstring) == 7:
            try:
                int(hexstring[1:], 16)
            except ValueError:
                raise GraphicsError(
                    f"\n\nGraphicsError: The hexstring value must be a hexadecimal string, not {hexstring}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The length of the hexstring must be 7: '#rrggbb', not {hexstring}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: Hex value must be a string in format: #rrggbb, not {hexstring}")

    return _hex_to_cmyk(hexstring)


def hex_to_hsl(hexstring):
    if isinstance(hexstring, str):
        if len(hexstring) == 7:
            try:
                int(hexstring[1:], 16)
            except ValueError:
                raise GraphicsError(
                    f"\n\nGraphicsError: The hexstring value must be a hexadecimal string, not {hexstring}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The length of the hexstring must be 7: '#rrggbb', not {hexstring}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: Hex value must be a string in format: #rrggbb, not {hexstring}")

    return _hex_to_cmyk(hexstring)


def hex_to_hsv(hexstring):
    if isinstance(hexstring, str):
        if len(hexstring) == 7:
            try:
                int(hexstring[1:], 16)
            except ValueError:
                raise GraphicsError(
                    f"\n\nGraphicsError: The hexstring value must be a hexadecimal string, not {hexstring}")
        else:
            raise GraphicsError(f"\n\nGraphicsError: The length of the hexstring must be 7: '#rrggbb', not {hexstring}")
    else:
        raise GraphicsError(f"\n\nGraphicsError: Hex value must be a string in format: #rrggbb, not {hexstring}")

    return _hex_to_cmyk(hexstring)


# CMYK to other format

def cmyk_to_rgb(cyan, magenta, yellow, key):
    if isinstance(cyan, int):
        if isinstance(magenta, int):
            if isinstance(yellow, int):
                if isinstance(key, int):
                    if cyan < 0 or cyan > 100:
                        raise GraphicsError("\n\nGraphicsError: cyan value for CMYK to RGB conversion must be between "
                                            f"0 & 100, inclusive, 0 <= cyan <= 100, not {cyan}")
                    else:
                        if magenta < 0 or magenta > 100:
                            raise GraphicsError("\n\nGraphicsError: magenta value for CMYK to RGB conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= magenta <= 100, not {magenta}")
                        else:
                            if yellow < 0 or yellow > 100:
                                raise GraphicsError("\n\nGraphicsError: yellow value for CMYK to RGB conversion must be"
                                                    f" between 0 & 100, inclusive, 0 <= yellow <= 100, not {yellow}")
                else:
                    raise GraphicsError(
                        f"\n\nGraphicsError: key value for conversion from CMYK to RGB must be an integer, not {key}")
            else:
                raise GraphicsError(
                    f"\n\nGraphicsError: yellow value for conversion from CMYK to RGB must be an integer, not {yellow}")
        else:
            raise GraphicsError(
                f"\n\nGraphicsError: magenta value for conversion from CMYK to RGB must be an integer, not {magenta}")
    else:
        raise GraphicsError(
            f"\n\nGraphicsError: cyan value for conversion from CMYK to RGB must be an integer, not {cyan}")

    return _cmyk_to_rgb(cyan, magenta, yellow, key)


def cmyk_to_hex(cyan, magenta, yellow, key):
    if isinstance(cyan, int):
        if isinstance(magenta, int):
            if isinstance(yellow, int):
                if isinstance(key, int):
                    if cyan < 0 or cyan > 100:
                        raise GraphicsError("\n\nGraphicsError: cyan value for CMYK to Hex conversion must be between "
                                            f"0 & 100, inclusive, 0 <= cyan <= 100, not {cyan}")
                    else:
                        if magenta < 0 or magenta > 100:
                            raise GraphicsError("\n\nGraphicsError: magenta value for CMYK to Hex conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= magenta <= 100, not {magenta}")
                        else:
                            if yellow < 0 or yellow > 100:
                                raise GraphicsError("\n\nGraphicsError: yellow value for CMYK to Hex conversion must be"
                                                    f" between 0 & 100, inclusive, 0 <= yellow <= 100, not {yellow}")
                else:
                    raise GraphicsError(
                        f"\n\nGraphicsError: key value for conversion from CMYK to Hex must be an integer, not {key}")
            else:
                raise GraphicsError(
                    f"\n\nGraphicsError: yellow value for conversion from CMYK to Hex must be an integer, not {yellow}")
        else:
            raise GraphicsError(
                f"\n\nGraphicsError: magenta value for conversion from CMYK to Hex must be an integer, not {magenta}")
    else:
        raise GraphicsError(
            f"\n\nGraphicsError: cyan value for conversion from CMYK to Hex must be an integer, not {cyan}")

    return _cmyk_to_hex(cyan, magenta, yellow, key)


def cmyk_to_hsl(cyan, magenta, yellow, key):
    if isinstance(cyan, int):
        if isinstance(magenta, int):
            if isinstance(yellow, int):
                if isinstance(key, int):
                    if cyan < 0 or cyan > 100:
                        raise GraphicsError("\n\nGraphicsError: cyan value for CMYK to HSL conversion must be between "
                                            f"0 & 100, inclusive, 0 <= cyan <= 100, not {cyan}")
                    else:
                        if magenta < 0 or magenta > 100:
                            raise GraphicsError("\n\nGraphicsError: magenta value for CMYK to HSL conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= magenta <= 100, not {magenta}")
                        else:
                            if yellow < 0 or yellow > 100:
                                raise GraphicsError("\n\nGraphicsError: yellow value for CMYK to HSL conversion must be"
                                                    f" between 0 & 100, inclusive, 0 <= yellow <= 100, not {yellow}")
                else:
                    raise GraphicsError(
                        f"\n\nGraphicsError: key value for conversion from CMYK to HSL must be an integer, not {key}")
            else:
                raise GraphicsError(
                    f"\n\nGraphicsError: yellow value for conversion from CMYK to HSL must be an integer, not {yellow}")
        else:
            raise GraphicsError(
                f"\n\nGraphicsError: magenta value for conversion from CMYK to HSL must be an integer, not {magenta}")
    else:
        raise GraphicsError(
            f"\n\nGraphicsError: cyan value for conversion from CMYK to HSL must be an integer, not {cyan}")

    return _cmyk_to_hsl(cyan, magenta, yellow, key)


def cmyk_to_hsv(cyan, magenta, yellow, key):
    if isinstance(cyan, int):
        if isinstance(magenta, int):
            if isinstance(yellow, int):
                if isinstance(key, int):
                    if cyan < 0 or cyan > 100:
                        raise GraphicsError("\n\nGraphicsError: cyan value for CMYK to HSV conversion must be between "
                                            f"0 & 100, inclusive, 0 <= cyan <= 100, not {cyan}")
                    else:
                        if magenta < 0 or magenta > 100:
                            raise GraphicsError("\n\nGraphicsError: magenta value for CMYK to HSV conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= magenta <= 100, not {magenta}")
                        else:
                            if yellow < 0 or yellow > 100:
                                raise GraphicsError("\n\nGraphicsError: yellow value for CMYK to HSV conversion must be"
                                                    f" between 0 & 100, inclusive, 0 <= yellow <= 100, not {yellow}")
                else:
                    raise GraphicsError(
                        f"\n\nGraphicsError: key value for conversion from CMYK to HSV must be an integer, not {key}")
            else:
                raise GraphicsError(
                    f"\n\nGraphicsError: yellow value for conversion from CMYK to HSV must be an integer, not {yellow}")
        else:
            raise GraphicsError(
                f"\n\nGraphicsError: magenta value for conversion from CMYK to HSV must be an integer, not {magenta}")
    else:
        raise GraphicsError(
            f"\n\nGraphicsError: cyan value for conversion from CMYK to HSV must be an integer, not {cyan}")

    return _cmyk_to_hsv(cyan, magenta, yellow, key)


# HSV to other format

def hsv_to_rgb(hue, saturation, value):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(value, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSV to RGB conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSV to RGB conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if value < 0 or value > 100:
                            raise GraphicsError("\n\nGraphicsError: value value for HSV to RGB conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= value <= 100, not {value}")
            else:
                raise GraphicsError("\n\nGraphicsError: value value for conversion from HSV to RGB must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: saturation value for conversion from HSV to RGB must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSV to RGB must be an integer")

    return _hsv_to_rgb(hue, saturation, value)


def hsv_to_hex(hue, saturation, value):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(value, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSV to Hex conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSV to Hex conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if value < 0 or value > 100:
                            raise GraphicsError("\n\nGraphicsError: value value for HSV to Hex conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= value <= 100, not {value}")
            else:
                raise GraphicsError("\n\nGraphicsError: value value for conversion from HSV to Hex must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: saturation value for conversion from HSV to Hex must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSV to Hex must be an integer")

    return _hsv_to_hex(hue, saturation, value)


def hsv_to_cmyk(hue, saturation, value):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(value, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSV to CMYK conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSV to CMYK conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if value < 0 or value > 100:
                            raise GraphicsError("\n\nGraphicsError: value value for HSV to CMYK conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= value <= 100, not {value}")
            else:
                raise GraphicsError("\n\nGraphicsError: value value for conversion from HSV to CMYK must be an integer")
        else:
            raise GraphicsError(
                "\n\nGraphicsError: saturation value for conversion from HSV to CMYK must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSV to CMYK must be an integer")

    return _hsv_to_cmyk(hue, saturation, value)


def hsv_to_hsl(hue, saturation, value):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(value, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSV to HSL conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSV to HSL conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if value < 0 or value > 100:
                            raise GraphicsError("\n\nGraphicsError: value value for HSV to HSL conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= value <= 100, not {value}")
            else:
                raise GraphicsError("\n\nGraphicsError: value value for conversion from HSV to HSL must be an integer")
        else:
            raise GraphicsError("\n\nGraphicsError: saturation value for conversion from HSV to HSL must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSV to HSL must be an integer")

    return _hsv_to_hsl(hue, saturation, value)


# HSL to other format

def hsl_to_rgb(hue, saturation, luminance):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(luminance, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSL to RGB conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSL to RGB conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if luminance < 0 or luminance > 100:
                            raise GraphicsError("\n\nGraphicsError: luminance value for HSL to RGB conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= luminance <= 100, not {luminance}")
            else:
                raise GraphicsError(
                    "\n\nGraphicsError: luminance value for conversion from HSL to RGB must be an integer")
        else:
            raise GraphicsError(
                "\n\nGraphicsError: saturation value for conversion from HSL to RGB must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSL to RGB must be an integer")

    return _hsl_to_rgb(hue, saturation, luminance)


def hsl_to_hex(hue, saturation, luminance):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(luminance, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSL to Hex conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSL to Hex conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if luminance < 0 or luminance > 100:
                            raise GraphicsError("\n\nGraphicsError: luminance value for HSL to Hex conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= luminance <= 100, not {luminance}")
            else:
                raise GraphicsError(
                    "\n\nGraphicsError: luminance value for conversion from HSL to Hex must be an integer")
        else:
            raise GraphicsError(
                "\n\nGraphicsError: saturation value for conversion from HSL to Hex must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSL to Hex must be an integer")

    return _hsl_to_hex(hue, saturation, luminance)


def hsl_to_cmyk(hue, saturation, luminance):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(luminance, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSL to CMYK conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSL to CMYK conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if luminance < 0 or luminance > 100:
                            raise GraphicsError("\n\nGraphicsError: luminance value for HSL to CMYK conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= luminance <= 100, not {luminance}")
            else:
                raise GraphicsError(
                    "\n\nGraphicsError: luminance value for conversion from HSL to CMYK must be an integer")
        else:
            raise GraphicsError(
                "\n\nGraphicsError: saturation value for conversion from HSL to CMYK must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSL to CMYK must be an integer")

    return _hsl_to_cmyk(hue, saturation, luminance)


def hsl_to_hsv(hue, saturation, luminance):
    if isinstance(hue, int):
        if isinstance(saturation, int):
            if isinstance(luminance, int):
                if hue < 0 or hue > 360:
                    raise GraphicsError("\n\nGraphicsError: hue value for HSL to HSV conversion must be between "
                                        f"0 & 360, inclusive, 0 <= hue <= 360, not {hue}")
                else:
                    if saturation < 0 or saturation > 100:
                        raise GraphicsError("\n\nGraphicsError: saturation value for HSL to HSV conversion must be "
                                            f"between 0 & 100, inclusive, 0 <= saturation <= 100, not {saturation}")
                    else:
                        if luminance < 0 or luminance > 100:
                            raise GraphicsError("\n\nGraphicsError: luminance value for HSL to HSV conversion must be "
                                                f"between 0 & 100, inclusive, 0 <= luminance <= 100, not {luminance}")
            else:
                raise GraphicsError(
                    "\n\nGraphicsError: luminance value for conversion from HSL to HSV must be an integer")
        else:
            raise GraphicsError(
                "\n\nGraphicsError: saturation value for conversion from HSL to HSV must be an integer")
    else:
        raise GraphicsError("\n\nGraphicsError: hue value for conversion from HSL to HSV must be an integer")

    return _hsl_to_hsv(hue, saturation, luminance)


# -------------------------------------------------------------------------
# COLOUR TYPE CONVERSIONS (without argument checking)

# RGB to other format

def _rgb_to_hex(red, green, blue):
    return "#%02x%02x%02x" % (red, green, blue)


def _rgb_to_cmyk(red, green, blue):
    red /= 255
    green /= 255
    blue /= 255

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)


def _rgb_to_hsl(red, green, blue):
    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    L = 0.5 * (cmax + cmin)

    if delta == 0:
        h = 0
        s = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
        s = delta / (1 - abs(2 * L - 1))
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
        s = delta / (1 - abs(2 * L - 1))
    else:
        h = 60 * (((red - green) / delta) + 4)
        s = delta / (1 - abs(2 * L - 1))

    return round(h), round(100 * s), round(100 * L)


def _rgb_to_hsv(red, green, blue):
    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
    else:
        h = 60 * (((red - green) / delta) + 4)

    s = 0 if cmax == 0 else (delta / cmax)

    return round(h), round(100 * s), round(100 * cmax)


# Hex to other format

def _hex_to_rgb(hexstring):
    return (int(hexstring[i:i + 2], 16) for i in (1, 3, 5))


def _hex_to_cmyk(hexstring):
    red, green, blue = hex_to_rgb(hexstring)

    red /= 255
    green /= 255
    blue /= 255

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)


def _hex_to_hsl(hexstring):
    red, green, blue = hex_to_rgb(hexstring)

    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    L = 0.5 * (cmax + cmin)

    if delta == 0:
        h = 0
        s = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
        s = delta / (1 - abs(2 * L - 1))
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
        s = delta / (1 - abs(2 * L - 1))
    else:
        h = 60 * (((red - green) / delta) + 4)
        s = delta / (1 - abs(2 * L - 1))

    return round(h), round(100 * s), round(100 * L)


def _hex_to_hsv(hexstring):
    red, green, blue = hex_to_rgb(hexstring)

    red /= 255
    green /= 255
    blue /= 255

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
    else:
        h = 60 * (((red - green) / delta) + 4)

    s = 0 if cmax == 0 else (delta / cmax)

    return round(h), round(100 * s), round(100 * cmax)


# CMYK to other format

def _cmyk_to_rgb(cyan, magenta, yellow, key):
    return round(255 * (1 - (cyan + key) / 100)), \
           round(255 * (1 - (magenta + key) / 100)), \
           round(255 * (1 - (yellow + key) / 100))


def _cmyk_to_hex(cyan, magenta, yellow, key):
    return "#%02x%02x%02x" % (round(255 * (1 - (cyan + key) / 100)),
                              round(255 * (1 - (magenta + key) / 100)),
                              round(255 * (1 - (yellow + key) / 100)))


def _cmyk_to_hsl(cyan, magenta, yellow, key):
    red = 1 - (cyan + key) / 100
    green = 1 - (magenta + key) / 100
    blue = 1 - (yellow + key) / 100

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    L = 0.5 * (cmax + cmin)

    if delta == 0:
        h = 0
        s = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
        s = delta / (1 - abs(2 * L - 1))
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
        s = delta / (1 - abs(2 * L - 1))
    else:
        h = 60 * (((red - green) / delta) + 4)
        s = delta / (1 - abs(2 * L - 1))

    return round(h), round(100 * s), round(100 * L)


def _cmyk_to_hsv(cyan, magenta, yellow, key):
    red = 1 - (cyan + key) / 100
    green = 1 - (magenta + key) / 100
    blue = 1 - (yellow + key) / 100

    cmax = max(red, green, blue)
    cmin = min(red, green, blue)

    delta = cmax - cmin

    if delta == 0:
        h = 0
    elif cmax == red:
        h = 60 * (((green - blue) / delta) % 6)
    elif cmax == green:
        h = 60 * (((blue - red) / delta) + 2)
    else:
        h = 60 * (((red - green) / delta) + 4)

    s = 0 if cmax == 0 else delta / cmax

    return round(h), round(100 * s), round(100 * cmax)


# HSV to other format

def _hsv_to_rgb(hue, saturation, value):
    saturation /= 100
    value /= 100

    c = value * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = value - c

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return round(255 * (rgb_[0] + m)), \
           round(255 * (rgb_[1] + m)), \
           round(255 * (rgb_[2] + m))


def _hsv_to_hex(hue, saturation, value):
    saturation /= 100
    value /= 100

    c = value * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = value - c

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return "#%02x%02x%02x" % (round(255 * (rgb_[0] + m)), round(255 * (rgb_[1] + m)), round(255 * (rgb_[2] + m)))


def _hsv_to_cmyk(hue, saturation, value):
    saturation /= 100
    value /= 100

    c = value * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = value - c

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    red = rgb_[0] + m
    green = rgb_[1] + m
    blue = rgb_[2] + m

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)


def _hsv_to_hsl(hue, saturation, value):
    saturation /= 100
    value /= 100

    L = value - (0.5 * value * saturation)
    saturation = 0 if L == 0 else ((value - L) / min(L, 1 - L))

    return hue, round(100 * saturation), round(100 * L)


# HSL to other format

def _hsl_to_rgb(hue, saturation, luminance):
    saturation /= 100
    luminance /= 100

    c = (1 - abs(2 * luminance - 1)) * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = luminance - c / 2

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return round(255 * (rgb_[0] + m)), round(255 * (rgb_[1] + m)), round(255 * (rgb_[2] + m))


def _hsl_to_hex(hue, saturation, luminance):
    saturation /= 100
    luminance /= 100

    c = (1 - abs(2 * luminance - 1)) * saturation
    x = c * (1 - abs((hue / 60) % 2 - 1))
    m = luminance - c / 2

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    return "#%02x%02x%02x" % (round(255 * (rgb_[0] + m)), round(255 * (rgb_[1] + m)), round(255 * (rgb_[2] + m)))


def _hsl_to_cmyk(hue, saturation, luminance):
    saturation /= 100
    luminance /= 100

    c = saturation * (1 - abs(2 * luminance - 1))
    m = luminance - c / 2

    x = c * (1 - abs((hue / 60) % 2 - 1))

    if hue < 60:
        rgb_ = (c, x, 0)
    elif hue < 120:
        rgb_ = (x, c, 0)
    elif hue < 180:
        rgb_ = (0, c, x)
    elif hue < 240:
        rgb_ = (0, x, c)
    elif hue < 300:
        rgb_ = (x, 0, c)
    else:
        rgb_ = (c, 0, x)

    red = rgb_[0] + m
    green = rgb_[1] + m
    blue = rgb_[2] + m

    k = 1 - max(red, green, blue)
    k_inverse = 1 - k

    return round(100 * (k_inverse - red) / k_inverse), \
           round(100 * (k_inverse - green) / k_inverse), \
           round(100 * (k_inverse - blue) / k_inverse), \
           round(100 * k)


def _hsl_to_hsv(hue, saturation, luminance):
    saturation /= 100
    luminance /= 100

    v = luminance + saturation * min(luminance, 1 - luminance)
    saturation = 0 if v == 0 else 2 - (2 * luminance / v)

    return hue, round(100 * saturation), round(100 * v)


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

LIGHTEST_OLIVE_GREEN = ColourRGB(210, 225, 144)
LIGHTER_OLIVE_GREEN = ColourRGB(196, 216, 108)
LIGHT_OLIVE_GREEN = ColourRGB(181, 207, 73)
LIGHTISH_OLIVE_GREEN = ColourRGB(163, 191, 69)
OLIVE_GREEN = ColourRGB(129, 161, 64)
DARKISH_OLIVE_GREEN = ColourRGB(116, 146, 58)
DARK_OLIVE_GREEN = ColourRGB(97, 123, 48)
DARKER_OLIVE_GREEN = ColourRGB(66, 84, 31)
DARKEST_OLIVE_GREEN = ColourRGB(46, 64, 11)

LIGHTEST_GREEN = ColourRGB(200, 230, 201)
LIGHTER_GREEN = ColourRGB(165, 214, 167)
LIGHT_GREEN = ColourRGB(129, 199, 132)
LIGHTISH_GREEN = ColourRGB(102, 187, 106)
GREEN = ColourRGB(76, 175, 80)
DARKISH_GREEN = ColourRGB(67, 160, 71)
DARK_GREEN = ColourRGB(56, 142, 60)
DARKER_GREEN = ColourRGB(46, 125, 50)
DARKEST_GREEN = ColourRGB(27, 83, 32)

ABSOLUTE_GREEN = ColourRGB(0, 255, 0)

# Blues
DARKEST_NAVY_BLUE = ColourRGB(20, 27, 34)
DARKER_NAVY_BLUE = ColourRGB(30, 37, 44)
DARK_NAVY_BLUE = ColourRGB(38, 45, 56)
DARKISH_NAVY_BLUE = ColourRGB(45, 57, 68)
NAVY_BLUE = ColourRGB(40, 57, 81)
LIGHTISH_NAVY_BLUE = ColourRGB(35, 57, 93)
LIGHT_NAVY_BLUE = ColourRGB(45, 67, 103)
LIGHTER_NAVY_BLUE = ColourRGB(65, 87, 123)
LIGHTEST_NAVY_BLUE = ColourRGB(85, 107, 143)

LIGHTEST_BLUE = ColourRGB(227, 242, 253)
LIGHTER_BLUE = ColourRGB(187, 222, 251)
LIGHT_BLUE = ColourRGB(144, 202, 255)
LIGHTISH_BLUE = ColourRGB(100, 181, 246)
BLUE = ColourRGB(33, 165, 245)
DARKISH_BLUE = ColourRGB(30, 136, 229)
DARK_BLUE = ColourRGB(25, 118, 210)
DARKER_BLUE = ColourRGB(21, 101, 192)
DARKEST_BLUE = ColourRGB(12, 70, 160)

ABSOLUTE_BLUE = ColourRGB(0, 0, 255)

DARKEST_TURQUOISE = ColourRGB(0, 56, 41)
DARKER_TURQUOISE = ColourRGB(0, 106, 78)
DARK_TURQUOISE = ColourRGB(46, 133, 110)
DARKISH_TURQUOISE = ColourRGB(68, 51, 153)
TURQUOISE = ColourRGB(92, 160, 142)
LIGHTISH_TURQUOISE = ColourRGB(115, 173, 158)
LIGHT_TURQUOISE = ColourRGB(138, 186, 174)
LIGHTER_TURQUOISE = ColourRGB(161, 200, 190)
LIGHTEST_TURQUOISE = ColourRGB(184, 213, 205)

ABSOLUTE_CYAN = ColourRGB(0, 255, 255)

# Purples & Violets
LIGHTEST_PURPLE = ColourRGB(225, 190, 231)
LIGHTER_PURPLE = ColourRGB(206, 147, 216)
LIGHT_PURPLE = ColourRGB(186, 104, 200)
LIGHTISH_PURPLE = ColourRGB(171, 71, 188)
PURPLE = ColourRGB(156, 39, 176)
DARKISH_PURPLE = ColourRGB(142, 36, 170)
DARK_PURPLE = ColourRGB(123, 31, 162)
DARKER_PURPLE = ColourRGB(106, 27, 154)
DARKEST_PURPLE = ColourRGB(74, 20, 140)

ABSOLUTE_PURPLE = ColourRGB(255, 0, 255)

LIGHTEST_VIOLET = ColourRGB(209, 196, 233)
LIGHTER_VIOLET = ColourRGB(179, 157, 219)
LIGHT_VIOLET = ColourRGB(149, 117, 205)
LIGHTISH_VIOLET = ColourRGB(126, 87, 194)
VIOLET = ColourRGB(103, 58, 183)
DARKISH_VIOLET = ColourRGB(94, 53, 177)
DARK_VIOLET = ColourRGB(81, 45, 168)
DARKER_VIOLET = ColourRGB(69, 39, 160)
DARKEST_VIOLET = ColourRGB(49, 27, 146)

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
              LIGHTISH_TURQUOISE, LIGHT_TURQUOISE, LIGHTER_TURQUOISE, LIGHTEST_TURQUOISE, ABSOLUTE_CYAN]

PURPLES = [DARKEST_PURPLE, DARKER_PURPLE, DARK_PURPLE, DARKISH_PURPLE, PURPLE, LIGHTISH_PURPLE, LIGHT_PURPLE,
           LIGHTER_PURPLE, LIGHTEST_PURPLE, ABSOLUTE_PURPLE]

VIOLETS = [DARKEST_VIOLET, DARKER_VIOLET, DARK_VIOLET, DARKISH_VIOLET, VIOLET, LIGHTISH_VIOLET, LIGHT_VIOLET,
           LIGHTER_VIOLET, LIGHTEST_VIOLET]

ABSOLUTE_COLOURS = [ABSOLUTE_BLUE, ABSOLUTE_GREEN, ABSOLUTE_RED, ABSOLUTE_YELLOW, ABSOLUTE_PURPLE, ABSOLUTE_CYAN]

WARM_COLOURS = REDS + YELLOWS + BROWNS + ORANGES + PINKS
COOL_COLOURS = PURPLES + VIOLETS + GREENS + OLIVE_GREENS + NAVY_BLUES + BLUES + TURQUOISES

GOOPYLIB_COLOURS = GREYS + BLUE_GREYS + REDS + PINKS + ORANGES + BROWNS + YELLOWS + OLIVE_GREENS + GREENS + NAVY_BLUES \
                   + BLUES + TURQUOISES + PURPLES + VIOLETS

# American Spelling

ABSOLUTE_COLORS = ABSOLUTE_COLOURS

WARM_COLORS = WARM_COLOURS
COOL_COLORS = COOL_COLOURS

GOOPYLIB_COLORS = GOOPYLIB_COLOURS
