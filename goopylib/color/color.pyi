"""
Module defining colors
"""

from __future__ import annotations

from typing import Union, Tuple


# The reason docstrings for the class are copied to the __init__() method is because CLion
# (and presumably other Jetbrains products) renders the 'Raises' section with an odd indentation otherwise.


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

    def __init__(self, *args) -> None:
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

    def __repr__(self) -> str:
        pass

    def __add__(self, other: Union[int, Color]) -> Color:
        """
        Adds an integer value to the RGB components of the color,
        or adds the RGB components of another color supplied.
        You can also use in-place addition.

        Examples:
            >>> Color(120, 50, 60) + 5  # increases the brightness by 5 points
            Color(125, 55, 65)

            >>> Color(15, 20, 30) + Color(60, 5, 30)
            Color(75, 25, 60)
        """

    def __sub__(self, other: Union[int, Color]) -> Color:
        """
        Subtracts an integer value from the RGB components of the color,
        or subtracts the RGB components of another color supplied.
        You can also use in-place subtraction.

        Examples:
            >>> Color(120, 50, 60) - 5  # decreases the brightness by 5 points
            Color(115, 45, 55)

            >>> Color(60, 80, 100) - Color(10, 20, 30)
            Color(50, 60, 70)
        """

    def __iadd__(self, other: Union[int, Color]) -> None:
        pass

    def __isub__(self, other: Union[int, Color]) -> None:
        pass

    @property
    def red(self) -> int:
        """
        Returns:
            the red component of the color
        """

    @red.setter
    def red(self, value: int) -> None:
        pass

    @property
    def green(self) -> int:
        """
        Returns:
            the green component of the color
        """

    @green.setter
    def green(self, value: int) -> None:
        pass

    @property
    def blue(self) -> int:
        """
        Returns:
            the blue component of the color
        """

    @blue.setter
    def blue(self, value: int) -> None:
        pass

    @property
    def alpha(self) -> float:
        """
        Returns:
            the alpha component of the color
        """

    @alpha.setter
    def alpha(self, value: float) -> None:
        pass

    @property
    def redf(self) -> float:
        """
        Returns:
            the red component of the color normalised between 0-1
        """

    @property
    def greenf(self) -> float:
        """
        Returns:
            the green component of the color normalised between 0-1
        """

    @property
    def bluef(self) -> float:
        """
        Returns:
            the blue component of the color normalised between 0-1
        """

    @property
    def rgbaf(self) -> Tuple[float, float, float, float]:
        """
        Returns:
            the RGBA components of the color normalised between 0-1
        """

    @property
    def rgbf(self) -> Tuple[float, float, float]:
        """
        Returns:
            the RGB components of the color normalised between 0-1
        """

    def to_rgb(self) -> ColorHex:
        """
        Returns: a ColorRGB representation of the color
        """

    def to_hex(self) -> ColorHex:
        """
        Returns: a ColorHex representation of the color
        """

    def to_cmyk(self) -> ColorCMYK:
        """
        Returns: a ColorCMYK representation of the color
        """

    def to_hsl(self) -> ColorHSL:
        """
        Returns: a ColorHSL representation of the color
        """

    def to_hsv(self) -> ColorHSV:
        """
        Returns: a ColorHSV representation of the color
        """


class ColorRGB(Color):
    """
    Create an RGB color by passing RGB arguments with an optional alpha parameter.

    Convert another color object to RGB by passing it as a parameter.

    Raises:
        TypeError: expected integers for RGB and floats for alpha
        ValueError: RGB must be between 0-255, alpha must be between 0-1

    Examples:
        >>> ColorRGB(120, 70, 0)
        ColorRGB(120, 70, 0)

        >>> ColorRGB(60, 180, 90, 0.5)
        Color(60, 180, 90)

        >>> ColorRGB(other_color)
    """

    def __init__(self, *args) -> None:
        """
        Create an RGB color by passing RGB arguments with an optional alpha parameter.

        Convert another color object to RGB by passing it as a parameter.

        Raises:
            TypeError: expected integers for RGB and floats for alpha
            ValueError: RGB must be between 0-255, alpha must be between 0-1

        Examples:
            >>> ColorRGB(120, 70, 0)
            ColorRGB(120, 70, 0)

            >>> ColorRGB(60, 180, 90, 0.5)
            Color(60, 180, 90)

            >>> ColorRGB(other_color)
        """


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

    def __init__(self, *args) -> None:
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

    def __repr__(self) -> str:
        """
        Returns:
            the hexadecimal string
        """


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

    def __init__(self, *args) -> None:
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

    @property
    def cyan(self) -> float:
        """
        Returns:
            the cyan component of the color
        """

    @cyan.setter
    def cyan(self, value: float) -> None:
        pass

    @property
    def magenta(self) -> float:
        """
        Returns:
            the magenta component of the color
        """

    @magenta.setter
    def magenta(self, value: float) -> None:
        pass

    @property
    def yellow(self) -> float:
        """
        Returns:
            the yellow component of the color
        """

    @yellow.setter
    def yellow(self, value: float) -> None:
        pass

    @property
    def key(self) -> float:
        """
        Returns:
            the key component of the color
        """

    @key.setter
    def key(self, value: float) -> None:
        pass


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

    def __init__(self, *args) -> None:
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

    @property
    def hue(self) -> int:
        """
        Returns:
            the hue component of the color
        """

    @hue.setter
    def hue(self, value: int) -> None:
        pass

    @property
    def saturation(self) -> float:
        """
        Returns:
            the saturation component of the color
        """

    @saturation.setter
    def saturation(self, value: float) -> None:
        pass

    @property
    def value(self) -> float:
        """
        Returns:
            the value component of the color
        """

    @value.setter
    def value(self, value: float) -> None:
        pass


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

    def __init__(self, *args) -> None:
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

    @property
    def hue(self) -> int:
        """
        Returns:
            the hue component of the color
        """

    @hue.setter
    def hue(self, value: int) -> None:
        pass

    @property
    def saturation(self) -> float:
        """
        Returns:
            the saturation component of the color
        """

    @saturation.setter
    def saturation(self, value: float) -> None:
        pass

    @property
    def luminance(self) -> float:
        """
        Returns:
            the luminance component of the color
        """

    @luminance.setter
    def luminance(self, value: float) -> None:
        pass
