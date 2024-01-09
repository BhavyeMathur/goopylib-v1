#include "circle.h"

namespace circle {
    static PyMethodDef methods[] = {
            {nullptr}
    };
}

PyTypeObject CircleType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Circle",
        sizeof(CircleObject),
        0,
        (destructor) circle::dealloc,
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
        (traverseproc) circle::traverse,
        (inquiry) circle::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        circle::methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) circle::init,
        nullptr,
        circle::new_,
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
