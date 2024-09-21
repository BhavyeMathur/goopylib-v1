#pragma once

#include "gp.h"

struct Point;

namespace gp::packing {
    namespace shelf {
        class Shelf;

        class ShelfPackingAlgorithm;

        class NextFit;

        class FirstFit;

        class ScoredFit;
    }

    class GPAPI Item {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

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
