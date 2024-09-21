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
    class GPAPI ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        ShelfPackingAlgorithm();

        virtual ~ShelfPackingAlgorithm() = default;

        virtual void pack(Item &item, bool allowRotation);

        void packAll(std::vector<Item> &items, bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        void packOriented(Item &item, bool orientVertically = true);

        void packAllOriented(std::vector<Item> &items, bool orientVertically = true,
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

        void pack(Item &item, bool allowRotation) override;

    private:
        shared_ptr<Shelf> m_Shelf;
    };

    class GPAPI FirstFit final : public ShelfPackingAlgorithm {

    public:
        FirstFit(float binWidth, float binHeight);

        void pack(Item &item, bool allowRotation) override;
    };
}
