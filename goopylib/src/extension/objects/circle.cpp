#include "src/goopylib/objects/Circle.h"
#include "circle.h"

#if GP_LOG_CIRCLE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_CIRCLE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "extension/debug.h"


struct CircleObject {
    PyObject_HEAD
    std::shared_ptr<gp::Circle> circle;
};


// Circle Core
namespace circle {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        CircleObject *self;
        self = (CircleObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(CircleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.circle.Circle()");

        return 0;
    }

    static PyObject *repr(CircleObject *self) {
        return PyUnicode_FromString("Circle()");
    }

    static int traverse(CircleObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(CircleObject *self) {
        return 0;
    }

    static void dealloc(CircleObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->circle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Circle Type
namespace circle {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject CircleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Circle",
        .tp_basicsize = sizeof(CircleObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = circle::new_,
        .tp_init = (initproc) circle::init,

        .tp_methods = circle::methods,
        .tp_getset = circle::getsetters,

        .tp_traverse = (traverseproc) circle::traverse,
        .tp_clear = (inquiry) circle::clear,
        .tp_dealloc = (destructor) circle::dealloc,

        .tp_repr = (reprfunc) circle::repr,
};

static struct PyModuleDef circlemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "circle",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_circle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_circle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&circlemodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
