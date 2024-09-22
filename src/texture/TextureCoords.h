#pragma once

#include "gp.h"
#include "maths/gpmath.h"

namespace gp {
    struct GPAPI TextureCoords {
        Point p1{0, 0};
        Point p2{0, 0};

        TextureCoords(Point p1, Point p2);
    };
}
