#define GP_LOGGING_LEVEL 3

#include "ColorHSV.h"
#include "ColorHSL.h"
#include "ColorRGB.h"
#include "debug/Error.h"


namespace gp {
    ColorHSV::ColorHSV(const Color &color)
        : ColorHSV{color.toHSV()} {
        GP_CORE_INFO("gp::ColorHSV::ColorHSV({0})", color->toString());
    }

    ColorHSV::ColorHSV(const int hue, const float saturation, const float value, const float alpha)
        : Color{toRGB(hue, saturation, value, alpha)},
          m_Hue(hue),
          m_Saturation(saturation),
          m_Value(value) {
        GP_CORE_INFO("gp::ColorHSV::ColorHSV({0}, {1}, {2}, alpha={3})", hue, saturation, value, alpha);

        // Alpha value is checked in gp::Color constructor
        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1")
    }

    ColorRGB ColorHSV::toRGB() const {
        GP_CORE_TRACE("gp::ColorHSV::toRGB({0})", this->toString());
        return toRGB(m_Hue, m_Saturation, m_Value, m_Alpha);
    }

    ColorRGB ColorHSV::toRGB(const int hue, const float saturation, const float value, float alpha) {
        GP_CORE_DEBUG("gp::ColorHSV::toRGB({0}, {1}, {2}, alpha={3})", hue, saturation, value, alpha);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1")

        const float c = value * saturation;
        const float x = c * (1 - fabsf(fmodf(static_cast<float>(hue) / 60.0f, 2) - 1));
        const float m = value - c;

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
            alpha,
        };
    }

    ColorHSL ColorHSV::toHSL() const {
        GP_CORE_DEBUG("gp::ColorHSV::toHSL({0})", this->toString());
        const float luminance = m_Value * (1 - m_Saturation / 2);
        float saturation;

        if (luminance == 0 or luminance == 1) {
            saturation = 0;
        }
        else if (luminance < 0.5) {
            saturation = (m_Value - luminance) / luminance;
        }
        else {
            saturation = (m_Value - luminance) / (1 - luminance);
        }
        return {m_Hue, saturation, luminance, m_Alpha};
    }

    std::string ColorHSV::toString() const {
        if (m_Alpha == 1) {
            return strformat("ColorHSV(%i, %.2f, %.2f)", m_Hue, m_Saturation, m_Value);
        }
        return strformat("ColorHSV(%i, %.2f, %.2f, alpha=%.2f)", m_Hue, m_Saturation, m_Value, m_Alpha);
    }

    int ColorHSV::getHue() const {
        GP_CORE_TRACE("gp::ColorHSV::getHue()");
        return m_Hue;
    }

    void ColorHSV::setHue(const int value) {
        GP_CORE_DEBUG("gp::ColorHSV::setHue({0})", value);
        m_Hue = value;
        _updateOnlyRGB(toRGB(m_Hue, m_Saturation, m_Value));
    }

    float ColorHSV::getSaturation() const {
        GP_CORE_TRACE("gp::ColorHSV::getSaturation()");
        return m_Saturation;
    }

    void ColorHSV::setSaturation(const float value) {
        GP_CORE_DEBUG("gp::ColorHSV::setSaturation({0})", value);
        m_Saturation = value;
        _updateOnlyRGB(toRGB(m_Hue, m_Saturation, m_Value));
    }

    float ColorHSV::getValue() const {
        GP_CORE_TRACE("gp::ColorHSV::getValue()");
        return m_Value;
    }

    void ColorHSV::setValue(const float value) {
        GP_CORE_DEBUG("gp::ColorHSV::setValue({0})", value);
        m_Value = value;
        _updateOnlyRGB(toRGB(m_Hue, m_Saturation, m_Value));
    }

    void ColorHSV::_updateDerivedClass() {
        GP_CORE_DEBUG("gp::ColorHSV::_update({0})", this->toString());
        const auto hsv = toHSV();

        m_Hue = hsv.m_Hue;
        m_Saturation = hsv.m_Saturation;
        m_Value = hsv.m_Value;
    }
}
