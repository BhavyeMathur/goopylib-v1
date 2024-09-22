#include "PackingAlgorithm.h"

namespace gp::packing {
    PackingAlgorithm::PackingAlgorithm(float binWidth, float binHeight)
            : m_BinWidth(binWidth),
              m_BinHeight(binHeight) {
    }

    uint32_t PackingAlgorithm::pages() const {
        return m_Pages;
    }
}
