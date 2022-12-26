#pragma once

#include "color.h"


static PyObject *Color_create(PyObject *value) {
    return PyObject_Call((PyObject *) &ColorType, value, Py_None);
}

static bool Color_isinstance(PyObject *object) {
    return PyObject_IsInstance(object, (PyObject *) &ColorType);
}

static gp::Color Color_get_pointer(PyObject *object) {
    return *((ColorObject *) object)->color;
}
