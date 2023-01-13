#pragma once

#include "gp.h"
#include "src/goopylib/maths/gpmath.h"

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
        GPAPI Item(float width, float height, void *userObject = nullptr);

        GPAPI bool isVertical() const;

        GPAPI bool isHorizontal() const;

        GPAPI bool isRotated() const;

        GPAPI float area() const;

        GPAPI Point p1() const;

        GPAPI Point p2() const;

        GPAPI float getX() const;

        GPAPI float getY() const;

        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

        GPAPI float getLongSide() const;

        GPAPI float getShortSide() const;

        GPAPI uint32_t getPage() const;

        GPAPI void* getUserObject() const;

    private:
        float m_Width;
        float m_Height;
        const float m_LongSide;
        const float m_ShortSide;

        void *m_UserObject;

        float m_X = -1;
        float m_Y = -1;
        uint32_t m_Page = 0;

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
        GPAPI virtual float packingRatio(bool countFullBin) const;

        GPAPI std::vector<Ref<Item>> items() const;

        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

        GPAPI uint32_t getPage() const;

    protected:
        const float m_Width;
        const float m_Height;
        const uint32_t m_Page;

        std::vector<Ref<Item>> m_Items;

        Bin(float width, float height, uint32_t page);

        void add(const Ref<Item>& item);
    };
}

// Sorting Algorithms
namespace gp::packing {
    using SortingFunction = std::function<std::vector<Ref<Item>>(std::vector<Ref<Item>>)>;

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

    protected:
        PackingAlgorithm(float binWidth, float binHeight);

        const float m_BinWidth;
        const float m_BinHeight;
    };
}
