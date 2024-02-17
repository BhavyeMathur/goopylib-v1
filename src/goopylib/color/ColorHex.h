#pragma once

#include "Color.h"


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
        ColorHex(const Color &color);

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
        ColorHex(const std::string& hexstring, float alpha = 1.0f);

        [[nodiscard]] GPAPI std::string toString() const override;

        [[nodiscard]] GPAPI ColorRGB toRGB() const override;

        [[nodiscard]] static GPAPI ColorRGB toRGB(const std::string& hexstring, float alpha = 1);

    private:
        GPAPI static ColorRGB _3toRGB(std::string hexstring, float alpha);

        GPAPI static ColorRGB _4toRGB(std::string hexstring, float alpha);

        GPAPI static ColorRGB _6toRGB(std::string hexstring, float alpha);

        GPAPI static ColorRGB _7toRGB(std::string hexstring, float alpha);

        GPAPI static int _digitToInt(char digit);
    };
}
