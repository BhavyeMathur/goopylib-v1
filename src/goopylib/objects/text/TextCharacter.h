#pragma once

#include "Glyph.h"
#include "src/goopylib/objects/TexturedRectangle.h"


namespace gp {
    /**
     * An object representing a single text character
     */
    class TextCharacter : public TexturedRectangle {

        friend class Renderer;

        friend class Text;

    public:
        GPAPI TextCharacter(const Glyph &glyph, Point position);

    private:
        GPAPI uint32_t _draw(Window *window) const override;

        GPAPI void _destroy() const override;

        GPAPI void _update() const override;
    };
}
