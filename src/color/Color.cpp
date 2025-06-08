#define GP_LOGGING_LEVEL 3

#include "Color.h"
#include "ColorRGB.h"
#include "ColorHex.h"
#include "ColorCMYK.h"
#include "ColorHSL.h"
#include "ColorHSV.h"
#include "debug/Error.h"

#define GP_COLOR_CLAMP(arg) arg = std::clamp(arg, 0, 255)
#define GP_COLOR_CLAMPf(arg) std::clamp(arg, 0.0f, 1.0f)
#define GP_COLOR_CLAMP_01(arg) arg = GP_COLOR_CLAMPf(arg)
#define GP_COLOR_CLAMP_RGB GP_COLOR_CLAMP(red); GP_COLOR_CLAMP(green); GP_COLOR_CLAMP(blue)

#define GP_COLOR_NORMALISE(arg) static_cast<float>(arg) / 255.0f


// Color Base Class
namespace gp {
    Color::Color(const int red, const int green, const int blue, const float alpha)
        : m_Red{red},
          m_Green{green},
          m_Blue{blue},
          m_Alpha{alpha},
          m_Redf{GP_COLOR_NORMALISE(red)},
          m_Greenf{GP_COLOR_NORMALISE(green)},
          m_Bluef{GP_COLOR_NORMALISE(blue)} {
        GP_CORE_INFO("gp::Color::Color({0}, {1}, {2}, alpha={3})", red, green, blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    Color::Color(const std::string &hexstring, const float alpha)
        : Color{ColorHex{hexstring, alpha}} {  // NOLINT(*-slicing)
        GP_CORE_INFO("gp::Color::Color({0}, alpha={1})", hexstring, alpha);
    }

    void Color::_updateOnlyRGB(const ColorRGB &color) {
        GP_CORE_DEBUG("gp::Color::updateRGBA(RGB({0}, {1}, {2}), alpha={3})",
                      color.m_Red, color.m_Green, color.m_Blue, color.m_Alpha);

        m_Red = color.m_Red;
        m_Green = color.m_Green;
        m_Blue = color.m_Blue;

        m_Redf = color.m_Redf;
        m_Greenf = color.m_Redf;
        m_Bluef = color.m_Bluef;
    }

    void Color::_clampValues() {
        GP_CORE_DEBUG("gp::Color::update()");

        GP_COLOR_CLAMP(m_Red);
        GP_COLOR_CLAMP(m_Green);
        GP_COLOR_CLAMP(m_Blue);

        GP_COLOR_CLAMP_01(m_Alpha);

        m_Redf = GP_COLOR_NORMALISE(m_Red);
        m_Greenf = GP_COLOR_NORMALISE(m_Green);
        m_Bluef = GP_COLOR_NORMALISE(m_Blue);

        _updateDerivedClass();
    }

    std::string Color::toString() const {
        if (m_Alpha == 1) {
            return strformat("Color(%i, %i, %i)", m_Red, m_Green, m_Blue);
        }
        return strformat("Color(%i, %i, %i, alpha=%.2f)", m_Red, m_Green, m_Blue, m_Alpha);
    }

    int Color::getRed() const {
        GP_CORE_TRACE("gp::Color::getRed()");
        return m_Red;
    }

    void Color::setRed(const int value) {
        GP_CORE_DEBUG("gp::Color::setRed({0})", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color red value must be between 0 and 255")

        m_Red = value;
        m_Redf = GP_COLOR_NORMALISE(value);
        _updateDerivedClass();
    }

    int Color::getGreen() const {
        GP_CORE_TRACE("gp::Color::getGreen()");
        return m_Green;
    }

    void Color::setGreen(const int value) {
        GP_CORE_DEBUG("gp::Color::setGreen({0)", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color green value must be between 0 and 255")

        m_Green = value;
        m_Greenf = GP_COLOR_NORMALISE(value);
        _updateDerivedClass();
    }

    int Color::getBlue() const {
        GP_CORE_TRACE("gp::Color::getBlue()");
        return m_Blue;
    }

    void Color::setBlue(const int value) {
        GP_CORE_DEBUG("gp::Color::setBlue({0})", value);
        GP_CHECK_INCLUSIVE_RANGE(value, 0, 255, "Color blue value must be between 0 and 255")

        m_Blue = value;
        m_Bluef = GP_COLOR_NORMALISE(value);
        _updateDerivedClass();
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
            GP_COLOR_CLAMPf(cyan),
            GP_COLOR_CLAMPf(magenta),
            GP_COLOR_CLAMPf(yellow),
            GP_COLOR_CLAMPf(key),
            m_Alpha,
        };
    }

    ColorHSL Color::toHSL() const {
        GP_CORE_INFO("gp::Color::toHSL({0})", this->toString());

        const auto [cmin, cmax] = std::minmax({m_Redf, m_Greenf, m_Bluef});

        const float delta = cmax - cmin;
        const float luminance = (cmax + cmin) / 2;

        if (delta == 0) {
            return {0, 0, GP_COLOR_CLAMPf(luminance)};
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
            GP_COLOR_CLAMPf(saturation),
            GP_COLOR_CLAMPf(luminance),
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
            GP_COLOR_CLAMPf(saturation),
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

        GP_COLOR_CLAMP_RGB;

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator+(const Color &value) const {
        int red = m_Red + value.m_Red;
        int green = m_Green + value.m_Green;
        int blue = m_Blue + value.m_Blue;

        GP_COLOR_CLAMP_RGB;

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator-(const int value) const {
        int red = m_Red - value;
        int green = m_Green - value;
        int blue = m_Blue - value;

        GP_COLOR_CLAMP_RGB;

        return {red, green, blue, m_Alpha};
    }

    Color Color::operator-(const Color &value) const {
        int red = m_Red - value.m_Red;
        int green = m_Green - value.m_Green;
        int blue = m_Blue - value.m_Blue;

        GP_COLOR_CLAMP_RGB;

        return {red, green, blue, m_Alpha};
    }

    Color &Color::operator+=(const int value) {
        m_Red += value;
        m_Green += value;
        m_Blue += value;

        _clampValues();

        return *this;
    }

    Color &Color::operator+=(const Color &value) {
        m_Red += value.m_Red;
        m_Green += value.m_Green;
        m_Blue += value.m_Blue;

        _clampValues();

        return *this;
    }

    Color &Color::operator-=(const int value) {
        m_Red -= value;
        m_Green -= value;
        m_Blue -= value;

        _clampValues();

        return *this;
    }

    Color &Color::operator-=(const Color &value) {
        m_Red -= value.m_Red;
        m_Green -= value.m_Green;
        m_Blue -= value.m_Blue;

        _clampValues();

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

#undef GP_COLOR_CLAMP_ARG
#undef GP_COLOR_CLAMP_RGB
#undef GP_COLOR_CLAMPf
#undef GP_COLOR_CLAMP
#undef GP_COLOR_CLAMP_01
#undef GP_COLOR_NORMALISE

#define GP_COLOR_SWAP(arg) std::swap(arg, other.arg)
#define GP_COLOR_SWAP_RGBA GP_COLOR_SWAP(m_Red); GP_COLOR_SWAP(m_Green); GP_COLOR_SWAP(m_Blue); GP_COLOR_SWAP(m_Alpha)
#define GP_COLOR_COPY_ASSIGNMENT GP_COLOR_SWAP_RGBA; return *this
#define GP_COLOR_COPY_ASSIGNMENT_OPERATOR(T) Color &Color::operator=(T &other) { GP_COLOR_COPY_ASSIGNMENT; }

#define GP_COLOR_MOVE(arg) arg = std::move(other.arg)
#define GP_COLOR_MOVE_RGBA GP_COLOR_MOVE(m_Red); GP_COLOR_MOVE(m_Green); GP_COLOR_MOVE(m_Blue); GP_COLOR_MOVE(m_Alpha)
#define GP_COLOR_MOVE_ASSIGNMENT GP_COLOR_MOVE_RGBA; return *this;
#define GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(T) Color &Color::operator=(T &&other) noexcept { GP_COLOR_MOVE_ASSIGNMENT }

#define GP_COLOR_MOVE_AND_COPY_OPERATOR(T) GP_COLOR_COPY_ASSIGNMENT_OPERATOR(T) GP_COLOR_MOVE_ASSIGNMENT_OPERATOR(T)

// Move & Copy
namespace gp {
    GP_COLOR_MOVE_AND_COPY_OPERATOR(ColorRGB)
    GP_COLOR_MOVE_AND_COPY_OPERATOR(ColorHex)
    GP_COLOR_MOVE_AND_COPY_OPERATOR(ColorCMYK)
    GP_COLOR_MOVE_AND_COPY_OPERATOR(ColorHSL)
    GP_COLOR_MOVE_AND_COPY_OPERATOR(ColorHSV)
}

#undef GP_COLOR_SWAP
#undef GP_COLOR_SWAP_RGBA
#undef GP_COLOR_COPY_ASSIGNMENT
#undef GP_COLOR_COPY_ASSIGNMENT_OPERATOR

#undef GP_COLOR_MOVE
#undef GP_COLOR_MOVE_RGBA
#undef GP_COLOR_MOVE_ASSIGNMENT
#undef GP_COLOR_MOVE_ASSIGNMENT_OPERATOR

#undef GP_COLOR_MOVE_AND_COPY_OPERATOR
