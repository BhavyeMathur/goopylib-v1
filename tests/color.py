import unittest

import color.color as gp


class ColorConversionMethods(unittest.TestCase):
    def test_rgb_to_hex(self):
        self.assertEqual(gp.rgb_to_hex(0, 0, 0), "#000000")
        self.assertEqual(gp.rgb_to_hex(255, 255, 255), "#ffffff")
        self.assertEqual(gp.rgb_to_hex(125, 125, 125), "#7d7d7d")

        self.assertEqual(gp.rgb_to_hex(255, 0, 0), "#ff0000")
        self.assertEqual(gp.rgb_to_hex(0, 255, 0), "#00ff00")
        self.assertEqual(gp.rgb_to_hex(0, 0, 255), "#0000ff")

        self.assertEqual(gp.rgb_to_hex(80, 0, 140), "#50008c")
        self.assertEqual(gp.rgb_to_hex(0, 50, 60), "#00323c")

    def test_rgb_to_cmyk(self):
        self.assertEqual(gp.rgb_to_cmyk(0, 0, 0), (0, 0, 0, 1))
        self.assertEqual(gp.rgb_to_cmyk(255, 255, 255), (0, 0, 0, 0))
        self.assertEqual(gp.rgb_to_cmyk(125, 125, 125), (0, 0, 0, 0.5098038911819458))

        self.assertEqual(gp.rgb_to_cmyk(255, 0, 0), (0, 1, 1, 0))
        self.assertEqual(gp.rgb_to_cmyk(0, 255, 0), (1, 0, 1, 0))
        self.assertEqual(gp.rgb_to_cmyk(0, 0, 255), (1, 1, 0, 0))

        self.assertEqual(gp.rgb_to_cmyk(80, 0, 140), (0.4285714328289032, 1.0, 0.0, 0.45098036527633667))
        self.assertEqual(gp.rgb_to_cmyk(0, 50, 60), (1.0, 0.1666666567325592, 0.0, 0.7647058963775635))

    def test_rgb_to_hsv(self):
        self.assertEqual(gp.rgb_to_hsv(0, 0, 0), (0, 0, 0))
        self.assertEqual(gp.rgb_to_hsv(255, 255, 255), (0, 0, 1))
        self.assertEqual(gp.rgb_to_hsv(125, 125, 125), (0, 0, 0.4901960790157318))

        self.assertEqual(gp.rgb_to_hsv(255, 0, 0), (0, 1, 1))
        self.assertEqual(gp.rgb_to_hsv(0, 255, 0), (120, 1, 1))
        self.assertEqual(gp.rgb_to_hsv(0, 0, 255), (240, 1, 1))

        self.assertEqual(gp.rgb_to_hsv(80, 0, 140), (274, 1, 0.5490196347236633))
        self.assertEqual(gp.rgb_to_hsv(0, 50, 60), (190, 1, 0.23529411852359772))

    def test_rgb_to_hsl(self):
        self.assertEqual(gp.rgb_to_hsl(0, 0, 0), (0, 0, 0))
        self.assertEqual(gp.rgb_to_hsl(255, 255, 255), (0, 0, 1))
        self.assertEqual(gp.rgb_to_hsl(125, 125, 125), (0, 0, 0.4901960790157318))

        self.assertEqual(gp.rgb_to_hsl(255, 0, 0), (0, 1, 0.5))
        self.assertEqual(gp.rgb_to_hsl(0, 255, 0), (120, 1, 0.5))
        self.assertEqual(gp.rgb_to_hsl(0, 0, 255), (240, 1, 0.5))

        self.assertEqual(gp.rgb_to_hsl(80, 0, 140), (274, 1, 0.27450981736183167))
        self.assertEqual(gp.rgb_to_hsl(0, 50, 60), (190, 1.0000001192092896, 0.11764705926179886))

    def test_hex_to_rgb(self):
        self.assertEqual(gp.hex_to_rgb("#000000"), (0, 0, 0))
        self.assertEqual(gp.hex_to_rgb("#ffffff"), (255, 255, 255))
        self.assertEqual(gp.hex_to_rgb("#7d7d7d"), (125, 125, 125))

        self.assertEqual(gp.hex_to_rgb("#ff0000"), (255, 0, 0))
        self.assertEqual(gp.hex_to_rgb("#00ff00"), (0, 255, 0))
        self.assertEqual(gp.hex_to_rgb("#0000ff"), (0, 0, 255))

        self.assertEqual(gp.hex_to_rgb("#50008c"), (80, 0, 140))
        self.assertEqual(gp.hex_to_rgb("#00323c"), (0, 50, 60))

    def test_cmyk_to_rgb(self):
        self.assertEqual(gp.cmyk_to_rgb(1, 1, 1, 1), (0, 0, 0))
        self.assertEqual(gp.cmyk_to_rgb(0, 0, 0, 0), (255, 255, 255))

        self.assertEqual(gp.cmyk_to_rgb(1, 0, 0, 0), (0, 255, 255))
        self.assertEqual(gp.cmyk_to_rgb(0, 1, 0, 0), (255, 0, 255))
        self.assertEqual(gp.cmyk_to_rgb(0, 0, 1, 0), (255, 255, 0))
        self.assertEqual(gp.cmyk_to_rgb(0, 0, 0, 1), (0, 0, 0))

        self.assertEqual(gp.cmyk_to_rgb(0.2, 0.3, 0.1, 0.5), (102, 89, 115))
        self.assertEqual(gp.cmyk_to_rgb(0.8, 0.5, 0, 0.1), (46, 115, 230))
        self.assertEqual(gp.cmyk_to_rgb(0.4, 0.6, 0.3, 0.7), (46, 31, 54))

    def test_hsv_to_rgb(self):
        self.assertEqual(gp.hsv_to_rgb(0, 0, 0), (0, 0, 0))
        self.assertEqual(gp.hsv_to_rgb(180, 1, 1), (0, 255, 255))

        self.assertEqual(gp.hsv_to_rgb(279, 0.43, 0.21), (45, 31, 54))
        self.assertEqual(gp.hsv_to_rgb(99, 0.19, 0.48), (107, 122, 99))
        self.assertEqual(gp.hsv_to_rgb(292, 0.75, 0.26), (60, 17, 66))

    def test_hsl_to_rgb(self):
        self.assertEqual(gp.hsv_to_rgb(0, 0, 0), (0, 0, 0))
        self.assertEqual(gp.hsv_to_rgb(180, 1, 1), (0, 255, 255))

        self.assertEqual(gp.hsl_to_rgb(191, 0.19, 0.49), (101, 140, 149))
        self.assertEqual(gp.hsl_to_rgb(29, 0.97, 0.63), (252, 158, 69))
        self.assertEqual(gp.hsl_to_rgb(260, 0.1, 0.8), (202, 199, 209))


