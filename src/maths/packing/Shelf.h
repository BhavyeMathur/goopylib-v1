#pragma once


#include "gp.h"
#include "Packing.h"

namespace gp::packing {
    class ShelvedBin;

    namespace shelf {
        class ShelfPackingAlgorithm;

        class NextFit;

        class FirstFit;

        class ScoredFit;
    }
}

// Shelf Class
namespace gp::packing::shelf {
    class GPAPI Shelf {

        friend class gp::packing::ShelvedBin;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        [[nodiscard]] std::string toString() const;

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

        [[nodiscard]] float getVerticalOffset() const;

        [[nodiscard]] float getPackedWidth() const;

        [[nodiscard]] float getAvailableWidth() const;

        [[nodiscard]] bool isOpen() const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_VerticalOffset;

        bool m_IsOpen = true;

        Bin &m_Bin;
        std::vector<shared_ptr<Item>> m_Items;

        Shelf(float verticalOffset, Bin &bin);

        [[nodiscard]] bool fits(const shared_ptr<Item> &item) const;

        [[nodiscard]] bool fitsAbove(const shared_ptr<Item> &item) const;

        void add(const shared_ptr<Item>& item);

        void close();

        [[nodiscard]] float packedArea() const;
    };
}

// Shelved Bin Class
namespace gp::packing {
    class GPAPI ShelvedBin final : public Bin {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        [[nodiscard]] float packingRatio() const override;

        shared_ptr<shelf::Shelf> getOpenShelf();

        std::vector<shared_ptr<shelf::Shelf>> getShelves();

        [[nodiscard]] std::vector<shared_ptr<shelf::Shelf>>::const_iterator begin() const;

        [[nodiscard]] std::vector<shared_ptr<shelf::Shelf>>::const_iterator end() const;

    private:
        shared_ptr<shelf::Shelf> m_OpenShelf;
        std::vector<shared_ptr<shelf::Shelf>> m_Shelves;

        ShelvedBin(float width, float height);

        shared_ptr<shelf::Shelf> addShelf();
    };
}

// Shelf Packing Algorithms Classes
namespace gp::packing::shelf {
    using ScoringFunction = std::function<float(const shared_ptr<gp::packing::shelf::Shelf> &,
                                                const shared_ptr<Item> &)>;

    class GPAPI ShelfPackingAlgorithm : public PackingAlgorithm {

    public:
        ShelfPackingAlgorithm();

        virtual ~ShelfPackingAlgorithm() = default;

        virtual void pack(const shared_ptr<Item>& item, bool allowRotation);

        void packAll(std::vector<shared_ptr<Item>> items,
                     bool allowRotation = true,
                     const SortingFunction &sortingFunction = sortByShortSide(true));

        void packOriented(const shared_ptr<Item>& item, bool orientVertically = true);

        void packAllOriented(std::vector<shared_ptr<Item>> items,
                             bool orientVertically = true,
                             const SortingFunction &sortingFunction = sortByLongSide(true));

        [[nodiscard]] std::vector<shared_ptr<ShelvedBin>> bins() const;

    protected:
        ShelfPackingAlgorithm(float binWidth, float binHeight);

        std::vector<shared_ptr<ShelvedBin>> m_Bins;
    };

    class GPAPI NextFit final : public ShelfPackingAlgorithm {

    public:
        NextFit(float binWidth, float binHeight);

        void pack(const shared_ptr<Item> &item, bool allowRotation) override;

    private:
        shared_ptr<Shelf> m_Shelf;
    };

    class GPAPI FirstFit final : public ShelfPackingAlgorithm {

    public:
        FirstFit(float binWidth, float binHeight);

        void pack(const shared_ptr<Item> &item, bool allowRotation) override;
    };

    class GPAPI ScoredFit : public ShelfPackingAlgorithm {

    public:
        ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction);

        void pack(const shared_ptr<Item> &item, bool allowRotation) override;

    private:
        ScoringFunction m_ScoringFunction;
    };

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
