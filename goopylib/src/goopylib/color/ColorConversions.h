#pragma once

#include "gp.h"
#include "ColorStructs.h"

namespace gp {
    
    // RGB to other format

    namespace rgb {
        const char *toHex(int red, int green, int blue);

        CMYK toCMYK(int red, int green, int blue);

        HSL toHSL(int red, int green, int blue);

        HSV toHSV(int red, int green, int blue);
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
        RGB toRGB(int hue, float saturation, float luminance);

        const char *toHex(int hue, float saturation, float luminance);

        CMYK toCMYK(int hue, float saturation, float luminance);

        HSV toHSV(int hue, float saturation, float luminance);
    }

    // HSV to other format

    namespace hsv {
        RGB toRGB(int hue, float saturation, float value);

        const char *toHex(int hue, float saturation, float value);

        CMYK toCMYK(int hue, float saturation, float value);

        HSL toHSL(int hue, float saturation, float value);
    }
}
