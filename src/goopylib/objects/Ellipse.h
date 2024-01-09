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
        GPAPI Ellipse(Point position, float xRadius, float yRadius);

        /**
         * An object representing an ellipse or oval
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         */
        GPAPI Ellipse(Point p1, Point p2);

        GPAPI virtual ~Ellipse() = default;

        GPAPI std::string toString() const override;

        /**
         * Sets the fill color of the object
         *
         * @param color the color of the object
         */
        GPAPI void setColor(const Color &color);

        /**
         * Sets the fill color of the object
         *
         * @param color the color of the object
         * @param alpha alpha component of the color between 0-1
         *
         * @throws std::invalid_argument invalid hexstring
         * @throws std::invalid_argument alpha must be between 0-1
         */
        GPAPI void setColor(const char *hexstring, float alpha = 1);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         * @param color3 the color of the 3rd vertex
         * @param color4 the color of the 4th vertex
         *
         * @throws std::invalid_argument invalid hexstring
         */
        GPAPI void setColor(const char *hex1, const char *hex2, const char *hex3, const char *hex4);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the bottom-left color
         * @param color2 the bottom-right color
         * @param color3 the top-right color
         * @param color4 the top-left color
         */
        GPAPI void setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4);

        /**
         * Sets the fill color of the object
         *
         * @param red red component of the color between 0-255
         * @param green green component of the color between 0-255
         * @param blue blue component of the color between 0-255
         * @param alpha alpha component of the color between 0-1
         *
         * @throws std::invalid_argument RGB must be between 0-255
         * @throws std::invalid_argument alpha must be between 0-1
         */
        GPAPI void setColor(int red, int green, int blue, float alpha = 1);

        /**
         * Sets the transparency of the object
         *
         * @param value transparency of the object between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        GPAPI void setTransparency(float value) override;

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
        GPAPI void setTransparency(float v1, float v2, float v3, float v4);

        /**
         *
         * @return the transparency at each vertex of the object
         *
         */
        [[nodiscard]] GPAPI Float4 getTransparency();

        [[nodiscard]] GPAPI bool isOpaque() const override;

    protected:
        float m_Radius1;
        float m_Radius2;

    private:
        EllipseVertexAttrib m_V1 = {{-1,   -1},
                                    {0.0f, 0.55f, 0.9f}};
        EllipseVertexAttrib m_V2 = {{1,    -1},
                                    {0.0f, 0.55f, 0.9f}};
        EllipseVertexAttrib m_V3 = {{1,    1},
                                    {0.0f, 0.55f, 0.9f}};
        EllipseVertexAttrib m_V4 = {{-1,   1},
                                    {0.0f, 0.55f, 0.9f}};

        [[nodiscard]] GPAPI bool _contains(float x, float y) const override;

        GPAPI void _onScale(float xfactor, float yfactor) override;

        [[nodiscard]] GPAPI RenderableSubclass _getRenderableSubclass() override;
    };
}
