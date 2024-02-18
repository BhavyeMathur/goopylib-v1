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
    class GPAPI ColorHSV final : public Color {
    public:
        /**
         * Create a ColorHSV from another color object.
         */
        ColorHSV(const Color &color); // NOLINT(*-explicit-conversions)

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

        [[nodiscard]] ColorRGB toRGB() const override;

        [[nodiscard]] ColorHSL toHSL() const override;

        [[nodiscard]] static ColorRGB toRGB(int hue, float saturation, float value, float alpha = 1);

    protected:
        void _updateDerivedClass() override;

    private:
        int m_Hue;
        float m_Saturation;
        float m_Value;
    };
}
