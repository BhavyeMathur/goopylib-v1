#pragma once

#include "Renderable.h"
#include "Rectangle.h"

#include "freetype/ft2build.h"
#include FT_FREETYPE_H

#include "harfbuzz/hb.h"


namespace gp {
    struct Font {
        FT_Face ft_face;
        hb_font_t *hb_font;
    };

    struct Typeface {
        std::string family;
        std::string style;
    };

    class Text : public Renderable {

    public:
        Text(std::string text, Point position, uint32_t fontSize);

        ~Text();

        std::string getText() const;

        uint32_t getFontSize() const;

        void setTransparency(float value) override;

        // Static methods
        static void loadFont(const std::string& filepath, uint32_t faceIndex = 0, bool setDefault = true);

        static void init();

        static void terminate();

    private:
        std::string m_Text;
        std::vector<Rectangle *> m_Characters;

        uint32_t m_FontSize;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        // Static members & methods

        static FT_Library s_FontLibrary;
        static Typeface s_DefaultTypeface;

        // {family1: {style1: ..., style2: ...}, family2: ...}
        static std::unordered_map<std::string, std::unordered_map<std::string, Font>> s_Fonts;

        static int forceUCS2(FT_Face face);
    };
}
