#include <map-macro/map.h>

#include "goopylib/header.h"
#include "objects/Quad.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(quad, m) {
    auto colorModule = py::module_::import("goopylib.color");
    py::object Color = colorModule.attr("Color");

    py::class_<gp::Quad, gp::Renderable>(m, "Quad")
            .def(py::init([](py::tuple p1, py::tuple p2, py::tuple p3, py::tuple p4) {
                GP_PARSE_POINTS(1, 2, 3, 4);
                return new gp::Quad(v1, v2, v3, v4);
            }), "p1"_a, "p2"_a, "p3"_a, "p4"_a)

                    GP_COLOR_SETTERS(gp::Quad, 1, 2, 3, 4)
                    GP_POINT_PROPERTY(gp::Quad, 1)
                    GP_POINT_PROPERTY(gp::Quad, 2)
                    GP_POINT_PROPERTY(gp::Quad, 3)
                    GP_POINT_PROPERTY(gp::Quad, 4)

            .def_property("transparency", GP_GET_STRUCT_TUPLE(gp::Quad, Transparency, a1, a2, a3, a4),
                          [](gp::Quad &self, const py::object &value) {
                              if (py::isinstance<py::tuple>(value)) {
                                  py::tuple object = value;

                                  if (len(object) != 4) {
                                      throw std::invalid_argument("Transparency tuple must contain 4 values");
                                  }

                                  GP_GET_ELEMENT_FROM_TUPLE(0, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(1, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(2, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(3, float);
                                  self.setTransparency(value0, value1, value2, value3);
                              } else {
                                  self.setTransparency(value.cast<float>());
                              }
                          });
}
