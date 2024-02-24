import unittest

import goopylib.color as gp


class ColorClass(unittest.TestCase):
    def test_color_from_rgb(self):
        color_rgb = gp.ColorRGB(10, 15, 20, 0.1)
        color = gp.Color(color_rgb)

        self.assertEqual(color.__repr__(), "Color(10, 15, 20, alpha=0.10)")
        self.assertEqual(color.rgbaf, color_rgb.rgbaf)

    def test_color_from_hex(self):
        color_hex = gp.ColorHex("#f05", 0.2)
        color = gp.Color(color_hex)
        self.assertEqual(color.rgbaf, color_hex.rgbaf)

    def test_color_from_cmyk(self):
        color_cmyk = gp.ColorCMYK(0.5, 0.6, 0.7, 0.3)
        color = gp.Color(color_cmyk)
        self.assertEqual(color.rgbaf, color_cmyk.rgbaf)

    def test_color_from_hsl(self):
        color_hsl = gp.ColorHSL(10, 0.2, 0.3, 0.4)
        color = gp.Color(color_hsl)
        self.assertEqual(color.rgbaf, color_hsl.rgbaf)

    def test_color_from_hsv(self):
        color_hsv = gp.ColorHSV(20, 0.3, 0.4, 0.5)
        color = gp.Color(color_hsv)
        self.assertEqual(color.rgbaf, color_hsv.rgbaf)

    def test_color_from_rgba(self):
        color = gp.Color(0, 10, 20)

        self.assertEqual(color.red, 0)
        self.assertEqual(color.green, 10)
        self.assertEqual(color.blue, 20)
        self.assertEqual(color.alpha, 1)

        color = gp.Color(0, 10, 20, 0.5)
        self.assertEqual(color.alpha, 0.5)

    def test_color_from_rgba_error(self):
        with self.assertRaises(ValueError):
            color = gp.Color(300, 0, 0)
        with self.assertRaises(ValueError):
            color = gp.Color(0, 300, 0)
        with self.assertRaises(ValueError):
            color = gp.Color(0, 0, 300)

        with self.assertRaises(ValueError):
            color = gp.Color(-30, 0, 0)
        with self.assertRaises(ValueError):
            color = gp.Color(0, -30, 0)
        with self.assertRaises(ValueError):
            color = gp.Color(0, 0, -30)

        with self.assertRaises(ValueError):
            color = gp.Color(0, 0, 0, 2)
        with self.assertRaises(ValueError):
            color = gp.Color(0, 0, 0, -0.5)

    def test_color_from_hexstring(self):
        color = gp.Color("#f01")
        self.assertEqual(color.red, 255)
        self.assertEqual(color.green, 0)
        self.assertEqual(color.blue, 17)
        self.assertEqual(color.alpha, 1)

        color = gp.Color("f01")
        self.assertEqual(color.red, 255)
        self.assertEqual(color.green, 0)
        self.assertEqual(color.blue, 17)
        self.assertEqual(color.alpha, 1)

        color = gp.Color("#f01001")
        self.assertEqual(color.red, 240)
        self.assertEqual(color.green, 16)
        self.assertEqual(color.blue, 1)
        self.assertEqual(color.alpha, 1)

        color = gp.Color("f01001")
        self.assertEqual(color.red, 240)
        self.assertEqual(color.green, 16)
        self.assertEqual(color.blue, 1)
        self.assertEqual(color.alpha, 1)

        color = gp.Color("#f01", 0.5)
        self.assertEqual(color.red, 255)
        self.assertEqual(color.green, 0)
        self.assertEqual(color.blue, 17)
        self.assertEqual(color.alpha, 0.5)

    def test_color_from_hexstring_errors(self):
        with self.assertRaises(ValueError):
            color = gp.Color("#0000")
        with self.assertRaises(ValueError):
            color = gp.Color("0000")
        with self.assertRaises(ValueError):
            color = gp.Color("#00000")
        with self.assertRaises(ValueError):
            color = gp.Color("#0000000")
        with self.assertRaises(ValueError):
            color = gp.Color("0000000")
        with self.assertRaises(ValueError):
            color = gp.Color("#g00")
        with self.assertRaises(ValueError):
            color = gp.Color("gf0011")

        with self.assertRaises(ValueError):
            color = gp.Color("#000", 2)
        with self.assertRaises(ValueError):
            color = gp.Color("#000", -0.5)

    def test_color_repr(self):
        color = gp.Color(0, 10, 20)
        self.assertEqual(str(color), "Color(0, 10, 20)")

        color = gp.Color(0, 10, 20, 0.5)
        self.assertEqual(color.__repr__(), "Color(0, 10, 20, alpha=0.50)")

    def test_color_properties(self):
        color = gp.Color(0, 0, 0)

        color.red = 153
        self.assertEqual(color.red, 153)
        self.assertAlmostEqual(color.redf, 0.6)

        color.green = 102
        self.assertEqual(color.green, 102)
        self.assertAlmostEqual(color.greenf, 0.4)

        color.blue = 51
        self.assertEqual(color.blue, 51)
        self.assertAlmostEqual(color.bluef, 0.2)

        color.alpha = 0.5
        self.assertEqual(color.alpha, 0.5)

        self.assertEqual(tuple(map(lambda n: round(n, 2), color.rgbaf)), (0.6, 0.4, 0.2, 0.5))
        self.assertEqual(tuple(map(lambda n: round(n, 2), color.rgbf)), (0.6, 0.4, 0.2))
        self.assertEqual(f"{color}", "Color(153, 102, 51, alpha=0.50)")

    def test_color_property_errors(self):
        color = gp.Color(0, 0, 0)

        with self.assertRaises(ValueError):
            color.red = 300
        with self.assertRaises(ValueError):
            color.red = -30

        with self.assertRaises(ValueError):
            color.green = 300
        with self.assertRaises(ValueError):
            color.green = -30

        with self.assertRaises(ValueError):
            color.blue = 300
        with self.assertRaises(ValueError):
            color.blue = -30

        with self.assertRaises(ValueError):
            color.alpha = 2
        with self.assertRaises(ValueError):
            color.alpha = -0.5

    def test_color_arithmetic(self):
        color1 = gp.Color(100, 100, 100)
        color2 = gp.Color(5, 10, 15)

        self.assertEqual((color1 + 50).__repr__(), "Color(150, 150, 150)")
        self.assertEqual((color1 - 50).__repr__(), "Color(50, 50, 50)")

        self.assertEqual((color1 + color2).__repr__(), "Color(105, 110, 115)")
        self.assertEqual((color1 - color2).__repr__(), "Color(95, 90, 85)")

        color1 += 50
        self.assertEqual(color1.__repr__(), "Color(150, 150, 150)")

        color1 -= 70
        self.assertEqual(color1.__repr__(), "Color(80, 80, 80)")

        color1 += color2
        self.assertEqual(color1.__repr__(), "Color(85, 90, 95)")

        color1 -= color2
        self.assertEqual(color1.__repr__(), "Color(80, 80, 80)")

    def test_color_arithmetic_alpha(self):
        color1 = gp.Color(100, 100, 100, 0.5)
        color2 = gp.Color(5, 10, 15, 0.2)

        self.assertEqual((color1 + 50).__repr__(), "Color(150, 150, 150, alpha=0.50)")
        self.assertEqual((color1 - 50).__repr__(), "Color(50, 50, 50, alpha=0.50)")

        self.assertEqual((color1 + color2).__repr__(), "Color(105, 110, 115, alpha=0.50)")
        self.assertEqual((color1 - color2).__repr__(), "Color(95, 90, 85, alpha=0.50)")

        color1 += 50
        self.assertEqual(color1.__repr__(), "Color(150, 150, 150, alpha=0.50)")

        color1 -= 70
        self.assertEqual(color1.__repr__(), "Color(80, 80, 80, alpha=0.50)")

        color1 += color2
        self.assertEqual(color1.__repr__(), "Color(85, 90, 95, alpha=0.50)")

        color1 -= color2
        self.assertEqual(color1.__repr__(), "Color(80, 80, 80, alpha=0.50)")

    def test_color_arithmetic_overflow(self):
        color1 = gp.Color(250, 250, 250)
        color2 = gp.Color(5, 10, 15)

        self.assertEqual((color1 + 50).__repr__(), "Color(255, 255, 255)")
        self.assertEqual((color1 + color2).__repr__(), "Color(255, 255, 255)")

        color1 += 50
        self.assertEqual(color1.__repr__(), "Color(255, 255, 255)")
        self.assertEqual(color1.rgbaf, (1, 1, 1, 1))

    def test_color_arithmetic_underflow(self):
        color1 = gp.Color(5, 5, 5)
        color2 = gp.Color(5, 10, 15)

        self.assertEqual((color1 - 50).__repr__(), "Color(0, 0, 0)")
        self.assertEqual((color1 - color2).__repr__(), "Color(0, 0, 0)")

        color1 -= 50
        self.assertEqual(color1.__repr__(), "Color(0, 0, 0)")
        self.assertEqual(color1.rgbaf, (0, 0, 0, 1))


class ColorRGBClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.ColorRGB(0, 10, 20)

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual("Color(0, 10, 20)", self.color.__repr__())

    def test_get_red(self):
        self.assertEqual(self.color.red, 0)

    def test_get_green(self):
        self.assertEqual(self.color.green, 10)

    def test_get_blue(self):
        self.assertEqual(self.color.blue, 20)

    def test_get_alpha(self):
        self.assertEqual(self.color.alpha, 1)

    def test_value_error(self):
        with self.assertRaises(ValueError):
            gp.ColorRGB(-5, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorRGB(0, -5, 0)

        with self.assertRaises(ValueError):
            gp.ColorRGB(0, 0, -5)

        with self.assertRaises(ValueError):
            gp.ColorRGB(265, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorRGB(0, 265, 0)

        with self.assertRaises(ValueError):
            gp.ColorRGB(0, 0, 265)

        with self.assertRaises(ValueError):
            gp.ColorRGB(0, 0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorRGB(0, 0, 0, 2)


class ColorHexClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.ColorHex("#01f")

    def test_init(self):
        self.assertEqual(gp.ColorHex("012").__repr__(), "#001122")
        self.assertEqual(gp.ColorHex("#012").__repr__(), "#001122")
        self.assertEqual(gp.ColorHex("001122").__repr__(), "#001122")
        self.assertEqual(gp.ColorHex("#001122").__repr__(), "#001122")

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual(self.color.__repr__(), "#0011ff")

    def test_get_red(self):
        self.assertEqual(self.color.red, 0)

    def test_get_green(self):
        self.assertEqual(self.color.green, 17)

    def test_get_blue(self):
        self.assertEqual(self.color.blue, 255)

    def test_get_alpha(self):
        self.assertEqual(self.color.alpha, 1)

    def test_value_error(self):
        with self.assertRaises(ValueError):
            gp.ColorHex("#0000")

        with self.assertRaises(ValueError):
            gp.ColorHex("#g00")

        with self.assertRaises(ValueError):
            gp.ColorHex("#000", -1)

        with self.assertRaises(ValueError):
            gp.ColorHex("#000", 2)


class ColorCMYKClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.ColorCMYK(0, 0.1, 0.2, 0.9)

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual(self.color.__repr__(), "ColorCMYK(0.00, 0.10, 0.20, 0.90)")

    def test_get_cyan(self):
        self.assertAlmostEqual(self.color.cyan, 0)

    def test_get_magenta(self):
        self.assertAlmostEqual(self.color.magenta, 0.1)

    def test_get_yellow(self):
        self.assertAlmostEqual(self.color.yellow, 0.2)

    def test_get_key(self):
        self.assertAlmostEqual(self.color.key, 0.9)

    def test_get_alpha(self):
        self.assertAlmostEqual(self.color.alpha, 1)

    def test_value_error(self):
        with self.assertRaises(ValueError):
            gp.ColorCMYK(-1, 0, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, -1, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 0, -1, 0)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(2, 0, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 2, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 0, 2, 0)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 0, 0, 2)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 0, 0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorCMYK(0, 0, 0, 0, 2)


class ColorHSVClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.ColorHSV(0, 0.1, 0.2)

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual(self.color.__repr__(), "ColorHSV(0, 0.10, 0.20)")

    def test_get_hue(self):
        self.assertEqual(self.color.hue, 0)

    def test_get_saturation(self):
        self.assertAlmostEqual(self.color.saturation, 0.1)

    def test_get_value(self):
        self.assertAlmostEqual(self.color.value, 0.2)

    def test_get_alpha(self):
        self.assertAlmostEqual(self.color.alpha, 1)

    def test_value_error(self):
        with self.assertRaises(ValueError):
            gp.ColorHSV(-5, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSV(0, -1, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSV(0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorHSV(370, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSV(0, 2, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSV(0, 0, 2)

        with self.assertRaises(ValueError):
            gp.ColorHSV(0, 0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorHSV(0, 0, 0, 2)


class ColorHSLClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.ColorHSL(0, 0, 0)

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual(self.color.__repr__(), "ColorHSL(0, 0.00, 0.00)")

    def test_get_hue(self):
        self.assertEqual(self.color.hue, 0)

    def test_get_saturation(self):
        self.assertEqual(self.color.saturation, 0)

    def test_get_luminance(self):
        self.assertEqual(self.color.luminance, 0)

    def test_get_alpha(self):
        self.assertEqual(self.color.alpha, 1)

    def test_value_error(self):
        with self.assertRaises(ValueError):
            gp.ColorHSL(-5, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSL(0, -1, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSL(0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorHSL(370, 0, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSL(0, 2, 0)

        with self.assertRaises(ValueError):
            gp.ColorHSL(0, 0, 2)

        with self.assertRaises(ValueError):
            gp.ColorHSL(0, 0, 0, -1)

        with self.assertRaises(ValueError):
            gp.ColorHSL(0, 0, 0, 2)


# TODO tests for HSL -> HSV and HSV -> HSL conversions
class ColorConversionMethods(unittest.TestCase):
    def assertColorEqual(self, actual: gp.Color, expected):
        if isinstance(expected, tuple):
            self.assertEqual(str(actual), str(actual.__class__(*expected)))
        else:
            self.assertEqual(str(actual), str(actual.__class__(expected)))

    def test_rgb_to_hex(self):
        self.assertColorEqual(gp.ColorRGB(0, 0, 0).to_hex(), "#000000")
        self.assertColorEqual(gp.ColorRGB(255, 255, 255).to_hex(), "#ffffff")
        self.assertColorEqual(gp.ColorRGB(125, 125, 125).to_hex(), "#7d7d7d")

        self.assertColorEqual(gp.ColorRGB(255, 0, 0).to_hex(), "#ff0000")
        self.assertColorEqual(gp.ColorRGB(0, 255, 0).to_hex(), "#00ff00")
        self.assertColorEqual(gp.ColorRGB(0, 0, 255).to_hex(), "#0000ff")

        self.assertColorEqual(gp.ColorRGB(80, 0, 140).to_hex(), "#50008c")
        self.assertColorEqual(gp.ColorRGB(0, 50, 60).to_hex(), "#00323c")

    def test_rgb_to_cmyk(self):
        self.assertColorEqual(gp.ColorRGB(0, 0, 0).to_cmyk(), (0, 0, 0, 1))
        self.assertColorEqual(gp.ColorRGB(255, 255, 255).to_cmyk(), (0, 0, 0, 0))
        self.assertColorEqual(gp.ColorRGB(125, 125, 125).to_cmyk(), (0, 0, 0, 0.51))

        self.assertColorEqual(gp.ColorRGB(255, 0, 0).to_cmyk(), (0, 1, 1, 0))
        self.assertColorEqual(gp.ColorRGB(0, 255, 0).to_cmyk(), (1, 0, 1, 0))
        self.assertColorEqual(gp.ColorRGB(0, 0, 255).to_cmyk(), (1, 1, 0, 0))

        self.assertColorEqual(gp.ColorRGB(80, 0, 140).to_cmyk(), (0.43, 1.0, 0.0, 0.45))
        self.assertColorEqual(gp.ColorRGB(0, 50, 60).to_cmyk(), (1.0, 0.17, 0.0, 0.76))

    def test_rgb_to_hsv(self):
        self.assertColorEqual(gp.ColorRGB(0, 0, 0).to_hsv(), (0, 0, 0))
        self.assertColorEqual(gp.ColorRGB(255, 255, 255).to_hsv(), (0, 0, 1))
        self.assertColorEqual(gp.ColorRGB(125, 125, 125).to_hsv(), (0, 0, 0.49))

        self.assertColorEqual(gp.ColorRGB(255, 0, 0).to_hsv(), (0, 1, 1))
        self.assertColorEqual(gp.ColorRGB(0, 255, 0).to_hsv(), (120, 1, 1))
        self.assertColorEqual(gp.ColorRGB(0, 0, 255).to_hsv(), (240, 1, 1))

        self.assertColorEqual(gp.ColorRGB(80, 0, 140).to_hsv(), (274, 1, 0.55))
        self.assertColorEqual(gp.ColorRGB(0, 50, 60).to_hsv(), (190, 1, 0.24))

    def test_rgb_to_hsl(self):
        self.assertColorEqual(gp.ColorRGB(0, 0, 0).to_hsl(), (0, 0, 0))
        self.assertColorEqual(gp.ColorRGB(255, 255, 255).to_hsl(), (0, 0, 1))
        self.assertColorEqual(gp.ColorRGB(125, 125, 125).to_hsl(), (0, 0, 0.49))

        self.assertColorEqual(gp.ColorRGB(255, 0, 0).to_hsl(), (0, 1, 0.5))
        self.assertColorEqual(gp.ColorRGB(0, 255, 0).to_hsl(), (120, 1, 0.5))
        self.assertColorEqual(gp.ColorRGB(0, 0, 255).to_hsl(), (240, 1, 0.5))

        self.assertColorEqual(gp.ColorRGB(80, 0, 140).to_hsl(), (274, 1, 0.27))
        self.assertColorEqual(gp.ColorRGB(0, 50, 60).to_hsl(), (190, 1, 0.12))

    def test_hex_to_rgb(self):
        self.assertColorEqual(gp.ColorHex("#000000").to_rgb(), (0, 0, 0))
        self.assertColorEqual(gp.ColorHex("#ffffff").to_rgb(), (255, 255, 255))
        self.assertColorEqual(gp.ColorHex("#7d7d7d").to_rgb(), (125, 125, 125))

        self.assertColorEqual(gp.ColorHex("#ff0000").to_rgb(), (255, 0, 0))
        self.assertColorEqual(gp.ColorHex("#00ff00").to_rgb(), (0, 255, 0))
        self.assertColorEqual(gp.ColorHex("#0000ff").to_rgb(), (0, 0, 255))

        self.assertColorEqual(gp.ColorHex("#50008c").to_rgb(), (80, 0, 140))
        self.assertColorEqual(gp.ColorHex("#00323c").to_rgb(), (0, 50, 60))

    def test_cmyk_to_rgb(self):
        self.assertColorEqual(gp.ColorCMYK(1, 1, 1, 1).to_rgb(), (0, 0, 0))
        self.assertColorEqual(gp.ColorCMYK(0, 0, 0, 0).to_rgb(), (255, 255, 255))

        self.assertColorEqual(gp.ColorCMYK(1, 0, 0, 0).to_rgb(), (0, 255, 255))
        self.assertColorEqual(gp.ColorCMYK(0, 1, 0, 0).to_rgb(), (255, 0, 255))
        self.assertColorEqual(gp.ColorCMYK(0, 0, 1, 0).to_rgb(), (255, 255, 0))
        self.assertColorEqual(gp.ColorCMYK(0, 0, 0, 1).to_rgb(), (0, 0, 0))

        self.assertColorEqual(gp.ColorCMYK(0.2, 0.3, 0.1, 0.5).to_rgb(), (102, 89, 115))
        self.assertColorEqual(gp.ColorCMYK(0.8, 0.5, 0, 0.1).to_rgb(), (46, 115, 230))
        self.assertColorEqual(gp.ColorCMYK(0.4, 0.6, 0.3, 0.7).to_rgb(), (46, 31, 54))

    def test_hsl_to_rgb(self):
        self.assertColorEqual(gp.ColorHSL(0, 0, 0).to_rgb(), (0, 0, 0))
        self.assertColorEqual(gp.ColorHSL(180, 1, 1).to_rgb(), (255, 255, 255))

        self.assertColorEqual(gp.ColorHSL(191, 0.19, 0.49).to_rgb(), (101, 140, 149))
        self.assertColorEqual(gp.ColorHSL(29, 0.97, 0.63).to_rgb(), (252, 158, 69))
        self.assertColorEqual(gp.ColorHSL(260, 0.1, 0.8).to_rgb(), (202, 199, 209))

    def test_hsv_to_rgb(self):
        self.assertColorEqual(gp.ColorHSV(0, 0, 0).to_rgb(), (0, 0, 0))
        self.assertColorEqual(gp.ColorHSV(180, 1, 1).to_rgb(), (0, 255, 255))

        self.assertColorEqual(gp.ColorHSV(279, 0.43, 0.21).to_rgb(), (45, 31, 54))
        self.assertColorEqual(gp.ColorHSV(99, 0.19, 0.48).to_rgb(), (107, 122, 99))
        self.assertColorEqual(gp.ColorHSV(292, 0.75, 0.26).to_rgb(), (60, 17, 66))
