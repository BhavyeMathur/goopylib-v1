#pragma once

#include <Python.h>
#include "pch.h"
#include "util.h"

#include <goopylib/Core/Base.h>
#include <goopylib/Core/Window.h>
#include <Platform/Independent/BaseWindow.h>

#if GP_ERROR_CHECKING
#define CHECK_WINDOW_ACTIVE(val) \
if (self->window->isDestroyed()) { \
    PyErr_SetString(PyExc_RuntimeError, "window has been destroyed"); \
    return val; \
}
#else
#define CHECK_WINDOW_ACTIVE(val)
#endif

struct WindowObject {
    PyObject_HEAD
    std::unique_ptr<gp::Window> window;
    gp::WindowConfig config;

    PyObject *resize_callback;
    PyObject *close_callback;
    PyObject *destroy_callback;
    PyObject *position_callback;
    PyObject *content_scale_callback;
    PyObject *framebuffer_size_callback;
    PyObject *minimize_callback;
    PyObject *maximize_callback;
    PyObject *focus_callback;
    PyObject *refresh_callback;
};

// Window Core
namespace window {
    static int init(WindowObject *self, PyObject *args, PyObject *kwds) {
        GP_PY_INFO("Initializing gp.Window()");

        static const char *kwlist[] = {"width", "height", "title", nullptr};

        PyObject *tmp = nullptr;
        self->config = gp::WindowConfig();
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "II|U", (char **) kwlist, &self->config.width,
                                         &self->config.height, &tmp)) {
            return -1;
        }
        if (tmp) {
            self->config.title = PyUnicode_AsUTF8(tmp);
        }

        self->window = std::unique_ptr<gp::Window>(new gp::Window(self->config));

        GP_PY_TRACE("Initialized gp.Window()");

        return 0;
    }

    static PyObject *repr(WindowObject *self) {
        if (self->window->isDestroyed()) {
            return PyUnicode_FromString("Destroyed Window()");
        } else {
            return PyUnicode_FromFormat("Window(width=%i, height=%i, title='%s')",
                                        self->window->getWidth(), self->window->getHeight(), self->window->getTitle());
        }
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

        return 0;
    }

    static int clear(WindowObject *self) {
        GP_PY_TRACE("Clearing gp.Window()");

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

        self->window.reset();
        return 0;
    }

    static void dealloc(WindowObject *self) {
        GP_PY_INFO("Deallocating gp.Window()");

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

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Window Methods
namespace window {
    static PyObject *is_open(WindowObject *self, PyObject *Py_UNUSED(args)) {
        if (self->window->isClosed()) { Py_RETURN_FALSE; }
        Py_RETURN_TRUE;
    }

    static PyObject *is_closed(WindowObject *self, PyObject *Py_UNUSED(args)) {
        if (self->window->isClosed()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    static PyObject *update(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        self->window->update();
        Py_RETURN_NONE;
    }

    static PyObject *destroy(WindowObject *self, PyObject *Py_UNUSED(args)) {
        self->window->destroy();
        Py_RETURN_NONE;
    }
}

// Window States
namespace window {
    static PyObject *is_fullscreen(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isFullscreen()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    static PyObject *is_maximized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isMaximized()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    static PyObject *is_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isMinimized()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    static PyObject *is_visible(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isVisible()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }
}

// Window Getter & Setters
namespace window {
    // Resizable
    static int set_resizable(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setResizable(value == Py_True);
        return 0;
    }

    static PyObject *is_resizable(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isResizable()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    // Decorated
    static int set_decorated(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setDecorated(value == Py_True);
        return 0;
    }

    static PyObject *is_decorated(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isDecorated()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    // Floating
    static int set_floating(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setFloating(value == Py_True);
        return 0;
    }

    static PyObject *is_floating(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isFloating()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    // Auto Minimized
    static int set_auto_minimized(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setAutoMinimized(value == Py_True);
        return 0;
    }

    static PyObject *is_auto_minimized(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isAutoMinimized()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }


    // Focused on Show
    static int set_focused_on_show(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyBool_Check(value)) {
            RAISE_TYPE_ERROR(-1, "boolean", value)
        }
        #endif

        self->window->setFocusedOnShow(value == Py_True);
        return 0;
    }

    static PyObject *is_focused_on_show(WindowObject *self, PyObject *Py_UNUSED(args)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        if (self->window->isFocusedOnShow()) { Py_RETURN_TRUE; }
        Py_RETURN_FALSE;
    }

    // -------------------------------------------------------------------------------------------------------------

    // Width
    static PyObject *get_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getWidth());
    }

    static int set_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        unsigned int width = (unsigned int) PyLong_AsLong(value);

        #if GP_ERROR_CHECKING
        if (width <= 0) {
            RAISE_VALUE_ERROR(-1, "width must be greater than 0")
        }
        #endif

        self->window->setWidth(width);
        return 0;
    }

    // Height
    static PyObject *get_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getHeight());
    }

    static int set_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        #endif

        unsigned int height = (unsigned int) PyLong_AsLong(value);

        #if GP_ERROR_CHECKING
        if (height <= 0) {
            RAISE_VALUE_ERROR(-1, "height must be greater than 0")
        }
        #endif

        self->window->setHeight(height);
        return 0;
    }

    // Minimum Width
    static PyObject *get_min_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMinimumWidth());
    }

    static int set_min_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            unsigned int minWidth = (unsigned int) PyLong_AsLong(value);

            #if GP_ERROR_CHECKING
            if (minWidth < 0) {
                RAISE_VALUE_ERROR(-1, "minimum width must be greater than or equal to 0")
            }
            #endif

            self->window->setMinimumWidth(minWidth);
        } else if (value == Py_None) {
            self->window->setMinimumWidth(0);
        } else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // Minimum Height
    static PyObject *get_min_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMinimumHeight());
    }

    static int set_min_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            unsigned int minHeight = (unsigned int) PyLong_AsLong(value);
            #if GP_ERROR_CHECKING
            if (minHeight < 0) {
                RAISE_VALUE_ERROR(-1, "minimum height must be greater than or equal to 0")
            }
            #endif

            self->window->setMinimumHeight(minHeight);
        } else if (value == Py_None) {
            self->window->setMinimumHeight(0);
        } else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // Maximum Width
    static PyObject *get_max_width(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMaximumWidth());
    }

    static int set_max_width(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            int maxWidth = (int) PyLong_AsLong(value);

            #if GP_ERROR_CHECKING
            // The greater than 0 case must be checked because the minimum width for no value is -1
            // thus an input of 0 would pass the next test if min_width was never set
            if (maxWidth < 0) {
                RAISE_VALUE_ERROR(-1, "maximum width must be greater than or equal to 0")
            }
            if (maxWidth < self->window->getMinimumWidth()) {
                RAISE_VALUE_ERROR(-1, "maximum width must be greater than or equal to minimum width")
            }
            #endif

            self->window->setMaximumWidth(maxWidth);
        } else if (value == Py_None) {
            self->window->setMaximumWidth(MAX_WIDTH);
        } else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // Maximum Height
    static PyObject *get_max_height(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)
        return PyLong_FromLong(self->window->getMaximumHeight());
    }

    static int set_max_height(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (PyLong_Check(value)) {
            int maxHeight = (int) PyLong_AsLong(value);

            #if GP_ERROR_CHECKING
            // the greater than 0 case must be checked because the minimum height for no value is -1
            // thus an input of 0 would pass the next test if min_height was never set
            if (maxHeight < 0) {
                RAISE_VALUE_ERROR(-1, "maximum height must be greater than or equal to 0")
            }
            if (maxHeight < self->window->getMinimumHeight()) {
                RAISE_VALUE_ERROR(-1, "maximum height must be greater than or equal to minimum height")
            }
            #endif

            self->window->setMaximumHeight(maxHeight);
        } else if (value == Py_None) {
            self->window->setMaximumHeight(MAX_HEIGHT);
        } else {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }
        return 0;
    }

    // X Position
    static int set_x_position(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }

        self->window->setXPos((int) PyLong_AsLong(value));
        return 0;
    }

    static PyObject *get_x_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyLong_FromLong(self->window->getXPos());
    }

    // Y Position
    static int set_y_position(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        if (!PyLong_Check(value)) {
            RAISE_TYPE_ERROR(-1, "integer", value)
        }

        self->window->setYPos((int) PyLong_AsLong(value));
        return 0;
    }

    static PyObject *get_y_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyLong_FromLong(self->window->getYPos());
    }

    // Title
    static int set_title(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyUnicode_Check(value)) {
            RAISE_TYPE_ERROR(-1, "string argument expected, got %S", PyObject_Type(value))
        }
        #endif

        self->window->setTitle(PyUnicode_AsUTF8(value));
        return 0;
    }

    static PyObject *get_title(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyUnicode_FromString(self->window->getTitle());
    }
}

