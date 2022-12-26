from __future__ import annotations
import goopylib.ext.color_conversions as __conversions


class Color:
    def __init__(self, *args):
        self.__not_implemented(args)

    def __not_implemented(self, *args):
        raise NotImplementedError()

    def __repr__(self) -> str:
        return self.__not_implemented()

    def __add__(self, other: Union[int, Color]) -> Color:
        return self.__not_implemented()

    def __sub__(self, other: Union[int, Color]) -> Color:
        return self.__not_implemented()

    def __iadd__(self, other: Union[int, Color]):
        self.__not_implemented()

    def __isub__(self, other: Union[int, Color]):
        self.__not_implemented()

    @property
    def red(self) -> int:
        return self.__not_implemented()

    @red.setter
    def red(self, value: int):
        self.__not_implemented(value)

    @property
    def green(self) -> int:
        return self.__not_implemented()

    @green.setter
    def green(self, value: int):
        self.__not_implemented(value)

    @property
    def blue(self) -> int:
        return self.__not_implemented()

    @blue.setter
    def blue(self, value: int):
        self.__not_implemented(value)

    @property
    def alpha(self) -> float:
        return self.__not_implemented()

    @alpha.setter
    def alpha(self, value: float):
        self.__not_implemented(value)


class ColorRGB(Color):
    def __not_implemented(self):
        raise NotImplementedError()


class ColorHex(Color):
    def __not_implemented(self):
        raise NotImplementedError()


class ColorCMYK(Color):
    def __not_implemented(self, *args):
        raise NotImplementedError()

    @property
    def cyan(self) -> float:
        return self.__not_implemented()

    @cyan.setter
    def cyan(self, value: float):
        self.__not_implemented(value)

    @property
    def magenta(self) -> float:
        return self.__not_implemented()

    @magenta.setter
    def magenta(self, value: float):
        self.__not_implemented(value)

    @property
    def yellow(self) -> float:
        return self.__not_implemented()

    @yellow.setter
    def yellow(self, value: float):
        self.__not_implemented(value)

    @property
    def key(self) -> float:
        return self.__not_implemented()

    @key.setter
    def key(self, value: float):
        self.__not_implemented(value)


class ColorHSV(Color):
    def __not_implemented(self, *args):
        raise NotImplementedError()

    @property
    def hue(self) -> int:
        return self.__not_implemented()

    @hue.setter
    def hue(self, value: int):
        self.__not_implemented(value)

    @property
    def saturation(self) -> float:
        return self.__not_implemented()

    @saturation.setter
    def saturation(self, value: float):
        self.__not_implemented(value)

    @property
    def value(self) -> float:
        return self.__not_implemented()

    @value.setter
    def value(self, value: float):
        self.__not_implemented(value)


class ColorHSL(Color):
    def __not_implemented(self, *args):
        raise NotImplementedError()

    @property
    def hue(self) -> int:
        return self.__not_implemented()

    @hue.setter
    def hue(self, value: int):
        self.__not_implemented(value)

    @property
    def saturation(self) -> float:
        return self.__not_implemented()

    @saturation.setter
    def saturation(self, value: float):
        self.__not_implemented(value)

    @property
    def luminance(self) -> float:
        return self.__not_implemented()

    @luminance.setter
    def luminance(self, value: float):
        self.__not_implemented(value)


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
    return __conversions.rgb_to_hex(red, green, blue)


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
    return __conversions.rgb_to_cmyk(red, green, blue)


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
    return __conversions.rgb_to_hsl(red, green, blue)


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
    return __conversions.rgb_to_hsv(red, green, blue)


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
    return __conversions.hex_to_rgb(hexstring)


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
    return __conversions.hex_to_cmyk(hexstring)


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
    return __conversions.hex_to_hsv(hexstring)


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
    return __conversions.hex_to_hsl(hexstring)


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
    return __conversions.cmyk_to_rgb(cyan, magenta, yellow, key)


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
    return __conversions.cmyk_to_hex(cyan, magenta, yellow, key)


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
    return __conversions.cmyk_to_hsv(cyan, magenta, yellow, key)


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
    return __conversions.cmyk_to_hsl(cyan, magenta, yellow, key)


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
    return __conversions.hsv_to_rgb(hue, saturation, value)


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
    return __conversions.hsv_to_hex(hue, saturation, value)


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
    return __conversions.hsv_to_cmyk(hue, saturation, value)


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
    return __conversions.hsv_to_hsl(hue, saturation, value)


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
    return __conversions.hsl_to_rgb(hue, saturation, luminance)


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
    return __conversions.hsl_to_hex(hue, saturation, luminance)


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
    return __conversions.hsl_to_cmyk(hue, saturation, luminance)


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
    return __conversions.hsl_to_hsv(hue, saturation, luminance)


# Random Colors

def random_rgb() -> ColorRGB:
    raise NotImplementedError()


def random_hex() -> ColorHex:
    raise NotImplementedError()


def random_cmyk() -> ColorCMYK:
    raise NotImplementedError()


def random_hsv() -> ColorHSV:
    raise NotImplementedError()


def random_hsl() -> ColorHSL:
    raise NotImplementedError()
