#include <Python.h>
#include <goopylib/color/Color.h>

#ifndef Py_COLORMODULE_H
#define Py_COLORMODULE_H

#ifdef __cplusplus
extern "C" {
#endif

    /* C++ API functions */
    #define Color_create_NUM 0
    #define Color_create_RETURN PyObject*
    #define Color_create_PROTO (PyObject *value)

    #define Color_isinstance_NUM 1
    #define Color_isinstance_RETURN bool
    #define Color_isinstance_PROTO (PyObject *value)

    #define Color_get_pointer_NUM 2
    #define Color_get_pointer_RETURN gp::Color
    #define Color_get_pointer_PROTO (PyObject *object)

    /* Total number of C++ API pointers */
    #define PyColor_API_pointers 3

    #ifdef COLOR_MODULE

        static Color_create_RETURN Color_create Color_create_PROTO;
        static Color_isinstance_RETURN Color_isinstance Color_isinstance_PROTO;
        static Color_get_pointer_RETURN Color_get_pointer Color_get_pointer_PROTO;

    #else

        static void **PyColor_API;

        #define Color_create \
        (*(Color_create_RETURN (*)Color_create_PROTO) PyColor_API[Color_create_NUM])

        #define Color_isinstance \
        (*(Color_isinstance_RETURN (*)Color_isinstance_PROTO) PyColor_API[Color_isinstance_NUM])

        #define Color_get_pointer \
        (*(Color_get_pointer_RETURN (*)Color_get_pointer_PROTO) PyColor_API[Color_get_pointer_NUM])

        static int import_color() {
            PyColor_API = (void **) PyCapsule_Import("ext.color._C_API", 0);
            return (PyColor_API != nullptr) ? 0 : -1;
        }

    #endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_COLORMODULE_H) */
