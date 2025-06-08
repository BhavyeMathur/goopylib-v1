#pragma once

#include "gp.h"
#include "maths/gpmath.h"

namespace gp {
    struct GPAPI TextureCoords {
        Point p1{0, 0};
        Point p2{0, 0};

        TextureCoords(Point p1, Point p2);

        Point topleft() const;

        Point topright() const;

        Point bottomleft() const;

        Point bottomright() const;
    };

    struct GPAPI TextureAtlasCoords {
        TextureCoords coords;
        uint32_t page;

        TextureAtlasCoords(Point p1, Point p2, uint32_t page);
    };

    struct TextureData {
        uint32_t index;
        TextureCoords texCoords;
    };
}
