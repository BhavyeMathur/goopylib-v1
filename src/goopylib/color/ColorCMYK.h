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
    class ColorCMYK final : public Color {
    public:
        /**
         * Create a ColorCMYK from another color object.
         */
        GPAPI ColorCMYK(Color const *color);

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
        GPAPI ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha = 1.0f);

        [[nodiscard]] GPAPI std::string toString() const override;

        /**
         * @return the cyan component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getCyan() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setCyan(float value);

        /**
         * @return the magenta component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getMagenta() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setMagenta(float value);

        /**
         * @return the yellow component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getYellow() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setYellow(float value);

        /**
         * @return the key component of the color between 0-1
         */
        [[nodiscard]] GPAPI float getKey() const;

        /**
         * @param value between 0-1
         * @throws std::invalid_argument value must be in the range specified
         */
        GPAPI void setKey(float value);

    protected:
        GPAPI void _update() override;

    private:
        float m_Cyan;
        float m_Magenta;
        float m_Yellow;
        float m_Key;
    };
}
