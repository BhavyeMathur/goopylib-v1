#pragma once

#include "gp.h"

// TODO check if the < 0 error checking is still needed if the values are ints

#if GP_ERROR_CHECKING

#define CHECK_RED(val) \
if (red < 0 || red > 255) { \
    RAISE_VALUE_ERROR(val, "RGB red value must be between 0 and 255") \
}

#define CHECK_GREEN(val) \
if (green < 0 || green > 255) {                                             \
    RAISE_VALUE_ERROR(val, "RGB green value must be between 0 and 255") \
}

#define CHECK_BLUE(val) \
if (blue < 0 || blue > 255) {                                               \
    RAISE_VALUE_ERROR(val, "RGB blue value must be between 0 and 255")  \
}

#define CHECK_ALPHA(val) \
if (alpha < 0 || alpha > 1) {                                               \
    RAISE_VALUE_ERROR(val, "Color alpha value must be between 0 and 1")  \
}

#define CHECK_CYAN(val) \
if (cyan < 0 || cyan > 1) {                                               \
    RAISE_VALUE_ERROR(val, "CMYK cyan value must be between 0 and 1")  \
}

#define CHECK_MAGENTA(val) \
if (magenta < 0 || magenta > 1) {                                               \
    RAISE_VALUE_ERROR(val, "CMYK magenta value must be between 0 and 1")  \
}

#define CHECK_YELLOW(val) \
if (yellow < 0 || yellow > 1) {                                               \
    RAISE_VALUE_ERROR(val, "CMYK yellow value must be between 0 and 1")  \
}

#define CHECK_KEY(val) \
if (key < 0 || key > 1) {                                               \
    RAISE_VALUE_ERROR(val, "CMYK key value must be between 0 and 1")  \
}

#define CHECK_HUE(val) \
if (hue < 0 || hue > 360) {                                               \
    RAISE_VALUE_ERROR(val, "Color hue value must be between 0 and 360")  \
}

#define CHECK_SATURATION(val) \
if (saturation < 0 || saturation > 1) {                                               \
    RAISE_VALUE_ERROR(val, "Color saturation value must be between 0 and 1")  \
}

#define CHECK_VALUE(val) \
if (value < 0 || value > 1) {                                               \
    RAISE_VALUE_ERROR(val, "HSV value must be between 0 and 1")  \
}

#define CHECK_LUMINANCE(val) \
if (luminance < 0 || luminance > 1) {                                               \
    RAISE_VALUE_ERROR(val, "HSL luminance value must be between 0 and 1")  \
}

#define CHECK_RGB(val) CHECK_RED(val) CHECK_GREEN(val) CHECK_BLUE(val)
#define CHECK_RGBA(val) CHECK_RGB(val) CHECK_ALPHA(val)

#define CHECK_CMYK(val) CHECK_CYAN(val) CHECK_MAGENTA(val) CHECK_YELLOW(val) CHECK_KEY(val)
#define CHECK_CMYKA(val) CHECK_CMYK(val) CHECK_ALPHA(val)

#define CHECK_HSV(val) CHECK_HUE(val) CHECK_SATURATION(val) CHECK_VALUE(val)
#define CHECK_HSVA(val) CHECK_HSV(val) CHECK_ALPHA(val)

#define CHECK_HSL(val) CHECK_HUE(val) CHECK_SATURATION(val) CHECK_LUMINANCE(val)
#define CHECK_HSLA(val) CHECK_HSL(val) CHECK_ALPHA(val)

#else

#define CHECK_RED
#define CHECK_GREEN
#define CHECK_BLUE
#define CHECK_ALPHA

#define CHECK_CYAN
#define CHECK_MAGENTA
#define CHECK_YELLOW
#define CHECK_KEY

#define CHECK_HUE
#define CHECK_SATURATION
#define CHECK_VALUE
#define CHECK_LUMINANCE

#define CHECK_RGB(val)
#define CHECK_RGBA(val)

#define CHECK_CMYK(val)
#define CHECK_CMYKA(val)

#define CHECK_HSV(val)
#define CHECK_HSVA(val)

#define CHECK_HSL(val)
#define CHECK_HSLA(val)

#endif

#define PARSE_RGB \
int red, green, blue; \
if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) { \
    return nullptr; \
} \
CHECK_RGB(nullptr)

#define PARSE_CMYK \
float cyan, magenta, yellow, key; \
if (!PyArg_ParseTuple(args, "ffff", &cyan, &magenta, &yellow, &key)) { \
    return nullptr; \
} \
CHECK_CMYK(nullptr)

#define PARSE_HEX \
PyObject *hexobject; \
if (!PyArg_ParseTuple(args, "O", &hexobject)) { \
return nullptr; \
} \
const char *hexstring = PyUnicode_AsUTF8(hexobject);

#define PARSE_HSV \
int hue; \
float saturation, value; \
if (!PyArg_ParseTuple(args, "iff", &hue, &saturation, &value)) { \
    return nullptr; \
} \
CHECK_HSV(nullptr)

#define PARSE_HSL \
int hue; \
float saturation, luminance; \
if (!PyArg_ParseTuple(args, "iff", &hue, &saturation, &luminance)) { \
    return nullptr; \
} \
CHECK_HSL(nullptr)

#define PyColorObject_HEAD_INIT \
PyVarObject_HEAD_INIT(nullptr, 0) \
.tp_itemsize = 0, \
.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC, \
.tp_new = PyType_GenericNew, \
.tp_repr = (reprfunc) color::repr, \
.tp_traverse = (traverseproc) color::traverse, \
.tp_clear = (inquiry) color::clear, \
.tp_dealloc = (destructor) color::dealloc,
