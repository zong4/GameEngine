#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Engine::Logger::m_EngineLogger;
std::shared_ptr<spdlog::logger> Engine::Logger::m_EditorLogger;

void Engine::Logger::Init()
{
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    m_EngineLogger = spdlog::stdout_color_mt("ENGINE");
    m_EngineLogger->set_level(spdlog::level::trace);

    m_EditorLogger = spdlog::stdout_color_mt("EDITOR");
    m_EditorLogger->set_level(spdlog::level::trace);
}