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

TEST(CoreColorTests, ColorFromRGBA) {
    gp::Color color{0, 10, 20};
    EXPECT_EQ(color.getRed(), 0);
    EXPECT_EQ(color.getGreen(), 10);
    EXPECT_EQ(color.getBlue(), 20);
    EXPECT_EQ(color.getAlpha(), 1);

    gp::Color color2{0, 10, 20, 0.5};
    EXPECT_EQ(color2.getAlpha(), 0.5);
}

TEST(CoreColorTests, ColorFromRGBAErrors) {
    EXPECT_THROW(auto color = gp::Color(300, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 300, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 0, 300), std::invalid_argument);

    EXPECT_THROW(auto color = gp::Color(-30, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, -30, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 0, -30), std::invalid_argument);

    EXPECT_THROW(auto color = gp::Color(0, 0, 0, 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::Color(0, 0, 0, -0.5), std::invalid_argument);
}
