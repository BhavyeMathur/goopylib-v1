#pragma once

#include "renderable_object.h"
#include "goopylib/objects/Quad.h"

struct QuadObject {
    RenderableObject base;
    Ref<gp::Quad> quad;
};
