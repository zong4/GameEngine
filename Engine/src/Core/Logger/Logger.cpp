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

    s_EngineLogger->info("Logger is initialized");
}

void Engine::Logger::Shutdown()
{
    s_EngineLogger->info("Engine logger is shutdown");
    s_EngineLogger->flush();

    s_EditorLogger->info("Editor logger is shutdown");
    s_EditorLogger->flush();
}

#ifdef DEBUG
void Engine::Logger::EngineTrace(const std::string& message)
{
    s_EngineLogger->trace(message);
}

void Engine::Logger::EngineInfo(const std::string& message)
{
    s_EngineLogger->info(message);
}

void Engine::Logger::EngineWarn(const std::string& message)
{
    s_EngineLogger->warn(message);
}

void Engine::Logger::EngineError(const std::string& message)
{
    s_EngineLogger->error(message);
}

void Engine::Logger::EngineAssert(bool condition, const std::string& message)
{
    if (!condition) {
        s_EngineLogger->error(message);

#ifdef _WIN32
        __debugbreak();
#else
        __builtin_trap();
#endif
    }
}

void Engine::Logger::EditorTrace(const std::string& message)
{
    s_EditorLogger->trace(message);
}

void Engine::Logger::EditorInfo(const std::string& message)
{
    s_EditorLogger->info(message);
}

void Engine::Logger::EditorWarn(const std::string& message)
{
    s_EditorLogger->warn(message);
}

void Engine::Logger::EditorError(const std::string& message)
{
    s_EditorLogger->error(message);
}

void Engine::Logger::EditorAssert(bool condition, const std::string& message)
{
    if (!condition) {
        s_EditorLogger->error(message);

#ifdef _WIN32
        __debugbreak();
#else
        __builtin_trap();
#endif
    }
}
#elif RELEASE
void Engine::Logger::EngineTrace(const std::string& message)
{
}

void Engine::Logger::EngineInfo(const std::string& message)
{
}

void Engine::Logger::EngineWarn(const std::string& message)
{
}

void Engine::Logger::EngineAssert(bool condition, const std::string& message)
{
}

void Engine::Logger::EditorTrace(const std::string& message)
{
}

void Engine::Logger::EditorInfo(const std::string& message)
{
}

void Engine::Logger::EditorWarn(const std::string& message)
{
}

void Engine::Logger::EditorAssert(bool condition, const std::string& message)
{
}
#endif