#pragma once

#include "gp.h"
#include "maths/gpmath.h"

#include <algorithm>

namespace gp::packing::shelf {
    class Shelf;

    class ShelfPackingAlgorithm;

    class NextFit;

    class FirstFit;

    class ScoredFit;
}

// Item Class
namespace gp::packing {
    class GPAPI Item {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        Item(float width, float height);

        Item (const Item&) = delete;

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

// Bin Class
namespace gp::packing {
    class GPAPI Bin {

        friend class shelf::Shelf;

    public:
        Bin (const Bin&) = delete;

        [[nodiscard]] virtual float packingRatio() const;

        [[nodiscard]] std::vector<shared_ptr<Item>> items() const;

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

    protected:
        const float m_Width;
        const float m_Height;

        const uint32_t m_ID;

        std::vector<shared_ptr<Item>> m_Items;

        static uint32_t s_Bins;

        Bin(float width, float height);

        void add(const shared_ptr<Item>& item);
    };
}

// Sorting Algorithms
namespace gp::packing {
    using SortingFunction = std::function<std::vector<shared_ptr<Item>>(std::vector<shared_ptr<Item>>)>;

    SortingFunction sortByWidth(bool descending = false);

    SortingFunction sortByHeight(bool descending = false);

    SortingFunction sortByPerimeter(bool descending = false);

    SortingFunction sortByArea(bool descending = false);

    SortingFunction sortBySideRatio(bool descending = false);

    SortingFunction sortByLongSide(bool descending = false);

    SortingFunction sortByShortSide(bool descending = false);
}

// Packing Algorithm Class
namespace gp::packing {
    class GPAPI PackingAlgorithm {

    public:
        PackingAlgorithm (const PackingAlgorithm&) = delete;

    protected:
        PackingAlgorithm(float binWidth, float binHeight);

        const float m_BinWidth;
        const float m_BinHeight;
    };
}
