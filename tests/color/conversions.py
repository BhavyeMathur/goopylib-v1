import unittest
import goopylib.color.conversions as gp


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
        self.assertEqual(gp.hsl_to_rgb(0, 0, 0), (0, 0, 0))
        self.assertEqual(gp.hsl_to_rgb(180, 1, 1), (255, 255, 255))

        self.assertEqual(gp.hsl_to_rgb(191, 0.19, 0.49), (101, 140, 149))
        self.assertEqual(gp.hsl_to_rgb(29, 0.97, 0.63), (252, 158, 69))
        self.assertEqual(gp.hsl_to_rgb(260, 0.1, 0.8), (202, 199, 209))
