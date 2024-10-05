import unittest
import goopylib as gp


class RandomColorMethods(unittest.TestCase):
    def test_random_rgb(self):
        self.assertIsInstance(gp.random_rgb(), gp.ColorRGB)
        self.assertNotEqual(gp.random_rgb(), gp.random_rgb())

    def test_random_hex(self):
        self.assertIsInstance(gp.random_hex(), gp.ColorHex)
        self.assertNotEqual(gp.random_hex(), gp.random_hex())

    def test_random_cmyk(self):
        self.assertIsInstance(gp.random_cmyk(), gp.ColorCMYK)
        self.assertNotEqual(gp.random_cmyk(), gp.random_cmyk())

    def test_random_hsv(self):
        self.assertIsInstance(gp.random_hsv(), gp.ColorHSV)
        self.assertNotEqual(gp.random_hsv(), gp.random_hsv())

    def test_random_hsl(self):
        self.assertIsInstance(gp.random_hsl(), gp.ColorHSL)
        self.assertNotEqual(gp.random_hsl(), gp.random_hsl())
