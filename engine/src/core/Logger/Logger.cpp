#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Engine::Logger::s_EngineLogger;
std::shared_ptr<spdlog::logger> Engine::Logger::s_EditorLogger;

void Engine::Logger::Init()
{
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    s_EngineLogger = spdlog::stdout_color_mt("ENGINE");
    s_EngineLogger->set_level(spdlog::level::trace);

    s_EditorLogger = spdlog::stdout_color_mt("EDITOR");
    s_EditorLogger->set_level(spdlog::level::trace);
}