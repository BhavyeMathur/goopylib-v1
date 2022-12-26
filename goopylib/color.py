"""
Module defining colors and related functions
"""

from __future__ import annotations

import goopylib.ext.color as _color
import goopylib.ext.color_conversions as _conversions

from random import randint as _randint
from random import random as _random


# The reason docstrings for the class are copied to the __init__() method is because CLion (and presumably PyCharm)
# renders the 'Raises' section with an odd identation otherwise.


class Color:
    """
    Create colors by passing RGB arguments or a hexstring.
    Specify an alpha value by passing a float as the last parameter.

    Raises:
        ValueError: unrecognised or invalid parameters

    Examples:
        >>> Color(120, 70, 0)
        Color(120, 70, 0)

        >>> Color("#fff")
        Color(255, 255, 255)

        >>> Color(60, 180, 90, 0.5)
        Color(60, 180, 90)
    """

    def __init__(self, *args):
        """
        Create colors by passing RGB arguments or a hexstring.
        Specify an alpha value by passing a float as the last parameter.

        Raises:
            ValueError: unrecognised or invalid parameters

        Examples:
            >>> Color(120, 70, 0)
            Color(120, 70, 0)

            >>> Color("#fff")
            Color(255, 255, 255)

            >>> Color(60, 180, 90, 0.5)
            Color(60, 180, 90)
        """
        self._color = _color.Color(*args)

    def __repr__(self) -> str:
        return self._color.__repr__()

    def __add__(self, other: Union[int, Color]) -> Color:
        if isinstance(other, Color):
            return self._color.__add__(other._color)
        return self._color.__add__(other)

    def __sub__(self, other: Union[int, Color]) -> Color:
        if isinstance(other, Color):
            return self._color.__sub__(other._color)
        return self._color.__sub__(other)

    def __iadd__(self, other: Union[int, Color]):
        if isinstance(other, Color):
            return self._color.__iadd__(other._color)
        return self._color.__iadd__(other)

    def __isub__(self, other: Union[int, Color]):
        if isinstance(other, Color):
            return self._color.__isub__(other._color)
        return self._color.__isub__(other)

    @property
    def red(self) -> int:
        """
        Returns: the red component of the color
        """
        return self._color.red

    @red.setter
    def red(self, value: int):
        self._color.red = value

    @property
    def green(self) -> int:
        """
        Returns: the green component of the color
        """
        return self._color.green

    @green.setter
    def green(self, value: int):
        self._color.green = value

    @property
    def blue(self) -> int:
        """
        Returns: the blue component of the color
        """
        return self._color.blue

    @blue.setter
    def blue(self, value: int):
        self._color.blue = value

    @property
    def alpha(self) -> float:
        """
        Returns: the alpha component of the color
        """
        return self._color.alpha

    @alpha.setter
    def alpha(self, value: float):
        self._color.alpha = value


class ColorRGB(Color):
    """
    Create an RGB color by passing RGB arguments with an optional alpha parameter.
    Convert another color object to RGB by passing it as a parameter.

    Raises:
        TypeError: expected ints for RGB and floats for alpha
        ValueError: RGB must be between 0-255, alpha must be between 0-1

    Examples:
        >>> ColorRGB(120, 70, 0)
        ColorRGB(120, 70, 0)

        >>> ColorRGB(60, 180, 90, 0.5)
        Color(60, 180, 90)

        >>> ColorRGB(other_color)
    """

    def __init__(self, *args):
        """
        Create an RGB color by passing RGB arguments with an optional alpha parameter.
        Convert another color object to RGB by passing it as a parameter.

        Raises:
            TypeError: expected ints for RGB and floats for alpha
            ValueError: RGB must be between 0-255, alpha must be between 0-1

        Examples:
            >>> ColorRGB(120, 70, 0)
            ColorRGB(120, 70, 0)

            >>> ColorRGB(60, 180, 90, 0.5)
            Color(60, 180, 90)

            >>> ColorRGB(other_color)
        """
        self._color = _color.ColorRGB(*args)


class ColorHex(Color):
    """
    Create a Hexadecimal color by passing a hexstring with an optional alpha parameter. The '#' is optional.
    Convert another color object to Hexadecimal by passing it as a parameter.

    Raises:
        TypeError: hexstring must be a string, alpha must be a float

    Examples:
        >>> ColorHex("#000")
        "#000000"

        >>> ColorHex("a7b7c7")
        "#a7b7c7"

        >>> ColorHex(other_color)
    """

    def __init__(self, *args):
        """
        Create a Hexadecimal color by passing a hexstring with an optional alpha parameter. The '#' is optional.
        Convert another color object to Hexadecimal by passing it as a parameter.

        Raises:
            TypeError: hexstring must be a string, alpha must be a float

        Examples:
            >>> ColorHex("#000")
            "#000000"

            >>> ColorHex("a7b7c7")
            "#a7b7c7"

            >>> ColorHex(other_color)
        """

        self._color = _color.ColorHex(*args)


