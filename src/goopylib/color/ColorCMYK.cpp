#define GP_LOGGING_LEVEL 3

#include "ColorCMYK.h"
#include "ColorRGB.h"


// Color CMYK Class
namespace gp {
    ColorCMYK::ColorCMYK(const Color &color)
        : ColorCMYK{color.toCMYK()} {
    }

    ColorCMYK::ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha)
        : Color{toRGB(cyan, magenta, yellow, key, alpha)},
          m_Cyan(cyan),
          m_Magenta(magenta),
          m_Yellow(yellow),
          m_Key(key) {
        GP_CORE_INFO("gp::ColorCMYK::ColorCMYK({0}, {1}, {2}, {3}, alpha={4})", cyan, magenta, yellow, key, alpha);

        GP_CHECK_INCLUSIVE_RANGE(cyan, 0, 1, "Color cyan value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(magenta, 0, 1, "Color magenta value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(yellow, 0, 1, "Color yellow value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(key, 0, 1, "Color key value must be between 0 and 1")

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    ColorRGB ColorCMYK::toRGB() const {
        return toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key, m_Alpha);
    }

    ColorRGB ColorCMYK::toRGB(float cyan, float magenta, float yellow, float key, float alpha) {
        key = 1 - key;
        return {
            static_cast<int>(round(255 * (1 - cyan) * key)),
            static_cast<int>(round(255 * (1 - magenta) * key)),
            static_cast<int>(round(255 * (1 - yellow) * key)),
            alpha
        };
    }


    std::string ColorCMYK::toString() const {
        return strformat("ColorCMYK(%.2f, %.2f, %.2f, %.2f)", m_Cyan, m_Magenta, m_Yellow, m_Key);
    }

    float ColorCMYK::getCyan() const {
        return m_Cyan;
    }

    void ColorCMYK::setCyan(float value) {
        m_Cyan = value;
        updateRGBA(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    float ColorCMYK::getMagenta() const {
        return m_Magenta;
    }

    void ColorCMYK::setMagenta(float value) {
        m_Magenta = value;
        updateRGBA(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    float ColorCMYK::getYellow() const {
        return m_Yellow;
    }

    void ColorCMYK::setYellow(float value) {
        m_Yellow = value;
        updateRGBA(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    float ColorCMYK::getKey() const {
        return m_Key;
    }

    void ColorCMYK::setKey(float value) {
        m_Key = value;
        updateRGBA(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    void ColorCMYK::_update() {
        auto cmyk = toCMYK();

        m_Cyan = cmyk.m_Cyan;
        m_Magenta = cmyk.m_Magenta;
        m_Yellow = cmyk.m_Yellow;
        m_Key = cmyk.m_Key;
    }
}
