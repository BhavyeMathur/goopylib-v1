#include <pybind11/operators.h>
#include <map-macro/map.h>

#include "goopylib/header.h"

#include "color/Color.h"
#include "color/ColorRGB.h"
#include "color/ColorHex.h"
#include "color/ColorCMYK.h"
#include "color/ColorHSV.h"
#include "color/ColorHSL.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(color, m) {
    py::class_<gp::Color>(m, "Color")
            .def(py::init<std::string, float>(), "hexstring"_a, "alpha"_a = 1)
            .def(py::init<int, int, int, float>(), "red"_a, "green"_a, "blue"_a, "alpha"_a = 1)
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

            .def_property_readonly("rgbaf", GP_GET_STRUCT_TUPLE(gp::Color, RGBAf, red, green, blue, alpha))
            .def_property_readonly("rgbf", GP_GET_STRUCT_TUPLE(gp::Color, RGBAf, red, green, blue));


    py::class_<gp::ColorRGB, gp::Color>(m, "ColorRGB")
            .def(py::init<int, int, int, float>(), "red"_a, "green"_a, "blue"_a, "alpha"_a = 1)
            .def(py::init<gp::Color>());

    gp::ColorRGB (gp::ColorHex::*HextoRGB)() const = &gp::ColorHex::toRGB;
    gp::ColorRGB (gp::ColorCMYK::*CMYKtoRGB)() const = &gp::ColorCMYK::toRGB;
    gp::ColorRGB (gp::ColorHSL::*HSLtoRGB)() const = &gp::ColorHSL::toRGB;
    gp::ColorRGB (gp::ColorHSV::*HSVtoRGB)() const = &gp::ColorHSV::toRGB;

    py::class_<gp::ColorHex, gp::Color>(m, "ColorHex")
            .def(py::init<std::string, float>(), "hexstring"_a, "alpha"_a = 1)
            .def(py::init<gp::Color>())
            .def("__repr__", &gp::ColorHex::toString)

            .def("to_rgb", HextoRGB);

    py::class_<gp::ColorCMYK, gp::Color>(m, "ColorCMYK")
            .def(py::init<float, float, float, float, float>(), "cyan"_a, "magenta"_a, "yellow"_a, "key"_a,
                 "alpha"_a = 1)
            .def(py::init<gp::Color>())
            .def("__repr__", &gp::ColorCMYK::toString)

            .def_property("cyan", &gp::ColorCMYK::getCyan, &gp::ColorCMYK::setCyan)
            .def_property("magenta", &gp::ColorCMYK::getMagenta, &gp::ColorCMYK::setMagenta)
            .def_property("yellow", &gp::ColorCMYK::getYellow, &gp::ColorCMYK::setYellow)
            .def_property("key", &gp::ColorCMYK::getKey, &gp::ColorCMYK::setKey)

            .def("to_rgb", CMYKtoRGB);

    py::class_<gp::ColorHSL, gp::Color>(m, "ColorHSL")
            .def(py::init<float, float, float, float>(), "hue"_a, "saturation"_a, "luminance"_a, "alpha"_a = 1)
            .def(py::init<gp::Color>())
            .def("__repr__", &gp::ColorHSL::toString)

            .def_property("hue", &gp::ColorHSL::getHue, &gp::ColorHSL::setHue)
            .def_property("saturation", &gp::ColorHSL::getSaturation, &gp::ColorHSL::setSaturation)
            .def_property("luminance", &gp::ColorHSL::getLuminance, &gp::ColorHSL::setLuminance)

            .def("to_rgb", HSLtoRGB)
            .def("to_hsv", &gp::ColorHSL::toHSV);

    py::class_<gp::ColorHSV, gp::Color>(m, "ColorHSV")
            .def(py::init<float, float, float, float>(), "hue"_a, "saturation"_a, "value"_a, "alpha"_a = 1)
            .def(py::init<gp::Color>())
            .def("__repr__", &gp::ColorHSV::toString)

            .def_property("hue", &gp::ColorHSV::getHue, &gp::ColorHSV::setHue)
            .def_property("saturation", &gp::ColorHSV::getSaturation, &gp::ColorHSV::setSaturation)
            .def_property("value", &gp::ColorHSV::getValue, &gp::ColorHSV::setValue)

            .def("to_rgb", HSVtoRGB)
            .def("to_hsl", &gp::ColorHSV::toHSL);
}
