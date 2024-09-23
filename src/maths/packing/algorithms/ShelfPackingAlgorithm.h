#pragma once

#include "gp.h"
#include "PackingAlgorithm.h"
#include "SortingAlgorithms.h"
#include "maths/packing/ShelvedBin.h"
#include "maths/packing/Shelf.h"


namespace gp::packing {
    class Item;

    class Shelf;

    class GPAPI ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        virtual ~ShelfPackingAlgorithm() = default;

        /**
         * Packs an item into a bin
         *
         * @param item the item to pack
         * @param allowRotation whether the item is allowed to be rotated
         *
         * @note for multiple items, use packAll() since packing ratio is often better after sorting the items
         *
         * @throws std::value_error if an item does not fit into the dimensions of the bin
         */
        virtual void pack(Item &item, bool allowRotation) = 0;

        /**
         * Packs a vector of items into a bin, optionally after sorting them.
         *
         * @param items the items to pack
         * @param allowRotation whether the items are allowed to be rotated
         * @param sortingFunction the function to use for sorting the items. Defaults to sortByShortSide.
         *
         * @throws std::value_error if an item does not fit into the dimensions of the bin
         */
        void packAll(std::vector<Item> &items, bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        /**
         * @return a vector of bins containing the packed items
         */
        [[nodiscard]] const std::vector<ShelvedBin> &bins() const;

    protected:
        std::vector<ShelvedBin> m_Bins;

        ShelfPackingAlgorithm(float binWidth, float binHeight);

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
        static void addItemToShelf(Item &item, ShelvedBin& bin, Shelf& shelf);
    };
}
