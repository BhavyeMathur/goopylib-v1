#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyEllipse_API;
extern PyTypeObject *EllipseType;


namespace circle {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(CircleObject *self, PyObject *args, PyObject *kwds);

    int traverse(CircleObject *self, visitproc visit, void *arg);

    int clear(CircleObject *self);

    void dealloc(CircleObject *self);
}

extern PyTypeObject CircleType;
