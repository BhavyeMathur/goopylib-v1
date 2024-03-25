#pragma once

#include <Python.h>
#include <iostream>

#include <memory>
#include <string>
#include <stdexcept>

#define EXPOSE_PYOBJECT_CLASS(ObjectType, name) \
if (PyType_Ready(&(ObjectType)) < 0) return nullptr; \
Py_INCREF(&(ObjectType)); \
if (PyModule_AddObject(m, name, (PyObject *) &(ObjectType)) < 0) { \
    Py_DECREF(&(ObjectType)); \
    Py_DECREF(m); \
    return nullptr; }

#if GP_LOGGING_LEVEL >= 6
#define IMPORT_GP_MODULE_LOG(this, module) std::cout << "[--:--:--] PYTHON: PyInit_##this() - import_##module()" << std::endl;
#else
#define IMPORT_GP_MODULE_LOG(this, module)
#endif

#define INITIALIZE_PYOBJECT(variable, value) Py_INCREF((value)); (variable) = value
#define SET_PYOBJECT(variable, value) PyObject *tmp = variable; INITIALIZE_PYOBJECT(variable, value); Py_XDECREF(tmp)
#define RETURN_PYOBJECT(name) Py_INCREF(name); return name
#define PYOBJECT_NAME(object) object->ob_type->tp_name

#define GETTER_SETTER(name) {#name, (getter) get_##name, (setter) set_##name, #name, nullptr}

#undef Py_VISIT
#define Py_VISIT(op)                                                    \
    do {                                                                \
        if (op) {                                                       \
            const int vret = visit(_PyObject_CAST(op), arg);            \
            if (vret)                                                   \
                return vret;                                            \
        }                                                               \
    } while (0)

static bool isinstance(PyObject * object, PyTypeObject * type) {
    return PyObject_IsInstance(object, (PyObject *) type);
}

using std::make_unique, std::make_shared, std::shared_ptr, std::unique_ptr;

#define GP_RETHROW_ERROR(code, error, msg) try { code; } catch (std::runtime_error &e) { throw py::error(msg); };
#define GP_RETHROW_TYPE_ERROR(code, type) GP_RETHROW_ERROR(code, type_error, "Expected " #type " argument")
#define GP_RETHROW_TYPE_ERROR_POSITION(code, type, pos) GP_RETHROW_ERROR(code, type_error, "Expected " #type " argument in position " #pos)

#define GP_GET_VALUE_ATTR(attr) value.attr
#define GP_GET_STRUCT_TUPLE_BODY(func, ...) auto value = self.get##func(); return py::make_tuple(MAP_LIST(GP_GET_VALUE_ATTR, __VA_ARGS__))
#define GP_GET_STRUCT_TUPLE(type, func, ...) [](const type &self) { GP_GET_STRUCT_TUPLE_BODY(func, __VA_ARGS__); }

#define GP_GET_ELEMENT_FROM_TUPLE(el, type) int value##el; GP_RETHROW_TYPE_ERROR_POSITION(value##el = object[el].cast<type>(), type, el)
