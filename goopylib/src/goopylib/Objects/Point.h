#pragma once

#include "gp.h"
#include "src/goopylib/Math/gpmath.h"

#define GP_CREATE_VERTEX(type) struct type##Vertex { Point vertex; type##VertexAttrib attrib; }

namespace gp {
    struct RGBAf {
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 1;

        RGBAf(float red, float green, float blue, float alpha = 1)
                : red(red),
                green(green),
                blue(blue),
                alpha(alpha) {
        }
    };

    // TODO pack 3x32-bit float color data into 1x32-bit unsigned int

    struct ColorVertexAttrib {
        RGBAf color;

        ColorVertexAttrib(RGBAf color) : color(color) {
        }
    };

    struct EllipseVertexAttrib {
        Point localCoord;
        RGBAf color;
    };

    struct ImageVertexAttrib {
        Point texCoord;
        uint32_t texSlot = 0;
        float transparency = 0;

        ImageVertexAttrib(Point texCoord) : texCoord(texCoord) {
        }
    };

    #define LineVertexAttrib ColorVertexAttrib
    #define TriangleVertexAttrib ColorVertexAttrib
    #define QuadVertexAttrib ColorVertexAttrib

    GP_CREATE_VERTEX(Line);
    GP_CREATE_VERTEX(Triangle);
    GP_CREATE_VERTEX(Quad);
    GP_CREATE_VERTEX(Ellipse);
    GP_CREATE_VERTEX(Image);
}
