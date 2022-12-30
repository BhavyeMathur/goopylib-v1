#define WINDOW_MODULE

#include "window.h"
#include "window_object.h"
#include "window_module.h"
#include "window_capsule.h"

#include "color/color_object.h"
#include "color/color_module.h"

#include "scene/camera_object.h"
#include "scene/camera_module.h"

#include "goopylib/core/Window.h"
#include "goopylib/events/MouseCodes.h"

#include "config.h"

#if (GP_LOG_WINDOW != true) and (GP_LOG_WINDOW <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_WINDOW
#endif

#if !GP_VALUE_CHECK_WINDOW
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"

#if GP_ERROR_CHECKING
#define CHECK_ACTIVE(val) \
do { if (self->window->isDestroyed()) { \
    PyErr_SetString(PyExc_RuntimeError, "window has been destroyed"); \
    return val; \
} } while (0)
#else
#define CHECK_ACTIVE(val) nullptr
#endif

// Window Core
namespace window {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        WindowObject *self;
        self = (WindowObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {
            self->resize_callback = Py_None;
            self->close_callback = Py_None;
            self->destroy_callback = Py_None;
            self->position_callback = Py_None;
            self->content_scale_callback = Py_None;
            self->framebuffer_size_callback = Py_None;
            self->minimize_callback = Py_None;
            self->maximize_callback = Py_None;
            self->focus_callback = Py_None;
            self->refresh_callback = Py_None;
            self->mouse_motion_callback = Py_None;
            self->mouse_enter_callback = Py_None;
            self->scroll_callback = Py_None;

            self->background = Py_None;
            self->camera = Py_None;
        }
        return (PyObject *) self;
    }

    static int init(WindowObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.window.Window()");

        PyObject *tmp;
        int width, height;
        if (!PyArg_ParseTuple(args, "iiU", &width, &height, &tmp)) {
            return -1;
        }

        GP_CHECK_GT(width, 0, -1, "width must be greater than 0")
        GP_CHECK_GT(height, 0, -1, "height must be greater than 0")

        self->background = PyObject_CallObject((PyObject *) ColorType, Py_BuildValue("iii", 255, 255, 255));

        self->window = std::unique_ptr<gp::Window>(new gp::Window(width, height, PyUnicode_AsUTF8(tmp)));
        self->window->setBackground(*((ColorObject *) self->background)->color);

        self->camera = PyObject_CallObject((PyObject *) CameraType, Py_BuildValue("iiii", 0, 0, 0, 0));
        ((CameraObject *) self->camera)->camera = std::shared_ptr<gp::Camera>(&self->window->getCamera());

        return 0;
    }

    static PyObject *repr(WindowObject *self) {
        GP_PY_TRACE("gp.window.Window.__repr__()");
        return PyUnicode_FromString(self->window->toString().c_str());
    }

    static int traverse(WindowObject *self, visitproc visit, void *arg) {
        Py_VISIT(self->resize_callback);
        Py_VISIT(self->close_callback);
        Py_VISIT(self->destroy_callback);
        Py_VISIT(self->position_callback);
        Py_VISIT(self->content_scale_callback);
        Py_VISIT(self->framebuffer_size_callback);
        Py_VISIT(self->minimize_callback);
        Py_VISIT(self->maximize_callback);
        Py_VISIT(self->focus_callback);
        Py_VISIT(self->refresh_callback);
        Py_VISIT(self->mouse_motion_callback);
        Py_VISIT(self->mouse_enter_callback);
        Py_VISIT(self->scroll_callback);

        Py_VISIT(self->background);

        for (auto key: self->key_callbacks) {
            Py_VISIT(key.second);
        }
        for (auto button: self->mouse_callbacks) {
            Py_VISIT(button.second);
        }

        return 0;
    }

    static int clear(WindowObject *self) {
        GP_PY_TRACE("gp.window.Window.clear()");

        self->window.reset();

        Py_CLEAR(self->resize_callback);
        Py_CLEAR(self->close_callback);
        Py_CLEAR(self->position_callback);
        Py_CLEAR(self->destroy_callback);
        Py_CLEAR(self->content_scale_callback);
        Py_CLEAR(self->framebuffer_size_callback);
        Py_CLEAR(self->minimize_callback);
        Py_CLEAR(self->maximize_callback);
        Py_CLEAR(self->focus_callback);
        Py_CLEAR(self->refresh_callback);
        Py_CLEAR(self->mouse_motion_callback);
        Py_CLEAR(self->mouse_enter_callback);
        Py_CLEAR(self->scroll_callback);

        Py_CLEAR(self->background);

        for (auto key: self->key_callbacks) {
            Py_CLEAR(key.second);
        }
        for (auto button: self->mouse_callbacks) {
            Py_CLEAR(button.second);
        }

        return 0;
    }

