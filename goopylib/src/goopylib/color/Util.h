#pragma once

#include "gp.h"
#include "Color.h"

namespace gp {
    /**
     * @return a random RGB color
     */
    ColorRGB randomRGB();

    /**
     * @return a random Hexadecimal color
     */
    ColorHex randomHex();

    /**
     * @return a random CMYK color
     */
    ColorCMYK randomCMYK();

    /**
     * @return a random HSV color
     */
    ColorHSV randomHSV();

    /**
     * @return a random HSL color
     */
    ColorHSL randomHSL();
}
