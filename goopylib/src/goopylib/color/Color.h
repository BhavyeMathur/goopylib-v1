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
        Color(Color const *color);

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
        Color(const char *hexstring, float alpha = 1);

        ~Color();

        /**
         * @return a string representation of the color
         */
        [[nodiscard]] virtual std::string toString() const;

        /**
         * @return the red component of the color
         */
        [[nodiscard]] int getRed() const;

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

        // Operator Overloads

        Color operator+(int value) const;

        Color operator+(const Color &value) const;

        Color operator-(int value) const;

        Color operator-(const Color &value) const;

        Color &operator+=(int value);

        Color &operator+=(const Color &value);

        Color &operator-=(int value);

        Color &operator-=(const Color &value);

    protected:
        int m_Red;
        int m_Green;
        int m_Blue;
        float m_Alpha;

        Color(const RGB &color, float alpha);

        void fromRGB(const RGB &color, float alpha);

        void update();

    private:
        float m_Redf = 0;
        float m_Greenf = 0;
        float m_Bluef = 0;
    };
}

namespace gp {
    /**
     * Create an RGB color by passing RGB arguments with an optional alpha parameter.
     * Convert another color object to RGB by passing it as a parameter.
     *
     * @example
     *      auto color = ColorRGB(120, 70, 0);
     * @example
     *      auto color = ColorRGB(60, 180, 90, 0.5);
     * @example
     *      auto color = ColorRGB(otherColor);
     */
    class ColorRGB final : public Color {
    public:
        /**
         * Create a ColorRGB from another color object.
         */
        ColorRGB(Color const *color);

        /**
         * Create an RGB color by passing RGB arguments with an optional alpha parameter.
         * Convert another color object to RGB by passing it as a parameter.
         *
         * @param red between 0-255
         * @param green between 0-255
         * @param blue between 0-255
         * @param alpha between 0-1
         *
         * @throws std::invalid_argument RGB must be between 0-255
         * @throws std::invalid_argument alpha must be between 0-1
         */
        ColorRGB(int red, int green, int blue, float alpha = 1.0f);
    };
}

namespace gp {
    /**
     * Create a Hexadecimal color by passing a hexstring with an optional alpha parameter. The '#' is optional.
     * Convert another color object to Hexadecimal by passing it as a parameter.
     *
     * @example
     *      auto color = ColorHex("#000");
     * @example
     *      auto color = ColorHex("a7b7c7");
     * @example
     *      auto color = ColorHex(otherColor);
     */
    class ColorHex final : public Color {
    public:
        /**
         * Create a ColorHex from another color object.
         */
        ColorHex(Color const *color);

        /**
         * Create a Hexadecimal color by passing a hexstring with an optional alpha parameter. The '#' is optional.
         * Convert another color object to Hexadecimal by passing it as a parameter.
         *
         * @param hexstring '#' is optional
         * @param alpha between 0-1
         *
         * @throws std::invalid_argument invalid hexstring
         * @throws std::invalid_argument alpha must be between 0-1
         */
        ColorHex(const char *hexstring, float alpha = 1.0f);

        [[nodiscard]] std::string toString() const override;
    };
}

namespace gp {
    /**
     * Create a CMYK color by passing cyan, magenta, yellow, key and optionally, alpha.
     * Convert another color object to CMYK by passing it as a parameter.
     *
     * @example
     *      auto color = ColorCMYK(0.5, 0.4, 0.2, 0.1);
     * @example
     *      auto color = ColorCMYK(0.6, 0.9, 1, 1, 0.5);
     * @example
     *      auto color = ColorCMYK(otherColor);
     */
    class ColorCMYK final : public Color {
    public:
        /**
         * Create a ColorCMYK from another color object.
         */
        ColorCMYK(Color const *color);

        /**
         * Create a CMYK color by passing cyan, magenta, yellow, key and optionally, alpha.
         * Convert another color object to CMYK by passing it as a parameter.
         *
         * @param cyan between 0-1
         * @param magenta between 0-1
         * @param yellow between 0-1
         * @param key between 0-1
         * @param alpha between 0-1
         *
         * @throws std::invalid_argument CMYK must be between 0-1
         * @throws std::invalid_argument alpha must be between 0-1
         */
        ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha = 1.0f);

        [[nodiscard]] std::string toString() const override;

