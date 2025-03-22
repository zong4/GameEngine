#pragma once

#include <chrono>

namespace Engine
{
class Timestep
{
  public:
    Timestep() = default;
    Timestep(std::chrono::duration<double> time) : m_Time(time) {}

    operator double() const { return m_Time.count(); }

  public:
    double Seconds() const { return m_Time.count(); }
    double Milliseconds() const { return m_Time.count() * 1000.0; }

  private:
    std::chrono::duration<double> m_Time;
};
} // namespace Engine