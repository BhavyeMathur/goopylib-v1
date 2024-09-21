#pragma once

#include "gp.h"

struct Point;

namespace gp::packing {
    class PackingAlgorithm;

    namespace shelf {
        class Shelf;
    }

    class GPAPI Item {

        friend class shelf::Shelf;

        friend class PackingAlgorithm;

    public:
        Item(float width, float height);

        Item(const Item &) = delete;

        [[nodiscard]] bool isVertical() const;

        [[nodiscard]] bool isHorizontal() const;

        [[nodiscard]] bool isRotated() const;

        [[nodiscard]] float area() const;

        [[nodiscard]] Point p1() const;

        [[nodiscard]] Point p2() const;

        [[nodiscard]] float getX() const;

        [[nodiscard]] float getY() const;

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

        [[nodiscard]] float getLongSide() const;

        [[nodiscard]] float getShortSide() const;

    private:
        float m_Width;
        float m_Height;
        const float m_LongSide;
        const float m_ShortSide;

        float m_X = -1;
        float m_Y = -1;

        bool m_Rotated = false;

        const uint32_t m_ID;
        static uint32_t s_Items;

        void rotate();
    };
}
