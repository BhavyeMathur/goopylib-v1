#include "ColorHex.h"
#include "ColorConversions.h"

namespace {
    int digitToInt(char digit) {
        GP_CORE_TRACE("gp::digitToInt(digit={0})", digit);

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
                GP_VALUE_ERROR("digitToInt() invalid hexstring character '{0}'", digit);
                return 0;
        }
    }

    gp::RGB Hex3toRGB(const char *hexstring) {
        GP_CORE_DEBUG("Hex3toRGB(hexstring={0})", hexstring);

        return gp::RGB{17 * digitToInt(hexstring[0]),
                       17 * digitToInt(hexstring[1]),
                       17 * digitToInt(hexstring[2])};
    }

    gp::RGB Hex4toRGB(const char *hexstring) {
        GP_CORE_DEBUG("Hex4toRGB(hexstring={0})", hexstring);

        return gp::RGB{17 * digitToInt(hexstring[1]),
                       17 * digitToInt(hexstring[2]),
                       17 * digitToInt(hexstring[3])};
    }

    gp::RGB Hex6toRGB(const char *hexstring) {
        GP_CORE_DEBUG("Hex6toRGB(hexstring={0})", hexstring);

        return gp::RGB{16 * digitToInt(hexstring[0]) + digitToInt(hexstring[1]),
                       16 * digitToInt(hexstring[2]) + digitToInt(hexstring[3]),
                       16 * digitToInt(hexstring[4]) + digitToInt(hexstring[5])};
    }

    gp::RGB Hex7toRGB(const char *hexstring) {
        GP_CORE_DEBUG("Hex7toRGB(hexstring={0})", hexstring);

        return gp::RGB{16 * digitToInt(hexstring[1]) + digitToInt(hexstring[2]),
                       16 * digitToInt(hexstring[3]) + digitToInt(hexstring[4]),
                       16 * digitToInt(hexstring[5]) + digitToInt(hexstring[6])};
    }
}

namespace gp::hex {
    // Hex to other format

    RGB toRGB(const char *hexstring) {
        GP_CORE_INFO("gp::hex::toRGB(hexstring={0})", hexstring);

        switch (strlen(hexstring)) {
            case 3:
                return Hex3toRGB(hexstring);
            case 4:
                return Hex4toRGB(hexstring);
            case 6:
                return Hex6toRGB(hexstring);
            case 7:
                return Hex7toRGB(hexstring);
            default:
                GP_VALUE_ERROR("gp::hex::toRGB() invalid hexstring '{0}'", hexstring);
                return {-1, -1, -1};
        }
    }

    CMYK toCMYK(const char *hexstring) {
        GP_CORE_INFO("gp::hex::toCMYK(hexstring={0})", hexstring);

        const RGB color_rgb = toRGB(hexstring);
        return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    HSL toHSL(const char *hexstring) {
        GP_CORE_INFO("gp::hex::toHSL(hexstring={0})", hexstring);

        const RGB color_rgb = toRGB(hexstring);
        return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
    }

    HSV toHSV(const char *hexstring) {
        GP_CORE_INFO("gp::hex::toHSV(hexstring={0})", hexstring);

        const RGB color_rgb = toRGB(hexstring);
        return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
    }
}

namespace gp {
    ColorHex::ColorHex(const Color *color)
            : Color(*color) {
        GP_CORE_INFO("gp::ColorHex::ColorHex{0})", color->toString());
    }

    ColorHex::ColorHex(const char *hexstring, float alpha)
            : Color(hex::toRGB(hexstring), alpha) {
        GP_CORE_INFO("gp::ColorHex::ColorHex({0}, alpha={1})", hexstring, alpha);

        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }

    std::string ColorHex::toString() const {
        return {rgb::toHex(m_Red, m_Green, m_Blue)};
    }
}
