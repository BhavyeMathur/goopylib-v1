#include "vertex_array.h"

struct VertexArrayObject {
    PyObject_HEAD
    Ref<gp::VertexArray> vertex_array;
    PyObject *index_buffer;
    PyObject *vertex_buffers;
};

// Vertex Array Object
namespace VertexArray {
    static int init(VertexArrayObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        GP_PY_INFO("Initializing gp.VertexArray()");

        self->vertex_buffers = PyList_New(0);

        self->vertex_array = std::make_shared<gp::VertexArray>();

        return 0;
    }

    static int traverse(VertexArrayObject *self, visitproc visit, void *arg) {
        Py_VISIT(self->vertex_buffers);
        Py_VISIT(self->index_buffer);

        return 0;
    }

    static int clear(VertexArrayObject *self) {
        GP_PY_TRACE("Clearing gp.VertexArray()");

        Py_CLEAR(self->vertex_buffers);
        Py_CLEAR(self->index_buffer);

        return 0;
    }

    static void dealloc(VertexArrayObject *self) {
        GP_PY_INFO("Deallocating gp.VertexArray()");

        Py_XDECREF(self->vertex_buffers);
        Py_XDECREF(self->index_buffer);

        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }

    static PyObject *repr(VertexArrayObject *self) {
        return PyUnicode_FromString("VertexArray()");
    }
}

// Vertex Array Methods
namespace VertexArray {
    static PyObject *bind(VertexArrayObject *self, PyObject *Py_UNUSED(args)) {
        self->vertex_array->bind();
        Py_RETURN_NONE;
    }

    static PyObject *unbind(VertexArrayObject *self, PyObject *Py_UNUSED(args)) {
        self->vertex_array->unbind();
        Py_RETURN_NONE;
    }

    static PyObject *draw(VertexArrayObject *self, PyObject *Py_UNUSED(args)) {
        self->vertex_array->draw();
        Py_RETURN_NONE;
    }

    static PyObject *set_index_buffer(VertexArrayObject *self, PyObject *index_buffer) {
        if (!PyObject_IsInstance(index_buffer, (PyObject *) &IndexBufferType)) {
            RAISE_TYPE_ERROR(nullptr, "IndexBuffer", index_buffer)
        }

        self->vertex_array->setIndexBuffer(((IndexBufferObject *) index_buffer)->buffer);
        SET_PYOBJECT(self->index_buffer, index_buffer)
        Py_RETURN_NONE;
    }

    static PyObject *add_vertex_buffer(VertexArrayObject *self, PyObject *vertex_buffer) {
        if (!PyObject_IsInstance(vertex_buffer, (PyObject *) &VertexBufferType)) {
            RAISE_TYPE_ERROR(nullptr, "VertexBuffer", vertex_buffer)
        }

        PyList_Append(self->vertex_buffers, (PyObject *) vertex_buffer);

        self->vertex_array->setVertexBuffer(*((VertexBufferObject *) vertex_buffer)->buffer);
        Py_RETURN_NONE;
    }

    static PyObject *get_vertex_buffer(VertexArrayObject *self, PyObject *Py_UNUSED(args)) {
        RETURN_PYOBJECT(self->vertex_buffers)
    }

    static PyMethodDef methods[] = {
            {"bind",   (PyCFunction) bind,   METH_NOARGS,
                    "Binds the Vertex Array"},
            {"unbind", (PyCFunction) unbind, METH_NOARGS,
                    "Unbinds the Vertex Array"},

            {"draw", (PyCFunction) draw, METH_NOARGS,
                    "Draws the Vertex Buffer"},

            {"set_index_buffer", (PyCFunction) set_index_buffer, METH_O,
                    "Sets the Index Buffer of the Vertex Array"},

            {"add_vertex_buffer", (PyCFunction) add_vertex_buffer, METH_O,
                    "Adds a Vertex Buffer to the Vertex Array"},
            {"get_vertex_buffers", (PyCFunction) add_vertex_buffer, METH_NOARGS,
                    "Gets a list of the Vertex Buffer assigned to the Vertex Array"},

            {nullptr}
    };
}

PyTypeObject VertexArrayType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        .tp_basicsize = sizeof(VertexArrayObject),
        .tp_itemsize = 0,
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
        .tp_new = PyType_GenericNew,
        .tp_name = "goopylib.VertexArray",
        .tp_init = (initproc) VertexArray::init,

        .tp_traverse = (traverseproc) VertexArray::traverse,
        .tp_clear = (inquiry) VertexArray::clear,
        .tp_dealloc = (destructor) VertexArray::dealloc,

        .tp_repr = (reprfunc) VertexArray::repr,

        .tp_methods = VertexArray::methods
};
