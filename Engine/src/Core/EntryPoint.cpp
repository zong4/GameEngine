#include "EnginePCH.hpp"

#include "Core/Application/Application.hpp"
#include "Core/Logger/Logger.hpp"

int main(int argc, char** argv)
{
    Engine::Logger::Init();

    auto& app = Engine::Application::Create();
    app->Init();
    app->Run();
    app->Shutdown();

    return 0;
}