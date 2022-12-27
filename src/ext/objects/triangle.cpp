#include "goopylib/objects/Triangle.h"
#include "renderable.h"
#include "triangle.h"

#if GP_LOG_TRIANGLE != true
#undef GP_PY_LOGGING_LEVEL
#define GP_PY_LOGGING_LEVEL GP_LOG_TRIANGLE
#endif

#if !GP_VALUE_CHECK_CORE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"


struct TriangleObject {
    RenderableObject base;
    std::shared_ptr<gp::Triangle> triangle;
};


// Triangle Core
namespace triangle {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        TriangleObject *self;
        self = (TriangleObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(TriangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.triangle.Triangle()");

        float x1, x2, x3;
        float y1, y2, y3;
        if (!PyArg_ParseTuple(args, "(ff)(ff)(ff)", &x1, &y1, &x2, &y2, &x3, &y3)) {
            return -1;
        }

        self->triangle = std::shared_ptr<gp::Triangle>(new gp::Triangle({x1, y1}, {x2, y2}, {x3, y3}));
        self->base.renderable = self->triangle;

        return 0;
    }

    static PyObject *repr(TriangleObject *self) {
        return PyUnicode_FromString("Triangle()");
    }

    static int traverse(TriangleObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(TriangleObject *self) {
        return 0;
    }

    static void dealloc(TriangleObject *self) {
        GP_PY_DEBUG("gp.window.Window.dealloc()");

        self->triangle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Triangle Type
namespace triangle {
    static PyMethodDef methods[] = {
            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {nullptr}
    };
}

PyTypeObject TriangleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Triangle",
        .tp_basicsize = sizeof(TriangleObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = triangle::new_,
        .tp_init = (initproc) triangle::init,

        .tp_methods = triangle::methods,
        .tp_getset = triangle::getsetters,

        .tp_traverse = (traverseproc) triangle::traverse,
        .tp_clear = (inquiry) triangle::clear,
        .tp_dealloc = (destructor) triangle::dealloc,

        .tp_repr = (reprfunc) triangle::repr,
};

static struct PyModuleDef trianglemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "triangle",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_triangle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_triangle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&trianglemodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(TriangleType, "Triangle");

    TriangleType.tp_base = &RenderableType;

    return m;
}
