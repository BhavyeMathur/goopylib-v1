#define GP_LOGGING_LEVEL 3

#include <utility>

#include "TexturedQuad.h"
#include "texture/Bitmap.h"
#include "debug/Error.h"

// Core Methods
namespace gp {
    TexturedQuad::TexturedQuad(std::string texture, Point p1, Point p2, Point p3, Point p4)
            : Quad(p1, p2, p3, p4),
              m_Texture(std::move(texture)) {
        GP_CORE_DEBUG("gp::TexturedQuad::TexturedQuad(({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
    }

    TexturedQuad::TexturedQuad(std::string texture, const shared_ptr<Bitmap> &bitmap, Point p1, Point p2, Point p3,
                               Point p4)
            : TexturedQuad(std::move(texture), p1, p2, p3, p4) {
        GP_CORE_DEBUG("gp::TexturedQuad::TexturedQuad({8}, ({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, texture);

        m_Bitmap = bitmap;
    }

    TexturedQuad::TexturedQuad(std::string texture)
            : m_Texture(std::move(texture)) {
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

    const void *TexturedQuad::vertexAttribData() const {
        return static_cast<const void *>(m_VertexAttribs);
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

    void TexturedQuad::_setColor(const RGBAf rgbaf1, const RGBAf rgbaf2, const RGBAf rgbaf3, const RGBAf rgbaf4) {
        m_VertexAttribs[0].color = rgbaf1;
        m_VertexAttribs[1].color = rgbaf2;
        m_VertexAttribs[2].color = rgbaf3;
        m_VertexAttribs[3].color = rgbaf4;

        update();
    }

    void TexturedQuad::_setTransparency(float v1, float v2, float v3, float v4) {
        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, "transparency must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, "transparency must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, "transparency must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, "transparency must be between 0 and 1")

        m_VertexAttribs[0].color.alpha = v1;
        m_VertexAttribs[1].color.alpha = v2;
        m_VertexAttribs[2].color.alpha = v3;
        m_VertexAttribs[3].color.alpha = v4;

        update();
    }
}
