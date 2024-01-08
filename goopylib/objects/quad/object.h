#pragma once

#include "goopylib/debug.h"

#include "goopylib/color/color_object.h"
#include "../renderable/object.h"

namespace gp {
    class Quad;
}

struct QuadObject {
    RenderableObject base;
    Ref<gp::Quad> quad;
};
