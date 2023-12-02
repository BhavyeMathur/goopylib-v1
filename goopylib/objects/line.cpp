#include "line.h"
#include "renderable_module.h"
#include "renderable_object.h"

#include "goopylib/color/color_object.h"
#include "goopylib/color/color_module.h"

#include "src/goopylib/objects/Line.h"

#include "config.h"

#if (GP_LOG_LINE != true) and (GP_LOG_LINE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_LINE
#endif

#if !GP_VALUE_CHECK_LINE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug.h"


struct LineObject {
    RenderableObject base;
    Ref<gp::Line> line;
};


// Line Core
namespace line {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        LineObject *self;
        self = (LineObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(LineObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.line.Line()");

        float x1, x2;
        float y1, y2;
        if (!PyArg_ParseTuple(args, "(ff)(ff)", &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->line = Ref<gp::Line>(new gp::Line({x1, y1}, {x2, y2}));
        self->base.renderable = self->line;

        return 0;
    }

    static PyObject *repr(LineObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.line.Line.__repr__()");
        return PyUnicode_FromString("Line()");
    }

    static int traverse(LineObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(LineObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.line.Line.clear()");
        return 0;
    }

    static void dealloc(LineObject *self) {
        GP_PY_DEBUG("gp.line.Line.__dealloc__()");

        self->line.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Line methods
namespace line {
    static PyObject *set_color(LineObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.line.Line.set_color({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PyObject *arg1, *arg2;
        PyObject *color1;
        if (PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {

            PyObject *color2;

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

            self->line->setColor(*((ColorObject *) color1)->color,
                                 *((ColorObject *) color2)->color);
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

        self->line->setColor(*((ColorObject *) color1)->color);
        Py_RETURN_NONE;
    }

    static PyObject *set_transparency(LineObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.line.Line.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2;
        if (PyArg_ParseTuple(args, "ff", &v1, &v2)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->line->setTransparency(v1, v2);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &v1)) {
            return nullptr;
        }

        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

        self->line->setTransparency(v1);
        Py_RETURN_NONE;
    }
}


// Line Type
namespace line {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},

            {nullptr}
    };
}

static PyTypeObject LineType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Line",
        sizeof(LineObject),
        0,
        (destructor) line::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) line::repr,
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
        (traverseproc) line::traverse,
        (inquiry) line::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        line::methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) line::init,
        nullptr,
        line::new_,
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

static struct PyModuleDef LineModule = {
        PyModuleDef_HEAD_INIT,
        "line",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_line(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_line()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&LineModule);
    if (m == nullptr) {
        return nullptr;
    }

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_line() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_line() - import_color()" << std::endl;
    #endif
    PyColor_API = (void **) PyCapsule_Import("goopylib.ext.color._C_API", 0);
    if (PyColor_API == nullptr) {
        return nullptr;
    }

    ColorType = Color_pytype();

    LineType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(LineType, "Line");

    return m;
}
