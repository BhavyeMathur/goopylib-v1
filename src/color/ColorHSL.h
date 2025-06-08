#pragma once

#include "Color.h"


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
    class GPAPI ColorHSL final : public Color {
    public:
        /**
         * Create a ColorHSL from another color object.
         */
        ColorHSL(const Color &color); // NOLINT(*-explicit-conversions)

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

        [[nodiscard]] ColorRGB toRGB() const override;

        [[nodiscard]] ColorHSV toHSV() const override;

        [[nodiscard]] static ColorRGB toRGB(int hue, float saturation, float luminance, float alpha = 1);

    protected:
        void _updateDerivedClass() override;

    private:
        int m_Hue;
        float m_Saturation;
        float m_Luminance;
    };
}
