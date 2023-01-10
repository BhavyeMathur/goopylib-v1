#pragma once

#include "gp.h"
#include "src/goopylib/color/ColorStructs.h"
#include "src/goopylib/maths/gpmath.h"

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

        TextureVertexAttrib(Point texCoord)
                : texCoord(texCoord) {
        }
    };

    struct SolidVertex {
        Point vertex;
        SolidVertexAttrib attrib;
    };

    struct EllipseVertex {
        Point vertex;
        EllipseVertexAttrib attrib;
    };

    struct TextureVertex {
        Point vertex;
        SolidVertexAttrib attrib;
        TextureVertexAttrib texture;
    };
}
