#include "goopylib/objects/Line.h"
#include "line.h"

#if GP_LOG_LINE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_LINE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"


struct LineObject {
    PyObject_HEAD
    std::shared_ptr<gp::Line> line;
};


// Line Core
namespace line {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        LineObject *self;
        self = (LineObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(LineObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.line.Line()");

        return 0;
    }

    static PyObject *repr(LineObject *self) {
        return PyUnicode_FromString("Line()");
    }

    static int traverse(LineObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(LineObject *self) {
        return 0;
    }

    static void dealloc(LineObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->line.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Line Type
namespace line {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject LineType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Line",
        .tp_basicsize = sizeof(LineObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = line::new_,
        .tp_init = (initproc) line::init,

        .tp_methods = line::methods,
        .tp_getset = line::getsetters,

        .tp_traverse = (traverseproc) line::traverse,
        .tp_clear = (inquiry) line::clear,
        .tp_dealloc = (destructor) line::dealloc,

        .tp_repr = (reprfunc) line::repr,
};

static struct PyModuleDef linemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "line",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_line(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_line()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&linemodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
