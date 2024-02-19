#include "gtest/gtest.h"
#include <src/goopylib.h>

TEST(IndexBufferTests, Constructor) {
    gp::init();
    EXPECT_NO_THROW(gp::IndexBuffer());
    EXPECT_NO_THROW(gp::IndexBuffer(nullptr, 0));

    int data[] = {1, 2, 3, 2, 3, 4};
    EXPECT_NO_THROW(gp::IndexBuffer(data, 6));

    int *data2 = new int[10];
    EXPECT_NO_THROW(gp::IndexBuffer(data2, 10));
    delete[] data2;

    std::array data3 = {1, 2, 3, 2, 3, 4};
    // auto test = gp::IndexBuffer(data3);
    // EXPECT_NO_THROW();
}

TEST(IndexBufferTests, ConstructorErrors) {
    gp::init();
    EXPECT_THROW(gp::IndexBuffer(nullptr, -1), std::invalid_argument);
    EXPECT_THROW(gp::IndexBuffer(nullptr, 10), std::invalid_argument);

    gp::terminate();
    EXPECT_THROW(gp::IndexBuffer(nullptr, 0), std::runtime_error);
}
