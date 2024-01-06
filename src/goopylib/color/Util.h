#pragma once

#include "gp.h"
#include "ColorRGB.h"
#include "ColorHex.h"
#include "ColorCMYK.h"
#include "ColorHSL.h"
#include "ColorHSV.h"

namespace gp {
    /**
     * @return a random RGB color
     */
    [[nodiscard]] ColorRGB GPAPI randomRGB();

    /**
     * @return a random Hexadecimal color
     */
    [[nodiscard]] ColorHex GPAPI randomHex();

    /**
     * @return a random CMYK color
     */
    [[nodiscard]] ColorCMYK GPAPI randomCMYK();

    /**
     * @return a random HSV color
     */
    [[nodiscard]] ColorHSV GPAPI randomHSV();

    /**
     * @return a random HSL color
     */
    [[nodiscard]] ColorHSL GPAPI randomHSL();
}
