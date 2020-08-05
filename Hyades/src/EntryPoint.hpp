#pragma once
#include "Logger.hpp"

extern Hyades::Application* Hyades::createApplication();

int main()
{
    Hyades::Logger::init();
    Hyades::Logger::s_logger->info("starting app");
    
    // create a Hyades instance
    Hyades::Application* app = Hyades::createApplication();

    // run the main loop
    app ->run();

    // free resources
    delete app;
}