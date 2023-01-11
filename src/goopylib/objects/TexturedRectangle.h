#pragma once

#include <utility>

#include "TexturedQuad.h"
#include "src/goopylib/texture/Bitmap.h"

namespace gp {
    /**
     * An object representing a textured rectangle
     */
    class TexturedRectangle : public TexturedQuad {

    public:
        /**
         * An object representing a textured rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        GPAPI TexturedRectangle(std::string texture, Point position, float width, float height)
                : TexturedQuad(std::move(texture),
                               {position.x - width / 2.0f, position.y - height / 2.0f},
                               {position.x + width / 2.0f, position.y - height / 2.0f},
                               {position.x + width / 2.0f, position.y + height / 2.0f},
                               {position.x - width / 2.0f, position.y + height / 2.0f}) {
        };

        /**
         * An object representing a textured rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         */
        GPAPI TexturedRectangle(std::string texture, const Ref<Bitmap> &bitmap, Point position)
                : TexturedQuad(std::move(texture), bitmap,
                               {position.x - (float) bitmap->getWidth() / 2.0f,
                                position.y - (float) bitmap->getHeight() / 2.0f},

                               {position.x + (float) bitmap->getWidth() / 2.0f,
                                position.y - (float) bitmap->getHeight() / 2.0f},

                               {position.x + (float) bitmap->getWidth() / 2.0f,
                                position.y + (float) bitmap->getHeight() / 2.0f},

                               {position.x - (float) bitmap->getWidth() / 2.0f,
                                position.y + (float) bitmap->getHeight() / 2.0f}) {
        };

        /**
         * An object representing a textured rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        GPAPI TexturedRectangle(std::string texture, const Ref<Bitmap> &bitmap, Point position, float width,
                                float height)
                : TexturedQuad(std::move(texture), bitmap,
                               {position.x - width / 2.0f, position.y - height / 2.0f},
                               {position.x + width / 2.0f, position.y - height / 2.0f},
                               {position.x + width / 2.0f, position.y + height / 2.0f},
                               {position.x - width / 2.0f, position.y + height / 2.0f}) {
        };

        /**
         * An object representing a textured rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI TexturedRectangle(std::string texture, Point p1, Point p2)
                : TexturedQuad(std::move(texture),
                               {p1.x, p1.y},
                               {p2.x, p1.y},
                               {p2.x, p2.y},
                               {p1.x, p2.y}) {
        };

        /**
         * An object representing a textured rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI TexturedRectangle(std::string texture, const Ref<Bitmap> &bitmap, Point p1, Point p2)
                : TexturedQuad(std::move(texture), bitmap,
                               {p1.x, p1.y},
                               {p2.x, p1.y},
                               {p2.x, p2.y},
                               {p1.x, p2.y}) {
        };
    };
}
