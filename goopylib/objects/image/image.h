#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyRectangle_API;
extern PyTypeObject *RectangleType;

extern void **PyWindow_API;
extern PyTypeObject *WindowType;


namespace image {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(ImageObject *self, PyObject *args, PyObject *kwds);

    int traverse(ImageObject *self, visitproc visit, void *arg);

    int clear(ImageObject *self);

    void dealloc(ImageObject *self);
}

namespace image {
    PyObject *get_path(ImageObject *self, PyObject *args);

    PyObject *draw(ImageObject *self, PyObject *arg);
}

extern PyTypeObject ImageType;
