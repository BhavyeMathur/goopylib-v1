#pragma once

#include "goopylib/header.h"
#include "src/goopylib/objects/Renderable.h"

struct RenderableObject {
    PyObject_HEAD
    Ref<gp::Renderable> renderable;
};
