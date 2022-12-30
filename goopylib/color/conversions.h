#pragma once

#include "header.h"

namespace color {

    // RGB to other format

    PyObject *rgb_to_hex(PyObject *self, PyObject *args);

    PyObject *rgb_to_cmyk(PyObject *self, PyObject *args);

    PyObject *rgb_to_hsv(PyObject *self, PyObject *args);

    PyObject *rgb_to_hsl(PyObject *self, PyObject *args);

    // Hex to other format

    PyObject *hex_to_rgb(PyObject *self, PyObject *args);

    PyObject *hex_to_cmyk(PyObject *self, PyObject *args);

    PyObject *hex_to_hsl(PyObject *self, PyObject *args);

    PyObject *hex_to_hsv(PyObject *self, PyObject *args);

    // CMYK to other format

    PyObject *cmyk_to_rgb(PyObject *self, PyObject *args);

    PyObject *cmyk_to_hex(PyObject *self, PyObject *args);

    PyObject *cmyk_to_hsv(PyObject *self, PyObject *args);

    PyObject *cmyk_to_hsl(PyObject *self, PyObject *args);

    // HSV to other format

    PyObject *hsv_to_rgb(PyObject *self, PyObject *args);

    PyObject *hsv_to_hex(PyObject *self, PyObject *args);

    PyObject *hsv_to_cmyk(PyObject *self, PyObject *args);

    PyObject *hsv_to_hsl(PyObject *self, PyObject *args);

    // HSL to other format

    PyObject *hsl_to_rgb(PyObject *self, PyObject *args);

    PyObject *hsl_to_hex(PyObject *self, PyObject *args);

    PyObject *hsl_to_cmyk(PyObject *self, PyObject *args);

    PyObject *hsl_to_hsv(PyObject *self, PyObject *args);
}
