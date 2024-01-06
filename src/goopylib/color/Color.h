#pragma once

#include "gp.h"
#include "ColorStructs.h"

namespace gp {
    /**
     * Create colors by passing RGB arguments or a hexstring.
     * Specify an alpha value by passing a float as the last parameter.
     *
     * @example
     *      auto color = Color(120, 70, 0);
     * @example
     *      auto color = Color("#fff");
     * @example
     *      auto color = Color(60, 180, 90, 0.5);
     */
    class Color {
    public:
        /**
         * Create a color object from another color object.
         */
        GPAPI Color(Color const *color);

        /**
         * Create colors by passing RGB arguments or a hexstring.
         * Specify an alpha value by passing a float as the last parameter.
         *
         * @param red red component of the color between 0-255
         * @param green green component of the color between 0-255
         * @param blue blue component of the color between 0-255
         * @param alpha alpha component of the color between 0-1
         *
         * @throws std::invalid_argument RGB must be between 0-255
         * @throws std::invalid_argument alpha must be between 0-1
         */
        GPAPI Color(int red, int green, int blue, float alpha = 1);

        /**
         * Create colors by passing RGB arguments or a hexstring.
         * Specify an alpha value by passing a float as the last parameter.
         *
         * @param hexstring color hexadecimal string. '#' is optional.
         * @param alpha alpha component of the color between 0-1
         *
         * @throws std::invalid_argument invalid hexstring
         * @throws std::invalid_argument alpha must be between 0-1
         */
        GPAPI Color(const char *hexstring, float alpha = 1);

        GPAPI virtual ~Color();

        /**
         * @return a string representation of the color
         */
        [[nodiscard]] GPAPI virtual std::string toString() const;

        /**
         * @return the red component of the color
         */
        [[nodiscard]] GPAPI int getRed() const;

        // TODO unittests for changing RGB components and effect on HSV/HSL/CMYK/Hexstring

        /**
         * @param value between 0-255
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setRed(int value);

        /**
         * @return the green component of the color
         */
        [[nodiscard]] GPAPI int getGreen() const;

        /**
         * @param value between 0-255
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setGreen(int value);

        /**
         * @return the blue component of the color
         */
        [[nodiscard]] GPAPI int getBlue() const;

        /**
         * @param value between 0-255
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setBlue(int value);

        /**
         * @return the alpha component of the color
         */
        [[nodiscard]] GPAPI float getAlpha() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setAlpha(float value);

        /**
         * @return the red component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getRedf() const;

        /**
         * @return the green component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getGreenf() const;

        /**
         * @return the blue component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getBluef() const;

        /**
         * @return a struct with RGBA between 0-1
         */
        [[nodiscard]] RGBAf getRGBAf() const;

        // Operator Overloads

        GPAPI Color operator+(int value) const;

        GPAPI Color operator+(const Color &value) const;

        GPAPI Color operator-(int value) const;

        GPAPI Color operator-(const Color &value) const;

        GPAPI Color &operator+=(int value);

        GPAPI Color &operator+=(const Color &value);

        GPAPI Color &operator-=(int value);

        GPAPI Color &operator-=(const Color &value);

    protected:
        int m_Red;
        int m_Green;
        int m_Blue;
        float m_Alpha;

        GPAPI Color(const RGB &color, float alpha);

        GPAPI void fromRGB(const RGB &color, float alpha);

        GPAPI void update();

        GPAPI virtual void _update() {};

    private:
        float m_Redf = 0;
        float m_Greenf = 0;
        float m_Bluef = 0;
    };
}

namespace gp {
    GPAPI std::ostream &operator<<(std::ostream &os, const Color &color);
}
