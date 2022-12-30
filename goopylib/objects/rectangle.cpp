#include "rectangle.h"
#include "quad_module.h"
#include "quad_object.h"

#include "goopylib/objects/Rectangle.h"

#include "config.h"

#if (GP_LOG_RECTANGLE != true) and (GP_LOG_RECTANGLE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_RECTANGLE
#endif

#if !GP_VALUE_CHECK_RECTANGLE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


struct RectangleObject {
    QuadObject base;
    Ref<gp::Rectangle> rectangle;
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

        float x1, y1;
        float width, height;
        if (PyArg_ParseTuple(args, "(ff)ff", &x1, &y1, &width, &height)) {
            self->rectangle = Ref<gp::Rectangle>(new gp::Rectangle({x1, y1}, width, height));
            self->base.quad = self->rectangle;
            self->base.base.renderable = self->rectangle;
            return 0;
        }
        PyErr_Clear();

        float x2, y2;
        if (!PyArg_ParseTuple(args, "(ff)(ff)", &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->rectangle = Ref<gp::Rectangle>(new gp::Rectangle({x1, y1}, {x2, y2}));
        self->base.quad = self->rectangle;
        self->base.base.renderable = self->rectangle;
        return 0;
    }

    static PyObject *repr(RectangleObject *self) {
        GP_PY_TRACE("gp.rectangle.Rectangle.__repr__()");
        return PyUnicode_FromString("Rectangle()");
    }

    static int traverse(RectangleObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(RectangleObject *self) {
        GP_PY_TRACE("gp.rectangle.Rectangle.clear()");
        return 0;
    }

    static void dealloc(RectangleObject *self) {
        GP_PY_DEBUG("gp.rectangle.Rectangle.__dealloc__()");

        self->rectangle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}


PyTypeObject RectangleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Rectangle",
        .tp_basicsize = sizeof(RectangleObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = rectangle::new_,
        .tp_init = (initproc) rectangle::init,

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

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_rectangle() - import_quad()" << std::endl;
    #endif
    PyQuad_API = (void **) PyCapsule_Import("goopylib.ext.quad._C_API", 0);
    if (PyQuad_API == nullptr) {
        return nullptr;
    }

    QuadType = Quad_pytype();

    RectangleType.tp_base = QuadType;

    EXPOSE_PYOBJECT_CLASS(RectangleType, "Rectangle");

    return m;
}
