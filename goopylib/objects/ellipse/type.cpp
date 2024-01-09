#include "ellipse.h"

namespace ellipse {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            GETTER_SETTER(transparency),

            {nullptr}
    };
}

PyTypeObject EllipseType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Ellipse",
        sizeof(EllipseObject),
        0,
        (destructor) ellipse::dealloc,
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
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_BASETYPE,
        "",
        (traverseproc) ellipse::traverse,
        (inquiry) ellipse::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        ellipse::methods,
        nullptr,
        (PyGetSetDef *) ellipse::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) ellipse::init,
        nullptr,
        ellipse::new_,
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
