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
        : Color{ColorHex{hexstring, alpha}} { // NOLINT(*-slicing)
        GP_CORE_INFO("gp::Color::Color({0}, alpha={1})", hexstring, alpha);
    }

    void Color::updateRGBA(const ColorRGB &color) {
        GP_CORE_DEBUG("gp::Color::updateRGBA(RGB({0}, {1}, {2}), alpha={3})",
                      color.m_Red, color.m_Green, color.m_Blue, color.m_Alpha);

        m_Red = color.m_Red;
        m_Green = color.m_Green;
        m_Blue = color.m_Blue;
        m_Alpha = color.m_Alpha;

        update();
    }

    void Color::update() {
        GP_CORE_DEBUG("gp::Color::update()");

        m_Red = m_Red > 255 ? 255 : m_Red < 0 ? 0 : m_Red;
        m_Green = m_Green > 255 ? 255 : m_Green < 0 ? 0 : m_Green;
        m_Blue = m_Blue > 255 ? 255 : m_Blue < 0 ? 0 : m_Blue;

        m_Alpha = m_Alpha > 1.0f ? 1.0f : m_Alpha < 0.0f ? 0.0f : m_Alpha;

        m_Redf = static_cast<float>(m_Red) / 255.0f;
        m_Greenf = static_cast<float>(m_Green) / 255.0f;
        m_Bluef = static_cast<float>(m_Blue) / 255.0f;

        _update();
    }

    std::string Color::toString() const {
        GP_CORE_TRACE("gp::Color::toString()");
        return strformat("Color(%i, %i, %i, %.2f)", m_Red, m_Green, m_Blue, m_Alpha);
    }

    int Color::getRed() const {
        GP_CORE_TRACE("gp::Color::getRed()");
        return m_Red;
    }

    void Color::setRed(const int value) {
        GP_CORE_DEBUG("gp::Color::setRed({0})", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color red value must be between 0 and 255")

        m_Red = value;
        m_Redf = static_cast<float>(value) / 255.0f;
        _update();
    }

    int Color::getGreen() const {
        GP_CORE_TRACE("gp::Color::getGreen()");
        return m_Green;
    }

    void Color::setGreen(const int value) {
        GP_CORE_DEBUG("gp::Color::setGreen({0)", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color green value must be between 0 and 255")

        m_Green = value;
        m_Greenf = static_cast<float>(value) / 255.0f;
        _update();
    }

    int Color::getBlue() const {
        GP_CORE_TRACE("gp::Color::getBlue()");
        return m_Blue;
    }

    void Color::setBlue(const int value) {
        GP_CORE_DEBUG("gp::Color::setBlue({0})", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color blue value must be between 0 and 255")

        m_Blue = value;
        m_Bluef = static_cast<float>(value) / 255.0f;
        _update();
    }

    float Color::getAlpha() const {
        GP_CORE_TRACE("gp::Color::getAlpha()");
        return m_Alpha;
    }

    void Color::setAlpha(const float value) {
        GP_CORE_DEBUG("gp::Color::setAlpha({0})", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color alpha value must be between 0 and 1")

        m_Alpha = value;
    }

    float Color::getRedf() const {
        GP_CORE_TRACE("gp::Color::getRedf()");
        return m_Redf;
    }

    float Color::getGreenf() const {
        GP_CORE_TRACE("gp::Color::getGreenf()");
        return m_Greenf;
    }

    float Color::getBluef() const {
        GP_CORE_TRACE("gp::Color::getBluef()");
        return m_Bluef;
    }

    RGBAf Color::getRGBAf() const {
        GP_CORE_TRACE_ALL("gp::Color::getRGBAf()");
        return {m_Redf, m_Greenf, m_Bluef, m_Alpha};
    }
}

// Color Conversion Methods
namespace gp {
    ColorRGB Color::toRGB() const {
        GP_CORE_DEBUG("gp::Color::toRGB({0})", this->toString());
        return ColorRGB{*this}; // copy constructor of ColorRGB
    }

    ColorHex Color::toHex() const {
        GP_CORE_DEBUG("gp::Color::toHex({0})", this->toString());
        return {strformat("#%02x%02x%02x", m_Red, m_Green, m_Blue), m_Alpha};
    }

    ColorCMYK Color::toCMYK() const {
        GP_CORE_INFO("gp::Color::toCMYK({0})", this->toString());

        const float maximum = std::max({m_Redf, m_Greenf, m_Bluef});

        if (maximum == 0) {
            return {0, 0, 0, 1};
        }

        const float cyan = (maximum - m_Redf) / maximum;
        const float magenta = (maximum - m_Greenf) / maximum;
        const float yellow = (maximum - m_Bluef) / maximum;
        const float key = 1 - maximum;

        return {
            std::clamp(cyan, 0.0f, 1.0f),
            std::clamp(magenta, 0.0f, 1.0f),
            std::clamp(yellow, 0.0f, 1.0f),
            std::clamp(key, 0.0f, 1.0f),
            m_Alpha,
        };
    }

    ColorHSL Color::toHSL() const {
        GP_CORE_INFO("gp::Color::toHSL({0})", this->toString());

        const auto [cmin, cmax] = std::minmax({m_Redf, m_Greenf, m_Bluef});

        const float delta = cmax - cmin;
        const float luminance = (cmax + cmin) / 2;

        if (delta == 0) {
            return {0, 0, std::clamp(luminance, 0.0f, 1.0f)};
        }

        const float saturation = delta / (1 - abs(2 * luminance - 1));

        float hue;

        if (cmax == m_Redf) {
            hue = fmodf((m_Greenf - m_Bluef) / delta, 6);
        }
        else if (cmax == m_Greenf) {
            hue = (m_Bluef - m_Redf) / delta + 2;
        }
        else {
            hue = (m_Redf - m_Greenf) / delta + 4;
        }

        return {
            std::clamp(static_cast<int>(round(60 * hue)), 0, 360),
            std::clamp(saturation, 0.0f, 1.0f),
            std::clamp(luminance, 0.0f, 1.0f),
            m_Alpha,
        };
    }

    ColorHSV Color::toHSV() const {
        GP_CORE_INFO("gp::Color::toHSV({0})", this->toString());

        const auto [cmin, cmax] = std::minmax({m_Redf, m_Greenf, m_Bluef});

        const float delta = cmax - cmin;
        const float saturation = cmax == 0 ? 0 : delta / cmax;

        float hue;

        if (delta == 0) {
            hue = 0;
        }
        else if (cmax == m_Redf) {
            hue = fmodf((m_Greenf - m_Bluef) / delta, 6);
        }
        else if (cmax == m_Greenf) {
            hue = (m_Bluef - m_Redf) / delta + 2;
        }
        else {
            hue = (m_Redf - m_Greenf) / delta + 4;
        }

        return {
            static_cast<int>(round(60 * hue)),
            std::clamp(saturation, 0.0f, 1.0f),
            cmax,
            m_Alpha,
        };
    }
}

// Color Operator Overloading
namespace gp {
    Color Color::operator+(const int value) const {
        int red = m_Red + value;
        int green = m_Green + value;
        int blue = m_Blue + value;

        red = red > 255 ? 255 : red < 0 ? 0 : red;
        green = green > 255 ? 255 : green < 0 ? 0 : green;
        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator+(const Color &value) const {
        int red = m_Red + value.m_Red;
        int green = m_Green + value.m_Green;
        int blue = m_Blue + value.m_Blue;

        red = red > 255 ? 255 : red < 0 ? 0 : red;
        green = green > 255 ? 255 : green < 0 ? 0 : green;
        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator-(const int value) const {
        int red = m_Red - value;
        int green = m_Green - value;
        int blue = m_Blue - value;

        red = red > 255 ? 255 : red < 0 ? 0 : red;
        green = green > 255 ? 255 : green < 0 ? 0 : green;
        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator-(const Color &value) const {
        int red = m_Red - value.m_Red;
        int green = m_Green - value.m_Green;
        int blue = m_Blue - value.m_Blue;

        red = red > 255 ? 255 : red < 0 ? 0 : red;
        green = green > 255 ? 255 : green < 0 ? 0 : green;
        blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;

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

    bool Color::operator==(const std::string &other) const {
        return *this == ColorHex(other);
    }

    std::ostream &operator<<(std::ostream &os, const Color &color) {
        return os << color.toString();
    }

    std::string RGBAf::toString() const {
        return strformat("RGBAf(%i, %i, %i, %.2f)", red, green, blue, alpha);
    }

    std::string RGBf::toString() const {
        return strformat("RGBAf(%i, %i, %i)", red, green, blue);
    }

    std::ostream &operator<<(std::ostream &os, const RGBAf &color) {
        return os << color.toString();
    }

    std::ostream &operator<<(std::ostream &os, const RGBf &color) {
        return os << color.toString();
    }
}

#define GP_COLOR_SWAP(arg) std::swap(arg, other.arg)
#define GP_COLOR_SWAP_RGBA GP_COLOR_SWAP(m_Red); GP_COLOR_SWAP(m_Green); GP_COLOR_SWAP(m_Blue); GP_COLOR_SWAP(m_Alpha)
#define GP_COLOR_COPY_ASSIGNMENT GP_COLOR_SWAP_RGBA; return *this
#define GP_COLOR_COPY_ASSIGNMENT_OPERATOR(T) Color &Color::operator=(T &other) { GP_COLOR_COPY_ASSIGNMENT; }

#define GP_COLOR_MOVE(arg) arg = std::move(other.arg)
#define GP_COLOR_MOVE_RGBA GP_COLOR_MOVE(m_Red); GP_COLOR_MOVE(m_Green); GP_COLOR_MOVE(m_Blue); GP_COLOR_MOVE(m_Alpha)
#define GP_COLOR_MOVE_ASSIGNMENT GP_COLOR_MOVE_RGBA; return *this;
#define GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(T) Color &Color::operator=(T &&other) noexcept { GP_COLOR_MOVE_ASSIGNMENT }

// Move & Copy
namespace gp {
    GP_COLOR_COPY_ASSIGNMENT_OPERATOR(ColorRGB)
    GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(ColorRGB)

    GP_COLOR_COPY_ASSIGNMENT_OPERATOR(ColorHex)
    GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(ColorHex)

    GP_COLOR_COPY_ASSIGNMENT_OPERATOR(ColorCMYK)
    GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(ColorCMYK)

    GP_COLOR_COPY_ASSIGNMENT_OPERATOR(ColorHSL)
    GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(ColorHSL)

    GP_COLOR_COPY_ASSIGNMENT_OPERATOR(ColorHSV)
    GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(ColorHSV)
}

#undef GP_COLOR_SWAP
#undef GP_COLOR_SWAP_RGBA
#undef GP_COLOR_COPY_ASSIGNMENT
#undef GP_COLOR_COPY_ASSIGNMENT_OPERATOR
