#pragma once

#include "extension/header.h"

#include "color.h"


namespace color {
    static bool isinstance(PyObject *object) {
        return PyObject_IsInstance(object, (PyObject *) &ColorType);
    }

    static gp::Color getPointer(PyObject *object) {
        return *((ColorObject *) object)->color;
    }

    // Create color instances

    static PyObject *create(PyObject *value) {
        return PyObject_Call((PyObject *) &ColorType, value, Py_None);
    }

    static PyObject *create(int red, int green, int blue) {
        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);
        
        return PyObject_Call((PyObject *) &ColorType,
                             Py_BuildValue("iii", red, green, blue), Py_None);
    }

    static PyObject *create(int red, int green, int blue, float alpha) {
        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

        alpha = alpha > 1 ? 1 : (alpha < 0 ? 0 : alpha);

        return PyObject_Call((PyObject *) &ColorType,
                             Py_BuildValue("iiif", red, green, blue, alpha), Py_None);
    }

    static PyObject *createRGB(int red, int green, int blue) {
        return PyObject_Call((PyObject *) &ColorRGBType,
                             Py_BuildValue("iii", red, green, blue), Py_None);
    }

    static PyObject *createHex(const char *hexstring) {
        return PyObject_Call((PyObject *) &ColorHexType,
                             Py_BuildValue("(s)", hexstring), Py_None);
    }

    static PyObject *createCMYK(float cyan, float magenta, float yellow, float key) {
        return PyObject_Call((PyObject *) &ColorCMYKType,
                             Py_BuildValue("ffff", cyan, magenta, yellow, key), Py_None);
    }

    static PyObject *createHSV(int hue, float saturation, float value) {
        return PyObject_Call((PyObject *) &ColorHSVType,
                             Py_BuildValue("iff", hue, saturation, value), Py_None);
    }

    static PyObject *createHSL(int hue, float saturation, float luminance) {
        return PyObject_Call((PyObject *) &ColorHSLType,
                             Py_BuildValue("iff", hue, saturation, luminance), Py_None);
    }
}

static PyObject *Color_create(PyObject *value) {
    return color::create(value);
}

static bool Color_isinstance(PyObject *object) {
    return color::isinstance(object);
}

static gp::Color Color_get_pointer(PyObject *object) {
    return *((ColorObject *) object)->color;
}
