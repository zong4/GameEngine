#pragma once

#include <engine.hpp>

class Editor : public Engine::Application
{
public:
    Editor() = default;
    virtual ~Editor() noexcept override = default;

    void Init() override;
    void Run() override;
    void Shutdown() override;
};