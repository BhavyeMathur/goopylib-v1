#pragma once

#include "src/extension/util.h"

#include "src/goopylib/Math/Easing.h"

struct EasingObject;

#define EASING_TYPE(name) \
static PyTypeObject type = { \
    PyVarObject_HEAD_INIT(nullptr, 0) \
    .tp_itemsize = 0, \
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, \
    .tp_new = PyType_GenericNew, \
    .tp_init = (initproc) init, \
    .tp_call = (ternaryfunc) call, \
    .tp_repr = (reprfunc) repr, \
    .tp_basicsize = sizeof(EasingObject), \
    .tp_name = (name), \
    .tp_traverse = (traverseproc) traverse, \
    .tp_clear = (inquiry) clear, \
    .tp_dealloc = (destructor) dealloc \
};

#define PyEasing_HEAD PyObject_HEAD std::function<float(float)> easing; PyObject *string;
