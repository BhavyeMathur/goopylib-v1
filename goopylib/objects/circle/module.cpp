#include "circle.h"
#include "../ellipse/module.h"

void **PyEllipse_API;
PyTypeObject *EllipseType;

static struct PyModuleDef CircleModule = {
        PyModuleDef_HEAD_INIT,
        "circle",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_circle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_circle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&CircleModule);
    if (m == nullptr) {
        return nullptr;
    }

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_circle() - import_ellipse()" << std::endl;
    #endif
    PyEllipse_API = (void **) PyCapsule_Import("goopylib.ext.ellipse._C_API", 0);
    if (PyEllipse_API == nullptr) {
        return nullptr;
    }

    EllipseType = Ellipse_pytype();

    CircleType.tp_base = EllipseType;

    EXPOSE_PYOBJECT_CLASS(CircleType, "Circle");

    return m;
}
