#pragma once

#include "header.h"

static void **PyQuad_API;
static PyTypeObject *QuadType;


struct RectangleObject;

namespace rectangle {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(RectangleObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(RectangleObject *self);

    static int traverse(RectangleObject *self, visitproc visit, void *arg);

    static int clear(RectangleObject *self);

    static void dealloc(RectangleObject *self);
}
