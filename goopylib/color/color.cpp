#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "color/Color.h"
#include "color/ColorRGB.h"
#include "color/ColorHex.h"
#include "color/ColorCMYK.h"
#include "color/ColorHSV.h"
#include "color/ColorHSL.h"

namespace py = pybind11;

PYBIND11_MODULE(color, m) {
    py::class_<gp::Color>(m, "Color")
            .def(py::init<std::string>())
            .def(py::init<std::string, float>())
            .def(py::init<int, int, int>())
            .def(py::init<int, int, int, float>())
            .def(py::init<int, int, int, float>())
            .def(py::init<gp::Color>())
            .def("__repr__", &gp::Color::toString)

            .def(py::self + py::self)
            .def(py::self - py::self)
            .def(py::self += py::self)
            .def(py::self -= py::self)

            .def(py::self + float())
            .def(py::self - float())
            .def(py::self += float())
            .def(py::self -= float())

            .def(py::self == py::self)

            .def("to_rgb", &gp::Color::toRGB)
            .def("to_hex", &gp::Color::toHex)
            .def("to_cmyk", &gp::Color::toCMYK)
            .def("to_hsl", &gp::Color::toHSL)
            .def("to_hsv", &gp::Color::toHSV)

            .def_property("red", &gp::Color::getRed, &gp::Color::setRed)
            .def_property("green", &gp::Color::getGreen, &gp::Color::setGreen)
            .def_property("blue", &gp::Color::getBlue, &gp::Color::setBlue)
            .def_property("alpha", &gp::Color::getAlpha, &gp::Color::setAlpha)
            .def_property_readonly("redf", &gp::Color::getRedf)
            .def_property_readonly("greenf", &gp::Color::getGreenf)
            .def_property_readonly("bluef", &gp::Color::getBluef)
            .def_property_readonly("rgbaf", &gp::Color::getRGBAf)
            ;

    py::class_<gp::ColorRGB, gp::Color>(m, "ColorRGB");

    py::class_<gp::ColorHex, gp::Color>(m, "ColorHex");

    py::class_<gp::ColorCMYK, gp::Color>(m, "ColorCMYK");

    py::class_<gp::ColorHSL, gp::Color>(m, "ColorHSL");

    py::class_<gp::ColorHSV, gp::Color>(m, "ColorHSV");
}
