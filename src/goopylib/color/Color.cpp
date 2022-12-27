#include "Color.h"
#include "ColorConversions.h"

#if !GP_LOG_COLOR
#undef GP_LOGGING_LEVEL
#endif

#include "goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_COLOR
#undef GP_VALUE_CHECKING
#endif

#include "goopylib/debug/Error.h"


// Color Base Class
namespace gp {
    Color::Color(const RGB &color, float alpha) :
            m_Red(color.red),
            m_Green(color.green),
            m_Blue(color.blue),

            m_Alpha(alpha) {
        GP_CORE_INFO("gp::Color::Color(RGB({0}, {1}, {2}), alpha={1})", color.red, color.green, color.blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(color.red, 0, 255, "Color red value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(color.green, 0, 255, "Color green value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(color.blue, 0, 255, "Color blue value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");

        update();
    }

    Color::Color(const Color *color) :
            m_Red(color->m_Red),
            m_Green(color->m_Green),
            m_Blue(color->m_Blue),

            m_Alpha(color->m_Alpha) {
        GP_CORE_INFO("gp::Color::Color({0})", color->toString());
    }

    Color::Color(int red, int green, int blue, float alpha) :
            m_Red(red),
            m_Green(green),
            m_Blue(blue),

            m_Alpha(alpha) {
        GP_CORE_INFO("gp::Color::Color({0}, {1}, {2}, alpha={3})", red, green, blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");

        update();
    }

    Color::Color(const char *hexstring, float alpha)
    : Color(hex::toRGB(hexstring), alpha) {
        GP_CORE_INFO("gp::Color::Color({0}, alpha={3})", hexstring, alpha);
    }

    Color::~Color() {
        GP_CORE_DEBUG("gp::Color::~Color()");
    }

    void Color::fromRGB(const RGB &color, float alpha) {
        GP_CORE_TRACE("gp::Color::fromRGB(RGB({0}, {1}, {2}), alpha={3})", color.red, color.green, color.blue, alpha);

        m_Red = color.red;
        m_Green = color.green;
        m_Blue = color.blue;
        m_Alpha = alpha;

        update();
    }

    void Color::update() {
        GP_CORE_TRACE("gp::Color::update()");

        m_Red = m_Red > 255 ? 255 : (m_Red < 0 ? 0 : m_Red);
        m_Green = m_Green > 255 ? 255 : (m_Green < 0 ? 0 : m_Green);
        m_Blue = m_Blue > 255 ? 255 : (m_Blue < 0 ? 0 : m_Blue);

        m_Alpha = m_Alpha > 1.0f ? 1.0f : (m_Alpha < 0.0f ? 0.0f : m_Alpha);

        m_Redf = (float) m_Red / 255.0f;
        m_Greenf = (float) m_Green / 255.0f;
        m_Bluef = (float) m_Blue / 255.0f;
    }

    std::string Color::toString() const {
        return strformat("Color(%i, %i, %i)", m_Red, m_Green, m_Blue);
    }

    int Color::getRed() const {
        return m_Red;
    }

    void Color::setRed(int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color red value must be between 0 and 255");

        m_Red = value;
        m_Redf = (float) value / 255.0f;
    }

    int Color::getGreen() const {
        return m_Green;
    }

    void Color::setGreen(int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color green value must be between 0 and 255");

        m_Green = value;
        m_Greenf = (float) value / 255.0f;
    }

    int Color::getBlue() const {
        return m_Blue;
    }

    void Color::setBlue(int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color blue value must be between 0 and 255");

        m_Blue = value;
        m_Bluef = (float) value / 255.0f;
    }

    float Color::getAlpha() const {
        return m_Alpha;
    }

    void Color::setAlpha(float value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color alpha value must be between 0 and 1");

        m_Alpha = value;
    }

    float Color::getRedf() const {
        return m_Redf;
    }

    float Color::getGreenf() const {
        return m_Greenf;
    }

    float Color::getBluef() const {
        return m_Bluef;
    }

    RGBAf Color::getRGBAf() const {
        return {m_Redf, m_Greenf, m_Bluef, m_Alpha};
    }
}

// Color Operator Overloading
namespace gp {
    Color Color::operator+(int value) const {
        return {m_Red + value, m_Green + value, m_Blue + value, m_Alpha};
    }

    Color Color::operator+(const Color& value) const {
        return {m_Red + value.m_Red, m_Green + value.m_Green, m_Blue + value.m_Blue, m_Alpha};
    }

    Color Color::operator-(int value) const {
        return {m_Red - value, m_Green - value, m_Blue - value, m_Alpha};
    }

    Color Color::operator-(const Color& value) const {
        return {m_Red - value.m_Red, m_Green - value.m_Green, m_Blue - value.m_Blue, m_Alpha};
    }

    Color &Color::operator+=(int value) {
        m_Red += value;
        m_Green += value;
        m_Blue += value;

        update();

        return *this;
    }

    Color &Color::operator+=(const Color& value) {
        m_Red += value.m_Red;
        m_Green += value.m_Green;
        m_Blue += value.m_Blue;

        update();

        return *this;
    }

    Color &Color::operator-=(int value) {
        m_Red -= value;
        m_Green -= value;
        m_Blue -= value;

        update();

        return *this;
    }

    Color &Color::operator-=(const Color& value) {
        m_Red -= value.m_Red;
        m_Green -= value.m_Green;
        m_Blue -= value.m_Blue;

        update();

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Color& color) {
        return os << color.toString();
    }
}


// Color RGB Class
namespace gp {
    ColorRGB::ColorRGB(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorRGB::ColorRGB({0})", color->toString());
    }

    ColorRGB::ColorRGB(int red, int green, int blue, float alpha)
            : Color(red, green, blue, alpha) {
        GP_CORE_INFO("gp::ColorRGB::ColorRGB({0}, {1}, {2}, alpha={3})", red, green, blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255");
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");
    }
}

// Color Hex Class
namespace gp {
    ColorHex::ColorHex(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorHex::ColorHex{0})", color->toString());
    }

    ColorHex::ColorHex(const char *hexstring, float alpha)
            : Color(hex::toRGB(hexstring), alpha) {
        GP_CORE_INFO("gp::ColorHex::ColorHex({0}, alpha={1})", hexstring, alpha);

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");
    }

    std::string ColorHex::toString() const {
        return {rgb::toHex(m_Red, m_Green, m_Blue)};
    }
}

// Color CMYK Class
namespace gp {
    ColorCMYK::ColorCMYK(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorCMYK::ColorCMYK({0})", color->toString());

        CMYK data = rgb::toCMYK(m_Red, m_Green, m_Blue);

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

        GP_CHECK_INCLUSIVE_RANGE(cyan, 0, 1, "Color cyan value must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(magenta, 0, 1, "Color magenta value must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(yellow, 0, 1, "Color yellow value must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(key, 0, 1, "Color key value must be between 0 and 1");

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");
    }

    std::string ColorCMYK::toString() const {
        return strformat("ColorCMYK(%g, %g, %g, %g)", m_Cyan, m_Magenta, m_Yellow, m_Key);
    }

    float ColorCMYK::getCyan() const {
        return m_Cyan;
    }

    void ColorCMYK::setCyan(float value) {
        m_Cyan = value;
        RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    float ColorCMYK::getMagenta() const {
        return m_Magenta;
    }

    void ColorCMYK::setMagenta(float value) {
        m_Magenta = value;
        RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    float ColorCMYK::getYellow() const {
        return m_Yellow;
    }

    void ColorCMYK::setYellow(float value) {
        m_Yellow = value;
        RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }

    float ColorCMYK::getKey() const {
        return m_Key;
    }

    void ColorCMYK::setKey(float value) {
        m_Key = value;
        RGB data = cmyk::toRGB(m_Cyan, m_Magenta, m_Yellow, m_Key);
        fromRGB(data, m_Alpha);
    }
}

// Color HSV Class
namespace gp {
    ColorHSV::ColorHSV(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorHSV::ColorHSV({0})", color->toString());

        HSV data = rgb::toHSV(m_Red, m_Green, m_Blue);

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

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360");
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1");

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");
    }

    std::string ColorHSV::toString() const {
        return strformat("ColorHSV(%i, %g, %g)", m_Hue, m_Saturation, m_Value);
    }

    int ColorHSV::getHue() const {
        return m_Hue;
    }

    void ColorHSV::setHue(int value) {
        m_Hue = value;
        RGB data = hsv::toRGB(m_Hue, m_Saturation, m_Value);
        fromRGB(data, m_Alpha);
    }

    float ColorHSV::getSaturation() const {
        return m_Saturation;
    }

    void ColorHSV::setSaturation(float value) {
        m_Saturation = value;
        RGB data = hsv::toRGB(m_Hue, m_Saturation, m_Value);
        fromRGB(data, m_Alpha);
    }

    float ColorHSV::getValue() const {
        return m_Value;
    }

    void ColorHSV::setValue(float value) {
        m_Value = value;
        RGB data = hsv::toRGB(m_Hue, m_Saturation, m_Value);
        fromRGB(data, m_Alpha);
    }
}

// Color HSL Class
namespace gp {
    ColorHSL::ColorHSL(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorHSL::ColorHSL({0})", color->toString());

        HSL data = rgb::toHSL(m_Red, m_Green, m_Blue);

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

        GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360");
        GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1");

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1");
    }

    std::string ColorHSL::toString() const {
        return strformat("ColorHSL(%i, %g, %g)", m_Hue, m_Saturation, m_Luminance);
    }

    int ColorHSL::getHue() const {
        return m_Hue;
    }

    void ColorHSL::setHue(int value) {
        m_Hue = value;
        RGB data = hsl::toRGB(m_Hue, m_Saturation, m_Luminance);
        fromRGB(data, m_Alpha);
    }

    float ColorHSL::getSaturation() const {
        return m_Saturation;
    }

    void ColorHSL::setSaturation(float value) {
        m_Saturation = value;
        RGB data = hsl::toRGB(m_Hue, m_Saturation, m_Luminance);
        fromRGB(data, m_Alpha);
    }

    float ColorHSL::getLuminance() const {
        return m_Luminance;
    }

    void ColorHSL::setLuminance(float value) {
        m_Luminance = value;
        RGB data = hsl::toRGB(m_Hue, m_Saturation, m_Luminance);
        fromRGB(data, m_Alpha);
    }
}
