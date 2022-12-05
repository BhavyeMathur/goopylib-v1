#pragma once

#include <Python.h>
#include "pch.h"
#include "util.h"

#include <goopylib/Math/Easing.h>

#define EASING_TYPE(name) \
static PyTypeObject type = { \
    PyVarObject_HEAD_INIT(nullptr, 0) \
    .tp_itemsize = 0, \
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, \
    .tp_new = PyType_GenericNew, \
    .tp_init = (initproc) init, \
    .tp_call = (ternaryfunc) call, \
    .tp_repr = (reprfunc) repr, \
    .tp_basicsize = sizeof(EasingObject), \
    .tp_name = name, \
    .tp_traverse = (traverseproc) traverse, \
    .tp_clear = (inquiry) clear, \
    .tp_dealloc = (destructor) dealloc \
};

#define PyEasing_HEAD PyObject_HEAD std::function<float(float)> easing; PyObject *string;

struct EasingObject {
    PyEasing_HEAD
};

namespace easing {
    static int traverse(EasingObject *self, visitproc visit, void *arg) {
        Py_VISIT(self->string);
        return 0;
    }

    static int clear(EasingObject *self) {
        Py_CLEAR(self->string);
        return 0;
    }

    static void dealloc(EasingObject *self) {
        PyObject_GC_UnTrack(self);
        clear(self);
        Py_TYPE(self)->tp_free((PyObject *) self);
    }

    PyObject *call(EasingObject *self, PyObject *args) {
        float t;
        if (!PyArg_ParseTuple(args, "f", &t)) {
            return nullptr;
        }
        #ifdef GP_ERROR_CHECKING
        if (t > 1 or t < 0) { RAISE_VALUE_ERROR(nullptr, "easing argument must be between 0 and 1 (inclusive)") }
        #endif

        return PyFloat_FromDouble(self->easing(t));
    }

    static PyObject *repr(EasingObject *self) {
        Py_INCREF(self->string);
        return self->string;
    }

    namespace linear {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseLinear();
            self->string = PyUnicode_FromString("ease_linear()");
            return 0;
        }

