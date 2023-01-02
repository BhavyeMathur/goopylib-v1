#pragma once

#include "goopylib/header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;


struct ImageObject;

namespace image {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

    static int init(ImageObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(ImageObject *Py_UNUSED(self));

    static int traverse(ImageObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

    static int clear(ImageObject *Py_UNUSED(self));

    static void dealloc(ImageObject *self);
}

namespace image {
    static PyObject *set_color(ImageObject *self, PyObject *args);

    static PyObject *set_transparency(ImageObject *self, PyObject *args);
}
