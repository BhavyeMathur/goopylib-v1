#define IMAGE_MODULE

#include "image.h"
#include "../rectangle/module.h"


void **PyRectangle_API;
PyTypeObject *RectangleType;

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

    RectangleType = Rectangle_pytype();

    // Exposing Class

    ImageType.tp_base = RectangleType;

    EXPOSE_PYOBJECT_CLASS(ImageType, "Image");

    return m;
}
