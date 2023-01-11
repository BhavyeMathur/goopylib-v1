#include "Font.h"

#include "src/config.h"

#if (GP_LOG_FONT != true) and (GP_LOG_FONT <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_FONT
#endif

#if !GP_VALUE_CHECK_FONT
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"

namespace gp {
    Font::~Font() {
        GP_CORE_DEBUG("gp::Font::~Font()");
        for (auto &glyph: glyphs) {
            delete glyph.second;
        }
    }
}
