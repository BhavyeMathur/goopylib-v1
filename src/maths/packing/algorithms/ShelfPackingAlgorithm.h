#pragma once

#include "gp.h"
#include "PackingAlgorithm.h"
#include "SortingAlgorithms.h"
#include "maths/packing/ShelvedBin.h"
#include "maths/packing/Shelf.h"


namespace gp::packing {
    class Item;

    class ShelvedBin;

    class Shelf;

    class GPAPI ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        virtual ~ShelfPackingAlgorithm() = default;

        virtual void pack(Item &item, bool allowRotation) = 0;

        void packAll(std::vector<Item> &items, bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        void packOriented(Item &item, bool orientVertically = true);

        void packAllOriented(std::vector<Item> &items, bool orientVertically = true,
                             const SortingFunction &sortingFunction = sortByLongSide(true));

        [[nodiscard]] const std::vector<ShelvedBin> &bins() const;

    protected:
        std::vector<ShelvedBin> m_Bins;

        ShelfPackingAlgorithm(float binWidth, float binHeight);

        void orientItemForShelf(Item &item, Shelf &shelf, bool allowRotation);

        void addItemToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation);

        bool tryAddingToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation);

        void addItemToNewBin(Item &item, bool allowRotation);

        void addItemToShelf(Item &item, ShelvedBin& bin, Shelf& shelf);
    };
}
