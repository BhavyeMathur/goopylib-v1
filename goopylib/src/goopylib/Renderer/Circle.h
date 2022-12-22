#pragma once

#include "Ellipse.h"

namespace gp {
    class Circle : public Ellipse {

    public:
        Circle(Point position, float radius)
                : Ellipse(position, radius, radius) {}
    };
}
