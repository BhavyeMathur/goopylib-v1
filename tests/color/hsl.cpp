#include "color.h"


TEST(ColorHSLTests, ColorFromHSL) {
    gp::ColorHSL color{0, 0.1, 0.2};
    EXPECT_NEAR(color.getHue(), 0, 1e-2);
    EXPECT_NEAR(color.getSaturation(), 0.1, 1e-2);
    EXPECT_NEAR(color.getLuminance(), 0.2, 1e-2);

    gp::ColorHSL color1{0, 0.1, 0.2, 0.4};
    EXPECT_NEAR(color1.getHue(), 0, 1e-2);
    EXPECT_NEAR(color1.getSaturation(), 0.1, 1e-2);
    EXPECT_NEAR(color1.getLuminance(), 0.2, 1e-2);
    EXPECT_NEAR(color1.getAlpha(), 0.4, 1e-2);
}

TEST(ColorHSLTests, ColorFromHSLErrors) {
    EXPECT_THROW(auto color = gp::ColorHSL(361, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSL(0, 2, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSL(0, 0, 2), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorHSL(-5, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSL(0, -0.5, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSL(0, 0, -0.5), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorHSL(0, 0, 0, 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSL(0, 0, 0, -0.5), std::invalid_argument);
}

TEST(ColorHSLTests, ColorHSLAttributes) {
    gp::ColorHSL color{0, 0, 0};

    EXPECT_EQ(color.toString(), "ColorHSL(0, 0.00, 0.00)");

    color.setHue(60);
    EXPECT_NEAR(color.getHue(), 60, 1e-2);

    color.setSaturation(0.3);
    EXPECT_NEAR(color.getSaturation(), 0.3, 1e-2);

    color.setLuminance(0.4);
    EXPECT_NEAR(color.getLuminance(), 0.4, 1e-2);

    EXPECT_EQ(color.toString(), "ColorHSL(60, 0.30, 0.40)");
}

TEST(ColorHSLTests, ColorAttributesError) {
    gp::ColorHSL color{0, 0, 0};

    EXPECT_THROW(color.setHue(361), std::invalid_argument);
    EXPECT_THROW(color.setHue(-5), std::invalid_argument);

    EXPECT_THROW(color.setSaturation(2), std::invalid_argument);
    EXPECT_THROW(color.setSaturation(-0.5), std::invalid_argument);

    EXPECT_THROW(color.setLuminance(2), std::invalid_argument);
    EXPECT_THROW(color.setLuminance(-0.5), std::invalid_argument);
}

TEST(ColorHSLTests, ColorRGBAttributes) {
    gp::ColorHSL color{0, 0, 0};

    color.setRed(15);
    EXPECT_COLOR_EQ(color, gp::ColorHSL(0, 1, 0.03));

    color.setGreen(40);
    EXPECT_COLOR_EQ(color, gp::ColorHSL(98, 1, 0.08));

    color.setBlue(60);
    EXPECT_COLOR_EQ(color, gp::ColorHSL(207, 0.6, 0.15));

    EXPECT_EQ(color.toString(), "ColorHSL(207, 0.60, 0.15)");
}

TEST(ColorHSLTests, ColorRGBAttributesAlpha) {
    gp::ColorHSL color{0, 0, 0, 0.5};

    color.setRed(15);
    color.setGreen(40);
    color.setBlue(60);

    EXPECT_EQ(color.toString(), "ColorHSL(207, 0.60, 0.15, alpha=0.50)");
}

TEST(ColorHSLTests, HSLtoRGB) {
    EXPECT_COLOR_EQ(gp::ColorHSL(0, 0, 0).toRGB(), gp::ColorRGB(0, 0, 0));
    EXPECT_COLOR_EQ(gp::ColorHSL(180, 1, 1).toRGB(), gp::ColorRGB(255, 255, 255));

    EXPECT_COLOR_EQ(gp::ColorHSL(191, 0.19, 0.49).toRGB(), gp::ColorRGB(101, 140, 149));
    EXPECT_COLOR_EQ(gp::ColorHSL(29, 0.97, 0.63).toRGB(), gp::ColorRGB(252, 158, 69));
    EXPECT_COLOR_EQ(gp::ColorHSL(260, 0.1, 0.8).toRGB(), gp::ColorRGB(202, 199, 209));
}
