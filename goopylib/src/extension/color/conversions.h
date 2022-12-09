#pragma once

#include "macros.h"
#include "extension/util.h"

#include "goopylib/Color/ColorConversions.h"

namespace color {

    // RGB to other format

    PyObject *rgb_to_hex(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *rgb_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *rgb_to_hsv(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *rgb_to_hsl(PyObject *Py_UNUSED(self), PyObject *args);

    // Hex to other format

    PyObject *hex_to_rgb(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hex_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hex_to_hsl(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hex_to_hsv(PyObject *Py_UNUSED(self), PyObject *args);

    // CMYK to other format

    PyObject *cmyk_to_rgb(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *cmyk_to_hex(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *cmyk_to_hsv(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *cmyk_to_hsl(PyObject *Py_UNUSED(self), PyObject *args);

    // HSV to other format

    PyObject *hsv_to_rgb(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hsv_to_hex(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hsv_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hsv_to_hsl(PyObject *Py_UNUSED(self), PyObject *args);

    // HSL to other format

    PyObject *hsl_to_rgb(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hsl_to_hex(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hsl_to_cmyk(PyObject *Py_UNUSED(self), PyObject *args);

    PyObject *hsl_to_hsv(PyObject *Py_UNUSED(self), PyObject *args);
}
