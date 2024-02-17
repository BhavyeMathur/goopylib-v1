#pragma once

#include "gtest/gtest.h"
#include <goopylib/goopylib.h>

#define EXPECT_COLOR_EQ(arg1, arg2) EXPECT_TRUE(colorNearEquality((arg1), (arg2)))

static bool colorNearEquality(const gp::Color &color1, const gp::Color &color2) {
    return color1.toString() == color2.toString();
}
