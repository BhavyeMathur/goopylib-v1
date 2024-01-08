#pragma once

#include "../ellipse_object.h"

namespace gp {
    class Circle;
}

struct CircleObject {
    EllipseObject base;
    Ref<gp::Circle> circle;
};