// Window Get & Set functions
namespace window {
    // Position
    static PyObject *set_position(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        int x_position, y_position;
        if (!PyArg_ParseTuple(args, "ii", &x_position, &y_position)) {
            return nullptr;
        }

        self->window->setPosition(x_position, y_position);
        Py_RETURN_NONE;
    }

    static PyObject *get_position(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getXPos()), PyLong_FromLong(self->window->getYPos()));
    }

    // Size
    static PyObject *set_size(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        int width, height;
        if (!PyArg_ParseTuple(args, "ii", &width, &height)) {
            return nullptr;
        }

        #if GP_ERROR_CHECKING
        if (width <= 0) {
            RAISE_VALUE_ERROR(nullptr, "width must be greater than 0")
        }
        if (height <= 0) {
            RAISE_VALUE_ERROR(nullptr, "height must be greater than 0")
        }
        #endif

        self->window->setSize(width, height);
        Py_RETURN_NONE;
    }

    static PyObject *get_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getWidth()), PyLong_FromLong(self->window->getHeight()));
    }

    // Size Limits
    static PyObject *set_size_limits(WindowObject *self, PyObject *args, PyObject *kwds) {
        CHECK_WINDOW_ACTIVE(nullptr)

        static const char *kwlist[] = {"min_width", "min_height", "max_width", "max_height", nullptr};

        PyObject *min_width, *min_height, *max_width, *max_height;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "OOOO", (char **) kwlist, &min_width, &min_height, &max_width,
                                         &max_height)) {
            return nullptr;
        }

        unsigned int tmp_min_width, tmp_min_height, tmp_max_width, tmp_max_height;
        if (PyLong_Check(min_width)) {
            tmp_min_width = (unsigned int) PyLong_AsLong(min_width);
        } else if (min_width == Py_None) {
            tmp_min_width = 0;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_width)
        }

        if (PyLong_Check(max_width)) {
            tmp_max_width = (unsigned int) PyLong_AsLong(max_width);
        } else if (max_width == Py_None) {
            tmp_max_width = MAX_WIDTH;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_width)
        }

        if (PyLong_Check(min_height)) {
            tmp_min_height = (int) PyLong_AsLong(min_height);
        } else if (min_height == Py_None) {
            tmp_min_height = 0;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_height)
        }

        if (PyLong_Check(max_height)) {
            tmp_max_height = (int) PyLong_AsLong(max_height);
        } else if (max_height == Py_None) {
            tmp_max_height = MAX_HEIGHT;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_height)
        }

        #if GP_ERROR_CHECKING
        if (tmp_min_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum width must be greater than or equal to 0")
        }
        if (tmp_max_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to 0")
        }
        if (tmp_max_width < tmp_min_width) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to minimum width")
        }

        if (tmp_min_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum height must be greater than or equal to 0")
        }
        if (tmp_max_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to 0")
        }
        if (tmp_max_height < tmp_min_height) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to minimum height")
        }
        #endif

        self->window->setSizeLimits(tmp_min_width, tmp_min_height,
                                    tmp_max_width, tmp_max_height);
        Py_RETURN_NONE;
    }

    // Minimum Size
    static PyObject *set_minimum_size(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        PyObject *min_width, *min_height;
        if (!PyArg_ParseTuple(args, "OO", &min_width, &min_height)) {
            return nullptr;
        }

        unsigned int tmp_width, tmp_height;

        if (PyLong_Check(min_width)) {
            tmp_width = (unsigned int) PyLong_AsLong(min_width);
        } else if (min_width == Py_None) {
            tmp_width = 0;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_width)
        }

        if (PyLong_Check(min_height)) {
            tmp_height = (unsigned int) PyLong_AsLong(min_height);
        } else if (min_height == Py_None) {
            tmp_height = 0;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", min_height)
        }

        #if GP_ERROR_CHECKING
        if (tmp_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum width must be greater than or equal to 0")
        }
        if (tmp_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "minimum height must be greater than or equal to 0")
        }
        #endif

        self->window->setMinimumSize(tmp_width, tmp_height);
        Py_RETURN_NONE;
    }

    static PyObject *get_minimum_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getMinimumWidth()),
                            PyLong_FromLong(self->window->getMinimumHeight()));
    }

    // Maximum Size
    static PyObject *set_maximum_size(WindowObject *self, PyObject *args) {
        CHECK_WINDOW_ACTIVE(nullptr)

        PyObject *max_width, *max_height;
        if (!PyArg_ParseTuple(args, "OO", &max_width, &max_height)) {
            return nullptr;
        }

        unsigned int tmp_width, tmp_height;

        if (PyLong_Check(max_width)) {
            tmp_width = (unsigned int) PyLong_AsLong(max_width);
        } else if (max_width == Py_None) {
            tmp_width = MAX_WIDTH;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_width)
        }

        if (PyLong_Check(max_height)) {
            tmp_height = (int) PyLong_AsLong(max_height);
        } else if (max_height == Py_None) {
            tmp_height = MAX_HEIGHT;
        } else {
            RAISE_TYPE_ERROR(nullptr, "integer", max_height)
        }

        #if GP_ERROR_CHECKING
        if (tmp_width < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to 0")
        }
        if (tmp_width < self->window->getMinimumWidth()) {
            RAISE_VALUE_ERROR(nullptr, "maximum width must be greater than or equal to minimum width")
        }

        if (tmp_height < 0) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to 0")
        }
        if (tmp_height < self->window->getMinimumHeight()) {
            RAISE_VALUE_ERROR(nullptr, "maximum height must be greater than or equal to minimum height")
        }
        #endif

        self->window->setMaximumSize(tmp_width, tmp_height);
        Py_RETURN_NONE;
    }

    static PyObject *get_maximum_size(WindowObject *self, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(nullptr)

        return PyTuple_Pack(2, PyLong_FromLong(self->window->getMaximumWidth()),
                            PyLong_FromLong(self->window->getMaximumHeight()));
    }
}

