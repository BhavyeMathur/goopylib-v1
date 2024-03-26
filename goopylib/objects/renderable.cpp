#include <map-macro/map.h>
#include <pybind11/pybind11.h>

#include "goopylib/header.h"
#include "objects/Renderable.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(renderable, m) {
    auto windowModule = py::module_::import("goopylib.core");
    py::object Window = windowModule.attr("Window");

    py::class_<gp::Renderable>(m, "Renderable")
            .def("__repr__", &gp::Renderable::toString)

            .def("draw", &gp::Renderable::draw)
            .def("destroy", &gp::Renderable::destroy)
            .def("is_drawn", &gp::Renderable::isDrawn)

            .def("set_anchor", &gp::Renderable::setAnchor)
            .def("reset_anchor", &gp::Renderable::resetAnchor)

            .def("move", &gp::Renderable::move)
            .def("rotate", &gp::Renderable::rotate)

            .def("scale", static_cast<void (gp::Renderable::*)(float)>(&gp::Renderable::scale))
            .def("scale", static_cast<void (gp::Renderable::*)(float, float)>(&gp::Renderable::scale))
            .def("set_size", &gp::Renderable::setSize)

            .def("hide", &gp::Renderable::hide)
            .def("show", &gp::Renderable::show)
            .def("is_hidden", &gp::Renderable::isHidden)
            .def("is_opaque", &gp::Renderable::isOpaque)

            .def("box_contains", static_cast<bool (gp::Renderable::*)(float, float) const>(&gp::Renderable::boxContains))
            .def("contains", static_cast<bool (gp::Renderable::*)(float, float) const>(&gp::Renderable::contains))

            .def_property("x", &gp::Renderable::getX, &gp::Renderable::setX)
            .def_property("y", &gp::Renderable::getY, &gp::Renderable::setY)
            .def_property("z", &gp::Renderable::getZ, &gp::Renderable::setZ)
            .def_property("position", GP_GET_STRUCT_TUPLE(gp::Renderable, Position, x, y),
                          [](gp::Renderable &self, const py::tuple &object) {
                              GP_GET_ELEMENT_FROM_TUPLE(0, int);
                              GP_GET_ELEMENT_FROM_TUPLE(1, int);
                              self.setPosition(value0, value1);
                          })
            .def_property("rotation", &gp::Renderable::getRotation, &gp::Renderable::setRotation)
            .def_property("scalex", [](gp::Renderable &self) {
                return self.getScale().xscale;
            }, &gp::Renderable::setScaleX)
            .def_property("scaley", [](gp::Renderable &self) {
                return self.getScale().yscale;
            }, &gp::Renderable::setScaleY)
            .def_property("width", &gp::Renderable::getWidth, &gp::Renderable::setWidth)
            .def_property("height", &gp::Renderable::getHeight, &gp::Renderable::setHeight);
}
