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

    PyObject *repr(TriangleObject *self);

    int traverse(TriangleObject *self, visitproc visit, void *arg);

    int clear(TriangleObject *self);

    void dealloc(TriangleObject *self);
}

namespace triangle {
    PyObject *set_color(TriangleObject *self, PyObject *args);

    PyObject *set_transparency(TriangleObject *self, PyObject *args);
}

extern PyTypeObject TriangleType;
