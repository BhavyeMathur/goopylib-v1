#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "goopylib/core/window_object.h"

#include "renderable.h"
#include "src/goopylib/objects/Renderable.h"


namespace renderable {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        GP_PY_DEBUG("gp.renderable.Renderable.__new__()");

        RenderableObject *self;
        self = (RenderableObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    int init(RenderableObject *Py_UNUSED(self), PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.renderable.Renderable()");
        return 0;
    }

    PyObject *repr(RenderableObject *self) {
        GP_PY_TRACE("gp.renderable.Renderable.__repr__()");
        return PyUnicode_FromString(self->renderable->toString().c_str());
    }

    int traverse(RenderableObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(RenderableObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.renderable.Renderable.clear()");
        return 0;
    }

    void dealloc(RenderableObject *self) {
        GP_PY_DEBUG("gp.renderable.Renderable.__dealloc__()");

        self->renderable.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Renderable methods
namespace renderable {
    PyObject *draw(RenderableObject *self, PyObject *arg) {
        GP_PY_DEBUG("gp.objects.renderable.Renderable.draw({0})", PyUnicode_AsUTF8(PyObject_Repr(arg)));

        #if GP_TYPE_CHECKING
        if (!isinstance(arg, WindowType)) {
            RAISE_TYPE_ERROR(nullptr, "Window", arg);
        }
        #endif

        self->renderable->draw(*((WindowObject *) arg)->window);
        RETURN_PYOBJECT((PyObject *) self);
    }

    PyObject *destroy(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        self->renderable->destroy();
        Py_RETURN_NONE;
    }

    PyObject *is_drawn(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        if (self->renderable->isDrawn()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    PyObject *set_anchor(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        self->renderable->setAnchor(x, y);
        Py_RETURN_NONE;
    }

    PyObject *reset_anchor(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        self->renderable->resetAnchor();
        Py_RETURN_NONE;
    }

    PyObject *move(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        self->renderable->move(x, y);
        Py_RETURN_NONE;
    }

    PyObject *rotate(RenderableObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "number", arg);
        }
        #endif

        self->renderable->rotate((float) PyFloat_AsDouble(arg));
        Py_RETURN_NONE;
    }

    PyObject *scale(RenderableObject *self, PyObject *args) {
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

    PyObject *set_size(RenderableObject *self, PyObject *args) {
        float width, height;
        if (!PyArg_ParseTuple(args, "ff", &width, &height)) {
            return nullptr;
        }

        self->renderable->setSize(width, height);
        Py_RETURN_NONE;
    }

    PyObject *hide(RenderableObject *self, PyObject *arg) {
        #if GP_TYPE_CHECKING
        if (!PyBool_Check(arg)) {
            RAISE_TYPE_ERROR(nullptr, "bool", arg);
        }
        #endif

        self->renderable->hide(arg == Py_True);
        Py_RETURN_NONE;
    }

    PyObject *show(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        self->renderable->show();
        Py_RETURN_NONE;
    }

    PyObject *is_hidden(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        if (self->renderable->isHidden()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    PyObject *is_opaque(RenderableObject *self, PyObject *Py_UNUSED(args)) {
        if (self->renderable->isOpaque()) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    PyObject *box_contains(RenderableObject *self, PyObject *args) {
        float x, y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
            return nullptr;
        }

        if (self->renderable->boxContains({x, y})) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    PyObject *contains(RenderableObject *self, PyObject *args) {
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
    PyObject *get_x(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getX());
    }

    int set_x(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setX((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Y-Position
    PyObject *get_y(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getY());
    }

    int set_y(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setY((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Position
    PyObject *get_position(RenderableObject *self, void *Py_UNUSED(closure)) {
        return Py_BuildValue("ff", self->renderable->getX(), self->renderable->getY());
    }

    int set_position(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        float x, y;
        if (!PyArg_ParseTuple(value, "ff", &x, &y)) {
            return -1;
        }

        self->renderable->setPosition(x, y);
        return 0;
    }

    // Rotation
    PyObject *get_rotation(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getRotation());
    }

    int set_rotation(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setRotation((float) PyFloat_AsDouble(value));
        return 0;
    }

    // X-Scale
    PyObject *get_xscale(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getScale().xscale);
    }

    int set_xscale(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setScaleX((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Y-Scale
    PyObject *get_yscale(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getScale().yscale);
    }

    int set_yscale(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setScaleY((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Width
    PyObject *get_width(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getWidth());
    }

    int set_width(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setWidth((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Height
    PyObject *get_height(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getHeight());
    }

    int set_height(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setHeight((float) PyFloat_AsDouble(value));
        return 0;
    }

    // Z-Position
    PyObject *get_z(RenderableObject *self, void *Py_UNUSED(closure)) {
        return PyFloat_FromDouble(self->renderable->getZPosition());
    }

    int set_z(RenderableObject *self, PyObject *value, void *Py_UNUSED(closure)) {
        #if GP_TYPE_CHECKING
        if (!PyNumber_Check(value)) {
            RAISE_TYPE_ERROR(-1, "number", value);
        }
        #endif

        self->renderable->setZPosition((float) PyFloat_AsDouble(value));
        return 0;
    }
}
