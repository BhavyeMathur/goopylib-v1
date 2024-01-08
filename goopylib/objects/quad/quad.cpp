#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "quad.h"
#include "src/goopylib/objects/Quad.h"


// Quad Core
namespace quad {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        QuadObject *self;
        self = (QuadObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    int init(QuadObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.quad.Quad()");

        float x1, x2, x3, x4;
        float y1, y2, y3, y4;
        if (!PyArg_ParseTuple(args, "(ff)(ff)(ff)(ff)", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4)) {
            return -1;
        }

        self->quad = Ref<gp::Quad>(new gp::Quad({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}));
        self->base.renderable = self->quad;

        return 0;
    }

    PyObject *repr(QuadObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.quad.Quad.__repr__()");
        return PyUnicode_FromString("Quad()");
    }

    int traverse(QuadObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(QuadObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.quad.Quad.clear()");
        return 0;
    }

    void dealloc(QuadObject *self) {
        GP_PY_DEBUG("gp.quad.Quad.__dealloc__()");

        self->quad.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}
