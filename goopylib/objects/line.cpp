#include <map-macro/map.h>
#include <pybind11/pybind11.h>

#include "goopylib/header.h"
#include "objects/Line.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(line, m) {
    auto colorModule = py::module_::import("goopylib.color");
    py::object Color = colorModule.attr("Color");

    py::class_<gp::Line, gp::Quad, gp::Renderable>(m, "Line")
            .def(py::init([](py::tuple p1, py::tuple p2, float thickness) {
                GP_PARSE_POINTS(1, 2);
                return new gp::Line(v1, v2, thickness);
            }), "p1"_a, "p2"_a, "thickness"_a = 3)

            .def("set_color", static_cast<void (gp::Line::*)(const gp::Color &)>(&gp::Line::setColor))
            .def("set_color", static_cast<void (gp::Line::*)(const char *, float)>(&gp::Line::setColor),
                 "color"_a, "alpha"_a=1)
            .def("set_color", static_cast<void (gp::Line::*)(int, int, int, float)>(&gp::Line::setColor),
                 "red"_a, "green"_a, "blue"_a, "alpha"_a=1)
            .def("set_color", GP_COLOR_SETTER(gp::Line, 1, 2, 3, 4))
            .def("set_color", GP_COLOR_SETTER(gp::Line, 1, 2))
            
            .def_property("transparency",
                          GP_GET_STRUCT_TUPLE(gp::Line, Transparency, a1, a2),
                          [](gp::Line &self, const py::object &value) {
                              if (py::isinstance<py::tuple>(value)) {
                                  py::tuple object = value;

                                  if (len(object) == 2) {
                                      GP_GET_ELEMENT_FROM_TUPLE(0, float);
                                      GP_GET_ELEMENT_FROM_TUPLE(1, float);
                                      self.setTransparency(value0, value1);
                                  }
                                  else if (len(object) == 4) {
                                      GP_GET_ELEMENT_FROM_TUPLE(0, float);
                                      GP_GET_ELEMENT_FROM_TUPLE(1, float);
                                      GP_GET_ELEMENT_FROM_TUPLE(2, float);
                                      GP_GET_ELEMENT_FROM_TUPLE(3, float);
                                      self.setTransparency(value0, value1, value2, value3);
                                  }
                                  else {
                                      throw std::invalid_argument("Transparency tuple must contain 2 or 4 values");
                                  }

                              } else {
                                  self.setTransparency(value.cast<float>());
                              }
                          })
            .def_property("thickness", &gp::Line::getThickness, &gp::Line::setThickness);
}
