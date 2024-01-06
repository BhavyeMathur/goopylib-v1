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
        GPAPI ColorHex(Color const *color);

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
        GPAPI ColorHex(const char *hexstring, float alpha = 1.0f);

        [[nodiscard]] GPAPI std::string toString() const override;
    };
}