        /**
         * @return the cyan component of the color between 0-1
         */
        [[nodiscard]] float getCyan() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setCyan(float value);

        /**
         * @return the magenta component of the color between 0-1
         */
        [[nodiscard]] float getMagenta() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setMagenta(float value);

        /**
         * @return the yellow component of the color between 0-1
         */
        [[nodiscard]] float getYellow() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setYellow(float value);

        /**
         * @return the key component of the color between 0-1
         */
        [[nodiscard]] float getKey() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setKey(float value);

    private:
        float m_Cyan;
        float m_Magenta;
        float m_Yellow;
        float m_Key;
    };
}

namespace gp {
    /**
     * Create an HSV color by passing hue (0-360), saturation (0-1), value (0-1) and optionally, alpha (0-1)
     * Convert another color object to HSV by passing it as a parameter.
     *
     * @example
     *      auto color = ColorHSV(90, 0.2, 0.2);
     * @example
     *      auto color = ColorHSV(240, 0.8, 0.9, 0.5);
     * @example
     *      auto color = ColorHSV(otherColor);
     */
    class ColorHSV final : public Color {
    public:
        /**
         * Create a ColorHSV from another color object.
         */
        ColorHSV(Color const *color);

        /**
         * Create an HSV color by passing hue (0-360), saturation (0-1), value (0-1) and optionally, alpha (0-1)
         * Convert another color object to HSV by passing it as a parameter.
         *
         * @param hue between 0-360
         * @param saturation between 0-1
         * @param value between 0-1
         * @param alpha between 0-1
         *
         * @throws std::invalid_argument hue must be between 0-360
         * @throws std::invalid_argument saturation & value must be between 0-1
         * @throws std::invalid_argument alpha must be between 0-1
         */
        ColorHSV(int hue, float saturation, float value, float alpha = 1.0f);

        [[nodiscard]] std::string toString() const override;

        /**
         * @return the hue component of the color between 0-360
         */
        [[nodiscard]] int getHue() const;

        /**
         * @param value between 0-360
         * @throws std::invalid_argument value must be in the range specified
         */
        void setHue(int value);

        /**
         * @return the saturation component of the color between 0-1
         */
        [[nodiscard]] float getSaturation() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setSaturation(float value);

        /**
         * @return the value component of the color between 0-1
         */
        [[nodiscard]] float getValue() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setValue(float value);

    private:
        int m_Hue;
        float m_Saturation;
        float m_Value;
    };
}

namespace gp {
    /**
     * Create an HSL color by passing hue (0-360), saturation (0-1), luminance (0-1) and optionally, alpha (0-1)
     * Convert another color object to HSL by passing it as a parameter.
     *
     * @example
     *      auto color = ColorHSL(90, 0.2, 0.2);
     * @example
     *      auto color = ColorHSL(240, 0.8, 0.9, 0.5);
     * @example
     *      auto color = ColorHSL(otherColor);
     */
    class ColorHSL final : public Color {
    public:
        /**
         * Create a ColorHSL from another color object.
         */
        ColorHSL(Color const *color);

        /**
         * Create an HSL color by passing hue (0-360), saturation (0-1), luminance (0-1) and optionally, alpha (0-1)
         * Convert another color object to HSL by passing it as a parameter.
         *
         * @param hue between 0-360
         * @param saturation between 0-1
         * @param luminance between 0-1
         * @param alpha between 0-1
         *
         * @throws std::invalid_argument hue must be between 0-360
         * @throws std::invalid_argument saturation & luminance must be between 0-1
         * @throws std::invalid_argument alpha must be between 0-1
         */
        ColorHSL(int hue, float saturation, float luminance, float alpha = 1.0f);

        [[nodiscard]] std::string toString() const override;

        /**
         * @return the hue component of the color between 0-360
         */
        [[nodiscard]] int getHue() const;

        /**
         * @param value between 0-360
         * @throws std::invalid_argument value must be in the range specified
         */
        void setHue(int value);

        /**
         * @return the saturation component of the color between 0-1
         */
        [[nodiscard]] float getSaturation() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setSaturation(float value);

        /**
         * @return the luminance component of the color between 0-1
         */
        [[nodiscard]] float getLuminance() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        void setLuminance(float value);

    private:
        int m_Hue;
        float m_Saturation;
        float m_Luminance;
    };
}

namespace gp {
    std::ostream &operator<<(std::ostream &os, const Color &color);
}
