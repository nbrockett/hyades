#pragma once

extern Hyades::Application* Hyades::createApplication();

int main()
{
    auto app = Hyades::createApplication();
    app ->run();
    delete app;
}