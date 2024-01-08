#define RENDERABLE_MODULE

#include "renderable.h"

#include "module.h"
#include "capsule.h"

#include "goopylib/core/window_module.h"

void **PyWindow_API;
PyTypeObject *WindowType;

static struct PyModuleDef RenderableModule = {
        PyModuleDef_HEAD_INIT,
        "renderable",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_renderable(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_renderable()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&RenderableModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Window

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_renderable() - import_window()" << std::endl;
    #endif
    PyWindow_API = (void **) PyCapsule_Import("goopylib.ext.window._C_API", 0);
    if (PyWindow_API == nullptr) {
        return nullptr;
    }

    WindowType = Window_pytype();

    // Exposing class

    EXPOSE_PYOBJECT_CLASS(RenderableType, "Renderable");

    // Exposing capsule

    static void *PyRenderable_API[PyRenderable_API_pointers];
    PyObject * c_api_object;

    PyRenderable_API[Renderable_pytype_NUM] = (void *) Renderable_pytype;
    c_api_object = PyCapsule_New((void *) PyRenderable_API, "goopylib.ext.renderable._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
