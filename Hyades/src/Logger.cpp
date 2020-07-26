#include "Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Hyades
{
    // initialize static variable
    std::shared_ptr<spdlog::logger> Logger::s_logger;

    void Logger::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_logger = spdlog::stdout_color_mt("HYADES");
        s_logger->set_level(spdlog::level::trace);

    }


} // namespace Hyades

