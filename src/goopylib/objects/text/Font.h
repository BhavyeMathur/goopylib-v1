#pragma once

#include "Glyph.h"

#include "freetype/ft2build.h"
#include "src/vendor/freetype/freetype/freetype.h"

#include "harfbuzz/hb.h"

namespace gp {
    struct Font {
        FT_Face ft_face;
        hb_font_t *hb_font;
        std::unordered_map<uint32_t, Glyph *> glyphs;

        ~Font();
    };

    struct Typeface {
        std::string family;
        std::string style;
    };
}
