from __future__ import annotations


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
    raise NotImplementedError()


def rgb_to_cmyk(red: int, green: int, blue: int) -> tuple[float, float, float, float]:
    raise NotImplementedError()


def rgb_to_hsl(red: int, green: int, blue: int) -> tuple[int, float, float]:
    raise NotImplementedError()


def rgb_to_hsv(red: int, green: int, blue: int) -> tuple[int, float, float]:
    raise NotImplementedError()


# Hex to other format

def hex_to_rgb(hexstring: str) -> tuple[int, int, int]:
    raise NotImplementedError()


def hex_to_cmyk(hexstring: str) -> tuple[float, float, float, float]:
    raise NotImplementedError()


def hex_to_hsv(hexstring: str) -> tuple[int, float, float]:
    raise NotImplementedError()


def hex_to_hsl(hexstring: str) -> tuple[int, float, float]:
    raise NotImplementedError()


# CMYK to other format

def cmyk_to_rgb(cyan: float, magenta: float, yellow: float, key: float) -> tuple[int, int, int]:
    raise NotImplementedError()


def cmyk_to_hex(cyan: float, magenta: float, yellow: float, key: float) -> str:
    raise NotImplementedError()


def cmyk_to_hsv(cyan: float, magenta: float, yellow: float, key: float) -> tuple[int, float, float]:
    raise NotImplementedError()


def cmyk_to_hsl(cyan: float, magenta: float, yellow: float, key: float) -> tuple[int, float, float]:
    raise NotImplementedError()


# HSV to other format


def hsv_to_rgb(hue: int, saturation: float, value: float) -> tuple[int, int, int]:
    raise NotImplementedError()


def hsv_to_hex(hue: int, saturation: float, value: float) -> str:
    raise NotImplementedError()


def hsv_to_cmyk(hue: int, saturation: float, value: float) -> tuple[float, float, float, float]:
    raise NotImplementedError()


def hsv_to_hsl(hue: int, saturation: float, value: float) -> tuple[int, float, float]:
    raise NotImplementedError()


# HSV to other format


def hsl_to_rgb(hue: int, saturation: float, luminance: float) -> tuple[int, int, int]:
    raise NotImplementedError()


def hsl_to_hex(hue: int, saturation: float, luminance: float) -> str:
    raise NotImplementedError()


def hsl_to_cmyk(hue: int, saturation: float, luminance: float) -> tuple[float, float, float, float]:
    raise NotImplementedError()


def hsl_to_hsl(hue: int, saturation: float, luminance: float) -> tuple[int, float, float]:
    raise NotImplementedError()


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
