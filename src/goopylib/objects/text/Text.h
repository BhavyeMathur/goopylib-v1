#pragma once

#include "Font.h"
#include "TextCharacter.h"


namespace gp {
    class Text : public Renderable {

    public:
        GPAPI Text(std::string text, Point position, uint32_t fontSize, const Ref<Font>& font = nullptr);

        GPAPI ~Text();

        GPAPI std::string getText() const;

        GPAPI uint32_t getFontSize() const;

        GPAPI void setTransparency(float value) override;

    private:
        std::string m_Text;
        std::vector<TextCharacter *> m_Characters;

        uint32_t m_FontSize;
        Ref<Font> m_Font;

        uint32_t m_GlyphCount = 0;
        hb_glyph_info_t *m_GlyphInfo;
        hb_glyph_position_t *m_GlyphPositions;

        void _createGlyphs();

        uint32_t _draw(Window *window) override;

        void _destroy() const override;

        void _update() override;
    };
}
