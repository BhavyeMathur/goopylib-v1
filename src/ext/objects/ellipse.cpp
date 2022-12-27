#include "goopylib/objects/Ellipse.h"
#include "ellipse.h"

#if GP_LOG_ELLIPSE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_ELLIPSE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"


struct EllipseObject {
    PyObject_HEAD
    std::shared_ptr<gp::Ellipse> ellipse;
};


// Ellipse Core
namespace ellipse {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        EllipseObject *self;
        self = (EllipseObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(EllipseObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.ellipse.Ellipse()");

        return 0;
    }

    static PyObject *repr(EllipseObject *self) {
        return PyUnicode_FromString("Ellipse()");
    }

    static int traverse(EllipseObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(EllipseObject *self) {
        return 0;
    }

    static void dealloc(EllipseObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->ellipse.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Ellipse Type
namespace ellipse {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject EllipseType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Ellipse",
        .tp_basicsize = sizeof(EllipseObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = ellipse::new_,
        .tp_init = (initproc) ellipse::init,

        .tp_methods = ellipse::methods,
        .tp_getset = ellipse::getsetters,

        .tp_traverse = (traverseproc) ellipse::traverse,
        .tp_clear = (inquiry) ellipse::clear,
        .tp_dealloc = (destructor) ellipse::dealloc,

        .tp_repr = (reprfunc) ellipse::repr,
};

static struct PyModuleDef ellipsemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "ellipse",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_ellipse(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&ellipsemodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
