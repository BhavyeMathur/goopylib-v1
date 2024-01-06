#define GP_LOGGING_LEVEL 3

#include "Util.h"
#include "ColorConversions.h"

#include <random>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());

std::uniform_int_distribution<int> rgb_distribution(0, 255);
std::uniform_int_distribution<int> angle_distribution(0, 360);
std::uniform_real_distribution<float> normalized_distribution(0.0f, 1.0f);

namespace gp {
    ColorRGB randomRGB() {
        GP_CORE_INFO("gp::randomRGB()");

        return {rgb_distribution(generator),
                rgb_distribution(generator),
                rgb_distribution(generator)};
    }

    ColorHex randomHex() {
        GP_CORE_INFO("gp::randomHex()");

        return {rgb::toHex(rgb_distribution(generator),
                           rgb_distribution(generator),
                           rgb_distribution(generator))};
    }

    ColorCMYK randomCMYK() {
        GP_CORE_INFO("gp::randomCMYK()");

        return {normalized_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }

    ColorHSV randomHSV() {
        GP_CORE_INFO("gp::randomHSV()");

        return {angle_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }

    ColorHSL randomHSL() {
        GP_CORE_INFO("gp::randomHSL()");

        return {angle_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }
}