    static void dealloc(WindowObject *self) {
        GP_PY_DEBUG("gp.window.Window.__dealloc__()");

        self->window.reset();

        Py_XDECREF(self->resize_callback);
        Py_XDECREF(self->close_callback);
        Py_XDECREF(self->position_callback);
        Py_XDECREF(self->destroy_callback);
        Py_XDECREF(self->content_scale_callback);
        Py_XDECREF(self->framebuffer_size_callback);
        Py_XDECREF(self->minimize_callback);
        Py_XDECREF(self->maximize_callback);
        Py_XDECREF(self->focus_callback);
        Py_XDECREF(self->refresh_callback);
        Py_XDECREF(self->mouse_motion_callback);
        Py_XDECREF(self->mouse_enter_callback);
        Py_XDECREF(self->scroll_callback);

        Py_XDECREF(self->background);

        for (auto key: self->key_callbacks) {
            Py_XDECREF(key.second);
        }
        for (auto button: self->mouse_callbacks) {
            Py_XDECREF(button.second);
        }

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Window Methods
namespace window {
    static PyObject *is_closed(WindowObject *self, PyObject *Py_UNUSED(args)) {
        if (self->window->isClosed()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *is_open(WindowObject *self, PyObject *Py_UNUSED(args)) {
        if (self->window->isClosed()) {
            Py_RETURN_FALSE;
        }
        Py_RETURN_TRUE;
    }

    static PyObject *update(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->update();
        Py_RETURN_NONE;
    }

    static PyObject *destroy(WindowObject *self, PyObject *Py_UNUSED(args)) {
        self->window->destroy();
        Py_RETURN_NONE;
    }

    static PyObject *get_camera(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);
        RETURN_PYOBJECT(self->camera);
    }

    static PyObject *to_world(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        auto pos = self->window->toWorld({x, y});
        return PyTuple_Pack(2, PyFloat_FromDouble(pos.x), PyFloat_FromDouble(pos.y));
    }

    static PyObject *to_screen(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        auto pos = self->window->toScreen({x, y});
        return PyTuple_Pack(2, PyFloat_FromDouble(pos.x), PyFloat_FromDouble(pos.y));
    }
}

// Window Getter & Setters
namespace window {
    // Width
    static PyObject *get_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getWidth());
    }

    static int set_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int width = (int) PyLong_AsLong(value);

        GP_CHECK_GT(width, 0, -1, "width must be greater than 0")

        self->window->setWidth(width);
        return 0;
    }

    // Height
    static PyObject *get_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getHeight());
    }

    static int set_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int height = (int) PyLong_AsLong(value);

        GP_CHECK_GT(height, 0, -1, "width must be greater than 0")

        self->window->setHeight(height);
        GP_PY_TRACE("gp.window.Window.set_height() - returning");
        return 0;
    }

    // Title
    static int set_title(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyUnicode_Check(value)) {
            RAISE_TYPE_ERROR(-1, "string", value);
        }
        #endif

        self->window->setTitle(PyUnicode_AsUTF8(value));
        return 0;
    }

    static PyObject *get_title(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyUnicode_FromString(self->window->getTitle());
    }

    // X Position
    static int set_xpos(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        self->window->setXPos((int) PyLong_AsLong(value));
        return 0;
    }

    static PyObject *get_xpos(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getXPos());
    }

    // Y Position
    static int set_ypos(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_TRACE("gp.window.Window.set_ypos({0})", PyUnicode_AsUTF8(PyObject_Repr(value)));

        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        self->window->setYPos((int) PyLong_AsLong(value));
        return 0;
    }

    static PyObject *get_ypos(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getYPos());
    }

    // Background
    static int set_background(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        if (isinstance(value, ColorType)) {
            SET_PYOBJECT(self->background, value);
        }
        else {
            PyObject *tmp = self->background;
            self->background = PyObject_CallObject((PyObject *) ColorType, value);
            Py_XDECREF(tmp);

            #if GP_TYPE_CHECKING
            if (self->background == nullptr) {
                return -1;
            }
            #endif
        }

        self->window->setBackground(*((ColorObject *) self->background)->color);

        return 0;
    }

    static PyObject *get_background(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        RETURN_PYOBJECT(self->background);
    }

    // Minimum Width
    static PyObject *get_min_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getMinWidth());
    }

    static int set_min_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int minWidth = (int) PyLong_AsLong(value);

        GP_CHECK_GE(minWidth, 0, -1, "minimum width must be greater than or equal to 0")

        self->window->setMinWidth(minWidth);
        return 0;
    }

    // Minimum Height
    static PyObject *get_min_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getMinHeight());
    }

    static int set_min_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        #endif

        int minHeight = (int) PyLong_AsLong(value);
        GP_CHECK_GE(minHeight, 0, -1, "minimum height must be greater than or equal to 0")

        self->window->setMinHeight(minHeight);
        return 0;
    }

    // Maximum Width
    static PyObject *get_max_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getMaxWidth());
    }

    static int set_max_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        if (PyLong_Check(value)) {
            int maxWidth = (int) PyLong_AsLong(value);

            GP_CHECK_GE(maxWidth, self->window->getMinWidth(), -1,
                        "maximum width must be greater than or equal to minimum width")

            self->window->setMaxWidth(maxWidth);
        }
        else if (value == Py_None) {
            self->window->setMaxWidth(INT_MAX);
        }
        else {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        return 0;
    }

    // Maximum Height
    static PyObject *get_max_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyLong_FromLong(self->window->getMaxHeight());
    }

    static int set_max_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        if (PyLong_Check(value)) {
            int maxHeight = (int) PyLong_AsLong(value);

            GP_CHECK_GE(maxHeight, self->window->getMinHeight(), -1,
                        "maximum height must be greater than or equal to minimum height")

            self->window->setMaxHeight(maxHeight);
        }
        else if (value == Py_None) {
            self->window->setMaxHeight(INT_MAX);
        }
        else {
            RAISE_TYPE_ERROR(-1, "integer", value);
        }
        return 0;
    }
}

