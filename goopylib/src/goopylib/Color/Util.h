#pragma once

#include "Color.h"
#include "ColorConversions.h"

namespace gp {
    GPAPI ColorRGB randomRGB();

    GPAPI ColorHex randomHex();

    GPAPI ColorCMYK randomCMYK();

    GPAPI ColorHSV randomHSV();

    GPAPI ColorHSL randomHSL();
}
