#pragma once

#include "goopylib/header.h"
#include "object.h"

static void **PyEllipse_API;
static PyTypeObject *EllipseType;


namespace circle {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(CircleObject *self, PyObject *args, PyObject *kwds);

    PyObject *repr(CircleObject *self);

    int traverse(CircleObject *self, visitproc visit, void *arg);

    int clear(CircleObject *self);

    void dealloc(CircleObject *self);
}

extern PyTypeObject CircleType;
