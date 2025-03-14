#pragma once

#include <spdlog/spdlog.h>

namespace Engine
{
    class Logger
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetEngineLogger() { return m_EngineLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetEditorLogger() { return m_EditorLogger; }

    private:
        static std::shared_ptr<spdlog::logger> m_EngineLogger;
        static std::shared_ptr<spdlog::logger> m_EditorLogger;
    };
} // namespace Engine

#ifdef DEBUG

#define ENGINE_TRACE(...) ::Engine::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...) ::Engine::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) ::Engine::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Logger::GetEngineLogger()->error(__VA_ARGS__)

#define EDITOR_TRACE(...) ::Engine::Logger::GetEditorLogger()->trace(__VA_ARGS__)
#define EDITOR_INFO(...) ::Engine::Logger::GetEditorLogger()->info(__VA_ARGS__)
#define EDITOR_WARN(...) ::Engine::Logger::GetEditorLogger()->warn(__VA_ARGS__)
#define EDITOR_ERROR(...) ::Engine::Logger::GetEditorLogger()->error(__VA_ARGS__)

#elif RELEASE

#define ENGINE_TRACE(...)
#define ENGINE_INFO(...)
#define ENGINE_WARN(...) ::Engine::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Logger::GetEngineLogger()->error(__VA_ARGS__)

#define EDITOR_TRACE(...)
#define EDITOR_INFO(...)
#define EDITOR_WARN(...) ::Engine::Logger::GetEditorLogger()->warn(__VA_ARGS__)
#define EDITOR_ERROR(...) ::Engine::Logger::GetEditorLogger()->error(__VA_ARGS__)

#endif