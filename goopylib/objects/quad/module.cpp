#define QUAD_MODULE

#include "quad.h"

#include "../renderable/module.h"
#include "goopylib/color/color_module.h"

#include "module.h"
#include "capsule.h"


void **PyRenderable_API;
PyTypeObject *RenderableType;

void **PyColor_API;
PyTypeObject *ColorType;

static struct PyModuleDef QuadModule = {
        PyModuleDef_HEAD_INIT,
        "quad",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_quad(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_quad()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&QuadModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Renderable

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_quad() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    // Importing Color

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_quad() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    // Exposing Class

    QuadType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(QuadType, "Quad");

    // Exposing Capsule

    static void *PyQuad_API[PyQuad_API_pointers];
    PyObject * c_api_object;

    PyQuad_API[Quad_pytype_NUM] = (void *) Quad_pytype;
    c_api_object = PyCapsule_New((void *) PyQuad_API, "goopylib.ext.quad._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
