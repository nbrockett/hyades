#pragma once
#include "GLFW/glfw3.h"
#include "Window.hpp"

namespace Hyades
{
    class Application
    {
    private:
        bool m_running;
        std::unique_ptr<Window> m_window;

    
    public:
        Application();
        ~Application();

        void run();
        static void onWindowClose(GLFWwindow* window);

    };

    // defined in client
    Application* createApplication();


}