import unittest
import goopylib as gp
import math
import time


# noinspection PyTypeChecker, PyUnusedLocal
class WindowMethods(unittest.TestCase):
    window = None
    initial_width = 500
    initial_height = 400
    initial_title = "New Window!"

    @classmethod
    def setUpClass(cls):
        gp.init()
        cls.window = gp.Window(cls.initial_width, cls.initial_height, cls.initial_title)

    @classmethod
    def tearDownClass(cls):
        cls.window.destroy()
        gp.terminate()

    # Constructor Tests ------------------------------------------------------------------------------------------------

    def test_constructor(self):
        window = gp.Window(height=500, title="Test Window", width=700)
        self.assertEqual(window.width, 700)
        self.assertEqual(window.height, 500)
        self.assertEqual(window.title, "Test Window")

        window.destroy()

    def test_constructor_type_errors1(self):
        with self.assertRaises(TypeError):
            gp.Window(height=500.5, title="Test Window", width=700)
        with self.assertRaises(TypeError):
            gp.Window(height=500, title="Test Window", width=700.0)
        with self.assertRaises(TypeError):
            gp.Window(height=500, title=0, width=700)

    def test_constructor_type_errors2(self):
        with self.assertRaises(TypeError):
            # noinspection PyArgumentList
            gp.Window(500)

    def test_constructor_value_errors(self):
        with self.assertRaises(ValueError):
            gp.Window(height=-500, title="Test Window", width=700)
        with self.assertRaises(ValueError):
            gp.Window(height=500, title="Test Window", width=0)

    """Core Window Methods ------------------------------------------------------------------------------------------"""

    def test_repr(self):
        window = gp.Window(500, 400, "Test Window")
        self.assertEqual(window.__repr__(), f"Window(width=500, height=400, title='Test Window')")

    # Window States ----------------------------------------------------------------------------------------------------

    def test_update(self):
        self.assertIsNone(self.window.update())

    def test_set_focus(self):
        self.window.minimize()
        self.assertFalse(self.window.has_focus())
        self.assertIsNone(self.window.set_focus())
        self.assertTrue(self.window.has_focus())

    def test_is_open(self):
        self.assertTrue(self.window.is_open())

    def test_is_closed(self):
        self.assertFalse(self.window.is_closed())

    def test_make_windowed(self):
        self.window.unfullscreen()
        self.assertFalse(self.window.is_fullscreen())

    def test_make_fullscreen(self):
        self.window.fullscreen()
        self.assertTrue(self.window.is_fullscreen())

    def test_minimize(self):
        self.assertFalse(self.window.is_minimized())
        self.window.minimize()
        self.assertTrue(self.window.is_minimized())

    def test_show(self):
        self.window.show()
        self.assertTrue(self.window.is_visible())
        self.assertFalse(self.window.is_hidden())

    def test_hide(self):
        self.window.hide()
        self.assertFalse(self.window.is_visible())
        self.assertTrue(self.window.is_hidden())

    def test_maximize(self):
        self.window.restore()
        self.assertFalse(self.window.is_maximized())
        self.window.maximize()
        self.assertTrue(self.window.is_maximized())

    def test_restore(self):
        self.window.restore()
        self.assertFalse(self.window.is_minimized())
        self.assertFalse(self.window.is_maximized())
        self.assertFalse(self.window.is_fullscreen())

    # def test_transparent_frame_buffer(self):
    #     self.assertFalse(self.window.has_transparent_framebuffer())

    def test_mouse_hovering(self):
        self.assertIsInstance(self.window.is_mouse_hovering(), bool)

    # GLFW Window Parameters

    def test_get_frame_size(self):
        value = self.window.get_frame_size()
        self.assertIsInstance(value, tuple)
        self.assertEqual(len(value), 4)
        for val in value:
            self.assertIsInstance(val, int)

    def test_get_content_scale(self):
        value = self.window.get_content_scale()
        self.assertIsInstance(value, tuple)
        self.assertEqual(len(value), 2)
        for val in value:
            self.assertIsInstance(val, float)

    # Aspect Ratio Functions

    def test_get_aspect_ratio(self):
        gcd = math.gcd(self.initial_width, self.initial_height)
        window = gp.Window(self.initial_width, self.initial_height)

        self.assertEqual(window.get_aspect_ratio(), (self.initial_width // gcd, self.initial_height // gcd))

        window.destroy()

    def test_set_aspect_ratio1(self):
        self.window.set_aspect_ratio(13, 7)

    def test_set_aspect_ratio2(self):
        self.window.set_aspect_ratio(None, None)

    def test_aspect_ratio_keywords(self):
        self.window.set_aspect_ratio(denominator=13, numerator=7)

    def test_set_aspect_ratio_value_error(self):
        initial_value = self.window.get_aspect_ratio()

        with self.assertRaises(ValueError):
            self.window.set_aspect_ratio(13, -7)
        with self.assertRaises(ValueError):
            self.window.set_aspect_ratio(-13, 7)

        self.assertEqual(self.window.get_aspect_ratio(), initial_value)

    """Callbacks ----------------------------------------------------------------------------------------------------"""

    def test_resize_callback(self):

        callback_executed = False

        def callback(width, height):
            nonlocal callback_executed
            callback_executed = True

        self.window.resize_callback = callback
        self.assertEqual(self.window.resize_callback, callback)

        self.window.height = 100
        self.assertTrue(callback_executed)

    def test_remove_resize_callback(self):
        self.window.resize_callback = None
        self.assertEqual(self.window.resize_callback, None)

    def test_resize_callback_type_error(self):
        initial_value = self.window.resize_callback

        with self.assertRaises(TypeError):
            self.window.resize_callback = "string"

        self.assertEqual(self.window.resize_callback, initial_value)

    def test_resize_callback_value_errors(self):
        initial_value = self.window.resize_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.resize_callback = callback

        with self.assertRaises(ValueError):
            def callback(width):
                pass

            self.window.resize_callback = callback

        with self.assertRaises(ValueError):
            def callback(width, height, arg):
                pass

            self.window.resize_callback = callback

        self.assertEqual(self.window.resize_callback, initial_value)

    # Position Callback

    def test_position_callback(self):

        callback_executed = False

        def callback(xpos, ypos):
            nonlocal callback_executed
            callback_executed = True

        self.window.position_callback = callback
        self.assertEqual(self.window.position_callback, callback)

        self.window.set_position(0, 0)
        self.assertTrue(callback_executed)

    def test_remove_position_callback(self):
        self.window.position_callback = None
        self.assertEqual(self.window.position_callback, None)

    def test_position_callback_type_error(self):
        initial_value = self.window.position_callback

        with self.assertRaises(TypeError):
            self.window.position_callback = "string"

        self.assertEqual(self.window.position_callback, initial_value)

    def test_position_callback_value_errors(self):
        initial_value = self.window.position_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.position_callback = callback

        with self.assertRaises(ValueError):
            def callback(xpos):
                pass

            self.window.position_callback = callback

        with self.assertRaises(ValueError):
            def callback(xpos, ypos, arg):
                pass

            self.window.position_callback = callback

        self.assertEqual(self.window.position_callback, initial_value)

    # Framebuffer Size Callback

    def test_framebuffer_size_callback(self):

        def callback(width, height):
            pass

        self.window.framebuffer_size_callback = callback
        self.assertEqual(self.window.framebuffer_size_callback, callback)

    def test_remove_framebuffer_size_callback(self):
        self.window.framebuffer_size_callback = None
        self.assertEqual(self.window.framebuffer_size_callback, None)

    def test_framebuffer_size_callback_type_error(self):
        initial_value = self.window.framebuffer_size_callback

        with self.assertRaises(TypeError):
            self.window.framebuffer_size_callback = "string"

        self.assertEqual(self.window.framebuffer_size_callback, initial_value)

    def test_framebuffer_size_callback_value_errors(self):
        initial_value = self.window.framebuffer_size_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.framebuffer_size_callback = callback

        with self.assertRaises(ValueError):
            def callback(width):
                pass

            self.window.framebuffer_size_callback = callback

        with self.assertRaises(ValueError):
            def callback(width, height, thing):
                pass

            self.window.framebuffer_size_callback = callback

        self.assertEqual(self.window.framebuffer_size_callback, initial_value)

    # Content Scale Callback

    def test_content_scale_callback(self):

        def callback(xscale, yscale):
            pass

        self.window.content_scale_callback = callback
        self.assertEqual(self.window.content_scale_callback, callback)

    def test_remove_content_scale_callback(self):
        self.window.content_scale_callback = None
        self.assertEqual(self.window.content_scale_callback, None)

    def test_content_scale_callback_type_error(self):
        initial_value = self.window.content_scale_callback

        with self.assertRaises(TypeError):
            self.window.content_scale_callback = "string"

        self.assertEqual(self.window.content_scale_callback, initial_value)

    def test_content_scale_callback_value_errors(self):
        initial_value = self.window.content_scale_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.content_scale_callback = callback

        with self.assertRaises(ValueError):
            def callback(xscale):
                pass

            self.window.content_scale_callback = callback

        with self.assertRaises(ValueError):
            def callback(xscale, yscale, arg):
                pass

            self.window.content_scale_callback = callback

        self.assertEqual(self.window.content_scale_callback, initial_value)

    # Close Callback

    def test_close_callback(self):

        callback_executed = 0

        def callback():
            nonlocal callback_executed
            callback_executed += 1

        window = gp.Window(500, 500)
        window.close_callback = callback
        self.assertEqual(window.close_callback, callback)

        window.close()
        self.assertEqual(callback_executed, 1)

        window.close()
        self.assertEqual(callback_executed, 2)

        window.destroy()

    def test_remove_close_callback(self):
        self.window.close_callback = None
        self.assertEqual(self.window.close_callback, None)

    def test_close_callback_type_error(self):
        initial_value = self.window.close_callback

        with self.assertRaises(TypeError):
            self.window.close_callback = "string"

        self.assertEqual(self.window.close_callback, initial_value)

    def test_close_callback_value_errors(self):
        initial_value = self.window.close_callback

        with self.assertRaises(ValueError):
            def callback(arg):
                pass

            self.window.close_callback = callback

        self.assertEqual(self.window.close_callback, initial_value)

    # Destroy Callback

    def test_destroy_callback(self):

        callback_executed = 0

        def callback():
            nonlocal callback_executed
            callback_executed += 1

        window = gp.Window(500, 500)
        window.destroy_callback = callback
        self.assertEqual(window.destroy_callback, callback)

        window.destroy()
        self.assertEqual(callback_executed, 1)

        window.destroy()  # make sure the callback doesn't execute again
        self.assertEqual(callback_executed, 1)

    def test_remove_destroy_callback(self):
        self.window.destroy_callback = None
        self.assertEqual(self.window.destroy_callback, None)

    def test_destroy_callback_type_error(self):
        initial_value = self.window.destroy_callback

        with self.assertRaises(TypeError):
            self.window.destroy_callback = "string"

        self.assertEqual(self.window.destroy_callback, initial_value)

    def test_destroy_callback_value_errors(self):
        initial_value = self.window.destroy_callback

        with self.assertRaises(ValueError):
            def callback(arg):
                pass

            self.window.destroy_callback = callback

        self.assertEqual(self.window.destroy_callback, initial_value)

    # Minimize Callback

    def test_minimize_callback(self):

        callback_executed = False

        def callback(minimized):
            nonlocal callback_executed
            callback_executed = True

        self.window.minimize_callback = callback
        self.assertEqual(self.window.minimize_callback, callback)

        self.window.restore()
        self.window.minimize()
        self.assertTrue(callback_executed)

    def test_remove_minimize_callback(self):
        self.window.minimize_callback = None
        self.assertEqual(self.window.minimize_callback, None)

    def test_minimize_callback_type_error(self):
        initial_value = self.window.minimize_callback

        with self.assertRaises(TypeError):
            self.window.minimize_callback = "string"

        self.assertEqual(self.window.minimize_callback, initial_value)

    def test_minimize_callback_value_errors(self):
        initial_value = self.window.minimize_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.minimize_callback = callback

        with self.assertRaises(ValueError):
            def callback(minimize, arg):
                pass

            self.window.minimize_callback = callback

        self.assertEqual(self.window.minimize_callback, initial_value)

    # Maximize Callback

    def test_maximize_callback(self):

        callback_executed = False

        def callback(maximized):
            nonlocal callback_executed
            callback_executed = True

        self.window.maximize_callback = callback
        self.assertEqual(self.window.maximize_callback, callback)

        self.window.restore()
        self.window.maximize()
        self.assertTrue(callback_executed)

    def test_remove_maximize_callback(self):
        self.window.maximize_callback = None
        self.assertEqual(self.window.maximize_callback, None)

    def test_maximize_callback_type_error(self):
        initial_value = self.window.maximize_callback

        with self.assertRaises(TypeError):
            self.window.maximize_callback = "string"

        self.assertEqual(self.window.maximize_callback, initial_value)

    def test_maximize_callback_value_errors(self):
        initial_value = self.window.maximize_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.maximize_callback = callback

        with self.assertRaises(ValueError):
            def callback(maximize, arg):
                pass

            self.window.maximize_callback = callback

        self.assertEqual(self.window.maximize_callback, initial_value)

    # Focus Callback

    def test_focus_callback(self):

        callback_executed = False

        def callback(focused):
            nonlocal callback_executed
            callback_executed = True

        self.window.focus_callback = callback
        self.assertEqual(self.window.focus_callback, callback)

        self.window.minimize()
        self.window.set_focus()
        self.assertTrue(callback_executed)

    def test_remove_focus_callback(self):
        self.window.focus_callback = None
        self.assertEqual(self.window.focus_callback, None)

    def test_focus_callback_type_error(self):
        initial_value = self.window.focus_callback

        with self.assertRaises(TypeError):
            self.window.focus_callback = "string"

        self.assertEqual(self.window.focus_callback, initial_value)

    def test_focus_callback_value_errors(self):
        initial_value = self.window.focus_callback

        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.focus_callback = callback

        with self.assertRaises(ValueError):
            def callback(focused, arg):
                pass

            self.window.focus_callback = callback

        self.assertEqual(self.window.focus_callback, initial_value)

    # Refresh Callback

    def test_refresh_callback(self):

        callback_executed = False

        def callback():
            nonlocal callback_executed
            callback_executed = True

        self.window.refresh_callback = callback
        self.assertEqual(self.window.refresh_callback, callback)

        self.window.fullscreen()
        self.window.unfullscreen()
        self.assertTrue(callback_executed)

    def test_remove_refresh_callback(self):
        self.window.refresh_callback = None
        self.assertEqual(self.window.refresh_callback, None)

    def test_refresh_callback_type_error(self):
        initial_value = self.window.refresh_callback

        with self.assertRaises(TypeError):
            self.window.refresh_callback = "string"

        self.assertEqual(self.window.refresh_callback, initial_value)

    def test_refresh_callback_value_errors(self):
        initial_value = self.window.refresh_callback

        with self.assertRaises(ValueError):
            def callback(arg):
                pass

            self.window.refresh_callback = callback

        self.assertEqual(self.window.refresh_callback, initial_value)

    """Getter & Setters ---------------------------------------------------------------------------------------------"""

    # Width
    def test_width(self):
        self.window.width = 200
        self.assertEqual(self.window.width, 200)

    def test_width_errors(self):
        initial_value = self.window.width

        with self.assertRaises(TypeError):
            self.window.width = 102.2
        with self.assertRaises(ValueError):
            self.window.width = -100

        self.assertEqual(self.window.width, initial_value)

    # Height

    def test_height(self):
        self.window.height = 200
        self.assertEqual(self.window.height, 200)

    def test_height_errors(self):
        initial_value = self.window.height

        with self.assertRaises(TypeError):
            self.window.height = 102.2
        with self.assertRaises(ValueError):
            self.window.height = -100

        self.assertEqual(self.window.height, initial_value)

    # Size

    def test_size1(self):
        self.window.set_size(height=200, width=250)
        self.assertEqual(self.window.get_size(), (250, 200))

    def test_size2(self):
        self.window.set_size(self.initial_width, self.initial_height)
        self.assertEqual(self.window.get_size(), (self.initial_width, self.initial_height))

    def test_size_type_errors(self):
        initial_value = self.window.get_size()

        with self.assertRaises(TypeError):
            self.window.set_size("wrong", 100)
        with self.assertRaises(TypeError):
            self.window.set_size(100, "wrong")

        self.assertEqual(self.window.get_size(), initial_value)

    def test_size_value_errors(self):
        initial_value = self.window.get_size()

        with self.assertRaises(ValueError):
            self.window.set_size(-100, 100)
        with self.assertRaises(ValueError):
            self.window.set_size(100, -100)

        self.assertEqual(self.window.get_size(), initial_value)

    # X Position

    def test_x_position(self):
        self.window.xpos = 200
        self.assertEqual(self.window.xpos, 200)

    def test_x_position_errors(self):
        initial_value = self.window.xpos

        with self.assertRaises(TypeError):
            self.window.xpos = 102.2

        self.assertEqual(self.window.xpos, initial_value)

    # Height

    def test_y_position(self):
        self.window.ypos = 205
        self.assertEqual(self.window.ypos, 205)

    def test_y_position_errors(self):
        initial_value = self.window.ypos

        with self.assertRaises(TypeError):
            self.window.ypos = 102.2

        self.assertEqual(self.window.ypos, initial_value)

    # Size

    def test_position1(self):
        self.window.set_position(200, 250)
        # self.assertEqual(self.window.get_position(), (200, 250))

    def test_position2(self):
        self.window.set_position(y_position=105, x_position=115)
        self.assertEqual(self.window.get_position(), (115, 105))

    def test_position_errors(self):
        initial_value = self.window.get_position()

        with self.assertRaises(TypeError):
            self.window.set_position("wrong", 100)
        with self.assertRaises(TypeError):
            self.window.set_position(100, "wrong")

        self.assertEqual(self.window.get_position(), initial_value)

    # Title

    def test_title(self):
        self.assertEqual(self.window.title, self.initial_title)
        self.window.title = "This is a new title"
        self.assertEqual(self.window.title, "This is a new title")

    def test_title_errors(self):
        initial_value = self.window.title

        with self.assertRaises(TypeError):
            self.window.title = 1000

        self.assertEqual(self.window.title, initial_value)

    # Size Limits

    def test_set_size_limits1(self):
        self.assertIsNone(self.window.set_size_limits(50, 50, 1000, 1000))

    def test_set_size_limits2(self):
        self.window.set_size_limits(50, None, None, None)
        self.assertEqual(self.window.min_height, 0)
        self.assertIsNone(self.window.max_width)
        self.assertIsNone(self.window.max_height)

    def test_set_size_limits3(self):
        self.window.set_size_limits(None, 50, None, None)
        self.assertEqual(self.window.min_width, 0)
        self.assertIsNone(self.window.max_width)
        self.assertIsNone(self.window.max_height)

    def test_set_size_limits4(self):
        self.window.set_size_limits(None, None, 1000, None)
        self.assertEqual(self.window.max_height, gp.get_screen_height())
        self.assertIsNone(self.window.min_width)
        self.assertIsNone(self.window.min_height)

    def test_set_size_limits5(self):
        self.window.set_size_limits(None, None, None, 1000)
        self.assertEqual(self.window.max_width, gp.get_screen_width())
        self.assertIsNone(self.window.min_width)
        self.assertIsNone(self.window.min_height)

    def test_set_size_limits_type_errors(self):
        initial_value = (*self.window.get_minimum_size(), *self.window.get_maximum_size())

        with self.assertRaises(TypeError):
            self.window.set_size_limits("Test", 50, 1000, 1000)
        with self.assertRaises(TypeError):
            self.window.set_size_limits(50, "Test", 1000, 1000)
        with self.assertRaises(TypeError):
            self.window.set_size_limits(50, 50, "Test", 1000)
        with self.assertRaises(TypeError):
            self.window.set_size_limits(50, 50, 1000, "Test")

        self.assertEqual((*self.window.get_minimum_size(), *self.window.get_maximum_size()), initial_value)

    def test_set_size_limits_value_errors1(self):
        initial_value = (*self.window.get_minimum_size(), *self.window.get_maximum_size())

        with self.assertRaises(ValueError):
            self.window.set_size_limits(-1, 50, 1000, 1000)
        with self.assertRaises(ValueError):
            self.window.set_size_limits(50, -1, 1000, 1000)
        with self.assertRaises(ValueError):
            self.window.set_size_limits(50, 50, -1, 1000)
        with self.assertRaises(ValueError):
            self.window.set_size_limits(50, 50, 1000, -1)

        self.assertEqual((*self.window.get_minimum_size(), *self.window.get_maximum_size()), initial_value)

    def test_set_size_limits_value_errors2(self):
        initial_value = (*self.window.get_minimum_size(), *self.window.get_maximum_size())

        with self.assertRaises(ValueError):
            self.window.set_size_limits(100, 50, 50, 1000)
        with self.assertRaises(ValueError):
            self.window.set_size_limits(50, 100, 1000, 50)

        self.assertEqual((*self.window.get_minimum_size(), *self.window.get_maximum_size()), initial_value)

    def test_set_size_limits_keywords(self):
        self.window.set_size_limits(max_height=600, min_height=300, min_width=85, max_width=1005)
        self.assertEqual(self.window.get_minimum_size(), (85, 300))
        self.assertEqual(self.window.get_maximum_size(), (1005, 600))

    # Minimum Size

    def test_set_minimum_size1(self):
        self.assertIsNone(self.window.set_min_size(50, 50))

    def test_set_minimum_size2(self):
        self.window.set_min_size(50, None)
        self.assertEqual(self.window.min_height, 0)

    def test_set_minimum_size3(self):
        self.window.set_min_size(None, 50)
        self.assertEqual(self.window.min_width, 0)

    def test_set_minimum_size_type_errors(self):
        initial_value = self.window.get_minimum_size()

        with self.assertRaises(TypeError):
            self.window.set_min_size("Test", 50)
        with self.assertRaises(TypeError):
            self.window.set_min_size(50, "Test")

        self.assertEqual(self.window.get_minimum_size(), initial_value)

    def test_set_minimum_size_value_errors1(self):
        initial_value = self.window.get_minimum_size()

        with self.assertRaises(ValueError):
            self.window.set_min_size(-1, 50)
        with self.assertRaises(ValueError):
            self.window.set_min_size(50, -1)

        self.assertEqual(self.window.get_minimum_size(), initial_value)

    def test_set_minimum_size_keywords(self):
        self.window.set_min_size(min_height=605, min_width=405)
        self.assertEqual(self.window.get_minimum_size(), (405, 605))

    def test_get_minimum_size1(self):
        self.window.set_min_size(100, 200)
        self.assertEqual(self.window.get_minimum_size(), (100, 200))

    def test_get_minimum_size2(self):
        self.window.set_min_size(100, None)
        self.assertEqual(self.window.get_minimum_size(), (100, 0))

    def test_get_minimum_size3(self):
        self.window.set_min_size(None, 200)
        self.assertEqual(self.window.get_minimum_size(), (0, 200))

    def test_get_minimum_size4(self):
        self.window.set_min_size(None, None)
        self.assertIsNone(self.window.get_minimum_size())

    # Maximum Size

    def test_set_maximum_size1(self):
        self.assertIsNone(self.window.set_max_size(1000, 1000))

    def test_set_maximum_size2(self):
        self.window.set_max_size(1000, None)
        self.assertEqual(self.window.max_height, gp.get_screen_height())

    def test_set_maximum_size3(self):
        self.window.set_max_size(None, 1000)
        self.assertEqual(self.window.max_width, gp.get_screen_width())

    def test_set_maximum_size_type_errors(self):
        initial_value = self.window.get_maximum_size()

        with self.assertRaises(TypeError):
            self.window.set_max_size("Test", 1000)
        with self.assertRaises(TypeError):
            self.window.set_max_size(1000, "Test")

        self.assertEqual(self.window.get_maximum_size(), initial_value)

    def test_set_maximum_size_value_errors1(self):
        initial_value = self.window.get_maximum_size()

        with self.assertRaises(ValueError):
            self.window.set_max_size(-1, 1000)
        with self.assertRaises(ValueError):
            self.window.set_max_size(1000, -1)

        self.assertEqual(self.window.get_maximum_size(), initial_value)

    def test_set_maximum_size_value_errors2(self):
        initial_value = self.window.get_maximum_size()

        self.window.set_min_size(100, 100)
        with self.assertRaises(ValueError):
            self.window.set_max_size(50, 1000)
        with self.assertRaises(ValueError):
            self.window.set_max_size(1000, 50)

        self.assertEqual(self.window.get_maximum_size(), initial_value)

    def test_set_maximum_size_keywords(self):
        self.window.set_max_size(max_height=905, max_width=705)
        self.assertEqual(self.window.get_maximum_size(), (705, 905))

    def test_get_maximum_size1(self):
        self.window.set_max_size(1000, 1200)
        self.assertEqual(self.window.get_maximum_size(), (1000, 1200))

    def test_get_maximum_size2(self):
        self.window.set_max_size(1000, None)
        self.assertEqual(self.window.get_maximum_size(), (1000, gp.get_screen_height()))

    def test_get_maximum_size3(self):
        self.window.set_max_size(None, 200)
        self.assertEqual(self.window.get_maximum_size(), (gp.get_screen_width(), 200))

    def test_get_maximum_size4(self):
        self.window.set_max_size(None, None)
        self.assertIsNone(self.window.get_maximum_size())

    # Minimum Width

    def test_min_width1(self):
        self.window.min_width = 200
        self.assertEqual(self.window.min_width, 200)

    def test_min_width2(self):
        self.window.set_size_limits(None, None, None, None)
        self.window.min_width = 400
        self.assertEqual(self.window.min_height, 0)

    def test_min_width_errors(self):
        initial_value = self.window.min_width

        with self.assertRaises(TypeError):
            self.window.min_width = 105.5
        with self.assertRaises(ValueError):
            self.window.min_width = -100

        self.assertEqual(self.window.min_width, initial_value)

    # Maximum Width

    def test_max_width1(self):
        self.window.max_width = 1200
        self.assertEqual(self.window.max_width, 1200)

    def test_max_width2(self):
        self.window.set_size_limits(None, None, None, None)
        self.window.max_width = 1000
        self.assertEqual(self.window.max_height, gp.get_screen_height())

    def test_max_width_errors(self):
        initial_value = self.window.max_width

        with self.assertRaises(TypeError):
            self.window.max_width = 105.5
        with self.assertRaises(ValueError):
            self.window.max_width = -100
        with self.assertRaises(ValueError):
            self.window.min_width = 50
            self.window.max_width = 20

        self.assertEqual(self.window.max_width, initial_value)

    # Minimum Height

    def test_min_height1(self):
        self.window.min_height = 200
        self.assertEqual(self.window.min_height, 200)

    def test_min_height2(self):
        self.window.set_size_limits(None, None, None, None)
        self.window.min_height = 400
        self.assertEqual(self.window.min_width, 0)

    def test_min_height_errors(self):
        initial_value = self.window.min_height

        with self.assertRaises(TypeError):
            self.window.min_height = 105.5
        with self.assertRaises(ValueError):
            self.window.min_height = -100

        self.assertEqual(self.window.min_height, initial_value)

    # Maximum Height

    def test_max_height1(self):
        self.window.max_height = 1200
        self.assertEqual(self.window.max_height, 1200)

    def test_max_height2(self):
        self.window.set_size_limits(None, None, None, None)
        self.window.max_height = 1000
        self.assertEqual(self.window.max_width, gp.get_screen_width())

    def test_max_height_errors(self):
        initial_value = self.window.max_height

        with self.assertRaises(TypeError):
            self.window.max_height = 105.5
        with self.assertRaises(ValueError):
            self.window.max_height = -100
        with self.assertRaises(ValueError):
            self.window.min_height = 50
            self.window.max_height = 20

        self.assertEqual(self.window.max_height, initial_value)

    # Framebuffer Size Functions

    def test_framebuffer_size1(self):
        self.assertIsInstance(self.window.framebuffer_size, tuple)
        self.assertEqual(len(self.window.framebuffer_size), 2)
        for obj in self.window.framebuffer_size:
            self.assertIsInstance(obj, int)

    def test_framebuffer_size2(self):
        self.assertIsInstance(self.window.framebuffer_size, tuple)
        self.assertEqual(len(self.window.framebuffer_size), 2)
        for obj in self.window.framebuffer_size:
            self.assertIsInstance(obj, int)

    def test_framebuffer_size_error(self):
        initial_value = self.window.framebuffer_size

        with self.assertRaises(NotImplementedError):
            self.window.framebuffer_size = (100, 100)

        self.assertEqual(self.window.framebuffer_size, initial_value)

    # Other Attributes
    def test_resizable(self):
        self.assertFalse(self.window.resizable)
        self.window.resizable = True
        self.assertTrue(self.window.resizable)
        self.window.resizable = False
        self.assertFalse(self.window.resizable)

    def test_decorated(self):
        self.assertTrue(self.window.decorated)
        self.window.decorated = False
        self.assertFalse(self.window.decorated)
        self.window.decorated = True
        self.assertTrue(self.window.decorated)

    def test_auto_minimized(self):
        self.assertTrue(self.window.auto_minimized)
        self.window.auto_minimized = False
        self.assertFalse(self.window.auto_minimized)

    def test_floating(self):
        self.assertFalse(self.window.floating)
        self.window.floating = True
        self.assertTrue(self.window.floating)

    def test_focused_on_show(self):
        self.assertTrue(self.window.focused_on_show)
        self.window.focused_on_show = False
        self.assertFalse(self.window.focused_on_show)

    # Window Events

    def test_check_key(self):
        self.assertIsInstance(self.window.check_key(gp.KEY_0), bool)

    def test_check_key_type_error(self):
        with self.assertRaises(TypeError):
            self.window.check_key("string")

    def test_check_key_value_error(self):
        with self.assertRaises(ValueError):
            self.window.check_key(-2)

    # Key Code Callback

    def test_key_code_callback(self):

        def callback(key_coded):
            pass

        self.window.set_key_callback(gp.KEY_0, callback)

    def test_remove_key_code_callback(self):
        self.window.set_key_callback(gp.KEY_0, None)

    def test_key_code_callback_type_error(self):
        with self.assertRaises(TypeError):
            self.window.set_key_callback(gp.KEY_0, "string")

        with self.assertRaises(TypeError):
            self.window.set_key_callback("string", lambda x: x)

        with self.assertRaises(ValueError):
            self.window.set_key_callback(-2, lambda x: x)

    def test_key_code_callback_value_errors(self):
        with self.assertRaises(ValueError):
            def callback():
                pass

            self.window.set_key_callback(gp.KEY_0, callback)

        with self.assertRaises(ValueError):
            def callback(keycode, arg):
                pass

            self.window.set_key_callback(gp.KEY_0, callback)
