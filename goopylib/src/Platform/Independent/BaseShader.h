#pragma once

#include "pch.h"


namespace gp {
    class BaseShader {
    public:
        virtual ~BaseShader() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;
    };
}
