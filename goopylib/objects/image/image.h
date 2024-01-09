#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyRectangle_API;
extern PyTypeObject *RectangleType;


namespace image {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(ImageObject *self, PyObject *args, PyObject *kwds);

    PyObject *repr(ImageObject *self);

    int traverse(ImageObject *self, visitproc visit, void *arg);

    int clear(ImageObject *self);

    void dealloc(ImageObject *self);
}

namespace image {
    PyObject *set_transparency(ImageObject *self, PyObject *args);

    PyObject *get_path(ImageObject *self, PyObject *args);
}

extern PyTypeObject ImageType;
