#pragma once

#include "Color.h"


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
        GPAPI ColorHSV(Color const *color);

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
        GPAPI ColorHSV(int hue, float saturation, float value, float alpha = 1.0f);

        [[nodiscard]] GPAPI std::string toString() const override;

        /**
         * @return the hue component of the color between 0-360
         */
        [[nodiscard]] GPAPI int getHue() const;

        /**
         * @param value between 0-360
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setHue(int value);

        /**
         * @return the saturation component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getSaturation() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setSaturation(float value);

        /**
         * @return the value component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getValue() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setValue(float value);

    protected:
        GPAPI void _update() override;

    private:
        int m_Hue;
        float m_Saturation;
        float m_Value;
    };
}