// Window Get & Set functions
namespace window {
    // Size
    static PyObject *set_size(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        int width, height;
        if (!PyArg_ParseTuple(args, "ii", &width, &height)) {
            return nullptr;
        }

        GP_CHECK_GT(width, 0, nullptr, "width must be greater than 0")
        GP_CHECK_GT(height, 0, nullptr, "height must be greater than 0")

        self->window->setSize(width, height);
        Py_RETURN_NONE;
    }

    static PyObject *get_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyTuple_Pack(2, PyLong_FromLong(self->window->getWidth()), PyLong_FromLong(self->window->getHeight()));
    }

    // Size Limits
    static PyObject *set_size_limits(WindowObject *self, PyObject *args, PyObject *kwds) {
        CHECK_ACTIVE(nullptr);

        int minWidth, minHeight;
        PyObject *tmp_width, *tmp_height;
        if (!PyArg_ParseTuple(args, "iiOO", &minWidth, &minHeight, &tmp_width, &tmp_height)) {
            return nullptr;
        }

        GP_CHECK_GE(minWidth, 0, nullptr, "minimum width must be greater than or equal to 0")
        GP_CHECK_GE(minHeight, 0, nullptr, "minimum height must be greater than or equal to 0")

        int maxWidth, maxHeight;
        if (PyLong_Check(tmp_width)) {
            maxWidth = (int) PyLong_AsLong(tmp_width);
        }
        else if (tmp_width == Py_None) {
            maxWidth = INT_MAX;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_width);
        }

        if (PyLong_Check(tmp_height)) {
            maxHeight = (int) PyLong_AsLong(tmp_height);
        }
        else if (tmp_height == Py_None) {
            maxHeight = INT_MAX;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_height);
        }

        GP_CHECK_GE(maxWidth, minWidth, nullptr, "maximum width must be greater than or equal to minimum width")
        GP_CHECK_GE(maxHeight, minHeight, nullptr, "maximum height must be greater than or equal to minimum height")

        self->window->setSizeLimits(minWidth, minHeight, maxWidth, maxHeight);
        Py_RETURN_NONE;
    }

    // Minimum Size
    static PyObject *set_min_size(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        int minWidth, minHeight;
        if (!PyArg_ParseTuple(args, "ii", &minWidth, &minHeight)) {
            return nullptr;
        }

        GP_CHECK_GE(minWidth, 0, nullptr, "minimum width must be greater than or equal to 0")
        GP_CHECK_GE(minHeight, 0, nullptr, "minimum height must be greater than or equal to 0")

        self->window->setMinSize(minWidth, minHeight);
        Py_RETURN_NONE;
    }

    static PyObject *get_min_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getMinWidth()),
                            PyLong_FromLong(self->window->getMinHeight()));
    }

    // Maximum Size
    static PyObject *set_max_size(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        PyObject *tmp_width, *tmp_height;
        if (!PyArg_ParseTuple(args, "OO", &tmp_width, &tmp_height)) {
            return nullptr;
        }

        int maxWidth, maxHeight;

        if (PyLong_Check(tmp_width)) {
            maxWidth = (int) PyLong_AsLong(tmp_width);
        }
        else if (tmp_width == Py_None) {
            maxWidth = INT_MAX;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_width);
        }

        if (PyLong_Check(tmp_height)) {
            maxHeight = (int) PyLong_AsLong(tmp_height);
        }
        else if (tmp_height == Py_None) {
            maxHeight = INT_MAX;
        }
        else {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_height);
        }

        GP_CHECK_GE(maxWidth, self->window->getMinWidth(), nullptr,
                    "maximum width must be greater than or equal to minimum width")
        GP_CHECK_GE(maxHeight, self->window->getMinHeight(), nullptr,
                    "maximum height must be greater than or equal to minimum height")

        self->window->setMaxSize(maxWidth, maxHeight);
        Py_RETURN_NONE;
    }

    static PyObject *get_max_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getMaxWidth()),
                            PyLong_FromLong(self->window->getMaxHeight()));
    }

    // Position
    static PyObject *set_position(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        int xpos, ypos;
        if (!PyArg_ParseTuple(args, "ii", &xpos, &ypos)) {
            return nullptr;
        }

        self->window->setPosition(xpos, ypos);
        Py_RETURN_NONE;
    }

    static PyObject *get_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyTuple_Pack(2, PyLong_FromLong(self->window->getXPos()), PyLong_FromLong(self->window->getYPos()));
    }

    // Aspect Ratio
    static PyObject *set_aspect_ratio(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        PyObject *tmp_numerator, *tmp_denominator;
        if (!PyArg_ParseTuple(args, "OO", &tmp_numerator, &tmp_denominator)) {
            return nullptr;
        }

        if (tmp_numerator == Py_None or tmp_denominator == Py_None) {
            self->window->setAspectRatio(-1, -1);
            Py_RETURN_NONE;
        }

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(tmp_numerator)) {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_numerator);
        }
        if (!PyLong_Check(tmp_denominator)) {
            RAISE_TYPE_ERROR(nullptr, "integer", tmp_denominator);
        }
        #endif

        int numerator = (int) PyLong_AsLong(tmp_numerator);
        int denominator = (int) PyLong_AsLong(tmp_denominator);

        GP_CHECK_GT(numerator, 0, nullptr, "aspect ratio numerator must be None or greater than 0")
        GP_CHECK_GT(denominator, 0, nullptr, "aspect ratio denominator must be None or greater than 0")

        self->window->setAspectRatio(numerator, denominator);
        Py_RETURN_NONE;
    }

    static PyObject *get_aspect_ratio(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        gp::AspectRatio value = self->window->getAspectRatio();
        return PyTuple_Pack(2, PyLong_FromLong(value.numerator), PyLong_FromLong(value.denominator));
    }

    // Frame size & Content Scale
    static PyObject *get_frame_size(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        gp::WindowFrame value = self->window->getFrameSize();
        return Py_BuildValue("iiii", value.left, value.top, value.right, value.bottom);
    }

    static PyObject *get_content_scale(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        gp::ContentScale value = self->window->getContentScale();
        return PyTuple_Pack(2, PyFloat_FromDouble(value.xScale), PyFloat_FromDouble(value.yScale));
    }

    static PyObject *get_framebuffer_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);

        gp::FramebufferSize value = self->window->getFramebufferSize();
        return PyTuple_Pack(2, PyLong_FromLong(value.width), PyLong_FromLong(value.height));
    }
}

