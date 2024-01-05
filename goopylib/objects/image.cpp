#define GP_LOGGING_LEVEL 3
#include "goopylib/debug.h"

#include "image.h"
#include "renderable_module.h"
#include "renderable_object.h"

#include "src/goopylib/objects/Image.h"


struct ImageObject {
    RenderableObject base;
    Ref<gp::Image> image;
};


// Image Core
namespace image {
    static PyObject *new_(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        ImageObject *self;
        self = (ImageObject *) type->tp_alloc(type, 0);

        if (self != nullptr) {

        }
        return (PyObject *) self;
    }

    static int init(ImageObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("gp.image.Image({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float x1, y1;
        float width, height;
        const char *path;
        if (PyArg_ParseTuple(args, "s(ff)ff", &path, &x1, &y1, &width, &height)) {
            self->image = Ref<gp::Image>(new gp::Image(path, {x1, y1}, width, height));
            self->base.renderable = self->image;
            return 0;
        }
        PyErr_Clear();

        if (PyArg_ParseTuple(args, "s(ff)", &path, &x1, &y1)) {

            try {
                self->image = Ref<gp::Image>(new gp::Image(path, {x1, y1}));
            }
            catch (const std::runtime_error &e) {
                PyErr_SetString(PyExc_FileNotFoundError, path);
                return -1;
            }

            self->base.renderable = self->image;
            return 0;
        }
        PyErr_Clear();

        float x2, y2;
        if (!PyArg_ParseTuple(args, "s(ff)(ff)", &path, &x1, &y1, &x2, &y2)) {
            return -1;
        }

        self->image = Ref<gp::Image>(new gp::Image(path, {x1, y1}, {x2, y2}));
        self->base.renderable = self->image;

        return 0;
    }

    static PyObject *repr(ImageObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.image.Image.__repr__()");
        return PyUnicode_FromString("Image()");
    }

    static int traverse(ImageObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(ImageObject *Py_UNUSED(self)) {
        GP_PY_TRACE("gp.image.Image.clear()");
        return 0;
    }

    static void dealloc(ImageObject *self) {
        GP_PY_DEBUG("gp.image.Image.__dealloc__()");

        self->image.reset();

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

// Image methods
namespace image {
    static PyObject *set_transparency(ImageObject *self, PyObject *args) {
        GP_PY_DEBUG("gp.image.Image.set_transparency({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        float v1, v2, v3, v4;
        if (PyArg_ParseTuple(args, "ffff", &v1, &v2, &v3, &v4)) {
            GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, nullptr, "transparency must be between 0 and 1")
            GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, nullptr, "transparency must be between 0 and 1")

            self->image->setTransparency(v1, v2, v3, v4);
            Py_RETURN_NONE;
        }
        PyErr_Clear();

        if (!PyArg_ParseTuple(args, "f", &v1)) {
            return nullptr;
        }

        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, nullptr, "transparency must be between 0 and 1")

        self->image->setTransparency(v1);
        Py_RETURN_NONE;
    }

    static PyObject *get_path(ImageObject *self, PyObject *Py_UNUSED(args)) {
        GP_PY_DEBUG("gp.image.Image.get_path()");
        return PyUnicode_FromString(self->image->getPath().c_str());
    }
}


// Image Type
namespace image {
    static PyMethodDef methods[] = {
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},
            {"get_path",         (PyCFunction) get_path,         METH_NOARGS,
                    "Returns the filepath the image is using"},

            {nullptr}
    };
}

static PyTypeObject ImageType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Image",
        sizeof(ImageObject),
        0,
        (destructor) image::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) image::repr,
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
        (traverseproc) image::traverse,
        (inquiry) image::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        image::methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) image::init,
        nullptr,
        image::new_,
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

static struct PyModuleDef ImageModule = {
        PyModuleDef_HEAD_INIT,
        "image",
        "",
        -1,
        nullptr,
};

PyMODINIT_FUNC PyInit_image(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_image()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&ImageModule);
    if (m == nullptr) {
        return nullptr;
    }

    // Importing Renderable

    #if GP_LOGGING_LEVEL >= 6
    std::cout << "[--:--:--] PYTHON: PyInit_image() - import_renderable()" << std::endl;
    #endif
    PyRenderable_API = (void **) PyCapsule_Import("goopylib.ext.renderable._C_API", 0);
    if (PyRenderable_API == nullptr) {
        return nullptr;
    }

    RenderableType = Renderable_pytype();

    // Exposing Class

    ImageType.tp_base = RenderableType;

    EXPOSE_PYOBJECT_CLASS(ImageType, "Image");

    return m;
}
