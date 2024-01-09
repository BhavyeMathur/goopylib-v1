#ifndef Py_RECTANGLE_MODULE_H
#define Py_RECTANGLE_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Rectangle_pytype_NUM 0
#define Rectangle_pytype_RETURN PyTypeObject*
#define Rectangle_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyRectangle_API_pointers 1

#ifdef RECTANGLE_MODULE

static Rectangle_pytype_RETURN Rectangle_pytype Rectangle_pytype_PROTO;

#else
#define Rectangle_pytype \
        (*(Rectangle_pytype_RETURN (*)Rectangle_pytype_PROTO) PyRectangle_API[Rectangle_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_RECTANGLE_MODULE_H) */
