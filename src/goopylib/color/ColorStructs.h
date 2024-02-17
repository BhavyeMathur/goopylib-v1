#pragma once

namespace gp {
    struct RGB {
        int red;
        int green;
        int blue;

        RGB(int red, int green, int blue)
            : red{red},
              green{green},
              blue{blue} {
        }

        bool operator==(const RGB &) const = default;
    };

    struct CMYK {
        float cyan;
        float magenta;
        float yellow;
        float key;

        CMYK(float cyan, float magenta, float yellow, float key)
            : cyan{cyan},
              magenta{magenta},
              yellow{yellow},
              key{key} {
        }

        bool operator==(const CMYK &) const = default;
    };

    struct HSV {
        int hue;
        float saturation;
        float value;

        HSV(int hue, float saturation, float value)
            : hue{hue},
              saturation{saturation},
              value{value} {
        }

        bool operator==(const HSV &) const = default;
    };

    struct HSL {
        int hue;
        float saturation;
        float luminance;

        HSL(int hue, float saturation, float luminance)
            : hue{hue},
              saturation{saturation},
              luminance{luminance} {
        }

        bool operator==(const HSL &) const = default;
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

        bool operator==(const RGBAf &) const = default;
    };

    struct RGBf {
        float red = 0;
        float green = 0;
        float blue = 0;

        RGBf(float red, float green, float blue)
            : red(red),
              green(green),
              blue(blue) {
        }

        bool operator==(const RGBf &) const = default;
    };
}
