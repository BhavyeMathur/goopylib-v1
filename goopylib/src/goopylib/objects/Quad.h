#pragma once

#include "Renderable.h"


namespace gp {
    /**
     * An object representing a quad with 4 vertices.
     */
    class Quad : public Renderable {

        friend class Renderer;

    public:
        /**
         * An object representing a quad with 4 vertices.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         * @param p3 3rd coordinate (x, y) in world space
         * @param p4 4th coordinate (x, y) in world space
         */
        Quad(Point p1, Point p2, Point p3, Point p4);

        /**
         * Sets the fill color of the quad
         * @param color the color of the quad
         */
        void setColor(const Color& color);

        /**
         * Sets the fill color of the quad
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         * @param color3 the color of the 3rd vertex
         * @param color4 the color of the 4th vertex
         */
        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        void setTransparency(float value) override;

        /**
         * Sets the transparency of the quad
         *
         * @param v1 transparency of the 1st vertex between 0-1
         * @param v2 transparency of the 2nd vertex between 0-1
         * @param v3 transparency of the 3rd vertex between 0-1
         * @param v4 transparency of the 4th vertex between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void setTransparency(float v1, float v2, float v3, float v4);

    private:
        QuadVertexAttrib m_V1 = {{0, 0.55, 0.9}};
        QuadVertexAttrib m_V2 = {{0, 0.55, 0.9}};
        QuadVertexAttrib m_V3 = {{0, 0.55, 0.9}};
        QuadVertexAttrib m_V4 = {{0, 0.55, 0.9}};

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        [[nodiscard]] bool _contains(float x, float y) const override;
    };
}
