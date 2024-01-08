#define ELLIPSE_MODULE

#include "ellipse.h"
#include "module.h"
#include "capsule.h"

#include "goopylib/color/color_module.h"
#include "../renderable/module.h"

void **PyRenderable_API;
PyTypeObject *RenderableType;

void **PyColor_API;
PyTypeObject *ColorType;

static struct PyModuleDef EllipseModule = {
        PyModuleDef_HEAD_INIT,
        "ellipse",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_ellipse(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&EllipseModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Renderable

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    // Importing Color

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    // Exposing Class

    EllipseType.tp_base = RenderableType;
    EXPOSE_PYOBJECT_CLASS(EllipseType, "Ellipse");

    // Exposing Capsule

    static void *PyEllipse_API[PyEllipse_API_pointers];
    PyObject * c_api_object;

    PyEllipse_API[Ellipse_pytype_NUM] = (void *) Ellipse_pytype;
    c_api_object = PyCapsule_New((void *) PyEllipse_API, "goopylib.ext.ellipse._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
