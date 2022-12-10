#include "shader.h"

struct ShaderObject {
    PyObject_HEAD
    std::shared_ptr<gp::Shader> shader;
};

// Shader Object
namespace shader {
    static int init(ShaderObject *self, PyObject *args, PyObject *kwds) {
        GP_PY_INFO("Initializing gp.Shader()");

        static const char *kwlist[] = {"vertex_shader", "fragment_shader", nullptr};

        const char *vertex_shader;
        const char *fragment_shader;

        if (!PyArg_ParseTupleAndKeywords(args, kwds, "ss", (char **) kwlist, &vertex_shader, &fragment_shader)) {
            return -1;
        }

        self->shader = std::make_shared<gp::Shader>(vertex_shader, fragment_shader);

        return 0;
    }

    static int traverse(ShaderObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(ShaderObject *Py_UNUSED(self)) {
        GP_PY_TRACE("Clearing gp.Shader()");
        return 0;
    }

    static void dealloc(ShaderObject *self) {
        GP_PY_INFO("Deallocating gp.Shader()");

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }

    static PyObject *repr(ShaderObject *self) {
        return PyUnicode_FromString("Shader()");
    }
}

// Shader Methods
namespace shader {
    static PyObject *bind(ShaderObject *self, PyObject *Py_UNUSED(args)) {
        self->shader->bind();
        Py_RETURN_NONE;
    }

    static PyObject *unbind(ShaderObject *self, PyObject *Py_UNUSED(args)) {
        self->shader->unbind();
        Py_RETURN_NONE;
    }

    static PyMethodDef methods[] = {
            {"bind",   (PyCFunction) bind,   METH_NOARGS,
                    "Binds the Shader"},
            {"unbind", (PyCFunction) unbind, METH_NOARGS,
                    "Unbinds the Shader"},

            {nullptr}
    };
}

PyTypeObject ShaderType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_basicsize = sizeof(ShaderObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        .tp_new = PyType_GenericNew,
        .tp_name = "goopylib.Shader",
        .tp_init = (initproc) shader::init,

        .tp_traverse = (traverseproc) shader::traverse,
        .tp_clear = (inquiry) shader::clear,
        .tp_dealloc = (destructor) shader::dealloc,

        .tp_repr = (reprfunc) shader::repr,

        .tp_methods = shader::methods
};

static PyMethodDef ShaderMethods[] = {
        {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef shadermodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "shader",
        .m_size = -1,
        .m_methods = ShaderMethods,
};


PyMODINIT_FUNC PyInit_shader() {
    #if GP_LOGGING
    std::cout << "Initializing shader logger" << std::endl;
    gp::Log::Init();
    #endif

    GP_PY_TRACE("Initializing shader module");

    PyObject *m;
    m = PyModule_Create(&shadermodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_CLASS(ShaderType, "Shader")

    return m;
}
