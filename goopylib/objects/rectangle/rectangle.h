#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyQuad_API;
extern PyTypeObject *QuadType;


namespace rectangle {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(RectangleObject *self, PyObject *args, PyObject *kwds);

    int traverse(RectangleObject *self, visitproc visit, void *arg);

    int clear(RectangleObject *self);

    void dealloc(RectangleObject *self);
}

extern PyTypeObject RectangleType;
