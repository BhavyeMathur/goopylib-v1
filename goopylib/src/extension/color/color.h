#pragma once

#include "extension/header.h"

#define COLOR_MODULE
#include "colormodule.h"

#include "goopylib/color/Color.h"

extern PyTypeObject ColorType;

struct ColorObject {
    PyObject_HEAD
    std::shared_ptr<gp::Color> color;
};

#include "capsule.h"
