#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyColor_API;
extern PyTypeObject *ColorType;

extern void **PyQuad_API;
extern PyTypeObject *QuadType;


namespace line {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(LineObject *self, PyObject *args, PyObject *kwds);

    int traverse(LineObject *self, visitproc visit, void *arg);

    int clear(LineObject *self);

    void dealloc(LineObject *self);
}

namespace line {
    PyObject *set_color(LineObject *self, PyObject *args);
}

namespace line {
    // Thickness
    PyObject *get_thickness(LineObject *self, void *closure);

    int set_thickness(LineObject *self, PyObject *value, void *closure);

    // Transparency
    PyObject *get_transparency(LineObject *self, void *closure);

    int set_transparency(LineObject *self, PyObject *value, void *closure);
}

extern PyTypeObject LineType;
