#pragma once

#include "TexturedRectangle.h"


namespace gp {
    /**
     * An object representing a textured rectangle - an image
     */
    class GPAPI Image final : public TexturedRectangle {

        friend class Renderer;

    public:
        /**
         * An object representing a textured rectangle - an image
         *
         * @param path the filepath to the image
         * @param position the center (x, y) in world space
         *
         * @throws std::filesystem::filesystem_error image was not found
         * @throws std::invalid_argument unsupported image format
         */
        Image(std::string path, Point position);

        /**
         * An object representing a textured rectangle - an image
         *
         * @param path the filepath to the image
         * @param position the center (x, y) in world space
         * @param width in world space
         * @param height in world space
         *
         * @throws std::filesystem::filesystem_error image was not found
         * @throws std::invalid_argument unsupported image format
         */
        Image(std::string path, Point position, float width, float height);

        /**
         * An object representing a textured rectangle - an image
         *
         * @param path the filepath to the image
         * @param p1 the bottom-left (x, y) in world space
         * @param p2 the top-right (x, y) in world space
         *
         * @throws std::filesystem::filesystem_error image was not found
         * @throws std::invalid_argument unsupported image format
         */
        Image(std::string path, Point p1, Point p2);

        std::string toString() const override;

        /**
         *
         * @return the filepath used by the image
         */
        [[nodiscard]] std::string getPath() const;

        [[nodiscard]] shared_ptr<Bitmap> getBitmap() const override;

    private:
        const std::string m_Path;
    };
}
