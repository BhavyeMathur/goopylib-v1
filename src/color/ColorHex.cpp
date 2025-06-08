#define GP_LOGGING_LEVEL 3

#include "ColorHex.h"
#include "ColorRGB.h"
#include "debug/Error.h"

namespace gp {
    int ColorHex::_digitToInt(char digit) {
        GP_CORE_TRACE_ALL("gp::ColorHex::_digitToInt({0})", digit);

        if (isdigit(digit)) {
            return digit - '0';
        }

        switch (digit) {
            case 'a':
            case 'A':
                return 10;
            case 'b':
            case 'B':
                return 11;
            case 'c':
            case 'C':
                return 12;
            case 'd':
            case 'D':
                return 13;
            case 'e':
            case 'E':
                return 14;
            case 'f':
            case 'F':
                return 15;
            default:
                GP_VALUE_ERROR("gp::ColorHex::_digitToInt() invalid hexstring character '{0}'", digit);
                return 0;
        }
    }

    ColorRGB ColorHex::_3toRGB(const std::string &hexstring, const float alpha) {
        GP_CORE_TRACE("gp::ColorHex::_3toRGB({0}, {1})", hexstring, alpha);

        return {
            17 * _digitToInt(hexstring[0]),
            17 * _digitToInt(hexstring[1]),
            17 * _digitToInt(hexstring[2]),
            alpha
        };
    }

    ColorRGB ColorHex::_4toRGB(const std::string &hexstring, const float alpha) {
        GP_CORE_TRACE("gp::ColorHex::_4toRGB({0}, {1})", hexstring, alpha);

        return {
            17 * _digitToInt(hexstring[1]),
            17 * _digitToInt(hexstring[2]),
            17 * _digitToInt(hexstring[3]),
            alpha
        };
    }

    ColorRGB ColorHex::_6toRGB(const std::string &hexstring, const float alpha) {
        GP_CORE_TRACE("gp::ColorHex::_6toRGB({0}, {1})", hexstring, alpha);

        return {
            16 * _digitToInt(hexstring[0]) + _digitToInt(hexstring[1]),
            16 * _digitToInt(hexstring[2]) + _digitToInt(hexstring[3]),
            16 * _digitToInt(hexstring[4]) + _digitToInt(hexstring[5]),
            alpha
        };
    }

    ColorRGB ColorHex::_7toRGB(const std::string &hexstring, const float alpha) {
        GP_CORE_TRACE("gp::ColorHex::_7toRGB({0}, {1})", hexstring, alpha);

        return {
            16 * _digitToInt(hexstring[1]) + _digitToInt(hexstring[2]),
            16 * _digitToInt(hexstring[3]) + _digitToInt(hexstring[4]),
            16 * _digitToInt(hexstring[5]) + _digitToInt(hexstring[6]),
            alpha
        };
    }
}

namespace gp {
    ColorHex::ColorHex(const Color &color)
        : Color{color} {
        GP_CORE_INFO("gp::ColorHex::ColorHex{0})", color->toString());
    }

    ColorHex::ColorHex(const std::string &hexstring, const float alpha)
        : Color{toRGB(hexstring, alpha)} {
        GP_CORE_INFO("gp::ColorHex::ColorHex({0}, alpha={1})", hexstring, alpha);

        // Alpha value is checked in gp::Color constructor
    }

    std::string ColorHex::toString() const {
        if (m_Alpha == 1) {
            return strformat("#%02x%02x%02x", m_Red, m_Green, m_Blue);
        }
        return strformat("ColorHex('#%02x%02x%02x', alpha=%.2f)", m_Red, m_Green, m_Blue, m_Alpha);
    }

    ColorRGB ColorHex::toRGB() const {
        GP_CORE_DEBUG("gp::ColorHex::toRGB({0})", this->toString());
        return {m_Red, m_Green, m_Blue, m_Alpha};
    }

    ColorRGB ColorHex::toRGB(const std::string &hexstring, const float alpha) {
        GP_CORE_DEBUG("gp::ColorHex::toRGB({0}, {1})", hexstring, alpha);

        switch (hexstring.length()) {
            case 3:
                return _3toRGB(hexstring, alpha);
            case 4:
                if (hexstring.starts_with("#")) {
                    return _4toRGB(hexstring, alpha);
                }
            case 6:
                return _6toRGB(hexstring, alpha);
            case 7:
                if (hexstring.starts_with("#")) {
                    return _7toRGB(hexstring, alpha);
                }
            default:
                GP_VALUE_ERROR("gp::hex::toRGB() invalid hexstring '{0}'", hexstring.c_str());
                return {-1, -1, -1};
        }
    }
}