        EASING_TYPE("linear")
    }

    namespace poly {
        int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            float power = 6;
            if (!PyArg_ParseTuple(args, "|f", &power)) {
                return -1;
            }

            self->easing = gp::EasePolyInOut(power);
            self->string = PyUnicode_FromFormat("ease_poly(power=%S)", PyFloat_FromDouble(power));
            return 0;
        }

        EASING_TYPE("poly")

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                float power = 6;
                if (!PyArg_ParseTuple(args, "|f", &power)) {
                    return -1;
                }

                self->easing = gp::EasePolyIn(power);
                self->string = PyUnicode_FromFormat("ease_poly_in(power=%S)", PyFloat_FromDouble(power));
                return 0;
            }

            EASING_TYPE("poly_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                float power = 6;
                if (!PyArg_ParseTuple(args, "|f", &power)) {
                    return -1;
                }

                self->easing = gp::EasePolyOut(power);
                self->string = PyUnicode_FromFormat("ease_poly_out(power=%S)", PyFloat_FromDouble(power));
                return 0;
            }

            EASING_TYPE("poly_out")
        }
    }

    namespace quad {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseQuadInOut();
            self->string = PyUnicode_FromString("ease_quad()");
            return 0;
        }

        EASING_TYPE("quad")

        namespace in {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseQuadIn();
                self->string = PyUnicode_FromString("ease_quad_in()");
                return 0;
            }

            EASING_TYPE("quad_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseQuadOut();
                self->string = PyUnicode_FromString("ease_quad_out()");
                return 0;
            }

            EASING_TYPE("quad_out")
        }
    }

    namespace cubic {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseCubicInOut();
            self->string = PyUnicode_FromString("ease_cubic()");
            return 0;
        }

        EASING_TYPE("cubic")

        namespace in {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseCubicIn();
                self->string = PyUnicode_FromString("ease_cubic_in()");
                return 0;
            }

            EASING_TYPE("cubic_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseCubicOut();
                self->string = PyUnicode_FromString("ease_cubic_out()");
                return 0;
            }

            EASING_TYPE("cubic_out")
        }
    }

    namespace quart {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseQuartInOut();
            self->string = PyUnicode_FromString("ease_quart()");
            return 0;
        }

        EASING_TYPE("quart")

        namespace in {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseQuartIn();
                self->string = PyUnicode_FromString("ease_quart_in()");
                return 0;
            }

            EASING_TYPE("quart_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseQuartOut();
                self->string = PyUnicode_FromString("ease_quart_out()");
                return 0;
            }

            EASING_TYPE("quart_out")
        }
    }

    namespace quint {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseQuintInOut();
            self->string = PyUnicode_FromString("ease_quint()");
            return 0;
        }

        EASING_TYPE("quint")

        namespace in {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseQuintIn();
                self->string = PyUnicode_FromString("ease_quint_in()");
                return 0;
            }

            EASING_TYPE("quint_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseQuintOut();
                self->string = PyUnicode_FromString("ease_quint_out()");
                return 0;
            }

            EASING_TYPE("quint_out")
        }
    }

    namespace circle {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseCircleInOut();
            self->string = PyUnicode_FromString("ease_circle()");
            return 0;
        }

        EASING_TYPE("circle")

        namespace in {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseCircleIn();
                self->string = PyUnicode_FromString("ease_circle_in()");
                return 0;
            }

            EASING_TYPE("circle_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseCircleOut();
                self->string = PyUnicode_FromString("ease_circle_out()");
                return 0;
            }

            EASING_TYPE("circle_out")
        }
    }

    namespace sin {
        int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
            self->easing = gp::EaseSinInOut();
            self->string = PyUnicode_FromString("ease_sin()");
            return 0;
        }

        EASING_TYPE("sin")

        namespace in {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseSinIn();
                self->string = PyUnicode_FromString("ease_sin_in()");
                return 0;
            }

            EASING_TYPE("sin_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
                self->easing = gp::EaseSinOut();
                self->string = PyUnicode_FromString("ease_sin_out()");
                return 0;
            }

            EASING_TYPE("sin_out")
        }
    }

    namespace exp {
        int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            float base = 2.718281828459045;
            if (!PyArg_ParseTuple(args, "|f", &base)) {
                return -1;
            }

            self->easing = gp::EaseExpInOut(base);
            self->string = PyUnicode_FromFormat("ease_exp(base=%S)", PyFloat_FromDouble(base));
            return 0;
        }

        EASING_TYPE("exp")

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                float base = 2.718281828459045;
                if (!PyArg_ParseTuple(args, "|f", &base)) {
                    return -1;
                }

                self->easing = gp::EaseExpIn(base);
                self->string = PyUnicode_FromFormat("ease_exp_in(base=%S)", PyFloat_FromDouble(base));
                return 0;
            }

            EASING_TYPE("exp_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                float base = 2.718281828459045;
                if (!PyArg_ParseTuple(args, "|f", &base)) {
                    return -1;
                }

                self->easing = gp::EaseExpOut(base);
                self->string = PyUnicode_FromFormat("ease_exp_out(base=%S)", PyFloat_FromDouble(base));
                return 0;
            }

            EASING_TYPE("exp_out")
        }
    }

    namespace back {
        int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            float factor = 1.70158;
            if (!PyArg_ParseTuple(args, "|f", &factor)) {
                return -1;
            }

            self->easing = gp::EaseBackInOut(factor);
            self->string = PyUnicode_FromFormat("ease_back(factor=%S)", PyFloat_FromDouble(factor));
            return 0;
        }

        EASING_TYPE("back")

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                float factor = 1.70158;
                if (!PyArg_ParseTuple(args, "|f", &factor)) {
                    return -1;
                }

                self->easing = gp::EaseBackIn(factor);
                self->string = PyUnicode_FromFormat("ease_back_in(factor=%S)", PyFloat_FromDouble(factor));
                return 0;
            }

            EASING_TYPE("back_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                float factor = 1.70158;
                if (!PyArg_ParseTuple(args, "|f", &factor)) {
                    return -1;
                }

                self->easing = gp::EaseBackOut(factor);
                self->string = PyUnicode_FromFormat("ease_back_out(factor=%S)", PyFloat_FromDouble(factor));
                return 0;
            }

            EASING_TYPE("back_out")
        }
    }

    namespace elastic {
        int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
            int factor = 3;
            if (!PyArg_ParseTuple(args, "|I", &factor)) {
                return -1;
            }

            self->easing = gp::EaseElasticInOut(factor);
            self->string = PyUnicode_FromFormat("ease_elastic(factor=%i)", factor);
            return 0;
        }

        EASING_TYPE("elastic")

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                int factor = 3;
                if (!PyArg_ParseTuple(args, "|I", &factor)) {
                    return -1;
                }

                self->easing = gp::EaseElasticIn(factor);
                self->string = PyUnicode_FromFormat("ease_elastic_in(factor=%i)", factor);
                return 0;
            }

            EASING_TYPE("elastic_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
                int factor = 3;
                if (!PyArg_ParseTuple(args, "|I", &factor)) {
                    return -1;
                }

                self->easing = gp::EaseElasticOut(factor);
                self->string = PyUnicode_FromFormat("ease_elastic_out(factor=%i)", factor);
                return 0;
            }

            EASING_TYPE("elastic_out")
        }
    }

    namespace bounce {
        int init(EasingObject *self, PyObject *args, PyObject *kwds) {
            static const char *kwlist[] = {"bounces", "damping", nullptr};

            int bounces = 4;
            float damping = 0.4;
            if (!PyArg_ParseTupleAndKeywords(args, kwds, "|if", (char **) kwlist, &bounces, &damping)) {
                return -1;
            }

            self->easing = gp::EaseBounceInOut(bounces, damping);
            self->string = PyUnicode_FromFormat("ease_bounce(bounces=%i, damping=%S)", bounces,
                                                PyFloat_FromDouble(damping));
            return 0;
        }

        EASING_TYPE("bounce")

        namespace in {
            int init(EasingObject *self, PyObject *args, PyObject *kwds) {
                static const char *kwlist[] = {"bounces", "damping", nullptr};

                int bounces = 4;
                float damping = 0.4;
                if (!PyArg_ParseTupleAndKeywords(args, kwds, "|if", (char **) kwlist, &bounces, &damping)) {
                    return -1;
                }

                self->easing = gp::EaseBounceIn(bounces, damping);
                self->string = PyUnicode_FromFormat("ease_bounce_in(bounces=%i, damping=%S)", bounces,
                                                    PyFloat_FromDouble(damping));
                return 0;
            }

            EASING_TYPE("bounce_in")
        }

        namespace out {
            int init(EasingObject *self, PyObject *args, PyObject *kwds) {
                static const char *kwlist[] = {"bounces", "damping", nullptr};

                int bounces = 4;
                float damping = 0.4;
                if (!PyArg_ParseTupleAndKeywords(args, kwds, "|if", (char **) kwlist, &bounces, &damping)) {
                    return -1;
                }

                self->easing = gp::EaseBounceOut(bounces, damping);
                self->string = PyUnicode_FromFormat("ease_bounce_out(bounces=%i, damping=%S)", bounces,
                                                    PyFloat_FromDouble(damping));
                return 0;
            }

            EASING_TYPE("bounce_out")
        }
    }
}

