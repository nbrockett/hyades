#pragma once

namespace Hyades
{
    class Application
    {
    private:
        /* data */
    public:
        Application(/* args */);
        ~Application();

        void run();

    };

    // defined in client
    Application* createApplication();

}