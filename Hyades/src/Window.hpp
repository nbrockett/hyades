#pragma once

#include "GLFW/glfw3.h"
#include "HyadesPCH.hpp"

namespace Hyades
{
    class Window
    {
    private:

        GLFWwindow* m_window;

        size_t m_width{ 800 };
        size_t m_height{ 600 };

        const std::string m_title{ "Hyades Window" };

    public:
        Window(const std::string& title, const size_t& width, const size_t& height);
        ~Window();

        void on_update();
        
        // getters
        size_t const& width() const { return m_width; };
        size_t const& height() const { return m_height; }; 

        // setters
        size_t& width() { return m_width; }
        size_t& height() { return m_height; }

        // callbacks
        static void set_window_size_callback(GLFWwindow* window, int width, int height);
        static void set_window_close_callback(GLFWwindow* window);


    };


} // namespace Hyades


