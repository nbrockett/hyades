#pragma once
#include "GLFW/glfw3.h"
#include "Window.hpp"
#include "Event.hpp"
#include "Renderer/RenderContext.hpp"

namespace Hyades
{
    class Application
    {
    private:
        bool m_running{ false };
        std::unique_ptr<Window> m_window{ nullptr };
        std::shared_ptr<EventHandler> m_event_handler{ nullptr };

        RenderContext m_renderer = RenderContext();

    public:
        Application();
        ~Application();

        void run();

        void on_window_close(const WindowCloseEvent& event);
        void on_window_resize(const WindowResizeEvent& event);

    };

    // defined in client
    Application* createApplication();


}