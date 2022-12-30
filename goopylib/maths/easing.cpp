#include "easing.h"
#include "goopylib/maths/Easing.h"

#include "config.h"

#if (GP_LOG_EASING != true) and (GP_LOG_EASING <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_EASING
#endif

#if !GP_VALUE_CHECK_EASING
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"

// TODO Easing base class

namespace easing {
    struct EasingObject {
        PyObject_HEAD
        std::function<float(float)> easing;
        PyObject *string;
    };

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

        return PyFloat_FromDouble(self->easing(t));
    }

    static PyObject *repr(EasingObject *self) {
        Py_INCREF(self->string);
        return self->string;
    }
}

namespace easing {
    int linear::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeLinear();
        self->string = PyUnicode_FromString("ease_linear()");
        return 0;
    }

    EASING_IN_OUT_TYPE(linear);

    int poly::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float power;
        if (!PyArg_ParseTuple(args, "f", &power)) {
            return -1;
        }

        self->easing = gp::easePolyInOut(power);
        self->string = PyUnicode_FromFormat("ease_poly(power=%S)", PyFloat_FromDouble(power));
        return 0;
    }

    int poly::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float power;
        if (!PyArg_ParseTuple(args, "f", &power)) {
            return -1;
        }

        self->easing = gp::easePolyIn(power);
        self->string = PyUnicode_FromFormat("ease_poly_in(power=%S)", PyFloat_FromDouble(power));
        return 0;
    }

    int poly::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float power;
        if (!PyArg_ParseTuple(args, "f", &power)) {
            return -1;
        }

        self->easing = gp::easePolyOut(power);
        self->string = PyUnicode_FromFormat("ease_poly_out(power=%S)", PyFloat_FromDouble(power));
        return 0;
    }

    EASING_IN_OUT_TYPE(poly);
    EASING_IN_TYPE(poly);
    EASING_OUT_TYPE(poly);

    int quad::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuadInOut();
        self->string = PyUnicode_FromString("ease_quad()");
        return 0;
    }

    int quad::in::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuadIn();
        self->string = PyUnicode_FromString("ease_quad_in()");
        return 0;
    }

    int quad::out::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuadOut();
        self->string = PyUnicode_FromString("ease_quad_out()");
        return 0;
    }

    EASING_IN_OUT_TYPE(quad);
    EASING_IN_TYPE(quad);
    EASING_OUT_TYPE(quad);

    int cubic::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeCubicInOut();
        self->string = PyUnicode_FromString("ease_cubic()");
        return 0;
    }

    int cubic::in::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeCubicIn();
        self->string = PyUnicode_FromString("ease_cubic_in()");
        return 0;
    }

    int cubic::out::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeCubicOut();
        self->string = PyUnicode_FromString("ease_cubic_out()");
        return 0;
    }

    EASING_IN_OUT_TYPE(cubic);
    EASING_IN_TYPE(cubic);
    EASING_OUT_TYPE(cubic);

    int quart::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuartInOut();
        self->string = PyUnicode_FromString("ease_quart()");
        return 0;
    }

    int quart::in::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuartIn();
        self->string = PyUnicode_FromString("ease_quart_in()");
        return 0;
    }

    int quart::out::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuartOut();
        self->string = PyUnicode_FromString("ease_quart_out()");
        return 0;
    }

    EASING_IN_OUT_TYPE(quart);
    EASING_IN_TYPE(quart);
    EASING_OUT_TYPE(quart);

    int quint::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuintInOut();
        self->string = PyUnicode_FromString("ease_quint()");
        return 0;
    }

    int quint::in::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuintIn();
        self->string = PyUnicode_FromString("ease_quint_in()");
        return 0;
    }

    int quint::out::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeQuintOut();
        self->string = PyUnicode_FromString("ease_quint_out()");
        return 0;
    }

    EASING_IN_OUT_TYPE(quint);
    EASING_IN_TYPE(quint);
    EASING_OUT_TYPE(quint);

    int circle::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeCircleInOut();
        self->string = PyUnicode_FromString("ease_circle()");
        return 0;
    }

    int circle::in::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeCircleIn();
        self->string = PyUnicode_FromString("ease_circle_in()");
        return 0;
    }

    int circle::out::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeCircleOut();
        self->string = PyUnicode_FromString("ease_circle_out()");
        return 0;
    }

    EASING_IN_OUT_TYPE(circle);
    EASING_IN_TYPE(circle);
    EASING_OUT_TYPE(circle);

    int sin::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeSinInOut();
        self->string = PyUnicode_FromString("ease_sin()");
        return 0;
    }

    int sin::in::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeSinIn();
        self->string = PyUnicode_FromString("ease_sin_in()");
        return 0;
    }

    int sin::out::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeSinOut();
        self->string = PyUnicode_FromString("ease_sin_out()");
        return 0;
    }

    EASING_IN_OUT_TYPE(sin);
    EASING_IN_TYPE(sin);
    EASING_OUT_TYPE(sin);

    int exp::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float base;
        if (!PyArg_ParseTuple(args, "f", &base)) {
            return -1;
        }

        self->easing = gp::easeExpInOut(base);
        self->string = PyUnicode_FromFormat("ease_exp(base=%S)", PyFloat_FromDouble(base));
        return 0;
    }

    int exp::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float base;
        if (!PyArg_ParseTuple(args, "f", &base)) {
            return -1;
        }

        self->easing = gp::easeExpIn(base);
        self->string = PyUnicode_FromFormat("ease_exp_in(base=%S)", PyFloat_FromDouble(base));
        return 0;
    }

    int exp::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float base;
        if (!PyArg_ParseTuple(args, "f", &base)) {
            return -1;
        }

        self->easing = gp::easeExpOut(base);
        self->string = PyUnicode_FromFormat("ease_exp_out(base=%S)", PyFloat_FromDouble(base));
        return 0;
    }

    EASING_IN_OUT_TYPE(exp);
    EASING_IN_TYPE(exp);
    EASING_OUT_TYPE(exp);

    int back::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float factor;
        if (!PyArg_ParseTuple(args, "f", &factor)) {
            return -1;
        }

        self->easing = gp::easeBackInOut(factor);
        self->string = PyUnicode_FromFormat("ease_back(factor=%S)", PyFloat_FromDouble(factor));
        return 0;
    }

    int back::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float factor;
        if (!PyArg_ParseTuple(args, "f", &factor)) {
            return -1;
        }

        self->easing = gp::easeBackIn(factor);
        self->string = PyUnicode_FromFormat("ease_back_in(factor=%S)", PyFloat_FromDouble(factor));
        return 0;
    }

    int back::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float factor;
        if (!PyArg_ParseTuple(args, "f", &factor)) {
            return -1;
        }

        self->easing = gp::easeBackOut(factor);
        self->string = PyUnicode_FromFormat("ease_back_out(factor=%S)", PyFloat_FromDouble(factor));
        return 0;
    }

    EASING_IN_OUT_TYPE(back);
    EASING_IN_TYPE(back);
    EASING_OUT_TYPE(back);

    int elastic::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int factor;
        if (!PyArg_ParseTuple(args, "i", &factor)) {
            return -1;
        }

        self->easing = gp::easeElasticInOut(factor);
        self->string = PyUnicode_FromFormat("ease_elastic(factor=%i)", factor);
        return 0;
    }

    int elastic::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int factor;
        if (!PyArg_ParseTuple(args, "i", &factor)) {
            return -1;
        }

        self->easing = gp::easeElasticIn(factor);
        self->string = PyUnicode_FromFormat("ease_elastic_in(factor=%i)", factor);
        return 0;
    }

    int elastic::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int factor;
        if (!PyArg_ParseTuple(args, "i", &factor)) {
            return -1;
        }

        self->easing = gp::easeElasticOut(factor);
        self->string = PyUnicode_FromFormat("ease_elastic_out(factor=%i)", factor);
        return 0;
    }

    EASING_IN_OUT_TYPE(elastic);
    EASING_IN_TYPE(elastic);
    EASING_OUT_TYPE(elastic);

    int bounce::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int bounces;
        float damping;
        if (!PyArg_ParseTuple(args, "if", &bounces, &damping)) {
            return -1;
        }

        GP_CHECK_GE(damping, 0, -1, "damping value for easing must be greater than or equal to 0")
        GP_CHECK_GE(bounces, 1, -1, "bounces value for easing must be greater than or equal to 1")

        self->easing = gp::easeBounceInOut(bounces, damping);
        self->string = PyUnicode_FromFormat("ease_bounce(bounces=%i, damping=%S)", bounces,
                                            PyFloat_FromDouble(damping));
        return 0;
    }

    int bounce::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int bounces;
        float damping;
        if (!PyArg_ParseTuple(args, "if", &bounces, &damping)) {
            return -1;
        }

        self->easing = gp::easeBounceIn(bounces, damping);
        self->string = PyUnicode_FromFormat("ease_bounce_in(bounces=%i, damping=%S)", bounces,
                                            PyFloat_FromDouble(damping));
        return 0;
    }

    int bounce::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int bounces;
        float damping;
        if (!PyArg_ParseTuple(args, "if", &bounces, &damping)) {
            return -1;
        }

        self->easing = gp::easeBounceOut(bounces, damping);
        self->string = PyUnicode_FromFormat("ease_bounce_out(bounces=%i, damping=%S)", bounces,
                                            PyFloat_FromDouble(damping));
        return 0;
    }

    EASING_IN_OUT_TYPE(bounce);
    EASING_IN_TYPE(bounce);
    EASING_OUT_TYPE(bounce);
}

