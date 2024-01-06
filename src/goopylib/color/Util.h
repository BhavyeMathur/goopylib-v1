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
    ColorRGB GPAPI randomRGB();

    /**
     * @return a random Hexadecimal color
     */
    ColorHex GPAPI randomHex();

    /**
     * @return a random CMYK color
     */
    ColorCMYK GPAPI randomCMYK();

    /**
     * @return a random HSV color
     */
    ColorHSV GPAPI randomHSV();

    /**
     * @return a random HSL color
     */
    ColorHSL GPAPI randomHSL();
}
