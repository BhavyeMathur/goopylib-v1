#include "ShelfPackingAlgorithm.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/Item.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing {
    ShelfPackingAlgorithm::ShelfPackingAlgorithm(float binWidth, float binHeight)
            : PackingAlgorithm(binWidth, binHeight) {
    }

    void ShelfPackingAlgorithm::_pack(std::vector<Item> &items, bool allowRotation) {
        for (auto &item: items)
            _packItem(item, allowRotation);
    }

    const std::vector<ShelvedBin> &ShelfPackingAlgorithm::bins() const {
        return m_Bins;
    }

    void ShelfPackingAlgorithm::orientItemForShelf(Item &item, Shelf &shelf, bool allowRotation) {
        if (allowRotation and shelf.fitsItemVertically(item) != item.isVertical())
            item.rotate();
    }

    void ShelfPackingAlgorithm::addItemToNewShelf(Item &item, ShelvedBin &bin, bool allowRotation) {
        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        bin.addShelf();
        bin.add(item, bin.getOpenShelf());
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
        m_Bins.push_back({m_BinWidth, m_BinHeight, static_cast<uint32_t>(m_Bins.size())});
        auto &newBin = m_Bins.back();

        if (allowRotation)  // Ensure item added is horizontal (so that it occupies less vertical space)
            item.setHorizontal();

        newBin.add(item, newBin.getOpenShelf());
    }

    void ShelfPackingAlgorithm::addItemToShelf(Item &item, ShelvedBin &bin, Shelf &shelf) {
        bin.add(item, shelf);
    }
}
