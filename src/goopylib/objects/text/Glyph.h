#pragma once

#include "gp.h"


namespace gp {
    class Bitmap;

    struct Glyph {
        float xAdvance = 0;
        float yAdvance = 0;
        float xOffset = 0;
        float yOffset = 0;

        uint32_t width = 0;
        uint32_t height = 0;

        uint32_t codepoint = 0;
        Ref<Bitmap> bitmap = nullptr;

        Glyph() = default;

        Glyph(float xAdvance, float yAdvance, float xOffset, float yOffset, uint32_t code, const Ref<Bitmap> &bitmap);
    };
}
