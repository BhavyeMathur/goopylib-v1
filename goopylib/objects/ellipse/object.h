#pragma once

#include "../renderable/object.h"

namespace gp {
    class Ellipse;
}

struct EllipseObject {
    RenderableObject base;
    shared_ptr<gp::Ellipse> ellipse;
};
