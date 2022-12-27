#include "goopylib/objects/Quad.h"
#include "quad.h"

#if GP_LOG_QUAD != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_QUAD
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"


struct QuadObject {
    PyObject_HEAD
    std::shared_ptr<gp::Quad> quad;
};


// Quad Core
namespace quad {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        QuadObject *self;
        self = (QuadObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(QuadObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.quad.Quad()");

        return 0;
    }

    static PyObject *repr(QuadObject *self) {
        return PyUnicode_FromString("Quad()");
    }

    static int traverse(QuadObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(QuadObject *self) {
        return 0;
    }

    static void dealloc(QuadObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->quad.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Quad Type
namespace quad {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject QuadType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Quad",
        .tp_basicsize = sizeof(QuadObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = quad::new_,
        .tp_init = (initproc) quad::init,

        .tp_methods = quad::methods,
        .tp_getset = quad::getsetters,

        .tp_traverse = (traverseproc) quad::traverse,
        .tp_clear = (inquiry) quad::clear,
        .tp_dealloc = (destructor) quad::dealloc,

        .tp_repr = (reprfunc) quad::repr,
};

static struct PyModuleDef quadmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "quad",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_quad(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_quad()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&quadmodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