static PyMethodDef EasingMethods[] = {
        {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef easingmodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "easing",
        .m_size = -1,
        .m_methods = EasingMethods,
};

PyMODINIT_FUNC PyInit_easing() {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_easing()" << std::endl;
    #endif

    PyObject *m;
    m = PyModule_Create(&easingmodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(easing::linear_type, "ease_linear");

    EXPOSE_PYOBJECT_CLASS(easing::poly_in_type, "ease_poly_in");
    EXPOSE_PYOBJECT_CLASS(easing::poly_out_type, "ease_poly_out");
    EXPOSE_PYOBJECT_CLASS(easing::poly_type, "ease_poly");

    EXPOSE_PYOBJECT_CLASS(easing::quad_in_type, "ease_quad_in");
    EXPOSE_PYOBJECT_CLASS(easing::quad_out_type, "ease_quad_out");
    EXPOSE_PYOBJECT_CLASS(easing::quad_type, "ease_quad");

    EXPOSE_PYOBJECT_CLASS(easing::cubic_in_type, "ease_cubic_in");
    EXPOSE_PYOBJECT_CLASS(easing::cubic_out_type, "ease_cubic_out");
    EXPOSE_PYOBJECT_CLASS(easing::cubic_type, "ease_cubic");

    EXPOSE_PYOBJECT_CLASS(easing::quart_in_type, "ease_quart_in");
    EXPOSE_PYOBJECT_CLASS(easing::quart_out_type, "ease_quart_out");
    EXPOSE_PYOBJECT_CLASS(easing::quart_type, "ease_quart");

    EXPOSE_PYOBJECT_CLASS(easing::quint_in_type, "ease_quint_in");
    EXPOSE_PYOBJECT_CLASS(easing::quint_out_type, "ease_quint_out");
    EXPOSE_PYOBJECT_CLASS(easing::quint_type, "ease_quint");

    EXPOSE_PYOBJECT_CLASS(easing::circle_in_type, "ease_circle_in");
    EXPOSE_PYOBJECT_CLASS(easing::circle_out_type, "ease_circle_out");
    EXPOSE_PYOBJECT_CLASS(easing::circle_type, "ease_circle");

    EXPOSE_PYOBJECT_CLASS(easing::sin_in_type, "ease_sin_in");
    EXPOSE_PYOBJECT_CLASS(easing::sin_out_type, "ease_sin_out");
    EXPOSE_PYOBJECT_CLASS(easing::sin_type, "ease_sin");

    EXPOSE_PYOBJECT_CLASS(easing::exp_in_type, "ease_exp_in");
    EXPOSE_PYOBJECT_CLASS(easing::exp_out_type, "ease_exp_out");
    EXPOSE_PYOBJECT_CLASS(easing::exp_type, "ease_exp");

    EXPOSE_PYOBJECT_CLASS(easing::back_in_type, "ease_back_in");
    EXPOSE_PYOBJECT_CLASS(easing::back_out_type, "ease_back_out");
    EXPOSE_PYOBJECT_CLASS(easing::back_type, "ease_back");

    EXPOSE_PYOBJECT_CLASS(easing::elastic_in_type, "ease_elastic_in");
    EXPOSE_PYOBJECT_CLASS(easing::elastic_out_type, "ease_elastic_out");
    EXPOSE_PYOBJECT_CLASS(easing::elastic_type, "ease_elastic");

    EXPOSE_PYOBJECT_CLASS(easing::bounce_in_type, "ease_bounce_in");
    EXPOSE_PYOBJECT_CLASS(easing::bounce_out_type, "ease_bounce_out");
    EXPOSE_PYOBJECT_CLASS(easing::bounce_type, "ease_bounce");

    return m;
}
