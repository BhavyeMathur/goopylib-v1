#include "image.h"
#include "../renderable/module.h"

void **PyRenderable_API;
PyTypeObject *RenderableType;

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

    // Importing Renderable

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_image() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    // Exposing Class

    ImageType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(ImageType, "Image");

    return m;
}
