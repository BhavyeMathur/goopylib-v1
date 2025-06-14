#pragma once

#include "gp.h"
#include "PackingAlgorithm.h"
#include "maths/packing/ShelvedBin.h"
#include "maths/packing/Shelf.h"


namespace gp::packing {
    class Item;

    class Shelf;

    class GPAPI ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        virtual ~ShelfPackingAlgorithm() = default;

        /**
         * @return a vector of bins containing the packed items
         */
        [[nodiscard]] const std::vector<ShelvedBin> &bins() const;

    protected:
        std::vector<ShelvedBin> m_Bins;

        ShelfPackingAlgorithm(float binWidth, float binHeight);

        void _pack(std::vector<Item> &items, bool allowRotation = true) override;

        virtual void _packItem(Item &items, bool allowRotation = true) = 0;

        /**
         * Creates a new ShelvedBin with an open shelf and adds the given item to it.
         *
         * @param allowRotation whether rotating the item is allowed
         */
        void addItemToNewBin(Item &item, bool allowRotation);

        /**
         * If the item is allowed to be rotated, checks if it can fit vertically into a shelf.
         * If it can, orients the item vertically. Otherwise, orients it horizontally.
         *
         * @param allowRotation whether rotating the item is allowed
         */
        static void orientItemForShelf(Item &item, Shelf &shelf, bool allowRotation);

        /**
         * Adds a new shelf to the specified bin and adds this item to it.
         *
         * @param item the item to put into the new shelf
         * @param bin the bin to add a new shelf to
         * @param allowRotation whether rotating the item is allowed
         */
        static void addItemToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation);

        /**
         * Attemps to add the item to a new shelf in the specified bin (if it fits).
         *
         * @note: if rotation is allowed, the item will be added horizontally to ensure the height of the new shelf is minimised
         *
         * @param item the item to put into the new shelf
         * @param bin the bin to add a new shelf to
         * @param allowRotation whether rotating the item is allowed
         *
         * @return true/false depending on whether the item fit and was added successfully
         */
        static bool tryAddingToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation);

        /**
         * Adds the item (in its current orientation) to the specified shelf in the specified bin.
         */
        static void addItemToShelf(Item &item, ShelvedBin &bin, Shelf &shelf);
    };
}
