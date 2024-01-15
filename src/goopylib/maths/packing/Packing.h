#pragma once

#include "gp.h"
#include "src/goopylib/maths/gpmath.h"

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
    class Item {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        GPAPI Item(float width, float height);

        GPAPI Item (const Item&) = delete;

        [[nodiscard]] GPAPI bool isVertical() const;

        [[nodiscard]] GPAPI bool isHorizontal() const;

        [[nodiscard]] GPAPI bool isRotated() const;

        [[nodiscard]] GPAPI float area() const;

        [[nodiscard]] GPAPI Point p1() const;

        [[nodiscard]] GPAPI Point p2() const;

        [[nodiscard]] GPAPI float getX() const;

        [[nodiscard]] GPAPI float getY() const;

        [[nodiscard]] GPAPI float getWidth() const;

        [[nodiscard]] GPAPI float getHeight() const;

        [[nodiscard]] GPAPI float getLongSide() const;

        [[nodiscard]] GPAPI float getShortSide() const;

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
    class Bin {

        friend class shelf::Shelf;

    public:
        GPAPI Bin (const Bin&) = delete;

        [[nodiscard]] GPAPI virtual float packingRatio() const;

        [[nodiscard]] GPAPI std::vector<shared_ptr<Item>> items() const;

        [[nodiscard]] GPAPI float getWidth() const;

        [[nodiscard]] GPAPI float getHeight() const;

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

    GPAPI SortingFunction sortByWidth(bool descending = false);

    GPAPI SortingFunction sortByHeight(bool descending = false);

    GPAPI SortingFunction sortByPerimeter(bool descending = false);

    GPAPI SortingFunction sortByArea(bool descending = false);

    GPAPI SortingFunction sortBySideRatio(bool descending = false);

    GPAPI SortingFunction sortByLongSide(bool descending = false);

    GPAPI SortingFunction sortByShortSide(bool descending = false);
}

// Packing Algorithm Class
namespace gp::packing {
    class PackingAlgorithm {

    public:
        GPAPI PackingAlgorithm (const PackingAlgorithm&) = delete;

    protected:
        PackingAlgorithm(float binWidth, float binHeight);

        const float m_BinWidth;
        const float m_BinHeight;
    };
}
