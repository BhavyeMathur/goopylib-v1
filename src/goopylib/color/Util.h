#pragma once

#include "gp.h"
#include "ColorRGB.h"
#include "ColorHex.h"
#include "ColorCMYK.h"
#include "ColorHSL.h"
#include "ColorHSV.h"

namespace gp {
    void initColorRNG();

    /**
     * @return a random color
     */
    [[nodiscard]] GPAPI Color randomColor();

    /**
     * @return a random RGB color
     */
    [[nodiscard]] GPAPI ColorRGB randomRGB();

    /**
     * @return a random Hexadecimal color
     */
    [[nodiscard]] GPAPI ColorHex randomHex();

    /**
     * @return a random CMYK color
     */
    [[nodiscard]] GPAPI ColorCMYK randomCMYK();

    /**
     * @return a random HSV color
     */
    [[nodiscard]] GPAPI ColorHSV randomHSV();

    /**
     * @return a random HSL color
     */
    [[nodiscard]] GPAPI ColorHSL randomHSL();
}
