#pragma once

#include "renderable.h"

static PyTypeObject *Renderable_pytype() {
    return &RenderableType;
}
