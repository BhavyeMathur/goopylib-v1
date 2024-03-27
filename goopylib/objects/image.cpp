#include <map-macro/map.h>

#include "goopylib/header.h"
#include "objects/Image.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(image, m) {
    py::class_<gp::Image, gp::Rectangle, gp::Quad, gp::Renderable>(m, "Image")
            .def(py::init([](const std::string& path, py::tuple p1) {
                GP_PARSE_POINTS(1);
                return new gp::Image(path, v1);
            }), "path"_a, "p1"_a)

            .def(py::init([](const std::string& path, py::tuple p1, float width, float height) {
                GP_PARSE_POINTS(1);
                return new gp::Image(path, v1, width, height);
            }), "path"_a, "p1"_a, "width"_a, "height"_a)

            .def(py::init([](const std::string& path, py::tuple p1, py::tuple p2) {
                GP_PARSE_POINTS(1, 2);
                return new gp::Image(path, v1, v2);
            }), "path"_a, "p1"_a, "p2"_a)

            .def("get_path", &gp::Image::getPath);
}
