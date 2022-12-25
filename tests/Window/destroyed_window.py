import unittest
import goopylib as gp


# noinspection PyTypeChecker
class DestroyedWindowMethods(unittest.TestCase):
    window = None
    initial_width = 500
    initial_height = 400
    initial_title = "New Window!"

    @classmethod
    def setUpClass(cls):
        gp.init()
        cls.window = gp.Window(cls.initial_width, cls.initial_height, cls.initial_title)
        cls.window.destroy()

    @classmethod
    def tearDownClass(cls):
        gp.terminate()

    """Core Window Methods ------------------------------------------------------------------------------------------"""

    def test_repr(self):
        self.assertEqual(self.window.__repr__(), f"Destroyed Window()")

    # Window Methods

    def test_redestroy(self):
        self.assertIsNone(self.window.destroy())

    def test_close(self):
        with self.assertRaises(RuntimeError):
            self.window.close()

    def test_update(self):
        self.assertIsNone(self.window.update())

    def test_set_focus(self):
        with self.assertRaises(RuntimeError):
            self.assertIsNone(self.window.set_focus())

    def test_has_focus(self):
        with self.assertRaises(RuntimeError):
            self.assertIsNone(self.window.has_focus())

    def test_is_open(self):
        self.assertFalse(self.window.is_open())

    def test_is_closed(self):
        self.assertTrue(self.window.is_closed())
        
    # Window States

    def test_is_fullscreen(self):
        with self.assertRaises(RuntimeError):
            self.window.is_fullscreen()

    def test_is_maximized(self):
        with self.assertRaises(RuntimeError):
            self.window.is_maximized()

    def test_is_minimized(self):
        with self.assertRaises(RuntimeError):
            self.window.is_minimized()

    def test_is_visible(self):
        with self.assertRaises(RuntimeError):
            self.window.is_visible()

    def test_is_hidden(self):
        with self.assertRaises(RuntimeError):
            self.window.is_hidden()

    def test_make_fullscreen(self):
        with self.assertRaises(RuntimeError):
            self.window.fullscreen()

    def test_make_windowed(self):
        with self.assertRaises(RuntimeError):
            self.window.unfullscreen()

    def test_minimize(self):
        with self.assertRaises(RuntimeError):
            self.window.minimize()

    def test_maximize(self):
        with self.assertRaises(RuntimeError):
            self.window.maximize()

    def test_restore(self):
        with self.assertRaises(RuntimeError):
            self.window.restore()

    def test_show(self):
        with self.assertRaises(RuntimeError):
            self.window.show()

    def test_hide(self):
        with self.assertRaises(RuntimeError):
            self.window.hide()

    # Window Events

    def test_is_mouse_hovering(self):
        with self.assertRaises(RuntimeError):
            self.window.is_mouse_hovering()

    def test_check_key(self):
        with self.assertRaises(RuntimeError):
            self.window.check_key(gp.KEY_0)

    # def test_has_transparent_frame_buffer(self):
    #     with self.assertRaises(RuntimeError):
    #         self.window.has_transparent_framebuffer()

    # Set Size Limits

    def test_set_size_limits(self):
        with self.assertRaises(RuntimeError):
            self.window.set_size_limits(50, 50, 100, 100)

    def test_set_minimum_size(self):
        with self.assertRaises(RuntimeError):
            self.window.set_minimum_size(50, 50)
        with self.assertRaises(RuntimeError):
            tmp = self.window.min_width
        with self.assertRaises(RuntimeError):
            tmp = self.window.min_height

    def test_set_maximum_size(self):
        with self.assertRaises(RuntimeError):
            self.window.set_maximum_size(1000, 1000)
        with self.assertRaises(RuntimeError):
            tmp = self.window.max_width
        with self.assertRaises(RuntimeError):
            tmp = self.window.max_height

    # Aspect Ratio & Scaling

    def test_get_frame_size(self):
        with self.assertRaises(RuntimeError):
            self.window.get_frame_size()

    def test_get_content_scale(self):
        with self.assertRaises(RuntimeError):
            self.window.get_content_scale()

    def test_set_aspect_ratio(self):
        with self.assertRaises(RuntimeError):
            self.window.set_aspect_ratio(1, 1)

    def test_get_aspect_ratio(self):
        with self.assertRaises(RuntimeError):
            self.window.get_aspect_ratio()

    # Callbacks

    def test_resize_callback_warning(self):

        def callback(width, height):
            pass

        with self.assertRaises(RuntimeError):
            self.window.resize_callback = callback
        self.assertEqual(self.window.resize_callback, None)

    def test_position_callback_warning(self):

        def callback(xpos, ypos):
            pass

        with self.assertRaises(RuntimeError):
            self.window.position_callback = callback
        self.assertEqual(self.window.position_callback, None)

    def test_framebuffer_size_callback_warning(self):

        def callback(width, height):
            pass

        with self.assertRaises(RuntimeError):
            self.window.framebuffer_size_callback = callback
        self.assertEqual(self.window.framebuffer_size_callback, None)

    def test_content_scale_callback_warning(self):

        def callback(xscale, yscale):
            pass

        with self.assertRaises(RuntimeError):
            self.window.content_scale_callback = callback
        self.assertEqual(self.window.content_scale_callback, None)

    def test_close_callback_warning(self):

        def callback():
            pass

        with self.assertRaises(RuntimeError):
            self.window.close_callback = callback
        self.assertEqual(self.window.close_callback, None)

    def test_destroy_callback_warning(self):

        def callback():
            pass

        with self.assertRaises(RuntimeError):
            self.window.destroy_callback = callback
        self.assertEqual(self.window.destroy_callback, None)

    def test_minimize_callback_warning(self):

        def callback(minimized):
            pass

        with self.assertRaises(RuntimeError):
            self.window.minimize_callback = callback
        self.assertEqual(self.window.minimize_callback, None)

    def test_maximize_callback_warning(self):

        def callback(maximized):
            pass

        with self.assertRaises(RuntimeError):
            self.window.maximize_callback = callback
        self.assertEqual(self.window.maximize_callback, None)

    def test_focus_callback_warning(self):

        def callback(focused):
            pass

        with self.assertRaises(RuntimeError):
            self.window.focus_callback = callback
        self.assertEqual(self.window.focus_callback, None)

    def test_refresh_callback_warning(self):

        def callback():
            pass

        with self.assertRaises(RuntimeError):
            self.window.refresh_callback = callback
        self.assertEqual(self.window.refresh_callback, None)

    """Getters & Setters --------------------------------------------------------------------------------------------"""
    
    # Width
    def test_width1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.width

    def test_width2(self):
        with self.assertRaises(RuntimeError):
            self.window.width = self.initial_width
    
    # Height
    def test_height1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.height

    def test_height2(self):
        with self.assertRaises(RuntimeError):
            self.window.height = self.initial_height
    
    # Size
    def test_size1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.get_size()

    def test_size2(self):
        with self.assertRaises(RuntimeError):
            self.window.set_size(self.initial_width, self.initial_height)
    
    # X Position
    def test_x_position1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.xpos

    def test_x_position2(self):
        with self.assertRaises(RuntimeError):
            self.window.xpos = 50

    # Y Position 
    def test_y_position1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.ypos

    def test_y_position2(self):
        with self.assertRaises(RuntimeError):
            self.window.ypos = 50
    
    # Position
    def test_position1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.get_position()

    def test_position2(self):
        with self.assertRaises(RuntimeError):
            self.window.set_position(100, 100)
    
    # Title
    def test_title1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.title

    def test_title2(self):
        with self.assertRaises(RuntimeError):
            self.window.title = "This is a new title"
    
    # Framebuffer Size
    def test_framebuffer_size(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.framebuffer_size
    
    # Minimum & Maximum Sizes
    def test_min_width(self):
        with self.assertRaises(RuntimeError):
            self.window.min_width = 200
        with self.assertRaises(RuntimeError):
            tmp = self.window.min_width
    
    def test_max_width(self):
        with self.assertRaises(RuntimeError):
            self.window.max_width = 1200
        with self.assertRaises(RuntimeError):
            tmp = self.window.max_width

    def test_min_height(self):
        with self.assertRaises(RuntimeError):
            self.window.min_height = 200
        with self.assertRaises(RuntimeError):
            tmp = self.window.min_height

    def test_max_height(self):
        with self.assertRaises(RuntimeError):
            self.window.max_height = 1200
        with self.assertRaises(RuntimeError):
            tmp = self.window.max_height
    
    # Resizable
    def test_resizable1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.resizable

    def test_resizable2(self):
        with self.assertRaises(RuntimeError):
            self.window.resizable = True
    
    # Decorated
    def test_decorated1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.decorated

    def test_decorated2(self):
        with self.assertRaises(RuntimeError):
            self.window.decorated = True
    
    # Auto Minimized
    def test_auto_minimized1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.auto_minimized

    def test_auto_minimized2(self):
        with self.assertRaises(RuntimeError):
            self.window.auto_minimized = True
    
    # Floating
    def test_floating1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.floating

    def test_floating2(self):
        with self.assertRaises(RuntimeError):
            self.window.floating = True
    
    # Focused on Show
    def test_focused_on_show1(self):
        with self.assertRaises(RuntimeError):
            tmp = self.window.focused_on_show

    def test_focused_on_show2(self):
        with self.assertRaises(RuntimeError):
            self.window.focused_on_show = True
