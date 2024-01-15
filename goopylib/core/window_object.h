#pragma once

#include "goopylib/header.h"
#include "src/goopylib/core/Window.h"

struct WindowObject {
    PyObject_HEAD
    unique_ptr<gp::Window> window;

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
    PyObject *mouse_motion_callback;
    PyObject *mouse_enter_callback;
    PyObject *scroll_callback;

    PyObject *background;
    PyObject *camera;

    PyObject* key_callbacks;
    PyObject* mouse_callbacks;
};