namespace window {
    // Resizable
    static int set_resizable(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value);
        }
        #endif

        self->window->setResizable(value == Py_True);
        return 0;
    }

    static PyObject *is_resizable(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isResizable()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // Decorated
    static int set_decorated(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value);
        }
        #endif

        self->window->setDecorated(value == Py_True);
        return 0;
    }

    static PyObject *is_decorated(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isDecorated()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // Floating
    static int set_floating(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value);
        }
        #endif

        self->window->setFloating(value == Py_True);
        return 0;
    }

    static PyObject *is_floating(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isFloating()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    // Auto Minimized
    static int set_auto_minimized(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value);
        }
        #endif

        self->window->setAutoMinimized(value == Py_True);
        return 0;
    }

    static PyObject *is_auto_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isAutoMinimized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }


    // Focused on Show
    static int set_focused_on_show(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value);
        }
        #endif

        self->window->setFocusedOnShow(value == Py_True);
        return 0;
    }

    static PyObject *is_focused_on_show(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isFocusedOnShow()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
}

// Window States
namespace window {
    static PyObject *restore(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->restore();
        Py_RETURN_NONE;
    }

    static PyObject *is_fullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isFullscreen()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *fullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->fullscreen();
        Py_RETURN_NONE;
    }

    static PyObject *is_maximized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isMaximized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *maximize(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->maximize();
        Py_RETURN_NONE;
    }

    static PyObject *is_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isMinimized()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *minimize(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->minimize();
        Py_RETURN_NONE;
    }

    static PyObject *show(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->show();
        Py_RETURN_NONE;
    }

    static PyObject *hide(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->hide();
        Py_RETURN_NONE;
    }

    static PyObject *is_visible(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isVisible()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *focus(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->focus();
        Py_RETURN_NONE;
    }

    static PyObject *has_focus(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->hasFocus()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *request_attention(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        self->window->requestAttention();
        Py_RETURN_NONE;
    }
}

// Window Input Events
namespace window {
    static PyObject *is_mouse_hovering(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->isMouseHovering()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *get_mouse_position(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        auto pos = self->window->getMousePosition();
        return PyTuple_Pack(2, PyFloat_FromDouble(pos.x), PyFloat_FromDouble(pos.y));
    }

    static PyObject *set_cursor_mode(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        #if GP_TYPE_CHECKING
        if (!PyUnicode_Check(args)) {
            RAISE_TYPE_ERROR(nullptr, "string", args);
        }
        #endif

        const char *mode = PyUnicode_AsUTF8(args);

        if (strcmp(mode, "hidden") == 0) {
            self->window->setCursorMode(gp::CursorMode::Hidden);
        }
        else if (strcmp(mode, "disabled") == 0) {
            self->window->setCursorMode(gp::CursorMode::Disabled);
        }
        else if (strcmp(mode, "normal") == 0) {
            self->window->setCursorMode(gp::CursorMode::Normal);
        }
        else {
            RAISE_VALUE_ERROR(nullptr, "cursor mode must be one of 'normal', 'hidden', or 'disabled'");
        }

        Py_RETURN_NONE;
    }

    static PyObject *check_shift_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkShiftKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_control_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkControlKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_alt_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkAltKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_super_key(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkSuperKey()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_key(WindowObject *self, PyObject *arg) {
        CHECK_ACTIVE(nullptr);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "button", arg);
        }
        #endif

        if (self->window->checkKey((int) PyLong_AsLong(arg))) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_mouse_button(WindowObject *self, PyObject *arg) {
        CHECK_ACTIVE(nullptr);

        #if GP_TYPE_CHECKING
        if (!PyLong_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "button", arg);
        }
        #endif

        if (self->window->checkMouseButton((int) PyLong_AsLong(arg))) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_left_click(WindowObject *self, PyObject *Py_UNUSED(arg)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkLeftClick()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_middle_click(WindowObject *self, PyObject *Py_UNUSED(arg)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkMiddleClick()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *check_right_click(WindowObject *self, PyObject *Py_UNUSED(arg)) {
        CHECK_ACTIVE(nullptr);

        if (self->window->checkRightClick()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *set_key_callback(WindowObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        CHECK_ACTIVE(nullptr);

        PyObject *callback;
        int key;
        if (!PyArg_ParseTuple(args, "iO", &key, &callback)) {
            return nullptr;
        }

        auto indexi = self->key_callbacks.find(key);

        if (callback == Py_None) {
            if (indexi == self->key_callbacks.end()) {
                Py_RETURN_NONE;
            }

            Py_DECREF(indexi->second);
            self->key_callbacks.erase(indexi);
            self->window->setKeyCallback(key, nullptr);

            Py_RETURN_NONE;
        }

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(callback)) {
            RAISE_TYPE_ERROR(nullptr, "callable", callback);
        }
        #endif

        if (indexi == self->key_callbacks.end()) {
            Py_INCREF(callback);
            // TODO libc++abi: terminating with uncaught exception of type std::overflow_error: __next_prime overflow
            self->key_callbacks.insert({key, callback});
        }
        else {
            SET_PYOBJECT(indexi->second, callback);
        }

        self->window->setKeyCallback(key, [callback](gp::Window *window, int action) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallOneArg(callback, PyLong_FromLong(action));
            PyGILState_Release(gstate);
        });

        Py_RETURN_NONE;
    }

    static PyObject *set_mouse_button_callback(WindowObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_DEBUG("gp.window.Window.set_mouse_button_callback({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        CHECK_ACTIVE(nullptr);

        PyObject *callback;
        int button;
        if (!PyArg_ParseTuple(args, "iO", &button, &callback)) {
            return nullptr;
        }

        auto indexi = self->mouse_callbacks.find(button);

        if (callback == Py_None) {
            GP_PY_TRACE("gp.window.Window.set_mouse_button_callback() callback == Py_None");

            if (indexi == self->mouse_callbacks.end()) {
                Py_RETURN_NONE;
            }

            Py_DECREF(indexi->second);
            self->mouse_callbacks.erase(indexi);
            self->window->setMouseButtonCallback(button, nullptr);

            Py_RETURN_NONE;
        }

        GP_PY_TRACE("gp.window.Window.set_mouse_button_callback() callback != Py_None");

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(callback)) {
            RAISE_TYPE_ERROR(nullptr, "callable", callback);
        }
        #endif

        if (indexi == self->mouse_callbacks.end()) {
            GP_PY_TRACE("gp.window.Window.set_mouse_button_callback() inserting new callback");

            Py_INCREF(callback);
            // TODO libc++abi: terminating with uncaught exception of type std::overflow_error: __next_prime overflow
            self->mouse_callbacks.insert({button, callback});
        }
        else {
            GP_PY_TRACE("gp.window.Window.set_mouse_button_callback() replacing old callback");

            SET_PYOBJECT(indexi->second, callback);
        }

        self->window->setMouseButtonCallback(button, [callback](gp::Window *window, int action) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallOneArg(callback, action ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        Py_RETURN_NONE;
    }
}

// Window Callbacks
namespace window {
    // Resize
    static int set_resize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->resize_callback, value);

        if (value == Py_None) {
            self->window->setResizeCallback(nullptr);
            return 0;
        }

        self->window->setResizeCallback([self](gp::Window *window, int width, int height) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->resize_callback, "ii", width, height);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_resize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->resize_callback);
    }

    // Close
    static int set_close_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->close_callback, value);

        if (value == Py_None) {
            self->window->setCloseCallback(nullptr);
            return 0;
        }

        self->window->setCloseCallback([self](gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->close_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_close_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->close_callback);
    }

    // Destroy
    static int set_destroy_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->destroy_callback, value);

        if (value == Py_None) {
            self->window->setDestroyCallback(nullptr);
            return 0;
        }

        self->window->setDestroyCallback([self](gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->destroy_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_destroy_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->destroy_callback);
    }

    // Position
    static int set_position_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->position_callback, value);

        if (value == Py_None) {
            self->window->setPositionCallback(nullptr);
            return 0;
        }

        self->window->setPositionCallback([self](gp::Window *window, int xPos, int yPos) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->position_callback, "ii", xPos, yPos);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_position_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->position_callback);
    }

    // Minimize
    static int set_minimize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->minimize_callback, value);

        if (value == Py_None) {
            self->window->setMinimizeCallback(nullptr);
            return 0;
        }

        self->window->setMinimizeCallback([self](gp::Window *window, bool minimized) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->minimize_callback, "O", minimized ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_minimize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->minimize_callback);
    }

    // Maximize
    static int set_maximize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->maximize_callback, value);

        if (value == Py_None) {
            self->window->setMaximizeCallback(nullptr);
            return 0;
        }

        self->window->setMaximizeCallback([self](gp::Window *window, bool maximized) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->maximize_callback, "O", maximized ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_maximize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->maximize_callback);
    }

    // Focus
    static int set_focus_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->focus_callback, value);

        if (value == Py_None) {
            self->window->setFocusCallback(nullptr);
            return 0;
        }

        self->window->setFocusCallback([self](gp::Window *window, bool focused) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->focus_callback, "O", focused ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_focus_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->focus_callback);
    }

    // Refresh
    static int set_refresh_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->refresh_callback, value);

        if (value == Py_None) {
            self->window->setRefreshCallback(nullptr);
            return 0;
        }

        self->window->setRefreshCallback([self](gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->refresh_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_refresh_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->refresh_callback);
    }

    // Content Scale
    static int set_content_scale_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->content_scale_callback, value);

        if (value == Py_None) {
            self->window->setContentScaleCallback(nullptr);
            return 0;
        }

        self->window->setContentScaleCallback([self](gp::Window *window, float xScale, float yScale) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->content_scale_callback, "ff", xScale, yScale);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_content_scale_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->content_scale_callback);
    }

    // Framebuffer Size
    static int set_framebuffer_size_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->framebuffer_size_callback, value);

        if (value == Py_None) {
            self->window->setFramebufferSizeCallback(nullptr);
            return 0;
        }

        self->window->setFramebufferSizeCallback([self](gp::Window *window, int width, int height) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->framebuffer_size_callback, "ii", width, height);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_framebuffer_size_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->framebuffer_size_callback);
    }

    // Mouse Motion
    static int set_mouse_motion_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->mouse_motion_callback, value);

        if (value == Py_None) {
            self->window->setMouseMotionCallback(nullptr);
            return 0;
        }

        self->window->setMouseMotionCallback([self](gp::Window *window, float xPos, float yPos) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->mouse_motion_callback, "ff", xPos, yPos);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_mouse_motion_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->mouse_motion_callback);
    }

    // Mouse Enter
    static int set_mouse_enter_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->mouse_enter_callback, value);

        if (value == Py_None) {
            self->window->setMouseEnterCallback(nullptr);
            return 0;
        }

        self->window->setMouseEnterCallback([self](gp::Window *window, bool entered) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->mouse_enter_callback, "O", entered ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_mouse_enter_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->mouse_enter_callback);
    }

    // Scroll
    static int set_scroll_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value);
        }
                #endif

        SET_PYOBJECT(self->scroll_callback, value);

        if (value == Py_None) {
            self->window->setScrollCallback(nullptr);
            return 0;
        }

        self->window->setScrollCallback([self](gp::Window *window, float xScroll, float yScroll) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->scroll_callback, "ff", xScroll, yScroll);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_scroll_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->scroll_callback);
    }

    // Mouse Buttons
    static int set_left_click_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        if (set_mouse_button_callback(self, Py_BuildValue("iO", GP_MOUSE_LEFT_BUTTON, value), Py_None)) {
            return 0;
        }
        return -1;
    }

    static PyObject *get_left_click_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        auto indexi = self->mouse_callbacks.find(GP_MOUSE_LEFT_BUTTON);
        if (indexi == self->mouse_callbacks.end()) {
            Py_RETURN_NONE;
        }
        RETURN_PYOBJECT(indexi->second);
    }

    static int set_middle_click_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        if (set_mouse_button_callback(self, Py_BuildValue("iO", GP_MOUSE_MIDDLE_BUTTON, value), Py_None)) {
            return 0;
        }
        return -1;
    }

    static PyObject *get_middle_click_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        auto indexi = self->mouse_callbacks.find(GP_MOUSE_MIDDLE_BUTTON);
        if (indexi == self->mouse_callbacks.end()) {
            Py_RETURN_NONE;
        }
        RETURN_PYOBJECT(indexi->second);
    }

    static int set_right_click_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        if (set_mouse_button_callback(self, Py_BuildValue("iO", GP_MOUSE_RIGHT_BUTTON, value), Py_None)) {
            return 0;
        }
        return -1;
    }

    static PyObject *get_right_click_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        auto indexi = self->mouse_callbacks.find(GP_MOUSE_RIGHT_BUTTON);
        if (indexi == self->mouse_callbacks.end()) {
            Py_RETURN_NONE;
        }
        RETURN_PYOBJECT(indexi->second);
    }
}

