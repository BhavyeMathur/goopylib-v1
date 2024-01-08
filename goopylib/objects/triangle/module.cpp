#define TRIANGLE_MODULE

#include "triangle.h"
#include "../renderable/module.h"
#include "goopylib/color/color_module.h"

void **PyRenderable_API;
PyTypeObject *RenderableType;

void **PyColor_API;
PyTypeObject *ColorType;

static struct PyModuleDef TriangleModule = {
        PyModuleDef_HEAD_INIT,
        "triangle",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_triangle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_triangle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&TriangleModule);
    if (m == nullptr) {
        return nullptr;
    }

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_triangle() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_triangle() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    TriangleType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(TriangleType, "Triangle");

    return m;
}
