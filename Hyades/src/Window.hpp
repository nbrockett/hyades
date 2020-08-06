#pragma once

#include "GLFW/glfw3.h"
#include "HyadesPCH.hpp"

namespace Hyades
{
    class Window
    {
    private:

        GLFWwindow* m_window;

        int m_width{ 800 };
        int m_height{ 600 };

        const std::string m_title{ "Hyades Window" };

    public:
        Window(const std::string& title, const int& width, const int& height);
        ~Window();

        void on_update();
        
        // getters
        int const& width() const { return m_width; };
        int const& height() const { return m_height; }; 

        // setters
        int& width() { return m_width; }
        int& height() { return m_height; }

        // callbacks
        static void set_window_size_callback(GLFWwindow* window, int width, int height);
        static void set_window_close_callback(GLFWwindow* window);


    };


} // namespace Hyades


