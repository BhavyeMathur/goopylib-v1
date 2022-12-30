#pragma once

#include "header.h"

static void **PyColor_API;
static PyTypeObject *ColorType;

static void **PyCamera_API;
static PyTypeObject *CameraType;

struct WindowObject;

// Window Core
namespace window {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(WindowObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(WindowObject *self);

    static int traverse(WindowObject *self, visitproc visit, void *arg);

    static int clear(WindowObject *self);

    static void dealloc(WindowObject *self);
}

// Window Methods
namespace window {
    static PyObject *is_closed(WindowObject *self, PyObject *args);

    static PyObject *is_open(WindowObject *self, PyObject *args);

    static PyObject *update(WindowObject *self, PyObject *args);

    static PyObject *destroy(WindowObject *self, PyObject *args);

    static PyObject *to_world(WindowObject *self, PyObject *args);

    static PyObject *to_screen(WindowObject *self, PyObject *args);
}

// Window Getter & Setters
namespace window {
    // Width
    static PyObject *get_width(WindowObject *self, void *closure);

    static int set_width(WindowObject *self, PyObject *value, void *closure);

    // Height
    static PyObject *get_height(WindowObject *self, void *closure);

    static int set_height(WindowObject *self, PyObject *value, void *closure);

    // Title
    static int set_title(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_title(WindowObject *self, void *closure);

    // X Position
    static int set_xpos(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_xpos(WindowObject *self, void *closure);

    // Y Position
    static int set_ypos(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_ypos(WindowObject *self, void *closure);

    // Background
    static int set_background(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_background(WindowObject *self, void *closure);

    // Minimum Width
    static PyObject *get_min_width(WindowObject *self, void *closure);

    static int set_min_width(WindowObject *self, PyObject *value, void *closure);

    // Minimum Height
    static PyObject *get_min_height(WindowObject *self, void *closure);

    static int set_min_height(WindowObject *self, PyObject *value, void *closure);

    // Maximum Width
    static PyObject *get_max_width(WindowObject *self, void *closure);

    static int set_max_width(WindowObject *self, PyObject *value, void *closure);

    // Maximum Height
    static PyObject *get_max_height(WindowObject *self, void *closure);

    static int set_max_height(WindowObject *self, PyObject *value, void *closure);
}

// Window Get & Set functions
namespace window {
    // Size
    static PyObject *set_size(WindowObject *self, PyObject *args);

    static PyObject *get_size(WindowObject *self, void *closure);

    // Size Limits
    static PyObject *set_size_limits(WindowObject *self, PyObject *args, PyObject *kwds);

    // Minimum Size
    static PyObject *set_min_size(WindowObject *self, PyObject *args);

    static PyObject *get_min_size(WindowObject *self, void *closure);

    // Maximum Size
    static PyObject *set_max_size(WindowObject *self, PyObject *args);

    static PyObject *get_max_size(WindowObject *self, void *closure);

    // Position
    static PyObject *set_position(WindowObject *self, PyObject *args);

    static PyObject *get_position(WindowObject *self, void *closure);

    // Aspect Ratio
    static PyObject *set_aspect_ratio(WindowObject *self, PyObject *args);

    static PyObject *get_aspect_ratio(WindowObject *self, PyObject *args);

    // Frame size & Content Scale
    static PyObject *get_frame_size(WindowObject *self, PyObject *args);

    static PyObject *get_content_scale(WindowObject *self, PyObject *args);

    static PyObject *get_framebuffer_size(WindowObject *self, void *closure);
}

namespace window {
    // Resizable
    static int set_resizable(WindowObject *self, PyObject *value, void *closure);

    static PyObject *is_resizable(WindowObject *self, PyObject *args);

    // Decorated
    static int set_decorated(WindowObject *self, PyObject *value, void *closure);

    static PyObject *is_decorated(WindowObject *self, PyObject *args);

    // Floating
    static int set_floating(WindowObject *self, PyObject *value, void *closure);

    static PyObject *is_floating(WindowObject *self, PyObject *args);

    // Auto Minimized
    static int set_auto_minimized(WindowObject *self, PyObject *value, void *closure);

    static PyObject *is_auto_minimized(WindowObject *self, PyObject *args);


    // Focused on Show
    static int set_focused_on_show(WindowObject *self, PyObject *value, void *closure);

    static PyObject *is_focused_on_show(WindowObject *self, PyObject *args);
}

// Window States
namespace window {
    static PyObject *restore(WindowObject *self, PyObject *args);

    static PyObject *is_fullscreen(WindowObject *self, PyObject *args);

    static PyObject *fullscreen(WindowObject *self, PyObject *args);

    static PyObject *is_maximized(WindowObject *self, PyObject *args);

    static PyObject *maximize(WindowObject *self, PyObject *args);

    static PyObject *is_minimized(WindowObject *self, PyObject *args);

    static PyObject *minimize(WindowObject *self, PyObject *args);

    static PyObject *show(WindowObject *self, PyObject *args);

    static PyObject *hide(WindowObject *self, PyObject *args);

    static PyObject *is_visible(WindowObject *self, PyObject *args);

    static PyObject *focus(WindowObject *self, PyObject *args);

    static PyObject *has_focus(WindowObject *self, PyObject *args);

    static PyObject *request_attention(WindowObject *self, PyObject *args);
}

// Window Input Events
namespace window {
    static PyObject *is_mouse_hovering(WindowObject *self, PyObject *args);

    static PyObject *get_mouse_position(WindowObject *self, PyObject *args);

    static PyObject *set_cursor_mode(WindowObject *self, PyObject *args);

    static PyObject *check_shift_key(WindowObject *self, PyObject *args);

    static PyObject *check_control_key(WindowObject *self, PyObject *args);

    static PyObject *check_alt_key(WindowObject *self, PyObject *args);

    static PyObject *check_super_key(WindowObject *self, PyObject *args);

    static PyObject *check_key(WindowObject *self, PyObject *arg);

    static PyObject *check_mouse_button(WindowObject *self, PyObject *arg);

    static PyObject *check_left_click(WindowObject *self, PyObject *arg);

    static PyObject *check_middle_click(WindowObject *self, PyObject *arg);

    static PyObject *check_right_click(WindowObject *self, PyObject *arg);

    static PyObject *set_key_callback(WindowObject *self, PyObject *args, PyObject *kwds);

    static PyObject *set_mouse_button_callback(WindowObject *self, PyObject *args, PyObject *kwds);
}

// Window Callbacks
namespace window {
    // Resize
    static int set_resize_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_resize_callback(WindowObject *self, void *closure);

    // Close
    static int set_close_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_close_callback(WindowObject *self, void *closure);

    // Destroy
    static int set_destroy_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_destroy_callback(WindowObject *self, void *closure);

    // Position
    static int set_position_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_position_callback(WindowObject *self, void *closure);

    // Minimize
    static int set_minimize_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_minimize_callback(WindowObject *self, void *closure);

    // Maximize
    static int set_maximize_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_maximize_callback(WindowObject *self, void *closure);

    // Focus
    static int set_focus_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_focus_callback(WindowObject *self, void *closure);

    // Refresh
    static int set_refresh_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_refresh_callback(WindowObject *self, void *closure);

    // Content Scale
    static int set_content_scale_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_content_scale_callback(WindowObject *self, void *closure);

    // Framebuffer Size
    static int set_framebuffer_size_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_framebuffer_size_callback(WindowObject *self, void *closure);

    // Mouse Motion
    static int set_mouse_motion_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_mouse_motion_callback(WindowObject *self, void *closure);

    // Mouse Enter
    static int set_mouse_enter_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_mouse_enter_callback(WindowObject *self, void *closure);

    // Scroll
    static int set_scroll_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_scroll_callback(WindowObject *self, void *closure);

    // Mouse Buttons
    static int set_left_click_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_left_click_callback(WindowObject *self, void *closure);

    static int set_middle_click_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_middle_click_callback(WindowObject *self, void *closure);

    static int set_right_click_callback(WindowObject *self, PyObject *value, void *closure);

    static PyObject *get_right_click_callback(WindowObject *self, void *closure);
}

// Static Window Methods
namespace window {
    static PyObject *update_all(WindowObject *self, PyObject *args);

    static PyObject *destroy_all(WindowObject *self, PyObject *args);
}

extern PyTypeObject WindowType;
