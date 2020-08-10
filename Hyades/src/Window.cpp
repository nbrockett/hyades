#include "Window.hpp"

namespace Hyades
{
    Window::Window(const std::string& title, const size_t& width, const size_t& height) : m_title{title}, m_width{width}, m_height{height}
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
        glfwSetWindowSizeCallback(m_window, this->set_window_size_callback);
        glfwSetWindowCloseCallback(m_window, this->set_window_close_callback);

    }
    
    Window::~Window()
    {   
        glfwDestroyWindow(m_window);
    }

    void Window::on_update()
    {
        Hyades::Logger::s_logger->critical("Updating!");
        while (!glfwWindowShouldClose(m_window))
        {
            // render(m_window);
            // Hyades::Logger::s_logger->debug("Looping!");
            // m_window->
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

    void Window::set_window_size_callback(GLFWwindow* window, int width, int height)
    {

        Hyades::Logger::s_logger->info("changing window size!");
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        win->width() = width;
        win->height() = height;


    }

    void Window::set_window_close_callback(GLFWwindow* window)
    {
        Hyades::Logger::s_logger->info("closing widnow!");
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        
    }

} // namespace Hyades


