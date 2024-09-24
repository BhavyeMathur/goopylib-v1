#include "PackingAlgorithm.h"
#include "maths/packing/Item.h"

namespace gp::packing {
    PackingAlgorithm::PackingAlgorithm(float binWidth, float binHeight)
            : m_BinWidth(binWidth),
              m_BinHeight(binHeight) {
    }

    uint32_t PackingAlgorithm::pages() const {
        return m_Pages;
    }

    void PackingAlgorithm::pack(gp::packing::Item &item, bool allowRotation) {
        std::vector<Item> items = {item};
        pack(items, allowRotation, nullptr);
    }

    void PackingAlgorithm::pack(std::vector<Item> &items, bool allowRotation,
                                const gp::packing::SortingFunction &sortingFunction) {
        if (sortingFunction)
            items = sortingFunction(items);

        _pack(items, allowRotation);
    }
}
