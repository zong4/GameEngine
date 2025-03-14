#pragma once

#include "Logger/Logger.hpp"
#include "Application/Application.hpp"

int main(int argc, char **argv)
{
    Engine::Logger::Init();
    ENGINE_INFO("Engine startup");

    auto app = Engine::CreateApplication();
    app->Run();
    delete app;

    ENGINE_INFO("Engine shutdown");
}