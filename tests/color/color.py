import unittest
import goopylib.color as gp


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
