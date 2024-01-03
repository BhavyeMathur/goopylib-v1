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
        [[nodiscard]] GPAPI std::string toString() const;

        [[nodiscard]] GPAPI float getWidth() const;

        [[nodiscard]] GPAPI float getHeight() const;

        [[nodiscard]] GPAPI float getVerticalOffset() const;

        [[nodiscard]] GPAPI float getPackedWidth() const;

        [[nodiscard]] GPAPI float getAvailableWidth() const;

        [[nodiscard]] GPAPI bool isOpen() const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_VerticalOffset;

        bool m_IsOpen = true;

        Bin &m_Bin;
        std::vector<Ref<Item>> m_Items;

        GPAPI Shelf(float verticalOffset, Bin &bin);

        [[nodiscard]] GPAPI bool fits(const Ref<Item> &item) const;

        [[nodiscard]] GPAPI bool fitsAbove(const Ref<Item> &item) const;

        GPAPI void add(const Ref<Item>& item);

        GPAPI void close();

        [[nodiscard]] GPAPI float packedArea() const;
    };
}

// Shelved Bin Class
namespace gp::packing {
    class ShelvedBin final : public Bin {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        [[nodiscard]] GPAPI float packingRatio() const override;

        GPAPI Ref<shelf::Shelf> getOpenShelf();

        GPAPI std::vector<Ref<shelf::Shelf>> getShelves();

        [[nodiscard]] GPAPI std::vector<Ref<shelf::Shelf>>::const_iterator begin() const;

        [[nodiscard]] GPAPI std::vector<Ref<shelf::Shelf>>::const_iterator end() const;

    private:
        Ref<shelf::Shelf> m_OpenShelf;
        std::vector<Ref<shelf::Shelf>> m_Shelves;

        GPAPI ShelvedBin(float width, float height);

        GPAPI Ref<shelf::Shelf> addShelf();
    };
}

// Shelf Packing Algorithms Classes
namespace gp::packing::shelf {
    using ScoringFunction = std::function<float(const Ref<gp::packing::shelf::Shelf> &,
                                                const Ref<Item> &)>;

    class ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        GPAPI virtual ~ShelfPackingAlgorithm() = default;

        GPAPI virtual void pack(const Ref<Item>& item, bool allowRotation = true);

        GPAPI void packAll(std::vector<Ref<Item>> items,
                     bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        GPAPI void packOriented(const Ref<Item>& item, bool orientVertically = true);

        GPAPI void packAllOriented(std::vector<Ref<Item>> items,
                             bool orientVertically = true,
                             const SortingFunction &sortingFunction = sortByLongSide(true));

        [[nodiscard]] GPAPI std::vector<Ref<ShelvedBin>> bins() const;

    protected:
        GPAPI ShelfPackingAlgorithm(float binWidth, float binHeight);

        std::vector<Ref<ShelvedBin>> m_Bins;
    };

    class NextFit final : public ShelfPackingAlgorithm {

    public:
        GPAPI NextFit(float binWidth, float binHeight);

        GPAPI void pack(const Ref<Item> &item, bool allowRotation) override;

    private:
        Ref<Shelf> m_Shelf;
    };

    class FirstFit final : public ShelfPackingAlgorithm {

    public:
        GPAPI FirstFit(float binWidth, float binHeight);

        GPAPI void pack(const Ref<Item> &item, bool allowRotation) override;
    };

    class ScoredFit : public ShelfPackingAlgorithm {

    public:
        GPAPI ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction);

        GPAPI void pack(const Ref<Item> &item, bool allowRotation) override;

    private:
        ScoringFunction m_ScoringFunction;
    };

    class BestWidthFit final : public ScoredFit {

    public:
        GPAPI BestWidthFit(float binWidth, float binHeight);
    };

    class WorstWidthFit final : public ScoredFit {

    public:
        GPAPI WorstWidthFit(float binWidth, float binHeight);
    };

    class BestHeightFit final : public ScoredFit {

    public:
        GPAPI BestHeightFit(float binWidth, float binHeight);
    };

    class WorstHeightFit final : public ScoredFit {

    public:
        GPAPI WorstHeightFit(float binWidth, float binHeight);
    };

    class BestAreaFit final : public ScoredFit {

    public:
        GPAPI BestAreaFit(float binWidth, float binHeight);
    };

    class WorstAreaFit final : public ScoredFit {

    public:
        GPAPI WorstAreaFit(float binWidth, float binHeight);
    };
}
