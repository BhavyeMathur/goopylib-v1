#pragma once

#include <Python.h>
#include <pybind11/pybind11.h>

#define PYOBJ py::object &
#define CONST_PYOBJ const PYOBJ

#define GP_RETHROW_ERROR(code, error, msg) try { code; } catch (std::runtime_error &e) { throw py::error(msg); };
#define GP_RETHROW_TYPE_ERROR(code, type) GP_RETHROW_ERROR(code, type_error, "Expected " #type " argument")
#define GP_RETHROW_TYPE_ERROR_POSITION(code, type, pos) GP_RETHROW_ERROR(code, type_error, "Expected " #type " argument in position " #pos)

#define _GP_VALUE_ATTR(attr) value.attr
#define _GP_GET_STRUCT_TUPLE(func, ...) auto value = self.get##func(); return py::make_tuple(MAP_LIST(_GP_VALUE_ATTR, __VA_ARGS__))
#define GP_GET_STRUCT_TUPLE(cls, func, ...) [](const cls &self) { _GP_GET_STRUCT_TUPLE(func, __VA_ARGS__); }

#define GP_GET_ELEMENT_FROM_TUPLE(el, type) type value##el; GP_RETHROW_TYPE_ERROR_POSITION(value##el = object[el].cast<type>(), type, el)

#define _GP_POINT_GETTER(cls, n) GP_GET_STRUCT_TUPLE(cls, P##n, x, y)
#define _GP_SET_POINT(n) GP_GET_ELEMENT_FROM_TUPLE(0, float); GP_GET_ELEMENT_FROM_TUPLE(1, float); self.setP##n({value0, value1})
#define _GP_POINT_SETTER(cls, n) [](cls &self, const py::tuple &object) { _GP_SET_POINT(n); }
#define GP_POINT_PROPERTY(cls, n) .def_property("p" #n, _GP_POINT_GETTER(cls, n), _GP_POINT_SETTER(cls, n))

#define _GP_POINT_TO_FLOATS(n) x##n = p##n[0].cast<float>(); y##n = p##n[1].cast<float>()
#define GP_POINT_TO_FLOATS(n) float x##n, y##n; GP_RETHROW_ERROR(_GP_POINT_TO_FLOATS(n), type_error, "Point must be a tuple of (x: float, y: float)")
#define GP_PARSE_POINT(n) GP_POINT_TO_FLOATS(n); Point v##n{x##n, y##n};
#define GP_PARSE_POINTS(...) MAP(GP_PARSE_POINT, __VA_ARGS__)

#define GP_TO_COLOR(v) if (!py::isinstance(v, Color)) { v = py::isinstance<py::tuple>(v) ? Color(*v) : Color(v); }
#define _GP_COLOR_PREFIX(n) color##n
#define _GP_COLOR_SETTER_ARGS(cls, ...) cls &self, MAP_LIST(PYOBJ, MAP_LIST(_GP_COLOR_PREFIX, __VA_ARGS__))
#define _GP_COLOR_CAST(n) _GP_COLOR_PREFIX(n).cast<gp::Color>()
#define _GP_COLOR_SETTER(cls, ...) MAP(GP_TO_COLOR, MAP_LIST(_GP_COLOR_PREFIX, __VA_ARGS__)) self.setColor(MAP_LIST(_GP_COLOR_CAST, __VA_ARGS__))
#define GP_COLOR_SETTER(cls, ...) [Color](_GP_COLOR_SETTER_ARGS(cls, __VA_ARGS__)) { _GP_COLOR_SETTER(cls, __VA_ARGS__); }

#define _GP_COLOR_SETTER1(cls) .def("set_color", static_cast<void (cls::*)(const gp::Color &)>(&cls::setColor))
#define _GP_COLOR_SETTER2(cls) .def("set_color", static_cast<void (cls::*)(const char *, float)>(&cls::setColor), "color"_a, "alpha"_a=1)
#define _GP_COLOR_SETTER3(cls) .def("set_color", static_cast<void (cls::*)(int, int, int, float)>(&cls::setColor), "red"_a, "green"_a, "blue"_a, "alpha"_a=1)
#define _GP_COLOR_SETTER4(cls, ...) .def("set_color", GP_COLOR_SETTER(cls, __VA_ARGS__))
#define GP_COLOR_SETTERS(cls, ...) _GP_COLOR_SETTER1(cls) _GP_COLOR_SETTER2(cls) _GP_COLOR_SETTER3(cls) _GP_COLOR_SETTER4(cls, __VA_ARGS__)
