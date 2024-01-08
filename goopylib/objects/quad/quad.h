#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyRenderable_API;
extern PyTypeObject *RenderableType;

extern void **PyColor_API;
extern PyTypeObject *ColorType;


namespace quad {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(QuadObject *self, PyObject *args, PyObject *kwds);

    PyObject *repr(QuadObject *self);

    int traverse(QuadObject *self, visitproc visit, void *arg);

    int clear(QuadObject *self);

    void dealloc(QuadObject *self);
}


extern PyTypeObject QuadType;
