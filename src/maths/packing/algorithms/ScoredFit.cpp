#include "ScoredFit.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing {
    ScoredFit::ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction)
            : ShelfPackingAlgorithm(binWidth, binHeight),
              m_ScoringFunction(std::move(scoringFunction)) {
    }

    void ScoredFit::pack(Item &item, bool allowRotation) {
        ShelvedBin *bestBin = nullptr;
        Shelf *bestShelf = nullptr;
        float bestScore = -std::numeric_limits<float>::infinity();
        bool bestOrientation = false;  // un-rotated

        for (auto &bin: m_Bins) {
            for (auto &shelf: bin) {
                orientItemForShelf(item, shelf, allowRotation);
                if (bin.fitsShelf(item, shelf)) {
                    float score = m_ScoringFunction(shelf, item);
                    if (score <= bestScore)
                        continue;

                    bestBin = &bin;
                    bestShelf = &shelf;
                    bestScore = score;
                    bestOrientation = item.isRotated();
                }
            }

            if (bestShelf == nullptr and tryAddingToNewShelf(item, bin, allowRotation))
                return;
        }

        if (bestBin == nullptr or bestShelf == nullptr)  // or bestShelf == nullptr is only for IDE type checking
            return addItemToNewBin(item, allowRotation);

        if (item.isRotated() != bestOrientation)
            item.rotate();

        addItemToShelf(item, *bestBin, *bestShelf);
    }
}
