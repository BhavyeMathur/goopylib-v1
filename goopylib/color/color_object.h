#pragma once

#include "goopylib/header.h"
#include "src/goopylib/color/Color.h"

struct ColorObject {
    PyObject_HEAD
    Ref<gp::Color> color;
};
