#define GP_LOGGING_LEVEL 3

#include "Color.h"
#include "ColorConversions.h"


// Color Base Class
namespace gp {
    Color::Color(const RGB &color, float alpha) :
            m_Red(color.red),
            m_Green(color.green),
            m_Blue(color.blue),

            m_Alpha(alpha) {
        GP_CORE_INFO("gp::Color::Color(RGB({0}, {1}, {2}), alpha={1})", color.red, color.green, color.blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(color.red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(color.green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(color.blue, 0, 255, "Color blue value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")

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

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")

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

        _update();
    }

    std::string Color::toString() const {
        return strformat("Color(%i, %i, %i)", m_Red, m_Green, m_Blue);
    }

    int Color::getRed() const {
        return m_Red;
    }

    void Color::setRed(int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color red value must be between 0 and 255")

        m_Red = value;
        m_Redf = (float) value / 255.0f;
        _update();
    }

    int Color::getGreen() const {
        return m_Green;
    }

    void Color::setGreen(int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color green value must be between 0 and 255")

        m_Green = value;
        m_Greenf = (float) value / 255.0f;
        _update();
    }

    int Color::getBlue() const {
        return m_Blue;
    }

    void Color::setBlue(int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color blue value must be between 0 and 255")

        m_Blue = value;
        m_Bluef = (float) value / 255.0f;
        _update();
    }

    float Color::getAlpha() const {
        return m_Alpha;
    }

    void Color::setAlpha(float value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color alpha value must be between 0 and 1")

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
