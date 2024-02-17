#include "gtest/gtest.h"
#include <goopylib/goopylib.h>

TEST(ColorRGBTests, ColorFromColorSubclass) {
    gp::Color color{10, 15, 20, 0.1};
    gp::ColorHex colorHex{"#f05", 0.2};
    gp::ColorCMYK colorCMYK{0.5, 0.6, 0.7, 0.3};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorRGB colorRGB{color}; // constructor from color
    EXPECT_EQ(color.getRGBAf(), colorRGB.getRGBAf());
    color = colorRGB; // copy assignment operator
    EXPECT_EQ(color.getRGBAf(), colorRGB.getRGBAf());

    gp::ColorRGB color2{colorHex}; // constructor from color
    EXPECT_EQ(color2.getRGBAf(), colorHex.getRGBAf());
    color2 = colorHex; // copy assignment operator
    EXPECT_EQ(color2.getRGBAf(), colorHex.getRGBAf());

    gp::ColorRGB color3{colorCMYK}; // constructor from color
    EXPECT_EQ(color3.getRGBAf(), colorCMYK.getRGBAf());
    color3 = colorCMYK; // copy assignment operator
    EXPECT_EQ(color3.getRGBAf(), colorCMYK.getRGBAf());

    gp::ColorRGB color4{colorHSL}; // constructor from color
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());
    color4 = colorHSL; // copy assignment operator
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());

    gp::ColorRGB color5{colorHSV}; // constructor from color
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
    color5 = colorHSV; // copy assignment operator
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
}

TEST(ColorRGBTests, ColorFromRGB) {
    gp::ColorRGB color{0, 10, 20};
    EXPECT_EQ(color.getRed(), 0);
    EXPECT_EQ(color.getGreen(), 10);
    EXPECT_EQ(color.getBlue(), 20);
    EXPECT_EQ(color.getAlpha(), 1);

    gp::ColorRGB color2{0, 10, 20, 0.5};
    EXPECT_EQ(color2.getAlpha(), 0.5);
}

TEST(ColorRGBTests, ColorFromRGBErrors) {
    EXPECT_THROW(auto color = gp::ColorRGB(300, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorRGB(0, 300, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorRGB(0, 0, 300), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorRGB(-30, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorRGB(0, -30, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorRGB(0, 0, -30), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorRGB(0, 0, 0, 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorRGB(0, 0, 0, -0.5), std::invalid_argument);
}

TEST(ColorRGBTests, RGBtoHex) {
    EXPECT_EQ(gp::rgb::toHex(0, 0, 0), "#000000");
    EXPECT_EQ(gp::rgb::toHex(255, 255, 255), "#ffffff");
    EXPECT_EQ(gp::rgb::toHex(125, 125, 125), "#7d7d7d");

    EXPECT_EQ(gp::rgb::toHex(255, 0, 0), "#ff0000");
    EXPECT_EQ(gp::rgb::toHex(0, 255, 0), "#00ff00");
    EXPECT_EQ(gp::rgb::toHex(0, 0, 255), "#0000ff");

    EXPECT_EQ(gp::rgb::toHex(80, 0, 140), "#50008c");
    EXPECT_EQ(gp::rgb::toHex(0, 50, 60), "#00323c");
}

TEST(ColorRGBTests, RGBtoCMYK) {
    EXPECT_EQ(gp::rgb::toCMYK(0, 0, 0), gp::CMYK(0, 0, 0, 1));
    EXPECT_EQ(gp::rgb::toCMYK(255, 255, 255), gp::CMYK(0, 0, 0, 0));
    EXPECT_EQ(gp::rgb::toCMYK(125, 125, 125), gp::CMYK(0, 0, 0, 0.51));

    EXPECT_EQ(gp::rgb::toCMYK(255, 0, 0), gp::CMYK(0, 1, 1, 0));
    EXPECT_EQ(gp::rgb::toCMYK(0, 255, 0), gp::CMYK(1, 0, 1, 0));
    EXPECT_EQ(gp::rgb::toCMYK(0, 0, 255), gp::CMYK(1, 1, 0, 0));

    EXPECT_EQ(gp::rgb::toCMYK(80, 0, 140), gp::CMYK(0.43, 1.0, 0.0, 0.45));
    EXPECT_EQ(gp::rgb::toCMYK(0, 50, 60), gp::CMYK(1.0, 0.17, 0.0, 0.76));
}

TEST(ColorRGBTests, RGBtoHSV) {
    EXPECT_EQ(gp::rgb::toHSV(0, 0, 0), gp::HSV(0, 0, 0));
    EXPECT_EQ(gp::rgb::toHSV(255, 255, 255), gp::HSV(0, 0, 1));
    EXPECT_EQ(gp::rgb::toHSV(125, 125, 125), gp::HSV(0, 0, 0.49));

    EXPECT_EQ(gp::rgb::toHSV(255, 0, 0), gp::HSV(0, 1, 1));
    EXPECT_EQ(gp::rgb::toHSV(0, 255, 0), gp::HSV(120, 1, 1));
    EXPECT_EQ(gp::rgb::toHSV(0, 0, 255), gp::HSV(240, 1, 1));

    EXPECT_EQ(gp::rgb::toHSV(80, 0, 140), gp::HSV(274, 1, 0.55));
    EXPECT_EQ(gp::rgb::toHSV(0, 50, 60), gp::HSV(190, 1, 0.24));
}

TEST(ColorRGBTests, RGBtoHSL) {
    EXPECT_EQ(gp::rgb::toHSL(0, 0, 0), gp::HSL(0, 0, 0));
    EXPECT_EQ(gp::rgb::toHSL(255, 255, 255), gp::HSL(0, 0, 1));
    EXPECT_EQ(gp::rgb::toHSL(125, 125, 125), gp::HSL(0, 0, 0.49));

    EXPECT_EQ(gp::rgb::toHSL(255, 0, 0), gp::HSL(0, 1, 0.5));
    EXPECT_EQ(gp::rgb::toHSL(0, 255, 0), gp::HSL(120, 1, 0.5));
    EXPECT_EQ(gp::rgb::toHSL(0, 0, 255), gp::HSL(240, 1, 0.5));

    EXPECT_EQ(gp::rgb::toHSL(80, 0, 140), gp::HSL(274, 1, 0.27));
    EXPECT_EQ(gp::rgb::toHSL(0, 50, 60).toString(), gp::HSL(190, 1, 0.12));
}
