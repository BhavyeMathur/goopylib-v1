#include "buffers.h"

struct BufferElementObject {
    PyObject_HEAD
    std::unique_ptr<gp::BufferElement> buffer_element;
    const char *dtype;
};

struct VertexBufferObject {
    PyObject_HEAD
    std::unique_ptr<gp::VertexBuffer> buffer;
};

struct IndexBufferObject {
    PyObject_HEAD
    std::unique_ptr<gp::IndexBuffer> buffer;
};

namespace BufferElement {
    static int init(BufferElementObject *self, PyObject *args, PyObject *kwds) {
        GP_PY_TRACE("Initializing gp.BufferElement()");

        static const char *kwlist[] = {"name", "dtype", "normalized", nullptr};

        const char *name;
        bool normalized = false;

        if (!PyArg_ParseTupleAndKeywords(args, kwds, "ss|p", (char **) kwlist, &name, &self->dtype, &normalized)) {
            return -1;
        }

        gp::ShaderDataType type;
        if (strcmp(self->dtype, "float") == 0) {
            type = gp::ShaderDataType::Float;
        }
        else if (strcmp(self->dtype, "float2") == 0) {
            type = gp::ShaderDataType::Float2;
        }
        else if (strcmp(self->dtype, "float3") == 0) {
            type = gp::ShaderDataType::Float3;
        }
        else if (strcmp(self->dtype, "float4") == 0) {
            type = gp::ShaderDataType::Float4;
        }
        else if (strcmp(self->dtype, "mat3") == 0) {
            type = gp::ShaderDataType::Mat3;
        }
        else if (strcmp(self->dtype, "ma4") == 0) {
            type = gp::ShaderDataType::Mat4;
        }
        else if (strcmp(self->dtype, "int") == 0) {
            type = gp::ShaderDataType::Int;
        }
        else if (strcmp(self->dtype, "int2") == 0) {
            type = gp::ShaderDataType::Int2;
        }
        else if (strcmp(self->dtype, "int3") == 0) {
            type = gp::ShaderDataType::Int3;
        }
        else if (strcmp(self->dtype, "int4") == 0) {
            type = gp::ShaderDataType::Int4;
        }
        else if (strcmp(self->dtype, "bool") == 0) {
            type = gp::ShaderDataType::Bool;
        }
        else {
            RAISE_VALUE_ERROR(-1, "invalid BufferElement dtype")
        }

        self->buffer_element = gp::make_unique<gp::BufferElement>(type, name, normalized);

        return 0;
    }

    static int traverse(BufferElementObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(BufferElementObject *Py_UNUSED(self)) {
        GP_PY_TRACE("Clearing gp.BufferElement()");
        return 0;
    }

    static void dealloc(BufferElementObject *self) {
        GP_PY_TRACE("Deallocating gp.BufferElement()");

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }

    static PyObject *repr(BufferElementObject *self) {
        return PyUnicode_FromFormat("BufferElement(%s, %s, normalized=%s)",
                                    self->buffer_element->getName(), self->dtype,
                                    self->buffer_element->isNormalized() ? "True" : "False");
    }
}

namespace VertexBuffer {
    static int init(VertexBufferObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_TRACE("Initializing gp.VertexBuffer()");

        return 0;
    }

    static int traverse(VertexBufferObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(VertexBufferObject *Py_UNUSED(self)) {
        GP_PY_TRACE("Clearing gp.VertexBuffer()");
        return 0;
    }

    static void dealloc(VertexBufferObject *self) {
        GP_PY_TRACE("Deallocating gp.VertexBuffer()");

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

namespace IndexBuffer {
    static int init(VertexBufferObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_TRACE("Initializing gp.IndexBuffer()");

        return 0;
    }

    static int traverse(IndexBufferObject *Py_UNUSED(self), visitproc Py_UNUSED(visit), void *Py_UNUSED(arg)) {
        return 0;
    }

    static int clear(IndexBufferObject *Py_UNUSED(self)) {
        GP_PY_TRACE("Clearing gp.IndexBuffer()");
        return 0;
    }

    static void dealloc(IndexBufferObject *self) {
        GP_PY_TRACE("Deallocating gp.IndexBuffer()");

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }
}

PyTypeObject BufferElementType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_basicsize = sizeof(BufferElementObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        .tp_new = PyType_GenericNew,
        .tp_name = "goopylib.BufferElement",
        .tp_init = (initproc) BufferElement::init,

        .tp_traverse = (traverseproc) BufferElement::traverse,
        .tp_clear = (inquiry) BufferElement::clear,
        .tp_dealloc = (destructor) BufferElement::dealloc,

        .tp_repr = (reprfunc) BufferElement::repr,
};

PyTypeObject VertexBufferType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_basicsize = sizeof(VertexBufferObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        .tp_new = PyType_GenericNew,
        .tp_name = "goopylib.VertexBuffer",
        .tp_init = (initproc) VertexBuffer::init,

        .tp_traverse = (traverseproc) VertexBuffer::traverse,
        .tp_clear = (inquiry) VertexBuffer::clear,
        .tp_dealloc = (destructor) VertexBuffer::dealloc,
};

PyTypeObject IndexBufferType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_basicsize = sizeof(IndexBufferObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        .tp_new = PyType_GenericNew,
        .tp_name = "goopylib.IndexBuffer",
        .tp_init = (initproc) IndexBuffer::init,

        .tp_traverse = (traverseproc) IndexBuffer::traverse,
        .tp_clear = (inquiry) IndexBuffer::clear,
        .tp_dealloc = (destructor) IndexBuffer::dealloc,
};

static PyMethodDef BufferMethods[] = {
        {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef buffersmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "buffers",
        .m_size = -1,
        .m_methods = BufferMethods,
};


PyMODINIT_FUNC PyInit_buffers() {
    #if GP_LOGGING
    std::cout << "Initializing buffers logger" << std::endl;
    gp::Log::Init();
    #endif

    GP_PY_TRACE("Initializing buffers module");

    PyObject *m;
    m = PyModule_Create(&buffersmodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_CLASS(BufferElementType, "BufferElement")
    EXPOSE_CLASS(VertexBufferType, "VertexBuffer")
    EXPOSE_CLASS(IndexBufferType, "IndexBuffer")

    return m;
}
