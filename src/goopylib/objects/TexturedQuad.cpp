#define GP_LOGGING_LEVEL 3

#include "TexturedQuad.h"

#include <utility>
#include "src/goopylib/texture/Bitmap.h"

// Core Methods
namespace gp {
    TexturedQuad::TexturedQuad(std::string texture, Point p1, Point p2, Point p3, Point p4)
            : Quad(p1, p2, p3, p4),
              m_Texture(std::move(texture)) {
        GP_CORE_DEBUG("gp::TexturedQuad::TexturedQuad(({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);

        m_V1.color = {1, 1, 1, 1};
        m_V2.color = m_V1.color;
        m_V3.color = m_V1.color;
        m_V4.color = m_V1.color;
    }

    TexturedQuad::TexturedQuad(std::string texture, const Ref<Bitmap> &bitmap, Point p1, Point p2, Point p3, Point p4)
            : TexturedQuad(std::move(texture), p1, p2, p3, p4) {
        GP_CORE_DEBUG("gp::TexturedQuad::TexturedQuad({8}, ({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, texture);

        m_Bitmap = bitmap;
    }

    TexturedQuad::TexturedQuad(std::string texture)
            : m_Texture(std::move(texture)) {

        m_V1.color = {1, 1, 1, 1};
        m_V2.color = m_V1.color;
        m_V3.color = m_V1.color;
        m_V4.color = m_V1.color;
    }

    TexturedQuad::TexturedQuad(std::string texture, const Ref<Bitmap> &bitmap)
            : TexturedQuad(std::move(texture)) {

        m_Bitmap = bitmap;
    }

    RenderableSubclass TexturedQuad::_getRenderableSubclass() {
        return RenderableSubclass::TexturedQuad;
    }

    std::ostream &operator<<(std::ostream &out, const TexturedQuad &obj) {
        out << strformat("TexturedQuad(%s, (%g, %g), (%g, %g), (%g, %g), (%g, %g))", obj.m_Texture.c_str(),
                         obj.getP1().x, obj.getP1().y, obj.getP2().x, obj.getP2().y,
                         obj.getP3().x, obj.getP3().y, obj.getP4().x, obj.getP4().y);
        return out;
    }
}

namespace gp {
    std::string TexturedQuad::getTextureName() const {
        return m_Texture;
    }

    void TexturedQuad::setBitmap(const Ref<Bitmap> &bitmap) {
        m_Bitmap = bitmap;
    }

    Ref<Bitmap> TexturedQuad::getBitmap() const {
        return m_Bitmap;
    }
}
