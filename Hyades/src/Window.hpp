#pragma once

#include "GLFW/glfw3.h"
#include "HyadesPCH.hpp"

namespace Hyades
{
    class Window
    {
    private:

        GLFWwindow* m_window;

        int m_width;
        int m_height;

        std::string m_title;

    public:
        Window(const std::string& title, const int& width, const int& height);
        ~Window();

        void onUpdate();
        
        // getters
        int const& width() const { return m_width; };
        int const& height() const { return m_height; }; 

        // setters
        int& width() { return m_width; }
        int& height() { return m_height; }

        // callbacks
        static void setWindowSizeCallback(GLFWwindow* window, int width, int height);


    };


} // namespace Hyades


