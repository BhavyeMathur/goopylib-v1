#pragma once


#include "gp.h"
#include "Packing.h"

namespace gp::packing {
    class ShelvedBin;

    namespace shelf {
        class ShelfPackingAlgorithm;

        class NextFit;

        class FirstFit;

        class ScoredFit;
    }
}

// Shelf Class
namespace gp::packing::shelf {
    class Shelf {

        friend class gp::packing::ShelvedBin;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        GPAPI std::string toString() const;

        GPAPI float getWidth() const;

        GPAPI float getHeight() const;

        GPAPI float getVerticalOffset() const;

        GPAPI float getPackedWidth() const;

        GPAPI float getAvailableWidth() const;

        GPAPI bool isOpen() const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_VerticalOffset;

        bool m_IsOpen = true;

        Bin &m_Bin;
        std::vector<Ref<Item>> m_Items;

        Shelf(float verticalOffset, Bin &bin);

        bool fits(const Ref<Item> &item) const;

        bool fitsAbove(const Ref<Item> &item) const;

        void add(const Ref<Item>& item);

        void close();

        float packedArea() const;
    };
}

// Shelved Bin Class
namespace gp::packing {
    class ShelvedBin : public Bin {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        GPAPI float packingRatio(bool countFullBin) const override;

        GPAPI Ref<shelf::Shelf> getOpenShelf();

        GPAPI std::vector<Ref<shelf::Shelf>> getShelves();

        [[nodiscard]] GPAPI std::vector<Ref<shelf::Shelf>>::const_iterator begin() const;

        [[nodiscard]] GPAPI std::vector<Ref<shelf::Shelf>>::const_iterator end() const;

    private:
        Ref<shelf::Shelf> m_OpenShelf;
        std::vector<Ref<shelf::Shelf>> m_Shelves;

        ShelvedBin(float width, float height, uint32_t page);

        Ref<shelf::Shelf> addShelf();
    };
}

// Shelf Packing Algorithms Classes
namespace gp::packing::shelf {
    using ScoringFunction = std::function<float(const Ref<gp::packing::shelf::Shelf> &,
                                                const Ref<Item> &)>;

    class ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        virtual void pack(const Ref<Item>& item, bool allowRotation = true);

        void packAll(std::vector<Ref<Item>> items,
                     bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        void packOriented(const Ref<Item>& item, bool orientVertically = true);

        void packAllOriented(std::vector<Ref<Item>> items,
                             bool orientVertically = true,
                             const SortingFunction &sortingFunction = sortByLongSide(true));

        std::vector<Ref<ShelvedBin>> bins() const;

        uint32_t getPages() const;

    protected:
        ShelfPackingAlgorithm(float binWidth, float binHeight);

        std::vector<Ref<ShelvedBin>> m_Bins;
    };

    class NextFit : public ShelfPackingAlgorithm {

    public:
        NextFit(float binWidth, float binHeight);

        void pack(const Ref<Item> &item, bool allowRotation) override;

    private:
        Ref<Shelf> m_Shelf;
    };

    class FirstFit : public ShelfPackingAlgorithm {

    public:
        FirstFit(float binWidth, float binHeight);

        void pack(const Ref<Item> &item, bool allowRotation) override;
    };

    class ScoredFit : public ShelfPackingAlgorithm {

    public:
        ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction);

        void pack(const Ref<Item> &item, bool allowRotation) override;

    private:
        ScoringFunction m_ScoringFunction;
    };

    class BestWidthFit : public ScoredFit {

    public:
        BestWidthFit(float binWidth, float binHeight);
    };

    class WorstWidthFit : public ScoredFit {

    public:
        WorstWidthFit(float binWidth, float binHeight);
    };

    class BestHeightFit : public ScoredFit {

    public:
        BestHeightFit(float binWidth, float binHeight);
    };

    class WorstHeightFit : public ScoredFit {

    public:
        WorstHeightFit(float binWidth, float binHeight);
    };

    class BestAreaFit : public ScoredFit {

    public:
        BestAreaFit(float binWidth, float binHeight);
    };

    class WorstAreaFit : public ScoredFit {

    public:
        WorstAreaFit(float binWidth, float binHeight);
    };
}
