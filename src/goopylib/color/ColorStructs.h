#pragma once

namespace gp {
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
