#pragma once

#include "gp.h"
#include "PackingAlgorithm.h"
#include "SortingAlgorithms.h"

namespace gp::packing {
    class Item;

    class ShelvedBin;

    namespace shelf {
        class Shelf;
    }
}

namespace gp::packing::shelf {
    using ScoringFunction = std::function<float(const shared_ptr<gp::packing::shelf::Shelf> &,
                                                const shared_ptr<Item> &)>;

    class GPAPI ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        ShelfPackingAlgorithm();

        virtual ~ShelfPackingAlgorithm() = default;

        virtual void pack(const shared_ptr<Item> &item, bool allowRotation);

        void packAll(std::vector<shared_ptr<Item>> items,
                     bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        void packOriented(const shared_ptr<Item> &item, bool orientVertically = true);

        void packAllOriented(std::vector<shared_ptr<Item>> items,
                             bool orientVertically = true,
                             const SortingFunction &sortingFunction = sortByLongSide(true));

        [[nodiscard]] std::vector<shared_ptr<ShelvedBin>> bins() const;

    protected:
        std::vector<shared_ptr<ShelvedBin>> m_Bins;

        ShelfPackingAlgorithm(float binWidth, float binHeight);

        void addItemToShelf(Item &item, Shelf &shelf);
    };

    class GPAPI NextFit final : public ShelfPackingAlgorithm {

    public:
        NextFit(float binWidth, float binHeight);

        void pack(const shared_ptr<Item> &item, bool allowRotation) override;

    private:
        shared_ptr<Shelf> m_Shelf;
    };

    class GPAPI FirstFit final : public ShelfPackingAlgorithm {

    public:
        FirstFit(float binWidth, float binHeight);

        void pack(const shared_ptr<Item> &item, bool allowRotation) override;
    };

    class GPAPI ScoredFit : public ShelfPackingAlgorithm {

    public:
        ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction);

        void pack(const shared_ptr<Item> &item, bool allowRotation) override;

    private:
        ScoringFunction m_ScoringFunction;
    };

    class GPAPI BestWidthFit final : public ScoredFit {

    public:
        BestWidthFit(float binWidth, float binHeight);
    };

    class GPAPI WorstWidthFit final : public ScoredFit {

    public:
        WorstWidthFit(float binWidth, float binHeight);
    };

    class GPAPI BestHeightFit final : public ScoredFit {

    public:
        BestHeightFit(float binWidth, float binHeight);
    };

    class GPAPI WorstHeightFit final : public ScoredFit {

    public:
        WorstHeightFit(float binWidth, float binHeight);
    };

    class GPAPI BestAreaFit final : public ScoredFit {

    public:
        BestAreaFit(float binWidth, float binHeight);
    };

    class GPAPI WorstAreaFit final : public ScoredFit {

    public:
        WorstAreaFit(float binWidth, float binHeight);
    };
}
