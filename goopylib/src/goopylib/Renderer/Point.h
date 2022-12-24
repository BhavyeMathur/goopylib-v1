#pragma once

#include "pch.h"

namespace gp {
    struct RGBf {
        float red = 0;
        float green = 0;
        float blue = 0;

        RGBf() = default;

        RGBf(float red, float green, float blue)
                : red(red),
                green(green),
                blue(blue) {
        }
    };

    struct RGBAf {
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 1;

        RGBAf() = default;

        RGBAf(float red, float green, float blue, float alpha = 1)
                : red(red),
                green(green),
                blue(blue),
                alpha(alpha) {
        }
    };

    struct Point {
        float x = 0;
        float y = 0;

        Point() = default;

        Point(float x, float y)
                : x(x),
                y(y) {
        }
    };

    // TODO pack 3x32-bit float color data into 1x32-bit unsigned int

    struct TriangleVertexAttrib {
        RGBf color;
        float transparency = 1;

        TriangleVertexAttrib() = default;

        explicit TriangleVertexAttrib(RGBf color)
                : color(color) {
        }
    };

    struct TriangleVertex {
        Point vertex;
        TriangleVertexAttrib attrib;
    };

    struct QuadVertexAttrib {
        RGBf color;
        float transparency = 1;

        QuadVertexAttrib() = default;

        explicit QuadVertexAttrib(RGBf color)
                : color(color) {
        }
    };

    struct QuadVertex {
        Point vertex;
        QuadVertexAttrib attrib;
    };

    struct EllipseVertexAttrib {
        Point localCoord;
        RGBf color;
        float transparency = 1;

        EllipseVertexAttrib() = default;

        EllipseVertexAttrib(Point localCoord, RGBf color)
                : localCoord(localCoord),
                color(color) {
        }
    };

    struct EllipseVertex {
        Point vertex;
        EllipseVertexAttrib attrib;
    };

    struct ImageVertexAttrib {
        Point texCoord;
        uint32_t texSlot = 0;
        float transparency = 1;

        ImageVertexAttrib() = default;

        ImageVertexAttrib(Point texCoord, uint32_t texSlot)
                : texCoord(texCoord),
                texSlot(texSlot) {
        }
    };

    struct ImageVertex {
        Point vertex;
        ImageVertexAttrib attrib;
    };

    struct LineVertexAttrib {
        RGBAf color;

        LineVertexAttrib() = default;

        explicit LineVertexAttrib(RGBAf color)
                : color(color) {
        }
    };

    struct LineVertex {
        Point vertex;
        LineVertexAttrib attrib;
    };
}
