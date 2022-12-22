#pragma once


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

    struct TriangleVertex {
        Point point;
        RGBf color;  // TODO pack 3x32-bit float data into 1x32-bit unsigned int
    };

    struct QuadVertex {
        Point point;
        RGBf color;  // TODO pack 3x32-bit float data into 1x32-bit unsigned int
    };

    struct CircleVertex {
        Point point;
        Point localCoord;
        RGBf color;  // TODO pack 3x32-bit float data into 1x32-bit unsigned int
    };
}
