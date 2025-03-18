#pragma once

#include "EnginePCH.hpp"

// Core
#include <glm/glm.hpp>

namespace Engine
{
inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec)
{
    os << "vec2: (" << vec.x << ", " << vec.y << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
    os << "vec3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vec)
{
    os << "vec4: (" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}
} // namespace Engine