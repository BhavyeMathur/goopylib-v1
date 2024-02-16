#include "gtest/gtest.h"
#include <goopylib/goopylib.h>

TEST(CoreColorTests, ColorFromColorSubclass) {
    gp::ColorRGB colorRGB{10, 15, 20, 0.1};
    gp::ColorHex colorHex{"#f05", 0.2};
    gp::ColorCMYK colorCMYK{0.5, 0.6, 0.7, 0.3};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::Color color{colorRGB};  // constructor from subclass
    EXPECT_EQ(color.getRGBAf(), colorRGB.getRGBAf());
    color = colorRGB;  // copy assignment operator
    EXPECT_EQ(color.getRGBAf(), colorRGB.getRGBAf());

    gp::Color color2{colorHex};  // constructor from subclass
    EXPECT_EQ(color2.getRGBAf(), colorHex.getRGBAf());
    color2 = colorHex;  // copy assignment operator
    EXPECT_EQ(color2.getRGBAf(), colorHex.getRGBAf());

    gp::Color color3{colorCMYK};  // constructor from subclass
    EXPECT_EQ(color3.getRGBAf(), colorCMYK.getRGBAf());
    color3 = colorCMYK;  // copy assignment operator
    EXPECT_EQ(color3.getRGBAf(), colorCMYK.getRGBAf());

    gp::Color color4{colorHSL};  // constructor from subclass
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());
    color4 = colorHSL;  // copy assignment operator
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());

    gp::Color color5{colorHSV};  // constructor from subclass
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
    color5 = colorHSV;  // copy assignment operator
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
}

TEST(CoreColorTests, ColorFromRGB) {
    gp::Color color{0, 10, 20};
    EXPECT_EQ(color.getRed(), 0);
    EXPECT_EQ(color.getGreen(), 10);
    EXPECT_EQ(color.getBlue(), 20);
    EXPECT_EQ(color.getAlpha(), 1);

    gp::Color color2{0, 10, 20, 0.5};
    EXPECT_EQ(color2.getAlpha(), 0.5);
}

TEST(CoreColorTests, ColorFromRGBErrors) {
    EXPECT_THROW(auto color = gp::Color(300, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 300, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 0, 300), std::invalid_argument);

    EXPECT_THROW(auto color = gp::Color(-30, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, -30, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 0, -30), std::invalid_argument);

    EXPECT_THROW(auto color = gp::Color(0, 0, 0, 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 0, 0, -0.5), std::invalid_argument);
}

TEST(CoreColorTests, ColorFromHex) {
    gp::Color color{"#f01"};
    EXPECT_EQ(color.getRed(), 255);
    EXPECT_EQ(color.getGreen(), 0);
    EXPECT_EQ(color.getBlue(), 17);
    EXPECT_EQ(color.getAlpha(), 1);

    gp::Color color1{"f01"};
    EXPECT_EQ(color1.getRed(), 255);
    EXPECT_EQ(color1.getGreen(), 0);
    EXPECT_EQ(color1.getBlue(), 17);
    EXPECT_EQ(color1.getAlpha(), 1);

    gp::Color color2{"#f01001"};
    EXPECT_EQ(color2.getRed(), 240);
    EXPECT_EQ(color2.getGreen(), 16);
    EXPECT_EQ(color2.getBlue(), 1);
    EXPECT_EQ(color2.getAlpha(), 1);

    gp::Color color3{"f01001"};
    EXPECT_EQ(color3.getRed(), 240);
    EXPECT_EQ(color3.getGreen(), 16);
    EXPECT_EQ(color3.getBlue(), 1);
    EXPECT_EQ(color3.getAlpha(), 1);

    gp::Color color4{"#f01", 0.5};
    EXPECT_EQ(color4.getRed(), 255);
    EXPECT_EQ(color4.getGreen(), 0);
    EXPECT_EQ(color4.getBlue(), 17);
    EXPECT_EQ(color4.getAlpha(), 0.5);
}

TEST(CoreColorTests, ColorFromHexErrors) {
    EXPECT_THROW(auto color = gp::Color("#0000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("0000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("#00000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("#0000000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("0000000"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("#g00"), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("gf0011"), std::invalid_argument);

    EXPECT_THROW(auto color = gp::Color("#000", 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color("#000", -0.5), std::invalid_argument);
}

TEST(CoreColorTests, ColorToString) {
    gp::Color color{0, 10, 20};
    EXPECT_EQ(color.toString(), "Color(0, 10, 20, 1.00)");
}

TEST(CoreColorTests, ColorAttributes) {
    gp::Color color{0, 0, 0};

    color.setRed(153);
    EXPECT_EQ(color.getRed(), 153);
    EXPECT_EQ(color.getRedf(), 0.6f);

    color.setGreen(102);
    EXPECT_EQ(color.getGreen(), 102);
    EXPECT_EQ(color.getGreenf(), 0.4f);

    color.setBlue(51);
    EXPECT_EQ(color.getBlue(), 51);
    EXPECT_EQ(color.getBluef(), 0.2f);

    color.setAlpha(0.5);
    EXPECT_EQ(color.getAlpha(), 0.5);
}

TEST(CoreColorTests, ColorAttributesError) {
    gp::Color color{0, 0, 0};

    EXPECT_THROW(color.setRed(300), std::invalid_argument);
    EXPECT_THROW(color.setRed(-30), std::invalid_argument);

    EXPECT_THROW(color.setGreen(300), std::invalid_argument);
    EXPECT_THROW(color.setGreen(-30), std::invalid_argument);

    EXPECT_THROW(color.setBlue(300), std::invalid_argument);
    EXPECT_THROW(color.setBlue(-30), std::invalid_argument);

    EXPECT_THROW(color.setAlpha(2), std::invalid_argument);
    EXPECT_THROW(color.setAlpha(-0.5), std::invalid_argument);
}
