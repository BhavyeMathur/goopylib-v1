#pragma once

namespace gp {
    struct RGB {
        int red;
        int green;
        int blue;
    };

    struct CMYK {
        float cyan;
        float magenta;
        float yellow;
        float key;
    };

    struct HSV {
        int hue;
        float saturation;
        float value;
    };

    struct HSL {
        int hue;
        float saturation;
        float luminance;
    };

    struct RGBAf {
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 1;

        RGBAf(float red, float green, float blue, float alpha = 1)
                : red(red),
                  green(green),
                  blue(blue),
                  alpha(alpha) {
        }
    };
}
