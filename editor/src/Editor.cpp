#include <iostream>

#include <engine.hpp>

class Editor : public Engine::Application
{
public:
    Editor()
    {
        EDITOR_INFO("Editor constructor");
    }

    ~Editor()
    {
        EDITOR_INFO("Editor destructor");
    }
};

Engine::Application *Engine::CreateApplication()
{
    return new Editor();
}