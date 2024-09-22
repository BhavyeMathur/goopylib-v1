#include "ScoredFit.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing::shelf {
    ScoredFit::ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction)
            : ShelfPackingAlgorithm(binWidth, binHeight),
              m_ScoringFunction(std::move(scoringFunction)) {
    }

    void ScoredFit::updateScore(float &bestScore, bool &bestOrientation, Shelf *&bestShelf, Shelf &shelf, Item &item) {
        float score = m_ScoringFunction(shelf, item);

        if (score <= bestScore)
            return;

        bestShelf = &shelf;
        bestScore = score;
        bestOrientation = item.isRotated();
    }

    void ScoredFit::pack(Item &item, bool allowRotation) {
        Shelf *bestShelf = nullptr;
        float bestScore = -std::numeric_limits<float>::infinity();
        bool bestOrientation = false;  // un-rotated

        for (auto &bin: m_Bins) {
            for (auto &shelf: bin) {
                orientItemForShelf(item, shelf, allowRotation);
                if (shelf.fits(item))
                    updateScore(bestScore, bestOrientation, bestShelf, shelf, item);
            }

            if (bestShelf == nullptr and tryAddingToNewShelf(item, bin.getOpenShelf(), bin, allowRotation))
                return;
        }

        if (bestShelf == nullptr)
            return addItemToNewBin(item, allowRotation);

        if (item.isRotated() != bestOrientation)
            item.rotate();
        addItemToShelf(item, *bestShelf);
    }
}
