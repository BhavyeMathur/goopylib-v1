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
    class GPAPI ColorHex final : public Color {
    public:
        /**
         * Create a ColorHex from another color object.
         */
        ColorHex(const Color &color); // NOLINT(*-explicit-conversions)

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
        ColorHex(const std::string& hexstring, float alpha = 1.0f); // NOLINT(*-explicit-conversions)

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] ColorRGB toRGB() const override;

        [[nodiscard]] static ColorRGB toRGB(const std::string& hexstring, float alpha = 1);

    private:
        static ColorRGB _3toRGB(const std::string &hexstring, float alpha);

        static ColorRGB _4toRGB(const std::string &hexstring, float alpha);

        static ColorRGB _6toRGB(const std::string &hexstring, float alpha);

        static ColorRGB _7toRGB(const std::string &hexstring, float alpha);

        static int _digitToInt(char digit);
    };
}
