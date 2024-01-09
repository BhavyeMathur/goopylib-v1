#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyRenderable_API;
extern PyTypeObject *RenderableType;

extern void **PyColor_API;
extern PyTypeObject *ColorType;


namespace quad {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(QuadObject *self, PyObject *args, PyObject *kwds);

    int traverse(QuadObject *self, visitproc visit, void *arg);

    int clear(QuadObject *self);

    void dealloc(QuadObject *self);
}

namespace quad {
    // Vertex Positions
    PyObject *get_p1(QuadObject *self, void *closure);

    int set_p1(QuadObject *self, PyObject *value, void *closure);

    PyObject *get_p2(QuadObject *self, void *closure);

    int set_p2(QuadObject *self, PyObject *value, void *closure);

    PyObject *get_p3(QuadObject *self, void *closure);

    int set_p3(QuadObject *self, PyObject *value, void *closure);

    PyObject *get_p4(QuadObject *self, void *closure);

    int set_p4(QuadObject *self, PyObject *value, void *closure);

    // Transparency
    PyObject *get_transparency(QuadObject *self, void *closure);

    int set_transparency(QuadObject *self, PyObject *value, void *closure);
}


extern PyTypeObject QuadType;
