#pragma once

#include "goopylib/color/Color.h"

#include "extension/header.h"

#define COLOR_MODULE
#include "colormodule.h"

extern PyTypeObject ColorType;

struct ColorObject {
    PyObject_HEAD
    std::shared_ptr<gp::Color> color;
};

#include "capsule.h"