// Window Callbacks
namespace window {

    // Resize
    static int set_resize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: width, height")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->resize_callback, value)

        self->window->setResizeCallback([self] (gp::Window *window, int width, int height) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->resize_callback, "ii", width, height);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_resize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->resize_callback)
    }

    // Close
    static int set_close_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 0) {
            RAISE_VALUE_ERROR(-1, "callback must not take arguments")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->close_callback, value)
        self->window->setCloseCallback([self] (gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->close_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_close_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->close_callback)
    }

    // Destroy
    static int set_destroy_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 0) {
            RAISE_VALUE_ERROR(-1, "callback must not take arguments")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->destroy_callback, value)
        self->window->setDestroyCallback([self] (gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->destroy_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_destroy_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->destroy_callback)
    }

    // Position
    static int set_position_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: xpos, ypos")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->position_callback, value)
        self->window->setPositionCallback([self] (gp::Window *window, int xPos, int yPos) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->position_callback, "ii", xPos, yPos);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_position_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->position_callback)
    }

    // Minimize
    static int set_minimize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 1) {
            RAISE_VALUE_ERROR(-1, "callback must take 1 argument: minimized")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->minimize_callback, value)
        self->window->setMinimizeCallback([self] (gp::Window *window, bool minimized) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->minimize_callback, "O", minimized ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_minimize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->minimize_callback)
    }

    // Maximize
    static int set_maximize_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 1) {
            RAISE_VALUE_ERROR(-1, "callback must take 1 argument: maximized")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->maximize_callback, value)
        self->window->setMaximizeCallback([self] (gp::Window *window, bool maximized) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->maximize_callback, "O", maximized ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_maximize_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->maximize_callback)
    }

    // Focus
    static int set_focus_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 1) {
            RAISE_VALUE_ERROR(-1, "callback must take 1 argument: focused")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->focus_callback, value)
        self->window->setFocusCallback([self](gp::Window *window, bool focused) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->focus_callback, "O", focused ? Py_True : Py_False);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_focus_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->focus_callback)
    }

    // Refresh
    static int set_refresh_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 0) {
            RAISE_VALUE_ERROR(-1, "callback must not take arguments")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->refresh_callback, value)
        self->window->setRefreshCallback([self] (gp::Window *window) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallNoArgs(self->refresh_callback);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_refresh_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->refresh_callback)
    }

    // Content Scale
    static int set_content_scale_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: xscale, yscale")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->content_scale_callback, value)
        self->window->setContentScaleCallback([self] (gp::Window *window, float xScale, float yScale) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->content_scale_callback, "ff", xScale, yScale);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_content_scale_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->content_scale_callback)
    }

    // Framebuffer Size
    static int set_framebuffer_size_callback(WindowObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        CHECK_WINDOW_ACTIVE(-1)

        #if GP_ERROR_CHECKING
        if (!PyCallable_Check(value) and value != Py_None) {
            RAISE_TYPE_ERROR(-1, "callable", value)
        }
        if (PyFunction_Check(value) and PyLong_AsLong(PyObject_GetAttrString(PyFunction_GetCode(value), "co_argcount")) != 2) {
            RAISE_VALUE_ERROR(-1, "callback must take 2 arguments: width, height")
        }
        #endif

        SET_PYOBJECT_ATTRIBUTE(self->framebuffer_size_callback, value)
        self->window->setFramebufferSizeCallback([self] (gp::Window *window, int width, int height) {
            PyGILState_STATE gstate = PyGILState_Ensure();
            PyObject_CallFunction(self->framebuffer_size_callback, "ii", width, height);
            PyGILState_Release(gstate);
        });

        return 0;
    }

    static PyObject *get_framebuffer_size_callback(WindowObject *self, void *Py_UNUSED(closure)) {
        RETURN_PYOBJECT(self->framebuffer_size_callback)
    }
}

