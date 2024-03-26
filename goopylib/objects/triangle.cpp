#include <map-macro/map.h>
#include <pybind11/pybind11.h>

#include "goopylib/header.h"
#include "objects/Triangle.h"

namespace py = pybind11;
using namespace pybind11::literals;

#define GP_POINT_TO_FLOATS(n) x##n = p##n[0].cast<float>(); y##n = p##n[1].cast<float>()
#define GP_SAFE_POINT_TO_FLOATS(n) float x##n, y##n; GP_RETHROW_ERROR(GP_POINT_TO_FLOATS(n), type_error, "Point must be a tuple of (x: float, y: float)")
#define GP_PARSE_POINT(n) GP_SAFE_POINT_TO_FLOATS(n); Point v##n{x##n, y##n};
#define GP_PARSE_POINTS(...) MAP(GP_PARSE_POINT, __VA_ARGS__)

PYBIND11_MODULE(triangle, m) {
    py::class_<gp::Triangle, gp::Renderable>(m, "Triangle")
            .def(py::init([](py::tuple p1, py::tuple p2, py::tuple p3) {
                GP_PARSE_POINTS(1, 2, 3);
                return new gp::Triangle(v1, v2, v3);
            }), "p1"_a, "p2"_a, "p3"_a)

            .def("set_color", static_cast<void (gp::Triangle::*)(const gp::Color &)>(&gp::Triangle::setColor))
            .def("set_color", static_cast<void (gp::Triangle::*)(const gp::Color &, const gp::Color &,
                                                                 const gp::Color &)>(&gp::Triangle::setColor))
            .def("set_color", static_cast<void (gp::Triangle::*)(const char *, float)>(&gp::Triangle::setColor))
            .def("set_color",
                 static_cast<void (gp::Triangle::*)(const char *, const char *, const char *)>(&gp::Triangle::setColor))
            .def("set_color", static_cast<void (gp::Triangle::*)(int, int, int, float)>(&gp::Triangle::setColor))

            .def_property("transparency", GP_GET_STRUCT_TUPLE(gp::Triangle, Transparency, a1, a2, a3),
                          [](gp::Triangle &self, const py::object &value) {
                              if (py::isinstance<py::tuple>(value)) {
                                  py::tuple object = value;
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
