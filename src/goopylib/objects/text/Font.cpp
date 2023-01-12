#include "Font.h"
#include "src/goopylib/texture/Bitmap.h"

#include "src/config.h"

#if (GP_LOG_FONT != true) and (GP_LOG_FONT <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_FONT
#endif

#if !GP_VALUE_CHECK_FONT
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"

#include "freetype/ttnameid.h"
#include "harfbuzz/hb-ft.h"

namespace gp {
    FT_Library Font::s_FontLibrary;
    Font *Font::s_DefaultFont;
    std::unordered_map<std::string, std::unordered_map<std::string, Font *>> Font::s_Fonts;

    Font::Font(const std::string &filepath, uint32_t faceIndex, bool setDefault) {
        GP_CORE_DEBUG("Font::loadFont('{0}', {1})", filepath, faceIndex);

        if (FT_New_Face(s_FontLibrary, filepath.c_str(), faceIndex, &m_FTFace)) {
            GP_RUNTIME_ERROR("Font::loadFont() failed to load font '{0}', face {1}", filepath, faceIndex);
        }

        forceUCS2();

        m_HBFont = hb_ft_font_create_referenced(m_FTFace);

        s_Fonts[m_FTFace->family_name].insert({m_FTFace->style_name, this});
        if (setDefault or s_DefaultFont == nullptr) {
            s_DefaultFont = this;
        }

        GP_CORE_INFO("Font::loadFont() loaded font '{0}' style '{1}'", m_FTFace->family_name, m_FTFace->style_name);
    }

    Font::~Font() {
        GP_CORE_DEBUG("gp::Font::~Font()");
        for (auto &glyph: m_Glyphs) {
            delete glyph.second;
        }
    }

    void Font::init() {
        GP_CORE_INFO("Font::init()");

        GP_CORE_DEBUG("Font::init() initialising FreeType");
        if (FT_Init_FreeType(&s_FontLibrary)) {
            GP_RUNTIME_ERROR("Font::init() failed to initialize FreeType");
        }
    }

    void Font::shutdown() {
        GP_CORE_INFO("Font::shutdown()");

        GP_CORE_DEBUG("Font::shutdown() destroying Harfbuzz fonts");
        for (const auto &fontFamily: s_Fonts) {
            for (const auto &style: fontFamily.second) {
                hb_font_destroy(style.second->m_HBFont);
            }
        }

        GP_CORE_DEBUG("Font::shutdown() freeing FreeType library");
        FT_Done_FreeType(s_FontLibrary);
    }

    int Font::forceUCS2() {
        for (int i = 0; i < m_FTFace->num_charmaps; i++) {
            FT_CharMap characterMap = m_FTFace->charmaps[i];

            if (((characterMap->platform_id == TT_PLATFORM_APPLE_UNICODE) and
                 (characterMap->encoding_id == TT_APPLE_ID_UNICODE_2_0))

                or ((characterMap->platform_id == TT_PLATFORM_MICROSOFT) and
                    (characterMap->encoding_id == TT_MS_ID_UNICODE_CS))) {
                return FT_Set_Charmap(m_FTFace, m_FTFace->charmaps[i]);
            }
        }
        return -1;
    }

    void Font::rasterizeGlyph(uint32_t codepoint) {
        if (FT_Error err = FT_Load_Glyph(m_FTFace, codepoint, FT_LOAD_RENDER)) {
            GP_CORE_WARN("Font::Font() failed to load {0}: '{1}'", codepoint, err);
            return;
        }

        if (m_UseSDF) {
            FT_Render_Glyph(m_FTFace->glyph, FT_RENDER_MODE_SDF);
        }

        uint32_t xSize = m_FTFace->glyph->bitmap.width;
        uint32_t ySize = m_FTFace->glyph->bitmap.rows;

        auto bitmapBuffer = new uint8_t[xSize * ySize];

        std::copy(m_FTFace->glyph->bitmap.buffer,
                  m_FTFace->glyph->bitmap.buffer + xSize * ySize, bitmapBuffer);

        auto bitmap = Ref<Bitmap>(new Bitmap(xSize, ySize, 1, bitmapBuffer));
        m_Glyphs.insert({codepoint, new Glyph(
                (float) m_FTFace->glyph->advance.x,
                (float) m_FTFace->glyph->advance.y,
                (float) m_FTFace->glyph->bitmap_left,
                (float) m_FTFace->glyph->bitmap_top,
                codepoint, bitmap)});
    }
}

// Static Methods
namespace gp {
    Ref<Font> Font::load(const std::string &filepath, uint32_t faceIndex, bool setDefault) {
        return Ref<Font>(new Font(filepath, faceIndex, setDefault));
    }
}
