#pragma once

#include "quad.h"

static PyTypeObject *Quad_pytype() {
    return &QuadType;
}
