#pragma once

#include "Color.h"


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
    class GPAPI ColorCMYK final : public Color {
    public:
        /**
         * Create a ColorCMYK from another color object.
         */
        ColorCMYK(const Color &color); // NOLINT(*-explicit-conversions)

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

        [[nodiscard]] ColorRGB toRGB() const override;

        [[nodiscard]] static ColorRGB toRGB(float cyan, float magenta, float yellow, float key, float alpha = 1);

    protected:
        void _updateDerivedClass() override;

    private:
        float m_Cyan;
        float m_Magenta;
        float m_Yellow;
        float m_Key;
    };
}
