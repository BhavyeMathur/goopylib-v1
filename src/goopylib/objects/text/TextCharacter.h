#pragma once

#include "src/goopylib/objects/TexturedRectangle.h"


namespace gp {
    class Font;

    class Glyph;

    /**
     * An object representing a single text character
     */
    class TextCharacter : public TexturedRectangle {

        friend class Renderer;

        friend class Text;

    public:
        GPAPI TextCharacter(const Ref<Font>& font, const Glyph &glyph, Point position);

    private:
        GPAPI uint32_t _draw(Window *window) override;

        GPAPI void _destroy() const override;

        GPAPI void _update() override;
    };
}
