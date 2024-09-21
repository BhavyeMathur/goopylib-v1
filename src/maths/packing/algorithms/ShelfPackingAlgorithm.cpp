#include "ShelfPackingAlgorithm.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"
#include "ScoredFit.h"

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
        std::vector<shared_ptr<ShelvedBin>>
                copy = m_Bins;
        return copy;
    }

    void ShelfPackingAlgorithm::addItemToShelf(Item &item, shelf::Shelf &shelf) {
        shelf.add(item);
    }
}
