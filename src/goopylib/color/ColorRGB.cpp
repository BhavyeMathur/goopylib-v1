#define GP_LOGGING_LEVEL 3

#include "ColorRGB.h"
#include "ColorConversions.h"

namespace gp::rgb {
    RGBf toRGBf(int red, int green, int blue) {
        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")

        return {
            static_cast<float>(red) / 255.0f,
            static_cast<float>(green) / 255.0f,
            static_cast<float>(blue) / 255.0f
        };
    }

    std::string toHex(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toHex(red={0}, green={1}, blue={2})", red, green, blue);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")

        return strformat("#%02x%02x%02x", red, green, blue);
    }

    CMYK toCMYK(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toCMYK(red={0}, green={1}, blue={2})", red, green, blue);

        // also checks for invalid RGB values outside [0, 255] range
        const auto [redf, greenf, bluef] = toRGBf(red, green, blue);
        const float maximum = std::max({redf, greenf, bluef});

        if (maximum == 0) {
            return CMYK{0, 0, 0, 1};
        }

        return CMYK{
            (maximum - redf) / maximum,
            (maximum - greenf) / maximum,
            (maximum - bluef) / maximum,
            1 - maximum
        };
    }

    HSL toHSL(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toHSL(red={0}, green={1}, blue={2})", red, green, blue);

        // also checks for invalid RGB values outside [0, 255] range
        const auto [redf, greenf, bluef] = toRGBf(red, green, blue);
        const auto [cmin, cmax] = std::minmax({redf, greenf, bluef});

        const float delta = cmax - cmin;
        const float luminance = (cmax + cmin) / 2;

        if (delta == 0) {
            return HSL{0, 0, luminance};
        }

        const float saturation = delta / (1 - abs(2 * luminance - 1));

        if (cmax == redf) {
            return HSL{static_cast<int>(round(60 * fmodf((greenf - bluef) / delta, 6))), saturation, luminance};
        }
        if (cmax == greenf) {
            return HSL{static_cast<int>(round(60 * ((bluef - redf) / delta + 2))), saturation, luminance};
        }
        // cmax == bluef
        return HSL{static_cast<int>(round(60 * ((redf - greenf) / delta + 4))), saturation, luminance};
    }

    HSV toHSV(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toHSV(red={0}, green={1}, blue={2})", red, green, blue);

        // also checks for invalid RGB values outside [0, 255] range
        const auto [redf, greenf, bluef] = toRGBf(red, green, blue);
        const auto [cmin, cmax] = std::minmax({redf, greenf, bluef});

        const float delta = cmax - cmin;
        const float saturation = cmax == 0 ? 0 : delta / cmax;

        if (delta == 0) {
            return HSV{0, saturation, cmax};
        }
        if (cmax == redf) {
            return HSV{static_cast<int>(round(60 * fmodf((greenf - bluef) / delta, 6))), saturation, cmax};
        }
        if (cmax == greenf) {
            return HSV{static_cast<int>(round(60 * ((bluef - redf) / delta + 2))), saturation, cmax};
        }
        // cmax == bluef
        return HSV{static_cast<int>(round(60 * ((redf - greenf) / delta + 4))), saturation, cmax};
    }
}

namespace gp {
    ColorRGB::ColorRGB(const Color &color)
        : Color{color} {
        GP_CORE_INFO("gp::ColorRGB::ColorRGB({0})", color->toString());
    }

    ColorRGB::ColorRGB(int red, int green, int blue, float alpha)
        : Color(red, green, blue, alpha) {
        GP_CORE_INFO("gp::ColorRGB::ColorRGB({0}, {1}, {2}, alpha={3})", red, green, blue, alpha);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(alpha, 0, 1, "Color alpha value must be between 0 and 1")
    }
}
