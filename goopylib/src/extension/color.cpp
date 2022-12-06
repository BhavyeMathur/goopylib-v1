#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "pch.h"
#include "util.h"
#include <goopylib/Renderer/Color.h>

#if GP_ERROR_CHECKING
#define PARSE_RGB \
int red, green, blue; \
if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) { \
    return nullptr; \
} \
if (red < 0 || red > 255) { \
    RAISE_VALUE_ERROR(nullptr, "RGB red value must be between 0 and 255") \
} \
if (green < 0 || green > 255) {                                             \
    RAISE_VALUE_ERROR(nullptr, "RGB green value must be between 0 and 255") \
} \
if (blue < 0 || blue > 255) {                                               \
    RAISE_VALUE_ERROR(nullptr, "RGB blue value must be between 0 and 255")  \
}
#else
#define CHECK_RGB \
int red, green, blue; \
if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) { \
    return nullptr; \
}
#endif

#define PARSE_HEX \
PyObject *hexobject; \
if (!PyArg_ParseTuple(args, "O", &hexobject)) { \
return nullptr; \
} \
const char *hexstring = PyUnicode_AsUTF8(hexobject);

#if GP_ERROR_CHECKING
#define PARSE_CMYK \
float cyan, magenta, yellow, key; \
if (!PyArg_ParseTuple(args, "ffff", &cyan, &magenta, &yellow, &key)) { \
    return nullptr; \
} \
if (cyan < 0 || cyan > 1) { \
    RAISE_VALUE_ERROR(nullptr, "CMYK cyan value must be between 0 and 1") \
} \
if (magenta < 0 || magenta > 1) { \
    RAISE_VALUE_ERROR(nullptr, "CMYK magenta value must be between 0 and 1") \
} \
if (yellow < 0 || yellow > 1) { \
    RAISE_VALUE_ERROR(nullptr, "CMYK yellow value must be between 0 and 1") \
} \
if (key < 0 || key > 1) { \
    RAISE_VALUE_ERROR(nullptr, "CMYK key value must be between 0 and 1") \
}
#else
#define CHECK_CMYK \
float cyan, magenta, yellow, key; \
if (!PyArg_ParseTuple(args, "ffff", &cyan, &magenta, &yellow, &key)) { \
    return nullptr; \
}
#endif

#if GP_ERROR_CHECKING
#define PARSE_HSV_HSL(letter, value) \
int hue; \
float saturation, value; \
if (!PyArg_ParseTuple(args, "iff", &hue, &saturation, &value)) { \
    return nullptr; \
} \
if (hue < 0 || hue > 360) { \
    RAISE_VALUE_ERROR(nullptr, "HS" letter " hue must be between 0 and 360") \
} \
if (saturation < 0 || saturation > 1) { \
    RAISE_VALUE_ERROR(nullptr, "HS" letter " saturation must be between 0 and 1") \
} \
if (value < 0 || value > 1) { \
    RAISE_VALUE_ERROR(nullptr, "HS" letter " " #value " must be between 0 and 1") \
}
#else
#define PARSE_HSV_HSL(letter, fullform) \
int hue; \
float saturation, value; \
if (!PyArg_ParseTuple(args, "iff", &hue, &saturation, &value)) { \
    return nullptr; \
}
#endif

#define PARSE_HSV PARSE_HSV_HSL("V", value)
#define PARSE_HSL PARSE_HSV_HSL("L", luminance)

namespace color {

    // RGB to other format

    static PyObject *rgb_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        return Py_BuildValue("s", gp::rgb::toHex(red, green, blue));
    }

    static PyObject *rgb_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::ColorCMYK color_cmyk = gp::rgb::toCMYK(red, green, blue);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *rgb_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::ColorHSV color_hsv = gp::rgb::toHSV(red, green, blue);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    static PyObject *rgb_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::ColorHSL color_hsl = gp::rgb::toHSL(red, green, blue);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // Hex to other format

    static PyObject *hex_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::ColorRGB color_rgb = gp::hex::toRGB(hexstring);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *hex_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::ColorCMYK color_cmyk = gp::hex::toCMYK(hexstring);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *hex_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::ColorHSL color_hsl = gp::hex::toHSL(hexstring);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    static PyObject *hex_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::ColorHSV color_hsv = gp::hex::toHSV(hexstring);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    // CMYK to other format

    static PyObject *cmyk_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::ColorRGB color_rgb = gp::cmyk::toRGB(cyan, magenta, yellow, key);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *cmyk_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        return Py_BuildValue("s", gp::cmyk::toHex(cyan, magenta, yellow, key));
    }

    static PyObject *cmyk_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::ColorHSV color_hsv = gp::cmyk::toHSV(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    static PyObject *cmyk_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::ColorHSL color_hsl = gp::cmyk::toHSL(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSV to other format

    static PyObject *hsv_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::ColorRGB color_rgb = gp::hsv::toRGB(hue, saturation, value);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *hsv_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        return Py_BuildValue("s", gp::hsv::toHex(hue, saturation, value));
    }

    static PyObject *hsv_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::ColorCMYK color_cmyk = gp::hsv::toCMYK(hue, saturation, value);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *hsv_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::ColorHSL color_hsl = gp::hsv::toHSL(hue, saturation, value);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSL to other format

    static PyObject *hsl_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::ColorRGB color_rgb = gp::hsl::toRGB(hue, saturation, luminance);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    static PyObject *hsl_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        return Py_BuildValue("s", gp::hsl::toHex(hue, saturation, luminance));
    }

    static PyObject *hsl_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::ColorCMYK color_cmyk = gp::hsl::toCMYK(hue, saturation, luminance);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    static PyObject *hsl_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::ColorHSV color_hsv = gp::hsl::toHSV(hue, saturation, luminance);

        return Py_BuildValue("ifff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }
}