class RandomColorMethods(unittest.TestCase):
    def test_random_rgb(self):
        self.assertIsInstance(gp.random_rgb(), gp.ColorRGB)

    def test_random_hex(self):
        self.assertIsInstance(gp.random_hex(), gp.ColorHex)

    def test_random_cmyk(self):
        self.assertIsInstance(gp.random_cmyk(), gp.ColorCMYK)

    def test_random_hsv(self):
        self.assertIsInstance(gp.random_hsv(), gp.ColorHSV)

    def test_random_hsl(self):
        self.assertIsInstance(gp.random_hsl(), gp.ColorHSL)


class ColorClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.Color(0, 10, 20)

    def test_repr(self):
        self.assertEqual("Color(0, 10, 20)", self.color.__repr__())

    def test_add_int(self):
        self.assertEqual("Color(5, 15, 25)", (self.color + 5).__repr__())

    def test_add_color(self):
        self.assertEqual("Color(5, 20, 40)", (self.color + gp.Color(5, 10, 20)).__repr__())

    def test_sub_int(self):
        self.assertEqual("Color(0, 5, 15)", (self.color - 5).__repr__())

    def test_sub_color(self):
        self.assertEqual("Color(0, 5, 5)", (self.color - gp.Color(5, 5, 15)).__repr__())

    def test_get_red(self):
        self.assertEqual(0, self.color.red)

    def test_get_green(self):
        self.assertEqual(10, self.color.green)

    def test_get_blue(self):
        self.assertEqual(20, self.color.blue)

    def test_get_alpha(self):
        self.assertEqual(1, self.color.alpha)

    def test_value_error(self):
        with self.assertRaises(ValueError):
            gp.Color(-5, 0, 0)

        with self.assertRaises(ValueError):
            gp.Color(0, -5, 0)

        with self.assertRaises(ValueError):
            gp.Color(0, 0, -5)

        with self.assertRaises(ValueError):
            gp.Color(265, 0, 0)

        with self.assertRaises(ValueError):
            gp.Color(0, 265, 0)

        with self.assertRaises(ValueError):
            gp.Color(0, 0, 265)

        with self.assertRaises(ValueError):
            gp.Color(0, 0, 0, -1)

        with self.assertRaises(ValueError):
            gp.Color(0, 0, 0, 2)


class ColorRGBClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.ColorRGB(0, 10, 20)

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual("Color(0, 10, 20)", self.color.__repr__())

    def test_get_red(self):
        self.assertEqual(0, self.color.red)

    def test_get_green(self):
        self.assertEqual(10, self.color.green)

    def test_get_blue(self):
        self.assertEqual(20, self.color.blue)

    def test_get_alpha(self):
        self.assertEqual(1, self.color.alpha)

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
        self.assertEqual("#001122", gp.ColorHex("012").__repr__())
        self.assertEqual("#001122", gp.ColorHex("#012").__repr__())
        self.assertEqual("#001122", gp.ColorHex("001122").__repr__())
        self.assertEqual("#001122", gp.ColorHex("#001122").__repr__())

    def test_subclass(self):
        self.assertIsInstance(self.color, gp.Color)

    def test_repr(self):
        self.assertEqual("#0011ff", self.color.__repr__())

    def test_get_red(self):
        self.assertEqual(0, self.color.red)

    def test_get_green(self):
        self.assertEqual(17, self.color.green)

    def test_get_blue(self):
        self.assertEqual(255, self.color.blue)

    def test_get_alpha(self):
        self.assertEqual(1, self.color.alpha)

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
        self.assertEqual("ColorCMYK(0, 0.1, 0.2, 0.9)", self.color.__repr__())

    def test_get_cyan(self):
        self.assertAlmostEqual(0, self.color.cyan)

    def test_get_magenta(self):
        self.assertAlmostEqual(0.1, self.color.magenta)

    def test_get_yellow(self):
        self.assertAlmostEqual(0.2, self.color.yellow)

    def test_get_key(self):
        self.assertAlmostEqual(0.9, self.color.key)

    def test_get_alpha(self):
        self.assertAlmostEqual(1, self.color.alpha)

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
        self.assertEqual("ColorHSV(0, 0.1, 0.2)", self.color.__repr__())

    def test_get_hue(self):
        self.assertEqual(0, self.color.hue)

    def test_get_saturation(self):
        self.assertAlmostEqual(0.1, self.color.saturation)

    def test_get_value(self):
        self.assertAlmostEqual(0.2, self.color.value)

    def test_get_alpha(self):
        self.assertAlmostEqual(1, self.color.alpha)

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
        self.assertEqual("ColorHSL(0, 0, 0)", self.color.__repr__())

    def test_get_hue(self):
        self.assertEqual(0, self.color.hue)

    def test_get_saturation(self):
        self.assertEqual(0, self.color.saturation)

    def test_get_luminance(self):
        self.assertEqual(0, self.color.luminance)

    def test_get_alpha(self):
        self.assertEqual(1, self.color.alpha)

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
