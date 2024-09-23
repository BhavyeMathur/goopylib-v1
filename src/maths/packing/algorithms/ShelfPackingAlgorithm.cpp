#include "ShelfPackingAlgorithm.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/Item.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing::shelf {
    ShelfPackingAlgorithm::ShelfPackingAlgorithm(float binWidth, float binHeight)
            : PackingAlgorithm(binWidth, binHeight) {
    }

    ShelfPackingAlgorithm::ShelfPackingAlgorithm() : PackingAlgorithm(0, 0) {
    }

    void ShelfPackingAlgorithm::packAll(std::vector<Item> &items, bool allowRotation,
                                        const SortingFunction &sortingFunction) {
        if (sortingFunction)
            items = sortingFunction(items);

        for (auto &item: items)
            pack(item, allowRotation);
    }

    void ShelfPackingAlgorithm::packOriented(Item &item, bool orientVertically) {
        if (item.isHorizontal() == orientVertically)
            item.rotate();

        pack(item, false);
    }

    void ShelfPackingAlgorithm::packAllOriented(std::vector<Item> &items, bool orientVertically,
                                                const SortingFunction &sortingFunction) {
        if (sortingFunction)
            items = sortingFunction(items);

        for (auto &item: items)
            packOriented(item, orientVertically);
    }

    const std::vector<ShelvedBin> &ShelfPackingAlgorithm::bins() const {
        return m_Bins;
    }

    void ShelfPackingAlgorithm::orientItemForShelf(Item &item, Shelf &shelf, bool allowRotation) {
        if (allowRotation and shelf.fitsItemVertically(item) != item.isVertical())
            item.rotate();
    }

    void ShelfPackingAlgorithm::addItemToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation) {
        auto shelf = bin.addShelf();

        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        bin.add(item, shelf);
    }

    bool ShelfPackingAlgorithm::tryAddingToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation) {
        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        if (bin.fitsNewShelf(item)) {
            addItemToNewShelf(item, bin, false);
            return true;
        }
        return false;
    }

    void ShelfPackingAlgorithm::addItemToNewBin(Item &item, bool allowRotation) {
        m_Pages++;
        m_Bins.emplace_back(m_BinWidth, m_BinHeight, m_Bins.size());
        auto &newBin = m_Bins.back();

        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        newBin.add(item, newBin.getOpenShelf());
    }
}
