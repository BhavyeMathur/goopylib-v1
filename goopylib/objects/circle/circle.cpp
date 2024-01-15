#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "circle.h"
#include "src/goopylib/objects/Circle.h"


namespace circle {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        CircleObject *self;
        self = (CircleObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    int init(CircleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.circle.Circle()");

        float x1, y1;
        float radius;
        if (!PyArg_ParseTuple(args, "(ff)f", &x1, &y1, &radius)) {
            return -1;
        }

        self->circle = shared_ptr<gp::Circle>(new gp::Circle({x1, y1}, radius));
        self->base.ellipse = self->circle;
        self->base.base.renderable = self->circle;
        return 0;
    }

    int traverse(CircleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(CircleObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.circle.Circle.clear()");
        return 0;
    }

    void dealloc(CircleObject *self) {
        GP_PY_DEBUG("gp.circle.Circle.__dealloc__()");

        self->circle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}
