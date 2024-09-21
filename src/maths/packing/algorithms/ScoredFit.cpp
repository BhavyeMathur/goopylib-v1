#include "ScoredFit.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing::shelf {
    ScoredFit::ScoredFit(float
                         binWidth, float
                         binHeight, ScoringFunction
                         scoringFunction)
            : ShelfPackingAlgorithm(binWidth, binHeight),
              m_ScoringFunction(std::move(scoringFunction)) {
    }

    void ScoredFit::pack(Item &item, bool allowRotation) {
        shared_ptr<Shelf> bestShelf = nullptr;
        float bestScore = -std::numeric_limits<float>::infinity();
        bool bestOrientation = false;  // un-rotated

        for (const auto &bin: m_Bins) {
            for (const auto &shelf: *bin) {
                if (allowRotation and (item.isVertical() != (item.getLongSide() <= shelf->getHeight())))
                    item.rotate();

                if (shelf->fits(item)) {
                    float score = m_ScoringFunction(*shelf, item);
                    if (score > bestScore) {
                        bestShelf = shelf;
                        bestScore = score;
                        bestOrientation = item.isRotated();
                    }
                }
            }

            if (bestShelf == nullptr and bin->m_OpenShelf->fitsAbove(item)) {
                auto shelf = bin->addShelf();

                float score = m_ScoringFunction(*shelf, item);
                if (score > bestScore) {
                    bestShelf = shelf;
                    bestScore = score;
                    bestOrientation = item.isRotated();
                }
            }
        }

        if (bestShelf == nullptr) {
            m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));

            if (allowRotation and item.isVertical())
                item.rotate();

            bestShelf = m_Bins.back()->m_OpenShelf;
            bestOrientation = item.isRotated();
        }

        if (item.isRotated() != bestOrientation)
            item.rotate();

        addItemToShelf(item, *bestShelf);
    }
}
