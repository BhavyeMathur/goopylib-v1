#pragma once

#include "gp.h"

namespace gp::packing {
    class Item;

    class GPAPI PackingAlgorithm {

    public:
        [[nodiscard]] uint32_t pages() const;

    protected:
        const float m_BinWidth;
        const float m_BinHeight;

        uint32_t m_Pages = 0;

        PackingAlgorithm(float binWidth, float binHeight);
    };
}
