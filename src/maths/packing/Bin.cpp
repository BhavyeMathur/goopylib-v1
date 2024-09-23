#define GP_LOGGING_LEVEl 3

#include "Bin.h"
#include "Item.h"

namespace gp::packing {
    Bin::Bin(float width, float height, uint32_t page)
            : m_Width(width),
              m_Height(height),
              m_Page(page) {
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

    float Bin::width() const {
        return m_Width;
    }

    float Bin::height() const {
        return m_Height;
    }

    uint32_t Bin::page() const {
        return m_Page;
    }
}
