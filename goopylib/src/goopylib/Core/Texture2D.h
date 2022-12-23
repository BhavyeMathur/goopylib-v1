#pragma once

#include "pch.h"

namespace gp {
    class Texture2D {

        friend class Renderer;

    public:
        ~Texture2D();

    private:
        int32_t m_Width = 0;
        int32_t m_Height = 0;
        int32_t m_Channels = 0;

        u_char *m_Data;
        const char *m_Path;

        uint32_t m_RendererID = 0;
        uint32_t m_Slot = 0;

        explicit Texture2D(const char *path);

        void init(uint32_t slot);

        void bind() const;

        static void unbind() ;
    };
}
