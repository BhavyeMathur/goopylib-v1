#pragma once

#include <utility>

#include "TexturedQuad.h"
#include "Rectangle.h"
#include "src/goopylib/texture/Bitmap.h"

namespace gp {
    /**
     * An object representing a textured rectangle
     */
    class TexturedRectangle : public TexturedQuad, public Rectangle {

    public:
        /**
         * An object representing a textured rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        GPAPI TexturedRectangle(const std::string &texture, Point position, float width, float height);

        /**
         * An object representing a textured rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         */
        GPAPI TexturedRectangle(const std::string &texture, const shared_ptr<Bitmap> &bitmap, Point position);

        /**
         * An object representing a textured rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        GPAPI TexturedRectangle(std::string texture, const shared_ptr<Bitmap> &bitmap, Point position, float width,
                                float height);

        /**
         * An object representing a textured rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI TexturedRectangle(std::string texture, Point p1, Point p2);

        /**
         * An object representing a textured rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI TexturedRectangle(std::string texture, const shared_ptr<Bitmap> &bitmap, Point p1, Point p2);

        [[nodiscard]] GPAPI std::string toString() const override;

    protected:
        /**
         * An object representing a textured rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI TexturedRectangle(std::string texture);

        /**
         * An object representing a textured rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI TexturedRectangle(std::string texture, const shared_ptr<Bitmap> &bitmap);
    };
}
