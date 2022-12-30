#pragma once

#include "header.h"
#include "renderable_object.h"

static void **PyWindow_API;
static PyTypeObject *WindowType;


namespace renderable {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(RenderableObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(RenderableObject *self);

    static int traverse(RenderableObject *self, visitproc visit, void *arg);

    static int clear(RenderableObject *self);

    static void dealloc(RenderableObject *self);
}

namespace renderable {
    static PyObject *draw(RenderableObject *self, PyObject *arg);

    static PyObject *destroy(RenderableObject *self, PyObject *args);

    static PyObject *is_drawn(RenderableObject *self, PyObject *args);

    static PyObject *set_anchor(RenderableObject *self, PyObject *args);

    static PyObject *reset_anchor(RenderableObject *self, PyObject *args);

    static PyObject *move(RenderableObject *self, PyObject *args);

    static PyObject *rotate(RenderableObject *self, PyObject *arg);

    static PyObject *scale(RenderableObject *self, PyObject *args);

    static PyObject *set_size(RenderableObject *self, PyObject *args);

    static PyObject *hide(RenderableObject *self, PyObject *arg);

    static PyObject *show(RenderableObject *self, PyObject *args);

    static PyObject *is_hidden(RenderableObject *self, PyObject *args);

    static PyObject *box_contains(RenderableObject *self, PyObject *args);

    static PyObject *contains(RenderableObject *self, PyObject *args);
}

namespace renderable {
    // X-Position
    static PyObject *get_x(RenderableObject *self, void *closure);

    static int set_x(RenderableObject *self, PyObject *value, void *closure);

    // Y-Position
    static PyObject *get_y(RenderableObject *self, void *closure);

    static int set_y(RenderableObject *self, PyObject *value, void *closure);

    // Position
    static PyObject *get_position(RenderableObject *self, void *closure);

    static int set_position(RenderableObject *self, PyObject *value, void *closure);

    // Rotation
    static PyObject *get_rotation(RenderableObject *self, void *closure);

    static int set_rotation(RenderableObject *self, PyObject *value, void *closure);

    // X-Scale
    static PyObject *get_xscale(RenderableObject *self, void *closure);

    static int set_xscale(RenderableObject *self, PyObject *value, void *closure);

    // Y-Scale
    static PyObject *get_yscale(RenderableObject *self, void *closure);

    static int set_yscale(RenderableObject *self, PyObject *value, void *closure);

    // Width
    static PyObject *get_width(RenderableObject *self, void *closure);

    static int set_width(RenderableObject *self, PyObject *value, void *closure);

    // Height
    static PyObject *get_height(RenderableObject *self, void *closure);

    static int set_height(RenderableObject *self, PyObject *value, void *closure);
}


extern PyTypeObject RenderableType;
