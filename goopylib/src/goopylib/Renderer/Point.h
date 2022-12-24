#pragma once

#include "pch.h"

namespace gp {
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
        RGBAf color;

        TriangleVertexAttrib() = default;

        TriangleVertexAttrib(RGBAf color)
                : color(color) {
        }
    };

    struct TriangleVertex {
        Point vertex;
        TriangleVertexAttrib attrib;
    };

    struct QuadVertexAttrib {
        RGBAf color;

        QuadVertexAttrib() = default;

        QuadVertexAttrib(RGBAf color)
                : color(color) {
        }
    };

    struct QuadVertex {
        Point vertex;
        QuadVertexAttrib attrib;
    };

    struct EllipseVertexAttrib {
        Point localCoord;
        RGBAf color;

        EllipseVertexAttrib() = default;

        EllipseVertexAttrib(Point localCoord, RGBAf color)
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

        ImageVertexAttrib(Point texCoord)
                : texCoord(texCoord) {
        }
    };

    struct ImageVertex {
        Point vertex;
        ImageVertexAttrib attrib;
    };

    struct LineVertexAttrib {
        RGBAf color;

        LineVertexAttrib() = default;

        LineVertexAttrib(RGBAf color)
                : color(color) {
        }
    };

    struct LineVertex {
        Point vertex;
        LineVertexAttrib attrib;
    };
}
