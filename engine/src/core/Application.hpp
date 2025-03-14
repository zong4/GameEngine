#pragma once

#include "Logger/Logger.hpp"

namespace Engine
{
    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        void Run();
    };

    extern Application *CreateApplication();
} // namespace Engine