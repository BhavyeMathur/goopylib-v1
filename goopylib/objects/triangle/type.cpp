#include "triangle.h"

namespace triangle {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},

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
        (reprfunc) triangle::repr,
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
        nullptr,
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
