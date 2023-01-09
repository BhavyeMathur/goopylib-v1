#include "Bitmap.h"


namespace gp {
    Bitmap::Bitmap(float width, float height)
            : m_Width(width),
              m_Height(height) {

    }

    float Bitmap::getWidth() const {
        return m_Width;
    }

    float Bitmap::getHeight() const {
        return m_Height;
    }
}
