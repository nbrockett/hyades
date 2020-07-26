#pragma once
#include "GLFW/glfw3.h"


namespace Hyades
{
    class Application
    {
    private:
        bool m_running{false};
        GLFWwindow* m_window{nullptr};
    
    public:
        Application(/* args */);
        ~Application();

        void run();
        static void onWindowClose(GLFWwindow* window);


    };

    // defined in client
    Application* createApplication();


}