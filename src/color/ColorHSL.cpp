#define GP_LOGGING_LEVEL 3

#include "ColorHSL.h"
#include "ColorHSV.h"
#include "ColorRGB.h"
#include "debug/Error.h"


namespace gp {
    ColorHSL::ColorHSL(const Color &color)
        : ColorHSL{color.toHSL()} {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0})", color->toString());
    }

    ColorHSL::ColorHSL(const int hue, const float saturation, const float luminance, const float alpha)
        : Color{toRGB(hue, saturation, luminance, alpha)},
          m_Hue(hue),
          m_Saturation(saturation),
          m_Luminance(luminance) {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0}, {1}, {2}, alpha={3})", hue, saturation, luminance, alpha);

        // Alpha value is checked in gp::Color constructor
        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1")
    }

    ColorRGB ColorHSL::toRGB() const {
        GP_CORE_TRACE("gp::ColorHSL::toRGB({0})", this->toString());
        return toRGB(m_Hue, m_Saturation, m_Luminance, m_Alpha);
    }

    ColorRGB ColorHSL::toRGB(const int hue, const float saturation, const float luminance, const float alpha) {
        GP_CORE_DEBUG("gp::ColorHSL::toRGB({0}, {1}, {2}, alpha={3})", hue, saturation, luminance, alpha);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1")

        const float c = (1 - fabsf(2 * luminance - 1)) * saturation;
        const float x = c * (1 - fabsf(fmodf(static_cast<float>(hue) / 60, 2) - 1));
        const float m = luminance - c / 2;

        float red;
        float green;
        float blue;

        if (hue < 60) {
            red = c + m;
            green = x + m;
            blue = m;
        }
        else if (hue < 120) {
            red = x + m;
            green = c + m;
            blue = m;
        }
        else if (hue < 180) {
            red = m;
            green = c + m;
            blue = x + m;
        }
        else if (hue < 240) {
            red = m;
            green = x + m;
            blue = c + m;
        }
        else if (hue < 300) {
            red = x + m;
            green = m;
            blue = c + m;
        }
        else {
            red = c + m;
            green = m;
            blue = x + m;
        }

        return {
            static_cast<int>(round(255 * red)),
            static_cast<int>(round(255 * green)),
            static_cast<int>(round(255 * blue)),
            alpha
        };
    }

    ColorHSV ColorHSL::toHSV() const {
        GP_CORE_DEBUG("gp::ColorHSL::toHSV({0})", this->toString());
        const float value = m_Luminance + m_Saturation * (m_Luminance < 0.5 ? m_Luminance : 1 - m_Luminance);
        const float saturation = value == 0 ? 0 : 2 * (1 - m_Luminance / value);

        return {m_Hue, saturation, value, m_Alpha};
    }

    std::string ColorHSL::toString() const {
        if (m_Alpha == 1) {
            return strformat("ColorHSL(%i, %.2f, %.2f)", m_Hue, m_Saturation, m_Luminance);
        }
        return strformat("ColorHSL(%i, %.2f, %.2f, alpha=%.2f)", m_Hue, m_Saturation, m_Luminance, m_Alpha);
    }

    int ColorHSL::getHue() const {
        GP_CORE_TRACE("gp::ColorHSL::getHue()");
        return m_Hue;
    }

    void ColorHSL::setHue(const int value) {
        GP_CORE_DEBUG("gp::ColorHSL::setHue({0})", value);
        m_Hue = value;
        _updateOnlyRGB(toRGB(m_Hue, m_Saturation, m_Luminance));
    }

    float ColorHSL::getSaturation() const {
        GP_CORE_TRACE("gp::ColorHSL::getSaturation()");
        return m_Saturation;
    }

    void ColorHSL::setSaturation(const float value) {
        GP_CORE_DEBUG("gp::ColorHSL::setSaturation({0})", value);
        m_Saturation = value;
        _updateOnlyRGB(toRGB(m_Hue, m_Saturation, m_Luminance));
    }

    float ColorHSL::getLuminance() const {
        GP_CORE_TRACE("gp::ColorHSL::getLuminance()");
        return m_Luminance;
    }

    void ColorHSL::setLuminance(const float value) {
        GP_CORE_DEBUG("gp::ColorHSL::setLuminance({0})", value);
        m_Luminance = value;
        _updateOnlyRGB(toRGB(m_Hue, m_Saturation, m_Luminance));
    }

    void ColorHSL::_updateDerivedClass() {
        GP_CORE_DEBUG("gp::ColorHSL::_update({0})", this->toString());
        const auto hsl = toHSL();

        m_Hue = hsl.m_Hue;
        m_Saturation = hsl.m_Saturation;
        m_Luminance = hsl.m_Luminance;
    }
}
