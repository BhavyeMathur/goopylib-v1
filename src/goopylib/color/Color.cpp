#define GP_LOGGING_LEVEL 3

#include "Color.h"
#include "ColorRGB.h"
#include "ColorHex.h"
#include "ColorCMYK.h"
#include "ColorHSL.h"
#include "ColorHSV.h"


// Color Base Class
namespace gp {
    Color::Color(const int red, const int green, const int blue, const float alpha)
        : m_Red{red},
          m_Green{green},
          m_Blue{blue},
          m_Alpha{alpha},
          m_Redf{static_cast<float>(m_Red) / 255.0f},
          m_Greenf{static_cast<float>(m_Green) / 255.0f},
          m_Bluef{static_cast<float>(m_Blue) / 255.0f} {
        GP_CORE_INFO("gp::Color::Color({0}, {1}, {2}, alpha={3})", red, green, blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    Color::Color(const std::string &hexstring, const float alpha)
        : Color{ColorHex{hexstring, alpha}} {
        GP_CORE_INFO("gp::Color::Color({0}, alpha={3})", hexstring, alpha);
    }

    void Color::updateRGBA(const ColorRGB &color) {
        GP_CORE_TRACE("gp::Color::updateRGBA(RGB({0}, {1}, {2}), alpha={3})",
                      color.m_Red, color.m_Green, color.m_Blue, color.m_Alpha);

        m_Red = color.m_Red;
        m_Green = color.m_Green;
        m_Blue = color.m_Blue;
        m_Alpha = color.m_Alpha;

        update();
    }

    void Color::update() {
        GP_CORE_TRACE("gp::Color::update()");

        m_Red = m_Red > 255 ? 255 : (m_Red < 0 ? 0 : m_Red);
        m_Green = m_Green > 255 ? 255 : (m_Green < 0 ? 0 : m_Green);
        m_Blue = m_Blue > 255 ? 255 : (m_Blue < 0 ? 0 : m_Blue);

        m_Alpha = m_Alpha > 1.0f ? 1.0f : (m_Alpha < 0.0f ? 0.0f : m_Alpha);

        m_Redf = static_cast<float>(m_Red) / 255.0f;
        m_Greenf = static_cast<float>(m_Green) / 255.0f;
        m_Bluef = static_cast<float>(m_Blue) / 255.0f;

        _update();
    }

    std::string Color::toString() const {
        return strformat("Color(%i, %i, %i, %.2f)", m_Red, m_Green, m_Blue, m_Alpha);
    }

    int Color::getRed() const {
        return m_Red;
    }

    void Color::setRed(const int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color red value must be between 0 and 255")

        m_Red = value;
        m_Redf = static_cast<float>(value) / 255.0f;
        _update();
    }

    int Color::getGreen() const {
        return m_Green;
    }

    void Color::setGreen(const int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color green value must be between 0 and 255")

        m_Green = value;
        m_Greenf = static_cast<float>(value) / 255.0f;
        _update();
    }

    int Color::getBlue() const {
        return m_Blue;
    }

    void Color::setBlue(const int value) {
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color blue value must be between 0 and 255")

        m_Blue = value;
        m_Bluef = static_cast<float>(value) / 255.0f;
        _update();
    }

    float Color::getAlpha() const {
        return m_Alpha;
    }

    void Color::setAlpha(const float value) {
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

// Color Conversion Methods
namespace gp {
    ColorRGB Color::toRGB() const {
        return *this; // copy constructor of ColorRGB
    }

    ColorHex Color::toHex() const {
        GP_CORE_INFO("gp::Color::toHex({0})", this.toString());
        return strformat("#%02x%02x%02x", m_Red, m_Green, m_Blue);
    }

    ColorCMYK Color::toCMYK() const {
        GP_CORE_INFO("gp::Color::toCMYK({0})", this.toString());

        const float maximum = std::max({m_Redf, m_Greenf, m_Bluef});

        if (maximum == 0) {
            return {0, 0, 0, 1};
        }

        return {
            (maximum - m_Redf) / maximum,
            (maximum - m_Greenf) / maximum,
            (maximum - m_Bluef) / maximum,
            1 - maximum
        };
    }

    ColorHSL Color::toHSL() const {
        GP_CORE_INFO("gp::Color::toHSL({0})", this.toString());

        const auto [cmin, cmax] = std::minmax({m_Redf, m_Greenf, m_Bluef});

        const float delta = cmax - cmin;
        const float luminance = (cmax + cmin) / 2;

        if (delta == 0) {
            return {0, 0, luminance};
        }

        const float saturation = delta / (1 - abs(2 * luminance - 1));

        if (cmax == m_Redf) {
            return {static_cast<int>(round(60 * fmodf((m_Greenf - m_Bluef) / delta, 6))), saturation, luminance};
        }
        if (cmax == m_Greenf) {
            return {static_cast<int>(round(60 * ((m_Bluef - m_Redf) / delta + 2))), saturation, luminance};
        }
        // cmax == m_Bluef
        return {static_cast<int>(round(60 * ((m_Redf - m_Greenf) / delta + 4))), saturation, luminance};
    }

    ColorHSV Color::toHSV() const {
        GP_CORE_INFO("gp::Color::toHSV({0})", this.toString());

        const auto [cmin, cmax] = std::minmax({m_Redf, m_Greenf, m_Bluef});

        const float delta = cmax - cmin;
        const float saturation = cmax == 0 ? 0 : delta / cmax;

        if (delta == 0) {
            return {0, saturation, cmax};
        }
        if (cmax == m_Redf) {
            return {static_cast<int>(round(60 * fmodf((m_Greenf - m_Bluef) / delta, 6))), saturation, cmax};
        }
        if (cmax == m_Greenf) {
            return {static_cast<int>(round(60 * ((m_Bluef - m_Redf) / delta + 2))), saturation, cmax};
        }
        // cmax == m_Bluef
        return {static_cast<int>(round(60 * ((m_Redf - m_Greenf) / delta + 4))), saturation, cmax};
    }
}

// Color Operator Overloading
namespace gp {
    Color Color::operator+(const int value) const {
        int red = m_Red + value;
        int green = m_Green + value;
        int blue = m_Blue + value;

        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator+(const Color &value) const {
        int red = m_Red + value.m_Red;
        int green = m_Green + value.m_Green;
        int blue = m_Blue + value.m_Blue;

        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator-(const int value) const {
        int red = m_Red - value;
        int green = m_Green - value;
        int blue = m_Blue - value;

        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator-(const Color &value) const {
        int red = m_Red - value.m_Red;
        int green = m_Green - value.m_Green;
        int blue = m_Blue - value.m_Blue;

        red = red > 255 ? 255 : (red < 0 ? 0 : red);
        green = green > 255 ? 255 : (green < 0 ? 0 : green);
        blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

        return {red, green, blue, m_Alpha};
    }

    Color &Color::operator+=(const int value) {
        m_Red += value;
        m_Green += value;
        m_Blue += value;

        update();

        return *this;
    }

    Color &Color::operator+=(const Color &value) {
        m_Red += value.m_Red;
        m_Green += value.m_Green;
        m_Blue += value.m_Blue;

        update();

        return *this;
    }

    Color &Color::operator-=(const int value) {
        m_Red -= value;
        m_Green -= value;
        m_Blue -= value;

        update();

        return *this;
    }

    Color &Color::operator-=(const Color &value) {
        m_Red -= value.m_Red;
        m_Green -= value.m_Green;
        m_Blue -= value.m_Blue;

        update();

        return *this;
    }

    bool Color::operator==(std::string other) const {
        return *this == ColorHex(other);
    }

    std::ostream &operator<<(std::ostream &os, const Color &color) {
        return os << color.toString();
    }
}
