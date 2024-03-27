#include <map-macro/map.h>

#include "goopylib/header.h"
#include "objects/Rectangle.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(rectangle, m) {
    py::class_<gp::Rectangle, gp::Quad, gp::Renderable>(m, "Rectangle")
            .def(py::init([](py::tuple p1, py::tuple p2) {
                GP_PARSE_POINTS(1, 2);
                return new gp::Rectangle(v1, v2);
            }), "p1"_a, "p2"_a)

            .def(py::init([](py::tuple p1, float width, float height) {
                GP_PARSE_POINT(1);
                return new gp::Rectangle(v1, width, height);
            }), "p1"_a, "width"_a, "height"_a);
}
