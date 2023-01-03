#pragma once

#include <Python.h>
#include <iostream>

#include <memory>
#include <string>
#include <stdexcept>

#define EXPOSE_PYOBJECT_CLASS(ObjectType, name) \
do { if (PyType_Ready(&(ObjectType)) < 0) return nullptr; \
    Py_INCREF(&(ObjectType)); \
    if (PyModule_AddObject(m, name, (PyObject *) &(ObjectType)) < 0) { \
        Py_DECREF(&(ObjectType)); \
        Py_DECREF(m); \
        return nullptr; \
    }                                      \
} while (0)

#define INITIALIZE_PYOBJECT(variable, value) Py_INCREF((value)); variable = value
#define SET_PYOBJECT(variable, value) PyObject *tmp = variable; INITIALIZE_PYOBJECT(variable, value); Py_XDECREF(tmp)
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
