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

        // glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        // {
        //     GLFWwindow* window_handle = static_cast<GLFWwindow*>(glfwGetWindowUserPointer(window));

        //     window_handle->width() = width;
        //     window_handle->height() = height;
        // }
        // )

        Hyades::Logger::s_logger->info("Window initialised");

        // set callback functions
        glfwSetWindowUserPointer(m_window, this);
        glfwSetWindowSizeCallback(m_window, this->on_window_resize);
        glfwSetWindowCloseCallback(m_window, this->on_window_close);


    }
    
    Window::~Window()
    {   
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
            // render(m_window);
            // Hyades::Logger::s_logger->debug("Looping!");
            // m_window->
            glfwSwapBuffers(m_window);
            glfwPollEvents();
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

} // namespace Hyades


