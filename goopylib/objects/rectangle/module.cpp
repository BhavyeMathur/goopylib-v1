#define RECTANGLE_MODULE

#include "rectangle.h"
#include "../quad/module.h"

#include "module.h"
#include "capsule.h"


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

    // Importing Quad

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_rectangle() - import_quad()" << std::endl;
    #endif
    PyQuad_API = (void **) PyCapsule_Import("goopylib.ext.quad._C_API", 0);
    if (PyQuad_API == nullptr) {
        return nullptr;
    }

    QuadType = Quad_pytype();

    // Exposing Rectangle

    RectangleType.tp_base = QuadType;

    EXPOSE_PYOBJECT_CLASS(RectangleType, "Rectangle");

    // Exposing Capsule

    static void *PyRectangle_API[PyRectangle_API_pointers];
    PyObject * c_api_object;

    PyRectangle_API[Rectangle_pytype_NUM] = (void *) Rectangle_pytype;
    c_api_object = PyCapsule_New((void *) PyRectangle_API, "goopylib.ext.rectangle._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
