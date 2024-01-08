#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "../quad/methods.h"
#include "goopylib/color/color_object.h"

#include "line.h"
#include "src/goopylib/objects/Line.h"


// Line Core
namespace line {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        LineObject *self;
        self = (LineObject *) type->tp_alloc(type, 0);

        return (PyObject *) self;
    }

    int init(LineObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.line.Line()");

        float x1, x2;
        float y1, y2;
        float thickness;
        if (!PyArg_ParseTuple(args, "(ff)(ff)f", &x1, &y1, &x2, &y2, &thickness)) {
            return -1;
        }

        self->line = Ref<gp::Line>(new gp::Line({x1, y1}, {x2, y2}, thickness));
        self->base.quad = self->line;
        self->base.base.renderable = self->line;
        return 0;
    }

    PyObject *repr(LineObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.line.Line.__repr__()");
        return PyUnicode_FromString("Line()");
    }

    int traverse(LineObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(LineObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.line.Line.clear()");
        return 0;
    }

    void dealloc(LineObject *self) {
        GP_PY_DEBUG("gp.line.Line.__dealloc__()");

        self->line.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Line methods
namespace line {
    PyObject *set_color(LineObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.line.Line.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject * arg1, *arg2;
        PyObject * color1;
        if (PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {

            PyObject * color2;

            if (!isinstance(arg1, ColorType)) {
                color1 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg1));
                GP_CHECK_NULL(color1, nullptr, "Invalid arguments to set 1st color")
            }
            else {
                color1 = arg1;
            }

            if (!isinstance(arg2, ColorType)) {
                color2 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg2));
                GP_CHECK_NULL(color2, nullptr, "Invalid arguments to set 2nd color")
            }
            else {
                color2 = arg2;
            }

            self->line->setColor(*((ColorObject *) color1)->color,
                                 *((ColorObject *) color2)->color);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (PyArg_ParseTuple(args, "O", &arg1)) {
            if (!isinstance(arg1, ColorType)) {
                color1 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg1));
                GP_CHECK_NULL(color1, nullptr, "Invalid arguments to set color")
            }
            else {
                color1 = arg1;
            }

            self->line->setColor(*((ColorObject *) color1)->color);
        }
        PyErr_Clear();

        return quad::set_color(reinterpret_cast<QuadObject *>(self), args);
    }

    PyObject *set_transparency(LineObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.line.Line.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2;
        if (PyArg_ParseTuple(args, "ff", &v1, &v2)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->line->setTransparency(v1, v2);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (PyArg_ParseTuple(args, "f", &v1)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->line->setTransparency(v1);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        return quad::set_transparency(reinterpret_cast<QuadObject *>(self), args);
    }
}

// Line Getters & Setters
namespace line {
    PyObject *get_thickness(LineObject *self, void *closure) {
        return PyFloat_FromDouble(self->line->getThickness());
    }

    int set_thickness(LineObject *self, PyObject *value, void *closure) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->line->setThickness((float) PyFloat_AsDouble(value));
        return 0;
    }
}
