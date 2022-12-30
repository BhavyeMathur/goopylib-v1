#include "circle.h"
#include "ellipse_module.h"
#include "ellipse_object.h"

#include "goopylib/objects/Circle.h"

#include "config.h"

#if (GP_LOG_CIRCLE != true) and (GP_LOG_CIRCLE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CIRCLE
#endif

#if !GP_VALUE_CHECK_CIRCLE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


struct CircleObject {
    EllipseObject base;
    Ref<gp::Circle> circle;
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

        float x1, y1;
        float radius;
        if (!PyArg_ParseTuple(args, "(ff)f", &x1, &y1, &radius)) {
            return -1;
        }

        self->circle = Ref<gp::Circle>(new gp::Circle({x1, y1}, radius));
        self->base.ellipse = self->circle;
        self->base.base.renderable = self->circle;
        return 0;
    }

    static PyObject *repr(CircleObject *self) {
        GP_PY_TRACE("gp.circle.Circle.__repr__()");
        return PyUnicode_FromString("Circle()");
    }

    static int traverse(CircleObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(CircleObject *self) {
        GP_PY_TRACE("gp.circle.Circle.clear()");
        return 0;
    }

    static void dealloc(CircleObject *self) {
        GP_PY_DEBUG("gp.circle.Circle.__dealloc__()");

        self->circle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}


PyTypeObject CircleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Circle",
        .tp_basicsize = sizeof(CircleObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = circle::new_,
        .tp_init = (initproc) circle::init,

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

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_circle() - import_ellipse()" << std::endl;
    #endif
    PyEllipse_API = (void **) PyCapsule_Import("goopylib.ext.ellipse._C_API", 0);
    if (PyEllipse_API == nullptr) {
        return nullptr;
    }

    EllipseType = Ellipse_pytype();

    CircleType.tp_base = EllipseType;

    EXPOSE_PYOBJECT_CLASS(CircleType, "Circle");

    return m;
}
