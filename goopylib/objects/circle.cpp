#include <map-macro/map.h>

#include "goopylib/header.h"
#include "objects/Circle.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(circle, m) {
    py::class_<gp::Circle, gp::Ellipse, gp::Renderable>(m, "Circle")
            .def(py::init([](py::tuple p1, float radius) {
                GP_PARSE_POINTS(1);
                return new gp::Circle(v1, radius);
            }), "p1"_a, "radius"_a);
}
