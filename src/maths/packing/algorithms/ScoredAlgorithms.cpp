#include "ScoredAlgorithms.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"

#include "maths/gpmath.h"


namespace gp::packing::shelf {
    BestWidthFit::BestWidthFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return obj.width() - shelf.getAvailableWidth();
                        }) {
    }

    WorstWidthFit::WorstWidthFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return shelf.getAvailableWidth() - obj.width();
                        }) {
    }

    BestHeightFit::BestHeightFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return obj.height() - shelf.height();
                        }) {
    }

    WorstHeightFit::WorstHeightFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return shelf.height() - obj.height();
                        }) {
    }

    BestAreaFit::BestAreaFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return (shelf.getPackedWidth() + obj.width()) * max(obj.height(), shelf.height());
                        }) {
    }

    WorstAreaFit::WorstAreaFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return -(shelf.getPackedWidth() + obj.width()) * max(obj.height(), shelf.height());
                        }) {
    }
}
