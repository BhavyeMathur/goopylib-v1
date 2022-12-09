#pragma once

#include "extension/util.h"

#include "macros.h"

#include "goopylib/Color/Color.h"
#include "goopylib/Color/ColorConversions.h"

extern PyTypeObject ColorType;

extern PyTypeObject ColorRGBType;
extern PyTypeObject ColorHexType;
extern PyTypeObject ColorCMYKType;
extern PyTypeObject ColorHSVType;
extern PyTypeObject ColorHSLType;

struct ColorObject {
    PyObject_HEAD
    std::shared_ptr<gp::Color> color;
};

struct ColorRGBObject {
    ColorObject base;
    std::shared_ptr<gp::ColorRGB> color;
};

struct ColorHexObject {
    ColorObject base;
    std::shared_ptr<gp::ColorHex> color;
};

struct ColorCMYKObject {
    ColorObject base;
    std::shared_ptr<gp::ColorCMYK> color;
};

struct ColorHSVObject {
    ColorObject base;
    std::shared_ptr<gp::ColorHSV> color;
};

struct ColorHSLObject {
    ColorObject base;
    std::shared_ptr<gp::ColorHSL> color;
};

#include "util.h"
