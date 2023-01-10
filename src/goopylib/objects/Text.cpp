#include "Text.h"
#include "src/goopylib/maths/packing/Packing.h"
#include "src/goopylib/texture/TextureAtlas.h"

#include "freetype/ttnameid.h"
#include "freetype/ftoutln.h"

#include "harfbuzz/hb.h"
#include "harfbuzz/hb-ft.h"


#include "src/config.h"

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

        #if GP_VALUE_CHECKING
        if (s_Fonts.empty()) {
            GP_RUNTIME_ERROR("Text::Text() no fonts have been loaded!");
        }
        #endif

        Font font = s_Fonts.at(s_DefaultTypeface.family).at(s_DefaultTypeface.style);
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

        float x = m_Position.x;
        float y = m_Position.y;

        std::unordered_map<uint32_t, Ref<Bitmap>> glyphBitmaps;
        std::vector<Ref<Bitmap>> bitmaps;
        m_Characters.reserve(glyphCount);

        for (uint32_t i = 0; i < glyphCount; i++) {
            uint32_t codepoint = glyphInfo[i].codepoint;

            if (glyphBitmaps.find(codepoint) == glyphBitmaps.end()) {
                if (FT_Error err = FT_Load_Glyph(font.ft_face, codepoint, FT_LOAD_RENDER)) {
                    GP_CORE_WARN("Text::Text() failed to load {0}: '{1}'", codepoint, err);
                    continue;
                }
                Ref<Bitmap> bitmap = Ref<Bitmap>(new Bitmap((float) font.ft_face->glyph->bitmap.width,
                                                            (float) font.ft_face->glyph->bitmap.rows));
                glyphBitmaps.insert({codepoint, bitmap});
                bitmaps.push_back(bitmap);
            }
        }

        for (uint32_t i = 0; i < glyphCount; i++) {
            Ref<Bitmap> bitmap = glyphBitmaps.at(glyphInfo[i].codepoint);

            auto xSize = (float) font.ft_face->glyph->bitmap.width;
            auto ySize = (float) font.ft_face->glyph->bitmap.rows;

            float xStart = x + (float) (font.ft_face->glyph->bitmap_left + glyphPositions[i].x_offset);
            float yStart = y + (float) (font.ft_face->glyph->bitmap_top + glyphPositions[i].y_offset);

            m_Characters.push_back(new gp::Image("", {xStart, yStart},
                                                     {xStart + xSize, yStart - ySize}));

            GP_CORE_TRACE("Text::Text() creating glyph {0} '{1}'", i, glyphInfo[i].codepoint);

            x += (float) glyphPositions[i].x_advance / 64.0f;
            y += (float) glyphPositions[i].y_advance / 64.0f;
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
            // character->_update();
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

        s_Fonts[face->family_name].insert({face->style_name, font});

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
