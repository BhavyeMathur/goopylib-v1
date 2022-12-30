#pragma once

#include "header.h"

static void **PyEllipse_API;
static PyTypeObject *EllipseType;


struct CircleObject;

namespace circle {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(CircleObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(CircleObject *self);

    static int traverse(CircleObject *self, visitproc visit, void *arg);

    static int clear(CircleObject *self);

    static void dealloc(CircleObject *self);
}
