#include "TexturedQuad.h"

#include <utility>
#include "src/goopylib/texture/Bitmap.h"

#include "src/config.h"

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
    TexturedQuad::TexturedQuad(std::string texture, Point p1, Point p2, Point p3, Point p4)
            : Quad({p1, p2, p3, p4}),
              m_Texture(std::move(texture)) {
        GP_CORE_DEBUG("gp::TexturedQuad::TexturedQuad({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);

        m_V1.color = {1, 1, 1, 1};
        m_V2.color = m_V1.color;
        m_V3.color = m_V1.color;
        m_V4.color = m_V1.color;
    }

    TexturedQuad::TexturedQuad(std::string texture, const Ref<Bitmap> &bitmap, Point p1, Point p2, Point p3, Point p4)
            : TexturedQuad(std::move(texture), p1, p2, p3, p4) {
        m_Bitmap = bitmap;
    }

    std::string TexturedQuad::getTextureName() const {
        return m_Texture;
    }

    void TexturedQuad::setBitmap(const Ref<Bitmap> &bitmap) {
        m_Bitmap = bitmap;
    }

    Bitmap TexturedQuad::getBitmap() const {
        return *m_Bitmap;
    }

    uint32_t TexturedQuad::_draw(Window &window) {
        return window.m_Renderer.drawTexturedQuad(this);
    }

    void TexturedQuad::_destroy() const {
        m_Window->m_Renderer.destroyTexturedQuad(m_RendererID);
    }

    void TexturedQuad::_update() {
        m_Window->m_Renderer.updateTexturedQuad(m_RendererID, this);
    }
}
