#pragma once

#include "../renderable/object.h"

namespace gp {
    class Triangle;
}

struct TriangleObject {
    RenderableObject base;
    Ref<gp::Triangle> triangle;
};
