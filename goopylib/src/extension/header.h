#pragma once

#include <Python.h>
#include <iostream>

#include "config.h"

#define EXPOSE_PYOBJECT_CLASS(ObjectType, name) \
do { if (PyType_Ready(&(ObjectType)) < 0) return nullptr; \
    Py_INCREF(&(ObjectType)); \
    if (PyModule_AddObject(m, name, (PyObject *) &(ObjectType)) < 0) { \
        Py_DECREF(&(ObjectType)); \
        Py_DECREF(m); \
        return nullptr; \
    }                                      \
} while (0)

#define SET_PYOBJECT(attribute, value) PyObject *tmp = attribute; Py_INCREF((value)); (attribute) = value; Py_XDECREF(tmp)
#define RETURN_PYOBJECT(name) Py_INCREF(name); return name
#define PYOBJECT_NAME(object) object->ob_type->tp_name
