#pragma once
#include "GLFW/glfw3.h"
#include "Window.hpp"

namespace Hyades
{
    class Application
    {
    private:
        bool m_running{ false };
        std::unique_ptr<Window> m_window{ nullptr };

    
    public:
        Application();
        ~Application();

        void run();
        static void on_window_close(GLFWwindow* window);

    };

    // defined in client
    Application* createApplication();


}