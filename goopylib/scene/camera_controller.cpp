#include "goopylib/header.h"
#include "scene/CameraController.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(camera_controller, m) {
    py::class_<gp::CameraController>(m, "CameraController")
            .def(py::init<gp::Window *>(), "window"_a)
            .def("update", &gp::CameraController::update)

            .def("enable_movement", &gp::CameraController::enableMovement)
            .def("enable_rotation", &gp::CameraController::enableRotation)
            .def("enable_zoom", &gp::CameraController::enableZoom)
            .def("invert_movement", &gp::CameraController::invertMovement)
            .def("invert_rotation", &gp::CameraController::invertRotation)

            .def("use_wasd", &gp::CameraController::useWASD)
            .def("use_arrows", &gp::CameraController::useArrows)
            .def("set_movement_keys", &gp::CameraController::setMovementKeys)
            .def("set_rotation_keys", &gp::CameraController::setRotationKeys)
            .def("set_zoom_keys", &gp::CameraController::setZoomKeys)

            .def_property("horizontal_speed", &gp::CameraController::getHorizontalSpeed, &gp::CameraController::setHorizontalSpeed)
            .def_property("vertical_speed", &gp::CameraController::getVerticalSpeed, &gp::CameraController::setVerticalSpeed)
            .def_property("rotate_speed", &gp::CameraController::getRotateSpeed, &gp::CameraController::setRotateSpeed)
            .def_property("zoom_speed", &gp::CameraController::getZoomSpeed, &gp::CameraController::setZoomSpeed);
}
