#pragma once

#include "gp.h"
#include "goopylib/color/ColorStructs.h"
#include "goopylib/maths/gpmath.h"

#define GP_CREATE_VERTEX(type) struct type##Vertex { Point vertex; type##VertexAttrib attrib; }

namespace gp {
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
        float transparency = 1;

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
