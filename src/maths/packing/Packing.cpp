#define GP_LOGGING_LEVEl 3

#include "Packing.h"

// Item Class
namespace gp::packing {
    uint32_t Item::s_Items = 0;

    Item::Item(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_LongSide(max(width, height)),
              m_ShortSide(min(width, height)),
              m_ID(Item::s_Items) {
        Item::s_Items++;
    }

    void Item::rotate() {
        const float tmp = m_Width;
        m_Width = m_Height;
        m_Height = tmp;

        m_Rotated = !m_Rotated;
    }

    bool Item::isVertical() const {
        return m_Height > m_Width;
    }

    bool Item::isHorizontal() const {
        return m_Width > m_Height;
    }

    bool Item::isRotated() const {
        return m_Rotated;
    }

    float Item::area() const {
        return m_Width * m_Height;
    }

    Point Item::p1() const {
        return {m_X, m_Y};
    }

    Point Item::p2() const {
        return {m_X + m_Width, m_Y + m_Height};
    }

    float Item::getX() const {
        return m_X;
    }

    float Item::getY() const {
        return m_Y;
    }

    float Item::getWidth() const {
        return m_Width;
    }

    float Item::getHeight() const {
        return m_Height;
    }

    float Item::getLongSide() const {
        return m_LongSide;
    }

    float Item::getShortSide() const {
        return m_ShortSide;
    }
}

// Bin Class
namespace gp::packing {
    uint32_t Bin::s_Bins = 0;

    Bin::Bin(float width, float height)
            : m_Width(width),
              m_Height(height),
              m_ID(Bin::s_Bins) {
        Bin::s_Bins++;
    }

    void Bin::add(const shared_ptr<Item> &item) {
        m_Items.push_back(item);
    }

    float Bin::packingRatio() const {
        float sum = 0;
        for (auto &item: m_Items) {
            sum += item->area();
        }

        return sum / (m_Width * m_Height);
    }

    std::vector<shared_ptr<Item>> Bin::items() const {
        std::vector<shared_ptr<Item>> copy = m_Items;
        return copy;
    }

    float Bin::getWidth() const {
        return m_Width;
    }

    float Bin::getHeight() const {
        return m_Height;
    }
}

#define RETURN_SORTING_FUNC return [compare](std::vector<shared_ptr<Item>> items) {std::sort(items.begin(), items.end(), compare); return items;}

// Sorting Algorithms
namespace gp::packing {
    SortingFunction sortByWidth(bool descending) {

        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getWidth() > item2->getWidth();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getWidth() < item2->getWidth();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByHeight(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getHeight() > item2->getHeight();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getHeight() < item2->getHeight();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByPerimeter(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() + item1->getHeight()) >
                       (item2->getWidth() + item2->getHeight());
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() + item1->getHeight()) <
                       (item2->getWidth() + item2->getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByArea(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() * item1->getHeight()) >
                       (item2->getWidth() * item2->getHeight());
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() * item1->getHeight()) <
                       (item2->getWidth() * item2->getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortBySideRatio(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() / item1->getHeight()) >
                       (item2->getWidth() / item2->getHeight());
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() / item1->getHeight()) <
                       (item2->getWidth() / item2->getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByLongSide(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getLongSide() > item2->getLongSide();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getLongSide() < item2->getLongSide();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByShortSide(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getShortSide() > item2->getShortSide();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getShortSide() < item2->getShortSide();
            };

        RETURN_SORTING_FUNC;
    }
}

// Packing Algorithm Class
namespace gp::packing {
    PackingAlgorithm::PackingAlgorithm(float binWidth, float binHeight)
            : m_BinWidth(binWidth),
              m_BinHeight(binHeight) {
    }
}
