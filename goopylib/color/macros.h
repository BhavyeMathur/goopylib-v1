#pragma once

#define CHECK_RED(val) GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, val, "Color red value must be between 0 and 255")
#define CHECK_GREEN(val) GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, val, "Color green value must be between 0 and 255")
#define CHECK_BLUE(val) GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, val, "Color blue value must be between 0 and 255")
#define CHECK_ALPHA(val) GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, val, "Color alpha value must be between 0 and 1")

#define CHECK_CYAN(val) GP_CHECK_INCLUSIVE_RANGE(cyan, 0, 1, val, "Color cyan value must be between 0 and 1")
#define CHECK_MAGENTA(val) GP_CHECK_INCLUSIVE_RANGE(magenta, 0, 1, val, "Color magenta value must be between 0 and 1")
#define CHECK_YELLOW(val) GP_CHECK_INCLUSIVE_RANGE(yellow, 0, 1, val, "Color yellow value must be between 0 and 1")
#define CHECK_KEY(val) GP_CHECK_INCLUSIVE_RANGE(key, 0, 1, val, "Color key value must be between 0 and 1")

#define CHECK_HUE(val) GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, val, "Color hue value must be between 0 and 360")
#define CHECK_SATURATION(val) GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, val, "Color saturation value must be between 0 and 1")
#define CHECK_VALUE(val) GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, val, "Color 'value' value must be between 0 and 1")
#define CHECK_LUMINANCE(val) GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, val, "Color luminance value must be between 0 and 1")

#define CHECK_RGB(val) CHECK_RED(val) CHECK_GREEN(val) CHECK_BLUE(val)
#define CHECK_RGBA(val) CHECK_RGB(val) CHECK_ALPHA(val)

#define CHECK_CMYK(val) CHECK_CYAN(val) CHECK_MAGENTA(val) CHECK_YELLOW(val) CHECK_KEY(val)
#define CHECK_CMYKA(val) CHECK_CMYK(val) CHECK_ALPHA(val)

#define CHECK_HSV(val) CHECK_HUE(val) CHECK_SATURATION(val) CHECK_VALUE(val)
#define CHECK_HSVA(val) CHECK_HSV(val) CHECK_ALPHA(val)

#define CHECK_HSL(val) CHECK_HUE(val) CHECK_SATURATION(val) CHECK_LUMINANCE(val)
#define CHECK_HSLA(val) CHECK_HSL(val) CHECK_ALPHA(val)

#define PARSE_RGB \
int red, green, blue; \
if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) \
    return nullptr; \
CHECK_RGB(nullptr)

#define PARSE_CMYK \
float cyan, magenta, yellow, key; \
if (!PyArg_ParseTuple(args, "ffff", &cyan, &magenta, &yellow, &key)) \
    return nullptr; \
CHECK_CMYK(nullptr)

#define PARSE_HEX \
const char *hexstring; \
if (!PyArg_ParseTuple(args, "s", &hexstring)) \
    return nullptr;

#define PARSE_HSV \
int hue; \
float saturation, value; \
if (!PyArg_ParseTuple(args, "iff", &hue, &saturation, &value)) \
    return nullptr; \
CHECK_HSV(nullptr)

#define PARSE_HSL \
int hue; \
float saturation, luminance; \
if (!PyArg_ParseTuple(args, "iff", &hue, &saturation, &luminance)) \
    return nullptr; \
CHECK_HSL(nullptr)

#define ColorType(name, init, getset) \
static PyTypeObject name##Type = { \
    PyVarObject_HEAD_INIT(nullptr, 0) \
    "goopylib." #name, \
    sizeof(name##Object), \
    0, \
    (destructor) color::dealloc, \
    0, \
    nullptr, \
    nullptr, \
    nullptr, \
    (reprfunc) color::repr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC, \
    "", \
    (traverseproc) color::traverse, \
    (inquiry) color::clear, \
    nullptr, \
    0, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    (PyGetSetDef *) (getset),  \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    0, \
    (initproc) (init), \
    nullptr, \
    PyType_GenericNew, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    nullptr, \
    0, \
    nullptr, \
    nullptr \
}
