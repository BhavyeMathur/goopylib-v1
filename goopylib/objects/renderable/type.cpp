#include "renderable.h"

namespace renderable {
    static PyMethodDef methods[] = {
            {"draw",         (PyCFunction) draw,         METH_O,
                    "Draws the object to a window"},
            {"destroy",      (PyCFunction) destroy,      METH_NOARGS,
                    "Destroys the object"},
            {"is_drawn",     (PyCFunction) is_drawn,     METH_NOARGS,
                    "Checks if the object has been drawn to a Window"},

            {"set_anchor",   (PyCFunction) set_anchor,   METH_VARARGS,
                    "Sets the anchor point of the object"},
            {"reset_anchor", (PyCFunction) reset_anchor, METH_NOARGS,
                    "Resets the object's anchor to its center"},

            {"move",         (PyCFunction) move,         METH_VARARGS,
                    "Moves the object"},
            {"rotate",       (PyCFunction) rotate,       METH_O,
                    "Rotates the object"},
            {"scale",        (PyCFunction) scale,        METH_VARARGS,
                    "Scales the object"},
            {"set_size",     (PyCFunction) set_size,     METH_VARARGS,
                    "Sets the width and height of the object"},

            {"hide",         (PyCFunction) hide,         METH_O,
                    "Hides the object"},
            {"show",         (PyCFunction) show,         METH_NOARGS,
                    "Unhides the object"},
            {"is_hidden",    (PyCFunction) is_hidden,    METH_NOARGS,
                    "Checks if the object is hidden"},

            {"box_contains", (PyCFunction) box_contains, METH_VARARGS,
                    "Checks if the object's rectangular bounding box contains a point"},
            {"contains",     (PyCFunction) contains,     METH_VARARGS,
                    "Checks if the object's bounding box contains a point"},

            {nullptr}
    };

    static PyGetSetDef getsetters[] = {
            GETTER_SETTER(x),
            GETTER_SETTER(y),
            GETTER_SETTER(position),

            GETTER_SETTER(rotation),
            GETTER_SETTER(xscale),
            GETTER_SETTER(yscale),

            GETTER_SETTER(width),
            GETTER_SETTER(height),

            GETTER_SETTER(z),

            {nullptr}
    };
}

PyTypeObject RenderableType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Renderable",
        sizeof(RenderableObject),
        0,
        (destructor) renderable::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) renderable::repr,
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
        (traverseproc) renderable::traverse,
        (inquiry) renderable::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        (PyMethodDef *) renderable::methods,
        nullptr,
        (PyGetSetDef *) renderable::getsetters,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) renderable::init,
        nullptr,
        renderable::new_,
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
