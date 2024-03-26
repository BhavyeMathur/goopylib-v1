#include <map-macro/map.h>
#include <pybind11/pybind11.h>

#include "goopylib/header.h"
#include "objects/Triangle.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(triangle, m) {
    auto colorModule = py::module_::import("goopylib.color");
    py::object Color = colorModule.attr("Color");

    py::class_<gp::Triangle, gp::Renderable>(m, "Triangle")
            .def(py::init([](py::tuple p1, py::tuple p2, py::tuple p3) {
                GP_PARSE_POINTS(1, 2, 3);
                return new gp::Triangle(v1, v2, v3);
            }), "p1"_a, "p2"_a, "p3"_a)

            .def("set_color", static_cast<void (gp::Triangle::*)(const gp::Color &)>(&gp::Triangle::setColor))
            .def("set_color", static_cast<void (gp::Triangle::*)(const char *, float)>(&gp::Triangle::setColor),
                 "color"_a, "alpha"_a=1)
            .def("set_color", static_cast<void (gp::Triangle::*)(int, int, int, float)>(&gp::Triangle::setColor),
                 "red"_a, "green"_a, "blue"_a, "alpha"_a=1)
            .def("set_color", GP_COLOR_SETTER(gp::Triangle, 1, 2, 3))

            .def_property("transparency", GP_GET_STRUCT_TUPLE(gp::Triangle, Transparency, a1, a2, a3),
                          [](gp::Triangle &self, const py::object &value) {
                              if (py::isinstance<py::tuple>(value)) {
                                  py::tuple object = value;

                                  if (len(object) != 3) {
                                      throw std::invalid_argument("Transparency tuple must contain 3 values");
                                  }

                                  GP_GET_ELEMENT_FROM_TUPLE(0, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(1, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(2, float);
                                  self.setTransparency(value0, value1, value2);
                              } else {
                                  self.setTransparency(value.cast<float>());
                              }
                          })

                    GP_POINT_PROPERTY(gp::Triangle, 1)
                    GP_POINT_PROPERTY(gp::Triangle, 2)
                    GP_POINT_PROPERTY(gp::Triangle, 3)
                    ;
}
