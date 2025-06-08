#pragma once

#include "gp.h"
#include "color/ColorStructs.h"
#include "maths/gpmath.h"

namespace gp {
    // TODO pack 3x32-bit float color data into 1x32-bit unsigned int (not for v2.0)

    struct SolidVertexAttrib {
        RGBAf color;
    };

    struct EllipseVertexAttrib {
        Point texCoord;
        RGBAf color;
    };

    struct TextureVertexAttrib {
        RGBAf color;
        Point texCoord;
        uint32_t texSlot = 0;
    };

    struct SolidVertex {
        Point vertex;
        float z;
        SolidVertexAttrib attrib;

        SolidVertex(Point vertex, float z, SolidVertexAttrib attrib) :
                vertex(vertex),
                z(z),
                attrib(attrib) {

        }
    };

    struct EllipseVertex {
        Point vertex;
        float z;
        EllipseVertexAttrib attrib;

        EllipseVertex(Point vertex, float z, EllipseVertexAttrib attrib) :
                vertex(vertex),
                z(z),
                attrib(attrib) {

        }
    };

    struct TextureVertex {
        Point vertex;
        float z;
        TextureVertexAttrib attrib;

        TextureVertex(Point vertex, float z, TextureVertexAttrib attrib) :
                vertex(vertex),
                z(z),
                attrib(attrib) {

        }
    };

    struct Float4 {
        float a1;
        float a2;
        float a3;
        float a4;
    };

    struct Float3 {
        float a1;
        float a2;
        float a3;
    };
}
