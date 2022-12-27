#include "module.h"

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
    #if GP_LOGGING_LEVEL
    std::cout << "Initializing buffers logger" << std::endl;
    gp::Log::init();
    #endif

    GP_PY_TRACE("Initializing buffers module");

    PyObject *m;
    m = PyModule_Create(&buffersmodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(BufferElementType, "BufferElement")
    EXPOSE_PYOBJECT_CLASS(VertexBufferType, "VertexBuffer")
    EXPOSE_PYOBJECT_CLASS(IndexBufferType, "IndexBuffer")

    EXPOSE_PYOBJECT_CLASS(VertexArrayType, "VertexArray")

    return m;
}
