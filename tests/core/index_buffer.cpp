#include "gtest/gtest.h"
#include <src/goopylib.h>

TEST(IndexBufferTests, EmptyConstructor) {
    EXPECT_NO_THROW(gp::IndexBuffer());
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

TEST(IndexBufferTests, InitialiserListConstructor) {
    gp::IndexBuffer buffer = {1, 2, 3, 2, 3, 4};
    EXPECT_EQ(buffer.length(), 6);
}

TEST(IndexBufferTests, ConstructorErrors) {
    EXPECT_THROW(gp::IndexBuffer(nullptr, -1), std::invalid_argument);
    EXPECT_THROW(gp::IndexBuffer(nullptr, 10), std::invalid_argument);
}

TEST(IndexBufferTests, Initialisation) {
    auto buffer = gp::IndexBuffer(nullptr, 0);
    EXPECT_THROW(buffer.init(), std::runtime_error);

    gp::init();
    auto window = gp::Window(100, 100);
    EXPECT_NO_THROW(buffer.init());
    EXPECT_NO_THROW(buffer.init()); // test twice init
    gp::terminate();
}

TEST(IndexBufferTests, UninitialisedAndActiveContext) {
    gp::init();
    auto buffer = gp::IndexBuffer{};
    auto window = gp::Window(100, 100);

    EXPECT_THROW(buffer.bind(), std::runtime_error);
    EXPECT_THROW(buffer.setData(nullptr, 0), std::runtime_error);
    EXPECT_THROW(buffer.setData(nullptr, 0, 0), std::runtime_error);
    EXPECT_NO_THROW(buffer.unbind());
    EXPECT_NO_THROW(buffer.init());

    gp::terminate();
}

TEST(IndexBufferTests, UninitialisedAndNoActiveContext) {
    auto buffer = gp::IndexBuffer{};

    EXPECT_THROW(buffer.init(), std::runtime_error);
    EXPECT_THROW(buffer.bind(), std::runtime_error);
    EXPECT_THROW(buffer.unbind(), std::runtime_error);
    EXPECT_THROW(buffer.setData(nullptr, 0), std::runtime_error);
    EXPECT_THROW(buffer.setData(nullptr, 0, 0), std::runtime_error);
}

TEST(IndexBufferTests, InitialisedAndActiveContext) {
    gp::init();
    auto window = gp::Window(100, 100);
    auto buffer = gp::IndexBuffer{};

    EXPECT_NO_THROW(buffer.init());
    EXPECT_NO_THROW(buffer.bind());
    EXPECT_NO_THROW(buffer.unbind());
    EXPECT_NO_THROW(buffer.setData(nullptr, 0));
    EXPECT_NO_THROW(buffer.setData(nullptr, 0, 0));

    gp::terminate();
}

TEST(IndexBufferTests, InitialisedAndNoActiveContext) {
    gp::init();
    auto window = gp::Window(100, 100);

    auto buffer = gp::IndexBuffer{};
    buffer.init();

    gp::terminate();

    EXPECT_THROW(buffer.bind(), std::runtime_error);
    EXPECT_THROW(buffer.unbind(), std::runtime_error);
    EXPECT_THROW(buffer.setData(nullptr, 0), std::runtime_error);
    EXPECT_THROW(buffer.setData(nullptr, 0, 0), std::runtime_error);
}

TEST(IndexBufferTests, SetData) {
    gp::init();
    auto window = gp::Window(100, 100);

    gp::IndexBuffer buffer = {1, 2, 3};
    buffer.init();

    std::array data1 = {1, 2, 3, 1, 2, 3};
    std::array data2 = {1, 2, 3};

    EXPECT_NO_THROW(buffer.setData(&data1[0], 6));
    EXPECT_NO_THROW(buffer.setData(&data2[0], 3, 0));
    EXPECT_NO_THROW(buffer.setData(&data2[0], 2, 1));
}

TEST(IndexBufferTests, SetDataErrors) {
    gp::init();
    auto window = gp::Window(100, 100);

    gp::IndexBuffer buffer = {1, 2, 3};
    buffer.init();

    std::array data1 = {1, 2, 3, 1, 2, 3};
    std::array data2 = {1, 2, 3};

    EXPECT_THROW(buffer.setData(nullptr, 10), std::invalid_argument);
    EXPECT_THROW(buffer.setData(nullptr, 10, 0), std::invalid_argument);
    EXPECT_THROW(buffer.setData(&data1[0], -10), std::invalid_argument);

    EXPECT_THROW(buffer.setData(&data1[0], 6, 0), std::invalid_argument);
    EXPECT_THROW(buffer.setData(&data2[0], 3, 1), std::invalid_argument);
    EXPECT_THROW(buffer.setData(&data1[0], -6, 0), std::invalid_argument);
}
