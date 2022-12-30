#pragma once

#include "header.h"

#define EASING_TYPE(name, space) \
static PyTypeObject name##_type = {\
    PyVarObject_HEAD_INIT(nullptr, 0) \
    .tp_itemsize = 0, \
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, \
    .tp_new = PyType_GenericNew, \
    .tp_init = (initproc) space::init, \
    .tp_call = (ternaryfunc) call, \
    .tp_repr = (reprfunc) repr, \
    .tp_basicsize = sizeof(EasingObject), \
    .tp_name = (#name), \
    .tp_traverse = (traverseproc) traverse, \
    .tp_clear = (inquiry) clear, \
    .tp_dealloc = (destructor) dealloc \
}

#define EASING_IN_TYPE(name) EASING_TYPE(name##_in, name::in)
#define EASING_OUT_TYPE(name) EASING_TYPE(name##_out, name::out)
#define EASING_IN_OUT_TYPE(name) EASING_TYPE(name, name)

namespace easing {
    struct EasingObject;

    static int traverse(EasingObject *self, visitproc visit, void *arg);

    static int clear(EasingObject *self);

    static void dealloc(EasingObject *self);

    PyObject *call(EasingObject *self, PyObject *args);

    static PyObject *repr(EasingObject *self);
}

namespace easing {
    namespace linear {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);
    }

    namespace poly {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace quad {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace cubic {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace quart {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);


        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace quint {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace circle {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace sin {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace exp {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace back {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace elastic {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }

    namespace bounce {
        int init(EasingObject *self, PyObject *args, PyObject *kwds);

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds);
        }
    }
}
