#include "easing.h"
#include "src/goopylib/math/Easing.h"

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
        #ifdef GP_ERROR_CHECKING
        if (t > 1 or t < 0) {
            RAISE_VALUE_ERROR(nullptr, "easing argument must be between 0 and 1 (inclusive)");
        }
        #endif

        return PyFloat_FromDouble(self->easing(t));
    }

    static PyObject *repr(EasingObject *self) {
        Py_INCREF(self->string);
        return self->string;
    }

    int linear::init(EasingObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
        self->easing = gp::easeLinear();
        self->string = PyUnicode_FromString("ease_linear()");
        return 0;
    }

    int poly::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float power = 6;
        if (!PyArg_ParseTuple(args, "|f", &power)) {
            return -1;
        }

        self->easing = gp::easePolyInOut(power);
        self->string = PyUnicode_FromFormat("ease_poly(power=%S)", PyFloat_FromDouble(power));
        return 0;
    }

    int poly::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float power = 6;
        if (!PyArg_ParseTuple(args, "|f", &power)) {
            return -1;
        }

        self->easing = gp::easePolyIn(power);
        self->string = PyUnicode_FromFormat("ease_poly_in(power=%S)", PyFloat_FromDouble(power));
        return 0;
    }

    int poly::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float power = 6;
        if (!PyArg_ParseTuple(args, "|f", &power)) {
            return -1;
        }

        self->easing = gp::easePolyOut(power);
        self->string = PyUnicode_FromFormat("ease_poly_out(power=%S)", PyFloat_FromDouble(power));
        return 0;
    }

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

    int exp::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float base = 2.718281828459045;
        if (!PyArg_ParseTuple(args, "|f", &base)) {
            return -1;
        }

        self->easing = gp::easeExpInOut(base);
        self->string = PyUnicode_FromFormat("ease_exp(base=%S)", PyFloat_FromDouble(base));
        return 0;
    }

    int exp::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float base = 2.718281828459045;
        if (!PyArg_ParseTuple(args, "|f", &base)) {
            return -1;
        }

        self->easing = gp::easeExpIn(base);
        self->string = PyUnicode_FromFormat("ease_exp_in(base=%S)", PyFloat_FromDouble(base));
        return 0;
    }

    int exp::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float base = 2.718281828459045;
        if (!PyArg_ParseTuple(args, "|f", &base)) {
            return -1;
        }

        self->easing = gp::easeExpOut(base);
        self->string = PyUnicode_FromFormat("ease_exp_out(base=%S)", PyFloat_FromDouble(base));
        return 0;
    }

    int back::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float factor = 1.70158;
        if (!PyArg_ParseTuple(args, "|f", &factor)) {
            return -1;
        }

        self->easing = gp::easeBackInOut(factor);
        self->string = PyUnicode_FromFormat("ease_back(factor=%S)", PyFloat_FromDouble(factor));
        return 0;
    }

    int back::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float factor = 1.70158;
        if (!PyArg_ParseTuple(args, "|f", &factor)) {
            return -1;
        }

        self->easing = gp::easeBackIn(factor);
        self->string = PyUnicode_FromFormat("ease_back_in(factor=%S)", PyFloat_FromDouble(factor));
        return 0;
    }

    int back::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        float factor = 1.70158;
        if (!PyArg_ParseTuple(args, "|f", &factor)) {
            return -1;
        }

        self->easing = gp::easeBackOut(factor);
        self->string = PyUnicode_FromFormat("ease_back_out(factor=%S)", PyFloat_FromDouble(factor));
        return 0;
    }

    int elastic::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int factor = 3;
        if (!PyArg_ParseTuple(args, "|I", &factor)) {
            return -1;
        }

        self->easing = gp::easeElasticInOut(factor);
        self->string = PyUnicode_FromFormat("ease_elastic(factor=%i)", factor);
        return 0;
    }

    int elastic::in::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int factor = 3;
        if (!PyArg_ParseTuple(args, "|I", &factor)) {
            return -1;
        }

        self->easing = gp::easeElasticIn(factor);
        self->string = PyUnicode_FromFormat("ease_elastic_in(factor=%i)", factor);
        return 0;
    }

    int elastic::out::init(EasingObject *self, PyObject *args, PyObject *Py_UNUSED(kwds)) {
        int factor = 3;
        if (!PyArg_ParseTuple(args, "|I", &factor)) {
            return -1;
        }

        self->easing = gp::easeElasticOut(factor);
        self->string = PyUnicode_FromFormat("ease_elastic_out(factor=%i)", factor);
        return 0;
    }

    int bounce::init(EasingObject *self, PyObject *args, PyObject *kwds) {
        static const char *kwlist[] = {"bounces", "damping", nullptr};

        int bounces = 4;
        float damping = 0.4;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "|if", (char **) kwlist, &bounces, &damping)) {
            return -1;
        }

        self->easing = gp::easeBounceInOut(bounces, damping);
        self->string = PyUnicode_FromFormat("ease_bounce(bounces=%i, damping=%S)", bounces,
                                            PyFloat_FromDouble(damping));
        return 0;
    }

    int bounce::in::init(EasingObject *self, PyObject *args, PyObject *kwds) {
        static const char *kwlist[] = {"bounces", "damping", nullptr};

        int bounces = 4;
        float damping = 0.4;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "|if", (char **) kwlist, &bounces, &damping)) {
            return -1;
        }

        self->easing = gp::easeBounceIn(bounces, damping);
        self->string = PyUnicode_FromFormat("ease_bounce_in(bounces=%i, damping=%S)", bounces,
                                            PyFloat_FromDouble(damping));
        return 0;
    }

    int bounce::out::init(EasingObject *self, PyObject *args, PyObject *kwds) {
        static const char *kwlist[] = {"bounces", "damping", nullptr};

        int bounces = 4;
        float damping = 0.4;
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "|if", (char **) kwlist, &bounces, &damping)) {
            return -1;
        }

        self->easing = gp::easeBounceOut(bounces, damping);
        self->string = PyUnicode_FromFormat("ease_bounce_out(bounces=%i, damping=%S)", bounces,
                                            PyFloat_FromDouble(damping));
        return 0;
    }

    namespace linear {
        EASING_TYPE("linear");
    }

    namespace poly {
        EASING_TYPE("poly");

        namespace in {
            EASING_TYPE("poly_in");
        }

        namespace out {
            EASING_TYPE("poly_out");
        }
    }

    namespace quad {
        EASING_TYPE("quad");

        namespace in {
            EASING_TYPE("quad_in");
        }

        namespace out {
            EASING_TYPE("quad_out");
        }
    }

    namespace cubic {
        EASING_TYPE("cubic");

        namespace in {
            EASING_TYPE("cubic_in");
        }

        namespace out {
            EASING_TYPE("cubic_out");
        }
    }

    namespace quart {
        EASING_TYPE("quart");

        namespace in {
            EASING_TYPE("quart_in");
        }

        namespace out {
            EASING_TYPE("quart_out");
        }
    }

    namespace quint {
        EASING_TYPE("quint");

        namespace in {
            EASING_TYPE("quint_in");
        }

        namespace out {
            EASING_TYPE("quint_out");
        }
    }

    namespace circle {
        EASING_TYPE("circle");

        namespace in {
            EASING_TYPE("circle_in");
        }

        namespace out {
            EASING_TYPE("circle_out");
        }
    }

    namespace sin {
        EASING_TYPE("sin");

        namespace in {
            EASING_TYPE("sin_in");
        }

        namespace out {
            EASING_TYPE("sin_out");
        }
    }

    namespace exp {
        EASING_TYPE("exp");

        namespace in {
            EASING_TYPE("exp_in");
        }

        namespace out {
            EASING_TYPE("exp_out");
        }
    }

    namespace back {
        EASING_TYPE("back");

        namespace in {
            EASING_TYPE("back_in");
        }

        namespace out {
            EASING_TYPE("back_out");
        }
    }

    namespace elastic {
        EASING_TYPE("elastic");

        namespace in {
            EASING_TYPE("elastic_in");
        }

        namespace out {
            EASING_TYPE("elastic_out");
        }
    }

    namespace bounce {
        EASING_TYPE("bounce");

        namespace in {
            EASING_TYPE("bounce_in");
        }

        namespace out {
            EASING_TYPE("bounce_out");
        }
    }
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
    #if GP_LOGGING >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_easing()" << std::endl;
    #endif

    PyObject *m;
    m = PyModule_Create(&easingmodule);
    if (m == nullptr) {
        return nullptr;
    }

    EXPOSE_PYOBJECT_CLASS(easing::linear::type, "ease_linear");

    EXPOSE_PYOBJECT_CLASS(easing::poly::in::type, "ease_poly_in");
    EXPOSE_PYOBJECT_CLASS(easing::poly::out::type, "ease_poly_out");
    EXPOSE_PYOBJECT_CLASS(easing::poly::type, "ease_poly");

    EXPOSE_PYOBJECT_CLASS(easing::quad::in::type, "ease_quad_in");
    EXPOSE_PYOBJECT_CLASS(easing::quad::out::type, "ease_quad_out");
    EXPOSE_PYOBJECT_CLASS(easing::quad::type, "ease_quad");

    EXPOSE_PYOBJECT_CLASS(easing::cubic::in::type, "ease_cubic_in");
    EXPOSE_PYOBJECT_CLASS(easing::cubic::out::type, "ease_cubic_out");
    EXPOSE_PYOBJECT_CLASS(easing::cubic::type, "ease_cubic");

    EXPOSE_PYOBJECT_CLASS(easing::quart::in::type, "ease_quart_in");
    EXPOSE_PYOBJECT_CLASS(easing::quart::out::type, "ease_quart_out");
    EXPOSE_PYOBJECT_CLASS(easing::quart::type, "ease_quart");

    EXPOSE_PYOBJECT_CLASS(easing::quint::in::type, "ease_quint_in");
    EXPOSE_PYOBJECT_CLASS(easing::quint::out::type, "ease_quint_out");
    EXPOSE_PYOBJECT_CLASS(easing::quint::type, "ease_quint");

    EXPOSE_PYOBJECT_CLASS(easing::circle::in::type, "ease_circle_in");
    EXPOSE_PYOBJECT_CLASS(easing::circle::out::type, "ease_circle_out");
    EXPOSE_PYOBJECT_CLASS(easing::circle::type, "ease_circle");

    EXPOSE_PYOBJECT_CLASS(easing::sin::in::type, "ease_sin_in");
    EXPOSE_PYOBJECT_CLASS(easing::sin::out::type, "ease_sin_out");
    EXPOSE_PYOBJECT_CLASS(easing::sin::type, "ease_sin");

    EXPOSE_PYOBJECT_CLASS(easing::exp::in::type, "ease_exp_in");
    EXPOSE_PYOBJECT_CLASS(easing::exp::out::type, "ease_exp_out");
    EXPOSE_PYOBJECT_CLASS(easing::exp::type, "ease_exp");

    EXPOSE_PYOBJECT_CLASS(easing::back::in::type, "ease_back_in");
    EXPOSE_PYOBJECT_CLASS(easing::back::out::type, "ease_back_out");
    EXPOSE_PYOBJECT_CLASS(easing::back::type, "ease_back");

    EXPOSE_PYOBJECT_CLASS(easing::elastic::in::type, "ease_elastic_in");
    EXPOSE_PYOBJECT_CLASS(easing::elastic::out::type, "ease_elastic_out");
    EXPOSE_PYOBJECT_CLASS(easing::elastic::type, "ease_elastic");

    EXPOSE_PYOBJECT_CLASS(easing::bounce::in::type, "ease_bounce_in");
    EXPOSE_PYOBJECT_CLASS(easing::bounce::out::type, "ease_bounce_out");
    EXPOSE_PYOBJECT_CLASS(easing::bounce::type, "ease_bounce");

    return m;
}
