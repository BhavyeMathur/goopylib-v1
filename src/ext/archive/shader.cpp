#include "shader.h"

struct ShaderObject {
    PyObject_HEAD
    Ref<gp::Shader> shader;
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

    static PyObject *set(ShaderObject *self, PyObject *args) {

        const char *name;
        float f1, f2, f3, f4;
        if (PyArg_ParseTuple(args, "sf|fff", &name, &f1, &f2, &f3, &f4)) {
            switch (PyTuple_GET_SIZE(args)) {
                case 2:
                    self->shader->set(name, f1);
                case 3:
                    self->shader->set(name, f1, f2);
                case 4:
                    self->shader->set(name, f1, f2, f3);
                case 5:
                    self->shader->set(name, f1, f2, f3, f4);
                default:
                    RAISE_VALUE_ERROR(nullptr, "invalid number of arguments provided")
            }
        }
        PyErr_Clear();

        int i1, i2, i3, i4;
        if (PyArg_ParseTuple(args, "si|iii", &name, &i1, &i2, &i3, &i4)) {
            switch (PyTuple_GET_SIZE(args)) {
                case 2:
                    self->shader->set(name, i1);
                case 3:
                    self->shader->set(name, i2, i2);
                case 4:
                    self->shader->set(name, i1, i2, i3);
                case 5:
                    self->shader->set(name, i1, i2, i3, i4);
                default:
                    RAISE_VALUE_ERROR(nullptr, "invalid number of arguments provided")
            }
        }
        PyErr_Clear();

        PyObject *matrix;
        if (!PyArg_ParseTuple(args, "sO", &name, &matrix)) {
            RAISE_VALUE_ERROR(nullptr, "invalid shader set uniform arguments")
        }

        PyObject *rowIterator, *colIterator;
        PyObject *matrixRow, *matrixCol;

        if (!(rowIterator = PyObject_GetIter(matrix))) {
            return nullptr;
        }

        int rows = 0;
        int cols = -1;
        int curCols = 0;

        std::vector<float> data;

        while ((matrixRow = PyIter_Next(rowIterator))) {
            if (!(colIterator = PyObject_GetIter(matrixRow))) {
                Py_DECREF(matrixRow);
                return nullptr;
            }

            while ((matrixCol = PyIter_Next(colIterator))) {
                if (!PyNumber_Check(matrixCol)) {
                    Py_DECREF(matrixCol);
                    RAISE_VALUE_ERROR(nullptr, "matrix must only contain floats")
                }

                data.push_back((float) PyFloat_AsDouble(matrixCol));

                curCols++;
                Py_DECREF(matrixCol);
            }

            if (cols == -1) {
                cols = curCols;
            }
            else if (cols != curCols) {
                RAISE_VALUE_ERROR(nullptr, "matrix columns must be the same size")
            }
            curCols = 0;

            rows++;
            Py_DECREF(matrixRow);
        }
        
        double arr[rows * cols];
        std::copy(data.begin(), data.end(), arr);

        switch (rows) {
            case 2:
                switch (cols) {
                    case 2:
                        self->shader->set(name, glm::make_mat2x2(arr));
                        Py_RETURN_NONE;

                    case 3:
                        self->shader->set(name, glm::make_mat3x2(arr));
                        Py_RETURN_NONE;

                    case 4:
                        self->shader->set(name, glm::make_mat4x2(arr));
                        Py_RETURN_NONE;

                    default:
                        RAISE_VALUE_ERROR(nullptr, "invalid matrix size")
                }

            case 3:
                switch (cols) {
                    case 2:
                        self->shader->set(name, glm::make_mat2x3(arr));
                        Py_RETURN_NONE;

                    case 3:
                        self->shader->set(name, glm::make_mat3x3(arr));
                        Py_RETURN_NONE;

                    case 4:
                        self->shader->set(name, glm::make_mat4x3(arr));
                        Py_RETURN_NONE;

                    default:
                        RAISE_VALUE_ERROR(nullptr, "invalid matrix size")
                }

            case 4:
                switch (cols) {
                    case 2:
                        self->shader->set(name, glm::make_mat2x4(arr));
                        Py_RETURN_NONE;

                    case 3:
                        self->shader->set(name, glm::make_mat3x4(arr));
                        Py_RETURN_NONE;

                    case 4:
                        self->shader->set(name, glm::make_mat4x4(arr));
                        Py_RETURN_NONE;

                    default:
                        RAISE_VALUE_ERROR(nullptr, "invalid matrix size")
                }
            default:
                RAISE_VALUE_ERROR(nullptr, "invalid matrix size")
        }

        Py_RETURN_NONE;
    }

    static PyMethodDef methods[] = {
            {"bind",   (PyCFunction) bind,   METH_NOARGS,
                    "Binds the Shader"},
            {"unbind", (PyCFunction) unbind, METH_NOARGS,
                    "Unbinds the Shader"},

            {"set", (PyCFunction) set, METH_VARARGS,
                    "Sets a Shader uniform"},

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
    #if GP_LOGGING_LEVEL
    std::cout << "Initializing shader logger" << std::endl;
    gp::Log::init();
    #endif

    GP_PY_TRACE("Initializing shader module");

    PyObject *m;
    m = PyModule_Create(&shadermodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(ShaderType, "Shader")

    return m;
}
