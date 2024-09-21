#include "PackingAlgorithm.h"
#include "Item.h"

namespace gp::packing {
    PackingAlgorithm::PackingAlgorithm(float binWidth, float binHeight)
            : m_BinWidth(binWidth),
              m_BinHeight(binHeight) {
    }

    void PackingAlgorithm::rotateItem(Item &item) {
        item.rotate();
    }
}