class ColorCMYK(Color):
    """
    Create a CMYK color by passing cyan, magenta, yellow, key and optionally, alpha.
    Convert another color object to CMYK by passing it as a parameter.

    Raises:
        TypeError: CMYK, alpha values must be floats
        ValueError: CMYK, alpha values must be between 0-1

    Examples:
        >>> ColorCMYK(0.5, 0.4, 0.2, 0.1)
        ColorCMYK(0.5, 0.4, 0.2, 0.1)

        >>> ColorCMYK(0.6, 0.9, 1, 1, 0.5)
        ColorCMYK(0.6, 0.9, 1, 1)

        >>> ColorCMYK(other_color)
    """

    def __init__(self, *args):
        """
        Create a CMYK color by passing cyan, magenta, yellow, key and optionally, alpha. All parameters are between 0-1.
        Convert another color object to CMYK by passing it as a parameter.

        Raises:
            TypeError: CMYK, alpha values must be floats
            ValueError: CMYK, alpha values must be between 0-1

        Examples:
            >>> ColorCMYK(0.5, 0.4, 0.2, 0.1)
            ColorCMYK(0.5, 0.4, 0.2, 0.1)

            >>> ColorCMYK(0.6, 0.9, 1, 1, 0.5)
            ColorCMYK(0.6, 0.9, 1, 1)

            >>> ColorCMYK(other_color)
        """
        self._color = _color.ColorCMYK(*args)

    @property
    def cyan(self) -> float:
        """
        Returns: the cyan component of the color
        """
        return self._color.cyan

    @cyan.setter
    def cyan(self, value: float):
        self._color.cyan = value

    @property
    def magenta(self) -> float:
        """
        Returns: the magenta component of the color
        """
        return self._color.magenta

    @magenta.setter
    def magenta(self, value: float):
        self._color.magenta = value

    @property
    def yellow(self) -> float:
        """
        Returns: the yellow component of the color
        """
        return self._color.yellow

    @yellow.setter
    def yellow(self, value: float):
        self._color.yellow = value

    @property
    def key(self) -> float:
        """
        Returns: the key component of the color
        """
        return self._color.key

    @key.setter
    def key(self, value: float):
        self._color.key = value


class ColorHSV(Color):
    """
    Create an HSV color by passing hue (0-360), saturation (0-1), value (0-1) and optionally, alpha (0-1)
    Convert another color object to HSV by passing it as a parameter.

    Raises:
        TypeError: hue must be an int, saturation, value, and alpha must be floats
        ValueError: hue must be between 0-360, saturation, value, and alpha must be between 0-1

    Examples:
        >>> ColorHSV(90, 0.2, 0.2)
        ColorHSV(90, 0.2, 0.2)

        >>> ColorHSV(240, 0.8, 0.9, 0.5)
        ColorHSV(240, 0.8, 0.9)

        >>> ColorHSV(other_color)
    """

    def __init__(self, *args):
        """
        Create an HSV color by passing hue (0-360), saturation (0-1), value (0-1) and optionally, alpha (0-1)
        Convert another color object to HSV by passing it as a parameter.

        Raises:
            TypeError: hue must be an int, saturation, value, and alpha must be floats
            ValueError: hue must be between 0-360, saturation, value, and alpha must be between 0-1

        Examples:
            >>> ColorHSV(90, 0.2, 0.2)
            ColorHSV(90, 0.2, 0.2)

            >>> ColorHSV(240, 0.8, 0.9, 0.5)
            ColorHSV(240, 0.8, 0.9)

            >>> ColorHSV(other_color)
        """
        self._color = _color.ColorHSV(*args)

    @property
    def hue(self) -> int:
        """
        Returns: the hue component of the color
        """
        return self._color.hue

    @hue.setter
    def hue(self, value: int):
        self._color.hue = value

    @property
    def saturation(self) -> float:
        """
        Returns: the saturation component of the color
        """
        return self._color.saturation

    @saturation.setter
    def saturation(self, value: float):
        self._color.saturation = value

    @property
    def value(self) -> float:
        """
        Returns: the value component of the color
        """
        return self._color.value

    @value.setter
    def value(self, value: float):
        self._color.value = value


