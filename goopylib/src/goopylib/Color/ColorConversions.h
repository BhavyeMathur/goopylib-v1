#pragma once

#include "Color.h"

// Color Conversion Functions

namespace gp {

    struct GPAPI RGB {
        int red;
        int green;
        int blue;
    };

    struct GPAPI CMYK {
        float cyan;
        float magenta;
        float yellow;
        float key;
    };

    struct GPAPI HSV {
        int hue;
        float saturation;
        float value;
    };

    struct GPAPI HSL {
        int hue;
        float saturation;
        float luminance;
    };

    // RGB to other format

    namespace rgb {
        GPAPI const char *toHex(int red, int green, int blue);

        GPAPI CMYK toCMYK(int red, int green, int blue);

        GPAPI HSL toHSL(int red, int green, int blue);

        GPAPI HSV toHSV(int red, int green, int blue);
    }

    // Hex to other format

    namespace hex {
        GPAPI RGB toRGB(const char *hexstring);

        GPAPI CMYK toCMYK(const char *hexstring);

        GPAPI HSL toHSL(const char *hexstring);

        GPAPI HSV toHSV(const char *hexstring);
    }

    // CMYK to other format

    namespace cmyk {
        GPAPI RGB toRGB(float cyan, float magenta, float yellow, float key);

        GPAPI const char *toHex(float cyan, float magenta, float yellow, float key);

        GPAPI HSL toHSL(float cyan, float magenta, float yellow, float key);

        GPAPI HSV toHSV(float cyan, float magenta, float yellow, float key);
    }

    // HSL to other format

    namespace hsl {
        GPAPI RGB toRGB(int hue, float saturation, float luminance);

        GPAPI const char *toHex(int hue, float saturation, float luminance);

        GPAPI CMYK toCMYK(int hue, float saturation, float luminance);

        GPAPI HSV toHSV(int hue, float saturation, float luminance);
    }

    // HSV to other format

    namespace hsv {
        GPAPI RGB toRGB(int hue, float saturation, float value);

        GPAPI const char *toHex(int hue, float saturation, float value);

        GPAPI CMYK toCMYK(int hue, float saturation, float value);

        GPAPI HSL toHSL(int hue, float saturation, float value);
    }
}
