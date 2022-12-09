#pragma once

#include "extension/util.h"

#include "macros.h"
#include "util.h"

#include "goopylib/Color/Util.h"


namespace color {
    PyObject *random_rgb(PyObject *Py_UNUSED(self));

    PyObject *random_hex(PyObject *Py_UNUSED(self));

    PyObject *random_cmyk(PyObject *Py_UNUSED(self));

    PyObject *random_hsv(PyObject *Py_UNUSED(self));

    PyObject *random_hsl(PyObject *Py_UNUSED(self));
}
