#pragma once

#include "header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;

static void **PyColor_API;
static PyTypeObject *ColorType;


struct QuadObject;

namespace quad {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(QuadObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(QuadObject *self);

    static int traverse(QuadObject *self, visitproc visit, void *arg);

    static int clear(QuadObject *self);

    static void dealloc(QuadObject *self);
}

namespace quad {
    static PyObject *set_color(QuadObject *self, PyObject *args);

    static PyObject *set_transparency(QuadObject *self, PyObject *args);
}


extern PyTypeObject QuadType;
