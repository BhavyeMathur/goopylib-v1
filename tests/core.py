import unittest
import goopylib as gp


class CoreMethods(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        gp.init()

    @classmethod
    def tearDownClass(cls):
        gp.terminate()

    def test_terminate(self):
        self.assertIsNone(gp.terminate())

    def test_init(self):
        self.assertIsNone(gp.init())

    def test_update(self):
        self.assertIsNone(gp.update())

    def test_compiled_version(self):
        self.assertIsInstance(gp.glfw_compiled_version(), str)

    def test_current_version(self):
        self.assertIsInstance(gp.glfw_current_version(), str)

    def test_get_refresh_rate(self):
        self.assertIsInstance(gp.get_refresh_rate(), int)

    def test_get_screen_width(self):
        self.assertIsInstance(gp.get_screen_width(), int)

    def test_get_screen_height(self):
        self.assertIsInstance(gp.get_screen_height(), int)

    def test_number_of_monitors(self):
        self.assertIsInstance(gp.number_of_monitors(), int)

    def test_set_buffer_swap_interval(self):
        self.assertIsNone(gp.set_buffer_swap_interval(0))

    def test_set_buffer_swap_interval_type_error(self):
        with self.assertRaises(TypeError):
            self.assertIsNone(gp.set_buffer_swap_interval(0.5))


class CoreMethodsUninitialized(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        gp.terminate()

    def test_get_refresh_rate(self):
        with self.assertRaises(RuntimeError):
            gp.get_refresh_rate()

    def test_get_screen_width_error(self):
        with self.assertRaises(RuntimeError):
            gp.get_screen_width()

    def test_get_screen_height_error(self):
        with self.assertRaises(RuntimeError):
            gp.get_screen_height()

    def test_number_of_monitors_error(self):
        with self.assertRaises(RuntimeError):
            gp.number_of_monitors()
