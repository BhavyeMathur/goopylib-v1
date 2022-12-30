#pragma once

#include "header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct TriangleObject;

namespace triangle {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(TriangleObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(TriangleObject *self);

    static int traverse(TriangleObject *self, visitproc visit, void *arg);

    static int clear(TriangleObject *self);

    static void dealloc(TriangleObject *self);
}

namespace triangle {
    static PyObject *set_color(TriangleObject *self, PyObject *args);

    static PyObject *set_transparency(TriangleObject *self, PyObject *args);
}
