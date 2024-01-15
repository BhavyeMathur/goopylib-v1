#pragma once

#include "../renderable/object.h"

namespace gp {
    class Triangle;
}

struct TriangleObject {
    RenderableObject base;
    shared_ptr<gp::Triangle> triangle;
};