int PyInit_easing(PyObject *m) {
    EXPOSE_CLASS(easing::linear::type, "ease_linear")

    EXPOSE_CLASS(easing::poly::in::type, "ease_poly_in")
    EXPOSE_CLASS(easing::poly::out::type, "ease_poly_out")
    EXPOSE_CLASS(easing::poly::type, "ease_poly")

    EXPOSE_CLASS(easing::quad::in::type, "ease_quad_in")
    EXPOSE_CLASS(easing::quad::out::type, "ease_quad_out")
    EXPOSE_CLASS(easing::quad::type, "ease_quad")

    EXPOSE_CLASS(easing::cubic::in::type, "ease_cubic_in")
    EXPOSE_CLASS(easing::cubic::out::type, "ease_cubic_out")
    EXPOSE_CLASS(easing::cubic::type, "ease_cubic")

    EXPOSE_CLASS(easing::quart::in::type, "ease_quart_in")
    EXPOSE_CLASS(easing::quart::out::type, "ease_quart_out")
    EXPOSE_CLASS(easing::quart::type, "ease_quart")

    EXPOSE_CLASS(easing::quint::in::type, "ease_quint_in")
    EXPOSE_CLASS(easing::quint::out::type, "ease_quint_out")
    EXPOSE_CLASS(easing::quint::type, "ease_quint")

    EXPOSE_CLASS(easing::circle::in::type, "ease_circle_in")
    EXPOSE_CLASS(easing::circle::out::type, "ease_circle_out")
    EXPOSE_CLASS(easing::circle::type, "ease_circle")

    EXPOSE_CLASS(easing::sin::in::type, "ease_sin_in")
    EXPOSE_CLASS(easing::sin::out::type, "ease_sin_out")
    EXPOSE_CLASS(easing::sin::type, "ease_sin")

    EXPOSE_CLASS(easing::exp::in::type, "ease_exp_in")
    EXPOSE_CLASS(easing::exp::out::type, "ease_exp_out")
    EXPOSE_CLASS(easing::exp::type, "ease_exp")

    EXPOSE_CLASS(easing::back::in::type, "ease_back_in")
    EXPOSE_CLASS(easing::back::out::type, "ease_back_out")
    EXPOSE_CLASS(easing::back::type, "ease_back")

    EXPOSE_CLASS(easing::elastic::in::type, "ease_elastic_in")
    EXPOSE_CLASS(easing::elastic::out::type, "ease_elastic_out")
    EXPOSE_CLASS(easing::elastic::type, "ease_elastic")

    EXPOSE_CLASS(easing::bounce::in::type, "ease_bounce_in")
    EXPOSE_CLASS(easing::bounce::out::type, "ease_bounce_out")
    EXPOSE_CLASS(easing::bounce::type, "ease_bounce")

    return 0;
}
