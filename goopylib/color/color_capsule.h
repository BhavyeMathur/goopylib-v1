#pragma once

#include "color.h"

static PyTypeObject *Color_pytype() {
    return &ColorType;
}
