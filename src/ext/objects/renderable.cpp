#include "goopylib/objects/Renderable.h"
#include "renderable.h"

#if GP_LOG_RENDERABLE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_RENDERABLE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "extension/debug.h"


struct RenderableObject {
    PyObject_HEAD
    std::shared_ptr<gp::Renderable> renderable;
};


// Renderable Core
namespace renderable {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        RenderableObject *self;
        self = (RenderableObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(RenderableObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.renderable.Renderable()");

        return 0;
    }

    static PyObject *repr(RenderableObject *self) {
        return PyUnicode_FromString("Renderable()");
    }

    static int traverse(RenderableObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(RenderableObject *self) {
        return 0;
    }

    static void dealloc(RenderableObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->renderable.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Renderable Type
namespace renderable {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject RenderableType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Renderable",
        .tp_basicsize = sizeof(RenderableObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = renderable::new_,
        .tp_init = (initproc) renderable::init,

        .tp_methods = renderable::methods,
        .tp_getset = renderable::getsetters,

        .tp_traverse = (traverseproc) renderable::traverse,
        .tp_clear = (inquiry) renderable::clear,
        .tp_dealloc = (destructor) renderable::dealloc,

        .tp_repr = (reprfunc) renderable::repr,
};

static struct PyModuleDef renderablemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "renderable",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_renderable(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_renderable()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&renderablemodule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
