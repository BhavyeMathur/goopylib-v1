#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "goopylib/color/color_object.h"

#include "triangle.h"
#include "src/goopylib/objects/Triangle.h"


// Triangle Core
namespace triangle {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        TriangleObject *self;
        self = (TriangleObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    int init(TriangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.triangle.Triangle()");

        float x1, x2, x3;
        float y1, y2, y3;
        if (!PyArg_ParseTuple(args, "(ff)(ff)(ff)", &x1, &y1, &x2, &y2, &x3, &y3)) {
            return -1;
        }

        self->triangle = shared_ptr<gp::Triangle>(new gp::Triangle({x1, y1}, {x2, y2}, {x3, y3}));
        self->base.renderable = self->triangle;

        return 0;
    }

    int traverse(TriangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(TriangleObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.triangle.Triangle.clear()");
        return 0;
    }

    void dealloc(TriangleObject *self) {
        GP_PY_DEBUG("gp.triangle.Triangle.__dealloc__()");

        self->triangle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Triangle methods
namespace triangle {
    PyObject *set_color(TriangleObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.triangle.Triangle.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject * arg1, *arg2, *arg3;
        PyObject * color1;
        if (PyArg_ParseTuple(args, "OOO", &arg1, &arg2, &arg3)) {

            PyObject * color2, *color3;

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

            self->triangle->setColor(*((ColorObject *) color1)->color,
                                     *((ColorObject *) color2)->color,
                                     *((ColorObject *) color3)->color);
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

        self->triangle->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }
}

// Triangle Getters & Setters
namespace triangle {
    PyObject *get_p1(TriangleObject *self, void *Py_UNUSED(closure)) {
        Point point = self->triangle->getP1();
        return Py_BuildValue("ff", point.x, point.y);
    }

    int set_p1(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        float x, y;
        if (!PyArg_ParseTuple(value, "ff", &x, &y)) {
            return -1;
        }

        self->triangle->setP1({x, y});
        return 0;
    }

    PyObject *get_p2(TriangleObject *self, void *Py_UNUSED(closure)) {
        Point point = self->triangle->getP2();
        return Py_BuildValue("ff", point.x, point.y);
    }

    int set_p2(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        float x, y;
        if (!PyArg_ParseTuple(value, "ff", &x, &y)) {
            return -1;
        }

        self->triangle->setP2({x, y});
        return 0;
    }

    PyObject *get_p3(TriangleObject *self, void *Py_UNUSED(closure)) {
        Point point = self->triangle->getP3();
        return Py_BuildValue("ff", point.x, point.y);
    }

    int set_p3(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        float x, y;
        if (!PyArg_ParseTuple(value, "ff", &x, &y)) {
            return -1;
        }

        self->triangle->setP3({x, y});
        return 0;
    }

    PyObject *get_transparency(TriangleObject *self, void *Py_UNUSED(closure)) {
        auto transparency = self->triangle->getTransparency();
        return PyTuple_Pack(3, PyFloat_FromDouble(transparency.a1), PyFloat_FromDouble(transparency.a2),
                            PyFloat_FromDouble(transparency.a3));
    }

    int set_transparency(TriangleObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        GP_PY_DEBUG("gp.quad.Quad.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3;
        if (PyArg_ParseTuple(value, "fff", &v1, &v2, &v3)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, -1, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, -1, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, -1, "transparency must be between 0 and 1")

            self->triangle->setTransparency(v1, v2, v3);
            return 0;
        }
        PyErr_Clear();

        if (!PyNumber_Check(value)) {
            RAISE_VALUE_ERROR(-1, "transparency must be a number");
        }

        v1 = (float) PyFloat_AsDouble(value);
        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, -2, "transparency must be between 0 and 1")

        self->triangle->setTransparency(v1);
        return 0;
    }
}
