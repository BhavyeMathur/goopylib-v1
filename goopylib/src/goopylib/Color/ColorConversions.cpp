#include "gp.h"
#include "ColorConversions.h"


// Internal Functions

namespace {
    int digitToInt(char digit) {

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
                GP_CORE_ERROR("invalid hexstring");
                return 0;
        }
    }

    gp::RGB Hex3toRGB(const char *hexstring) {
        return gp::RGB{17 * digitToInt(hexstring[0]),
                       17 * digitToInt(hexstring[1]),
                       17 * digitToInt(hexstring[2])};
    }

    gp::RGB Hex4toRGB(const char *hexstring) {
        return gp::RGB{17 * digitToInt(hexstring[1]),
                       17 * digitToInt(hexstring[2]),
                       17 * digitToInt(hexstring[3])};
    }

    gp::RGB Hex6toRGB(const char *hexstring) {
        return gp::RGB{16 * digitToInt(hexstring[0]) + digitToInt(hexstring[1]),
                       16 * digitToInt(hexstring[2]) + digitToInt(hexstring[3]),
                       16 * digitToInt(hexstring[4]) + digitToInt(hexstring[5])};
    }

    gp::RGB Hex7toRGB(const char *hexstring) {
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
            static char *hex_string[8];

            sprintf((char *) hex_string, "#%02x%02x%02x", red, green, blue);
            return (const char *) hex_string;
        }

        CMYK toCMYK(int red, int green, int blue) {
            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float maximum = redf > greenf ? redf : greenf;
            if (bluef > maximum) {
                maximum = bluef;
            }

            float k = 1 - maximum;

            return CMYK{(maximum - redf) / maximum,
                        (maximum - greenf) / maximum,
                        (maximum - bluef) / maximum,
                        k};
        }

        HSL toHSL(int red, int green, int blue) {
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
                    throw std::invalid_argument("invalid hexstring");
            }
        }

        CMYK toCMYK(const char *hexstring) {
            RGB color_rgb = toRGB(hexstring);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSL toHSL(const char *hexstring) {
            RGB color_rgb = toRGB(hexstring);
            return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSV toHSV(const char *hexstring) {
            RGB color_rgb = toRGB(hexstring);
            return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
        }
    }

    // CMYK to other format

    namespace cmyk {
        RGB toRGB(float cyan, float magenta, float yellow, float key) {
            key = 1 - key;
            return RGB{(int) round(255 * (1 - cyan) * key),
                       (int) round(255 * (1 - magenta) * key),
                       (int) round(255 * (1 - yellow) * key)};
        }

        const char *toHex(float cyan, float magenta, float yellow, float key) {
            RGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSL toHSL(float cyan, float magenta, float yellow, float key) {
            RGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSV toHSV(float cyan, float magenta, float yellow, float key) {
            RGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
        }
    }

    // HSL to other format

    namespace hsl {
        RGB toRGB(int hue, float saturation, float luminance) {
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
            RGB color_rgb = toRGB(hue, saturation, luminance);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        CMYK toCMYK(int hue, float saturation, float luminance) {
            RGB color_rgb = toRGB(hue, saturation, luminance);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSV toHSV(int hue, float saturation, float luminance) {
            float v = luminance + saturation * (luminance < 0.5 ? luminance : 1 - luminance);

            saturation = v == 0 ? 0 : 2 * (1 - luminance / v);

            return HSV{hue, saturation, v};
        }
    }

    // HSV to other format

    namespace hsv {
        RGB toRGB(int hue, float saturation, float value) {
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
            RGB color_rgb = toRGB(hue, saturation, value);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        CMYK toCMYK(int hue, float saturation, float value) {
            RGB color_rgb = toRGB(hue, saturation, value);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        HSL toHSL(int hue, float saturation, float value) {
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
}
