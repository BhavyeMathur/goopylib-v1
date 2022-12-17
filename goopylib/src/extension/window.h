#pragma once

#include "util.h"

#include "color/colormodule.h"

#include <goopylib/Core/Core.h>
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

struct WindowObject;

extern PyTypeObject WindowType;

namespace window {
    bool isinstance(PyObject *object);
}

PyObject *PyInit_window(PyObject *m);
