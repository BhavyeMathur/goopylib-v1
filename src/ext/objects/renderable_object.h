#pragma once

#include "ext/header.h"
#include "goopylib/objects/Renderable.h"

struct RenderableObject {
    PyObject_HEAD
    std::shared_ptr<gp::Renderable> renderable;
};
