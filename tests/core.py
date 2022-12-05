import unittest
import goopylib as gp


class CoreMethods(unittest.TestCase):
    def test_terminate(self):
        self.assertIsNone(gp.terminate())

    def test_init(self):
        self.assertIsNone(gp.init())

    def test_compiled_version(self):
        self.assertIsInstance(gp.glfw_compiled_version(), str)

    def test_current_version(self):
        self.assertIsInstance(gp.glfw_current_version(), str)

    def test_get_refresh_rate(self):
        self.assertIsInstance(gp.get_refresh_rate(), int)

    def test_get_refresh_rate_error(self):
        gp.terminate()
        with self.assertRaises(RuntimeError):
            gp.get_refresh_rate()
        gp.init()

    def test_get_screen_width(self):
        self.assertIsInstance(gp.get_screen_width(), int)

    def test_get_screen_width_error(self):
        gp.terminate()
        with self.assertRaises(RuntimeError):
            gp.get_screen_width()
        gp.init()

    def test_get_screen_height(self):
        self.assertIsInstance(gp.get_screen_height(), int)

    def test_get_screen_height_error(self):
        gp.terminate()
        with self.assertRaises(RuntimeError):
            gp.get_screen_height()
        gp.init()

    def test_number_of_monitors(self):
        self.assertIsInstance(gp.number_of_monitors(), int)

    def test_number_of_monitors_error(self):
        gp.terminate()
        with self.assertRaises(RuntimeError):
            gp.number_of_monitors()
        gp.init()
