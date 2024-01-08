#pragma once

#include "goopylib/debug.h"

#include "goopylib/color/color_module.h"
#include "goopylib/color/color_object.h"

#include "renderable_object.h"

#include "quad.h"
#include "src/goopylib/objects/Quad.h"


struct QuadObject {
    RenderableObject base;
    Ref<gp::Quad> quad;
};

namespace quad {
    PyObject *set_color(QuadObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.quad.Quad.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject *arg1, *arg2, *arg3, *arg4;
        PyObject *color1;

        if (PyArg_ParseTuple(args, "OOOO", &arg1, &arg2, &arg3, &arg4)) {

            PyObject *color2, *color3, *color4;

            if (!isinstance(arg1, ColorType)) {
                color1 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg1));
                GP_CHECK_NULL(color1, nullptr, "Invalid 1st color argument")
            }
            else {
                color1 = arg1;
            }

            if (!isinstance(arg2, ColorType)) {
                color2 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg2));
                GP_CHECK_NULL(color2, nullptr, "Invalid 2nd color argument")
            }
            else {
                color2 = arg2;
            }

            if (!isinstance(arg3, ColorType)) {
                color3 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg3));
                GP_CHECK_NULL(color3, nullptr, "Invalid 3rd color argument")
            }
            else {
                color3 = arg3;
            }

            if (!isinstance(arg4, ColorType)) {
                color4 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg4));
                GP_CHECK_NULL(color4, nullptr, "Invalid 4th color argument")
            }
            else {
                color4 = arg4;
            }

            self->quad->setColor(*((ColorObject *) color1)->color,
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
            GP_CHECK_NULL(color1, nullptr, "Invalid argument to set color")
        }
        else {
            color1 = arg1;
        }

        self->quad->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }

    PyObject *set_transparency(QuadObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.quad.Quad.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3, v4;
        if (PyArg_ParseTuple(args, "ffff", &v1, &v2, &v3, &v4)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->quad->setTransparency(v1, v2, v3, v4);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &v1)) {
            return nullptr;
        }

        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

        self->quad->setTransparency(v1);
        Py_RETURN_NONE;
    }
}
