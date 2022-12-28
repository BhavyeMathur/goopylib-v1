#ifndef Py_WINDOW_MODULE_H
#define Py_WINDOW_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Window_pytype_NUM 0
#define Window_pytype_RETURN PyTypeObject*
#define Window_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyWindow_API_pointers 1

#ifdef WINDOW_MODULE

static Window_pytype_RETURN Window_pytype Window_pytype_PROTO;

#else
#define Window_pytype \
        (*(Window_pytype_RETURN (*)Window_pytype_PROTO) PyWindow_API[Window_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_WINDOW_MODULE_H) */
