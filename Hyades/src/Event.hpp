#pragma once

#include "HyadesPCH.hpp"

namespace Hyades
{



    enum class EventType 
    {
        WindowClose, WindowResize
    };


    class Event
    {
    private:
        // EventType m_type = 0

    public:
        virtual ~Event() = default;
        // virtual Event() = 0;
    
        virtual EventType type() const = 0;
    
    
    };


    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() : m_type{EventType::WindowClose}
        {   }

        EventType type() const { return m_type; }


    private:
        EventType m_type;

    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(size_t width, size_t height) : m_width(width), m_height(height), m_type{EventType::WindowResize}
        {   }

        size_t const& width() const { return m_width; };
        size_t const& height() const { return m_height; };

        EventType type() const { return m_type; }

    private:
        size_t m_width;
        size_t m_height;
        EventType m_type;

    };


    class EventHandler
    {
    public:
        EventHandler() = default;


        void add_handler(std::function<void(const WindowCloseEvent&)> callback_func)
        {
            m_handler_map.insert(std::make_pair(EventType::WindowClose, callback_func));
        }

        void trigger(const WindowCloseEvent& event)
        {
            auto event_type = event.type();
            std::invoke(m_handler_map.at(event_type), event);

        }


    private:
        std::map<EventType, std::function<void(const WindowCloseEvent&)> > m_handler_map;

    };


} // namespace Hyades




