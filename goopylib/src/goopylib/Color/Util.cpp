#include "pch.h"
#include "Util.h"

static std::random_device rand_dev;
static std::mt19937 generator(rand_dev());

static std::uniform_int_distribution<int> rgb_distribution(0, 255);
static std::uniform_int_distribution<int> angle_distribution(0, 360);
static std::uniform_real_distribution<float> normalized_distribution(0.0f, 1.0f);

namespace gp {
    GPAPI ColorRGB randomRGB() {
        return {rgb_distribution(generator),
                rgb_distribution(generator),
                rgb_distribution(generator)};
    }

    GPAPI ColorHex randomHex() {
        return ColorHex(rgb::toHex(rgb_distribution(generator),
                                   rgb_distribution(generator),
                                   rgb_distribution(generator)));
    }

    GPAPI ColorCMYK randomCMYK() {
        return {normalized_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }

    GPAPI ColorHSV randomHSV() {
        return {angle_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }

    GPAPI ColorHSL randomHSL() {
        return {angle_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }
}
