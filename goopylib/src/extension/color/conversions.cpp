#include "conversions.h"

namespace color {

    // RGB to other format

    PyObject *rgb_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        return PyUnicode_FromString(gp::rgb::toHex(red, green, blue));
    }

    PyObject *rgb_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::CMYK color_cmyk = gp::rgb::toCMYK(red, green, blue);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *rgb_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::HSV color_hsv = gp::rgb::toHSV(red, green, blue);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    PyObject *rgb_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_RGB

        gp::HSL color_hsl = gp::rgb::toHSL(red, green, blue);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // Hex to other format

    PyObject *hex_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::RGB color_rgb = gp::hex::toRGB(hexstring);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *hex_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::CMYK color_cmyk = gp::hex::toCMYK(hexstring);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *hex_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::HSL color_hsl = gp::hex::toHSL(hexstring);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    PyObject *hex_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HEX

        gp::HSV color_hsv = gp::hex::toHSV(hexstring);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    // CMYK to other format

    PyObject *cmyk_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::RGB color_rgb = gp::cmyk::toRGB(cyan, magenta, yellow, key);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *cmyk_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        return PyUnicode_FromString(gp::cmyk::toHex(cyan, magenta, yellow, key));
    }

    PyObject *cmyk_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::HSV color_hsv = gp::cmyk::toHSV(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }

    PyObject *cmyk_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_CMYK

        gp::HSL color_hsl = gp::cmyk::toHSL(cyan, magenta, yellow, key);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSV to other format

    PyObject *hsv_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::RGB color_rgb = gp::hsv::toRGB(hue, saturation, value);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *hsv_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        return PyUnicode_FromString(gp::hsv::toHex(hue, saturation, value));
    }

    PyObject *hsv_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::CMYK color_cmyk = gp::hsv::toCMYK(hue, saturation, value);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *hsv_to_hsl(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSV

        gp::HSL color_hsl = gp::hsv::toHSL(hue, saturation, value);

        return Py_BuildValue("iff", color_hsl.hue, color_hsl.saturation, color_hsl.luminance);
    }

    // HSL to other format

    PyObject *hsl_to_rgb(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::RGB color_rgb = gp::hsl::toRGB(hue, saturation, luminance);

        return Py_BuildValue("iii", color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    PyObject *hsl_to_hex(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        return PyUnicode_FromString(gp::hsl::toHex(hue, saturation, luminance));
    }

    PyObject *hsl_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::CMYK color_cmyk = gp::hsl::toCMYK(hue, saturation, luminance);

        return Py_BuildValue("ffff", color_cmyk.cyan, color_cmyk.magenta, color_cmyk.yellow, color_cmyk.key);
    }

    PyObject *hsl_to_hsv(PyObject *Py_UNUSED(self), PyObject *args) {
        PARSE_HSL

        gp::HSV color_hsv = gp::hsl::toHSV(hue, saturation, luminance);

        return Py_BuildValue("ifff", color_hsv.hue, color_hsv.saturation, color_hsv.value);
    }
}
