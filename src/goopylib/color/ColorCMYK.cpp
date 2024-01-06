#include "ColorCMYK.h"
#include "ColorConversions.h"


namespace gp::cmyk {
    RGB toRGB(float cyan, float magenta, float yellow, float key) {
        GP_CORE_INFO("gp::cmyk::toRGB(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

        GP_CHECK_INCLUSIVE_RANGE(cyan, 0, 1, "Color cyan value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(magenta, 0, 1, "Color magenta value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(yellow, 0, 1, "Color yellow value must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(key, 0, 1, "Color key value must be between 0 and 1")

        key = 1 - key;
        return RGB{(int) round(255 * (1 - cyan) * key),
                   (int) round(255 * (1 - magenta) * key),
                   (int) round(255 * (1 - yellow) * key)};
    }

    const char *toHex(float cyan, float magenta, float yellow, float key) {
        GP_CORE_INFO("gp::cmyk::toHex(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

        const RGB color_rgb = toRGB(cyan, magenta, yellow, key);
        return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    HSL toHSL(float cyan, float magenta, float yellow, float key) {
        GP_CORE_INFO("gp::cmyk::toHSL(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

        const RGB color_rgb = toRGB(cyan, magenta, yellow, key);
        return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    HSV toHSV(float cyan, float magenta, float yellow, float key) {
        GP_CORE_INFO("gp::cmyk::toHSV(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

        const RGB color_rgb = toRGB(cyan, magenta, yellow, key);
        return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
    }
}


// Color CMYK Class
namespace gp {
    ColorCMYK::ColorCMYK(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorCMYK::ColorCMYK({0})", color->toString());

        const CMYK data = rgb::toCMYK(m_Red, m_Green, m_Blue);

        m_Cyan = data.cyan;
        m_Magenta = data.magenta;
        m_Yellow = data.yellow;
        m_Key = data.key;
    }

    ColorCMYK::ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha)
            : Color(cmyk::toRGB(cyan, magenta, yellow, key), alpha),
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

    std::string ColorCMYK::toString() const {
        return strformat("ColorCMYK(%g, %g, %g, %g)", m_Cyan, m_Magenta, m_Yellow, m_Key);
    }

    float ColorCMYK::getCyan() const {
        return m_Cyan;
    }

    void ColorCMYK::setCyan(float value) {
        m_Cyan = value;
        const RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    float ColorCMYK::getMagenta() const {
        return m_Magenta;
    }

    void ColorCMYK::setMagenta(float value) {
        m_Magenta = value;
        const RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    float ColorCMYK::getYellow() const {
        return m_Yellow;
    }

    void ColorCMYK::setYellow(float value) {
        m_Yellow = value;
        const RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    float ColorCMYK::getKey() const {
        return m_Key;
    }

    void ColorCMYK::setKey(float value) {
        m_Key = value;
        const RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    void ColorCMYK::_update() {
        auto cmyk = rgb::toCMYK(m_Red, m_Green, m_Blue);

        m_Cyan = cmyk.cyan;
        m_Magenta = cmyk.magenta;
        m_Yellow = cmyk.yellow;
        m_Key = cmyk.key;
    }
}
