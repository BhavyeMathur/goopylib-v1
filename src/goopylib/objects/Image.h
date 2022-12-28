#pragma once

#include "Renderable.h"


namespace gp {
    /**
     * An object representing a textured rectangle - an image
     */
    class Image : public Renderable {

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
        Image(const char *path, Point position);

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
        Image(const char *path, Point position, float width, float height);

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
        Image(const char *path, Point p1, Point p2);

        /**
         *
         * @return the filepath used by the image
         */
        [[nodiscard]] const char *getPath() const;

        void setTransparency(float value) override;

        /**
         * Sets the transparency of the image
         *
         * @param v1 transparency of bottom-left between 0-1
         * @param v2 transparency of bottom-right between 0-1
         * @param v3 transparency of top-right between 0-1
         * @param v4 transparency of top-left between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void setTransparency(float v1, float v2, float v3, float v4);

    private:
        ImageVertexAttrib m_V1 = {{0, 0}};
        ImageVertexAttrib m_V2 = {{1, 0}};
        ImageVertexAttrib m_V3 = {{1, 1}};
        ImageVertexAttrib m_V4 = {{0, 1}};

        const char *m_Path;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        [[nodiscard]] bool _contains(float x, float y) const override;
    };
}
