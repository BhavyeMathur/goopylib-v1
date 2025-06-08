#define GP_LOGGING_LEVEL 3

#include "core/Core.h"
#include "color/Util.h"
#include "debug/Error.h"

#include <random>

std::unique_ptr<std::random_device> rand_dev;
std::unique_ptr<std::mt19937> generator;

std::unique_ptr<std::uniform_int_distribution<> > rgb_distribution;
std::unique_ptr<std::uniform_int_distribution<> > angle_distribution;
std::unique_ptr<std::uniform_real_distribution<float> > normalized_distribution;


namespace gp {
    void initColorRNG() {
        GP_CORE_INFO("gp::initRNG()");

        try {
            rand_dev = make_unique<std::random_device>();
            generator = make_unique<std::mt19937>((*rand_dev)());

            rgb_distribution = make_unique<std::uniform_int_distribution<> >(0, 255);
            angle_distribution = make_unique<std::uniform_int_distribution<> >(0, 360);
            normalized_distribution = make_unique<std::uniform_real_distribution<float> >(0.0f, 1.0f);
        }
        catch (...) {
            GP_RUNTIME_ERROR("gp::initRNG() failed to initialize random color generator");
        }
    }

    Color randomColor() {
        GP_CORE_INFO("gp::randomColor()");
        GP_CHECK_INITIALISED("gp::randomColor()");

        return {
            (*rgb_distribution)(*generator),
            (*rgb_distribution)(*generator),
            (*rgb_distribution)(*generator)
        };
    }

    ColorRGB randomRGB() {
        GP_CORE_INFO("gp::randomRGB()");
        GP_CHECK_INITIALISED("gp::randomRGB()");
        return randomColor();
    }

    ColorHex randomHex() {
        GP_CORE_INFO("gp::randomHex()");
        GP_CHECK_INITIALISED("gp::randomHex()");
        return randomRGB();
    }

    ColorCMYK randomCMYK() {
        GP_CORE_INFO("gp::randomCMYK()");
        GP_CHECK_INITIALISED("gp::randomCMYK()");

        return {
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator)
        };
    }

    ColorHSV randomHSV() {
        GP_CORE_INFO("gp::randomHSV()");
        GP_CHECK_INITIALISED("gp::randomHSV()");

        return {
            (*angle_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator)
        };
    }

    ColorHSL randomHSL() {
        GP_CORE_INFO("gp::randomHSL()");
        GP_CHECK_INITIALISED("gp::randomHSL()");

        return {
            (*angle_distribution)(*generator),
            (*normalized_distribution)(*generator),
            (*normalized_distribution)(*generator)
        };
    }
}
