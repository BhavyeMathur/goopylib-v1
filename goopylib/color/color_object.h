#pragma once

#include "header.h"
#include "goopylib/color/Color.h"

struct ColorObject {
    PyObject_HEAD
    Ref<gp::Color> color;
};
