#pragma once

#include "header.h"


namespace core {
    static PyObject *init(PyObject *self);

    static PyObject *terminate(PyObject *self);

    static PyObject *update(PyObject *self);

    #if GP_USING_GLFW

    static PyObject *update_on_event(PyObject *self, PyObject *args);

    static PyObject *update_timeout(PyObject *self, PyObject *arg);

    static PyObject *glfw_compiled_version(PyObject *self);

    static PyObject *glfw_current_version(PyObject *self);

    static PyObject *get_refresh_rate(PyObject *self);

    static PyObject *get_screen_width(PyObject *self);

    static PyObject *get_screen_height(PyObject *self);

    static PyObject *number_of_monitors(PyObject *self);

    static PyObject *set_buffer_swap_interval(PyObject *self, PyObject *arg);

    #endif

    #if GP_USING_OPENGL

    static PyObject *opengl_version(PyObject *self);

    #endif
}
