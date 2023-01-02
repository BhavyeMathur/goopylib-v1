#pragma once

#include "goopylib/header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct QuadObject;

namespace quad {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

    static int init(QuadObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(QuadObject *Py_UNUSED(self));

    static int traverse(QuadObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

    static int clear(__attribute__((unused)) QuadObject *Py_UNUSED(self));

    static void dealloc(QuadObject *self);
}

namespace quad {
    static PyObject *set_color(QuadObject *self, PyObject *args);

    static PyObject *set_transparency(QuadObject *self, PyObject *args);
}


extern PyTypeObject QuadType;
