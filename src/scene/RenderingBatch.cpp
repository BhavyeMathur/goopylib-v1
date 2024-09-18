#include "RenderingBatch.h"

namespace gp {
    RenderingBatch::RenderingBatch(const BufferLayout &layout, const int32_t mode)
            : VAO(layout),
              mode(mode) {
    }
}
