#pragma once

#include "pch.h"

namespace gp {
    struct RGBf {
        float red;
        float green;
        float blue;
    };

    struct RGBAf {
        float red;
        float green;
        float blue;
        float alpha;
    };

    struct Point {
        float x;
        float y;
    };

    // TODO pack 3x32-bit float color data into 1x32-bit unsigned int

    struct TriangleVertex {
        Point point;
        RGBf color;
        float transparency;

        TriangleVertex() = default;

        TriangleVertex(Point point, RGBf color, float transperency = 1)
                : point(point),
                color(color),
                transparency(transperency) {
        }
    };

    struct QuadVertex {
        Point point;
        RGBf color;
        float transparency;

        QuadVertex() = default;

        QuadVertex(Point point, RGBf color, float transperency = 1)
                : point(point),
                color(color),
                transparency(transperency) {
        }
    };

    struct EllipseVertex {
        Point point;
        Point localCoord;
        RGBf color;
        float transparency;

        EllipseVertex() = default;

        EllipseVertex(Point point, Point localCoord, RGBf color, float transperency = 1)
                : point(point),
                localCoord(localCoord),
                color(color),
                transparency(transperency) {
        }
    };

    struct ImageVertex {
        Point point;
        Point texCoord;
        uint32_t texSlot;
        float transparency;

        ImageVertex() = default;

        ImageVertex(Point point, Point texCoord, uint32_t texSlot, float transperency = 1)
                : point(point),
                texCoord(texCoord),
                texSlot(texSlot),
                transparency(transperency) {
        }
    };

    struct LineVertex {
        Point point;
        RGBAf color;

        LineVertex() = default;

        LineVertex(Point point, RGBAf color)
                : point(point),
                color(color) {
        }
    };
}
