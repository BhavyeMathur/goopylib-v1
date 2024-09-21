#pragma once

#include "gp.h"

namespace gp::packing {
    class Item;

    class GPAPI PackingAlgorithm {

    protected:
        const float m_BinWidth;
        const float m_BinHeight;

        PackingAlgorithm(float binWidth, float binHeight);
    };
}
