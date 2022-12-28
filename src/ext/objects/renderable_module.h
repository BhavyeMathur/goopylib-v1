#ifndef Py_RENDERABLE_MODULE_H
#define Py_RENDERABLE_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Renderable_pytype_NUM 0
#define Renderable_pytype_RETURN PyTypeObject*
#define Renderable_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyRenderable_API_pointers 1

#ifdef RENDERABLE_MODULE

static Renderable_pytype_RETURN Renderable_pytype Renderable_pytype_PROTO;

#else
#define Renderable_pytype \
        (*(Renderable_pytype_RETURN (*)Renderable_pytype_PROTO) PyRenderable_API[Renderable_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_RENDERABLE_MODULE_H) */
