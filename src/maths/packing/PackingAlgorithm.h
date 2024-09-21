#pragma once

#include "gp.h"

namespace gp::packing {
    class GPAPI PackingAlgorithm {

    protected:
        PackingAlgorithm(float binWidth, float binHeight);

        const float m_BinWidth;
        const float m_BinHeight;
    };
}
