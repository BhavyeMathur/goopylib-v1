"""
Module defining functions to convert between color formats
"""

import goopylib.ext.color_conversions as _conversions


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
