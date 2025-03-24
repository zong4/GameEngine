#pragma once

#include <spdlog/spdlog.h>

namespace Engine
{
class Logger
{
  public:
    static void Init();
    static void Shutdown();

    static void                       EngineTrace(const std::string& message);
    static void                       EngineInfo(const std::string& message);
    static void                       EngineWarn(const std::string& message);
    static void                       EngineError(const std::string& message);
    static void                       EngineAssert(bool condition, const std::string& message);
    template <typename T> static void EngineAssert(T* ptr, const std::string& message) { EngineAssert(ptr != nullptr, message); }
    template <typename T> static void EngineAssert(std::unique_ptr<T>& ptr, const std::string& message) { EngineAssert(ptr.get() != nullptr, message); }

    static void                       EditorTrace(const std::string& message);
    static void                       EditorInfo(const std::string& message);
    static void                       EditorWarn(const std::string& message);
    static void                       EditorError(const std::string& message);
    static void                       EditorAssert(bool condition, const std::string& message);
    template <typename T> static void EditorAssert(T* ptr, const std::string& message) { EditorAssert(ptr != nullptr, message); }
    template <typename T> static void EditorAssert(std::unique_ptr<T>& ptr, const std::string& message) { EditorAssert(ptr.get() != nullptr, message); }

  public:
    static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
    static std::shared_ptr<spdlog::logger>& GetEditorLogger() { return s_EditorLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_EngineLogger;
    static std::shared_ptr<spdlog::logger> s_EditorLogger;
};
} // namespace Engine
