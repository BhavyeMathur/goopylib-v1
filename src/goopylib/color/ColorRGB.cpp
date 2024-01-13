#include "ColorRGB.h"
#include "ColorConversions.h"


namespace gp::rgb {
    const char *toHex(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toHex(red={0}, green={1}, blue={2})", red, green, blue);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")

        // TODO figure out a better way of doing this that doesn't construct a static string (v2.0.x)
        static char *hex_string[8];

        if (snprintf((char *) (hex_string), 8, "#%02x%02x%02x", red, green, blue) < 0) {
            GP_CORE_ERROR("gp::rgb::toHex(red={0}, green={1}, blue={2}) Error formatting string", red, green, blue);
        }
        return (char *) (hex_string);
    }

    CMYK toCMYK(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toCMYK(red={0}, green={1}, blue={2})", red, green, blue);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")

        const float redf = (float) red / 255.0f;
        const float greenf = (float) green / 255.0f;
        const float bluef = (float) blue / 255.0f;

        float maximum = redf > greenf ? redf : greenf;
        if (bluef > maximum) {
            maximum = bluef;
        }

        const float k = 1 - maximum;

        if (maximum == 0) {
            return CMYK{0, 0, 0, 1};
        }

        return CMYK{(maximum - redf) / maximum,
                    (maximum - greenf) / maximum,
                    (maximum - bluef) / maximum,
                    k};
    }

    HSL toHSL(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toHSL(red={0}, green={1}, blue={2})", red, green, blue);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")

        const float redf = (float) red / 255.0f;
        const float greenf = (float) green / 255.0f;
        const float bluef = (float) blue / 255.0f;

        float cmax, cmin;

        if (redf > greenf) {
            cmax = redf;
            cmin = greenf;
        }
        else {
            cmax = greenf;
            cmin = redf;
        }

        if (bluef > cmax) {
            cmax = bluef;
        }
        else if (bluef < cmin) {
            cmin = bluef;
        }

        const float delta = cmax - cmin;
        const float L = (cmax + cmin) / 2;

        if (delta == 0) {
            return HSL{0, 0, L};
        }

        const float s = delta / (1 - abs(2 * L - 1));

        if (cmax == redf) {
            return HSL{(int) round(60 * fmodf((greenf - bluef) / delta, 6)), s, L};
        }
        else if (cmax == greenf) {
            return HSL{(int) round(60 * (((bluef - redf) / delta) + 2)), s, L};
        }
        else {
            return HSL{(int) round(60 * (((redf - greenf) / delta) + 4)), s, L};
        }
    }

    HSV toHSV(int red, int green, int blue) {
        GP_CORE_INFO("gp::rgb::toHSV(red={0}, green={1}, blue={2})", red, green, blue);

        GP_CHECK_INCLUSIVE_RANGE(red, 0, 255, "Color red value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(green, 0, 255, "Color green value must be between 0 and 255")
        GP_CHECK_INCLUSIVE_RANGE(blue, 0, 255, "Color blue value must be between 0 and 255")

        const float redf = (float) red / 255.0f;
        const float greenf = (float) green / 255.0f;
        const float bluef = (float) blue / 255.0f;

        float cmax, cmin;

        if (redf > greenf) {
            cmax = redf;
            cmin = greenf;
        }
        else {
            cmax = greenf;
            cmin = redf;
        }

        if (bluef > cmax) {
            cmax = bluef;
        }
        else if (bluef < cmin) {
            cmin = bluef;
        }

        const float delta = cmax - cmin;
        int h;

        if (delta == 0) {
            h = 0;
        }
        else if (cmax == redf) {
            h = (int) round(60 * fmodf((greenf - bluef) / delta, 6));
        }
        else if (cmax == greenf) {
            h = (int) round(60 * (((bluef - redf) / delta) + 2));
        }
        else {
            h = (int) round(60 * (((redf - greenf) / delta) + 4));
        }

        return HSV{h, cmax == 0 ? 0 : delta / cmax, cmax};
    }
}

namespace gp {
    ColorRGB::ColorRGB(const Color *color)
            : Color(*color) {
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
