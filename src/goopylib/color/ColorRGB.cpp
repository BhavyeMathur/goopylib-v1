#define GP_LOGGING_LEVEL 3

#include "ColorRGB.h"


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
