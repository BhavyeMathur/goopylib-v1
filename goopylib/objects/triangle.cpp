#include <map-macro/map.h>

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

                    GP_COLOR_SETTERS(gp::Triangle, 1, 2, 3)
                    GP_POINT_PROPERTY(gp::Triangle, 1)
                    GP_POINT_PROPERTY(gp::Triangle, 2)
                    GP_POINT_PROPERTY(gp::Triangle, 3)

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
                          });
}
