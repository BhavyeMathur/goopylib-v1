#ifndef Py_COLOR_MODULE_H
#define Py_COLOR_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Color_pytype_NUM 0
#define Color_pytype_RETURN PyTypeObject*
#define Color_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyColor_API_pointers 1

#ifdef COLOR_MODULE

static Color_pytype_RETURN Color_pytype Color_pytype_PROTO;

#else
#define Color_pytype \
        (*(Color_pytype_RETURN (*)Color_pytype_PROTO) PyColor_API[Color_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_COLOR_MODULE_H) */
