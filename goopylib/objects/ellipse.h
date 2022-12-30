#pragma once

#include "header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct EllipseObject;

namespace ellipse {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(EllipseObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(EllipseObject *self);

    static int traverse(EllipseObject *self, visitproc visit, void *arg);

    static int clear(EllipseObject *self);

    static void dealloc(EllipseObject *self);
}

namespace ellipse {
    static PyObject *set_color(EllipseObject *self, PyObject *args);

    static PyObject *set_transparency(EllipseObject *self, PyObject *args);
}


extern PyTypeObject EllipseType;
