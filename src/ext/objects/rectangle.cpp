#include "goopylib/objects/Rectangle.h"
#include "rectangle.h"

#if GP_LOG_RECTANGLE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_RECTANGLE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"


struct RectangleObject {
    PyObject_HEAD
    std::shared_ptr<gp::Rectangle> rectangle;
};


// Rectangle Core
namespace rectangle {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        RectangleObject *self;
        self = (RectangleObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(RectangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.rectangle.Rectangle()");

        return 0;
    }

    static PyObject *repr(RectangleObject *self) {
        return PyUnicode_FromString("Rectangle()");
    }

    static int traverse(RectangleObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(RectangleObject *self) {
        return 0;
    }

    static void dealloc(RectangleObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->rectangle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Rectangle Type
namespace rectangle {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject RectangleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Rectangle",
        .tp_basicsize = sizeof(RectangleObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = rectangle::new_,
        .tp_init = (initproc) rectangle::init,

        .tp_methods = rectangle::methods,
        .tp_getset = rectangle::getsetters,

        .tp_traverse = (traverseproc) rectangle::traverse,
        .tp_clear = (inquiry) rectangle::clear,
        .tp_dealloc = (destructor) rectangle::dealloc,

        .tp_repr = (reprfunc) rectangle::repr,
};

static struct PyModuleDef rectanglemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "rectangle",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_rectangle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_rectangle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&rectanglemodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
