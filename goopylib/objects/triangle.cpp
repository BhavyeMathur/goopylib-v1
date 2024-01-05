#define GP_LOGGING_LEVEL 3
#include "goopylib/debug.h"

#include "triangle.h"
#include "renderable_module.h"
#include "renderable_object.h"

#include "goopylib/color/color_object.h"
#include "goopylib/color/color_module.h"

#include "src/goopylib/objects/Triangle.h"


struct TriangleObject {
    RenderableObject base;
    Ref<gp::Triangle> triangle;
};


// Triangle Core
namespace triangle {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
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

        self->triangle = Ref<gp::Triangle>(new gp::Triangle({x1, y1}, {x2, y2}, {x3, y3}));
        self->base.renderable = self->triangle;

        return 0;
    }

    static PyObject *repr(TriangleObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.triangle.Triangle.__repr__()");
        return PyUnicode_FromString("Triangle()");
    }

    static int traverse(TriangleObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(TriangleObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.triangle.Triangle.clear()");
        return 0;
    }

    static void dealloc(TriangleObject *self) {
        GP_PY_DEBUG("gp.triangle.Triangle.__dealloc__()");

        self->triangle.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Triangle methods
namespace triangle {
    static PyObject *set_color(TriangleObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.triangle.Triangle.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject *arg1, *arg2, *arg3;
        PyObject *color1;
        if (PyArg_ParseTuple(args, "OOO", &arg1, &arg2, &arg3)) {

            PyObject *color2, *color3;

            if (!isinstance(arg1, ColorType)) {
                color1 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg1));
                GP_CHECK_NULL(color1, nullptr, "Invalid arguments to set 1st color")
            }
            else {
                color1 = arg1;
            }

            if (!isinstance(arg2, ColorType)) {
                color2 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg2));
                GP_CHECK_NULL(color2, nullptr, "Invalid arguments to set 2nd color")
            }
            else {
                color2 = arg2;
            }

            if (!isinstance(arg3, ColorType)) {
                color3 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg3));
                GP_CHECK_NULL(color3, nullptr, "Invalid arguments to set 3rd color")
            }
            else {
                color3 = arg3;
            }

            self->triangle->setColor(*((ColorObject *) color1)->color,
                                     *((ColorObject *) color2)->color,
                                     *((ColorObject *) color3)->color);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "O", &arg1)) {
            return nullptr;
        }

        if (!isinstance(arg1, ColorType)) {
            color1 = PyObject_CallObject((PyObject *) ColorType, PyTuple_Pack(1, arg1));
            GP_CHECK_NULL(color1, nullptr, "Invalid arguments to set color")
        }
        else {
            color1 = arg1;
        }

        self->triangle->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }

    static PyObject *set_transparency(TriangleObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.triangle.Triangle.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3;
        if (PyArg_ParseTuple(args, "fff", &v1, &v2, &v3)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->triangle->setTransparency(v1, v2, v3);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &v1)) {
            return nullptr;
        }

        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

        self->triangle->setTransparency(v1);
        Py_RETURN_NONE;
    }
}


// Triangle Type
namespace triangle {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},

            {nullptr}
    };
}

static PyTypeObject TriangleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Triangle",
        sizeof(TriangleObject),
        0,
        (destructor) triangle::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) triangle::repr,
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
        (traverseproc) triangle::traverse,
        (inquiry) triangle::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        triangle::methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) triangle::init,
        nullptr,
        triangle::new_,
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

static struct PyModuleDef TriangleModule = {
        PyModuleDef_HEAD_INIT,
        "triangle",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_triangle(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_triangle()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&TriangleModule);
    if (m == nullptr) {
        return nullptr;
    }

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_triangle() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_triangle() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    TriangleType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(TriangleType, "Triangle");

    return m;
}
