#pragma once

#include "gp.h"
#include "ColorStructs.h"

namespace gp {
    class ColorRGB;

    class ColorHex;

    class ColorCMYK;

    class ColorHSV;

    class ColorHSL;

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
    class GPAPI Color {
    public:
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
        Color(const std::string &hexstring, float alpha = 1); // NOLINT(*-explicit-conversions)

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
        Color(int red, int green, int blue, float alpha = 1);

        Color(const Color &other) = default;

        Color(Color &&other) = default;

        virtual ~Color() = default;

        /**
         * @return a string representation of the color
         */
        [[nodiscard]] virtual std::string toString() const;

        /**
         * @return the red component of the color
         */
        [[nodiscard]] int getRed() const;

        // TODO unittests for changing RGB components and effect on HSV/HSL/CMYK/Hexstring

        /**
         * @param value between 0-255
         * @throws std::invalid_argument value must be in the range specified
         */
        void setRed(int value);

        /**
         * @return the green component of the color
         */
        [[nodiscard]] int getGreen() const;

        /**
         * @param value between 0-255
         * @throws std::invalid_argument value must be in the range specified
         */
        void setGreen(int value);

        /**
         * @return the blue component of the color
         */
        [[nodiscard]] int getBlue() const;

        /**
         * @param value between 0-255
         * @throws std::invalid_argument value must be in the range specified
         */
        void setBlue(int value);

        /**
         * @return the alpha component of the color
         */
        [[nodiscard]] float getAlpha() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setAlpha(float value);

        /**
         * @return the red component of the color between 0-1
         */
        [[nodiscard]] float getRedf() const;

        /**
         * @return the green component of the color between 0-1
         */
        [[nodiscard]] float getGreenf() const;

        /**
         * @return the blue component of the color between 0-1
         */
        [[nodiscard]] float getBluef() const;

        /**
         * @return a struct with RGBA between 0-1
         */
        [[nodiscard]] RGBAf getRGBAf() const;

        /**
         * Converts the Color to the RGB format
         */
        [[nodiscard]] virtual ColorRGB toRGB() const;

        /**
        * Converts the Color to the Hexadecimal format
        */
        [[nodiscard]] ColorHex toHex() const;

        /**
         * Converts the Color to the CMYK format
         */
        [[nodiscard]] ColorCMYK toCMYK() const;

        /**
         * Converts the Color to the HSV format
         */
        [[nodiscard]] virtual ColorHSV toHSV() const;

        /**
         * Converts the Color to the HSL format
         */
        [[nodiscard]] virtual ColorHSL toHSL() const;

        // Operator Overloads

        Color operator+(int value) const;

        Color operator+(const Color &value) const;

        Color operator-(int value) const;

        Color operator-(const Color &value) const;

        Color &operator+=(int value);

        Color &operator+=(const Color &value);

        Color &operator-=(int value);

        Color &operator-=(const Color &value);

        bool operator==(const Color &) const = default;

        bool operator==(const std::string &other) const;

        Color &operator=(const Color &other) = default;

        Color &operator=(Color &&other) noexcept = default;

#define GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS(T) Color &operator=(T &);Color &operator=(T &&) noexcept;

        GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS(ColorRGB)

        GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS(ColorHex)

        GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS(ColorCMYK)

        GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS(ColorHSV)

        GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS(ColorHSL)

#undef GP_COLOR_MOVE_COPY_ASSIGNMENT_OPERATORS

    protected:
        int m_Red;
        int m_Green;
        int m_Blue;
        float m_Alpha;

        void _updateOnlyRGB(const ColorRGB &color);

        virtual void _updateDerivedClass() {
        }

        void _clampValues();

    private:
        float m_Redf;
        float m_Greenf;
        float m_Bluef;
    };
}

namespace gp {
    std::ostream &operator<<(std::ostream &os, const Color &color);
}
