#define GP_LOGGING_LEVEL 3

#include "ColorCMYK.h"
#include "ColorRGB.h"
#include "debug/Error.h"


// Color CMYK Class
namespace gp {
    ColorCMYK::ColorCMYK(const Color &color)
        : ColorCMYK{color.toCMYK()} {
        GP_CORE_INFO("gp::ColorCMYK::ColorCMYK{0})", color->toString());
    }

    ColorCMYK::ColorCMYK(const float cyan, const float magenta, const float yellow, const float key, const float alpha)
        : Color{toRGB(cyan, magenta, yellow, key, alpha)},
          m_Cyan(cyan),
          m_Magenta(magenta),
          m_Yellow(yellow),
          m_Key(key) {
        GP_CORE_INFO("gp::ColorCMYK::ColorCMYK({0}, {1}, {2}, {3}, alpha={4})", cyan, magenta, yellow, key, alpha);

        // Alpha value is checked in gp::Color constructor
        GP_CHECK_INCLUSIVE_RANGE(cyan, 0, 1, "Color cyan value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(magenta, 0, 1, "Color magenta value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(yellow, 0, 1, "Color yellow value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(key, 0, 1, "Color key value must be between 0 and 1")
    }

    ColorRGB ColorCMYK::toRGB() const {
        GP_CORE_TRACE("gp::ColorCMYK::toRGB({0})", this->toString());
        return toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key, m_Alpha);
    }

    ColorRGB ColorCMYK::toRGB(const float cyan, const float magenta, const float yellow, float key, const float alpha) {
        GP_CORE_DEBUG("gp::ColorCMYK::toRGB({0}, {1}, {2}, {3}, alpha={4})", cyan, magenta, yellow, key, alpha);
        key = 1 - key;
        return {
            static_cast<int>(round(255 * (1 - cyan) * key)),
            static_cast<int>(round(255 * (1 - magenta) * key)),
            static_cast<int>(round(255 * (1 - yellow) * key)),
            alpha
        };
    }


    std::string ColorCMYK::toString() const {
        if (m_Alpha == 1) {
            return strformat("ColorCMYK(%.2f, %.2f, %.2f, %.2f)", m_Cyan, m_Magenta, m_Yellow, m_Key);
        }
        return strformat("ColorCMYK(%.2f, %.2f, %.2f, %.2f, alpha=%.2f)", m_Cyan, m_Magenta, m_Yellow, m_Key, m_Alpha);
    }

    float ColorCMYK::getCyan() const {
        GP_CORE_TRACE("gp::ColorCMYK::getCyan()");
        return m_Cyan;
    }

    void ColorCMYK::setCyan(const float value) {
        GP_CORE_DEBUG("gp::ColorCMYK::setCyan({0})", value);
        m_Cyan = value;
        _updateOnlyRGB(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    float ColorCMYK::getMagenta() const {
        GP_CORE_TRACE("gp::ColorCMYK::getMagenta()");
        return m_Magenta;
    }

    void ColorCMYK::setMagenta(const float value) {
        GP_CORE_DEBUG("gp::ColorCMYK::setMagenta({0})", value);
        m_Magenta = value;
        _updateOnlyRGB(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    float ColorCMYK::getYellow() const {
        GP_CORE_TRACE("gp::ColorCMYK::getYellow()");
        return m_Yellow;
    }

    void ColorCMYK::setYellow(const float value) {
        GP_CORE_DEBUG("gp::ColorCMYK::setYellow({0})", value);
        m_Yellow = value;
        _updateOnlyRGB(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    float ColorCMYK::getKey() const {
        GP_CORE_TRACE("gp::ColorCMYK::getKey()");
        return m_Key;
    }

    void ColorCMYK::setKey(const float value) {
        GP_CORE_DEBUG("gp::ColorCMYK::setKey({0})", value);
        m_Key = value;
        _updateOnlyRGB(toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key));
    }

    void ColorCMYK::_updateDerivedClass() {
        GP_CORE_DEBUG("gp::ColorCMYK::_update({0})", this->toString());
        const auto cmyk = toCMYK();

        m_Cyan = cmyk.m_Cyan;
        m_Magenta = cmyk.m_Magenta;
        m_Yellow = cmyk.m_Yellow;
        m_Key = cmyk.m_Key;
    }
}
