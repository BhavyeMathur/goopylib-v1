#include "ColorConversions.h"

#if !GP_LOG_COLOR_CONVERSIONS
#undef GP_LOGGING_LEVEL
#endif

#include "goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECKING_COLOR_CONVERSIONS
#undef GP_VALUE_CHECKING
#endif

#include "goopylib/debug/Error.h"

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
                GP_VALUE_ERROR("invalid hexstring character '{0}'", digit);
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

// Color Conversion Functions

namespace gp {

    // RGB to other format

    namespace rgb {
        const char *toHex(int red, int green, int blue) {
            GP_CORE_INFO("gp::rgb::toHex(red={0}, green={1}, blue={2})", red, green, blue);

            GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255");

            static char *hex_string[8];

            sprintf((char *) hex_string, "#%02x%02x%02x", red, green, blue);
            return (const char *) hex_string;
        }

        CMYK toCMYK(int red, int green, int blue) {
            GP_CORE_INFO("gp::rgb::toCMYK(red={0}, green={1}, blue={2})", red, green, blue);

            GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255");

            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float maximum = redf > greenf ? redf : greenf;
            if (bluef > maximum) {
                maximum = bluef;
            }

            float k = 1 - maximum;

            if (maximum == 0) {
                return CMYK{0, 0, 0, 1};
            }

            return CMYK{(maximum - redf) / maximum,
                        (maximum - greenf) / maximum,
                        (maximum - bluef) / maximum,
                        k};
        }

        HSL toHSL(int red, int green, int blue) {
            GP_CORE_INFO("gp::rgb::toHSL(red={0}, green={1}, blue={2})", red, green, blue);

            GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255");

            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float cmax, cmin;

            if (redf > greenf) {
                cmax = redf;
                cmin = greenf;
            }
            else {
                cmax = greenf;
                cmin = redf;
            }

            if (bluef > cmax) {
                cmax = bluef;
            }
            else if (bluef < cmin) {
                cmin = bluef;
            }

            float delta = cmax - cmin;
            float L = (cmax + cmin) / 2;

            if (delta == 0) {
                return HSL{0, 0, L};
            }

            float s = delta / (1 - abs(2 * L - 1));

            if (cmax == redf) {
                return HSL{(int) round(60 * fmodf((greenf - bluef) / delta, 6)), s, L};
            }
            else if (cmax == greenf) {
                return HSL{(int) round(60 * (((bluef - redf) / delta) + 2)), s, L};
            }
            else {
                return HSL{(int) round(60 * (((redf - greenf) / delta) + 4)), s, L};
            }
        }

        HSV toHSV(int red, int green, int blue) {
            GP_CORE_INFO("gp::rgb::toHSV(red={0}, green={1}, blue={2})", red, green, blue);

            GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255");
            GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255");

            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float cmax, cmin;

            if (redf > greenf) {
                cmax = redf;
                cmin = greenf;
            }
            else {
                cmax = greenf;
                cmin = redf;
            }

            if (bluef > cmax) {
                cmax = bluef;
            }
            else if (bluef < cmin) {
                cmin = bluef;
            }

            float delta = cmax - cmin;
            int h;

            if (delta == 0) {
                h = 0;
            }
            else if (cmax == redf) {
                h = (int) round(60 * fmodf((greenf - bluef) / delta, 6));
            }
            else if (cmax == greenf) {
                h = (int) round(60 * (((bluef - redf) / delta) + 2));
            }
            else {
                h = (int) round(60 * (((redf - greenf) / delta) + 4));
            }

            return HSV{h, cmax == 0 ? 0 : delta / cmax, cmax};
        }
    }

    // Hex to other format

