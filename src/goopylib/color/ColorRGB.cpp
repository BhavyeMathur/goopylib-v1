#define GP_LOGGING_LEVEL 3

#include "ColorRGB.h"


namespace gp {
    ColorRGB::ColorRGB(const Color &color)
        : Color{color} {
        GP_CORE_INFO("gp::ColorRGB::ColorRGB({0})", color->toString());
    }

    ColorRGB::ColorRGB(const int red, const int green, const int blue, const float alpha)
        : Color{red, green, blue, alpha} {
        GP_CORE_INFO("gp::ColorRGB::ColorRGB({0}, {1}, {2}, alpha={3})", red, green, blue, alpha);
        // Value checks are performed in gp::Color constructor
    }
}
