#include "Bin.h"
#include "Item.h"

namespace gp::packing {
    Bin::Bin(float width, float height)
            : m_Width(width),
              m_Height(height) {
    }

    void Bin::add(Item &item) {
        m_Items.push_back(item);
    }

    float Bin::packingRatio() const {
        float sum = 0;
        for (auto &item: m_Items)
            sum += item.area();

        return sum / (m_Width * m_Height);
    }

    const std::vector<Item> &Bin::items() const {
        return m_Items;
    }

    float Bin::getWidth() const {
        return m_Width;
    }

    float Bin::getHeight() const {
        return m_Height;
    }
}
