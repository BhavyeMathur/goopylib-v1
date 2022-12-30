#include "image.h"
#include "renderable_module.h"
#include "renderable_object.h"

#include "goopylib/objects/Image.h"

#include "config.h"

#if (GP_LOG_IMAGE != true) and (GP_LOG_IMAGE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_IMAGE
#endif

#if !GP_VALUE_CHECK_IMAGE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"


struct ImageObject {
    RenderableObject base;
    Ref<gp::Image> image;
};


// Image Core
namespace image {
    static PyObject *new_(PyTypeObject *type, PyObject *args, PyObject *kwds) {
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

    static PyObject *repr(ImageObject *self) {
        GP_PY_TRACE("gp.image.Image.__repr__()");
        return PyUnicode_FromString("Image()");
    }

    static int traverse(ImageObject *self, visitproc visit, void *arg) {
        return 0;
    }

    static int clear(ImageObject *self) {
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
        return PyUnicode_FromString(self->image->getPath());
    }
}


// Image Type
namespace image {
    static PyMethodDef methods[] = {
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},
            {"get_path", (PyCFunction) get_path, METH_NOARGS,
                    "Returns the filepath the image is using"},

            {nullptr}
    };
}

PyTypeObject ImageType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_name = "goopylib.Image",
        .tp_basicsize = sizeof(ImageObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

        .tp_new = image::new_,
        .tp_init = (initproc) image::init,

        .tp_methods = image::methods,

        .tp_traverse = (traverseproc) image::traverse,
        .tp_clear = (inquiry) image::clear,
        .tp_dealloc = (destructor) image::dealloc,

        .tp_repr = (reprfunc) image::repr,
};

static struct PyModuleDef imagemodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "image",
        .m_size = -1,
        .m_methods = nullptr,
};

PyMODINIT_FUNC PyInit_image(void) {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_image()" << std::endl;
    #endif

    PyObject *m = PyModule_Create(&imagemodule);
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
