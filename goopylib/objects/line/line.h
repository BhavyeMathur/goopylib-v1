#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyColor_API;
extern PyTypeObject *ColorType;

extern void **PyQuad_API;
extern PyTypeObject *QuadType;


namespace line {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(LineObject *self, PyObject *args, PyObject *kwds);

    PyObject *repr(LineObject *self);

    int traverse(LineObject *self, visitproc visit, void *arg);

    int clear(LineObject *self);

    void dealloc(LineObject *self);
}

namespace line {
    PyObject *set_color(LineObject *self, PyObject *args);

    PyObject *set_transparency(LineObject *self, PyObject *args);
}

extern PyTypeObject LineType;
