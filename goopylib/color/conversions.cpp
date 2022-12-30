#include "conversions.h"
#include "goopylib/color/ColorConversions.h"

#include "config.h"

#if (GP_LOG_COLOR_CONVERSIONS != true) and (GP_LOG_COLOR_CONVERSIONS <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_COLOR_CONVERSIONS
#endif

#if !GP_VALUE_CHECK_COLOR_CONVERSIONS
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "debug.h"
#include "macros.h"

namespace color {

    // RGB to other format

    PyObject *rgb_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.rgb_to_hex({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_RGB

        return PyUnicode_FromString(gp::rgb::toHex(red, green, blue));
    }

    PyObject *rgb_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.rgb_to_cmyk({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_RGB

        gp::CMYK color_cmyk = gp::rgb::toCMYK(red, green, blue);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *rgb_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.rgb_to_hsv({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_RGB

        gp::HSV color_hsv = gp::rgb::toHSV(red, green, blue);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    PyObject *rgb_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.rgb_to_hsl({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_RGB

        gp::HSL color_hsl = gp::rgb::toHSL(red, green, blue);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // Hex to other format

    PyObject *hex_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hex_to_rgb({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HEX

        gp::RGB color_rgb = gp::hex::toRGB(hexstring);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *hex_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hex_to_cmyk({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HEX

        gp::CMYK color_cmyk = gp::hex::toCMYK(hexstring);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *hex_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hex_to_hsl({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HEX

        gp::HSL color_hsl = gp::hex::toHSL(hexstring);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    PyObject *hex_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hex_to_hsv({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HEX

        gp::HSV color_hsv = gp::hex::toHSV(hexstring);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    // CMYK to other format

    PyObject *cmyk_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.cmyk_to_rgb({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_CMYK

        gp::RGB color_rgb = gp::cmyk::toRGB(cyan, magenta, yellow, key);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *cmyk_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.cmyk_to_hex({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_CMYK

        return PyUnicode_FromString(gp::cmyk::toHex(cyan, magenta, yellow, key));
    }

    PyObject *cmyk_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.cmyk_to_hsv({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_CMYK

        gp::HSV color_hsv = gp::cmyk::toHSV(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    PyObject *cmyk_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.cmyk_to_hsl({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_CMYK

        gp::HSL color_hsl = gp::cmyk::toHSL(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSV to other format

    PyObject *hsv_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsv_to_rgb({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSV

        gp::RGB color_rgb = gp::hsv::toRGB(hue, saturation, value);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *hsv_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsv_to_hex({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSV

        return PyUnicode_FromString(gp::hsv::toHex(hue, saturation, value));
    }

    PyObject *hsv_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsv_to_cmyk({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSV

        gp::CMYK color_cmyk = gp::hsv::toCMYK(hue, saturation, value);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *hsv_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsv_to_hsl({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSV

        gp::HSL color_hsl = gp::hsv::toHSL(hue, saturation, value);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSL to other format

    PyObject *hsl_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsl_to_rgb({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSL

        gp::RGB color_rgb = gp::hsl::toRGB(hue, saturation, luminance);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *hsl_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsl_to_hex({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSL

        return PyUnicode_FromString(gp::hsl::toHex(hue, saturation, luminance));
    }

    PyObject *hsl_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsl_to_cmyk({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSL

        gp::CMYK color_cmyk = gp::hsl::toCMYK(hue, saturation, luminance);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *hsl_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        GP_PY_INFO("gp.color_conversions.hsl_to_hsv({0})", PyUnicode_AsUTF8(PyObject_Repr(args)));

        PARSE_HSL

        gp::HSV color_hsv = gp::hsl::toHSV(hue, saturation, luminance);

        return Py_BuildValue("ifff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }
}

static PyMethodDef ColorConversionMethods[] = {

        // RGB to other format functions

        {"rgb_to_hex",  (PyCFunction) color::rgb_to_hex,  METH_VARARGS,
                                    "rgb_to_hex(int r, int g, int b) -> str '#rrggbb'\nConverts RGB values to a hex string"},

        {"rgb_to_cmyk", (PyCFunction) color::rgb_to_cmyk, METH_VARARGS,
                                    "rgb_to_cmyk(int r, int g, int b) -> tuple (float c, float m, float y, float k)\nConverts RGB values to CMYK"},

        {"rgb_to_hsl",  (PyCFunction) color::rgb_to_hsl,  METH_VARARGS,
                                    "rgb_to_hsl(int r, int g, int b) -> tuple (int h, float s, float l)\nConverts RGB values to HSL"},

        {"rgb_to_hsv",  (PyCFunction) color::rgb_to_hsv,  METH_VARARGS,
                                    "rgb_to_hsv(int r, int g, int b) -> tuple (int h, float s, float v)\nConverts RGB values to HSV"},

        // Hex to other format functions

        {"hex_to_rgb",  (PyCFunction) color::hex_to_rgb,  METH_VARARGS,
                                    "hex_to_rgb(str hexstring) -> tuple (int r, int g, int b)\nConverts Hex colour values to RGB"},

        {"hex_to_cmyk", (PyCFunction) color::hex_to_cmyk, METH_VARARGS,
                                    "hex_to_cmyk(str hexstring) -> tuple (float c, float m, float y, float k)\nConverts Hex colour values to CMYK "
                                    "represented as a tuple"},


        {"hex_to_hsl",  (PyCFunction) color::hex_to_hsl,  METH_VARARGS,
                                    "hex_to_hsl(str hexstring) -> tuple (int h, float s, float l)\nConverts Hex colour values to HSL"},

        {"hex_to_hsv",  (PyCFunction) color::hex_to_hsv,  METH_VARARGS,
                                    "hex_to_hsv(str hexstring) -> tuple (int h, float s, float v)\nConverts Hex colour values to HSV"},

        // CMYK to other format functions

        {"cmyk_to_rgb", (PyCFunction) color::cmyk_to_rgb, METH_VARARGS,
                                    "cmyk_to_rgb(float c, float m, float y, float k) -> tuple (int r, int g, int b)\nConverts CMYK values to RGB"},

        {"cmyk_to_hex", (PyCFunction) color::cmyk_to_hex, METH_VARARGS,
                                    "cmyk_to_hex(float c, float m, float y, float k) -> str '#rrggbb'\nConverts CMYK values to a hex string"},

        {"cmyk_to_hsl", (PyCFunction) color::cmyk_to_hsl, METH_VARARGS,
                                    "cmyk_to_hsl(float c, float m, float y, float k) -> tuple (int h, float s, float l)\nConverts CMYK values to HSL"},

        {"cmyk_to_hsv", (PyCFunction) color::cmyk_to_hsv, METH_VARARGS,
                                    "cmyk_to_hsv(float c, float m, float y, float k) -> tuple (int h, float s, float v)\nConverts CMYK values to HSV"},

        // HSV to other format functions

        {"hsv_to_rgb",  (PyCFunction) color::hsv_to_rgb,  METH_VARARGS,
                                    "hsv_to_rgb(int h, float s, float v) -> tuple (int r, int g, int b)\nConverts HSV values to RGB"},

        {"hsv_to_hex",  (PyCFunction) color::hsv_to_hex,  METH_VARARGS,
                                    "hsv_to_hex(int h, float s, float v) -> str '#rrggbb'\nConverts HSV values to a hex string"},

        {"hsv_to_cmyk", (PyCFunction) color::hsv_to_cmyk, METH_VARARGS,
                                    "hsv_to_cmyk(int h, float s, float v) -> tuple (float c, float m, float y, float k)\nConverts HSV values to CMYK"},

        {"hsv_to_hsl",  (PyCFunction) color::hsv_to_hsl,  METH_VARARGS,
                                    "hsv_to_hsl(int h, float s, float v) -> tuple (int h, float s, float l)\nConverts HSV values to HSL"},

        // HSL to other format functions

        {"hsl_to_rgb",  (PyCFunction) color::hsl_to_rgb,  METH_VARARGS,
                                    "hsl_to_rgb(int h, float s, float l) -> tuple (int r, int g, int b)\nConverts HSL values to RGB"},

        {"hsl_to_hex",  (PyCFunction) color::hsl_to_hex,  METH_VARARGS,
                                    "hsl_to_hex(int h, float s, float l) -> str '#rrggbb'\nConverts HSL values to a hex string"},

        {"hsl_to_cmyk", (PyCFunction) color::hsl_to_cmyk, METH_VARARGS,
                                    "hsl_to_cmyk(int h, float s, float l) -> tuple (float c, float m, float y, float k)\nConverts HSL values to CMYK"},

        {"hsl_to_hsv",  (PyCFunction) color::hsl_to_hsv,  METH_VARARGS,
                                    "hsl_to_hsv(int h, float s, float l) -> tuple (int h, float s, float v)\nConverts HSL values to HSV"},

        {nullptr,       nullptr, 0, nullptr}

};

static struct PyModuleDef ColorConversionsModule = {
        PyModuleDef_HEAD_INIT,
        .m_name = "conversions",
        .m_size = -1,
        .m_methods = ColorConversionMethods,
};


PyMODINIT_FUNC PyInit_color_conversions() {
    #if GP_LOGGING_LEVEL >= 5
    std::cout << "[--:--:--] PYTHON: PyInit_color_conversions()" << std::endl;
    #endif

    PyObject *m;
    m = PyModule_Create(&ColorConversionsModule);
    if (m == nullptr) {
        return nullptr;
    }

    return m;
}
