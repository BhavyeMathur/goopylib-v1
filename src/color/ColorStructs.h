#pragma once

namespace gp {
    struct GPAPI RGBAf final {
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 1;

        RGBAf(const float red, const float green, const float blue, const float alpha = 1)
            : red(red),
              green(green),
              blue(blue),
              alpha(alpha) {
        }

        [[nodiscard]] std::string toString() const;

        bool operator==(const RGBAf &) const = default;
    };

    struct GPAPI RGBf final {
        float red = 0;
        float green = 0;
        float blue = 0;

        RGBf(const float red, const float green, const float blue)
            : red(red),
              green(green),
              blue(blue) {
        }

        [[nodiscard]] std::string toString() const;

        bool operator==(const RGBf &) const = default;
    };

    GPAPI std::ostream &operator<<(std::ostream &os, const RGBAf &color);

    GPAPI std::ostream &operator<<(std::ostream &os, const RGBf &color);
}
