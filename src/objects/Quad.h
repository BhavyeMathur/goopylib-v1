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

        GPAPI virtual ~Quad() = default;

        GPAPI std::string toString() const override;

        /**
         * Sets the fill color of the object
         * @param color the color of the object
         */
        GPAPI void setColor(const Color &color);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         * @param color3 the color of the 3rd vertex
         * @param color4 the color of the 4th vertex
         */
        GPAPI void setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4);

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
         * @param v1 transparency of the 1st vertex between 0-1
         * @param v2 transparency of the 2nd vertex between 0-1
         * @param v3 transparency of the 3rd vertex between 0-1
         * @param v4 transparency of the 4th vertex between 0-1
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

        /**
        * Sets the position of the 1st vertex of the object
        *
        * @param point the (x, y) coordinate of the 1st vertex in world space
        *
        */
        GPAPI virtual void setP1(Point point);

        /**
         *
         * @return returns the (x, y) coordinates of the 1st vertex in world space
         *
         */
        [[nodiscard]] virtual GPAPI Point getP1() const;

        /**
         * Sets the position of the 2nd vertex of the object
         *
         * @param point the (x, y) coordinate of the 2nd vertex in world space
         *
         */
        GPAPI virtual void setP2(Point point);

        /**
         *
         * @return returns the (x, y) coordinates of the 2nd vertex in world space
         *
         */
        [[nodiscard]] virtual GPAPI Point getP2() const;

        /**
         * Sets the position of the 3rd vertex of the object
         *
         * @param point the (x, y) coordinate of the 3rd vertex in world space
         *
         */
        GPAPI virtual void setP3(Point point);

        /**
         *
         * @return returns the (x, y) coordinates of the 3rd vertex in world space
         *
         */
        [[nodiscard]] virtual GPAPI Point getP3() const;

        /**
         * Sets the position of the 4th vertex of the object
         *
         * @param point the (x, y) coordinate of the 4th vertex in world space
         *
         */
        GPAPI virtual void setP4(Point point);

        /**
         *
         * @return returns the (x, y) coordinates of the 4th vertex in world space
         *
         */
        [[nodiscard]] virtual GPAPI Point getP4() const;

    protected:
        SolidVertexAttrib m_V1 = {{0.0f, 0.55f, 0.9f}};
        SolidVertexAttrib m_V2 = {{0.0f, 0.55f, 0.9f}};
        SolidVertexAttrib m_V3 = {{0.0f, 0.55f, 0.9f}};
        SolidVertexAttrib m_V4 = {{0.0f, 0.55f, 0.9f}};

        GPAPI Quad() = default;

    private:
        [[nodiscard]] GPAPI bool _contains(float x, float y) const override;

        [[nodiscard]] GPAPI RenderableSubclass _getRenderableSubclass() override;
    };
}
