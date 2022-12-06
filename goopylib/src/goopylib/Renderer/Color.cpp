#include "pch.h"
#include "Color.h"


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
                return -1;
        }
    }

    gp::ColorRGB Hex3toRGB(const char *hexstring) {
        return gp::ColorRGB{17 * digitToInt(hexstring[0]),
                        17 * digitToInt(hexstring[1]),
                        17 * digitToInt(hexstring[2])};
    }

    gp::ColorRGB Hex4toRGB(const char *hexstring) {
        return gp::ColorRGB{17 * digitToInt(hexstring[1]),
                        17 * digitToInt(hexstring[2]),
                        17 * digitToInt(hexstring[3])};
    }

    gp::ColorRGB Hex6toRGB(const char *hexstring) {
        return gp::ColorRGB{16 * digitToInt(hexstring[0]) + digitToInt(hexstring[1]),
                        16 * digitToInt(hexstring[2]) + digitToInt(hexstring[3]),
                        16 * digitToInt(hexstring[4]) + digitToInt(hexstring[5])};
    }

    gp::ColorRGB Hex7toRGB(const char *hexstring) {
        return gp::ColorRGB{16 * digitToInt(hexstring[1]) + digitToInt(hexstring[2]),
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

        ColorCMYK toCMYK(int red, int green, int blue) {
            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float maximum = redf > greenf ? redf : greenf;
            if (bluef > maximum) {
                maximum = bluef;
            }

            float k = 1 - maximum;

            return ColorCMYK{(maximum - redf) / maximum,
                             (maximum - greenf) / maximum,
                             (maximum - bluef) / maximum,
                             k};
        }

        ColorHSL toHSL(int red, int green, int blue) {
            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float cmax, cmin;

            if (redf > greenf) {
                cmax = redf;
                cmin = greenf;
            } else {
                cmax = greenf;
                cmin = redf;
            }

            if (bluef > cmax) {
                cmax = bluef;
            } else if (bluef < cmin) {
                cmin = bluef;
            }

            float delta = cmax - cmin;
            float L = (cmax + cmin) / 2;

            if (delta == 0) {
                return ColorHSL{0, 0, L};
            }

            float s = delta / (1 - abs(2 * L - 1));

            if (cmax == redf) {
                return ColorHSL{(int) round(60 * fmodf((greenf - bluef) / delta, 6)), s, L};
            } else if (cmax == greenf) {
                return ColorHSL{(int) round(60 * (((bluef - redf) / delta) + 2)), s, L};
            } else {
                return ColorHSL{(int) round(60 * (((redf - greenf) / delta) + 4)), s, L};
            }
        }

        ColorHSV toHSV(int red, int green, int blue) {
            float redf = (float) red / 255.0f;
            float greenf = (float) green / 255.0f;
            float bluef = (float) blue / 255.0f;

            float cmax, cmin;

            if (redf > greenf) {
                cmax = redf;
                cmin = greenf;
            } else {
                cmax = greenf;
                cmin = redf;
            }

            if (bluef > cmax) {
                cmax = bluef;
            } else if (bluef < cmin) {
                cmin = bluef;
            }

            float delta = cmax - cmin;
            int h;

            if (delta == 0) {
                h = 0;
            } else if (cmax == redf) {
                h = (int) round(60 * fmodf((greenf - bluef) / delta, 6));
            } else if (cmax == greenf) {
                h = (int) round(60 * (((bluef - redf) / delta) + 2));
            } else {
                h = (int) round(60 * (((redf - greenf) / delta) + 4));
            }

            return ColorHSV{h, cmax == 0 ? 0 : delta / cmax, cmax};
        }
    }

    // Hex to other format

    namespace hex {
        ColorRGB toRGB(const char *hexstring) {
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
                    return ColorRGB{-1, -1, -1};
            }
        }

        ColorCMYK toCMYK(const char *hexstring) {
            ColorRGB color_rgb = toRGB(hexstring);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorHSL toHSL(const char *hexstring) {
            ColorRGB color_rgb = toRGB(hexstring);
            return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorHSV toHSV(const char *hexstring) {
            ColorRGB color_rgb = toRGB(hexstring);
            return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
        }
    }

    // CMYK to other format

    namespace cmyk {
        ColorRGB toRGB(float cyan, float magenta, float yellow, float key) {
            key = 1 - key;
            return ColorRGB{(int) round(255 * (1 - cyan) * key),
                            (int) round(255 * (1 - magenta) * key),
                            (int) round(255 * (1 - yellow) * key)};
        }

        const char *toHex(float cyan, float magenta, float yellow, float key) {
            ColorRGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorHSL toHSL(float cyan, float magenta, float yellow, float key) {
            ColorRGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHSL(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorHSV toHSV(float cyan, float magenta, float yellow, float key) {
            ColorRGB color_rgb = toRGB(cyan, magenta, yellow, key);
            return rgb::toHSV(color_rgb.red, color_rgb.green, color_rgb.blue);
        }
    }

    // HSL to other format

    namespace hsl {
        ColorRGB toRGB(int hue, float saturation, float luminance) {
            float c = (1 - fabsf(2 * luminance - 1)) * saturation;
            float x = c * (1 - fabsf(fmodf((float) hue / 60, 2) - 1));
            float m = luminance - c / 2;

            if (hue < 60) {
                return ColorRGB{(int) round(255 * (c + m)),
                                (int) round(255 * (x + m)),
                                (int) round(255 * m)};
            } else if (hue < 120) {
                return ColorRGB{(int) round(255 * (x + m)),
                                (int) round(255 * (c + m)),
                                (int) round(255 * m)};
            } else if (hue < 180) {
                return ColorRGB{(int) round(255 * m),
                                (int) round(255 * (c + m)),
                                (int) round(255 * (x + m))};
            } else if (hue < 240) {
                return ColorRGB{(int) round(255 * m),
                                (int) round(255 * (x + m)),
                                (int) round(255 * (c + m))};
            } else if (hue < 300) {
                return ColorRGB{(int) round(255 * (x + m)),
                                (int) round(255 * m),
                                (int) round(255 * (c + m))};
            } else {
                return ColorRGB{(int) round(255 * (c + m)),
                                (int) round(255 * m),
                                (int) round(255 * (x + m))};
            }
        }

        const char *toHex(int hue, float saturation, float luminance) {
            ColorRGB color_rgb = toRGB(hue, saturation, luminance);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorCMYK toCMYK(int hue, float saturation, float luminance) {
            ColorRGB color_rgb = toRGB(hue, saturation, luminance);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorHSV toHSV(int hue, float saturation, float luminance) {
            float v = luminance + saturation * (luminance < 0.5 ? luminance : 1 - luminance);

            saturation = v == 0 ? 0 : 2 * (1 - luminance / v);

            return ColorHSV{hue, saturation, v};
        }
    }

    // HSV to other format

    namespace hsv {
        ColorRGB toRGB(int hue, float saturation, float value) {
            float c = value * saturation;
            float x = c * (1 - fabsf(fmodf((float) hue / 60.0f, 2) - 1));
            float m = value - c;

            if (hue < 60) {
                return ColorRGB{(int) round(255 * (c + m)),
                                (int) round(255 * (x + m)),
                                (int) round(255 * m)};
            } else if (hue < 120) {
                return ColorRGB{(int) round(255 * (x + m)),
                                (int) round(255 * (c + m)),
                                (int) round(255 * m)};
            } else if (hue < 180) {
                return ColorRGB{(int) round(255 * m),
                                (int) round(255 * (c + m)),
                                (int) round(255 * (x + m))};
            } else if (hue < 240) {
                return ColorRGB{(int) round(255 * m),
                                (int) round(255 * (x + m)),
                                (int) round(255 * (c + m))};
            } else if (hue < 300) {
                return ColorRGB{(int) round(255 * (x + m)),
                                (int) round(255 * m),
                                (int) round(255 * (c + m))};
            } else {
                return ColorRGB{(int) round(255 * (c + m)),
                                (int) round(255 * m),
                                (int) round(255 * (x + m))};
            }
        }

        const char *toHex(int hue, float saturation, float value) {
            ColorRGB color_rgb = toRGB(hue, saturation, value);
            return rgb::toHex(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorCMYK toCMYK(int hue, float saturation, float value) {
            ColorRGB color_rgb = toRGB(hue, saturation, value);
            return rgb::toCMYK(color_rgb.red, color_rgb.green, color_rgb.blue);
        }

        ColorHSL toHSL(int hue, float saturation, float value) {
            float L = value * (1 - saturation / 2);

            if (L == 0 or L == 1) {
                return ColorHSL{hue, 0, L};
            } else if (L < 0.5) {
                return ColorHSL{hue, (value - L) / L, L};
            } else {
                return ColorHSL{hue, (value - L) / (1 - L), L};
            }
        }
    }
}
