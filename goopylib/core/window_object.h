#pragma once

#include "header.h"
#include "goopylib/core/Window.h"

struct WindowObject {
    PyObject_HEAD
            Scope<gp::Window> window;

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

    std::unordered_map<int, PyObject *> key_callbacks;
    std::unordered_map<int, PyObject *> mouse_callbacks;
};
