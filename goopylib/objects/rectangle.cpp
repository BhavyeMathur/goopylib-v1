#define GP_LOGGING_LEVEL 3
#include "goopylib/debug.h"

#include "rectangle.h"
#include "quad_module.h"
#include "quad_object.h"

#include "src/goopylib/objects/Rectangle.h"


struct RectangleObject {
    QuadObject base;
    Ref<gp::Rectangle> rectangle;
};


// Rectangle Core
namespace rectangle {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
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

    static PyObject *repr(RectangleObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.rectangle.Rectangle.__repr__()");
        return PyUnicode_FromString("Rectangle()");
    }

    static int traverse(RectangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(RectangleObject *Py_UNUSED(self)) {
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


static PyTypeObject RectangleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Rectangle",
        sizeof(RectangleObject),
        0,
        (destructor) rectangle::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) rectangle::repr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        "",
        (traverseproc) rectangle::traverse,
        (inquiry) rectangle::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) rectangle::init,
        nullptr,
        rectangle::new_,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        nullptr,
        nullptr
};

static struct PyModuleDef RectangleModule = {
        PyModuleDef_HEAD_INIT,
        "rectangle",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_rectangle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_rectangle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&RectangleModule);
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
