#include "line.h"

namespace line {
    static PyMethodDef methods[] = {
            {"set_color",        (PyCFunction) set_color,        METH_VARARGS,
                    "Sets the color of the object"},
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            GETTER_SETTER(thickness),
            {nullptr}
    };
}

PyTypeObject LineType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Line",
        sizeof(LineObject),
        0,
        (destructor) line::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) line::repr,
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
        (traverseproc) line::traverse,
        (inquiry) line::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        line::methods,
        nullptr,
        (PyGetSetDef *) line::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) line::init,
        nullptr,
        line::new_,
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
