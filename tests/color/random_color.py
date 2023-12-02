import unittest
import goopylib.color.random as gp


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
