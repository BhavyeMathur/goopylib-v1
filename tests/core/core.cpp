#include "gtest/gtest.h"
#include <goopylib.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"

TEST(CoreTests, InitAndTermination) {
    EXPECT_FALSE(gp::hasActiveContext());

    gp::init();
    EXPECT_TRUE(gp::isInitialized());
    gp::init(); // test twice
    EXPECT_TRUE(gp::isInitialized());

    EXPECT_FALSE(gp::hasActiveContext());

    gp::terminate();
    EXPECT_FALSE(gp::isInitialized());
    gp::terminate(); // test twice
    EXPECT_FALSE(gp::isInitialized());

    EXPECT_FALSE(gp::hasActiveContext());
}

TEST(CoreTests, ScreenParams) {
    gp::init();

    EXPECT_GT(gp::getRefreshRate(), 0);
    EXPECT_GT(gp::getScreenWidth(), 0);
    EXPECT_GT(gp::getScreenHeight(), 0);
    EXPECT_GT(gp::getNumberOfMonitors(), 0);
}

TEST(CoreTests, ScreenParamsError) {
    gp::terminate();

    EXPECT_THROW(gp::getRefreshRate(), std::runtime_error);
    EXPECT_THROW(gp::getScreenWidth(), std::runtime_error);
    EXPECT_THROW(gp::getScreenHeight(), std::runtime_error);
    EXPECT_THROW(gp::getNumberOfMonitors(), std::runtime_error);
}

TEST(CoreTests, Unintialised) {
    gp::terminate();

    EXPECT_THROW(gp::openglVersion(), std::runtime_error);
    EXPECT_THROW(gp::getTime(), std::runtime_error);

    EXPECT_THROW(gp::update(), std::runtime_error);
    EXPECT_THROW(gp::updateTimeout(0), std::runtime_error);
    EXPECT_THROW(gp::updateOnEvent(), std::runtime_error);
    EXPECT_THROW(gp::setBufferSwapInterval(0), std::runtime_error);
}

TEST(CoreTests, NoContext) {
    gp::init();

    EXPECT_THROW(gp::openglVersion(), std::runtime_error);
    EXPECT_NO_THROW(gp::getTime());

    EXPECT_NO_THROW(gp::update());
    EXPECT_NO_THROW(gp::updateTimeout(0));
    EXPECT_THROW(gp::updateOnEvent(), std::runtime_error);
    EXPECT_THROW(gp::setBufferSwapInterval(0), std::runtime_error);
}

TEST(CoreTests, InvalidValueError) {
    gp::init();

    EXPECT_THROW(gp::updateTimeout(-1), std::invalid_argument);
    EXPECT_THROW(gp::setBufferSwapInterval(-1), std::invalid_argument);
}

TEST(CoreTests, VersionParams) {
    gp::init();

    auto glfwCompiledVersion = gp::glfwCompiledVersion();
    auto glfwCurrentVersion = gp::glfwCurrentVersion();

    EXPECT_GT(gp::glfwCompiledVersion().length(), 0);
    EXPECT_GT(gp::glfwCurrentVersion().length(), 0);

    gp::terminate();

    EXPECT_STREQ(gp::glfwCompiledVersion().c_str(), glfwCompiledVersion.c_str());
    EXPECT_STREQ(gp::glfwCurrentVersion().c_str(), glfwCurrentVersion.c_str());
}

TEST(CoreTests, Time) {
    gp::init();
    EXPECT_GT(gp::getTime(), 0);
}

#pragma clang diagnostic pop
