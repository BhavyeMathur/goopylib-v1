#pragma once

#include "Color.h"

// Color Conversion Functions

namespace gp {

    struct RGB {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
    };

    struct CMYK {
        float cyan;
        float magenta;
        float yellow;
        float key;
    };

    struct HSV {
        unsigned int hue;
        float saturation;
        float value;
    };

    struct HSL {
        unsigned int hue;
        float saturation;
        float luminance;
    };

    // RGB to other format

    namespace rgb {
        const char *toHex(unsigned int red, unsigned int green, unsigned int blue);

        CMYK toCMYK(unsigned int red, unsigned int green, unsigned int blue);

        HSL toHSL(unsigned int red, unsigned int green, unsigned int blue);

        HSV toHSV(unsigned int red, unsigned int green, unsigned int blue);
    }

    // Hex to other format

    namespace hex {
        RGB toRGB(const char *hexstring);

        CMYK toCMYK(const char *hexstring);

        HSL toHSL(const char *hexstring);

        HSV toHSV(const char *hexstring);
    }

    // CMYK to other format

    namespace cmyk {
        RGB toRGB(float cyan, float magenta, float yellow, float key);

        const char *toHex(float cyan, float magenta, float yellow, float key);

        HSL toHSL(float cyan, float magenta, float yellow, float key);

        HSV toHSV(float cyan, float magenta, float yellow, float key);
    }

    // HSL to other format

    namespace hsl {
        RGB toRGB(unsigned int hue, float saturation, float luminance);

        const char *toHex(unsigned int hue, float saturation, float luminance);

        CMYK toCMYK(unsigned int hue, float saturation, float luminance);

        HSV toHSV(unsigned int hue, float saturation, float luminance);
    }

    // HSV to other format

    namespace hsv {
        RGB toRGB(unsigned int hue, float saturation, float value);

        const char *toHex(unsigned int hue, float saturation, float value);

        CMYK toCMYK(unsigned int hue, float saturation, float value);

        HSL toHSL(unsigned int hue, float saturation, float value);
    }
}

