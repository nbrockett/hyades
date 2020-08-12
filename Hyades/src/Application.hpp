#pragma once
#include "GLFW/glfw3.h"
#include "Window.hpp"
#include "Event.hpp"

namespace Hyades
{
    class Application
    {
    private:
        bool m_running{ false };
        std::unique_ptr<Window> m_window{ nullptr };
        std::shared_ptr<EventHandler> m_event_handler{ nullptr };
    
    public:
        Application();
        ~Application();

        void run();

        void on_window_close(const WindowCloseEvent& event);

    };

    // defined in client
    Application* createApplication();


}