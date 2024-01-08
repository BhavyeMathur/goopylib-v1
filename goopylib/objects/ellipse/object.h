#pragma once

#include "../renderable/object.h"

namespace gp {
    class Ellipse;
}

struct EllipseObject {
    RenderableObject base;
    Ref<gp::Ellipse> ellipse;
};
