#define GP_LOGGING_LEVEL 3

#include "goopylib/debug.h"

#include "goopylib/core/window_object.h"

#include "image.h"
#include "src/goopylib/objects/Image.h"


namespace image {
    PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        ImageObject *self;
        self = (ImageObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    int init(ImageObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.image.Image({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float x1, y1;
        float width, height;
        const char *path;
        if (PyArg_ParseTuple(args, "s(ff)ff", &path, &x1, &y1, &width, &height)) {
            self->image = shared_ptr<gp::Image>(new gp::Image(path, {x1, y1}, width, height));
            self->base.rectangle = self->image;
            self->base.base.quad = self->image;
            self->base.base.base.renderable = self->image;
            return 0;
        }
        PyErr_Clear();

        if (PyArg_ParseTuple(args, "s(ff)", &path, &x1, &y1)) {

            try {
                self->image = shared_ptr<gp::Image>(new gp::Image(path, {x1, y1}));
            }
            catch (const std::runtime_error &e) {
                PyErr_SetString(PyExc_FileNotFoundError, path);
                return -1;
            }

            self->base.rectangle = self->image;
            self->base.base.quad = self->image;
            self->base.base.base.renderable = self->image;
            return 0;
        }
        PyErr_Clear();

        float x2, y2;
        if (!PyArg_ParseTuple(args, "s(ff)(ff)", &path, &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->image = shared_ptr<gp::Image>(new gp::Image(path, {x1, y1}, {x2, y2}));
        self->base.rectangle = self->image;
        self->base.base.quad = self->image;
        self->base.base.base.renderable = self->image;

        return 0;
    }

    int traverse(ImageObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    int clear(ImageObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.image.Image.clear()");
        return 0;
    }

    void dealloc(ImageObject *self) {
        GP_PY_DEBUG("gp.image.Image.__dealloc__()");

        self->image.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Image methods
namespace image {
    PyObject *draw(ImageObject *self, PyObject *arg) {
        GP_PY_DEBUG((size_t) WindowType);

        #if GP_TYPE_CHECKING
        if (!isinstance(arg, WindowType)) {
            RAISE_TYPE_ERROR(nullptr, "Window", arg);
        }
        #endif

        try {
            self->image->draw(*((WindowObject *) arg)->window);
        }
        catch (std::runtime_error &e) {
            RAISE_FILENOTFOUND_ERROR(nullptr, self->image->getPath().c_str());
        }
        RETURN_PYOBJECT((PyObject *) self);
    }

    PyObject *get_path(ImageObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_DEBUG("gp.image.Image.get_path()");
        return PyUnicode_FromString(self->image->getPath().c_str());
    }
}
