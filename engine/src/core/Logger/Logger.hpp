#pragma once

#include <spdlog/spdlog.h>

namespace Engine
{
class Logger
{
  public:
    inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetEditorLogger() { return s_EditorLogger; }

    static void Init();

  private:
    static std::shared_ptr<spdlog::logger> s_EngineLogger;
    static std::shared_ptr<spdlog::logger> s_EditorLogger;
};
} // namespace Engine

#ifdef PLATFORM_WINDOWS
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif

#ifdef DEBUG

#define ENGINE_TRACE(...) ::Engine::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...) ::Engine::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define EDITOR_TRACE(...) ::Engine::Logger::GetEditorLogger()->trace(__VA_ARGS__)
#define EDITOR_INFO(...) ::Engine::Logger::GetEditorLogger()->info(__VA_ARGS__)

#elif RELEASE

#define ENGINE_TRACE(...)
#define ENGINE_INFO(...)
#define EDITOR_TRACE(...)
#define EDITOR_INFO(...)

#endif

#define ENGINE_WARN(...) ::Engine::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_ASSERT(x, ...)                                                                                          \
    {                                                                                                                  \
        if (!(x)) {                                                                                                    \
            ENGINE_ERROR("Assertion failed: {0}", __VA_ARGS__);                                                        \
            DEBUG_BREAK();                                                                                             \
        }                                                                                                              \
    }

#define EDITOR_WARN(...) ::Engine::Logger::GetEditorLogger()->warn(__VA_ARGS__)
#define EDITOR_ERROR(...) ::Engine::Logger::GetEditorLogger()->error(__VA_ARGS__)
#define EDITOR_ASSERT(x, ...)                                                                                          \
    {                                                                                                                  \
        if (!(x)) {                                                                                                    \
            EDITOR_ERROR("Assertion failed: {0}", __VA_ARGS__);                                                        \
            DEBUG_BREAK();                                                                                             \
        }                                                                                                              \
    }