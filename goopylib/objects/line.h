#pragma once

#include "goopylib/header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct LineObject;

namespace line {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

    static int init(LineObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(LineObject *Py_UNUSED(self));

    static int traverse(LineObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

    static int clear(__attribute__((unused)) LineObject *Py_UNUSED(self));

    static void dealloc(LineObject *self);
}

namespace line {
    static PyObject *set_color(LineObject *self, PyObject *args);

    static PyObject *set_transparency(LineObject *self, PyObject *args);
}
