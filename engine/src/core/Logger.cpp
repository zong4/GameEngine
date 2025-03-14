#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Engine::Logger::logger_engine;
std::shared_ptr<spdlog::logger> Engine::Logger::logger_editor;

void Engine::Logger::Init()
{
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    logger_engine = spdlog::stdout_color_mt("ENGINE");
    logger_engine->set_level(spdlog::level::trace);

    logger_editor = spdlog::stdout_color_mt("EDITOR");
    logger_editor->set_level(spdlog::level::trace);
}