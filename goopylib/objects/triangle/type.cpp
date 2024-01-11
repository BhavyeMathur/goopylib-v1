#include "triangle.h"

namespace triangle {
    static PyMethodDef methods[] = {
            {"set_color", (PyCFunction) set_color, METH_VARARGS,
                    "Sets the color of the object"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            GETTER_SETTER(p1),
            GETTER_SETTER(p2),
            GETTER_SETTER(p3),
            GETTER_SETTER(transparency),

            {nullptr}
    };
}

PyTypeObject TriangleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Triangle",
        sizeof(TriangleObject),
        0,
        (destructor) triangle::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
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
        (traverseproc) triangle::traverse,
        (inquiry) triangle::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        triangle::methods,
        nullptr,
        (PyGetSetDef *) triangle::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) triangle::init,
        nullptr,
        triangle::new_,
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
