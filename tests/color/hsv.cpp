#include "color.h"


TEST(ColorHSVTests, ColorFromHSV) {
    gp::ColorHSV color{0, 0.1, 0.2};
    EXPECT_NEAR(color.getHue(), 0, 1e-2);
    EXPECT_NEAR(color.getSaturation(), 0.1, 1e-2);
    EXPECT_NEAR(color.getValue(), 0.2, 1e-2);

    gp::ColorHSV color1{0, 0.1, 0.2, 0.4};
    EXPECT_NEAR(color1.getHue(), 0, 1e-2);
    EXPECT_NEAR(color1.getSaturation(), 0.1, 1e-2);
    EXPECT_NEAR(color1.getValue(), 0.2, 1e-2);
    EXPECT_NEAR(color1.getAlpha(), 0.4, 1e-2);
}

TEST(ColorHSVTests, ColorFromHSVErrors) {
    EXPECT_THROW(auto color = gp::ColorHSV(361, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSV(0, 2, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSV(0, 0, 2), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorHSV(-5, 0, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSV(0, -0.5, 0), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSV(0, 0, -0.5), std::invalid_argument);

    EXPECT_THROW(auto color = gp::ColorHSV(0, 0, 0, 2), std::invalid_argument);
    EXPECT_THROW(auto color = gp::ColorHSV(0, 0, 0, -0.5), std::invalid_argument);
}

TEST(ColorHSVTests, ColorHSVAttributes) {
    gp::ColorHSV color{0, 0, 0};

    EXPECT_EQ(color.toString(), "ColorHSV(0, 0.00, 0.00)");

    color.setHue(60);
    EXPECT_NEAR(color.getHue(), 60, 1e-2);

    color.setSaturation(0.3);
    EXPECT_NEAR(color.getSaturation(), 0.3, 1e-2);

    color.setValue(0.4);
    EXPECT_NEAR(color.getValue(), 0.4, 1e-2);

    EXPECT_EQ(color.toString(), "ColorHSV(60, 0.30, 0.40)");
}

TEST(ColorHSVTests, ColorAttributesError) {
    gp::ColorHSV color{0, 0, 0};

    EXPECT_THROW(color.setHue(361), std::invalid_argument);
    EXPECT_THROW(color.setHue(-5), std::invalid_argument);

    EXPECT_THROW(color.setSaturation(2), std::invalid_argument);
    EXPECT_THROW(color.setSaturation(-0.5), std::invalid_argument);

    EXPECT_THROW(color.setValue(2), std::invalid_argument);
    EXPECT_THROW(color.setValue(-0.5), std::invalid_argument);
}

TEST(ColorHSVTests, ColorRGBAttributes) {
    gp::ColorHSV color{0, 0, 0};

    color.setRed(15);
    EXPECT_COLOR_EQ(color, gp::ColorHSV(0, 1, 0.06));

    color.setGreen(40);
    EXPECT_COLOR_EQ(color, gp::ColorHSV(98, 1, 0.16));

    color.setBlue(60);
    EXPECT_COLOR_EQ(color, gp::ColorHSV(207, 0.75, 0.24));

    EXPECT_EQ(color.toString(), "ColorHSV(207, 0.75, 0.24)");
}

TEST(ColorHSVTests, ColorRGBAttributesAlpha) {
    gp::ColorHSV color{0, 0, 0, 0.5};

    color.setRed(15);
    color.setGreen(40);
    color.setBlue(60);

    EXPECT_EQ(color.toString(), "ColorHSV(207, 0.75, 0.24, alpha=0.50)");
}

TEST(ColorHSVTests, HSVtoRGB) {
    EXPECT_COLOR_EQ(gp::ColorHSV(0, 0, 0).toRGB(), gp::ColorRGB(0, 0, 0));
    EXPECT_COLOR_EQ(gp::ColorHSV(180, 1, 1).toRGB(), gp::ColorRGB(0, 255, 255));

    EXPECT_COLOR_EQ(gp::ColorHSV(279, 0.43, 0.21).toRGB(), gp::ColorRGB(45, 31, 54));
    EXPECT_COLOR_EQ(gp::ColorHSV(99, 0.19, 0.48).toRGB(), gp::ColorRGB(107, 122, 99));
    EXPECT_COLOR_EQ(gp::ColorHSV(292, 0.75, 0.26).toRGB(), gp::ColorRGB(60, 17, 66));
}
