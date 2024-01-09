#pragma once

#include "goopylib/header.h"
#include "object.h"

extern void **PyRenderable_API;
extern PyTypeObject *RenderableType;

extern void **PyColor_API;
extern PyTypeObject *ColorType;


namespace ellipse {
    PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds);

    int init(EllipseObject *self, PyObject *args, PyObject *kwds);

    int traverse(EllipseObject *self, visitproc visit, void *arg);

    int clear(EllipseObject *self);

    void dealloc(EllipseObject *self);

    PyObject *set_color(EllipseObject *self, PyObject *args);
}

namespace ellipse {
    // Transparency
    PyObject *get_transparency(EllipseObject *self, void *closure);

    int set_transparency(EllipseObject *self, PyObject *value, void *closure);

}

extern PyTypeObject EllipseType;
