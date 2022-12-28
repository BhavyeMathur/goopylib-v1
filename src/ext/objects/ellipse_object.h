#pragma once

#include "renderable_object.h"
#include "goopylib/objects/Ellipse.h"

struct EllipseObject {
    RenderableObject base;
    std::shared_ptr<gp::Ellipse> ellipse;
};
