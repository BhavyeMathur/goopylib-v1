#pragma once

#include "renderable_object.h"
#include "src/goopylib/objects/Quad.h"

struct QuadObject {
    RenderableObject base;
    Ref<gp::Quad> quad;
};
