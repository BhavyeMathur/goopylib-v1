#pragma once

#include "renderable_object.h"
#include "goopylib/objects/Quad.h"

struct QuadObject {
    RenderableObject base;
    std::shared_ptr<gp::Quad> quad;
};
