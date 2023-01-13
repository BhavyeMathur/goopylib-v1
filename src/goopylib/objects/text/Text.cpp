#include "Text.h"

#include <utility>

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


// Core Text Methods
namespace gp {
    Text::Text(std::string text, Point position, uint32_t fontSize, const Ref<Font>& font)
            : Renderable(position, {}),
              m_Text(std::move(text)),
              m_FontSize(fontSize),
              m_Direction(s_DefaultDirection),
              m_Script(s_DefaultScript),
              m_Language(s_DefaultLanguage) {
        GP_CORE_INFO("Text::Text('{0}', ({1}, {2}), {3})", m_Text, position.x, position.y, fontSize);

        if (font == nullptr) {
            m_Font = Ref<Font>(Font::s_DefaultFont);

            #if GP_VALUE_CHECKING
            if (!m_Font) {
                GP_RUNTIME_ERROR("Text::Text() no fonts have been loaded!");
            }
            #endif
        }
        else {
            m_Font = font;
        }

        _createGlyphs();
    }

    Text::~Text() {
        for (auto character: m_Characters) {
            delete character;
        }
    }

    void Text::_createGlyphs() {
        for (auto character: m_Characters) {
            character->destroy();
        }
        m_Characters.clear();

        FT_Set_Char_Size(m_Font->m_FTFace, 0, m_FontSize * 64, 0, 0);

        hb_buffer_t *buffer = hb_buffer_create();

        hb_buffer_set_direction(buffer, getHarfbuffDirection(m_Direction));
        hb_buffer_set_script(buffer, m_Script);
        hb_buffer_set_language(buffer, hb_language_from_string(m_Language.c_str(), -1));

        hb_buffer_add_utf8(buffer, m_Text.c_str(), -1, 0, -1);
        hb_shape(m_Font->m_HBFont, buffer, nullptr, 0);

        m_GlyphInfo = hb_buffer_get_glyph_infos(buffer, &m_GlyphCount);
        m_GlyphPositions = hb_buffer_get_glyph_positions(buffer, nullptr);
        m_Characters.reserve(m_GlyphCount);

        float x = m_Position.x;
        float y = m_Position.y;

        for (uint32_t i = 0; i < m_GlyphCount; i++) {
            uint32_t codepoint = m_GlyphInfo[i].codepoint;
            const hb_glyph_position_t &glyph = m_GlyphPositions[i];

            if (m_Font->m_Glyphs.find(codepoint) == m_Font->m_Glyphs.end()) {
                m_Font->rasterizeGlyph(codepoint);
            }

            auto character = new gp::TextCharacter(m_Font, *m_Font->m_Glyphs[codepoint],
                                                   {x + (float) glyph.x_offset, y + (float) glyph.y_offset});
            m_Characters.emplace_back(character);

            x += (float) glyph.x_advance / 64;
            y += (float) glyph.y_advance / 64;
        }

        hb_buffer_destroy(buffer);
    }

    uint32_t Text::_draw(Window *window) {
        for (auto character: m_Characters) {
            character->draw(window);
        }
        return 0;
    }

    void Text::_destroy() {
        for (auto character: m_Characters) {
            character->destroy();
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

    void Text::setDirection(TextDirection direction) {
        m_Direction = direction;
        _createGlyphs();
        update();
    }

    TextDirection Text::getDirection() const {
        return m_Direction;
    }

    void Text::setScript(hb_script_t script) {
        m_Script = script;
        _createGlyphs();
        update();
    }

    hb_script_t Text::getScript() const {
        return m_Script;
    }

    void Text::setLanguage(std::string language) {
        m_Language = std::move(language);
        _createGlyphs();
        update();
    }

    std::string Text::getLanguage() const {
        return m_Language;
    }
}

// Static Methods
namespace gp {
    TextDirection Text::s_DefaultDirection = TextDirection::LTR;
    hb_script_t Text::s_DefaultScript = HB_SCRIPT_LATIN;
    std::string Text::s_DefaultLanguage;

    void Text::init() {
        s_DefaultLanguage = "en";
    }

    hb_direction_t Text::getHarfbuffDirection(TextDirection direction) {
        switch (direction) {
            case TextDirection::LTR:
                return HB_DIRECTION_LTR;
            case TextDirection::RTL:
                return HB_DIRECTION_RTL;
            case TextDirection::TTB:
                return HB_DIRECTION_TTB;
            case TextDirection::BTT:
                return HB_DIRECTION_BTT;
        }
    }

    void Text::setDefaultDirection(TextDirection direction) {
        s_DefaultDirection = direction;
    }

    void Text::setDefaultScript(hb_script_t script) {
        s_DefaultScript = script;
    }

    void Text::setDefaultLanguage(std::string language) {
        s_DefaultLanguage = std::move(language);
    }
}
