#pragma once

#include "gp.h"
#include "src/goopylib/maths/gpmath.h"

namespace gp::packing {
    class Item;

    namespace shelf {
        class Shelf;
    }
}

// Bin Class
namespace gp::packing {
    class Bin {

        friend class shelf::Shelf;

    public:
        GPAPI virtual float packingRatio() const;

        GPAPI std::vector<Ref<Item>> items() const;

        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

    protected:
        uint32_t m_ID;

        float m_Width;
        float m_Height;

        std::vector<Ref<Item>> m_Items;

        static uint32_t bins;

        Bin(float width, float height);

        void add(const Ref<Item> &item);

        void add(Item &item);
    };

    class ShelvedBin;
}

// Sorting Algorithms
namespace gp::packing {
    using SortingFunction = std::function<std::vector<Ref<gp::packing::Item>>(std::vector<Ref<gp::packing::Item>>)>;

    GPAPI SortingFunction sortByWidth(bool descending = false);

    GPAPI SortingFunction sortByHeight(bool descending = false);

    GPAPI SortingFunction sortByPerimeter(bool descending = false);

    GPAPI SortingFunction sortByArea(bool descending = false);

    GPAPI SortingFunction sortBySideRatio(bool descending = false);

    GPAPI SortingFunction sortByLongSide(bool descending = false);

    GPAPI SortingFunction sortByShortSide(bool descending = false);
}

// Shelf Packing Algorithms
namespace gp::packing::shelf {
    using ScoringFunction = std::function<float(const Ref<gp::packing::shelf::Shelf> &,
                                                const Ref<gp::packing::Item> &)>;

