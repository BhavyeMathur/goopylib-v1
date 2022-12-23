#pragma once

#include "pch.h"

namespace gp {
    struct RGBf {
        float red;
        float green;
        float blue;
    };

    struct Point {
        float x;
        float y;
    };

    // TODO pack 3x32-bit float color data into 1x32-bit unsigned int

    struct TriangleVertex {
        Point point;
        RGBf color;
    };

    struct QuadVertex {
        Point point;
        RGBf color;
    };

    struct EllipseVertex {
        Point point;
        Point localCoord;
        RGBf color;
    };

    struct ImageVertex {
        Point point;
        Point texCoord;
        uint32_t texSlot;
    };
}
