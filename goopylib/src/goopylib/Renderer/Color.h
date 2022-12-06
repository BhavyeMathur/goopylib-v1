#pragma once

namespace gp {
    struct ColorRGB {
        int red;
        int green;
        int blue;
    };

    struct ColorCMYK {
        float cyan;
        float magenta;
        float yellow;
        float key;
    };

    struct ColorHSL {
        int hue;
        float saturation;
        float luminance;
    };

    struct ColorHSV {
        int hue;
        float saturation;
        float value;
    };
}

// Color Conversion Functions
namespace gp {

    // RGB to other format

    namespace rgb {
        const char *toHex(int red, int green, int blue);

        ColorCMYK toCMYK(int red, int green, int blue);

        ColorHSL toHSL(int red, int green, int blue);

        ColorHSV toHSV(int red, int green, int blue);
    }

    // Hex to other format

    namespace hex {
        ColorRGB toRGB(const char *hexstring);

        ColorCMYK toCMYK(const char *hexstring);

        ColorHSL toHSL(const char *hexstring);

        ColorHSV toHSV(const char *hexstring);
    }

    // CMYK to other format

    namespace cmyk {
        ColorRGB toRGB(float cyan, float magenta, float yellow, float key);

        const char *toHex(float cyan, float magenta, float yellow, float key);

        ColorHSL toHSL(float cyan, float magenta, float yellow, float key);

        ColorHSV toHSV(float cyan, float magenta, float yellow, float key);
    }

    // HSL to other format

    namespace hsl {
        ColorRGB toRGB(int hue, float saturation, float luminance);

        const char *toHex(int hue, float saturation, float luminance);

        ColorCMYK toCMYK(int hue, float saturation, float luminance);

        ColorHSV toHSV(int hue, float saturation, float luminance);
    }

    // HSV to other format

    namespace hsv {
        ColorRGB toRGB(int hue, float saturation, float value);

        const char *toHex(int hue, float saturation, float value);

        ColorCMYK toCMYK(int hue, float saturation, float value);

        ColorHSL toHSL(int hue, float saturation, float value);
    }
}

