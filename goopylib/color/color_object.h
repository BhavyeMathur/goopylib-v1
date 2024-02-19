#pragma once

#include "goopylib/header.h"
#include "color/Color.h"

struct ColorObject {
    PyObject_HEAD
    shared_ptr<gp::Color> color;
};
