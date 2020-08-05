#include "Application.hpp"
#include "Logger.hpp"
#include "Window.hpp"

namespace Hyades
{
    // Application::Application(const std::string& name, const int& width, const int& height) : m_running(true), m_window(std::make_unique<Window>(Window(name, width, height))) 
    
    Application::Application() : m_running(true), m_window(std::make_unique<Window>("yep", 800, 600))
    {   
        Hyades::Logger::s_logger->info("Initializing Hyades Application");
    }


    Application::~Application()
    {
        // Hyades::Logger::s_logger->info("Terminating Application");
        // glfwDestroyWindow(m_window);
        // glfwTerminate();
    }

    void Application::run() 
    {
        
        
        while (m_running)
        {
            m_window->onUpdate();
        }
        

    }

    void Application::onWindowClose(GLFWwindow* window) 
    {
        Hyades::Logger::s_logger->info("Closing Window...");
        // glfwSetWindowShouldClose(window, GLFW_TRUE);
        // m_running = false;
    }

} // namespace Hyades



