#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyRenderable_API;
extern PyTypeObject *RenderableType;

extern void **PyColor_API;
extern PyTypeObject *ColorType;


namespace triangle {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(TriangleObject *self, PyObject *args, PyObject *kwds);

    int traverse(TriangleObject *self, visitproc visit, void *arg);

    int clear(TriangleObject *self);

    void dealloc(TriangleObject *self);
}

namespace triangle {
    PyObject *set_color(TriangleObject *self, PyObject *args);
}

namespace triangle {
    // Vertex Positions
    PyObject *get_p1(TriangleObject *self, void *closure);

    int set_p1(TriangleObject *self, PyObject *value, void *closure);

    PyObject *get_p2(TriangleObject *self, void *closure);

    int set_p2(TriangleObject *self, PyObject *value, void *closure);

    PyObject *get_p3(TriangleObject *self, void *closure);

    int set_p3(TriangleObject *self, PyObject *value, void *closure);

    // Transparency
    PyObject *get_transparency(TriangleObject *self, void *closure);

    int set_transparency(TriangleObject *self, PyObject *value, void *closure);
}

extern PyTypeObject TriangleType;
