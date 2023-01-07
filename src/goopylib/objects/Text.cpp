#include "Text.h"

#include "freetype/ttnameid.h"
#include "freetype/ftoutln.h"

#include "harfbuzz/hb.h"
#include "harfbuzz/hb-ft.h"

#if (GP_LOG_TEXT != true) and (GP_LOG_TEXT <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_TEXT
#endif

#if !GP_VALUE_CHECK_TEXT
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"

struct Spanner {
    int xMin;
    int xMax;
    int yMin;
    int yMax;
};

void spanner_sizer(int y, int count, const FT_Span *spans, void *user) {
    auto baton = (Spanner *) user;

    if (y < baton->yMin) {
        baton->yMin = y;
    }
    if (y > baton->yMax) {
        baton->yMax = y;
    }

    for (int i = 0; i < count; i++) {
        if (spans[i].x + spans[i].len > baton->xMax) {
            baton->xMax = spans[i].x + spans[i].len;
        }
        if (spans[i].x < baton->xMin) {
            baton->xMin = spans[i].x;
        }
    }
}

namespace gp {
    Text::Text(std::string text, Point position, uint32_t fontSize)
            : m_Text(std::move(text)),
              m_FontSize(fontSize),
              Renderable(position, {}) {
        GP_CORE_INFO("Text::Text('{0}', ({1}, {2}), {3})", m_Text, position.x, position.y, fontSize);

        Font font = s_Fonts[s_DefaultTypeface.family][s_DefaultTypeface.style];
        FT_Set_Char_Size(font.ft_face, 0, m_FontSize * 64, 0, 0);

        hb_buffer_t *buffer = hb_buffer_create();

        hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
        hb_buffer_set_script(buffer, HB_SCRIPT_LATIN);
        hb_buffer_set_language(buffer, hb_language_from_string("en", -1));

        hb_buffer_add_utf8(buffer, m_Text.c_str(), -1, 0, -1);
        hb_shape(font.hb_font, buffer, nullptr, 0);

        uint32_t glyphCount;
        hb_glyph_info_t *glyphInfo = hb_buffer_get_glyph_infos(buffer, nullptr);
        hb_glyph_position_t *glyphPositions = hb_buffer_get_glyph_positions(buffer, &glyphCount);

        GP_CORE_DEBUG("Text::Text() got {0} glyphs", glyphCount);

        m_Characters.reserve(glyphCount);

        float x = m_Position.x;
        float y = m_Position.y;

        for (uint32_t i = 0; i < glyphCount; i++) {
            if (FT_Error err = FT_Load_Glyph(font.ft_face, glyphInfo[i].codepoint, 0)) {
                GP_CORE_WARN("Text::Text() failed to load {0}: '{1}'", glyphInfo[i].codepoint, err);
                continue;
            }
            if (font.ft_face->glyph->format != FT_GLYPH_FORMAT_OUTLINE) {
                GP_CORE_WARN("Text::Text() glyph->format = '{0}'", (char *) &font.ft_face->glyph->format);
                continue;
            }

            float xOffset = (float) glyphPositions[i].x_offset / 64.0f;
            float yOffset = (float) glyphPositions[i].y_offset / 64.0f;
            float xAdvance = (float) glyphPositions[i].x_advance / 64.0f;
            float yAdvance = (float) glyphPositions[i].y_advance / 64.0f;

            float xSize = (float) font.ft_face->glyph->metrics.width / 64.0f;
            float ySize = (float) font.ft_face->glyph->metrics.height / 64.0f;
            float xBearing = (float) font.ft_face->glyph->metrics.horiBearingX / 64.0f;
            float yBearing = (float) font.ft_face->glyph->metrics.horiBearingY / 64.0f;

            GP_CORE_TRACE("Text::Text() creating glyph {0} '{1}'", i, glyphInfo[i].codepoint);

            GP_CORE_TRACE("\tsize=({0}, {1})", xSize, ySize);
            GP_CORE_TRACE("\toffset=({0}, {1})", xOffset, yOffset);
            GP_CORE_TRACE("\tadvance=({0}, {1})", xAdvance, yAdvance);
            GP_CORE_TRACE("\tbearing=({0}, {1})", xBearing, yBearing);

            m_Characters.push_back(new gp::Rectangle({x + xBearing, y + yBearing},
                                                     {x + xBearing + xSize, y + yBearing - ySize}));

            x += xAdvance;
            y += yAdvance;
        }

        hb_buffer_destroy(buffer);
    }

