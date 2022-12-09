#include "random.h"

namespace color {
    PyObject *random_rgb(PyObject *Py_UNUSED(self)) {
        gp::ColorRGB rgb = gp::randomRGB();
        return color::createRGB(rgb.getRed(), rgb.getGreen(), rgb.getBlue());
    }

    PyObject *random_hex(PyObject *Py_UNUSED(self)) {
        gp::ColorHex hex = gp::randomHex();
        return color::createHex(hex.toString().c_str());
    }

    PyObject *random_cmyk(PyObject *Py_UNUSED(self)) {
        gp::ColorCMYK cmyk = gp::randomCMYK();
        return color::createCMYK(cmyk.getCyan(), cmyk.getMagenta(), cmyk.getYellow(), cmyk.getKey());
    }

    PyObject *random_hsv(PyObject *Py_UNUSED(self)) {
        gp::ColorHSV hsv = gp::randomHSV();
        return color::createHSV(hsv.getHue(), hsv.getSaturation(), hsv.getValue());
    }

    PyObject *random_hsl(PyObject *Py_UNUSED(self)) {
        gp::ColorHSL hsl = gp::randomHSL();
        return color::createHSV(hsl.getHue(), hsl.getSaturation(), hsl.getLuminance());
    }
}
