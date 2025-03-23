#pragma once

#include "../Buffer.hpp"
#include <glad/glad.h>

namespace Engine
{
constexpr GLenum BufferUsageToOpenGLUsage(BufferUsage usage)
{
    switch (usage) {
    case BufferUsage::Static:
        return GL_STATIC_DRAW;
    case BufferUsage::Dynamic:
        return GL_DYNAMIC_DRAW;
    case BufferUsage::Stream:
        return GL_STREAM_DRAW;
    default:
        Logger::EngineAssert(false, "Unknown BufferUsage!");
        return 0;
    }
}
} // namespace Engine