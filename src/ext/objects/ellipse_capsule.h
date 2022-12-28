#pragma once

#include "ellipse.h"

static PyTypeObject *Ellipse_pytype() {
    return &EllipseType;
}
