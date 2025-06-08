#include "color.h"


TEST(ColorRGBTests, ColorFromColorSubclass) {
    gp::Color color{10, 15, 20, 0.1};
    gp::ColorHex colorHex{"#f05", 0.2};
    gp::ColorCMYK colorCMYK{0.5, 0.6, 0.7, 0.3};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorRGB color1{color}; // constructor from color
    EXPECT_EQ(color1.getRGBAf(), color.getRGBAf());

    gp::ColorRGB color2{colorHex}; // constructor from color
    EXPECT_EQ(color2.getRGBAf(), colorHex.getRGBAf());

    gp::ColorRGB color3{colorCMYK}; // constructor from color
    EXPECT_EQ(color3.getRGBAf(), colorCMYK.getRGBAf());

    gp::ColorRGB color4{colorHSL}; // constructor from color
    EXPECT_EQ(color4.getRGBAf(), colorHSL.getRGBAf());

    gp::ColorRGB color5{colorHSV}; // constructor from color
    EXPECT_EQ(color5.getRGBAf(), colorHSV.getRGBAf());
}

TEST(ColorRGBTests, ColorFromCopyAssignment) {
    gp::Color color{10, 15, 20, 0.1};
    gp::ColorHex colorHex{"#f05", 0.2};
    gp::ColorCMYK colorCMYK{0.5, 0.6, 0.7, 0.3};
    gp::ColorHSL colorHSL{10, 0.2, 0.3, 0.4};
    gp::ColorHSV colorHSV{20, 0.3, 0.4, 0.5};

    gp::ColorRGB colorRGB{0, 0, 0};

    colorRGB = color;
    EXPECT_EQ(colorRGB.getRGBAf(), color.getRGBAf());

    colorRGB = colorHex;
    EXPECT_EQ(colorRGB.getRGBAf(), colorHex.getRGBAf());

    colorRGB = colorCMYK;
    EXPECT_EQ(colorRGB.getRGBAf(), colorCMYK.getRGBAf());

    colorRGB = colorHSL;
    EXPECT_EQ(colorRGB.getRGBAf(), colorHSL.getRGBAf());

    colorRGB = colorHSV;
    EXPECT_EQ(colorRGB.getRGBAf(), colorHSV.getRGBAf());
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
    EXPECT_EQ(gp::ColorRGB(0, 0, 0).toHex(), "#000000");
    EXPECT_EQ(gp::ColorRGB(255, 255, 255).toHex(), "#ffffff");
    EXPECT_EQ(gp::ColorRGB(125, 125, 125).toHex(), "#7d7d7d");

    EXPECT_EQ(gp::ColorRGB(255, 0, 0).toHex(), "#ff0000");
    EXPECT_EQ(gp::ColorRGB(0, 255, 0).toHex(), "#00ff00");
    EXPECT_EQ(gp::ColorRGB(0, 0, 255).toHex(), "#0000ff");

    EXPECT_EQ(gp::ColorRGB(80, 0, 140).toHex(), "#50008c");
    EXPECT_EQ(gp::ColorRGB(0, 50, 60).toHex(), "#00323c");
}

TEST(ColorRGBTests, RGBtoCMYK) {
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 0, 0).toCMYK(), gp::ColorCMYK(0, 0, 0, 1));
    EXPECT_COLOR_EQ(gp::ColorRGB(255, 255, 255).toCMYK(), gp::ColorCMYK(0, 0, 0, 0));
    EXPECT_COLOR_EQ(gp::ColorRGB(125, 125, 125).toCMYK(), gp::ColorCMYK(0, 0, 0, 0.51));

    EXPECT_COLOR_EQ(gp::ColorRGB(255, 0, 0).toCMYK(), gp::ColorCMYK(0, 1, 1, 0));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 255, 0).toCMYK(), gp::ColorCMYK(1, 0, 1, 0));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 0, 255).toCMYK(), gp::ColorCMYK(1, 1, 0, 0));

    EXPECT_COLOR_EQ(gp::ColorRGB(80, 0, 140).toCMYK(), gp::ColorCMYK(0.43, 1.0, 0.0, 0.45));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 50, 60).toCMYK(), gp::ColorCMYK(1.0, 0.17, 0.0, 0.76));
}

TEST(ColorRGBTests, RGBtoHSV) {
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 0, 0).toHSV(), gp::ColorHSV(0, 0, 0));
    EXPECT_COLOR_EQ(gp::ColorRGB(255, 255, 255).toHSV(), gp::ColorHSV(0, 0, 1));
    EXPECT_COLOR_EQ(gp::ColorRGB(125, 125, 125).toHSV(), gp::ColorHSV(0, 0, 0.49));

    EXPECT_COLOR_EQ(gp::ColorRGB(255, 0, 0).toHSV(), gp::ColorHSV(0, 1, 1));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 255, 0).toHSV(), gp::ColorHSV(120, 1, 1));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 0, 255).toHSV(), gp::ColorHSV(240, 1, 1));

    EXPECT_COLOR_EQ(gp::ColorRGB(80, 0, 140).toHSV(), gp::ColorHSV(274, 1, 0.55));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 50, 60).toHSV(), gp::ColorHSV(190, 1, 0.24));
}

TEST(ColorRGBTests, RGBtoHSL) {
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 0, 0).toHSL(), gp::ColorHSL(0, 0, 0));
    EXPECT_COLOR_EQ(gp::ColorRGB(255, 255, 255).toHSL(), gp::ColorHSL(0, 0, 1));
    EXPECT_COLOR_EQ(gp::ColorRGB(125, 125, 125).toHSL(), gp::ColorHSL(0, 0, 0.49));

    EXPECT_COLOR_EQ(gp::ColorRGB(255, 0, 0).toHSL(), gp::ColorHSL(0, 1, 0.5));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 255, 0).toHSL(), gp::ColorHSL(120, 1, 0.5));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 0, 255).toHSL(), gp::ColorHSL(240, 1, 0.5));

    EXPECT_COLOR_EQ(gp::ColorRGB(80, 0, 140).toHSL(), gp::ColorHSL(274, 1, 0.27));
    EXPECT_COLOR_EQ(gp::ColorRGB(0, 50, 60).toHSL(), gp::ColorHSL(190, 1, 0.12));
}
