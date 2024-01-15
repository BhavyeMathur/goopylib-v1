#pragma once

#include "../ellipse/object.h"

namespace gp {
    class Circle;
}

struct CircleObject {
    EllipseObject base;
    shared_ptr<gp::Circle> circle;
};
