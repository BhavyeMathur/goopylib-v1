#pragma once

#include "gp.h"
#include "ScoredFit.h"


namespace gp::packing {
    class GPAPI BestWidthFit final : public ScoredFit {
    public:
        BestWidthFit(float binWidth, float binHeight);
    };

    class GPAPI WorstWidthFit final : public ScoredFit {
    public:
        WorstWidthFit(float binWidth, float binHeight);
    };

    class GPAPI BestHeightFit final : public ScoredFit {
    public:
        BestHeightFit(float binWidth, float binHeight);
    };

    class GPAPI WorstHeightFit final : public ScoredFit {
    public:
        WorstHeightFit(float binWidth, float binHeight);
    };

    class GPAPI BestAreaFit final : public ScoredFit {
    public:
        BestAreaFit(float binWidth, float binHeight);
    };

    class GPAPI WorstAreaFit final : public ScoredFit {
    public:
        WorstAreaFit(float binWidth, float binHeight);
    };
}
