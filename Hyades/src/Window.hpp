#pragma once

#include "GLFW/glfw3.h"
#include "HyadesPCH.hpp"
#include "Event.hpp"

namespace Hyades
{
    class Window
    {
    private:

        GLFWwindow* m_window;

        size_t m_width{ 800 };
        size_t m_height{ 600 };

        const std::string m_title{ "Hyades Window" };

        std::shared_ptr<EventHandler> m_event_handler{ nullptr };

    public:
        Window(const std::string& title, const size_t& width, const size_t& height);
        ~Window();

        void set_event_handler(const std::shared_ptr<EventHandler> handler);

        void on_update();
        
        // getters
        size_t const& width() const { return m_width; };
        size_t const& height() const { return m_height; }; 

        // setters
        size_t& width() { return m_width; }
        size_t& height() { return m_height; }

        // callbacks
        static void on_window_resize(GLFWwindow* window, int width, int height);
        static void on_window_close(GLFWwindow* window);


    };


} // namespace Hyades


