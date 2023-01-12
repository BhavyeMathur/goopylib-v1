#pragma once

#include "Font.h"
#include "TextCharacter.h"


namespace gp {
    enum class TextDirection {
        LTR,
        RTL,
        TTB,
        BTT,
    };

    class Text : public Renderable {

    public:
        GPAPI Text(std::string text, Point position, uint32_t fontSize, const Ref<Font>& font = nullptr);

        GPAPI ~Text();

        GPAPI std::string getText() const;

        GPAPI uint32_t getFontSize() const;

        GPAPI void setTransparency(float value) override;

        GPAPI void setDirection(TextDirection direction);

        GPAPI TextDirection getDirection() const;

        GPAPI void setScript(hb_script_t script);

        GPAPI hb_script_t getScript() const;

        GPAPI void setLanguage(std::string language);

        GPAPI std::string getLanguage() const;

        GPAPI static void setDefaultDirection(TextDirection direction);

        GPAPI static void setDefaultScript(hb_script_t script);

        GPAPI static void setDefaultLanguage(std::string language);

        GPAPI static void init();

    private:
        std::string m_Text;
        std::vector<TextCharacter *> m_Characters;

        uint32_t m_FontSize;
        Ref<Font> m_Font;

        uint32_t m_GlyphCount = 0;
        hb_glyph_info_t *m_GlyphInfo = nullptr;
        hb_glyph_position_t *m_GlyphPositions = nullptr;

        TextDirection m_Direction;
        static TextDirection s_DefaultDirection;

        hb_script_t m_Script;
        static hb_script_t s_DefaultScript;

        std::string m_Language;
        static std::string s_DefaultLanguage;

        void _createGlyphs();

        uint32_t _draw(Window *window) override;

        void _destroy() const override;

        void _update() override;

        static hb_direction_t getHarfbuffDirection(TextDirection direction);
    };
}
