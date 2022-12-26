#include "Color.h"
#include "ColorConversions.h"

#if !GP_LOG_COLOR
#undef GP_LOGGING
#endif

#include "src/goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_COLOR
#undef GP_VALUE_CHECKING
#endif

#include "src/goopylib/debug/Error.h"


template<typename ... Args>
    std::string strformat(const std::string &format, Args ... args) {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size_s <= 0) {
            GP_RUNTIME_ERROR("Error during string formatting, {0}", format);
        }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
    }


// Color Base Class
namespace gp {
    Color::Color(const RGB &color, float alpha) :
            m_Red(color.red),
            m_Green(color.green),
            m_Blue(color.blue),

            m_Alpha(alpha) {
        GP_CORE_TRACE_ALL("Initializing Color() from struct", alpha);
        update();
    }

    Color::Color(const Color *color) :
            m_Red(color->m_Red),
            m_Green(color->m_Green),
            m_Blue(color->m_Blue),

            m_Alpha(color->m_Alpha) {
        GP_CORE_TRACE_ALL("Initializing Color() from {0}", color->toString());
    }

    Color::Color(int red, int green, int blue, float alpha) :
            m_Red(red),
            m_Green(green),
            m_Blue(blue),

            m_Alpha(alpha) {
        GP_CORE_TRACE_ALL("Initializing Color({0}, {1}, {2}, {3})", red, green, blue, alpha);
        update();
    }

    Color::~Color() {
        GP_CORE_TRACE_ALL("Deallocating Color");
    }

    void Color::fromRGB(const RGB &color, float alpha) {
        m_Red = color.red;
        m_Green = color.green;
        m_Blue = color.blue;
        m_Alpha = alpha;

        update();
    }

    void Color::update() {
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

    void Color::setRed(int red) {
        m_Red = red > 255 ? 255 : (red < 0 ? 0 : red);
        m_Redf = (float) red / 255.0f;
    }

    int Color::getGreen() const {
        return m_Green;
    }

    void Color::setGreen(int green) {
        m_Green = green > 255 ? 255 : (green < 0 ? 0 : green);
        m_Greenf = (float) green / 255.0f;
    }

    int Color::getBlue() const {
        return m_Blue;
    }

    void Color::setBlue(int blue) {
        m_Blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);
        m_Bluef = (float) blue / 255.0f;
    }

    float Color::getAlpha() const {
        return m_Alpha;
    }

    void Color::setAlpha(float alpha) {
        m_Alpha = alpha > 1.0f ? 1.0f : (alpha < 0.0f ? 0.0f : alpha);
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
        GP_CORE_TRACE_ALL("Initializing ColorRGB() from {0}", color->toString());
    }

    ColorRGB::ColorRGB(int red, int green, int blue, float alpha)
            : Color(red, green, blue, alpha) {
        GP_CORE_TRACE_ALL("Initializing ColorRGBA({0}, {1}, {2}, {3})", red, green, blue, alpha);
    }
}

// Color Hex Class
namespace gp {
    ColorHex::ColorHex(const Color *color)
            : Color(*color),
              m_String(rgb::toHex(color->getRed(), color->getGreen(), color->getBlue())) {
        GP_CORE_TRACE_ALL("Initializing ColorHex() from {0}", color->toString());
    }

    ColorHex::ColorHex(const char *hexstring, float alpha)
            : Color(hex::toRGB(hexstring), alpha),
              m_String(hexstring) {
        GP_CORE_TRACE_ALL("Initializing ColorHex({0}, {1})", hexstring, alpha);
    }

    std::string ColorHex::toString() const {
        return {m_String};
    }
}

// Color CMYK Class
namespace gp {
    ColorCMYK::ColorCMYK(const Color *color)
            : Color(*color) {
        GP_CORE_TRACE_ALL("Initializing ColorCMYK() from {0}", color.toString());

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
        GP_CORE_TRACE_ALL("Initializing ColorCMYK({0}, {1}, {2}, {3}, {4})", cyan, magenta, yellow, key, alpha);
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
        GP_CORE_TRACE_ALL("Initializing ColorHSV() from {0}", color->toString());

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
        GP_CORE_TRACE_ALL("Initializing ColorHSV({0}, {1}, {2}, {3})", hue, saturation, value, alpha);
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
        GP_CORE_TRACE_ALL("Initializing ColorHSL() from {0}", color->toString());

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
        GP_CORE_TRACE_ALL("Initializing ColorHSL({0}, {1}, {2}, {3})", hue, saturation, luminance, alpha);
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
