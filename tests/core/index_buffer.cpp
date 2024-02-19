#include "gtest/gtest.h"
#include <src/goopylib.h>

TEST(IndexBufferTests, EmptyConstructor) {
    gp::init();
    EXPECT_NO_THROW(gp::IndexBuffer(nullptr, 0));
}

TEST(IndexBufferTests, ArrayConstructor) {
    int data[] = {1, 2, 3, 2, 3, 4};
    auto buffer = gp::IndexBuffer(data, 6);
    EXPECT_EQ(buffer.length(), 6);
}

TEST(IndexBufferTests, HeapArrayConstructor) {
    int *data = new int[10];
    auto buffer = gp::IndexBuffer(data, 10);
    delete[] data;

    EXPECT_EQ(buffer.length(), 10);
}

TEST(IndexBufferTests, StdArrayConstructor) {
    std::array data = {1, 2, 3, 2, 3, 4};
    auto buffer = gp::IndexBuffer(data);
    EXPECT_EQ(buffer.length(), 6);
}

TEST(IndexBufferTests, VectorConstructor) {
    std::vector data = {1, 2, 3, 2, 3, 4};
    auto buffer = gp::IndexBuffer(data);
    EXPECT_EQ(buffer.length(), 6);
}

TEST(IndexBufferTests, ConstructorErrors) {
    EXPECT_THROW(gp::IndexBuffer(nullptr, -1), std::invalid_argument);
    EXPECT_THROW(gp::IndexBuffer(nullptr, 10), std::invalid_argument);

    gp::terminate();
    EXPECT_THROW(gp::IndexBuffer(nullptr, 0), std::runtime_error);

    int data1[] = {1, 2, 3, 2, 3, 4};
    EXPECT_THROW(gp::IndexBuffer(data1, 6), std::runtime_error);

    int *data2 = new int[10];
    EXPECT_THROW(gp::IndexBuffer(data2, 10), std::runtime_error);
    delete[] data2;

    std::array data3 = {1, 2, 3, 2, 3, 4};
    EXPECT_THROW(auto _ = gp::IndexBuffer(data3), std::runtime_error);

    std::vector data4 = {1, 2, 3, 2, 3, 4};
    EXPECT_THROW(auto _ = gp::IndexBuffer(data4), std::runtime_error);
}
