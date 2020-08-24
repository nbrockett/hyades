#include "Window.hpp"


namespace Hyades
{
    Window::Window(const std::string& title, const size_t& width, const size_t& height) : 
    m_title{title}, m_width{width}, m_height{height}
    {   
        if (!glfwInit())
        {
            Hyades::Logger::s_logger->error("ERROR: Failed to initialize GLFW");
        }

        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_window)
        {
            Hyades::Logger::s_logger->error("ERROR: Failed to create GLFW window");
        }

        Hyades::Logger::s_logger->info("Window initialised");

        // set callback functions
        glfwSetWindowUserPointer(m_window, this);
        glfwSetWindowSizeCallback(m_window, this->on_window_resize);
        glfwSetWindowCloseCallback(m_window, this->on_window_close);
        glfwSetKeyCallback(m_window, this->on_key_press);

        // create render context
        m_render_context = std::make_unique<RenderContext>(*this);

    }
    
    Window::~Window()
    {   
        Hyades::Logger::s_logger->debug("Deconstructing Window");
        
        m_render_context->destroy();
        
        glfwDestroyWindow(m_window);
    }

    void Window::set_event_handler(const std::shared_ptr<EventHandler> handler)
    {
        m_event_handler = handler;
    }


    void Window::on_update()
    {
        // Hyades::Logger::s_logger->critical("Updating!");
        while (!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();
            glfwSwapBuffers(m_window);
            m_render_context->render();
        }
    }

    void Window::on_window_resize(GLFWwindow* window, int width, int height)
    {

        Hyades::Logger::s_logger->info("changing window size!");
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        win->width() = width;
        win->height() = height;

        WindowResizeEvent event(width, height);
        win->m_event_handler->trigger(event);
    }

    void Window::on_window_close(GLFWwindow* window)
    {
        Hyades::Logger::s_logger->info("closing window!");
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        glfwSetWindowShouldClose(window, GLFW_TRUE);

        WindowCloseEvent event;
        win->m_event_handler->trigger(event);
    }

    void Window::on_key_press(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
            case GLFW_PRESS:
            {
                auto str_message = std::string("Key ") + std::to_string(key) + std::string(" pressed!");
                Hyades::Logger::s_logger->info(str_message);

                win->m_event_handler->trigger(KeyPressedEvent(static_cast<KeyCode>(key)));
                break;
            }
            case GLFW_RELEASE:
            {
                auto str_message = std::string("Key ") + std::to_string(key) + std::string(" released!");
                Hyades::Logger::s_logger->info(str_message);

                win->m_event_handler->trigger(KeyReleasedEvent(static_cast<KeyCode>(key)));
                break;
            }
            case GLFW_REPEAT:
            {
                auto str_message = std::string("Key ") + std::to_string(key) + std::string(" repeated!");
                Hyades::Logger::s_logger->info(str_message);

                win->m_event_handler->trigger(KeyRepeatEvent(static_cast<KeyCode>(key)));
                break;
            }
        }
    }

} // namespace Hyades


