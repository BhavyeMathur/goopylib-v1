#define GP_LOGGING_LEVEL 3

#include "Util.h"

#include <random>

unique_ptr<std::random_device> rand_dev;
unique_ptr<std::mt19937> generator;

unique_ptr<std::uniform_int_distribution<> > rgb_distribution;
unique_ptr<std::uniform_int_distribution<> > angle_distribution;
unique_ptr<std::uniform_real_distribution<float> > normalized_distribution;

namespace gp {
    void initRNG() {
        rand_dev = make_unique<std::random_device>();
        generator = make_unique<std::mt19937>((*rand_dev)());

        rgb_distribution = make_unique<std::uniform_int_distribution<> >(0, 255);
        angle_distribution = make_unique<std::uniform_int_distribution<> >(0, 360);
        normalized_distribution = make_unique<std::uniform_real_distribution<float> >(0.0f, 1.0f);
    }

    ColorRGB randomRGB() {
        GP_CORE_INFO("gp::randomRGB()");

        return {
            (*rgb_distribution)(*generator),
            (*rgb_distribution)(*generator),
            (*rgb_distribution)(*generator)
        };
    }

    ColorHex randomHex() {
        GP_CORE_INFO("gp::randomHex()");

        return randomRGB();
    }

    ColorCMYK randomCMYK() {
        GP_CORE_INFO("gp::randomCMYK()");

        return {
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator)
        };
    }

    ColorHSV randomHSV() {
        GP_CORE_INFO("gp::randomHSV()");

        return {
            (*angle_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator)
        };
    }

    ColorHSL randomHSL() {
        GP_CORE_INFO("gp::randomHSL()");

        return {
            (*angle_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator)
        };
    }
}
