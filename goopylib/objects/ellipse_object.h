#pragma once

#include "renderable_object.h"
#include "src/goopylib/objects/Ellipse.h"

struct EllipseObject {
    RenderableObject base;
    Ref<gp::Ellipse> ellipse;
};
