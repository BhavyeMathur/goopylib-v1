#pragma once

#include "Quad.h"

namespace gp {
    class Rectangle : public Quad {

    public:
        Rectangle(Point position, float width, float height)
        : Quad({position.x - width / 2.0f, position.y - height / 2.0f},
               {position.x + width / 2.0f, position.y - height / 2.0f},
               {position.x + width / 2.0f, position.y + height / 2.0f},
               {position.x - width / 2.0f, position.y + height / 2.0f}) {}

        Rectangle(Point p1, Point p2)
                : Quad({p1.x, p1.y},
                       {p2.x, p1.y},
                       {p2.x, p2.y},
                       {p1.x, p2.y}) {}
    };
}
