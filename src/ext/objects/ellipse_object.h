#pragma once

#include "renderable_object.h"
#include "goopylib/objects/Ellipse.h"

struct EllipseObject {
    RenderableObject base;
    Ref<gp::Ellipse> ellipse;
};
