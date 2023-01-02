#pragma once

#include "goopylib/header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct EllipseObject;

namespace ellipse {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds));

    static int init(EllipseObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(EllipseObject *Py_UNUSED(self));

    static int traverse(EllipseObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg));

    static int clear(__attribute__((unused)) EllipseObject *Py_UNUSED(self));

    static void dealloc(EllipseObject *self);
}

namespace ellipse {
    static PyObject *set_color(EllipseObject *self, PyObject *args);

    static PyObject *set_transparency(EllipseObject *self, PyObject *args);
}


extern PyTypeObject EllipseType;
