#define GP_LOGGING_LEVEL 3
#include "goopylib/debug.h"

#define WINDOW_MODULE

#include "window.h"

#include <memory>
#include "window_object.h"
#include "window_module.h"
#include "window_capsule.h"

#include "goopylib/color/color_object.h"
#include "goopylib/color/color_module.h"

#include "goopylib/scene/camera_object.h"
#include "goopylib/scene/camera_module.h"

#include "src/goopylib/core/Window.h"
#include "src/platform/events/MouseCodes.h"

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
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        WindowObject *self;
        self = (WindowObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {
            INITIALIZE_PYOBJECT(self->resize_callback, Py_None);
            INITIALIZE_PYOBJECT(self->close_callback, Py_None);
            INITIALIZE_PYOBJECT(self->destroy_callback, Py_None);
            INITIALIZE_PYOBJECT(self->position_callback, Py_None);
            INITIALIZE_PYOBJECT(self->content_scale_callback, Py_None);
            INITIALIZE_PYOBJECT(self->framebuffer_size_callback, Py_None);
            INITIALIZE_PYOBJECT(self->minimize_callback, Py_None);
            INITIALIZE_PYOBJECT(self->maximize_callback, Py_None);
            INITIALIZE_PYOBJECT(self->focus_callback, Py_None);
            INITIALIZE_PYOBJECT(self->refresh_callback, Py_None);
            INITIALIZE_PYOBJECT(self->mouse_motion_callback, Py_None);
            INITIALIZE_PYOBJECT(self->mouse_enter_callback, Py_None);
            INITIALIZE_PYOBJECT(self->scroll_callback, Py_None);

            INITIALIZE_PYOBJECT(self->background, Py_None);
            INITIALIZE_PYOBJECT(self->camera, Py_None);

            self->key_callbacks = PyDict_New();
            self->mouse_callbacks = PyDict_New();
        }
        return (PyObject *) self;
    }

    static int init(WindowObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.window.Window()");

        PyObject * tmp;
        int width, height;
        if (!PyArg_ParseTuple(args, "iiU", &width, &height, &tmp)) {
            return -1;
        }

        GP_CHECK_GT(width, 0, -1, "width must be greater than 0")
        GP_CHECK_GT(height, 0, -1, "height must be greater than 0")

        self->background = PyObject_CallObject((PyObject *) ColorType, Py_BuildValue("iii", 255, 255, 255));

        self->window = unique_ptr<gp::Window>(new gp::Window(width, height, PyUnicode_AsUTF8(tmp)));
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

        Py_VISIT(self->key_callbacks);
        Py_VISIT(self->mouse_callbacks);

        return 0;
    }

    static int clear(WindowObject *self) {
        GP_PY_TRACE("gp.window.Window.clear()");

        self->window.reset();

        GP_PY_TRACE("gp.window.Window.__dealloc__() decreasing callback references");
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

        GP_PY_TRACE("gp.window.Window.__dealloc__() decreasing background reference");
        Py_CLEAR(self->background);

        GP_PY_TRACE("gp.window.Window.__dealloc__() decreasing key & mouse callback references");
        Py_CLEAR(self->key_callbacks);
        Py_CLEAR(self->mouse_callbacks);

        return 0;
    }

    static void dealloc(WindowObject *self) {
        GP_PY_DEBUG("gp.window.Window.__dealloc__()");

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

        const int width = (int) PyLong_AsLong(value);

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

        const int height = (int) PyLong_AsLong(value);

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

    // Position
    static int set_position(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_TRACE("gp.window.Window.set_position({0})", PyUnicode_AsUTF8(PyObject_Repr(value)));

        CHECK_ACTIVE(-1);

        int xpos, ypos;
        if (!PyArg_ParseTuple(value, "(ii)", &xpos, &ypos)) {
            RAISE_TYPE_ERROR(-1, "tuple of integer", value);
        }

        self->window->setPosition(xpos, ypos);
        return 0;
    }

    static PyObject *get_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);
        return PyTuple_Pack(2, PyLong_FromLong(self->window->getXPos()), PyLong_FromLong(self->window->getYPos()));
    }

    // Background
    static int set_background(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(-1);

        if (isinstance(value, ColorType)) {
            SET_PYOBJECT(self->background, value);
        }
        else {
            PyObject * tmp = self->background;
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

        const int minWidth = (int) PyLong_AsLong(value);

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

        const int minHeight = (int) PyLong_AsLong(value);
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
            const int maxWidth = (int) PyLong_AsLong(value);

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
            const int maxHeight = (int) PyLong_AsLong(value);

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
    static PyObject *set_size_limits(WindowObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        CHECK_ACTIVE(nullptr);

        int minWidth, minHeight;
        PyObject * tmp_width, *tmp_height;
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

        PyObject * tmp_width, *tmp_height;
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

    // Aspect Ratio
    static PyObject *set_aspect_ratio(WindowObject *self, PyObject *args) {
        CHECK_ACTIVE(nullptr);

        PyObject * tmp_numerator, *tmp_denominator;
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

        const int numerator = (int) PyLong_AsLong(tmp_numerator);
        const int denominator = (int) PyLong_AsLong(tmp_denominator);

        GP_CHECK_GT(numerator, 0, nullptr, "aspect ratio numerator must be None or greater than 0")
        GP_CHECK_GT(denominator, 0, nullptr, "aspect ratio denominator must be None or greater than 0")

        self->window->setAspectRatio(numerator, denominator);
        Py_RETURN_NONE;
    }

    static PyObject *get_aspect_ratio(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        const gp::AspectRatio value = self->window->getAspectRatio();
        return PyTuple_Pack(2, PyLong_FromLong(value.numerator), PyLong_FromLong(value.denominator));
    }

    // Frame size & Content Scale
    static PyObject *get_frame_size(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        const gp::WindowFrame value = self->window->getFrameSize();
        return Py_BuildValue("iiii", value.left, value.top, value.right, value.bottom);
    }

    static PyObject *get_content_scale(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_ACTIVE(nullptr);

        const gp::ContentScale value = self->window->getContentScale();
        return PyTuple_Pack(2, PyFloat_FromDouble(value.xScale), PyFloat_FromDouble(value.yScale));
    }

    static PyObject *get_framebuffer_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_ACTIVE(nullptr);

        const gp::FramebufferSize value = self->window->getFramebufferSize();
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

    static PyObject *get_resizable(WindowObject *self, PyObject *Py_UNUSED(args)) {
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

    static PyObject *get_decorated(WindowObject *self, PyObject *Py_UNUSED(args)) {
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

    static PyObject *get_floating(WindowObject *self, PyObject *Py_UNUSED(args)) {
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

    static PyObject *get_auto_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
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

    static PyObject *get_focused_on_show(WindowObject *self, PyObject *Py_UNUSED(args)) {
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

    static PyObject *hide(WindowObject *self, PyObject *arg) {
        CHECK_ACTIVE(nullptr);

        self->window->hide(arg == Py_True);
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

        PyObject * callback;
        PyObject * key;
        if (!PyArg_ParseTuple(args, "O!O", &PyLong_Type, &key, &callback)) {
            return nullptr;
        }

        if (callback == Py_None) {
            PyDict_SetItem(self->key_callbacks, key, callback);
            self->window->setKeyCallback((int) PyLong_AsLong(key), nullptr);

            Py_RETURN_NONE;
        }

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(callback)) {
            RAISE_TYPE_ERROR(nullptr, "callable", callback);
        }
        #endif

        PyDict_SetItem(self->key_callbacks, key, callback);

        self->window->setKeyCallback(
                (int) PyLong_AsLong(key),
                [callback](gp::Window *Py_UNUSED(window), int action) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
                    PyObject_CallFunction(callback, "i", action);
                    PyGILState_Release(gstate);
                });

        Py_RETURN_NONE;
    }

    static PyObject *set_mouse_button_callback(WindowObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_DEBUG("gp.window.Window.set_mouse_button_callback({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        CHECK_ACTIVE(nullptr);

        PyObject * callback;
        PyObject * button;
        if (!PyArg_ParseTuple(args, "O!O", &PyLong_Type, &button, &callback)) {
            return nullptr;
        }

        if (callback == Py_None) {
            PyDict_SetItem(self->mouse_callbacks, button, callback);
            self->window->setMouseButtonCallback((int) PyLong_AsLong(button), nullptr);

            Py_RETURN_NONE;
        }

        #if GP_TYPE_CHECKING
        if (!PyCallable_Check(callback)) {
            RAISE_TYPE_ERROR(nullptr, "callable", callback);
        }
        #endif

        PyDict_SetItem(self->mouse_callbacks, button, callback);

        self->window->setMouseButtonCallback(
                (int) PyLong_AsLong(button),
                [callback](gp::Window *Py_UNUSED(window), int action) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
                    PyObject_CallFunction(callback, "O", action ? Py_True : Py_False);
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

        self->window->setResizeCallback(
                [self](gp::Window *Py_UNUSED(window), int width, int height) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setCloseCallback(
                [self](gp::Window *Py_UNUSED(window)) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
                    PyObject_Call(self->close_callback, Py_None, nullptr);
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

        self->window->setDestroyCallback(
                [self](gp::Window *Py_UNUSED(window)) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
                    PyObject_Call(self->destroy_callback, Py_None, nullptr);
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

        self->window->setPositionCallback(
                [self](gp::Window *Py_UNUSED(window), int xPos, int yPos) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setMinimizeCallback(
                [self](gp::Window *Py_UNUSED(window), bool minimized) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setMaximizeCallback(
                [self](gp::Window *Py_UNUSED(window), bool maximized) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setFocusCallback([self](gp::Window *Py_UNUSED(window), bool focused) {
            const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setRefreshCallback(
                [self](gp::Window *Py_UNUSED(window)) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
                    PyObject_Call(self->refresh_callback, Py_None, nullptr);
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

        self->window->setContentScaleCallback([self](gp::Window *Py_UNUSED(window), float xScale, float yScale) {
            const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setFramebufferSizeCallback(
                [self](gp::Window *Py_UNUSED(window), int width, int height) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setMouseMotionCallback(
                [self](gp::Window *Py_UNUSED(window), float xPos, float yPos) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setMouseEnterCallback(
                [self](gp::Window *Py_UNUSED(window), bool entered) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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

        self->window->setScrollCallback(
                [self](gp::Window *Py_UNUSED(window), float xScroll, float yScroll) {
                    const PyGILState_STATE gstate = PyGILState_Ensure();
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
        if (set_mouse_button_callback(self, Py_BuildValue("iO", GP_MOUSE_LEFT_BUTTON, value), nullptr)) {
            return 0;
        }
        return -1;
    }

    static PyObject *get_left_click_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        PyObject * button = PyLong_FromLong(GP_MOUSE_LEFT_BUTTON);

        if (PyDict_Contains(self->mouse_callbacks, button)) {
            RETURN_PYOBJECT(PyDict_GetItem(self->mouse_callbacks, button));
        }
        Py_RETURN_NONE;
    }

    static int set_middle_click_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        if (set_mouse_button_callback(self, Py_BuildValue("iO", GP_MOUSE_MIDDLE_BUTTON, value), nullptr)) {
            return 0;
        }
        return -1;
    }

    static PyObject *get_middle_click_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        PyObject * button = PyLong_FromLong(GP_MOUSE_MIDDLE_BUTTON);

        if (PyDict_Contains(self->mouse_callbacks, button)) {
            RETURN_PYOBJECT(PyDict_GetItem(self->mouse_callbacks, button));
        }
        Py_RETURN_NONE;
    }

    static int set_right_click_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        if (set_mouse_button_callback(self, Py_BuildValue("iO", GP_MOUSE_RIGHT_BUTTON, value), nullptr)) {
            return 0;
        }
        return -1;
    }

    static PyObject *get_right_click_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        PyObject * button = PyLong_FromLong(GP_MOUSE_RIGHT_BUTTON);

        if (PyDict_Contains(self->mouse_callbacks, button)) {
            RETURN_PYOBJECT(PyDict_GetItem(self->mouse_callbacks, button));
        }
        Py_RETURN_NONE;
    }
}

// Static Window Methods
namespace window {
    static PyObject *update_all(WindowObject *Py_UNUSED(self), PyObject *Py_UNUSED(args)) {
        gp::Window::updateAll();
        Py_RETURN_NONE;
    }

    static PyObject *destroy_all(WindowObject *Py_UNUSED(self), PyObject *Py_UNUSED(args)) {
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
            {"hide",                      (PyCFunction) hide,                      METH_O,
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
            GETTER_SETTER(width),
            GETTER_SETTER(height),
            GETTER_SETTER(title),

            GETTER_SETTER(xpos),
            GETTER_SETTER(ypos),
            GETTER_SETTER(position),

            GETTER_SETTER(background),

            GETTER_SETTER(min_width),
            GETTER_SETTER(max_width),
            GETTER_SETTER(min_height),
            GETTER_SETTER(max_height),

            GETTER_SETTER(resizable),
            GETTER_SETTER(decorated),
            GETTER_SETTER(auto_minimized),
            GETTER_SETTER(floating),
            GETTER_SETTER(focused_on_show),

            GETTER_SETTER(resize_callback),
            GETTER_SETTER(position_callback),
            GETTER_SETTER(framebuffer_size_callback),
            GETTER_SETTER(content_scale_callback),

            GETTER_SETTER(close_callback),
            GETTER_SETTER(destroy_callback),

            GETTER_SETTER(minimize_callback),
            GETTER_SETTER(maximize_callback),
            GETTER_SETTER(focus_callback),
            GETTER_SETTER(refresh_callback),

            GETTER_SETTER(mouse_motion_callback),
            GETTER_SETTER(mouse_enter_callback),
            GETTER_SETTER(scroll_callback),

            GETTER_SETTER(left_click_callback),
            GETTER_SETTER(middle_click_callback),
            GETTER_SETTER(right_click_callback),

            {nullptr}
    };
}

PyTypeObject WindowType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Window",
        sizeof(WindowObject),
        0,
        (destructor) window::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) window::repr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        "",
        (traverseproc) window::traverse,
        (inquiry) window::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        (PyMethodDef *) window::methods,
        nullptr,
        (PyGetSetDef *) window::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) window::init,
        nullptr,
        window::new_,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        nullptr,
        nullptr
};

static struct PyModuleDef WindowModule = {
        PyModuleDef_HEAD_INIT,
        "window",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_window(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_window()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&WindowModule);
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
    PyObject * c_api_object;

    PyWindow_API[Window_pytype_NUM] = (void *) Window_pytype;
    c_api_object = PyCapsule_New((void *) PyWindow_API, "goopylib.ext.window._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
