#include "Util.h"
#include "ColorConversions.h"

#if !GP_LOG_COLOR_UTIL
#undef GP_LOGGING_LEVEL
#endif

#include "goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_COLOR_UTIL
#undef GP_VALUE_CHECKING
#endif

#include "goopylib/debug/Error.h"

#include <random>

static std::random_device rand_dev;
static std::mt19937 generator(rand_dev());

static std::uniform_int_distribution<int> rgb_distribution(0, 255);
static std::uniform_int_distribution<int> angle_distribution(0, 360);
static std::uniform_real_distribution<float> normalized_distribution(0.0f, 1.0f);

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
