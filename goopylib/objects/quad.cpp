#include <map-macro/map.h>
#include <pybind11/pybind11.h>

#include "goopylib/header.h"
#include "objects/Quad.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(quad, m) {
    py::class_<gp::Quad, gp::Renderable>(m, "Quad")
            .def(py::init([](py::tuple p1, py::tuple p2, py::tuple p3, py::tuple p4) {
                GP_PARSE_POINTS(1, 2, 3, 4);
                return new gp::Quad(v1, v2, v3, v4);
            }), "p1"_a, "p2"_a, "p3"_a, "p4"_a)

            .def("set_color", static_cast<void (gp::Quad::*)(const gp::Color &)>(&gp::Quad::setColor))
            .def("set_color", static_cast<void (gp::Quad::*)(const gp::Color &, const gp::Color &, const gp::Color &, const gp::Color &)>(&gp::Quad::setColor))
            .def("set_color", static_cast<void (gp::Quad::*)(const char *, float)>(&gp::Quad::setColor))
            .def("set_color", static_cast<void (gp::Quad::*)(const char *, const char *, const char *, const char *)>(&gp::Quad::setColor))
            .def("set_color", static_cast<void (gp::Quad::*)(int, int, int, float)>(&gp::Quad::setColor))

            .def_property("transparency", GP_GET_STRUCT_TUPLE(gp::Quad, Transparency, a1, a2, a3, a4),
                          [](gp::Quad &self, const py::object &value) {
                              if (py::isinstance<py::tuple>(value)) {
                                  py::tuple object = value;
                                  GP_GET_ELEMENT_FROM_TUPLE(0, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(1, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(2, float);
                                  GP_GET_ELEMENT_FROM_TUPLE(3, float);
                                  self.setTransparency(value0, value1, value2, value3);
                              } else {
                                  self.setTransparency(value.cast<float>());
                              }
                          })

                    GP_POINT_PROPERTY(gp::Quad, 1)
                    GP_POINT_PROPERTY(gp::Quad, 2)
                    GP_POINT_PROPERTY(gp::Quad, 3)
                    GP_POINT_PROPERTY(gp::Quad, 4)
                    ;
}
