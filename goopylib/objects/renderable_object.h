#pragma once

#include "header.h"
#include "goopylib/objects/Renderable.h"

struct RenderableObject {
    PyObject_HEAD
    Ref<gp::Renderable> renderable;
};