static PyMethodDef ColorMethods[] = {

        // RGB to other format functions

        {"rgb_to_hex",  (PyCFunction) color::rgb_to_hex,  METH_VARARGS,
                "rgb_to_hex(int r, int g, int b) -> string '#rrggbb'\nConverts RGB values to a hex string"},

        {"rgb_to_cmyk", (PyCFunction) color::rgb_to_cmyk, METH_VARARGS,
                "rgb_to_cmyk(int r, int g, int b) -> tuple (float c, float m, float y, float k)\nConverts RGB values to CMYK"},

        {"rgb_to_hsl",  (PyCFunction) color::rgb_to_hsl,  METH_VARARGS,
                "rgb_to_hsl(int r, int g, int b) -> tuple (int h, float s, float l)\nConverts RGB values to HSL"},

        {"rgb_to_hsv",  (PyCFunction) color::rgb_to_hsv,  METH_VARARGS,
                "rgb_to_hsv(int r, int g, int b) -> tuple (int h, float s, float v)\nConverts RGB values to HSV"},

        // Hex to other format functions

        {"hex_to_rgb",  (PyCFunction) color::hex_to_rgb,  METH_VARARGS,
                "hex_to_rgb(string hexstring) -> tuple (int r, int g, int b)\nConverts Hex colour values to RGB"},

        {"hex_to_cmyk", (PyCFunction) color::hex_to_cmyk, METH_VARARGS,
                "hex_to_cmyk(string hexstring) -> tuple (float c, float m, float y, float k)\nConverts Hex colour values to CMYK "
                "represented as a tuple"},


        {"hex_to_hsl",  (PyCFunction) color::hex_to_hsl,  METH_VARARGS,
                "hex_to_hsl(string hexstring) -> tuple (int h, float s, float l)\nConverts Hex colour values to HSL"},

        {"hex_to_hsv",  (PyCFunction) color::hex_to_hsv,  METH_VARARGS,
                "hex_to_hsv(string hexstring) -> tuple (int h, float s, float v)\nConverts Hex colour values to HSV"},

        // CMYK to other format functions

        {"cmyk_to_rgb", (PyCFunction) color::cmyk_to_rgb, METH_VARARGS,
                "cmyk_to_rgb(float c, float m, float y, float k) -> tuple (int r, int g, int b)\nConverts CMYK values to RGB"},

        {"cmyk_to_hex", (PyCFunction) color::cmyk_to_hex, METH_VARARGS,
                "cmyk_to_hex(float c, float m, float y, float k) -> string '#rrggbb'\nConverts CMYK values to a hex string"},

        {"cmyk_to_hsl", (PyCFunction) color::cmyk_to_hsl, METH_VARARGS,
                "cmyk_to_hsl(float c, float m, float y, float k) -> tuple (int h, float s, float l)\nConverts CMYK values to HSL"},

        {"cmyk_to_hsv", (PyCFunction) color::cmyk_to_hsv, METH_VARARGS,
                "cmyk_to_hsv(float c, float m, float y, float k) -> tuple (int h, float s, float v)\nConverts CMYK values to HSV"},

        // HSV to other format functions

        {"hsv_to_rgb",  (PyCFunction) color::hsv_to_rgb,  METH_VARARGS,
                "hsv_to_rgb(int h, float s, float v) -> tuple (int r, int g, int b)\nConverts HSV values to RGB"},

        {"hsv_to_hex",  (PyCFunction) color::hsv_to_hex,  METH_VARARGS,
                "hsv_to_hex(int h, float s, float v) -> string '#rrggbb'\nConverts HSV values to a hex string"},

        {"hsv_to_cmyk", (PyCFunction) color::hsv_to_cmyk, METH_VARARGS,
                "hsv_to_cmyk(int h, float s, float v) -> tuple (float c, float m, float y, float k)\nConverts HSV values to CMYK"},

        {"hsv_to_hsl",  (PyCFunction) color::hsv_to_hsl,  METH_VARARGS,
                "hsv_to_hsl(int h, float s, float v) -> tuple (int h, float s, float l)\nConverts HSV values to HSL"},

        // HSL to other format functions

        {"hsl_to_rgb",  (PyCFunction) color::hsl_to_rgb,  METH_VARARGS,
                "hsl_to_rgb(int h, float s, float l) -> tuple (int r, int g, int b)\nConverts HSL values to RGB"},

        {"hsl_to_hex",  (PyCFunction) color::hsl_to_hex,  METH_VARARGS,
                "hsl_to_hex(int h, float s, float l) -> string '#rrggbb'\nConverts HSL values to a hex string"},

        {"hsl_to_cmyk", (PyCFunction) color::hsl_to_cmyk, METH_VARARGS,
                "hsl_to_cmyk(int h, float s, float l) -> tuple (float c, float m, float y, float k)\nConverts HSL values to CMYK"},

        {"hsl_to_hsv",  (PyCFunction) color::hsl_to_hsv,  METH_VARARGS,
                "hsl_to_hsv(int h, float s, float l) -> tuple (int h, float s, float v)\nConverts HSL values to HSV"},

        {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef colormodule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "color",
        .m_size = -1,
        .m_methods = ColorMethods,
};

PyMODINIT_FUNC PyInit_color(void) {
    PyObject *m;
    m = PyModule_Create(&colormodule);
    if (m == nullptr) { return nullptr; }

    return m;
}
