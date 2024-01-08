#include "image.h"

namespace image {
    static PyMethodDef methods[] = {
            {"set_transparency", (PyCFunction) set_transparency, METH_VARARGS,
                    "Sets the transparency of the object"},
            {"get_path",         (PyCFunction) get_path,         METH_NOARGS,
                    "Returns the filepath the image is using"},

            {nullptr}
    };
}

PyTypeObject ImageType = {
        PyVarObject_HEAD_INIT(nullptr, 0)
        "goopylib.Image",
        sizeof(ImageObject),
        0,
        (destructor) image::dealloc,
        0,
        nullptr,
        nullptr,
        nullptr,
        (reprfunc) image::repr,
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
        (traverseproc) image::traverse,
        (inquiry) image::clear,
        nullptr,
        0,
        nullptr,
        nullptr,
        image::methods,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        0,
        (initproc) image::init,
        nullptr,
        image::new_,
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
