#pragma once

#include "Glyph.h"

#include "freetype/ft2build.h"
#include "src/vendor/freetype/freetype/freetype.h"

#include "harfbuzz/hb.h"

namespace gp {
    class Font {

        friend class Text;

    public:
        GPAPI Font(const std::string &filepath, uint32_t faceIndex = 0, bool setDefault = true);

        GPAPI ~Font();

        GPAPI int forceUCS2();

        GPAPI void rasterizeGlyph(uint32_t codepoint);

        GPAPI static void init();

        GPAPI static void shutdown();

        GPAPI static Ref<Font> load(const std::string &filepath, uint32_t faceIndex = 0, bool setDefault = true);

    private:
        bool m_UseSDF = true;

        FT_Face m_FTFace = nullptr;
        hb_font_t *m_HBFont;
        std::unordered_map<uint32_t, Glyph *> m_Glyphs;

        static FT_Library s_FontLibrary;
        static Font *s_DefaultFont;

        // {family1: {style1: ..., style2: ...}, family2: ...}
        static std::unordered_map<std::string, std::unordered_map<std::string, Font *>> s_Fonts;
    };

    struct Typeface {
        std::string family;
        std::string style;
    };
}
