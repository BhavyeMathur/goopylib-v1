#pragma once

#include "goopylib/header.h"

static void **PyEllipse_API;
static PyTypeObject *EllipseType;


struct CircleObject;

namespace circle {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

    static int init(CircleObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(CircleObject *Py_UNUSED(self));

    static int traverse(CircleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

    static int clear(CircleObject *Py_UNUSED(self));

    static void dealloc(CircleObject *self);
}
