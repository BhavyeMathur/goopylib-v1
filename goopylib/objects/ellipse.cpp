#define ELLIPSE_MODULE

#include "ellipse.h"
#include "ellipse_object.h"
#include "ellipse_module.h"
#include "ellipse_capsule.h"
#include "renderable_module.h"

#include "color/color_object.h"
#include "color/color_module.h"

#include "goopylib/objects/Ellipse.h"

#include "config.h"

#if (GP_LOG_ELLIPSE != true) and (GP_LOG_ELLIPSE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_ELLIPSE
#endif

#if !GP_VALUE_CHECK_ELLIPSE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


// Ellipse Core
namespace ellipse {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
        EllipseObject *self;
        self = (EllipseObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(EllipseObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.ellipse.Ellipse()");

        float x1, y1;
        float radius1, radius2;
        if (PyArg_ParseTuple(args, "(ff)ff", &x1, &y1, &radius1, &radius2)) {
            self->ellipse = Ref<gp::Ellipse>(new gp::Ellipse({x1, y1}, radius1, radius2));
            self->base.renderable = self->ellipse;
            return 0;
        }
        PyErr_Clear();

        float x2, y2;
        if (!PyArg_ParseTuple(args, "(ff)(ff)", &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->ellipse = Ref<gp::Ellipse>(new gp::Ellipse({x1, y1}, {x2, y2}));
        self->base.renderable = self->ellipse;
        return 0;
    }

    static PyObject *repr(EllipseObject *self) {
        GP_PY_TRACE("gp.ellipse.Ellipse.__repr__()");
        return PyUnicode_FromString("Ellipse()");
    }

    static int traverse(EllipseObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(EllipseObject *self) {
        GP_PY_TRACE("gp.ellipse.Ellipse.clear()");
        return 0;
    }

    static void dealloc(EllipseObject *self) {
        GP_PY_DEBUG("gp.ellipse.Ellipse.__dealloc__()");

        self->ellipse.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Ellipse methods
namespace ellipse {
    static PyObject *set_color(EllipseObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.ellipse.Ellipse.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

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

            self->ellipse->setColor(*((ColorObject *) color1)->color,
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

        self->ellipse->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }

    static PyObject *set_transparency(EllipseObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.ellipse.Ellipse.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3, v4;
        if (PyArg_ParseTuple(args, "ffff", &v1, &v2, &v3, &v4)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->ellipse->setTransparency(v1, v2, v3, v4);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &v1)) {
            return nullptr;
        }

        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

        self->ellipse->setTransparency(v1);
        Py_RETURN_NONE;
    }
}


// Ellipse Type
namespace ellipse {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},

            {nullptr}
    };
}

PyTypeObject EllipseType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Ellipse",
        .tp_basicsize = sizeof(EllipseObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,

        .tp_new = ellipse::new_,
        .tp_init = (initproc) ellipse::init,

        .tp_methods = ellipse::methods,

        .tp_traverse = (traverseproc) ellipse::traverse,
        .tp_clear = (inquiry) ellipse::clear,
        .tp_dealloc = (destructor) ellipse::dealloc,

        .tp_repr = (reprfunc) ellipse::repr,
};

static struct PyModuleDef ellipsemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "ellipse",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_ellipse(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&ellipsemodule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Renderable

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    // Importing Color

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_ellipse() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    // Exposing Class

    EllipseType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(EllipseType, "Ellipse");

    // Exposing Capsule

    static void *PyEllipse_API[PyEllipse_API_pointers];
    PyObject *c_api_object;

    PyEllipse_API[Ellipse_pytype_NUM] = (void *) Ellipse_pytype;
    c_api_object = PyCapsule_New((void *) PyEllipse_API, "goopylib.ext.ellipse._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
