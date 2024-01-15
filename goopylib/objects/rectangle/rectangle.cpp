#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "rectangle.h"
#include "src/goopylib/objects/Rectangle.h"


// Rectangle Core
namespace rectangle {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        RectangleObject *self;
        self = (RectangleObject *) type->tp_alloc(type, 0);

        return (PyObject *) self;
    }

    int init(RectangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.rectangle.Rectangle()");

        float x1, y1;
        float width, height;
        if (PyArg_ParseTuple(args, "(ff)ff", &x1, &y1, &width, &height)) {
            self->rectangle = shared_ptr<gp::Rectangle>(new gp::Rectangle({x1, y1}, width, height));
            self->base.quad = self->rectangle;
            self->base.base.renderable = self->rectangle;
            return 0;
        }
        PyErr_Clear();

        float x2, y2;
        if (!PyArg_ParseTuple(args, "(ff)(ff)", &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->rectangle = shared_ptr<gp::Rectangle>(new gp::Rectangle({x1, y1}, {x2, y2}));
        self->base.quad = self->rectangle;
        self->base.base.renderable = self->rectangle;
        return 0;
    }

    int traverse(RectangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(RectangleObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.rectangle.Rectangle.clear()");
        return 0;
    }

    void dealloc(RectangleObject *self) {
        GP_PY_DEBUG("gp.rectangle.Rectangle.__dealloc__()");

        self->rectangle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}
