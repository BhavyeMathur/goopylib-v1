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

        [[nodiscard]] const std::vector<ShelvedBin>& bins() const;

    protected:
        std::vector<ShelvedBin> m_Bins;

        ShelfPackingAlgorithm(float binWidth, float binHeight);

        void orientItemForShelf(Item &item, Shelf &shelf, bool allowRotation);

        void addItemToShelf(Item &item, Shelf &shelf);

        void addItemToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation);

        bool tryAddingToNewShelf(Item &item, Shelf &shelf, ShelvedBin &bin, bool allowRotation);

        void addItemToNewBin(Item &item, bool allowRotation);
    };
}
