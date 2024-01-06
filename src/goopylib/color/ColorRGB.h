#pragma once

#include "Color.h"

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
        GPAPI ColorRGB(Color const *color);

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
        GPAPI ColorRGB(int red, int green, int blue, float alpha = 1.0f);
    };
}
