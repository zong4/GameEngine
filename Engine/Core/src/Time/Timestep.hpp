#pragma once

#include <chrono>

namespace Engine {
class Timestep
{
public:
    Timestep() = default;
    Timestep(std::chrono::duration<float> time) : m_Time(time) {}

    operator float() const { return m_Time.count(); }

public:
    float Seconds() const { return m_Time.count(); }
    float Milliseconds() const { return m_Time.count() * 1000.0f; }

private:
    std::chrono::duration<float> m_Time;
};
} // namespace Engine