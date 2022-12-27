#pragma once

#include "goopylib/objects/Renderable.h"

#include "ext/header.h"

struct RenderableObject {
    PyObject_HEAD
    std::shared_ptr<gp::Renderable> renderable;
};

PyTypeObject RenderableType;
