#pragma once

#include "gp.h"
#include "src/goopylib/color/ColorStructs.h"
#include "src/goopylib/maths/gpmath.h"

#define GP_CREATE_VERTEX(type) struct type##Vertex { Point vertex; type##VertexAttrib attrib; }

namespace gp {
    // TODO pack 3x32-bit float color data into 1x32-bit unsigned int

    struct SolidVertexAttrib {
        RGBAf color;

        SolidVertexAttrib(RGBAf color)
                : color(color) {
        }
    };

    struct EllipseVertexAttrib {
        Point texCoord;
        RGBAf color;
    };

    struct TextureVertexAttrib {
        Point texCoord;
        uint32_t texSlot = 0;
        RGBAf color;

        TextureVertexAttrib(Point texCoord, RGBAf color = {1, 1, 1, 1})
                : texCoord(texCoord),
                  color(color) {
        }
    };

    GP_CREATE_VERTEX(Solid);
    GP_CREATE_VERTEX(Ellipse);
    GP_CREATE_VERTEX(Texture);
}
