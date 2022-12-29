#pragma once

#include <Python.h>
#include <iostream>

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

#define GETTER_SETTER(name) {#name, (getter) get_##name, (setter) set_##name, #name, nullptr}

static bool isinstance(PyObject *object, PyTypeObject *type) {
    return PyObject_IsInstance(object, (PyObject *) type);
}

template<typename T>
    using Scope = std::unique_ptr<T>;

template<typename T>
    using Ref = std::shared_ptr<T>;
