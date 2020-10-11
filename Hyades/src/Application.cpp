#include "Application.hpp"
#include "Logger.hpp"
#include "Window.hpp"
#include "Event.hpp"

namespace Hyades
{
    // Application::Application(const std::string& name, const int& width, const int& height) : m_running(true), m_window(std::make_unique<Window>(Window(name, width, height))) 

    Application::Application() : m_running{true}, m_window{std::make_unique<Window>("yep", 800, 600)},
                                 m_event_handler{std::make_shared<EventHandler>()}
    {
        Hyades::Logger::s_logger->info("Initializing Hyades Application");

        // set window object bindings
        m_window->set_event_handler(m_event_handler);

        // set application event callback functions
        m_event_handler->add_handler<WindowCloseEvent>(std::bind(&Application::on_window_close, this, std::placeholders::_1));
        m_event_handler->add_handler<WindowResizeEvent>(std::bind(&Application::on_window_resize, this, std::placeholders::_1));
        // m_event_handler->add_handler<WindowCloseEvent>(std::bind_front(Application::on_window_close));
    }


    Application::~Application()
    {
        Hyades::Logger::s_logger->info("Terminating Application");

    }

    void Application::run()
    {
        while (m_running)
        {
            m_window->on_update();
        }

    }

    void Application::on_window_close(const WindowCloseEvent& event)
    {
        Hyades::Logger::s_logger->info("Stopping Application run..");
        m_running = false;
    }

    void Application::on_window_resize(const WindowResizeEvent& event)
    {
        Hyades::Logger::s_logger->info("Resize event triggered..");
        // m_render_context.on_window_resize(event.width(), event.height());
    }


} // namespace Hyades



