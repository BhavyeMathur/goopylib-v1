#include "TexturedRectangle.h"

namespace gp {
    TexturedRectangle::TexturedRectangle(const std::string &texture, Point position, float width, float height)
            : Quad({position.x - width / 2.0f, position.y - height / 2.0f},
                   {position.x + width / 2.0f, position.y - height / 2.0f},
                   {position.x + width / 2.0f, position.y + height / 2.0f},
                   {position.x - width / 2.0f, position.y + height / 2.0f}),
              TexturedQuad(texture),
              Rectangle() {
    };

    TexturedRectangle::TexturedRectangle(const std::string &texture, const Ref<Bitmap> &bitmap, Point position)
            : Quad({position.x - (float) bitmap->getWidth() / 2.0f,
                    position.y - (float) bitmap->getHeight() / 2.0f},

                   {position.x + (float) bitmap->getWidth() / 2.0f,
                    position.y - (float) bitmap->getHeight() / 2.0f},

                   {position.x + (float) bitmap->getWidth() / 2.0f,
                    position.y + (float) bitmap->getHeight() / 2.0f},

                   {position.x - (float) bitmap->getWidth() / 2.0f,
                    position.y + (float) bitmap->getHeight() / 2.0f}),

              TexturedQuad(texture, bitmap),
              Rectangle() {
    };

    TexturedRectangle::TexturedRectangle(std::string texture, const Ref<Bitmap> &bitmap, Point position,
                                         float width, float height)
            : Quad({position.x - width / 2.0f, position.y - height / 2.0f},
                   {position.x + width / 2.0f, position.y - height / 2.0f},
                   {position.x + width / 2.0f, position.y + height / 2.0f},
                   {position.x - width / 2.0f, position.y + height / 2.0f}),
              TexturedQuad(std::move(texture), bitmap),
              Rectangle() {
    };

    TexturedRectangle::TexturedRectangle(std::string texture, Point p1, Point p2)
            : Quad(p1, {p2.x, p1.y}, p2, {p1.x, p2.y}),
              TexturedQuad(std::move(texture)),
              Rectangle() {
    };

    TexturedRectangle::TexturedRectangle(std::string texture, const Ref<Bitmap> &bitmap, Point p1, Point p2)
            : Quad(p1, {p2.x, p1.y}, p2, {p1.x, p2.y}),
              TexturedQuad(std::move(texture), bitmap),
              Rectangle() {
    };

    TexturedRectangle::TexturedRectangle(std::string texture)
            : Quad(),
              TexturedQuad(std::move(texture)),
              Rectangle() {
    };

    TexturedRectangle::TexturedRectangle(std::string texture, const Ref<Bitmap> &bitmap)
            : Quad(),
              TexturedQuad(std::move(texture), bitmap),
              Rectangle() {
    };

    std::ostream &operator<<(std::ostream &out, const TexturedRectangle &obj) {
        out << strformat("TexturedQuad(%s, (%g, %g), (%g, %g))", obj.m_Texture.c_str(),
                         obj.getP1().x, obj.getP1().y, obj.getP3().x, obj.getP3().y);
        return out;
    }
}