    Text::~Text() {
        for (auto character: m_Characters) {
            delete character;
        }
    }

    uint32_t Text::_draw(Window *window) const {
        for (auto character: m_Characters) {
            character->draw(window);
        }
        return 0;
    }

    void Text::_destroy() const {
        for (auto character: m_Characters) {
            character->destroy();
        }
    }

    void Text::_update() const {
        for (auto character: m_Characters) {
            character->_update();
        }
    }
}

// Getters & Setters
namespace gp {
    std::string Text::getText() const {
        return m_Text;
    }

    uint32_t Text::getFontSize() const {
        return m_FontSize;
    }

    void Text::setTransparency(float value) {
        for (auto character: m_Characters) {
            character->setTransparency(value);
        }
    }
}


// Static Text Functions
namespace gp {
    Typeface Text::s_DefaultTypeface;

    FT_Library Text::s_FontLibrary;
    std::unordered_map<std::string, std::unordered_map<std::string, Font>> Text::s_Fonts;

    void Text::init() {
        GP_CORE_INFO("Text::init()");

        GP_CORE_DEBUG("Text::init() initialising FreeType");
        if (FT_Init_FreeType(&s_FontLibrary)) {
            GP_RUNTIME_ERROR("Text::init() failed to initialize FreeType");
        }
    }

    void Text::terminate() {
        GP_CORE_INFO("Text::terminate()");

        GP_CORE_DEBUG("Text::terminate() destroying Harfbuzz fonts");
        for (const auto &fontFamily: s_Fonts) {
            for (const auto &style: fontFamily.second) {
                hb_font_destroy(style.second.hb_font);
            }
        }

        GP_CORE_DEBUG("Text::terminate() freeing FreeType library");
        FT_Done_FreeType(s_FontLibrary);
    }

    void Text::loadFont(const std::string &filepath, uint32_t faceIndex, bool setDefault) {
        GP_CORE_DEBUG("Text::loadFont('{0}', {1})", filepath, faceIndex);

        FT_Face face;
        if (FT_New_Face(s_FontLibrary, filepath.c_str(), faceIndex, &face)) {
            GP_RUNTIME_ERROR("Text::loadFont() failed to load font '{0}', face {1}", filepath, faceIndex);
        }

        forceUCS2(face);

        Font font = {face,
                     hb_ft_font_create(face, nullptr)};

        s_Fonts[face->family_name][face->style_name] = font;

        if (setDefault or s_DefaultTypeface.family.empty()) {
            s_DefaultTypeface = {face->family_name, face->style_name};
        }

        GP_CORE_INFO("Text::loadFont() loaded font '{0}' style '{1}'", face->family_name, face->style_name);
    }

    int Text::forceUCS2(FT_Face face) {
        for (int i = 0; i < face->num_charmaps; i++) {
            FT_CharMap characterMap = face->charmaps[i];

            if (((characterMap->platform_id == TT_PLATFORM_APPLE_UNICODE) and
                 (characterMap->encoding_id == TT_APPLE_ID_UNICODE_2_0))

                or ((characterMap->platform_id == TT_PLATFORM_MICROSOFT) and
                    (characterMap->encoding_id == TT_MS_ID_UNICODE_CS))) {
                return FT_Set_Charmap(face, face->charmaps[i]);
            }
        }
        return -1;
    }
}
