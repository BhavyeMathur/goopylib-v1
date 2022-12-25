#pragma once

#include "src/extension/header.h"

#include "src/extension/color/colormodule.h"

#include "src/goopylib/core/Core.h"
#include "src/goopylib/core/Window.h"
#include "src/goopylib/core/Window.h"

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