    namespace hex {
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
                    GP_VALUE_ERROR("invalid hexstring '{0}'", hexstring);
                    return {-1, -1, -1};
            }
        }

        CMYK toCMYK(const char *hexstring) {
            GP_CORE_INFO("gp::hex::toCMYK(hexstring={0})", hexstring);

            RGB color_rgb = toRGB(hexstring);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSL toHSL(const char *hexstring) {
            GP_CORE_INFO("gp::hex::toHSL(hexstring={0})", hexstring);

            RGB color_rgb = toRGB(hexstring);
            return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSV toHSV(const char *hexstring) {
            GP_CORE_INFO("gp::hex::toHSV(hexstring={0})", hexstring);

            RGB color_rgb = toRGB(hexstring);
            return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
        }
    }

    // CMYK to other format

    namespace cmyk {
        RGB toRGB(float cyan, float magenta, float yellow, float key) {
            GP_CORE_INFO("gp::cmyk::toRGB(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

            GP_CHECK_INCLUSIVE_RANGE(cyan, 0, 1, "Color cyan value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(magenta, 0, 1, "Color magenta value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(yellow, 0, 1, "Color yellow value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(key, 0, 1, "Color key value must be between 0 and 1");

            key = 1 - key;
            return RGB{(int) round(255 * (1 - cyan) * key),
                       (int) round(255 * (1 - magenta) * key),
                       (int) round(255 * (1 - yellow) * key)};
        }

        const char *toHex(float cyan, float magenta, float yellow, float key) {
            GP_CORE_INFO("gp::cmyk::toHex(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

            RGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSL toHSL(float cyan, float magenta, float yellow, float key) {
            GP_CORE_INFO("gp::cmyk::toHSL(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

            RGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSV toHSV(float cyan, float magenta, float yellow, float key) {
            GP_CORE_INFO("gp::cmyk::toHSV(cyan={0}, magenta={1}, yellow={2}, key={3})", cyan, magenta, yellow, key);

            RGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
        }
    }

    // HSV to other format

    namespace hsv {
        RGB toRGB(int hue, float saturation, float value) {
            GP_CORE_INFO("gp::hsv::toRGB(hue={0}, saturation={1}, value={2})", hue, saturation, value);

            GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360");
            GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1");

            float c = value * saturation;
            float x = c * (1 - fabsf(fmodf((float) hue / 60.0f, 2) - 1));
            float m = value - c;

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

            RGB color_rgb = toRGB(hue, saturation, value);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        CMYK toCMYK(int hue, float saturation, float value) {
            GP_CORE_INFO("gp::hsv::toCMYK(hue={0}, saturation={1}, value={2})", hue, saturation, value);

            RGB color_rgb = toRGB(hue, saturation, value);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSL toHSL(int hue, float saturation, float value) {
            GP_CORE_INFO("gp::hsv::toHSL(hue={0}, saturation={1}, value={2})", hue, saturation, value);

            GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360");
            GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(value, 0, 1, "Color 'value' value must be between 0 and 1");

            float L = value * (1 - saturation / 2);

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

    // HSL to other format

    namespace hsl {
        RGB toRGB(int hue, float saturation, float luminance) {
            GP_CORE_INFO("gp::hsl::toRGB(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

            GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360");
            GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1");

            float c = (1 - fabsf(2 * luminance - 1)) * saturation;
            float x = c * (1 - fabsf(fmodf((float) hue / 60, 2) - 1));
            float m = luminance - c / 2;

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

        const char *toHex(int hue, float saturation, float luminance) {
            GP_CORE_INFO("gp::hsl::toHex(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

            RGB color_rgb = toRGB(hue, saturation, luminance);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        CMYK toCMYK(int hue, float saturation, float luminance) {
            GP_CORE_INFO("gp::hsl::toCMYK(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

            RGB color_rgb = toRGB(hue, saturation, luminance);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSV toHSV(int hue, float saturation, float luminance) {
            GP_CORE_INFO("gp::hsl::toHSV(hue={0}, saturation={1}, luminance={2})", hue, saturation, luminance);

            GP_CHECK_INCLUSIVE_RANGE(hue, 0, 360, "Color hue value must be between 0 and 360");
            GP_CHECK_INCLUSIVE_RANGE(saturation, 0, 1, "Color saturation value must be between 0 and 1");
            GP_CHECK_INCLUSIVE_RANGE(luminance, 0, 1, "Color luminance value must be between 0 and 1");

            float v = luminance + saturation * (luminance < 0.5 ? luminance : 1 - luminance);

            saturation = v == 0 ? 0 : 2 * (1 - luminance / v);

            return HSV{hue, saturation, v};
        }
    }
}
