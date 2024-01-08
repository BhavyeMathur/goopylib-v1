#define RECTANGLE_MODULE

#include "rectangle.h"
#include "../quad/module.h"

void **PyQuad_API;
PyTypeObject *QuadType;

static struct PyModuleDef RectangleModule = {
        PyModuleDef_HEAD_INIT,
        "rectangle",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_rectangle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_rectangle()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&RectangleModule);
    if (m == nullptr) {
        return nullptr;
    }

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_rectangle() - import_quad()" << std::endl;
    #endif
    PyQuad_API = (void **) PyCapsule_Import("goopylib.ext.quad._C_API", 0);
    if (PyQuad_API == nullptr) {
        return nullptr;
    }

    QuadType = Quad_pytype();

    RectangleType.tp_base = QuadType;

    EXPOSE_PYOBJECT_CLASS(RectangleType, "Rectangle");

    return m;
}
