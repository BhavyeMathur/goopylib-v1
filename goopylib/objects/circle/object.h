#pragma once

#include "../ellipse/object.h"

namespace gp {
    class Circle;
}

struct CircleObject {
    EllipseObject base;
    Ref<gp::Circle> circle;
};
