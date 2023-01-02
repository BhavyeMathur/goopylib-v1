#pragma once

#include "goopylib/header.h"

static void **PyQuad_API;
static PyTypeObject *QuadType;


struct RectangleObject;

namespace rectangle {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

    static int init(RectangleObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(RectangleObject *Py_UNUSED(self));

    static int traverse(RectangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

    static int clear(__attribute__((unused)) RectangleObject *Py_UNUSED(self));

    static void dealloc(RectangleObject *self);
}
