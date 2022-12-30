#pragma once

#include "header.h"

static void **PyRenderable_API;
static PyTypeObject *RenderableType;


struct ImageObject;

namespace image {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    static int init(ImageObject *self, PyObject *args, PyObject *kwds);

    static PyObject *repr(ImageObject *self);

    static int traverse(ImageObject *self, visitproc visit, void *arg);

    static int clear(ImageObject *self);

    static void dealloc(ImageObject *self);
}

namespace image {
    static PyObject *set_color(ImageObject *self, PyObject *args);

    static PyObject *set_transparency(ImageObject *self, PyObject *args);
}


extern PyTypeObject ImageType;
