#define IMAGE_MODULE

#include "image.h"
#include "../rectangle/module.h"

#include "goopylib/core/window_module.h"


void **PyRectangle_API;
PyTypeObject *RectangleType;

void **PyWindow_API;
PyTypeObject *WindowType;

static struct PyModuleDef ImageModule = {
        PyModuleDef_HEAD_INIT,
        "image",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_image(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_image()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&ImageModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Rectangle

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_image() - import_rectangle()" << std::endl;
    #endif
    PyRectangle_API = (void **) PyCapsule_Import("goopylib.ext.rectangle._C_API", 0);
    if (PyRectangle_API == nullptr) {
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

    RectangleType = Rectangle_pytype();

    // Exposing Class

    ImageType.tp_base = RectangleType;

    EXPOSE_PYOBJECT_CLASS(ImageType, "Image");

    return m;
}
