#define QUAD_MODULE

#include "quad.h"
#include "quad_object.h"
#include "quad_module.h"
#include "quad_capsule.h"
#include "renderable_module.h"

#include "color/color_object.h"
#include "color/color_module.h"

#include "goopylib/objects/Quad.h"

#include "config.h"

#if (GP_LOG_QUAD != true) and (GP_LOG_QUAD <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_QUAD
#endif

#if !GP_VALUE_CHECK_QUAD
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


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

        float x1, x2, x3, x4;
        float y1, y2, y3, y4;
        if (!PyArg_ParseTuple(args, "(ff)(ff)(ff)(ff)", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4)) {
            return -1;
        }

        self->quad = Ref<gp::Quad>(new gp::Quad({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}));
        self->base.renderable = self->quad;

        return 0;
    }

    static PyObject *repr(QuadObject *self) {
        GP_PY_TRACE("gp.quad.Quad.__repr__()");
        return PyUnicode_FromString("Quad()");
    }

    static int traverse(QuadObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(QuadObject *self) {
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

// Quad methods
namespace quad {
    static PyObject *set_color(QuadObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.quad.Quad.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject *arg1, *arg2, *arg3, *arg4;
        PyObject *color1;
        if (PyArg_ParseTuple(args, "OOOO", &arg1, &arg2, &arg3, &arg4)) {

            PyObject *color2, *color3, *color4;

            if (!isinstance(arg1, ColorType)) {
                color1 = PyObject_CallObject((PyObject *) ColorType, arg1);

                #if GP_TYPE_CHECKING
                if (color1 == nullptr) {
                    return nullptr;
                }
                #endif
            }
            else {
                color1 = arg1;
            }

            if (!isinstance(arg2, ColorType)) {
                color2 = PyObject_CallObject((PyObject *) ColorType, arg2);

                #if GP_TYPE_CHECKING
                if (color2 == nullptr) {
                    return nullptr;
                }
                #endif
            }
            else {
                color2 = arg2;
            }

            if (!isinstance(arg3, ColorType)) {
                color3 = PyObject_CallObject((PyObject *) ColorType, arg3);

                #if GP_TYPE_CHECKING
                if (color3 == nullptr) {
                    return nullptr;
                }
                #endif
            }
            else {
                color3 = arg3;
            }

            if (!isinstance(arg4, ColorType)) {
                color4 = PyObject_CallObject((PyObject *) ColorType, arg4);

                #if GP_TYPE_CHECKING
                if (color4 == nullptr) {
                    return nullptr;
                }
                #endif
            }
            else {
                color4 = arg4;
            }

            self->quad->setColor(*((ColorObject *) color1)->color,
                                 *((ColorObject *) color2)->color,
                                 *((ColorObject *) color3)->color,
                                 *((ColorObject *) color4)->color);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "O", &arg1)) {
            return nullptr;
        }

        if (!isinstance(arg1, ColorType)) {
            color1 = PyObject_CallObject((PyObject *) ColorType, arg1);

            #if GP_TYPE_CHECKING
            if (color1 == nullptr) {
                return nullptr;
            }
            #endif
        }
        else {
            color1 = arg1;
        }

        self->quad->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }

    static PyObject *set_transparency(QuadObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.quad.Quad.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3, v4;
        if (PyArg_ParseTuple(args, "ffff", &v1, &v2, &v3, &v4)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->quad->setTransparency(v1, v2, v3, v4);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &v1)) {
            return nullptr;
        }

        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

        self->quad->setTransparency(v1);
        Py_RETURN_NONE;
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
        .tp_name = "goopylib.Quad",
        .tp_basicsize = sizeof(QuadObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = quad::new_,
        .tp_init = (initproc) quad::init,

        .tp_methods = quad::methods,

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
    PyObject *c_api_object;

    PyQuad_API[Quad_pytype_NUM] = (void *) Quad_pytype;
    c_api_object = PyCapsule_New((void *) PyQuad_API, "goopylib.ext.quad._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
