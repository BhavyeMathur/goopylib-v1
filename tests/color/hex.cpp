#include "gtest/gtest.h"
#include <../../src/goopylib.h>

TEST(ColorHexTests, ColorFromColorSubclass) {
    gp::Color color{"#f05", 0.2};
    gp::ColorRGB colorRGB{10, 15, 20, 0.1};
    gp::ColorCMYK colorCMYK{0.5, 0.6, 0.7, 0.3};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorHex color1{color}; // constructor from color
    EXPECT_EQ(color1.getRGBAf(), color.getRGBAf());

    gp::ColorHex color2{colorRGB}; // constructor from color
    EXPECT_EQ(color2.getRGBAf(), colorRGB.getRGBAf());

    gp::ColorHex color3{colorCMYK}; // constructor from color
    EXPECT_EQ(color3.getRGBAf(), colorCMYK.getRGBAf());

    gp::ColorHex color4{colorHSL}; // constructor from color
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());

    gp::ColorHex color5{colorHSV}; // constructor from color
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
}

TEST(ColorHexTests, ColorFromCopyAssignment) {
    gp::Color color{"#f05", 0.2};
    gp::ColorRGB colorRGB{10, 15, 20, 0.1};
    gp::ColorCMYK colorCMYK{0.5, 0.6, 0.7, 0.3};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorHex colorHex{"#000"};

    colorHex = color;
    EXPECT_EQ(colorHex.getRGBAf(), color.getRGBAf());

    colorHex = colorRGB;
    EXPECT_EQ(colorHex.getRGBAf(), colorRGB.getRGBAf());

    colorHex = colorCMYK;
    EXPECT_EQ(colorHex.getRGBAf(), colorCMYK.getRGBAf());

    colorHex = colorHSL;
    EXPECT_EQ(colorHex.getRGBAf(), colorHSL.getRGBAf());

    colorHex = colorHSV;
    EXPECT_EQ(colorHex.getRGBAf(), colorHSV.getRGBAf());
}

TEST(ColorHexTests, ColorFromHex) {
    gp::ColorHex color{"#f01"};
    EXPECT_EQ(color.getRed(), 255);
    EXPECT_EQ(color.getGreen(), 0);
    EXPECT_EQ(color.getBlue(), 17);
    EXPECT_EQ(color.getAlpha(), 1);

    gp::ColorHex color1{"abc"};
    EXPECT_EQ(color1.getRed(), 170);
    EXPECT_EQ(color1.getGreen(), 187);
    EXPECT_EQ(color1.getBlue(), 204);
    EXPECT_EQ(color1.getAlpha(), 1);

    gp::ColorHex color2{"#ddeefa"};
    EXPECT_EQ(color2.getRed(), 221);
    EXPECT_EQ(color2.getGreen(), 238);
    EXPECT_EQ(color2.getBlue(), 250);
    EXPECT_EQ(color2.getAlpha(), 1);

    gp::ColorHex color3{"f01001"};
    EXPECT_EQ(color3.getRed(), 240);
    EXPECT_EQ(color3.getGreen(), 16);
    EXPECT_EQ(color3.getBlue(), 1);
    EXPECT_EQ(color3.getAlpha(), 1);

    gp::ColorHex color4{"#f01", 0.5};
    EXPECT_EQ(color4.getRed(), 255);
    EXPECT_EQ(color4.getGreen(), 0);
    EXPECT_EQ(color4.getBlue(), 17);
    EXPECT_EQ(color4.getAlpha(), 0.5);
}

TEST(ColorHexTests, ColorFromCapitalHex) {
    gp::ColorHex color{"#F01"};
    EXPECT_EQ(color.getRed(), 255);
    EXPECT_EQ(color.getGreen(), 0);
    EXPECT_EQ(color.getBlue(), 17);
    EXPECT_EQ(color.getAlpha(), 1);

    gp::ColorHex color1{"ABC"};
    EXPECT_EQ(color1.getRed(), 170);
    EXPECT_EQ(color1.getGreen(), 187);
    EXPECT_EQ(color1.getBlue(), 204);
    EXPECT_EQ(color1.getAlpha(), 1);

    gp::ColorHex color2{"#DDEEFA"};
    EXPECT_EQ(color2.getRed(), 221);
    EXPECT_EQ(color2.getGreen(), 238);
    EXPECT_EQ(color2.getBlue(), 250);
    EXPECT_EQ(color2.getAlpha(), 1);
}


TEST(ColorHexTests, ColorFromHexErrors) {
    EXPECT_THROW(auto color = gp::ColorHex("#0000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("0000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("#00000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("#0000000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("0000000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("#g00"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("gf0011"), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorHex("#000", 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHex("#000", -0.5), std::invalid_argument);
}


TEST(ColorHexTests, ColorToString) {
    gp::ColorHex color{"#FF00ab"};
    EXPECT_EQ(color.toString(), "#ff00ab");
}

TEST(ColorHexTests, HextoRGB) {
    EXPECT_EQ(gp::ColorHex("#000000").toRGB(), gp::ColorRGB(0, 0, 0));
    EXPECT_EQ(gp::ColorHex("#ffffff").toRGB(), gp::ColorRGB(255, 255, 255));
    EXPECT_EQ(gp::ColorHex("#7d7d7d").toRGB(), gp::ColorRGB(125, 125, 125));

    EXPECT_EQ(gp::ColorHex("#ff0000").toRGB(), gp::ColorRGB(255, 0, 0));
    EXPECT_EQ(gp::ColorHex("#00ff00").toRGB(), gp::ColorRGB(0, 255, 0));
    EXPECT_EQ(gp::ColorHex("#0000ff").toRGB(), gp::ColorRGB(0, 0, 255));

    EXPECT_EQ(gp::ColorHex("#50008c").toRGB(), gp::ColorRGB(80, 0, 140));
    EXPECT_EQ(gp::ColorHex("#00323c").toRGB(), gp::ColorRGB(0, 50, 60));
}

TEST(ColorHexTests, HextoRGBwithSetters) {
    gp::ColorHex color{"#FF0000"};

    color.setRed(17);
    EXPECT_EQ(color.toRGB(), gp::ColorRGB(17, 0, 0));

    color.setBlue(34);
    EXPECT_EQ(color.toRGB(), gp::ColorRGB(17, 0, 34));

    color.setGreen(51);
    EXPECT_EQ(color.toRGB(), gp::ColorRGB(17, 51, 34));
}
