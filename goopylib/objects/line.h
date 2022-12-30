#pragma once

#include "header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct LineObject;

namespace line {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(LineObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(LineObject *self);

    static int traverse(LineObject *self, visitproc visit, void *arg);

    static int clear(LineObject *self);

    static void dealloc(LineObject *self);
}

namespace line {
    static PyObject *set_color(LineObject *self, PyObject *args);

    static PyObject *set_transparency(LineObject *self, PyObject *args);
}
