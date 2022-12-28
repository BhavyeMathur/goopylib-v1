#ifndef Py_ELLIPSE_MODULE_H
#define Py_ELLIPSE_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Ellipse_pytype_NUM 0
#define Ellipse_pytype_RETURN PyTypeObject*
#define Ellipse_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyEllipse_API_pointers 1

#ifdef ELLIPSE_MODULE

static Ellipse_pytype_RETURN Ellipse_pytype Ellipse_pytype_PROTO;

#else
#define Ellipse_pytype \
        (*(Ellipse_pytype_RETURN (*)Ellipse_pytype_PROTO) PyEllipse_API[Ellipse_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_ELLIPSE_MODULE_H) */
