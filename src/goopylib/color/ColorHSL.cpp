#include "ColorHSL.h"
#include "ColorHSV.h"
#include "ColorRGB.h"


namespace gp {
    ColorHSL::ColorHSL(const Color &color)
        : ColorHSL{color.toHSL()} {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0})", color->toString());
    }

    ColorHSL::ColorHSL(int hue, float saturation, float luminance, float alpha)
        : Color{toRGB(hue, saturation, luminance, alpha)},
          m_Hue(hue),
          m_Saturation(saturation),
          m_Luminance(luminance) {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0}, {1}, {2}, alpha={3})", hue, saturation, luminance, alpha);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1")

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    ColorRGB ColorHSL::toRGB() const {
        return toRGB(m_Hue, m_Saturation, m_Luminance, m_Alpha);
    }

    ColorRGB ColorHSL::toRGB(int hue, float saturation, float luminance, float alpha) {
        GP_CORE_INFO("gp::hsl::toRGB(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

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
        const float value = m_Luminance + m_Saturation * (m_Luminance < 0.5 ? m_Luminance : 1 - m_Luminance);
        const float saturation = value == 0 ? 0 : 2 * (1 - m_Luminance / value);

        return {m_Hue, saturation, value, m_Alpha};
    }


    std::string ColorHSL::toString() const {
        return strformat("ColorHSL(%i, %.2f, %.2f)", m_Hue, m_Saturation, m_Luminance);
    }

    int ColorHSL::getHue() const {
        return m_Hue;
    }

    void ColorHSL::setHue(int value) {
        m_Hue = value;
        updateRGBA(toRGB(m_Hue, m_Saturation, m_Luminance));
    }

    float ColorHSL::getSaturation() const {
        return m_Saturation;
    }

    void ColorHSL::setSaturation(float value) {
        m_Saturation = value;
        updateRGBA(toRGB(m_Hue, m_Saturation, m_Luminance));
    }

    float ColorHSL::getLuminance() const {
        return m_Luminance;
    }

    void ColorHSL::setLuminance(float value) {
        m_Luminance = value;
        updateRGBA(toRGB(m_Hue, m_Saturation, m_Luminance));
    }

    void ColorHSL::_update() {
        auto hsl = toHSL();

        m_Hue = hsl.m_Hue;
        m_Saturation = hsl.m_Saturation;
        m_Luminance = hsl.m_Luminance;
    }
}
