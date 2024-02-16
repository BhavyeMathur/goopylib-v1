import unittest
import goopylib.color as gp


class ColorClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.color = gp.Color(0, 10, 20)

    def test_repr(self):
        self.assertEqual(self.color.__repr__(), "Color(0, 10, 20, 1.00)")

    def test_add_int(self):
        self.assertEqual((self.color + 5).__repr__(), "Color(5, 15, 25, 1.00)")

    def test_add_color(self):
        self.assertEqual((self.color + gp.Color(5, 10, 20)).__repr__(), "Color(5, 20, 40, 1.00)")

    def test_sub_int(self):
        self.assertEqual((self.color - 5).__repr__(), "Color(0, 5, 15, 1.00)")

    def test_sub_color(self):
        self.assertEqual((self.color - gp.Color(5, 5, 15)).__repr__(), "Color(0, 5, 5, 1.00)")

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
        self.assertEqual("Color(0, 10, 20, 1.00)", self.color.__repr__())

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
        self.assertEqual(self.color.__repr__(), "ColorCMYK(0, 0.1, 0.2, 0.9)")

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
        self.assertEqual(self.color.__repr__(), "ColorHSV(0, 0.1, 0.2)")

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
        self.assertEqual(self.color.__repr__(), "ColorHSL(0, 0, 0)")

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
