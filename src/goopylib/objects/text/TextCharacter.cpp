#include "TextCharacter.h"
#include "src/goopylib/texture/Bitmap.h"




// Core Methods
namespace gp {
    TextCharacter::TextCharacter(const Glyph &glyph, Point position)
            : TexturedRectangle(strformat("%i", glyph.codepoint),
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

    void TextCharacter::_destroy() const {
        m_Window->m_Renderer.destroyGlyph(m_RendererID);
    }

    void TextCharacter::_update() {
        m_Window->m_Renderer.updateGlyph(m_RendererID, this);
    }
}
