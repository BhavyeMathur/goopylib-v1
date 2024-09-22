#include "ScoredAlgorithms.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"

#include "maths/gpmath.h"


namespace gp::packing::shelf {
    BestWidthFit::BestWidthFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return obj.getWidth() - shelf.getAvailableWidth();
                        }) {
    }

    WorstWidthFit::WorstWidthFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return shelf.getAvailableWidth() - obj.getWidth();
                        }) {
    }

    BestHeightFit::BestHeightFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return obj.getHeight() - shelf.getHeight();
                        }) {
    }

    WorstHeightFit::WorstHeightFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return shelf.getHeight() - obj.getHeight();
                        }) {
    }

    BestAreaFit::BestAreaFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return (shelf.getPackedWidth() + obj.getWidth()) * max(obj.getHeight(), shelf.getHeight());
                        }) {
    }

    WorstAreaFit::WorstAreaFit(float binWidth, float binHeight)
            : ScoredFit(binWidth, binHeight,
                        [](const Shelf &shelf, const Item &obj) {
                            return -(shelf.getPackedWidth() + obj.getWidth()) * max(obj.getHeight(), shelf.getHeight());
                        }) {
    }
}
