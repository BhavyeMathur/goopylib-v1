#include <map-macro/map.h>

#include "goopylib/header.h"
#include "scene/Camera.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(camera, m) {
    py::class_<gp::CameraFrame>(m, "CameraFrame")
            .def(py::init<float, float, float, float>());

    py::class_<gp::CameraFrameSize>(m, "CameraFrameSize")
            .def(py::init<float, float>());

    py::class_<gp::Camera>(m, "Camera")
            .def(py::init<float, float, float, float>(), "left"_a, "right"_a, "bottom"_a, "top"_a)

            .def("set_projection", &gp::Camera::setProjection, "left"_a, "right"_a, "bottom"_a, "top"_a)
            .def("get_visible_frame", &gp::Camera::getVisibleFrame)
            .def("get_projection_frame", &gp::Camera::getProjectionFrame)

            .def("get_visible_width", &gp::Camera::getVisibleWidth)
            .def("get_visible_height", &gp::Camera::getVisibleHeight)
            .def("get_projection_width", &gp::Camera::getProjectionWidth)
            .def("get_projection_height", &gp::Camera::getProjectionHeight)

            .def("get_visible_size", &gp::Camera::getVisibleSize)
            .def("get_projection_size", &gp::Camera::getProjectionSize)

            .def("move", &gp::Camera::move)
            .def("rotate", &gp::Camera::rotate)
            .def("zoomin", &gp::Camera::zoom)

            .def_property("x", &gp::Camera::getX, &gp::Camera::setX)
            .def_property("y", &gp::Camera::getY, &gp::Camera::setY)
            .def_property("position", GP_GET_STRUCT_TUPLE(gp::Camera, Position, x, y),
                          [](gp::Camera &self, const py::tuple &object) {
                              GP_GET_ELEMENT_FROM_TUPLE(0, int);
                              GP_GET_ELEMENT_FROM_TUPLE(1, int);
                              self.setPosition(value0, value1);
                          })
            .def_property("rotation", &gp::Camera::getRotation, &gp::Camera::setRotation)
            .def_property("zoom", &gp::Camera::getZoom, &gp::Camera::setZoom)
                          ;
}
