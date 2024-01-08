#include "line.h"
#include "../quad/module.h"
#include "goopylib/color/color_module.h"

void **PyColor_API;
PyTypeObject *ColorType;

void **PyQuad_API;
PyTypeObject *QuadType;

static struct PyModuleDef LineModule = {
        PyModuleDef_HEAD_INIT,
        "line",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_line(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_line()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&LineModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Color

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_quad() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    // Importing Quad

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_line() - import_quad()" << std::endl;
    #endif
    PyQuad_API = (void **) PyCapsule_Import("goopylib.ext.quad._C_API", 0);
    if (PyQuad_API == nullptr) {
        return nullptr;
    }

    QuadType = Quad_pytype();

    LineType.tp_base = QuadType;

    EXPOSE_PYOBJECT_CLASS(LineType, "Line");

    return m;
}
