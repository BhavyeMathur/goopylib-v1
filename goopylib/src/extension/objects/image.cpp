#include "src/goopylib/objects/Image.h"
#include "image.h"

#if GP_LOG_IMAGE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_IMAGE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "extension/debug.h"


struct ImageObject {
    PyObject_HEAD
    std::shared_ptr<gp::Image> image;
};


// Image Core
namespace image {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        ImageObject *self;
        self = (ImageObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(ImageObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.image.Image()");

        return 0;
    }

    static PyObject *repr(ImageObject *self) {
        return PyUnicode_FromString("Image()");
    }

    static int traverse(ImageObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(ImageObject *self) {
        return 0;
    }

    static void dealloc(ImageObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->image.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Image Type
namespace image {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject ImageType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Image",
        .tp_basicsize = sizeof(ImageObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = image::new_,
        .tp_init = (initproc) image::init,

        .tp_methods = image::methods,
        .tp_getset = image::getsetters,

        .tp_traverse = (traverseproc) image::traverse,
        .tp_clear = (inquiry) image::clear,
        .tp_dealloc = (destructor) image::dealloc,

        .tp_repr = (reprfunc) image::repr,
};

static struct PyModuleDef imagemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "image",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_image(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_image()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&imagemodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
