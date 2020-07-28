#pragma once

extern Hyades::Application* Hyades::createApplication();

int main()
{
    // create a Hyades instance
    auto app = Hyades::createApplication();

    // run the main loop
    app ->run();

    // free resources
    delete app;
}