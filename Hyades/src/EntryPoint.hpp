#pragma once

#include "Logger.hpp"

extern Hyades::Application* Hyades::createApplication();

int main()
{

    Hyades::Logger::init();
    Hyades::Logger::s_logger->info("Initialised Log!");
    Hyades::Logger::s_logger->error("Testing errror");

    auto app = Hyades::createApplication();

    app ->run();
    delete app;
}