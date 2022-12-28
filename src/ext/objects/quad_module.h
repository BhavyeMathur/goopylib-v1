#ifndef Py_QUAD_MODULE_H
#define Py_QUAD_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Quad_pytype_NUM 0
#define Quad_pytype_RETURN PyTypeObject*
#define Quad_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyQuad_API_pointers 1

#ifdef QUAD_MODULE

static Quad_pytype_RETURN Quad_pytype Quad_pytype_PROTO;

#else
#define Quad_pytype \
        (*(Quad_pytype_RETURN (*)Quad_pytype_PROTO) PyQuad_API[Quad_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_QUAD_MODULE_H) */
