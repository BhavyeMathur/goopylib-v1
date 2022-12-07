#include "pch.h"
#include "Util.h"

static std::random_device rand_dev;
static std::mt19937 generator(rand_dev());

static std::uniform_int_distribution<int> rgb_distribution(0, 255);
static std::uniform_int_distribution<int> angle_distribution(0, 360);
static std::uniform_real_distribution<float> normalized_distribution(0.0f, 1.0f);

namespace gp {
    ColorRGB randomRGB() {
        return {(unsigned int) rgb_distribution(generator),
                (unsigned int) rgb_distribution(generator),
                (unsigned int) rgb_distribution(generator)};
    }

    ColorHex randomHex() {
        return ColorHex(rgb::toHex((unsigned int) rgb_distribution(generator),
                                   (unsigned int) rgb_distribution(generator),
                                   (unsigned int) rgb_distribution(generator)));
    }

    ColorCMYK randomCMYK() {
        return {normalized_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }

    ColorHSV randomHSV() {
        return {(unsigned int) angle_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }

    ColorHSL randomHSL() {
        return {(unsigned int) angle_distribution(generator),
                normalized_distribution(generator),
                normalized_distribution(generator)};
    }
}
