#pragma once

#include "gp.h"

#include "Bitmap.h"
#include "src/goopylib/maths/gpmath.h"
#include "src/goopylib/maths/packing/Packing.h"

namespace gp {
    struct TextureCoords {
        Point p1;
        Point p2;
    };

    class TextureAtlas {

    public:
        static TextureCoords add(const Bitmap& bitmap);

        static void init();

    private:
        packing::Bin* m_Bin;

        static std::vector<TextureAtlas *> s_Atlases;
        static uint32_t s_Width;
        static uint32_t s_Height;

        TextureAtlas();

        ~TextureAtlas() = default;
    };
}