class ColorHSL(Color):
    """
    Create an HSL color by passing hue (0-360), saturation (0-1), luminance (0-1) and optionally, alpha (0-1)
    Convert another color object to HSL by passing it as a parameter.

    Raises:
        TypeError: hue must be an int, saturation, luminance, and alpha must be floats
        ValueError: hue must be between 0-360, saturation, luminance, and alpha must be between 0-1

    Examples:
        >>> ColorHSL(90, 0.2, 0.2)
        ColorHSL(90, 0.2, 0.2)

        >>> ColorHSL(240, 0.8, 0.9, 0.5)
        ColorHSL(240, 0.8, 0.9)

        >>> ColorHSL(other_color)
    """

    def __init__(self, *args):
        """
        Create an HSL color by passing hue (0-360), saturation (0-1), luminance (0-1) and optionally, alpha (0-1)
        Convert another color object to HSL by passing it as a parameter.

        Raises:
            TypeError: hue must be an int, saturation, luminance, and alpha must be floats
            ValueError: hue must be between 0-360, saturation, luminance, and alpha must be between 0-1

        Examples:
            >>> ColorHSL(90, 0.2, 0.2)
            ColorHSL(90, 0.2, 0.2)

            >>> ColorHSL(240, 0.8, 0.9, 0.5)
            ColorHSL(240, 0.8, 0.9)

            >>> ColorHSL(other_color)
        """
        self._color = _color.ColorHSL(*args)

    @property
    def hue(self) -> int:
        """
        Returns: the hue component of the color
        """
        return self._color.hue

    @hue.setter
    def hue(self, value: int):
        self._color.hue = value

    @property
    def saturation(self) -> float:
        """
        Returns: the saturation component of the color
        """
        return self._color.saturation

    @saturation.setter
    def saturation(self, value: float):
        self._color.saturation = value

    @property
    def luminance(self) -> float:
        """
        Returns: the luminance component of the color
        """
        return self._color.luminance

    @luminance.setter
    def luminance(self, value: float):
        self._color.luminance = value


# RGB to other format

def rgb_to_hex(red: int, green: int, blue: int) -> str:
    """
    Converts a color from RGB to a Hexadecimal string

    Args:
        red: between 0 and 255
        green: between 0 and 255
        blue: between 0 and 255

    Returns:
        a hexstring in the format "#rrggbb"

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.rgb_to_hex(red, green, blue)


def rgb_to_cmyk(red: int, green: int, blue: int) -> tuple[float, float, float, float]:
    """
    Converts a color from RGB to CMYK

    Args:
        red: between 0 and 255
        green: between 0 and 255
        blue: between 0 and 255

    Returns:
        a tuple of CMYK values between 0 and 1

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.rgb_to_cmyk(red, green, blue)


def rgb_to_hsl(red: int, green: int, blue: int) -> tuple[int, float, float]:
    """
    Converts a color from RGB to HSL

    Args:
        red: between 0 and 255
        green: between 0 and 255
        blue: between 0 and 255

    Returns:
        a tuple of HSL values

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.rgb_to_hsl(red, green, blue)


def rgb_to_hsv(red: int, green: int, blue: int) -> tuple[int, float, float]:
    """
    Converts a color from RGB to HSV

    Args:
        red: between 0 and 255
        green: between 0 and 255
        blue: between 0 and 255

    Returns:
        a tuple of HSV values

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.rgb_to_hsv(red, green, blue)


# Hex to other format

def hex_to_rgb(hexstring: str) -> tuple[int, int, int]:
    """
    Converts a color hexstring to RGB

    Args:
        hexstring: a valid color hexadecimal string

    Returns:
        a tuple of RGB values between 0 and 255

    Raises:
        ValueError: if the hexstring is invalid
    """
    return _conversions.hex_to_rgb(hexstring)


def hex_to_cmyk(hexstring: str) -> tuple[float, float, float, float]:
    """
    Converts a color hexstring to CMYK

    Args:
        hexstring: a valid color hexadecimal string

    Returns:
        a tuple of CMYK values between 0 and 1

    Raises:
        ValueError: if the hexstring is invalid
    """
    return _conversions.hex_to_cmyk(hexstring)


def hex_to_hsv(hexstring: str) -> tuple[int, float, float]:
    """
    Converts a color hexstring to HSV

    Args:
        hexstring: a valid color hexadecimal string

    Returns:
        a tuple of HSV values

    Raises:
        ValueError: if the hexstring is invalid
    """
    return _conversions.hex_to_hsv(hexstring)


def hex_to_hsl(hexstring: str) -> tuple[int, float, float]:
    """
    Converts a color hexstring to HSL

    Args:
        hexstring: a valid color hexadecimal string

    Returns:
        a tuple of HSL values

    Raises:
        ValueError: if the hexstring is invalid
    """
    return _conversions.hex_to_hsl(hexstring)


# CMYK to other format