// Window Type
namespace window {
    static PyMethodDef methods[] = {
            {"update",           (PyCFunction) window::update,           METH_NOARGS,
                    "Update the Window"},
            {"destroy",          (PyCFunction) window::destroy,          METH_NOARGS,
                    "Destroys the Window"},

            {"is_open",          (PyCFunction) window::is_open,          METH_NOARGS,
                    "Returns whether the Window is open"},
            {"is_closed",        (PyCFunction) window::is_closed,        METH_NOARGS,
                    "Returns whether the Window is closed"},

            {"is_fullscreen",    (PyCFunction) window::is_fullscreen,    METH_NOARGS,
                    "Returns if the Window is fullscreen"},
            {"is_maximized",     (PyCFunction) window::is_maximized,     METH_NOARGS,
                    "Returns if the Window is maximized"},
            {"is_minimized",     (PyCFunction) window::is_minimized,     METH_NOARGS,
                    "Returns if the Window is minimized"},
            {"is_visible",       (PyCFunction) window::is_visible,       METH_NOARGS,
                    "Returns if the Window is visible"},

            {"set_size_limits",  (PyCFunction) window::set_size_limits,  METH_VARARGS | METH_KEYWORDS,
                    "Sets the minimum and maximum size for the window"},
            {"set_minimum_size", (PyCFunction) window::set_minimum_size, METH_VARARGS,
                    "Sets the minimum size for the window"},
            {"set_maximum_size", (PyCFunction) window::set_maximum_size, METH_VARARGS,
                    "Sets the maximum size for the window"},
            {"get_minimum_size", (PyCFunction) window::get_minimum_size, METH_NOARGS,
                    "Returns a tuple (width, height) containing the minimum size for the window"},
            {"get_maximum_size", (PyCFunction) window::get_maximum_size, METH_NOARGS,
                    "Returns a tuple (width, height) containing the maximum size for the window"},

            {"get_size",         (PyCFunction) window::get_size,         METH_NOARGS,
                    "Returns the Window's width and height as a tuple"},
            {"set_size",         (PyCFunction) window::set_size,         METH_VARARGS,
                    "Sets the Window's width and height"},
            {"get_position",     (PyCFunction) window::get_position,     METH_NOARGS,
                    "Returns the Window's x and y position as a tuple"},
            {"set_position",     (PyCFunction) window::set_position,     METH_VARARGS,
                    "Sets the Window's x and y position"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {"width",                     (getter) window::get_width,                     (setter) window::set_width,                     "width",                     nullptr},
            {"height",                    (getter) window::get_height,                    (setter) window::set_height,                    "height",                    nullptr},

            {"title",                     (getter) window::get_title,                     (setter) window::set_title,                     "title",                     nullptr},

            {"min_width",                 (getter) window::get_min_width,                 (setter) window::set_min_width,                 "minimum width",             nullptr},
            {"max_width",                 (getter) window::get_max_width,                 (setter) window::set_max_width,                 "maximum width",             nullptr},
            {"min_height",                (getter) window::get_min_height,                (setter) window::set_min_height,                "minimum height",            nullptr},
            {"max_height",                (getter) window::get_max_height,                (setter) window::set_max_height,                "maximum height",            nullptr},

            {"x_position",                (getter) window::get_x_position,                (setter) window::set_x_position,                "x position",                nullptr},
            {"y_position",                (getter) window::get_y_position,                (setter) window::set_y_position,                "y position",                nullptr},

            {"resizable",                 (getter) window::is_resizable,                  (setter) window::set_resizable,                 "resizable",                 nullptr},
            {"decorated",                 (getter) window::is_decorated,                  (setter) window::set_decorated,                 "decorated",                 nullptr},
            {"auto_minimized",            (getter) window::is_auto_minimized,             (setter) window::set_auto_minimized,            "auto minimized",            nullptr},
            {"floating",                  (getter) window::is_floating,                   (setter) window::set_floating,                  "floating",                  nullptr},
            {"focused_on_show",           (getter) window::is_focused_on_show,            (setter) window::set_focused_on_show,           "focused on show",           nullptr},

            {"resize_callback",           (getter) window::get_resize_callback,           (setter) window::set_resize_callback,           "resize callback",           nullptr},
            {"position_callback",         (getter) window::get_position_callback,         (setter) window::set_position_callback,         "position callback",         nullptr},
            {"framebuffer_size_callback", (getter) window::get_framebuffer_size_callback, (setter) window::set_framebuffer_size_callback, "framebuffer size callback", nullptr},
            {"close_callback",            (getter) window::get_close_callback,            (setter) window::set_close_callback,            "close callback",            nullptr},
            {"content_scale_callback",    (getter) window::get_content_scale_callback,    (setter) window::set_content_scale_callback,    "content scale callback",    nullptr},
            {"destroy_callback",          (getter) window::get_destroy_callback,          (setter) window::set_destroy_callback,          "destroy callback",          nullptr},
            {"minimize_callback",         (getter) window::get_minimize_callback,         (setter) window::set_minimize_callback,         "minimize callback",         nullptr},
            {"maximize_callback",         (getter) window::get_maximize_callback,         (setter) window::set_maximize_callback,         "maximize callback",         nullptr},
            {"focus_callback",            (getter) window::get_focus_callback,            (setter) window::set_focus_callback,            "focus callback",            nullptr},
            {"refresh_callback",          (getter) window::get_refresh_callback,          (setter) window::set_refresh_callback,          "refresh callback",          nullptr},

            {nullptr}
    };
}

PyTypeObject WindowType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Window",
        .tp_basicsize = sizeof(WindowObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = PyType_GenericNew,
        .tp_init = (initproc) window::init,

        .tp_methods = window::methods,
        .tp_getset = window::getsetters,

        .tp_traverse = (traverseproc) window::traverse,
        .tp_clear = (inquiry) window::clear,
        .tp_dealloc = (destructor) window::dealloc,

        .tp_repr = (reprfunc) window::repr,
};

int PyInit_window(PyObject *m) {
    EXPOSE_CLASS(WindowType, "Window")
    return 0;
}
