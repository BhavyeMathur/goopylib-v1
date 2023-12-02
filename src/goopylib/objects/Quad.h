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
        GPAPI Quad(Point p1, Point p2, Point p3, Point p4);

        // TODO colour alpha should affect shape transparency

        /**
         * Sets the fill color of the object
         * @param color the color of the object
         */
        void GPAPI setColor(const Color& color);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         * @param color3 the color of the 3rd vertex
         * @param color4 the color of the 4th vertex
         */
        void GPAPI setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        /**
         * Sets the fill color of the object
         * @param color the color of the object
         */
        void GPAPI setColor(const char *hexstring);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         * @param color3 the color of the 3rd vertex
         * @param color4 the color of the 4th vertex
         */
        void GPAPI setColor(const char *hex1, const char *hex2, const char *hex3, const char *hex4);

        /**
         * Sets the transparency of the object
         *
         * @param value transparency of the object between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void GPAPI setTransparency(float value) override;

        /**
         * Sets the transparency of the object
         *
         * @param v1 transparency of the 1st vertex between 0-1
         * @param v2 transparency of the 2nd vertex between 0-1
         * @param v3 transparency of the 3rd vertex between 0-1
         * @param v4 transparency of the 4th vertex between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void GPAPI setTransparency(float v1, float v2, float v3, float v4);

    protected:
        SolidVertexAttrib m_V1 = {{0.0f, 0.55f, 0.9f}};
        SolidVertexAttrib m_V2 = {{0.0f, 0.55f, 0.9f}};
        SolidVertexAttrib m_V3 = {{0.0f, 0.55f, 0.9f}};
        SolidVertexAttrib m_V4 = {{0.0f, 0.55f, 0.9f}};

        GPAPI void _update() override;

    private:
        GPAPI uint32_t _draw(Window *window) override;

        GPAPI void _destroy() const override;

        [[nodiscard]] GPAPI bool _contains(float x, float y) const override;
    };
}
