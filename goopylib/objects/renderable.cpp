#define RENDERABLE_MODULE

#include "renderable.h"
#include "renderable_object.h"
#include "renderable_module.h"
#include "renderable_capsule.h"

#include "goopylib/core/window_module.h"
#include "goopylib/core/window_object.h"

#include "config.h"

#if (GP_LOG_RENDERABLE != true) and (GP_LOG_RENDERABLE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_RENDERABLE
#endif

#if !GP_VALUE_CHECK_RENDERABLE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug.h"


// Renderable Core
namespace renderable {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        GP_PY_DEBUG("gp.renderable.Renderable.__new__()");

        RenderableObject *self;
        self = (RenderableObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(RenderableObject *Py_UNUSED(self), PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.renderable.Renderable()");

        return 0;
    }

    static PyObject *repr(RenderableObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.renderable.Renderable.__repr__()");
        return PyUnicode_FromString("Renderable()");
    }

    static int traverse(RenderableObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(RenderableObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.renderable.Renderable.clear()");
        return 0;
    }

    static void dealloc(RenderableObject *self) {
        GP_PY_DEBUG("gp.renderable.Renderable.__dealloc__()");

        self->renderable.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Renderable methods
namespace renderable {
    static PyObject *draw(RenderableObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!isinstance(arg, WindowType)) {
            RAISE_TYPE_ERROR(nullptr, "Window", arg);
        }
        #endif

        self->renderable->draw(((WindowObject *) arg)->window.get());
        RETURN_PYOBJECT((PyObject *) self);
    }

    static PyObject *destroy(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        self->renderable->destroy();
        Py_RETURN_NONE;
    }

    static PyObject *is_drawn(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        if (self->renderable->isDrawn()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *set_anchor(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        self->renderable->setAnchor(x, y);
        Py_RETURN_NONE;
    }

    static PyObject *reset_anchor(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        self->renderable->resetAnchor();
        Py_RETURN_NONE;
    }

    static PyObject *move(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        self->renderable->move(x, y);
        Py_RETURN_NONE;
    }

    static PyObject *rotate(RenderableObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "number", arg);
        }
        #endif

        self->renderable->rotate((float) PyFloat_AsDouble(arg));
        Py_RETURN_NONE;
    }

    static PyObject *scale(RenderableObject *self, PyObject *args) {
        float x, y;

        if (PyArg_ParseTuple(args, "ff", &x, &y)) {
            self->renderable->scale(x, y);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &x)) {
            return nullptr;
        }

        self->renderable->scale(x);
        Py_RETURN_NONE;
    }

    static PyObject *set_size(RenderableObject *self, PyObject *args) {
        float width, height;
        if (!PyArg_ParseTuple(args, "ff", &width, &height)) {
            return nullptr;
        }

        self->renderable->setSize(width, height);
        Py_RETURN_NONE;
    }

    static PyObject *hide(RenderableObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->renderable->hide(arg == Py_True);
        Py_RETURN_NONE;
    }

    static PyObject *show(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        self->renderable->show();
        Py_RETURN_NONE;
    }

    static PyObject *is_hidden(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        if (self->renderable->isHidden()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *box_contains(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        if (self->renderable->boxContains({x, y})) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    static PyObject *contains(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        if (self->renderable->contains({x, y})) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
}

// Renderable getters & setters
namespace renderable {
    // X-Position
    static PyObject *get_x(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getX());
    }

    static int set_x(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setX((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Y-Position
    static PyObject *get_y(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getY());
    }

    static int set_y(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setY((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Position
    static PyObject *get_position(RenderableObject *self, void *Py_UNUSED(closure)) {
        return Py_BuildValue("ff", self->renderable->getX(), self->renderable->getY());
    }

    static int set_position(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        float x, y;
        if (!PyArg_ParseTuple(value, "ff", &x, &y)) {
            return -1;
        }

        self->renderable->setPosition(x, y);
        return 0;
    }

    // Rotation
    static PyObject *get_rotation(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getRotation());
    }

    static int set_rotation(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setRotation((float) PyFloat_AsDouble(value));
        return 0;
    }

    // X-Scale
    static PyObject *get_xscale(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getScale().xscale);
    }

    static int set_xscale(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setScaleX((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Y-Scale
    static PyObject *get_yscale(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getScale().yscale);
    }

    static int set_yscale(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setScaleY((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Width
    static PyObject *get_width(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getWidth());
    }

    static int set_width(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setWidth((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Height
    static PyObject *get_height(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getHeight());
    }

    static int set_height(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setHeight((float) PyFloat_AsDouble(value));
        return 0;
    }
}

// Renderable Type
namespace renderable {
    static PyMethodDef methods[] = {
            {"draw",         (PyCFunction) draw,         METH_O,
                    "Draws the object to a window"},
            {"destroy",      (PyCFunction) destroy,      METH_NOARGS,
                    "Destroys the object"},
            {"is_drawn",     (PyCFunction) is_drawn,     METH_NOARGS,
                    "Checks if the object has been drawn to a Window"},

            {"set_anchor",   (PyCFunction) set_anchor,   METH_VARARGS,
                    "Sets the anchor point of the object"},
            {"reset_anchor", (PyCFunction) reset_anchor, METH_NOARGS,
                    "Resets the object's anchor to its center"},

            {"move",         (PyCFunction) move,         METH_VARARGS,
                    "Moves the object"},
            {"rotate",       (PyCFunction) rotate,       METH_O,
                    "Rotates the object"},
            {"scale",        (PyCFunction) scale,        METH_VARARGS,
                    "Scales the object"},
            {"set_size",     (PyCFunction) set_size,     METH_VARARGS,
                    "Sets the width and height of the object"},

            {"hide",         (PyCFunction) hide,         METH_O,
                    "Hides the object"},
            {"show",         (PyCFunction) show,         METH_NOARGS,
                    "Unhides the object"},
            {"is_hidden",    (PyCFunction) is_hidden,    METH_NOARGS,
                    "Checks if the object is hidden"},

            {"box_contains", (PyCFunction) box_contains, METH_VARARGS,
                    "Checks if the object's rectangular bounding box contains a point"},
            {"contains",     (PyCFunction) contains,     METH_VARARGS,
                    "Checks if the object's bounding box contains a point"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            {"x", (getter) get_x, (setter) set_x, "x", nullptr},
            {"y", (getter) get_y, (setter) set_y, "y", nullptr},
            {"position", (getter) get_position, (setter) set_position, "position", nullptr},

            {"rotation", (getter) get_rotation, (setter) set_rotation, "rotation", nullptr},
            {"xscale", (getter) get_xscale, (setter) set_xscale, "xscale", nullptr},
            {"yscale", (getter) get_yscale, (setter) set_yscale, "yscale", nullptr},

            {"width", (getter) get_width, (setter) set_width, "width", nullptr},
            {"height", (getter) get_height, (setter) set_height, "height", nullptr},

            {nullptr}
    };
}

PyTypeObject RenderableType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Renderable",
        sizeof(RenderableObject),
        0,
        (destructor) renderable::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) renderable::repr,
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
        (traverseproc) renderable::traverse,
        (inquiry) renderable::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        renderable::methods,
        nullptr,
        renderable::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) renderable::init,
        nullptr,
        renderable::new_,
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

static struct PyModuleDef RenderableModule = {
        PyModuleDef_HEAD_INIT,
        "renderable",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_renderable(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_renderable()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&RenderableModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Window

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_renderable() - import_window()" << std::endl;
    #endif
    PyWindow_API = (void **) PyCapsule_Import("goopylib.ext.window._C_API", 0);
    if (PyWindow_API == nullptr) {
        return nullptr;
    }

    WindowType = Window_pytype();

    // Exposing class

    EXPOSE_PYOBJECT_CLASS(RenderableType, "Renderable");

    // Exposing capsule

    static void *PyRenderable_API[PyRenderable_API_pointers];
    PyObject *c_api_object;

    PyRenderable_API[Renderable_pytype_NUM] = (void *) Renderable_pytype;
    c_api_object = PyCapsule_New((void *) PyRenderable_API, "goopylib.ext.renderable._C_API", nullptr);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
