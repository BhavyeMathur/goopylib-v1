#pragma once

#include "Renderable.h"


namespace gp {
    /**
     * An object representing an ellipse or oval
     */
    class Ellipse : public Renderable {

        friend class Renderer;

    public:
        /**
         * An object representing an ellipse or oval
         *
         * @param position the center (x, y) in world space
         * @param xRadius in world space
         * @param yRadius in world space
         */
        Ellipse(Point position, float xRadius, float yRadius);

        /**
         * An object representing an ellipse or oval
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         */
        Ellipse(Point p1, Point p2);

        /**
         * Sets the fill color of the object
         *
         * @param color the color of the object
         */
        void setColor(const Color& color);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the bottom-left color
         * @param color2 the bottom-right color
         * @param color3 the top-right color
         * @param color4 the top-left color
         */
        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        void setTransparency(float value) override;

        /**
         * Sets the transparency of the object
         *
         * @param v1 the bottom-left transparency
         * @param v2 the bottom-right transparency
         * @param v3 the top-right transparency
         * @param v4 the top-left transparency
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void setTransparency(float v1, float v2, float v3, float v4);

    private:
        EllipseVertexAttrib m_V1 = {{-1, -1},  {0, 0.55, 0.9}};
        EllipseVertexAttrib m_V2 = {{1, -1},  {0, 0.55, 0.9}};
        EllipseVertexAttrib m_V3 = {{1, 1},  {0, 0.55, 0.9}};
        EllipseVertexAttrib m_V4 = {{-1, 1},  {0, 0.55, 0.9}};

        float m_Radius1;
        float m_Radius2;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        [[nodiscard]] bool _contains(float x, float y) const override;

        void _onScale(float xfactor, float yfactor) override;
    };
}
