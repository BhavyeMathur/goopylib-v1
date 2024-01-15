#pragma once

#include "goopylib/debug.h"

#include "goopylib/color/color_object.h"
#include "../renderable/object.h"

namespace gp {
    class Quad;
}

struct QuadObject {
    RenderableObject base;
    shared_ptr<gp::Quad> quad;
};