def cmyk_to_rgb(cyan: float, magenta: float, yellow: float, key: float) -> tuple[int, int, int]:
    """
    Converts a color from CMYK to RGB

    Args:
        cyan: between 0 and 1
        magenta: between 0 and 1
        yellow: between 0 and 1
        key: between 0 and 1

    Returns:
        a tuple of RGB values between 0 and 255

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.cmyk_to_rgb(cyan, magenta, yellow, key)


def cmyk_to_hex(cyan: float, magenta: float, yellow: float, key: float) -> str:
    """
    Converts a color from CMYK to a Hexadecimal String

    Args:
        cyan: between 0 and 1
        magenta: between 0 and 1
        yellow: between 0 and 1
        key: between 0 and 1

    Returns:
        a hexstring in the format "#rrggbb"

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.cmyk_to_hex(cyan, magenta, yellow, key)


def cmyk_to_hsv(cyan: float, magenta: float, yellow: float, key: float) -> tuple[int, float, float]:
    """
    Converts a color from CMYK to HSV

    Args:
        cyan: between 0 and 1
        magenta: between 0 and 1
        yellow: between 0 and 1
        key: between 0 and 1

    Returns:
        a tuple of HSV values

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.cmyk_to_hsv(cyan, magenta, yellow, key)


def cmyk_to_hsl(cyan: float, magenta: float, yellow: float, key: float) -> tuple[int, float, float]:
    """
    Converts a color from CMYK to HSL

    Args:
        cyan: between 0 and 1
        magenta: between 0 and 1
        yellow: between 0 and 1
        key: between 0 and 1

    Returns:
        a tuple of HSL values

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.cmyk_to_hsl(cyan, magenta, yellow, key)


# HSV to other format


def hsv_to_rgb(hue: int, saturation: float, value: float) -> tuple[int, int, int]:
    """
    Converts a color from HSV to RGB

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        value: between 0 and 1

    Returns:
        a tuple of RGB values between 0 and 255

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsv_to_rgb(hue, saturation, value)


def hsv_to_hex(hue: int, saturation: float, value: float) -> str:
    """
    Converts a color from HSV to a Hexadecimal string

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        value: between 0 and 1

    Returns:
        a hexstring in the format "#rrggbb"

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsv_to_hex(hue, saturation, value)


def hsv_to_cmyk(hue: int, saturation: float, value: float) -> tuple[float, float, float, float]:
    """
    Converts a color from HSV to CMYK

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        value: between 0 and 1

    Returns:
        a tuple of CMYK values between 0 and 1

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsv_to_cmyk(hue, saturation, value)


def hsv_to_hsl(hue: int, saturation: float, value: float) -> tuple[int, float, float]:
    """
    Converts a color from HSV to HSL

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        value: between 0 and 1

    Returns:
        a tuple of HSL values

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsv_to_hsl(hue, saturation, value)


# HSV to other format


def hsl_to_rgb(hue: int, saturation: float, luminance: float) -> tuple[int, int, int]:
    """
    Converts a color from HSL to RGB

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        luminance: between 0 and 1

    Returns:
        a tuple of RGB values between 0 and 255

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsl_to_rgb(hue, saturation, luminance)


def hsl_to_hex(hue: int, saturation: float, luminance: float) -> str:
    """
    Converts a color from HSL to a Hexadecimal string

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        luminance: between 0 and 1

    Returns:
        a hexstring in the format "#rrggbb"

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsl_to_hex(hue, saturation, luminance)


def hsl_to_cmyk(hue: int, saturation: float, luminance: float) -> tuple[float, float, float, float]:
    """
    Converts a color from HSL to CMYK

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        luminance: between 0 and 1

    Returns:
        a tuple of CMYK values between 0 and 1

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsl_to_cmyk(hue, saturation, luminance)


def hsl_to_hsv(hue: int, saturation: float, luminance: float) -> tuple[int, float, float]:
    """
    Converts a color from HSL to HSV

    Args:
        hue: between 0 and 360
        saturation: between 0 and 1
        luminance: between 0 and 1

    Returns:
        a tuple of HSV values

    Raises:
        ValueError: if the inputs are outside their bounds
    """
    return _conversions.hsl_to_hsv(hue, saturation, luminance)


# Random Colors

def random_rgb() -> ColorRGB:
    """
    Returns: a random RGB color
    """
    return ColorRGB(_randint(0, 255), _randint(0, 255), _randint(0, 255))


def random_hex() -> ColorHex:
    """
    Returns: a random Hexadecimal color
    """
    return ColorHex(rgb_to_hex(_randint(0, 255), _randint(0, 255), _randint(0, 255)))


def random_cmyk() -> ColorCMYK:
    """
    Returns: a random CMYK color
    """
    return ColorCMYK(_random(), _random(), _random(), _random())


def random_hsv() -> ColorHSV:
    """
    Returns: a random HSV color
    """
    return ColorHSV(_randint(0, 360), _random(), _random())


def random_hsl() -> ColorHSL:
    """
    Returns: a random HSL color
    """
    return ColorHSL(_randint(0, 360), _random(), _random())
