#include "Application/Application.hpp"

int main(int argc, char** argv)
{
    auto& app = Engine::Application::Create();
    app->Init();
    app->Run();
    app->Shutdown();

    return 0;
}