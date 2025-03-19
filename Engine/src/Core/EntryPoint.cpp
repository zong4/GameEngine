#include "EnginePCH.hpp"

// Core
#include "Core/Application/Application.hpp"
#include "Core/Logger/Logger.hpp"

int main(int argc, char** argv)
{
    Engine::Logger::Init();
    ENGINE_INFO("Engine startup");

    auto app = Engine::CreateApplication();
    app->Run();

    ENGINE_INFO("Engine shutdown");
}