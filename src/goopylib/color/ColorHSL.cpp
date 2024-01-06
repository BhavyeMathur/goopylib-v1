#include "ColorHSL.h"
#include "ColorConversions.h"


namespace gp::hsl {
    RGB toRGB(int hue, float saturation, float luminance) {
        GP_CORE_INFO("gp::hsl::toRGB(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1")

        const float c = (1 - fabsf(2 * luminance - 1)) * saturation;
        const float x = c * (1 - fabsf(fmodf((float) hue / 60, 2) - 1));
        const float m = luminance - c / 2;

        if (hue < 60) {
            return RGB{(int) round(255 * (c + m)),
                       (int) round(255 * (x + m)),
                       (int) round(255 * m)};
        }
        else if (hue < 120) {
            return RGB{(int) round(255 * (x + m)),
                       (int) round(255 * (c + m)),
                       (int) round(255 * m)};
        }
        else if (hue < 180) {
            return RGB{(int) round(255 * m),
                       (int) round(255 * (c + m)),
                       (int) round(255 * (x + m))};
        }
        else if (hue < 240) {
            return RGB{(int) round(255 * m),
                       (int) round(255 * (x + m)),
                       (int) round(255 * (c + m))};
        }
        else if (hue < 300) {
            return RGB{(int) round(255 * (x + m)),
                       (int) round(255 * m),
                       (int) round(255 * (c + m))};
        }
        else {
            return RGB{(int) round(255 * (c + m)),
                       (int) round(255 * m),
                       (int) round(255 * (x + m))};
        }
    }

    const char *toHex(int hue, float saturation, float luminance) {
        GP_CORE_INFO("gp::hsl::toHex(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

        const RGB color_rgb = toRGB(hue, saturation, luminance);
        return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    CMYK toCMYK(int hue, float saturation, float luminance) {
        GP_CORE_INFO("gp::hsl::toCMYK(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

        const RGB color_rgb = toRGB(hue, saturation, luminance);
        return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    HSV toHSV(int hue, float saturation, float luminance) {
        GP_CORE_INFO("gp::hsl::toHSV(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1")

        const float v = luminance + saturation * (luminance < 0.5 ? luminance : 1 - luminance);

        saturation = v == 0 ? 0 : 2 * (1 - luminance / v);

        return HSV{hue, saturation, v};
    }
}


namespace gp {
    ColorHSL::ColorHSL(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0})", color->toString());

        const HSL data = rgb::toHSL(m_Red, m_Green, m_Blue);

        m_Hue = data.hue;
        m_Saturation = data.saturation;
        m_Luminance = data.luminance;
    }

    ColorHSL::ColorHSL(int hue, float saturation, float luminance, float alpha)
            : Color(hsl::toRGB(hue, saturation, luminance), alpha),
              m_Hue(hue),
              m_Saturation(saturation),
              m_Luminance(luminance) {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0}, {1}, {2}, alpha={3})", hue, saturation, luminance, alpha);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1")

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    std::string ColorHSL::toString() const {
        return strformat("ColorHSL(%i, %g, %g)", m_Hue, m_Saturation, m_Luminance);
    }

    int ColorHSL::getHue() const {
        return m_Hue;
    }

    void ColorHSL::setHue(int value) {
        m_Hue = value;
        const RGB data = hsl::toRGB(m_Hue, m_Saturation, m_Luminance);
        fromRGB(data, m_Alpha);
    }

    float ColorHSL::getSaturation() const {
        return m_Saturation;
    }

    void ColorHSL::setSaturation(float value) {
        m_Saturation = value;
        const RGB data = hsl::toRGB(m_Hue, m_Saturation, m_Luminance);
        fromRGB(data, m_Alpha);
    }

    float ColorHSL::getLuminance() const {
        return m_Luminance;
    }

    void ColorHSL::setLuminance(float value) {
        m_Luminance = value;
        const RGB data = hsl::toRGB(m_Hue, m_Saturation, m_Luminance);
        fromRGB(data, m_Alpha);
    }

    void ColorHSL::_update() {
        auto hsl = rgb::toHSL(m_Red, m_Green, m_Blue);

        m_Hue = hsl.hue;
        m_Saturation = hsl.saturation;
        m_Luminance = hsl.luminance;
    }
}
