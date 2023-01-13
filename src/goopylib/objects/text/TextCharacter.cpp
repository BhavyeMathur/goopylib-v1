#include "TextCharacter.h"

#include "Glyph.h"
#include "Font.h"

// Core Methods
namespace gp {
    TextCharacter::TextCharacter(const Ref<Font>& font, const Glyph &glyph, Point position)
            : TexturedRectangle(strformat("%s%i", font->getFamily(), glyph.codepoint),
                                glyph.bitmap,
                                {position.x + glyph.xOffset,
                                 position.y + glyph.yOffset - (float) glyph.height},

                                {position.x + glyph.xOffset + (float) glyph.width,
                                 position.y + glyph.yOffset}) {
        setColor({0, 0, 0});
    }

    uint32_t TextCharacter::_draw(Window *window) {
        return window->m_Renderer.drawGlyph(const_cast<TextCharacter *>(this));
    }
}
