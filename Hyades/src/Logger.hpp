#pragma once

#include "spdlog/spdlog.h"

namespace Hyades
{
    class Logger
    {
    public:
        
        // define static pointer to logger
        static std::shared_ptr<spdlog::logger> s_logger;

        static void init();

    };
} // namespace Hyades