    GPAPI std::vector<Ref<ShelvedBin>> packNextFit(std::vector<Ref<Item>> &items,
                                                   float binWidth,
                                                   float binHeight,
                                                   const SortingFunction &sorting = sortByShortSide(true),
                                                   bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packFirstFit(std::vector<Ref<Item>> &items,
                                                    float binWidth,
                                                    float binHeight,
                                                    const SortingFunction &sorting = sortByShortSide(true),
                                                    bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packScoredFit(std::vector<Ref<Item>> &items,
                                                     float binWidth,
                                                     float binHeight,
                                                     const ScoringFunction &scoringFunction,
                                                     const SortingFunction &sorting = sortByShortSide(true),
                                                     bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packBestWidthFit(std::vector<Ref<Item>> &items,
                                                        float binWidth,
                                                        float binHeight,
                                                        const SortingFunction &sorting = sortByShortSide(true),
                                                        bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packWorstWidthFit(std::vector<Ref<Item>> &items,
                                                         float binWidth,
                                                         float binHeight,
                                                         const SortingFunction &sorting = sortByShortSide(true),
                                                         bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packBestHeightFit(std::vector<Ref<Item>> &items,
                                                         float binWidth,
                                                         float binHeight,
                                                         const SortingFunction &sorting = sortByShortSide(true),
                                                         bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packWorstHeightFit(std::vector<Ref<Item>> &items,
                                                          float binWidth,
                                                          float binHeight,
                                                          const SortingFunction &sorting = sortByShortSide(true),
                                                          bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packBestAreaFit(std::vector<Ref<Item>> &items,
                                                       float binWidth,
                                                       float binHeight,
                                                       const SortingFunction &sorting = sortByShortSide(true),
                                                       bool allowRotation = true);

    GPAPI std::vector<Ref<ShelvedBin>> packWorstAreaFit(std::vector<Ref<Item>> &items,
                                                        float binWidth,
                                                        float binHeight,
                                                        const SortingFunction &sorting = sortByShortSide(true),
                                                        bool allowRotation = true);

}

// Item Class
namespace gp::packing {
    class Item {

        friend class shelf::Shelf;

        friend std::vector<Ref<ShelvedBin>> shelf::packNextFit(std::vector<Ref<Item>> &items,
                                                               float binWidth,
                                                               float binHeight,
                                                               const SortingFunction &sorting,
                                                               bool allowRotation);

        friend std::vector<Ref<ShelvedBin>> shelf::packFirstFit(std::vector<Ref<Item>> &items,
                                                                float binWidth,
                                                                float binHeight,
                                                                const SortingFunction &sorting,
                                                                bool allowRotation);

        friend std::vector<Ref<ShelvedBin>> shelf::packScoredFit(std::vector<Ref<Item>> &items,
                                                                 float binWidth,
                                                                 float binHeight,
                                                                 const shelf::ScoringFunction &scoringFunction,
                                                                 const SortingFunction &sorting,
                                                                 bool allowRotation);

    public:
        GPAPI Item(float width, float height);

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

        GPAPI static bool compareWidth(const Item &item1, const Item &item2) {
            return item1.m_Width < item2.m_Height;
        }

    private:
        float m_Width;
        float m_Height;
        float m_LongSide;
        float m_ShortSide;

        float m_X = -1;
        float m_Y = -1;

        bool m_Rotated = false;

        uint32_t m_ID;
        static uint32_t items;

        void rotate();
    };
}

// Shelf Class
namespace gp::packing::shelf {
    class Shelf {

        friend class gp::packing::ShelvedBin;

        friend std::vector<Ref<ShelvedBin>> shelf::packNextFit(std::vector<Ref<Item>> &items,
                                                               float binWidth,
                                                               float binHeight,
                                                               const SortingFunction &sorting,
                                                               bool allowRotation);

        friend std::vector<Ref<ShelvedBin>> shelf::packFirstFit(std::vector<Ref<Item>> &items,
                                                                float binWidth,
                                                                float binHeight,
                                                                const SortingFunction &sorting,
                                                                bool allowRotation);

        friend std::vector<Ref<ShelvedBin>> shelf::packScoredFit(std::vector<Ref<Item>> &items,
                                                                 float binWidth,
                                                                 float binHeight,
                                                                 const shelf::ScoringFunction &scoringFunction,
                                                                 const SortingFunction &sorting,
                                                                 bool allowRotation);

    public:
        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

        GPAPI float getVerticalOffset() const;

        GPAPI float getPackedWidth() const;

        GPAPI float getAvailableWidth() const;

        GPAPI bool isOpen() const;

    private:
        float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        float m_VerticalOffset;

        bool m_IsOpen = true;

        Bin &m_Bin;
        std::vector<Ref<Item>> m_Items;

        Shelf(float verticalOffset, Bin &bin);

        bool fits(const Ref<Item> &item) const;

        bool fitsAbove(const Ref<Item> &item) const;

        void add(const Ref<Item> &item);

        void close();

        float packedArea() const;
    };
}

// Shelved Bin Class
namespace gp::packing {
    class ShelvedBin : public Bin {

        friend class Shelf;

        friend std::vector<Ref<ShelvedBin>> shelf::packNextFit(std::vector<Ref<Item>> &items,
                                                               float binWidth,
                                                               float binHeight,
                                                               const SortingFunction &sorting,
                                                               bool allowRotation);

        friend std::vector<Ref<ShelvedBin>> shelf::packFirstFit(std::vector<Ref<Item>> &items,
                                                                float binWidth,
                                                                float binHeight,
                                                                const SortingFunction &sorting,
                                                                bool allowRotation);

        friend std::vector<Ref<ShelvedBin>> shelf::packScoredFit(std::vector<Ref<Item>> &items,
                                                                 float binWidth,
                                                                 float binHeight,
                                                                 const shelf::ScoringFunction &scoringFunction,
                                                                 const SortingFunction &sorting,
                                                                 bool allowRotation);

    public:
        GPAPI float packingRatio() const override;

        [[nodiscard]] GPAPI std::vector<Ref<shelf::Shelf>>::const_iterator begin() const;

        [[nodiscard]] GPAPI std::vector<Ref<shelf::Shelf>>::const_iterator end() const;

    private:
        Ref<shelf::Shelf> m_OpenShelf;
        std::vector<Ref<shelf::Shelf>> m_Shelves;

        ShelvedBin(float width, float height);

        Ref<shelf::Shelf> addShelf();
    };
}
