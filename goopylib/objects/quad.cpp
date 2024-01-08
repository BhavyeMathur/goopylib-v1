#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#define QUAD_MODULE

#include "quad_object.h"
#include "quad_module.h"
#include "quad_capsule.h"
#include "renderable_module.h"

#include "src/goopylib/objects/Quad.h"


// Quad Core
namespace quad {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        QuadObject *self;
        self = (QuadObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(QuadObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.quad.Quad()");

        float x1, x2, x3, x4;
        float y1, y2, y3, y4;
        if (!PyArg_ParseTuple(args, "(ff)(ff)(ff)(ff)", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4)) {
            return -1;
        }

        self->quad = Ref<gp::Quad>(new gp::Quad({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}));
        self->base.renderable = self->quad;

        return 0;
    }

    static PyObject *repr(QuadObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.quad.Quad.__repr__()");
        return PyUnicode_FromString("Quad()");
    }

    static int traverse(QuadObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(QuadObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.quad.Quad.clear()");
        return 0;
    }

    static void dealloc(QuadObject *self) {
        GP_PY_DEBUG("gp.quad.Quad.__dealloc__()");

        self->quad.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}


// Quad Type
namespace quad {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},

            {nullptr}
    };
}

PyTypeObject QuadType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Quad",
        sizeof(QuadObject),
        0,
        (destructor) quad::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) quad::repr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,
        "",
        (traverseproc) quad::traverse,
        (inquiry) quad::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        (PyMethodDef *) quad::methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) quad::init,
        nullptr,
        quad::new_,
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

static struct PyModuleDef QuadModule = {
        PyModuleDef_HEAD_INIT,
        "quad",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_quad(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_quad()" << std::endl;
    #endif

    PyObject * m = PyModule_Create(&QuadModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Renderable

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_quad() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    // Importing Color

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_quad() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    // Exposing Class

    QuadType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(QuadType, "Quad");

    // Exposing Capsule

    static void *PyQuad_API[PyQuad_API_pointers];
    PyObject * c_api_object;

    PyQuad_API[Quad_pytype_NUM] = (void *) Quad_pytype;
    c_api_object = PyCapsule_New((void *) PyQuad_API, "goopylib.ext.quad._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
