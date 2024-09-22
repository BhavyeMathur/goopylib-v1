#include "ShelfPackingAlgorithm.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"

#include "debug/Error.h"

namespace gp::packing::shelf {
    ShelfPackingAlgorithm::ShelfPackingAlgorithm(float binWidth, float binHeight)
            : PackingAlgorithm(binWidth, binHeight) {
        m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
    }

    ShelfPackingAlgorithm::ShelfPackingAlgorithm() : PackingAlgorithm(0, 0) {
    }

    void ShelfPackingAlgorithm::pack(Item &item, bool allowRotation) {
        GP_RUNTIME_ERROR("ShelfPackingAlgorithm::pack() unimplemented");
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
        if (sortingFunction) {
            items = sortingFunction(items);

            for (auto &item: items)
                packOriented(item, orientVertically);
        }
    }

    std::vector<shared_ptr<ShelvedBin>> ShelfPackingAlgorithm::bins() const {
        std::vector<shared_ptr<ShelvedBin>> copy = m_Bins;
        return copy;
    }

    void ShelfPackingAlgorithm::orientItemForShelf(Item &item, Shelf &shelf, bool allowRotation) {
        if (allowRotation and shelf.fitsItemVertically(item) != item.isVertical())
            item.rotate();
    }

    void ShelfPackingAlgorithm::addItemToShelf(Item &item, shelf::Shelf &shelf) {
        shelf.add(item);
    }

    void ShelfPackingAlgorithm::addItemToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation) {
        auto shelf = bin.addShelf();

        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();
        addItemToShelf(item, shelf);
    }

    bool ShelfPackingAlgorithm::tryAddingToNewShelf(Item &item, Shelf &shelf, ShelvedBin &bin, bool allowRotation) {
        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        if (shelf.fitsShelfAbove(item)) {
            addItemToNewShelf(item, bin, false);
            return true;
        }
        return false;
    }

    void ShelfPackingAlgorithm::addItemToNewBin(Item &item, bool allowRotation) {
        m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));
        const auto &newBin = m_Bins.back();

        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        addItemToShelf(item, newBin->getOpenShelf());
    }
}