// Static Window Methods
namespace window {
    static PyObject *update_all(WindowObject *Py_UNUSED(self), PyObject *args) {
        gp::Window::updateAll();
        Py_RETURN_NONE;
    }

    static PyObject *destroy_all(WindowObject *Py_UNUSED(self), PyObject *args) {
        gp::Window::destroyAll();
        Py_RETURN_NONE;
    }
}

// Window Type
namespace window {
    static PyMethodDef methods[] = {

            // Core Window Methods

            {"is_closed",                 (PyCFunction) is_closed,                 METH_NOARGS,
                    "Returns whether the Window is closed"},
            {"is_open",                   (PyCFunction) is_open,                   METH_NOARGS,
                    "Returns whether the Window is open"},

            {"update",                    (PyCFunction) update,                    METH_NOARGS,
                    "Update the Window"},
            {"destroy",                   (PyCFunction) destroy,                   METH_NOARGS,
                    "Destroys the Window"},

            // Window Get & Set Methods

            {"set_size",                  (PyCFunction) set_size,                  METH_VARARGS,
                    "Sets the Window's width and height"},
            {"set_size_limits",           (PyCFunction) set_size_limits,           METH_VARARGS,
                    "Sets the minimum and maximum size for the window"},
            {"set_min_size",              (PyCFunction) set_min_size,              METH_VARARGS,
                    "Sets the minimum size for the window"},
            {"set_max_size",              (PyCFunction) set_max_size,              METH_VARARGS,
                    "Sets the maximum size for the window"},

            {"set_position",              (PyCFunction) set_position,              METH_VARARGS,
                    "Sets the Window's x and y position"},

            {"set_aspect_ratio",          (PyCFunction) set_aspect_ratio,          METH_VARARGS,
                    "Sets the aspect ratio of the window"},
            {"get_aspect_ratio",          (PyCFunction) get_aspect_ratio,          METH_NOARGS,
                    "Returns a tuple (numerator, denominator) containing the aspect ratio of the window"},

            {"get_frame_size",            (PyCFunction) get_frame_size,            METH_NOARGS,
                    "Returns a tuple (left, top, right, bottom) containing the frame size of the window"},
            {"get_content_scale",         (PyCFunction) get_content_scale,         METH_NOARGS,
                    "Returns a tuple (xscale, yscale) containing the scale of the content on the window"},
            {"get_framebuffer_size",      (PyCFunction) get_framebuffer_size,      METH_NOARGS,
                    "Returns a tuple (width, height) containing the size of the Window's framebuffer"},

            // Window State Methods

            {"restore",                   (PyCFunction) restore,                   METH_NOARGS,
                    "Restores the Window"},
            {"fullscreen",                (PyCFunction) fullscreen,                METH_NOARGS,
                    "Makes the Window fullscreen"},
            {"is_fullscreen",             (PyCFunction) is_fullscreen,             METH_NOARGS,
                    "Returns if the Window is fullscreen"},
            {"maximize",                  (PyCFunction) maximize,                  METH_NOARGS,
                    "Maximizes the Window"},
            {"is_maximized",              (PyCFunction) is_maximized,              METH_NOARGS,
                    "Returns if the Window is maximized"},
            {"minimize",                  (PyCFunction) minimize,                  METH_NOARGS,
                    "Minimizes the Window"},
            {"is_minimized",              (PyCFunction) is_minimized,              METH_NOARGS,
                    "Returns if the Window is minimized"},

            {"show",                      (PyCFunction) show,                      METH_NOARGS,
                    "Makes the Window visible"},
            {"hide",                      (PyCFunction) hide,                      METH_NOARGS,
                    "Makes the Window invisible"},
            {"is_visible",                (PyCFunction) is_visible,                METH_NOARGS,
                    "Returns if the Window is visible"},

            {"focus",                     (PyCFunction) focus,                     METH_NOARGS,
                    "Sets the input focus to the Window"},
            {"has_focus",                 (PyCFunction) has_focus,                 METH_NOARGS,
                    "Returns whether the Window has input focus"},
            {"request_attention",         (PyCFunction) request_attention,         METH_NOARGS,
                    "Requests for user attention on the window"},

            // Window Input Events

            {"is_mouse_hovering",         (PyCFunction) is_mouse_hovering,         METH_NOARGS,
                    "Returns whether the mouse is hovering over the Window"},
            {"get_mouse_position",        (PyCFunction) get_mouse_position,        METH_NOARGS,
                    "Returns the position of the cursor as a tuple"},
            {"set_cursor_mode",           (PyCFunction) set_cursor_mode,           METH_O,
                    "Sets the cursor input mode"},

            {"check_shift_key",           (PyCFunction) check_shift_key,           METH_NOARGS,
                    "Returns whether the shift key is being pressed"},
            {"check_control_key",         (PyCFunction) check_control_key,         METH_NOARGS,
                    "Returns whether the control key is being pressed"},
            {"check_alt_key",             (PyCFunction) check_alt_key,             METH_NOARGS,
                    "Returns whether the alt key is being pressed"},
            {"check_super_key",           (PyCFunction) check_super_key,           METH_NOARGS,
                    "Returns whether the fromRGB key is being pressed"},

            {"check_key",                 (PyCFunction) check_key,                 METH_O,
                    "Returns whether the key specified is being pressed"},
            {"check_mouse_button",        (PyCFunction) check_mouse_button,        METH_O,
                    "Returns whether the mouse button specified is being pressed"},
            {"check_left_click",          (PyCFunction) check_left_click,          METH_NOARGS,
                    "Returns whether the left mouse button is being pressed"},
            {"check_middle_click",        (PyCFunction) check_middle_click,        METH_NOARGS,
                    "Returns whether the middle mouse button is being pressed"},
            {"check_right_click",         (PyCFunction) check_right_click,         METH_NOARGS,
                    "Returns whether the right mouse button is being pressed"},

            {"set_key_callback",          (PyCFunction) set_key_callback,          METH_VARARGS,
                    "Sets a callback function for a keyboard event"},
            {"set_mouse_button_callback", (PyCFunction) set_mouse_button_callback, METH_VARARGS,
                    "Sets a callback function for a mouse button event"},

            {"get_camera",                (PyCFunction) get_camera,                METH_NOARGS,
                    "Gets the camera object associated with the Window"},
            {"to_world",                  (PyCFunction) to_world,                  METH_VARARGS,
                    "Converts coordinates from screen space to world space"},
            {"to_screen",                 (PyCFunction) to_screen,                 METH_VARARGS,
                    "Converts coordinates from screen space to world space"},

            {"update_all",                (PyCFunction) update_all,                METH_STATIC | METH_NOARGS,
                    "Updates all currently active windows"},
            {"destroy_all",               (PyCFunction) destroy_all,               METH_STATIC | METH_NOARGS,
                    "Destroys all currently active windows"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {"width",                     (getter) get_width,                     (setter) set_width,                     "width",                     nullptr},
            {"height",                    (getter) get_height,                    (setter) set_height,                    "height",                    nullptr},
            {"title",                     (getter) get_title,                     (setter) set_title,                     "title",                     nullptr},

            {"xpos",                      (getter) get_xpos,                      (setter) set_xpos,                      "x position",                nullptr},
            {"ypos",                      (getter) get_ypos,                      (setter) set_ypos,                      "y position",                nullptr},

            {"background",                (getter) get_background,                (setter) set_background,                "background",                nullptr},

            {"min_width",                 (getter) get_min_width,                 (setter) set_min_width,                 "minimum width",             nullptr},
            {"max_width",                 (getter) get_max_width,                 (setter) set_max_width,                 "maximum width",             nullptr},
            {"min_height",                (getter) get_min_height,                (setter) set_min_height,                "minimum height",            nullptr},
            {"max_height",                (getter) get_max_height,                (setter) set_max_height,                "maximum height",            nullptr},

            {"resizable",                 (getter) is_resizable,                  (setter) set_resizable,                 "resizable",                 nullptr},
            {"decorated",                 (getter) is_decorated,                  (setter) set_decorated,                 "decorated",                 nullptr},
            {"auto_minimized",            (getter) is_auto_minimized,             (setter) set_auto_minimized,            "auto minimized",            nullptr},
            {"floating",                  (getter) is_floating,                   (setter) set_floating,                  "floating",                  nullptr},
            {"focused_on_show",           (getter) is_focused_on_show,            (setter) set_focused_on_show,           "focused on show",           nullptr},

            {"resize_callback",           (getter) get_resize_callback,           (setter) set_resize_callback,           "resize callback",           nullptr},
            {"position_callback",         (getter) get_position_callback,         (setter) set_position_callback,         "position callback",         nullptr},
            {"framebuffer_size_callback", (getter) get_framebuffer_size_callback, (setter) set_framebuffer_size_callback, "framebuffer size callback", nullptr},
            {"close_callback",            (getter) get_close_callback,            (setter) set_close_callback,            "close callback",            nullptr},
            {"content_scale_callback",    (getter) get_content_scale_callback,    (setter) set_content_scale_callback,    "content scale callback",    nullptr},
            {"destroy_callback",          (getter) get_destroy_callback,          (setter) set_destroy_callback,          "destroy callback",          nullptr},
            {"minimize_callback",         (getter) get_minimize_callback,         (setter) set_minimize_callback,         "minimize callback",         nullptr},
            {"maximize_callback",         (getter) get_maximize_callback,         (setter) set_maximize_callback,         "maximize callback",         nullptr},
            {"focus_callback",            (getter) get_focus_callback,            (setter) set_focus_callback,            "focus callback",            nullptr},
            {"refresh_callback",          (getter) get_refresh_callback,          (setter) set_refresh_callback,          "refresh callback",          nullptr},
            {"mouse_motion_callback",     (getter) get_mouse_motion_callback,     (setter) set_mouse_motion_callback,     "mouse motion callback",     nullptr},
            {"mouse_enter_callback",      (getter) get_mouse_enter_callback,      (setter) set_mouse_enter_callback,      "mouse enter callback",      nullptr},
            {"scroll_callback",           (getter) get_scroll_callback,           (setter) set_scroll_callback,           "scroll callback",           nullptr},

            {"left_click_callback",       (getter) get_left_click_callback,       (setter) set_left_click_callback,       "left click callback",       nullptr},
            {"middle_click_callback",     (getter) get_middle_click_callback,     (setter) set_middle_click_callback,     "middle click callback",     nullptr},
            {"right_click_callback",      (getter) get_right_click_callback,      (setter) set_right_click_callback,      "right click callback",      nullptr},

            {nullptr}
    };
}

PyTypeObject WindowType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Window",
        .tp_basicsize = sizeof(WindowObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = window::new_,
        .tp_init = (initproc) window::init,

        .tp_methods = window::methods,
        .tp_getset = window::getsetters,

        .tp_traverse = (traverseproc) window::traverse,
        .tp_clear = (inquiry) window::clear,
        .tp_dealloc = (destructor) window::dealloc,

        .tp_repr = (reprfunc) window::repr,
};

static struct PyModuleDef windowmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "window",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_window(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_window()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&windowmodule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing color

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_window() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    // Importing camera

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_window() - import_camera()" << std::endl;
    #endif
    PyCamera_API = (void **) PyCapsule_Import("goopylib.ext.camera._C_API", 0);
    if (PyCamera_API == nullptr) {
        return nullptr;
    }

    CameraType = Camera_pytype();

    // Exposing class

    EXPOSE_PYOBJECT_CLASS(WindowType, "Window");

    // Exposing capsule

    static void *PyWindow_API[PyWindow_API_pointers];
    PyObject *c_api_object;

    PyWindow_API[Window_pytype_NUM] = (void *) Window_pytype;
    c_api_object = PyCapsule_New((void *) PyWindow_API, "goopylib.ext.window._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
