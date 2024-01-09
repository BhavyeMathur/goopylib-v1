#pragma once

#include "rectangle.h"

static PyTypeObject *Rectangle_pytype() {
    return &RectangleType;
}
