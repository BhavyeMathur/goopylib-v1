#include <map-macro/map.h>

#include "goopylib/header.h"
#include "objects/Renderable.h"

namespace py = pybind11;
using namespace pybind11::literals;

class PyRenderable : public gp::Renderable {

public:
    void setTransparency(float value) override {
        PYBIND11_OVERRIDE_PURE_NAME(
                void,                /* Return type */
                gp::Renderable,      /* Parent class */
                "set_transparency", setTransparency,
        );
    }

    bool isOpaque() const override {
        PYBIND11_OVERRIDE_PURE_NAME(
                bool,                /* Return type */
                gp::Renderable,      /* Parent class */
                "is_opaque", isOpaque,
        );
    }

private:
    bool _contains(float x, float y) const override {
        PYBIND11_OVERRIDE_PURE_NAME(
                bool,                /* Return type */
                gp::Renderable,      /* Parent class */
                "_contains", _contains,
        );
    }

    gp::RenderableSubclass _getRenderableSubclass() override {
        PYBIND11_OVERRIDE_PURE_NAME(
                gp::RenderableSubclass, /* Return type */
                gp::Renderable,         /* Parent class */
                "_get_renderable_subclass", _getRenderableSubclass,
        );
    };
};

PYBIND11_MODULE(renderable, m) {
    auto windowModule = py::module_::import("goopylib.core");
    py::object Window = windowModule.attr("Window");

    py::class_<gp::Renderable, PyRenderable>(m, "Renderable")
            .def(py::init())
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

            .def("box_contains",
                 static_cast<bool (gp::Renderable::*)(float, float) const>(&gp::Renderable::boxContains))
            .def("contains", static_cast<bool (gp::Renderable::*)(float, float) const>(&gp::Renderable::contains))

            .def_property("x", &gp::Renderable::getX, &gp::Renderable::setX)
            .def_property("y", &gp::Renderable::getY, &gp::Renderable::setY)
            .def_property("z", &gp::Renderable::getZ, &gp::Renderable::setZ)
            .def_property("position", GP_GET_STRUCT_TUPLE(gp::Renderable, Position, x, y),
                          [](gp::Renderable &self, const py::tuple &object) {
                              GP_GET_ELEMENT_FROM_TUPLE(0, float);
                              GP_GET_ELEMENT_FROM_TUPLE(1, float);
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
            .def_property("height", &gp::Renderable::getHeight, &gp::Renderable::setHeight)

            .def_property_readonly("window", &gp::Renderable::getWindow, py::return_value_policy::reference);
}
