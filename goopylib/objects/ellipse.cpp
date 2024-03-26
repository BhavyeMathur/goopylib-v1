#include <map-macro/map.h>

#include "goopylib/header.h"
#include "objects/Ellipse.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(ellipse, m) {
    auto colorModule = py::module_::import("goopylib.color");
    py::object Color = colorModule.attr("Color");

    py::class_<gp::Ellipse, gp::Renderable>(m, "Ellipse")
            .def(py::init([](py::tuple p1, py::tuple p2) {
                GP_PARSE_POINTS(1, 2);
                return new gp::Ellipse(v1, v2);
            }), "p1"_a, "p2"_a)

            .def(py::init([](py::tuple p1, float width, float height) {
                GP_PARSE_POINT(1);
                return new gp::Ellipse(v1, width, height);
            }), "p1"_a, "width"_a, "height"_a)

                    GP_COLOR_SETTERS(gp::Ellipse, 1, 2, 3, 4)

            .def_property("transparency", GP_GET_STRUCT_TUPLE(gp::Ellipse, Transparency, a1, a2, a3, a4),
                          [](gp::Ellipse &self, const py::object &value) {
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
            ;
}
