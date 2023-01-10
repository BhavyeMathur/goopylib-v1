#include "TexturedQuad.h"

#include "config.h"

#if (GP_LOG_TEXTURED_QUAD != true) and (GP_LOG_TEXTURED_QUAD <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_TEXTURED_QUAD
#endif

#if !GP_VALUE_CHECK_TEXTURED_QUAD
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"

// Core Methods
namespace gp {
    TexturedQuad::TexturedQuad(const char* texture, Point p1, Point p2, Point p3, Point p4)
            : Quad({p1, p2, p3, p4}),
            m_Texture(texture) {
        GP_CORE_DEBUG("gp::TexturedQuad::TexturedQuad({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);

        m_V1.color = {1, 1, 1, 1};
        m_V2.color = {1, 1, 1, 1};
        m_V3.color = {1, 1, 1, 1};
        m_V4.color = {1, 1, 1, 1};
    }

    const char *TexturedQuad::getTextureName() const {
        return m_Texture;
    }

    uint32_t TexturedQuad::_draw(Window *window) const {
        return window->m_Renderer.drawTexturedQuad(const_cast<TexturedQuad *>(this));
    }

    void TexturedQuad::_destroy() const {
        m_Window->m_Renderer.destroyTexturedQuad(m_RendererID);
    }

    void TexturedQuad::_update() const {
        m_Window->m_Renderer.updateTexturedQuad(m_RendererID, this);
    }
}
