#include "Application.hpp"
#include "Logger.hpp"

namespace Hyades
{
    Application::Application(/* args */)
    {
        if (!glfwInit())
        {
            Hyades::Logger::s_logger->error("ERROR: Failed to initialize GLFW");
        }

        m_window = glfwCreateWindow(640, 480, "Hyades", NULL, NULL);
        if (!m_window)
        {
            Hyades::Logger::s_logger->error("ERROR: Failed to create GLFW window");
        }

        // TODO: fix this
        // glfwSetWindowCloseCallback(m_window, onWindowClose);

        m_running = true;

    }

    Application::~Application()
    {
        Hyades::Logger::s_logger->info("Terminating Application");
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Application::run() 
    {
        

        while (m_running)
        {
            while (!glfwWindowShouldClose(m_window))
            {
                // render(m_window);
            
                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }

        }
        

    }

    void Application::onWindowClose(GLFWwindow* window) 
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

} // namespace Hyades



