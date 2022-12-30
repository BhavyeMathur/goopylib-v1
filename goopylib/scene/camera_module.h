#ifndef Py_CAMERA_MODULE_H
#define Py_CAMERA_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* C++ API functions */
#define Camera_pytype_NUM 0
#define Camera_pytype_RETURN PyTypeObject*
#define Camera_pytype_PROTO ()

/* Total number of C++ API pointers */
#define PyCamera_API_pointers 1

#ifdef CAMERA_MODULE

static Camera_pytype_RETURN Camera_pytype Camera_pytype_PROTO;

#else
#define Camera_pytype \
        (*(Camera_pytype_RETURN (*)Camera_pytype_PROTO) PyCamera_API[Camera_pytype_NUM])

#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined(Py_CAMERA_MODULE_H) */
