#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyWindow_API;
extern PyTypeObject *WindowType;


namespace renderable {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(RenderableObject *self, PyObject *args, PyObject *kwds);

    PyObject *repr(RenderableObject *self);

    int traverse(RenderableObject *self, visitproc visit, void *arg);

    int clear(RenderableObject *self);

    void dealloc(RenderableObject *self);
}

namespace renderable {
    PyObject *draw(RenderableObject *self, PyObject *arg);

    PyObject *destroy(RenderableObject *self, PyObject *args);

    PyObject *is_drawn(RenderableObject *self, PyObject *args);

    PyObject *set_anchor(RenderableObject *self, PyObject *args);

    PyObject *reset_anchor(RenderableObject *self, PyObject *args);

    PyObject *move(RenderableObject *self, PyObject *args);

    PyObject *rotate(RenderableObject *self, PyObject *arg);

    PyObject *scale(RenderableObject *self, PyObject *args);

    PyObject *set_size(RenderableObject *self, PyObject *args);

    PyObject *hide(RenderableObject *self, PyObject *arg);

    PyObject *show(RenderableObject *self, PyObject *args);

    PyObject *is_hidden(RenderableObject *self, PyObject *args);

    PyObject *is_opaque(RenderableObject *self, PyObject *args);

    PyObject *box_contains(RenderableObject *self, PyObject *args);

    PyObject *contains(RenderableObject *self, PyObject *args);
}

namespace renderable {
    // X-Position
    PyObject *get_x(RenderableObject *self, void *closure);

    int set_x(RenderableObject *self, PyObject *value, void *closure);

    // Y-Position
    PyObject *get_y(RenderableObject *self, void *closure);

    int set_y(RenderableObject *self, PyObject *value, void *closure);

    // Position
    PyObject *get_position(RenderableObject *self, void *closure);

    int set_position(RenderableObject *self, PyObject *value, void *closure);

    // Rotation
    PyObject *get_rotation(RenderableObject *self, void *closure);

    int set_rotation(RenderableObject *self, PyObject *value, void *closure);

    // X-Scale
    PyObject *get_xscale(RenderableObject *self, void *closure);

    int set_xscale(RenderableObject *self, PyObject *value, void *closure);

    // Y-Scale
    PyObject *get_yscale(RenderableObject *self, void *closure);

    int set_yscale(RenderableObject *self, PyObject *value, void *closure);

    // Width
    PyObject *get_width(RenderableObject *self, void *closure);

    int set_width(RenderableObject *self, PyObject *value, void *closure);

    // Height
    PyObject *get_height(RenderableObject *self, void *closure);

    int set_height(RenderableObject *self, PyObject *value, void *closure);

    // Z-Position
    PyObject *get_z(RenderableObject *self, void *closure);

    int set_z(RenderableObject *self, PyObject *value, void *closure);
}


extern PyTypeObject RenderableType;
