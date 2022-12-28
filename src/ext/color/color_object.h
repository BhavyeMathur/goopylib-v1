#pragma once

#include "ext/header.h"
#include "goopylib/color/Color.h"

struct ColorObject {
    PyObject_HEAD
    std::shared_ptr<gp::Color> color;
};
