#include "ColorHSV.h"
#include "ColorConversions.h"


namespace gp::hsv {
    RGB toRGB(int hue, float saturation, float value) {
        GP_CORE_INFO("gp::hsv::toRGB(hue={0}, saturation={1}, value={2})", hue, saturation, value);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1")

        const float c = value * saturation;
        const float x = c * (1 - fabsf(fmodf((float) hue / 60.0f, 2) - 1));
        const float m = value - c;

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

    const char *toHex(int hue, float saturation, float value) {
        GP_CORE_INFO("gp::hsv::toHex(hue={0}, saturation={1}, value={2})", hue, saturation, value);

        const RGB color_rgb = toRGB(hue, saturation, value);
        return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    CMYK toCMYK(int hue, float saturation, float value) {
        GP_CORE_INFO("gp::hsv::toCMYK(hue={0}, saturation={1}, value={2})", hue, saturation, value);

        const RGB color_rgb = toRGB(hue, saturation, value);
        return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    HSL toHSL(int hue, float saturation, float value) {
        GP_CORE_INFO("gp::hsv::toHSL(hue={0}, saturation={1}, value={2})", hue, saturation, value);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1")

        const float L = value * (1 - saturation / 2);

        if (L == 0 or L == 1) {
            return HSL{hue, 0, L};
        }
        else if (L < 0.5) {
            return HSL{hue, (value - L) / L, L};
        }
        else {
            return HSL{hue, (value - L) / (1 - L), L};
        }
    }
}


namespace gp {
    ColorHSV::ColorHSV(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorHSV::ColorHSV({0})", color->toString());

        const HSV data = rgb::toHSV(m_Red, m_Green, m_Blue);

        m_Hue = data.hue;
        m_Saturation = data.saturation;
        m_Value = data.value;
    }

    ColorHSV::ColorHSV(int hue, float saturation, float value, float alpha)
            : Color(hsv::toRGB(hue, saturation, value), alpha),
              m_Hue(hue),
              m_Saturation(saturation),
              m_Value(value) {
        GP_CORE_INFO("gp::ColorHSV::ColorHSV({0}, {1}, {2}, alpha={3})", hue, saturation, value, alpha);

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360")
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1")

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    std::string ColorHSV::toString() const {
        return strformat("ColorHSV(%i, %g, %g)", m_Hue, m_Saturation, m_Value);
    }

    int ColorHSV::getHue() const {
        return m_Hue;
    }

    void ColorHSV::setHue(int value) {
        m_Hue = value;
        const RGB data = hsv::toRGB(m_Hue, m_Saturation, m_Value);
        fromRGB(data, m_Alpha);
    }

    float ColorHSV::getSaturation() const {
        return m_Saturation;
    }

    void ColorHSV::setSaturation(float value) {
        m_Saturation = value;
        const RGB data = hsv::toRGB(m_Hue, m_Saturation, m_Value);
        fromRGB(data, m_Alpha);
    }

    float ColorHSV::getValue() const {
        return m_Value;
    }

    void ColorHSV::setValue(float value) {
        m_Value = value;
        const RGB data = hsv::toRGB(m_Hue, m_Saturation, m_Value);
        fromRGB(data, m_Alpha);
    }

    void ColorHSV::_update() {
        auto hsv = rgb::toHSV(m_Red, m_Green, m_Blue);

        m_Hue = hsv.hue;
        m_Saturation = hsv.saturation;
        m_Value = hsv.value;
    }
}
