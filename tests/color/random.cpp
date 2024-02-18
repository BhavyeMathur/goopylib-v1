#include "color.h"


TEST(ColorRandomTests, ColorFromColorSubclass) {
    gp::Color color = gp::randomColor();
    gp::ColorRGB colorRGB = gp::randomRGB();
    gp::ColorHex colorHex = gp::randomHex();
    gp::ColorCMYK colorCMYK = gp::randomCMYK();
    gp::ColorHSL colorHSL = gp::randomHSL();
    gp::ColorHSV colorHSV = gp::randomHSV();
}
