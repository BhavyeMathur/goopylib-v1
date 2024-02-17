#include "color.h"


TEST(ColorCMYKTests, ColorFromColorSubclass) {
    gp::Color color{"#f05", 0.2};
    gp::ColorRGB colorRGB{10, 15, 20, 0.1};
    gp::ColorHex colorHex{"#aaa", 0.2};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorCMYK color1{color};
    EXPECT_EQ(color1.getRGBAf(), color.getRGBAf());
    EXPECT_EQ(color1, color.toCMYK());

    gp::ColorCMYK color2{colorRGB};
    EXPECT_EQ(color2.getRGBAf(), colorRGB.getRGBAf());
    EXPECT_EQ(color2, colorRGB.toCMYK());

    gp::ColorCMYK color3{colorHex};
    EXPECT_EQ(color3.getRGBAf(), colorHex.getRGBAf());
    EXPECT_EQ(color3, colorHex.toCMYK());

    gp::ColorCMYK color4{colorHSL};
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());
    EXPECT_EQ(color4, colorHSL.toCMYK());

    gp::ColorCMYK color5{colorHSV};
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
    EXPECT_EQ(color5, colorHSV.toCMYK());
}

TEST(ColorCMYKTests, ColorFromCopyAssignment) {
    gp::Color color{"#f05", 0.2};
    gp::ColorRGB colorRGB{10, 15, 20, 0.1};
    gp::ColorHex colorHex{"#aaa", 0.2};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorCMYK colorCMYK{0, 0, 0, 1};

    colorCMYK = color;
    EXPECT_EQ(colorCMYK.getRGBAf(), color.getRGBAf());
    EXPECT_EQ(colorCMYK, color.toCMYK());

    colorCMYK = colorRGB;
    EXPECT_EQ(colorCMYK.getRGBAf(), colorRGB.getRGBAf());
    EXPECT_EQ(colorCMYK, colorRGB.toCMYK());

    colorCMYK = colorHex;
    EXPECT_EQ(colorCMYK.getRGBAf(), colorCMYK.getRGBAf());
    EXPECT_EQ(colorCMYK, colorHex.toCMYK());

    colorCMYK = colorHSL;
    EXPECT_EQ(colorCMYK.getRGBAf(), colorHSL.getRGBAf());
    EXPECT_EQ(colorCMYK, colorHSL.toCMYK());

    colorCMYK = colorHSV;
    EXPECT_EQ(colorCMYK.getRGBAf(), colorHSV.getRGBAf());
    EXPECT_EQ(colorCMYK, colorHSV.toCMYK());
}

TEST(ColorCMYKTests, ColorFromHex) {
    gp::ColorCMYK color{0, 0.1, 0.2, 0.3};
    EXPECT_EQ(color.getCyan(), 0);
    EXPECT_EQ(color.getMagenta(), 0.1);
    EXPECT_EQ(color.getYellow(), 0.2);
    EXPECT_EQ(color.getKey(), 0.3);

    gp::ColorCMYK color1{0, 0.1, 0.2, 0.3, 0.4};
    EXPECT_EQ(color1.getCyan(), 0);
    EXPECT_EQ(color1.getMagenta(), 0.1);
    EXPECT_EQ(color1.getYellow(), 0.2);
    EXPECT_EQ(color1.getKey(), 0.3);
    EXPECT_EQ(color1.getAlpha(), 0.4);
}

TEST(ColorCMYKTests, ColorFromHexErrors) {
    EXPECT_THROW(auto color = gp::ColorCMYK(2, 0, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, 2, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, 0, 2, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, 0, 0, 2), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorCMYK(-0.5, 0, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, -0.5, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, 0, -0.5, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, 0, 0, -0.5), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorCMYK(0, 0, 0, 0, 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorCMYK(0, 0, 0, 0, -0.5), std::invalid_argument);
}

TEST(ColorCMYKTests, ColorCMYKAttributes) {
    gp::ColorCMYK color{0, 0, 0, 0};

    color.setCyan(0.2);
    EXPECT_EQ(color.getCyan(), 0.2);

    color.setMagenta(0.3);
    EXPECT_EQ(color.getMagenta(), 0.3);

    color.setYellow(0.4);
    EXPECT_EQ(color.getYellow(), 0.4);

    color.setKey(0.5);
    EXPECT_EQ(color.getKey(), 0.5);

    EXPECT_EQ(color.toString(), "ColorCMYK(0.20, 0.30, 0.40, 0.50, 1.0)");
}

TEST(ColorCMYKTests, ColorAttributesError) {
    gp::ColorCMYK color{0, 0, 0, 0};

    EXPECT_THROW(color.setCyan(2), std::invalid_argument);
    EXPECT_THROW(color.setCyan(-0.5), std::invalid_argument);

    EXPECT_THROW(color.setMagenta(2), std::invalid_argument);
    EXPECT_THROW(color.setMagenta(-0.5), std::invalid_argument);

    EXPECT_THROW(color.setYellow(2), std::invalid_argument);
    EXPECT_THROW(color.setYellow(-0.5), std::invalid_argument);

    EXPECT_THROW(color.setKey(2), std::invalid_argument);
    EXPECT_THROW(color.setKey(-0.5), std::invalid_argument);
}

TEST(ColorCMYKTests, ColorRGBAttributes) {
    gp::ColorCMYK color{0, 0, 0, 0};

    color.setRed(15);
    EXPECT_COLOR_EQ(color, gp::ColorCMYK(0.94, 0, 0, 0));

    color.setGreen(40);
    EXPECT_EQ(color, gp::ColorCMYK(0.94, 0.8, 0, 0));

    color.setBlue(60);
    EXPECT_EQ(color, gp::ColorCMYK(0.75, 0.33, 0, 0.76));

    EXPECT_EQ(color.toString(), "ColorCMYK(0.75, 0.33, 0.00, 0.76, 1.0)");
}
