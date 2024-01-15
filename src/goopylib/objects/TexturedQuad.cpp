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

    TexturedQuad::TexturedQuad(std::string texture, const shared_ptr<Bitmap> &bitmap, Point p1, Point p2, Point p3, Point p4)
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

    TexturedQuad::TexturedQuad(std::string texture, const shared_ptr<Bitmap> &bitmap)
            : TexturedQuad(std::move(texture)) {

        m_Bitmap = bitmap;
    }

    RenderableSubclass TexturedQuad::_getRenderableSubclass() {
        return RenderableSubclass::TexturedQuad;
    }

    std::string TexturedQuad::toString() const {
        return strformat("TexturedQuad('%s', (%g, %g), (%g, %g), (%g, %g), (%g, %g))", m_Texture.c_str(),
                         getP1().x, getP1().y, getP2().x, getP2().y, getP3().x, getP3().y, getP4().x, getP4().y);
    }
}

namespace gp {
    std::string TexturedQuad::getTextureName() const {
        return m_Texture;
    }

    void TexturedQuad::setBitmap(const shared_ptr<Bitmap> &bitmap) {
        m_Bitmap = bitmap;
    }

    shared_ptr<Bitmap> TexturedQuad::getBitmap() const {
        return m_Bitmap;
    }
}
