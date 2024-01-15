#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "ellipse.h"
#include "src/goopylib/objects/Ellipse.h"

#include "goopylib/color/color_object.h"


namespace ellipse {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        EllipseObject *self;
        self = (EllipseObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    int init(EllipseObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.ellipse.Ellipse()");

        float x1, y1;
        float radius1, radius2;
        if (PyArg_ParseTuple(args, "(ff)ff", &x1, &y1, &radius1, &radius2)) {
            self->ellipse = shared_ptr<gp::Ellipse>(new gp::Ellipse({x1, y1}, radius1, radius2));
            self->base.renderable = self->ellipse;
            return 0;
        }
        PyErr_Clear();

        float x2, y2;
        if (!PyArg_ParseTuple(args, "(ff)(ff)", &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->ellipse = shared_ptr<gp::Ellipse>(new gp::Ellipse({x1, y1}, {x2, y2}));
        self->base.renderable = self->ellipse;
        return 0;
    }

    int traverse(EllipseObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(EllipseObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.ellipse.Ellipse.clear()");
        return 0;
    }

    void dealloc(EllipseObject *self) {
        GP_PY_DEBUG("gp.ellipse.Ellipse.__dealloc__()");

        self->ellipse.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Ellipse Methods
namespace ellipse {
    PyObject *set_color(EllipseObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.ellipse.Ellipse.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject * arg1, *arg2, *arg3, *arg4;
        PyObject * color1;
        if (PyArg_ParseTuple(args, "OOOO", &arg1, &arg2, &arg3, &arg4)) {

            PyObject * color2, *color3, *color4;

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

            if (!isinstance(arg3, ColorType)) {
                color3 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg3));
                GP_CHECK_NULL(color3, nullptr, "Invalid arguments to set 3rd color")
            }
            else {
                color3 = arg3;
            }

            if (!isinstance(arg4, ColorType)) {
                color4 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg4));
                GP_CHECK_NULL(color4, nullptr, "Invalid arguments to set 4th color")
            }
            else {
                color4 = arg4;
            }

            self->ellipse->setColor(*((ColorObject *) color1)->color,
                                    *((ColorObject *) color2)->color,
                                    *((ColorObject *) color3)->color,
                                    *((ColorObject *) color4)->color);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "O", &arg1)) {
            return nullptr;
        }

        if (!isinstance(arg1, ColorType)) {
            color1 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg1));
            GP_CHECK_NULL(color1, nullptr, "Invalid arguments to set color")
        }
        else {
            color1 = arg1;
        }

        self->ellipse->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }
}

// Ellipse Getters & Setters
namespace ellipse {
    PyObject *get_transparency(EllipseObject *self, void *Py_UNUSED(closure)) {
        auto transparency = self->ellipse->getTransparency();
        return PyTuple_Pack(4, PyFloat_FromDouble(transparency.a1), PyFloat_FromDouble(transparency.a2),
                            PyFloat_FromDouble(transparency.a3), PyFloat_FromDouble(transparency.a4));
    }

    int set_transparency(EllipseObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.ellipse.Ellipse.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3, v4;
        if (PyArg_ParseTuple(value, "ffff", &v1, &v2, &v3, &v4)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, -1, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, -1, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, -1, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, -1, "transparency must be between 0 and 1")

            self->ellipse->setTransparency(v1, v2, v3, v4);
            return 0;
        }
        PyErr_Clear();

        if (!PyNumber_Check(value)) {
            RAISE_VALUE_ERROR(-1, "transparency must be a number");
        }

        v1 = (float) PyFloat_AsDouble(value);
        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, -1, "transparency must be between 0 and 1")

        self->ellipse->setTransparency(v1);
        return 0;
    }
}
