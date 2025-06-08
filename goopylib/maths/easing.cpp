#include <pybind11/functional.h>

#include "goopylib/header.h"
#include "maths/Easing.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(easing, m) {
    m.def("ease_linear", &gp::easeLinear);

    m.def("ease_poly", &gp::easePolyInOut, "power"_a=6);
    m.def("ease_poly_in", &gp::easePolyIn, "power"_a=6);
    m.def("ease_poly_out", &gp::easePolyOut, "power"_a=6);

    m.def("ease_quad", &gp::easeQuadInOut);
    m.def("ease_quad_in", &gp::easeQuadIn);
    m.def("ease_quad_out", &gp::easeQuadOut);

    m.def("ease_cubic", &gp::easeCubicInOut);
    m.def("ease_cubic_in", &gp::easeCubicIn);
    m.def("ease_cubic_out", &gp::easeCubicOut);

    m.def("ease_quart", &gp::easeQuartInOut);
    m.def("ease_quart_in", &gp::easeQuartIn);
    m.def("ease_quart_out", &gp::easeQuartOut);

    m.def("ease_quint", &gp::easeQuintInOut);
    m.def("ease_quint_in", &gp::easeQuintIn);
    m.def("ease_quint_out", &gp::easeQuintOut);

    m.def("ease_circle", &gp::easeCircleInOut);
    m.def("ease_circle_in", &gp::easeCircleIn);
    m.def("ease_circle_out", &gp::easeCircleOut);

    m.def("ease_sin", &gp::easeSinInOut);
    m.def("ease_sin_in", &gp::easeSinIn);
    m.def("ease_sin_out", &gp::easeSinOut);

    m.def("ease_exp", &gp::easeExpInOut, "base"_a=2.718281828459045);
    m.def("ease_exp_in", &gp::easeExpIn, "base"_a=2.718281828459045);
    m.def("ease_exp_out", &gp::easeExpOut, "base"_a=2.718281828459045);

    m.def("ease_back", &gp::easeBackInOut, "factor"_a=1.70158);
    m.def("ease_back_in", &gp::easeBackIn, "factor"_a=1.70158);
    m.def("ease_back_out", &gp::easeBackOut, "factor"_a=1.70158);

    m.def("ease_elastic", &gp::easeElasticInOut, "factor"_a=3);
    m.def("ease_elastic_in", &gp::easeElasticIn, "factor"_a=3);
    m.def("ease_elastic_out", &gp::easeElasticOut, "factor"_a=3);

    m.def("ease_bounce", &gp::easeBounceInOut, "bounces"_a=4, "damping"_a=0.4);
    m.def("ease_bounce_in", &gp::easeBounceIn, "bounces"_a=4, "damping"_a=0.4);
    m.def("ease_bounce_out", &gp::easeBounceOut, "bounces"_a=4, "damping"_a=0.4);
}
